void get_ip_from_domain(char *param)
{
  // Get the host information for the given domain name.
  struct addrinfo hints, *res;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_CANONNAME;

  int err = getaddrinfo(param, NULL, &hints, &res);
  if (err != 0)
  {
    printf("Not found information\n");
    return;
    // exit(1);
  }

  // Print the IP addresses of the host.
  int i = 0;
  for (struct addrinfo *p = res; p != NULL; p = p->ai_next)
  {
    if (p->ai_family == AF_INET || p->ai_family == AF_INET6)
    {
      char ip_address[INET6_ADDRSTRLEN];
      void *addr;
      if (p->ai_family == AF_INET)
      {
        addr = &((struct sockaddr_in *)p->ai_addr)->sin_addr;
      }
      else
      {
        addr = &((struct sockaddr_in6 *)p->ai_addr)->sin6_addr;
      }
      inet_ntop(p->ai_family, &((struct sockaddr_in *)p->ai_addr)->sin_addr, ip_address, sizeof(ip_address));

      if (i == 0)
      {
        printf("Official IP: %s\n", ip_address);
        printf("Alias IP:\n");
        i++;
      }
      else
      {
        printf("%s\n", ip_address);
      }
    }
    else
      printf("Not found information\n");
  }

  freeaddrinfo(res);
}

// Return the IP addresses that related to the domain
void domain_homepage()
{
  // First check if user is logged in or not
  if (!is_authenticated)
  {
    printf("\nYou must be logged in to perform this action!\n");
    return;
  }

  char *homepage_check = strdup(current_user->data.homepage);

  printf("\nUser homepage: %s\n", current_user->data.homepage);
  if (is_valid_domain_name_but_not_ip_address(homepage_check))
    get_ip_from_domain(current_user->data.homepage);
  else
    printf("Not found information\n");
}