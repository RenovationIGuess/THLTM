void handle_disconnect_client(int clientfd, int index)
{
  getpeername(clientfd, (struct sockaddr *)&client_address, &len);
  printf("Host disconnected, ip %s, port %d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
  close(clientfd);
  fds[index].fd = -1; // Set the file descriptor to -1 to indicate it's no longer in use
  recvFlags[index] = 0;
  invalid_login_count[index] = 0;
}

void assign_user_info(int index)
{
  strcpy(logged_users[index].username, cur->data.username);
  strcpy(logged_users[index].password, cur->data.password);
  strcpy(logged_users[index].homepage, cur->data.homepage);
  logged_users[index].status = cur->data.status;
}

void handle_client_connection(int clientfd, int index)
{
  // read_from_file();

  printf("Handling client connection at index: %d.\n", index);

  node *logged_user;

  // Receive the username from client
  n = recv(clientfd, (char *)buffer, MAX_BUFFER_SIZE, 0);
  if (n <= 0)
  {
    handle_disconnect_client(clientfd, index);
    return;
  }

  buffer[n] = '\0';

  if (recvFlags[index] == 0)
  {
    char username[MAX_BUFFER_SIZE];
    strcpy(username, buffer);

    if (!check_username_input(username))
    {
      char *ack = "Account not found";
      n = send(clientfd, (const char *)ack, MAX_BUFFER_SIZE, 0);
      if (n <= 0)
      {
        handle_disconnect_client(clientfd, index);
        return;
      }
    }

    // If the username is matched => set the user to track equal to found result
    assign_user_info(index);

    char *ack = "Insert password";
    n = send(clientfd, (const char *)ack, MAX_BUFFER_SIZE, 0);
    if (n <= 0)
    {
      handle_disconnect_client(clientfd, index);
      return;
    }

    recvFlags[index] = 1;
  }
  else if (recvFlags[index] == 1)
  {
    if (invalid_login_count[index] < 3)
    {
      // Receive the password
      char password[MAX_BUFFER_SIZE];
      strcpy(password, buffer);

      // If the password is not matched
      if (strcmp(logged_users[index].password, password) != 0)
      {
        invalid_login_count[index]++;

        if (invalid_login_count[index] >= 3)
        {
          // Send message
          char *ack = "Account is blocked";
          n = send(clientfd, (const char *)ack, MAX_BUFFER_SIZE, 0);
          if (n < 0)
          {
            handle_disconnect_client(clientfd, index);
            return;
          }

          // Re-navigate cur pointer
          search(logged_users[index]);
          // Delete account
          if (cur == l)
            delete_head();
          else
            delete_middle(); // Delete current pointer info
          rewrite_file();

          handle_disconnect_client(clientfd, index);
          return;
        }

        printf("Invalid login count: %d\n", invalid_login_count[index]);
        char *ack = "Not OK";
        n = send(clientfd, (const char *)ack, MAX_BUFFER_SIZE, 0);
        if (n < 0)
        {
          handle_disconnect_client(clientfd, index);
          return;
        }

        return;
      }
    }

    // If matched
    // If account is activated
    if (logged_users[index].status == 1)
    {
      printf("Username: %s\n", logged_users[index].username);
      search(logged_users[index]);
      logged_user = cur;
      printf("Logged user: %s\n", logged_user->data.username);

      char *ack = "OK";
      n = send(clientfd, (const char *)ack, MAX_BUFFER_SIZE, 0);
      if (n < 0)
      {
        handle_disconnect_client(clientfd, index);
      }

      recvFlags[index] = 2;
    }
    else
    {
      char ack2[MAX_BUFFER_SIZE];
      if (logged_users[index].status == 0)
      {
        strcpy(ack2, "Account is blocked");
      }
      else if (logged_users[index].status == 2)
      {
        strcpy(ack2, "Account not ready");
      }
      n = send(clientfd, (const char *)ack2, MAX_BUFFER_SIZE, 0);
      if (n < 0)
      {
        handle_disconnect_client(clientfd, index);
        return;
      }
    }
  }
  else if (recvFlags[index] == 2)
  {
    // Recieve new password from the client
    // If the user did not want to update password and sign out
    if (strcmp(buffer, "bye") == 0)
    {
      char end_msg[] = "Goodbye ";
      strcat(end_msg, logged_users[index].username);
      n = send(clientfd, (const char *)end_msg, MAX_BUFFER_SIZE, 0);
      if (n <= 0)
      {
        handle_disconnect_client(clientfd, index);
        return;
      }
      logged_user = NULL;
    }
    else
    {
      // Else if the user do want to change the password
      char new_password[MAX_BUFFER_SIZE];
      strcpy(new_password, buffer);
      // Check for a valid password
      if (!check_password_input(new_password))
      {
        char *ack1 = "Error";
        n = send(clientfd, (const char *)ack1, MAX_BUFFER_SIZE, 0);
        if (n < 0)
        {
          handle_disconnect_client(clientfd, index);
          return;
        }
      }
      else
      {
        // Now we update the new password
        // Set new password for user
        // search(logged_users[index]);
        // strcpy(cur->data.password, new_password);
        strcpy(logged_user->data.password, new_password);

        // Save to the file
        rewrite_file();

        // String to store characters
        char *chars = (char *)malloc(MAX_BUFFER_SIZE * sizeof(char));
        // String to store numbers
        char *numbers = (char *)malloc(MAX_BUFFER_SIZE * sizeof(char));

        int char_index = 0;
        int number_index = 0;

        // printf("New password: %s\n", new_password);

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
        n = send(clientfd, (const char *)ack2, MAX_BUFFER_SIZE, 0);
        if (n < 0)
        {
          handle_disconnect_client(clientfd, index);
          return;
        }

        free(chars);
        free(numbers);
      }
    }
  }
}