#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>

#define MAX_BUFFER_SIZE 1024
#define MAX_ARRAY_LENGTH 1024
#define MAX_STRING_LENGTH 256

#define LISTENQ 1
#define MAX_CLIENTS 10

char buffer[MAX_BUFFER_SIZE + 1];
struct pollfd fds[MAX_CLIENTS + 1]; // +1 for the server socket

// Socket variables declaration
int server_socket,
    max_sd,
    new_socket,
    client_sockets[MAX_CLIENTS],
    recvFlags[MAX_CLIENTS],
    sd;
struct sockaddr_in server_address, client_address;
fd_set readfds;
socklen_t len = sizeof(client_address);
socklen_t n;
int invalid_login_count[MAX_CLIENTS];

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

ElmType logged_users[MAX_CLIENTS];

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
    // read_from_file();

    printf("Connecting to server...\n");
    int port_num = atoi(argv[1]);

    // Initialize fds array
    for (int i = 0; i < MAX_CLIENTS + 1; i++)
    {
        fds[i].fd = -1;         // -1 means the entry is available
        fds[i].events = POLLIN; // We're interested in incoming data
    }

    // Create a TCP socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Create TCP socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options - allow multiple connections
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
    {
        perror("setsockopt");
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
    if (bind(server_socket, (const struct sockaddr *)&server_address, sizeof(server_address)) < 0)
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
    if (listen(server_socket, 10) < 0)
    {
        printf("Listen failed!");
        exit(EXIT_FAILURE);
    }
    else
        printf("Server is running... Waiting for connections.\n");

    // Add server socket to the first entry
    fds[0].fd = server_socket;

    read_from_file();

    while (1)
    {
        // Wait for an activity on one of the sockets
        int ret = poll(fds, MAX_CLIENTS + 1, -1); // -1 means wait indefinitely
        if (ret < 0)
        {
            printf("Poll error.\n");
            continue;
        }

        // If something happened on the server socket, it's an incoming connection
        if (fds[0].revents & POLLIN)
        {
            // ...
            if ((new_socket = accept(server_socket, (struct sockaddr *)&client_address, &len)) < 0)
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

            // Add new socket to the array of sockets
            for (int i = 1; i < MAX_CLIENTS + 1; i++) // Start from 1 because 0 is for the server socket
            {
                if (fds[i].fd == -1)
                {
                    fds[i].fd = new_socket;
                    printf("Adding to socket list as %d\n", i);
                    break;
                }
            }
        }

        for (int i = 1; i < MAX_CLIENTS + 1; i++)
        {
            if (fds[i].revents & POLLIN)
            {
                // Handle data from the client...
                handle_client_connection(fds[i].fd, i);
            }
        }
    }

    // Close the socket
    free_list();
    close(server_socket);

    return 0;
}