void handle_client_connection(int clientfd)
{
  socklen_t n;
  char buffer[MAX_BUFFER_SIZE];
  int invalid_login_count = 0;

  while (1)
  {
    // Receive the username from client
    n = recv(clientfd, (char *)buffer, MAX_BUFFER_SIZE, 0);
    if (n < 0)
    {
      printf("Receive failed\n");
      exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';
    char username[MAX_BUFFER_SIZE];
    strcpy(username, buffer);

    if (!check_username_input(username))
    {
      char *ack = "Account not found";
      n = send(clientfd, (const char *)ack, MAX_BUFFER_SIZE, 0);
      if (n < 0)
      {
        printf("Send failed\n");
        exit(EXIT_FAILURE);
      }
    }
    else
    {
      char *ack = "Insert password";
      n = send(clientfd, (const char *)ack, MAX_BUFFER_SIZE, 0);
      if (n < 0)
      {
        printf("Send failed\n");
        exit(EXIT_FAILURE);
      }

      while (1)
      {
        // Receive the password
        n = recv(clientfd, (char *)buffer, MAX_BUFFER_SIZE, 0);
        if (n < 0)
        {
          printf("Receive failed\n");
          exit(EXIT_FAILURE);
        }
        buffer[n] = '\0';
        char password[MAX_BUFFER_SIZE];
        strcpy(password, buffer);

        // printf("Invalid count: %d\n", invalid_login_count);

        // If the password is not matched
        if (strcmp(cur->data.password, password) != 0)
        {
          invalid_login_count++;
          if (invalid_login_count == 3)
            break;

          char *ack = "Not OK";
          n = send(clientfd, (const char *)ack, MAX_BUFFER_SIZE, 0);
          if (n < 0)
          {
            printf("Send failed\n");
            exit(EXIT_FAILURE);
          }
        }
        // If matched
        // If account is activated
        else if (cur->data.status == 1)
        {
          logged_user = cur;
          char *ack = "OK";
          n = send(clientfd, (const char *)ack, MAX_BUFFER_SIZE, 0);
          if (n < 0)
          {
            printf("Send failed\n");
            exit(EXIT_FAILURE);
          }

          while (1)
          {
            // Recieve new password from the client
            n = recv(clientfd, (char *)buffer, MAX_BUFFER_SIZE, 0);
            if (n < 0)
            {
              printf("Receive failed\n");
              exit(EXIT_FAILURE);
            }
            buffer[n] = '\0';

            // If the user did not want to update password and sign out
            if (strcmp(buffer, "bye") == 0)
            {
              char end_msg[] = "Goodbye ";
              strcat(end_msg, logged_user->data.username);
              n = send(clientfd, (const char *)end_msg, MAX_BUFFER_SIZE, 0);
              if (n < 0)
              {
                printf("Send failed\n");
                exit(EXIT_FAILURE);
              }
              logged_user = NULL;
              break;
            }

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
                printf("Send failed\n");
                exit(EXIT_FAILURE);
              }
            }
            else
            {
              // Now we update the new password
              // Set new password for user
              strcpy(logged_user->data.password, new_password);
              // printf("New password: %s\n", new_password);

              // Save to the file
              rewrite_file();

              // String to store characters
              char *chars = (char *)malloc(MAX_BUFFER_SIZE * sizeof(char));
              // String to store numbers
              char *numbers = (char *)malloc(MAX_BUFFER_SIZE * sizeof(char));

              // memset(&chars, 0, sizeof(chars));
              // memset(&numbers, 0, sizeof(numbers));

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

              // printf("\'%s\'\n\'%s\'\n", chars, numbers);

              char ack2[MAX_BUFFER_SIZE];
              // Encrypted data will be:
              // First line: chars
              // Second line: numbers
              // strcpy(ack2, "Encrypted data:\n");
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
                printf("Send failed\n");
                exit(EXIT_FAILURE);
              }

              free(chars);
              free(numbers);
            }
          }
          break;
        }
        else
        {
          char ack2[MAX_BUFFER_SIZE];
          if (cur->data.status == 0)
          {
            strcpy(ack2, "Account is blocked");
          }
          else if (cur->data.status == 2)
          {
            strcpy(ack2, "Account not ready");
          }
          n = send(clientfd, (const char *)ack2, MAX_BUFFER_SIZE, 0);
          if (n < 0)
          {
            printf("Send failed\n");
            exit(EXIT_FAILURE);
          }
          break;
        }
      }

      if (invalid_login_count == 3)
      {
        // Reset value
        // invalid_login_count = 0;
        // Delete account
        if (cur == l)
          delete_head();
        else
          delete_middle(); // Delete current pointer info
        // display_linked_list(); // Display linked list
        rewrite_file();

        // Send message
        char *ack = "Account is blocked";
        n = send(clientfd, (const char *)ack, MAX_BUFFER_SIZE, 0);
        if (n < 0)
        {
          printf("Send failed\n");
          exit(EXIT_FAILURE);
        }
        // printf("Invalid login count: %d\n", invalid_login_count);
        break;
      }
    }
  }
}