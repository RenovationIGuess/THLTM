int handleRecvData(Input *input)
{
  return read(new_socket, input, sizeof(Input));
}

int handleSendData(Output *output)
{
  return send(new_socket, output, sizeof(Output), 0);
}

void handleAction()
{
  switch (checkMsgType())
  {
  case 1:
    if (signInStatus == 0)
    {
      checkAccountUsername();
    }
    else
    {
      strcpy(output.data_type, "You are already logged in!");
      strcpy(output.msg_type, serverHeader[1]);
    }
    break;
  case 2:
    if (signInStatus == 1)
    {
      int res = getMsgToFile();
      if (res == 1)
      {
        strcpy(output.data_type, "Send message failed!");
        strcpy(output.msg_type, serverHeader[1]);
      }
      else
      {
        strcpy(output.data_type, "Send message success!");
        strcpy(output.msg_type, serverHeader[0]);
      }
    }
    else
    {
      strcpy(output.data_type, "You are not logged in!");
      strcpy(output.msg_type, serverHeader[1]);
    }
    break;
  case 3:
    strcpy(output.data_type, "Goodbye!");
    strcpy(output.msg_type, serverHeader[0]);
    signInStatus = 0;
    strcpy(account, "");
    printf("Logging out...\n");
    break;
  default:
    printf("Server Error in Switch case!\n");
    strcpy(output.data_type, "Internal Server Error!");
    strcpy(output.msg_type, serverHeader[0]);
    break;
  }
}