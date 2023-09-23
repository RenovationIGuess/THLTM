// rewrite the data of the file
void rewrite_file()
{
  // Open the file
  f = fopen("nguoidung.txt", "w");

  // Write to the file
  node *p = l;
  if (p == NULL)
  {
    printf("\nCon tro NULL!\n");
    return;
  }
  while (p != NULL)
  {
    fprintf(f, "%s %s %d\n", p->data.username, p->data.password, p->data.status);
    p = p->next;
  }

  // Close the file
  fclose(f);
}

// Display the signle linked list
void display_linked_list()
{
  printf("\n%-5s%-20s%-25s%-25s\n", "", "Username", "Password", "Status");

  node *p = l;
  int i = 0;
  char *status = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));

  if (p == NULL)
  {
    printf("\nCon tro NULL!\n");
    return;
  }

  while (p != NULL)
  {
    account_status_converter(status, p->data.status);
    printf("%-5d%-20s%-25s%-25s\n", i + 1, p->data.username, p->data.password, status);
    i++;
    p = p->next;
  }

  // Free space
  free(status);
}

// Normal .txt file
void read_from_file()
{
  printf("\nReading from nguoidung.txt...\n");

  // Open the file
  if ((f = fopen("nguoidung.txt", "a+")) == NULL)
  {
    printf("Cannot open %s.", "nguoidung.txt");
    exit(1);
  }

  // Create the array
  ElmType *a = (ElmType *)malloc(MAX_ARRAY_LENGTH * sizeof(ElmType));

  // Move the read cursor to file's beginning position
  fseek(f, 0, SEEK_SET);

  int i = 0;
  l = prev = cur = NULL;

  while (fscanf(f, "%s%s%d", a[i].username, a[i].password, &a[i].status) != EOF)
  {
    insert_after_cur(a[i]);
    i++;
  }

  // Display the read list
  display_linked_list();

  // Close when done :))
  fclose(f);
}

// Binary file like .dat
void read_from_file_binary()
{
  printf("\nReading from nguoidung.txt...\n");

  // Open the file
  if ((f = fopen("nguoidung.txt", "rb")) == NULL)
  {
    printf("Cannot open %s.", "nguoidung.txt");
    exit(1);
  }

  // Create the array
  ElmType *a = (ElmType *)malloc(MAX_ARRAY_LENGTH * sizeof(ElmType));

  // Move the cursor of the reader to the last position in the file
  fseek(f, 0, SEEK_END);

  // Calculate the number of element to read from file
  number_of_users = ftell(f) / sizeof(ElmType);

  int i = 0, num;

  // Set the cursor back to the first position in file
  fseek(f, 0, SEEK_SET);

  // Read from the file
  // Save into array a | size in bytes of each element in file to read
  // number of items to read | pointer to file object
  num = fread(a, sizeof(ElmType), number_of_users, f);

  // Create the list
  l = create_note(a[0]);

  cur = l;
  prev = NULL;
  for (i = 1; i < number_of_users; ++i)
  {
    insert_after_cur(a[i]);
  }

  // Display the read list
  display_linked_list();
}

// Search item in the list using the username
void search_by_username(char input_value[])
{
  char *status = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
  int result; // Value use to get the strcmp result
  node *p = l;
  if (p == NULL)
  {
    printf("\nCon tro NULL!\n");
    return;
  }
  while (p != NULL)
  {
    result = strcmp(p->data.username, input_value);
    if (result == 0)
    {
      // Set the current pointer to founded item
      // cur = p;
      account_status_converter(status, p->data.status);
      printf("\n%-20s%-25s\n", "Username", "Status");
      printf("%-20s%-25s\n", p->data.username, status);
      break;
    }
    p = p->next;
  }

  if (p == NULL)
    printf("Account not found!\n");

  // Free space
  free(status);
}