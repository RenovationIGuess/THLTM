void search_user()
{
  // If the user is not logged in
  if (!is_authenticated)
  {
    printf("\nYou must be logged in to perform this action!\n");
    return;
  }

  // Option for user to keep searching
  bool stop_searching = false;
  char stop_opt;
  char *search_value = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));

  do
  {
    printf("\nEnter username to search: ");
    fflush(stdin);
    scanf("%s", search_value);

    // Search
    search_by_username(search_value);

    do
    {
      printf("\nDo you want to continue searching (y/n): ");
      // fflush(stdin);
      getchar(); // Remove the whitespace
      scanf("%c", &stop_opt);

      switch (stop_opt)
      {
      case 'y':
        break;
      case 'n':
        stop_searching = true;
        break;
      default:
        printf("Invalid option!\n");
        break;
      } 
    } while (stop_opt != 'y' && stop_opt != 'n');

  } while (!stop_searching);

  // Free up the allocated space
  free(search_value);
}