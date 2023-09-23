void change_password()
{
  // First check if user is logged in or not
  if (!is_authenticated)
  {
    printf("\nYou must be logged in to perform this action!\n");
    return;
  }

  // Validate password
  char *old_password = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
  bool valid_password = false;
  int wrong_password_count = 0;
  int result; // Use for get strcmp result
  do
  {
    printf("\nEnter your old password: ");
    fflush(stdin);
    scanf("%s", old_password);

    result = strcmp(old_password, cur->data.password);

    if (result != 0)
    {
      printf("Incorrect password!\n");
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

  // Enter new password
  char *new_password = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
  printf("Enter your new password: ");
  fflush(stdin);
  scanf("%s", new_password);

  // Set new password for user
  strcpy(current_user->data.password, new_password);

  // Save to the file
  rewrite_file();

  // Notify
  printf("Password changed!\n");

  // Free up memory
  free(old_password);
  free(new_password);
}