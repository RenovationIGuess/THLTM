#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_BUFFER_SIZE 1024
#define MAX_ARRAY_LENGTH 1024
#define MAX_STRING_LENGTH 256

FILE *f;
int number_of_users;

typedef struct User
{
    char username[MAX_STRING_LENGTH];
    char password[MAX_STRING_LENGTH];
    int status;
    char homepage[MAX_STRING_LENGTH];
} User;

// ElmType - Element type :))
typedef struct User ElmType;

#include "./lib/linked_list.h"

node *logged_user;

#include "./utils/validators.h"
#include "./utils/status_converter.h"
#include "./utils/file_actions.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Syntax: ./server <Port number>\n");
        return 1;
    }

    // If the port is invalid, exit the program
    if (!is_valid_port(argv[1]))
    {
        printf("Invalid port number!\n");
        return 1;
    }

    // Get data from nguoidung.txt
    read_from_file();

    // Socket variables declaration
    int sockfd;
    struct sockaddr_in server_address, client_address;

    char buffer[MAX_BUFFER_SIZE];

    printf("Connecting to server...\n");
    int port_num = atoi(argv[1]);

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("Create socket failed");
        // exit(1)
        exit(EXIT_FAILURE);
    }

    // Init
    memset(&server_address, 0, sizeof(server_address));
    memset(&client_address, 0, sizeof(client_address));

    // Config
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port_num);

    // Binding
    if (bind(sockfd, (const struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Binding failed!");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Binding successful!\n");
        printf("[%s:%d]\n", inet_ntoa(server_address.sin_addr),
               ntohs(server_address.sin_port));
    }

    while (1)
    {
        socklen_t len, n;
        len = sizeof(client_address);

        // Receive the username from client
        n = recvfrom(sockfd, (char *)buffer, MAX_BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&client_address, &len);
        buffer[n] = '\0';
        char username[MAX_BUFFER_SIZE];
        strcpy(username, buffer);

        if (!check_username_input(username))
        {
            char *ack = "Account not found";
            sendto(sockfd, (const char *)ack, strlen(ack), MSG_CONFIRM, (const struct sockaddr *)&client_address, len);
        }
        else
        {
            char *ack = "Insert password";
            sendto(sockfd, (const char *)ack, strlen(ack), MSG_CONFIRM, (const struct sockaddr *)&client_address, len);
            int invalid_login_count = 0;

            while (invalid_login_count <= 2)
            {
                // Receive the password
                n = recvfrom(sockfd, (char *)buffer, MAX_BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&client_address, &len);
                buffer[n] = '\0';
                char password[MAX_BUFFER_SIZE];
                strcpy(password, buffer);

                // If the password is not matched
                if (strcmp(cur->data.password, password) != 0)
                {
                    invalid_login_count++;
                    char *ack = "Not OK";
                    sendto(sockfd, (const char *)ack, strlen(ack), MSG_CONFIRM, (const struct sockaddr *)&client_address, len);
                }
                // If matched
                // If account is activated
                else if (cur->data.status == 1)
                {
                    logged_user = cur;
                    char *ack = "OK";
                    sendto(sockfd, (const char *)ack, strlen(ack), MSG_CONFIRM, (const struct sockaddr *)&client_address, len);

                    while (1)
                    {
                        // Recieve new password from the client
                        n = recvfrom(sockfd, (char *)buffer, MAX_BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&client_address, &len);
                        buffer[n] = '\0';

                        // If the user did not want to update password and sign out
                        if (strcmp(buffer, "bye") == 0)
                        {
                            char end_msg[] = "Goodbye ";
                            strcat(end_msg, logged_user->data.username);
                            sendto(sockfd, (const char *)end_msg, strlen(end_msg), MSG_CONFIRM, (const struct sockaddr *)&client_address, len);
                            logged_user = NULL;
                            break;
                        }

                        // Else if the user do want to change the password
                        char new_password[MAX_BUFFER_SIZE];
                        strcpy(new_password, buffer);
                        // Check for a valid password
                        if (!check_password_input(new_password))
                        {
                            char *ack1 = "Error";
                            sendto(sockfd, (const char *)ack, strlen(ack1), MSG_CONFIRM, (const struct sockaddr *)&client_address, len);
                        }
                        else
                        {
                            // Now we update the new password
                            // Set new password for user
                            strcpy(logged_user->data.password, new_password);

                            // Save to the file
                            rewrite_file();

                            // String to store characters
                            char *chars = (char *)malloc(MAX_BUFFER_SIZE * sizeof(char));
                            // String to store numbers
                            char *numbers = (char *)malloc(MAX_BUFFER_SIZE * sizeof(char));

                            int char_index = 0;
                            int number_index = 0;

                            for (int i = 0; i < strlen(new_password); i++)
                            {
                                if (isalpha(new_password[i]))
                                {
                                    chars[char_index++] = new_password[i];
                                }
                                else if (isdigit(new_password[i]))
                                {
                                    numbers[number_index++] = new_password[i];
                                }
                            }

                            chars[char_index] = '\0';     // Null-terminate the character string
                            numbers[number_index] = '\0'; // Null-terminate the number string

                            char ack2[MAX_BUFFER_SIZE];
                            // Encrypted data will be:
                            // First line: chars
                            // Second line: numbers
                            // strcpy(ack2, "Encrypted data:\n");
                            int chars_len = strlen(chars);
                            int numbers_len = strlen(numbers);

                            if (chars_len == 0)
                            {
                                strcpy(ack2, numbers);
                            }
                            else if (numbers_len == 0)
                            {
                                strcpy(ack2, chars);
                            }
                            else
                            {
                                strcpy(ack2, chars);
                                strcat(ack2, "\n");
                                strcat(ack2, numbers);
                            }
                            sendto(sockfd, (const char *)ack2, strlen(ack2), MSG_CONFIRM, (const struct sockaddr *)&client_address, len);

                            free(chars);
                            free(numbers);
                        }
                    }
                    break;
                }
                else
                {
                    char ack2[MAX_BUFFER_SIZE];
                    if (cur->data.status == 0)
                    {
                        strcpy(ack2, "Account not ready");
                    }
                    else if (cur->data.status == 2)
                    {
                        strcpy(ack2, "Account is blocked");
                    }
                    sendto(sockfd, (const char *)ack2, strlen(ack2), MSG_CONFIRM, (const struct sockaddr *)&client_address, len);
                    break;
                }
            }

            if (invalid_login_count > 2)
            {
                // Delete account
                if (cur == l)
                    delete_head();
                else
                    delete_middle(); // Delete current pointer info
                rewrite_file();
                char *ack = "Account is blocked";
                sendto(sockfd, (const char *)ack, strlen(ack), MSG_CONFIRM, (const struct sockaddr *)&client_address, len);
                break;
            }
        }
    }

    // Close the socket
    close(sockfd);

    return 0;
}