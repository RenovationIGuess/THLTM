int checkAccountUsername()
{
  if (checkUsername(input.data_type, root) == 0)
  {
    strcpy(output.data_type, "Login Success");
    strcpy(output.msg_type, serverHeader[0]);
    signInStatus = 1;
    strcpy(account, input.data_type);
  }
  else
  {
    strcpy(output.data_type, "Account not exist!");
    strcpy(output.msg_type, serverHeader[1]);
  }
  return 0;
}

int checkMsgType()
{
  if (strcmp(input.msg_type, clientHeader[0]) == 0)
  {
    return 1;
  }
  else if (strcmp(input.msg_type, clientHeader[1]) == 0)
  {
    return 2;
  }
  else if (strcmp(input.msg_type, clientHeader[2]) == 0)
  {
    return 3;
  }
  return 0;
}