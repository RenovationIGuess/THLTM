bool is_ip_address_format(char *input_string)
{
  regex_t regex;
  int result = regcomp(&regex, "^([0-9]{1,3}\\.){3}[0-9]{1,3}$", REG_EXTENDED);
  if (result != 0)
  {
    return false;
  }

  result = regexec(&regex, input_string, 0, NULL, 0);
  regfree(&regex);
  return result == 0;
}

bool is_valid_ip_address(char *ip_address)
{
  // Check if the IP address is empty.
  if (strlen(ip_address) == 0)
  {
    return false;
  }

  // Check if the input string is in an IP address format
  // if (!is_ip_address_format(ip_address))
  // {
  //   printf('')
  //   return false;
  // }

  // Check if the IP address is in the correct format.
  if (!strstr(ip_address, "."))
  {
    return false;
  }

  // Split the IP address into four octets.
  char *octets[4];
  int num_octets = 0;
  char *token = strtok(ip_address, ".");
  while (token != NULL)
  {
    octets[num_octets++] = token;
    token = strtok(NULL, ".");
  }

  // Check if the number of octets is correct.
  if (num_octets != 4)
  {
    return false;
  }

  // Check if each octet is a valid number.
  for (int i = 0; i < num_octets; i++)
  {
    for (int j = 0; j < strlen(octets[i]); j++)
    {
      if (!isdigit(octets[i][j]))
      {
        return false;
      }
    }
  }

  // Check if each octet is in the range 0-255.
  for (int i = 0; i < num_octets; i++)
  {
    int octet_value = atoi(octets[i]);
    if (octet_value < 0 || octet_value > 255)
    {
      return false;
    }
  }

  // The IP address is valid.
  return true;
}