/*
  Return true if the typed status from user is valid
  which means that the typed value is in the status array
*/
// Below are the check_status_input in case the status is string
// bool check_status_input(char input_value[])
// {
//   int result;
//   for (int i = 0; i < 3; ++i)
//   {
//     result = strcmp(input_value, valid_status_value[i]);
//     if (result == 0)
//       return true;
//   }
//   return false;
// }

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

/*
    Return true if the input_valid is valid
    false if the input_valid is invalid
    This will only works with years that have 4 digits :((
*/
bool check_activation_code(char input_value[])
{
  // Case: activation code is coder's MSSV
  if (strcmp(input_value, my_activation_code) == 0) 
  {
    return true;
  }
  printf("Invalid activation code!\n\n");
  return false;

  // The below code is for the more open case where activation code
  // is not just our MSSV

  // First it has to be 8 characters
  if (strlen(input_value) != 8)
  {
    printf("The activation code must be 8 characters!\n\n");
    return false;
  }

  int multiplier = 1000;
  int year = 0;
  // Next the first 4 characters must be from 1956 -> current year value
  // Get the int value of first 4 character
  for (int i = 0; i < 4; ++i)
  {
    // Though 0 is wrong but since this is an open request so we leave it
    if (isdigit(input_value[i]) != 0)
    {
      int current_number = input_value[i] - '0';

      year = year + current_number * multiplier;
      multiplier /= 10;
    }
    else
    {
      printf("Invalid activation code!\n\n");
      return false;
    }
  }

  // Now we have the year in the activation code, let's compare
  if (year < min_year || year > current_year)
  {
    printf("Invalid activation code!\n\n");
    return false;
  }

  // If it passed all the tests => valid
  return true;
}

// Check username for signing out
bool check_username_for_sign_out(char input_value[])
{
  int result;

  // First compare with the logged-in account
  result = strcmp(input_value, current_user->data.username);

  if (result == 0)
  {
    printf("Sign out successfully!\n");
    // return true;
    exit(0);
  }
  else
  {
    // Now we surely know that the typed username is not correct
    // But it has 2 cases:
    // 1. Existed username but not logged in yet :))
    // 2. Non-existed username
    node *p = l;
    if (p == NULL)
    {
      printf("\nCon tro NULL!\n");
      return false;
    }

    while (p != NULL)
    {
      // If its the current user then skip cuz this is duplicate check
      // Should set a flag or something to prevent checking every elements
      // if (strcmp(p->data.username, current_user->data.username) == 0)
      //   continue;

      result = strcmp(input_value, p->data.username);
      if (result == 0)
      {
        printf("This is not the logged account!\n");
        return false;
      }
      p = p->next;
    }

    // Case 2
    if (p == NULL)
      printf("Username not found!\n");
  }

  return false;
}
