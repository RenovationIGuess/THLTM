/*
    If it returns true then it means that the username is existed
    and the typed value is invalid in resgisting account. In constrast,
    the typed value is valid if its for sign in
*/
bool check_username_input(char input_value[])
{
  node *p = l;
  if (p == NULL)
  {
    printf("\nCon tro NULL!\n");
    return false;
  }

  int result;
  while (p != NULL)
  {
    result = strcmp(input_value, p->data.username);
    if (result == 0)
    {
      cur = p;
      return true;
    }
    p = p->next;
  }
  return false;
}

// Use to check if the password is in correct format
bool check_password_input(char input_value[])
{
    int len = strlen(input_value);
    for (int i = 0; i < len; i++)
    {
        char ch = input_value[i];
        // If its neither characters or digits => invalid format
        if ((ch < '0' || ch > '9') && (ch < 'a' || ch > 'z') && (ch < 'A' || ch > 'Z'))
        {
            return false;
        }
    }
    return true;
}

// Check if the port number is valid or not
bool is_valid_port(char port_str[]) {
    int port_num = atoi(port_str);
    int len = strlen(port_str);
    
    // Check for boundary
    if (port_num < 1 || port_num > 65535) {
        return false;
    }

    // Check for format
    for (int i = 0; i < len; ++i) {
        if (!isdigit(port_str[i])) {
            return false;
        }
    }
    return true;
}
