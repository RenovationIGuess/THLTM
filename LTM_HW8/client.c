#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "./utils/check_valid_ip_address.h"

#define MAX_BUFFER_SIZE 1024

// Check if the port number is valid or not
bool is_valid_port(char port_str[])
{
    int port_num = atoi(port_str);
    int len = strlen(port_str);

    // Check for boundary
    if (port_num < 1 || port_num > 65535)
    {
        return false;
    }

    // Check for format
    for (int i = 0; i < len; ++i)
    {
        if (!isdigit(port_str[i]))
        {
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

    // Socket variables declaration
    int sockfd; // Naming convention: fd?
    socklen_t n, len;
    struct sockaddr_in server_address;

    char username[MAX_BUFFER_SIZE];
    char password[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Create a TCP socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Create TCP socket failed");
        // exit(1)
        exit(EXIT_FAILURE);
    }

    // Initialize
    memset(&server_address, 0, sizeof(server_address));

    // Config
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_num);
    server_address.sin_addr.s_addr = inet_addr(ip_address);

    // Connect to server
    if (connect(sockfd, (const struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        printf("Connect failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Username: ");
    // Able to ignore whitespace at the end
    fgets(username, sizeof(username), stdin);
    // Remove the newline character at the end of the username
    username[strcspn(username, "\n")] = 0;
    n = send(sockfd, (const char *)username, sizeof(username), 0);
    if (n < 0)
    {
        printf("Send failed\n");
        exit(EXIT_FAILURE);
    }

    n = recv(sockfd, (char *)buffer, MAX_BUFFER_SIZE, 0);
    if (n < 0)
    {
        printf("Receive failed\n");
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';
    printf("%s\n", buffer);

    // If the account is not found, then make user enter again
    while (strcmp(buffer, "Account not found") == 0)
    {
        printf("\nRe-enter username: ");
        fgets(username, sizeof(username), stdin);
        // Repeat the same process above to send to server and receive response
        username[strcspn(username, "\n")] = 0;
        n = send(sockfd, (const char *)username, MAX_BUFFER_SIZE, 0);
        if (n < 0)
        {
            printf("Send failed\n");
            exit(EXIT_FAILURE);
        }

        n = recv(sockfd, (char *)buffer, MAX_BUFFER_SIZE, 0);
        if (n < 0)
        {
            printf("Receive failed\n");
            exit(EXIT_FAILURE);
        }
        buffer[n] = '\0';
        printf("%s\n", buffer);
    }

    // After the username validation is completed, ask for password
    printf("\nPassword: ");
    fgets(password, sizeof(password), stdin);

    // Remove the newline character at the end of the password
    password[strcspn(password, "\n")] = 0;
    n = send(sockfd, (const char *)password, MAX_BUFFER_SIZE, 0);
    if (n < 0)
    {
        printf("Send failed\n");
        exit(EXIT_FAILURE);
    }

    n = recv(sockfd, (char *)buffer, MAX_BUFFER_SIZE, 0);
    if (n < 0)
    {
        printf("Receive failed\n");
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';
    printf("%s\n", buffer);

    while (strcmp(buffer, "Not OK") == 0)
    {
        printf("\nRe-enter password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = 0;

        n = send(sockfd, (const char *)password, MAX_BUFFER_SIZE, 0);
        if (n < 0)
        {
            printf("Send failed\n");
            exit(EXIT_FAILURE);
        }

        n = recv(sockfd, (char *)buffer, MAX_BUFFER_SIZE, 0);
        if (n <= 0)
        {
            printf("Receive failed\n");
            exit(EXIT_FAILURE);
        }
        buffer[n] = '\0';
        printf("%s\n", buffer);

        if (strcmp(buffer, "Account is blocked") == 0)
            break;
    }

    if (strcmp(buffer, "OK") == 0)
    {
        while (1)
        {
            char new_password[MAX_BUFFER_SIZE];
            char validate[MAX_BUFFER_SIZE];
            printf("\nNew password: ");
            fgets(new_password, sizeof(new_password), stdin);
            new_password[strcspn(new_password, "\n")] = 0;
            strcpy(validate, new_password);

            n = send(sockfd, (const char *)new_password, MAX_BUFFER_SIZE, 0);
            if (n < 0)
            {
                printf("Send failed\n");
                exit(EXIT_FAILURE);
            }

            n = recv(sockfd, (char *)buffer, MAX_BUFFER_SIZE, 0);
            if (n < 0)
            {
                printf("Receive failed\n");
                exit(EXIT_FAILURE);
            }
            buffer[n] = '\0';
            printf("%s\n", buffer);

            if (strcmp(validate, "bye") == 0)
                break;
        }
    }

    // Close the fd
    close(sockfd);

    return 0;
}