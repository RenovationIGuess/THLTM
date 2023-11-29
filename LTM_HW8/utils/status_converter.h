void account_status_converter(char *status, int status_code)
{
  switch (status_code)
    {
    case 0:
      strcpy(status, "Blocked");
      break;
    case 1:
      strcpy(status, "Active");
      break;
    case 2:
      strcpy(status, "Idle");
      break;
    default:
      printf("Invalid status code: %d\n", status_code);
      break;
    }
}