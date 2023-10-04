bool is_valid_ip_address(char *ip_address)
{
  // Check if the IP address is empty.
  if (strlen(ip_address) == 0)
  {
    return false;
  }

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

void get_domain_from_ip(char *param)
{
  // This return only 1 domain name
  // // Convert the IP address string to a socket address.
  // struct sockaddr_in addr;
  // addr.sin_family = AF_INET;
  // addr.sin_port = 0;
  // inet_pton(AF_INET, param, &addr.sin_addr);

  // // Get the host name associated with the socket address.
  // char hostname[NI_MAXHOST];
  // int err = getnameinfo((struct sockaddr *)&addr, sizeof(addr), hostname, sizeof(hostname), NULL, 0, 0);
  // if (err != 0)
  // {
  //   printf("Could not get domain name for IP address '%s': %s\n", param, gai_strerror(err));
  //   exit(1);
  // }

  // // Print the domain name to the console.
  // printf("The domain name for IP address '%s' is '%s'\n", param, hostname);

  // This return more than 1 domain name
  // Convert the IP address string to a socket address.
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = 0;
  inet_pton(AF_INET, param, &addr.sin_addr);

  // Get the host information for the socket address.
  struct addrinfo hints, *res;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_CANONNAME;

  int err = getaddrinfo(param, NULL, &hints, &res);
  if (err != 0) {
    printf("Could not get host information for IP address '%s': %s\n", param, gai_strerror(err));
    exit(1);
  }

  // Print the domain names of the host.
  printf("The domain names for IP address '%s' are:\n", param);
  for (struct addrinfo *p = res; p != NULL; p = p->ai_next) {
    char hostname[NI_MAXHOST];
    err = getnameinfo(p->ai_addr, p->ai_addrlen, hostname, sizeof(hostname), NULL, 0, 0);
    if (err != 0) {
      printf("Could not get domain name for IP address '%s': %s\n", param, gai_strerror(err));
      continue;
    }

    printf("  %s\n", hostname);
  }

  freeaddrinfo(res);
}
