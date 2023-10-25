#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdbool.h>
#include "./utils/check_valid_ip_address.h"

#define MAX_BUFFER_SIZE 1024

// Check if the port number is valid or not
bool is_valid_port(char port_str[]) {
    int port_num = atoi(port_str);
    int len = strlen(port_str);
    
    // Check for boundary
    if (port_num < 1 || port_num > 65535) {
        return false;
    }

    // Check for format
    for (int i = 0; i < len; ++i) {
        if (!isdigit(port_str[i])) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Syntax: ./client <IP Address> <Port number>\n");
        return 1;
    }

    // Resolve the IP address
    char *ip_address = strdup(argv[1]);
    // Resolve the port number from cmd => Convert to number
    int port_num = atoi(argv[2]);

    // If the IP address is invalid
    if (!is_valid_ip_address(argv[1]))
    {
        printf("Invalid IP address\n");
        return 1;
    }

    // If the port is invalid, exit the program
    if (!is_valid_port(argv[2]))
    {
        printf("Invalid port number\n");
        return 1;
    }

    // printf("IP address: %s\n", ip_address);
    // printf("Port number: %s\n", argv[2]);

    // Socket variables declaration
    int sockfd; // Naming convention: fd?
    socklen_t n, len;
    struct sockaddr_in server_address;

    char username[MAX_BUFFER_SIZE];
    char password[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("Create socket failed");
        // exit(1)
        exit(EXIT_FAILURE);
    }

    // Initialize
    memset(&server_address, 0, sizeof(server_address));

    // Config
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_num);
    server_address.sin_addr.s_addr = inet_addr(ip_address);

    printf("Username: ");
    // Able to ignore whitespace at the end
    fgets(username, sizeof(username), stdin);
    // Remove the newline character at the end of the username
    username[strcspn(username, "\n")] = 0;
    sendto(sockfd, (const char *)username, strlen(username), MSG_CONFIRM, (const struct sockaddr *)&server_address, sizeof(server_address));

    n = recvfrom(sockfd, (char *)buffer, MAX_BUFFER_SIZE, MSG_WAITALL, NULL, &len);
    buffer[n] = '\0';
    printf("%s\n", buffer);

    // If the account is not found, then make user enter again
    while (strcmp(buffer, "Account not found") == 0)
    {
        printf("\nRe-enter username: ");
        fgets(username, sizeof(username), stdin);
        // Repeat the same process above to send to server and receive response
        username[strcspn(username, "\n")] = 0;
        sendto(sockfd, (const char *)username, strlen(username), MSG_CONFIRM, (const struct sockaddr *)&server_address, sizeof(server_address));
        
        n = recvfrom(sockfd, (char *)buffer, MAX_BUFFER_SIZE, MSG_WAITALL, NULL, &len);
        buffer[n] = '\0';
        printf("%s\n", buffer);
    }

    // After the username validation is completed, ask for password
    printf("\nPassword: ");
    fgets(password, sizeof(password), stdin);

    // Remove the newline character at the end of the password
    password[strcspn(password, "\n")] = 0;
    sendto(sockfd, (const char *)password, strlen(password), MSG_CONFIRM, (const struct sockaddr *)&server_address, sizeof(server_address));
    n = recvfrom(sockfd, (char *)buffer, MAX_BUFFER_SIZE, MSG_WAITALL, NULL, &len);
    buffer[n] = '\0';
    printf("%s\n", buffer);

    while (strcmp(buffer, "Not OK") == 0)
    {
        printf("\nRe-enter password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = 0;
        sendto(sockfd, (const char *)password, strlen(password), MSG_CONFIRM, (const struct sockaddr *)&server_address, sizeof(server_address));

        n = recvfrom(sockfd, (char *)buffer, MAX_BUFFER_SIZE, MSG_WAITALL, NULL, &len);
        buffer[n] = '\0';
        printf("%s\n", buffer);
    }

    if (strcmp(buffer, "OK") == 0)
    {
        while (1)
        {
            char new_password[MAX_BUFFER_SIZE];
            printf("\nNew password: ");
            fgets(new_password, sizeof(new_password), stdin);
            new_password[strcspn(new_password, "\n")] = 0;
            sendto(sockfd, (const char *)new_password, strlen(new_password), MSG_CONFIRM, (const struct sockaddr *)&server_address, sizeof(server_address));

            n = recvfrom(sockfd, (char *)buffer, MAX_BUFFER_SIZE, MSG_WAITALL, NULL, &len);
            buffer[n] = '\0';
            printf("%s\n", buffer);

            if (strcmp(new_password, "bye") == 0)
                break;
        }
    }

    // Close the fd
    close(sockfd);

    return 0;
}
