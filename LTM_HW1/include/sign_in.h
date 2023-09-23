void sign_in()
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
    else
    {
      // If the account is valid BUT its status is blocked or idle then
      if (cur->data.status == 0 || cur->data.status == 2)
      {
        printf("This account is blocked!\n");
        valid_username = false;
      }
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
        printf("More than 3 times wrong, delete account!\n");

        // Here we have 2 approach
        // 1. Rewrite the file
        // 2. Delete a line in the file - which still needs to loop and compare until we find the
        // line that matches the cur pointer information => possibly has lower opacity since it doesn't
        // have to loop through all elements

        // Approach 1. Rewrite the file
        // First delete account
        delete_middle(); // Delete the cur pointer
        rewrite_file();

        // Approach 2. Delete a line
        /*
            In this approach we first have to open the file in append mode (a | a+)
            Then we set the read pointer to first position of the file
            Start looping through the file using fgets until we find the desire account
            In order to delete the line, w
            // printf("%s %s %s\n", p->data.username, p->data.password, p->data.status);e could:
            => Create a new file to store nguoidung.txt file's content without the account to delete
            Then remove the old nguoidung.txt using remove(file_name) and rename created file using
            rename(newly_created_file, nguoidung.txt aka old_file_name)
        */

        // Exit the function
        return;
      }
    }
    else
      valid_password = true;
  } while (!valid_password);

  // Set sign in state to true
  is_authenticated = true;

  // Set the current user pointer to current pointer
  current_user = cur;

  // Notify the user that login successful
  printf("Login successful!\n");

  // Free up memory
  free(username);
  free(password);
}