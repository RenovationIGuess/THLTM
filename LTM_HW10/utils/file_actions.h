void readFile()
{
  fptr = fopen("nguoidung.txt", "r+");
  rewind(fptr);
  if (fptr == NULL)
  {
    printf("Could not open file!");
    return;
  };
  a = (AccountList *)malloc(MAX * sizeof(AccountList));
  if (a == NULL)
  {
    printf("Cannot allocate memory!\n");
    return;
  }
  while (fscanf(fptr, "%s %s %d", a[n].username, a[n].password, &a[n].status) == 3)
    n++;
  printf("\nSo node hien co: %d \n", n);
  cur = root;
  for (int i = 0; i < n; ++i)
  {
    if (i == 0)
    {
      root = makeNewNode(a[i]);
      cur = root;
    }
    else
      insertAfterCur(root, a[i]);
  }
  fclose(fptr);
};

void getToFile()
{
  fptr = fopen("nguoidung.txt", "w+");
  cur = root;
  while (cur != NULL)
  {
    fprintf(fptr, "%s %s %d\n", cur->element.username, cur->element.password, cur->element.status);
    cur = cur->next;
  }
  fclose(fptr);
};

int getMsgToFile()
{

  time_t t; // not a primitive datatype
  time(&t);
  char *time = ctime(&t);
  time[strlen(time) - 1] = '\0';
  char msg[1025] = "";
  strcat(msg, "[");
  strcat(msg, time);
  strcat(msg, "] ");
  strcat(msg, input.data_type);
  char filename[20] = "message/";
  strcat(filename, account);
  strcat(filename, ".txt");
  fpMsg = fopen(filename, "a+");
  if (fpMsg == NULL)
  {
    printf("Cannot open file!\n");
    return 1;
  }
  fprintf(fpMsg, "%s\n", msg);
  fclose(fpMsg);
  return 0;
}