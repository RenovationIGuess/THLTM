#include <stdio.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "./utils/handle_blank_input.h"
#define MAX_MSG_TYPE 10
#define MAX_DATA_TYPE 1024

int sockfd, rcvBytes, sendBytes;
socklen_t len;
struct sockaddr_in servaddr, cliaddr;

char clientHeader[3][10] = {"LOGIN", "MESSAGE", "LOGOUT"};
char serverHeader[2][10] = {"SUCCESS", "ERROR"};

int logoutStatus = 0;

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

#include "./includes/handlers_client.c"

int main(int argc, char **argv)
{
    // Step 1: Construct socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Error: ");
        exit(0);
    }

    // Step 2: Define the address of the server
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(atoi(argv[2]));

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Error: ");
        exit(0);
    }

    // Step 3: Communicate with server
    while(1)
    {
        if (handleAction() == 1)
        {
            printf("\nInvalid choice! Please try again\n");
            continue;
        }

        sendBytes = handleSendData(&input);
        strcpy(input.data_type, "");
        strcpy(input.msg_type, "");
        if (sendBytes < 0)
        {
            perror("Error: ");
            exit(0);
        }

        rcvBytes = handleRecvData(&output);
        if (rcvBytes < 0)
        {
            perror("Error: ");
            exit(0);
        }

        printf("\n[%s:%d] %s - %s\n\n", inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port), output.msg_type, output.data_type);
        strcpy(output.data_type, "");
        strcpy(output.msg_type, "");

        if (logoutStatus == 1)
        {
            break;
        }
    }
    close(sockfd);
    return 0;
}