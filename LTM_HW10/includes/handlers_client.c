int handleAction()
{
    printf("Choose action:\n");
    printf("1. Sign in\n");
    printf("2. Send message\n");
    printf("3. Exit\n");
    printf("Your choice: ");

    int choice;
    scanf("%d", &choice);
    custom_fflush_stdin();

    switch (choice)
    {
    case 1:
        printf("Enter username: ");
        fgets(input.data_type, sizeof(input.data_type), stdin);
        // custom_fflush_stdin();
        input.data_type[strlen(input.data_type) - 1] = '\0';
        strcpy(input.msg_type, clientHeader[0]);
        break;
    case 2:
        printf("Enter message: ");
        fgets(input.data_type, sizeof(input.data_type), stdin);
        // custom_fflush_stdin();
        input.data_type[strlen(input.data_type) - 1] = '\0';
        strcpy(input.msg_type, clientHeader[1]);
        break;
    case 3:
        printf("Exit...\n");
        strcpy(input.data_type, "Logout request");
        strcpy(input.msg_type, clientHeader[2]);
        logoutStatus = 1;
        break;
    default:
        return 1;
    }
    return 0;
}

int handleSendData(Input *input)
{
    return send(sockfd, input, sizeof(Input), 0);
}

int handleRecvData(Output *output)
{
    return recv(sockfd, output, sizeof(Output), 0);
}