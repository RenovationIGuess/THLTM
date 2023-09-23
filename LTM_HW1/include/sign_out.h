void sign_out()
{
  // First check if user is logged in or not
  if (!is_authenticated)
  {
    printf("\nYou must be logged in to perform this action!\n");
    return;
  }

  bool correct_username = false;
  char *username = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
  do {
    printf("\nEnter logged in username: ");
    fflush(stdin);
    scanf("%s", username);

    correct_username = check_username_for_sign_out(username);
  }  while (!correct_username);

  // Clear all the authentication
  current_user = NULL;
  is_authenticated = false;

  // Free the memory
  free(username);
  free_list();
}