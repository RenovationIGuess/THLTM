#include <stdio.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include "./utils/handle_blank_input.h"
#define MAX_MSG_TYPE 10
#define MAX_DATA_TYPE 1024

const int MAX = 100;
FILE *fptr, *fpMsg;
int n;
int signInStatus = 0;
char account[20];

char clientHeader[3][10] = {"LOGIN", "MESSAGE", "LOGOUT"};
char serverHeader[2][10] = {"SUCCESS", "ERROR"};

typedef struct input
{
    char username[20];
    char password[20];
    int status;
} Account;

typedef struct __attribute__((packed))
{
    char msg_type[MAX_MSG_TYPE];
    char data_type[MAX_DATA_TYPE];
} Input;
Input input;

typedef struct __attribute__((packed))
{
    char msg_type[MAX_MSG_TYPE];
    char data_type[MAX_DATA_TYPE];
} Output;
Output output;

typedef Account AccountList;

struct node_t
{
    AccountList element;
    struct node_t *next;
};

typedef struct node_t node;
node *root, *cur, *pre;
AccountList *a;

int step = 1;

#include "./lib/single_linked_list.h"

int sockfd, new_socket, rcvBytes, sendBytes;
socklen_t len;
struct sockaddr_in servaddr, cliaddr;

// File actions
#include "./utils/file_actions.h"

// Validators
#include "./utils/validators.h"

// Handlers
#include "./includes/handlers_server.c"

int main(int argc, char **argv)
{
    readFile();
    // Step 1: Construct socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Error: ");
        exit(0);
    }

    // Step 2: Bind address to socket
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)))
    {
        perror("Error: ");
        exit(0);
    }
    printf("Server started!\n");

    // Step 3: Listen for incoming connections
    if (listen(sockfd, 5) < 0)
    {
        perror("Error: ");
        exit(0);
    }

    if ((new_socket = accept(sockfd, (struct sockaddr *)&cliaddr, &len)) < 0)
    {
        perror("Error: ");
        exit(0);
    }
    printf("Client connected!\n");

    // Step 4: Communicate with clients
    while(1)
    {
        printf("\nServer is waiting for request...\n");
        len = sizeof(cliaddr);
        rcvBytes = handleRecvData(&input);
        if (rcvBytes < 0)
        {
            perror("Error: ");
            exit(0);
        }
        printf("%s - %s\n", input.msg_type, input.data_type);

        handleAction();

        strcpy(input.data_type, "");
        strcpy(input.msg_type, "");
        sendBytes = handleSendData(&output);
        if (sendBytes < 0)
        {
            perror("Error: ");
            exit(0);
        }
        strcpy(output.data_type, "");
        strcpy(output.msg_type, "");
    }
    close(sockfd);
    return 0;
}