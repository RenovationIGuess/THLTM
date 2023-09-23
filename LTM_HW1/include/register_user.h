void register_user()
{

  ElmType new_user;

  // Enter username
  bool valid_username = false; // true - existed already | false - not existed
  do
  {
    printf("\nPlease enter username: ");
    fflush(stdin);
    scanf("%s", new_user.username);
    valid_username = !check_username_input(new_user.username);

    if (!valid_username)
    {
      printf("Username already in use!\n");
    }
  } while (!valid_username);

  // Enter password
  printf("Please enter password: ");
  fflush(stdin);
  scanf("%s", new_user.password);

  // New account auto idle status
  // strcpy(new_user.status, "idle");
  new_user.status = 2;

  // Add item to the linked list
  insert_at_tail(new_user);

  // Open the file again
  f = fopen("nguoidung.txt", "a+");

  // Write new user to file
  fprintf(f, "%s %s %d\n", new_user.username, new_user.password, new_user.status);

  // Close the file
  fclose(f);

  // Notify
  printf("Successful registration. Activation required!\n");
}