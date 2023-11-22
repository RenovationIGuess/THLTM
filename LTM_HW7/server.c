#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <pthread.h>

#define MAX_BUFFER_SIZE 1024
#define MAX_ARRAY_LENGTH 1024
#define MAX_STRING_LENGTH 256

#define LISTENQ 1
#define MAX_CLIENTS 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int num_clients = 0;

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
#include "./includes/handle_client_connection.h"

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

    printf("Connecting to server...\n");
    int port_num = atoi(argv[1]);

    // Create a TCP socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Create TCP socket failed");
        // exit(1)
        exit(EXIT_FAILURE);
    }

    // Init
    memset(&server_address, 0, sizeof(server_address));
    memset(&client_address, 0, sizeof(client_address));

    // Config
    server_address.sin_family = AF_INET;
    // server_address.sin_addr.s_addr = INADDR_ANY;
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

    // Listen for incomming connections
    if (listen(sockfd, 10) < 0)
    {
        printf("Listen failed!");
        exit(EXIT_FAILURE);
    }
    else
        printf("Server is running... Waiting for connections.\n");

    // Accept an incomming connection
    int clientfd;
    socklen_t len = sizeof(client_address);

    while (1)
    {
        clientfd = accept(sockfd, (struct sockaddr *)&client_address, &len);
        if (clientfd < 0)
        {
            printf("Accept failed!\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Accept successful!\n");
            printf("[%s:%d]\n", inet_ntoa(client_address.sin_addr),
                   ntohs(client_address.sin_port));
        }

        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client_connection, (void *)&clientfd);
        pthread_detach(thread_id);
    }

    // Close the socket
    close(sockfd);
    close(clientfd);

    return 0;
}