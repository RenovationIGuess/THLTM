void get_domain_from_ip(char *param)
{
  // This return more than 1 domain name
  // Convert the IP address string to a socket address.
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = 0;
  inet_pton(AF_INET, param, &addr.sin_addr);

  // struct sockaddr_storage addr;
  // memset(&addr, 0, sizeof(addr));
  // addr.ss_family = AF_UNSPEC;
  // inet_pton(AF_INET, param, &((struct sockaddr_in *)&addr)->sin_addr);

  // Get the host information for the socket address.
  struct addrinfo hints, *res;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_CANONNAME;

  int err = getaddrinfo(param, NULL, &hints, &res);
  if (err != 0 || res == NULL)
  {
    printf("Not found information\n");
    return;
    // exit(1);
  }

  // Print the domain names of the host.
  int i = 0;
  for (struct addrinfo *p = res; p != NULL; p = p->ai_next)
  {
    char hostname[NI_MAXHOST];
    err = getnameinfo(p->ai_addr, p->ai_addrlen, hostname, sizeof(hostname), NULL, 0, 0);
    if (err != 0)
    {
      printf("Not found information\n");
      continue;
    }

    if (i == 0)
    {
      printf("Official name: %s\n", hostname);
      printf("Alias name:\n");
      i++;
    }
    else
    {
      printf("%s\n", hostname);
    }
  }

  freeaddrinfo(res);
}

// Return the domains related to the IP address
void ip_address_homepage()
{
  // First check if user is logged in or not
  if (!is_authenticated)
  {
    printf("\nYou must be logged in to perform this action!\n");
    return;
  }

  char *homepage_check = strdup(current_user->data.homepage);
  char *second_check = strdup(current_user->data.homepage);

  printf("\nUser homepage: %s\n", current_user->data.homepage);
  if (is_valid_ip_address(homepage_check))
    get_domain_from_ip(current_user->data.homepage);
  else if (!is_valid_domain_name(second_check)) {
    printf("Not found information\n");
  }
}
