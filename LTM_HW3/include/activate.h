void activate()
{
  // Validate username
  char *username = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
  bool valid_username = false; // true - existed already | false - not existed
  do
  {
    printf("\nPlease enter username: ");
    fflush(stdin);
    scanf("%s", username);
    valid_username = check_username_input(username);

    if (!valid_username)
    {
      printf("Username not existed!\n");
    }

    // Check if the account is already activated
    // if (strcmp(cur->data.status, "active") == 0)
    if (cur->data.status == 1)
    {
      printf("Account activated!\n");
      // return;
      valid_username = false;
    }

    // Check if account is blocked
    // if (strcmp(cur->data.status, "blocked") == 0)
    // This code can be removed if the blocked account can still be actived again
    if (cur->data.status == 0)
    {
      printf("This account is blocked!\n");
      valid_username = false;
    }
  } while (!valid_username);

  // Validate password
  char *password = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
  bool valid_password = false;
  int wrong_password_count = 0;
  int result; // Use for get strcmp result
  do
  {
    printf("Please enter password: ");
    fflush(stdin);
    scanf("%s", password);

    result = strcmp(password, cur->data.password);

    if (result != 0)
    {
      printf("Incorrect password!\n\n");
      wrong_password_count++;
      if (wrong_password_count > 2)
      {
        // Notify
        printf("More than 3 times wrong, delete account!\n");

        // Delete account
        delete_middle(); // Delete current pointer info
        rewrite_file();

        // Exit the function
        return;
      }
    }
    else
      valid_password = true;
  } while (!valid_password);

  // Validate activation code
  char *activation_code = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
  bool valid_activation_code = false;
  int wrong_activation_code_count = 0;
  do
  {
    printf("Please enter activation code: ");
    fflush(stdin);
    scanf("%s", activation_code);
    valid_activation_code = check_activation_code(activation_code);

    if (!valid_activation_code)
    {
      wrong_activation_code_count++;
      if (wrong_activation_code_count > 3)
      {
        // Notify user
        printf("More than 4 times wrong, account blocked!\n");

        // Change status to blocked
        // strcpy(cur->data.status, "blocked");
        cur->data.status = 0;

        // Write new data to nguoidung.txt
        rewrite_file();

        // Exit the function
        return;
      }
    }
  } while (!valid_activation_code);

  // Activate the account
  // strcpy(cur->data.status, "active");
  cur->data.status = 1;

  // Write that activation to the file nguoidung.txt
  rewrite_file();

  // Notify user
  printf("Account activated!\n");

  // Free space after allocation
  free(username);
  free(password);
  free(activation_code);
}