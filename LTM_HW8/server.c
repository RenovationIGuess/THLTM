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
#include <sys/select.h>
#include <netinet/in.h>

#define MAX_BUFFER_SIZE 1024
#define MAX_ARRAY_LENGTH 1024
#define MAX_STRING_LENGTH 256

#define LISTENQ 1
#define MAX_CLIENTS 10

char buffer[MAX_BUFFER_SIZE + 1];

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

    // Initialize client_sockets[] to 0
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        client_sockets[i] = 0;
        recvFlags[i] = 0;
        invalid_login_count[i] = 0;
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

    read_from_file();

    while (1)
    {
        // Clear the socket set
        FD_ZERO(&readfds);

        // Add server socket to the set
        FD_SET(server_socket, &readfds);
        max_sd = server_socket;

        // Add client sockets to the set
        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            sd = client_sockets[i];

            if (sd > 0)
            {
                FD_SET(sd, &readfds);
            }

            if (sd > max_sd)
            {
                max_sd = sd;
            }
        }

        // Wait for an activity on one of the sockets
        if (select(max_sd + 1, &readfds, NULL, NULL, NULL) < 0)
        {
            printf("Select error.\n");
            // exit(EXIT_FAILURE);
            continue;
        }

        // If something happened on the server socket, it's an incoming connection
        if (FD_ISSET(server_socket, &readfds))
        {
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
            for (int i = 0; i < MAX_CLIENTS; i++)
            {
                if (client_sockets[i] == 0)
                {
                    client_sockets[i] = new_socket;
                    printf("Adding to socket list as %d\n", i);
                    break;
                }
            }
        }

        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            sd = client_sockets[i];

            if (FD_ISSET(sd, &readfds))
            {
                // Handle data from the client...
                handle_client_connection(sd, i);
            }
        }
    }

    // Close the socket
    free_list();
    close(server_socket);

    return 0;
}