bool is_valid_domain_name(char *domain_name)
{
  // Check if the domain name is empty.
  if (strlen(domain_name) == 0)
  {
    return false;
  }

  // Check if the domain name contains any invalid characters.
  for (int i = 0; i < strlen(domain_name); i++)
  {
    if (!isalnum(domain_name[i]) && domain_name[i] != '-' && domain_name[i] != '.')
    {
      return false;
    }
  }

  // Check if the domain name starts or ends with a hyphen.
  if (domain_name[0] == '-' || domain_name[strlen(domain_name) - 1] == '-')
  {
    return false;
  }

  // Check if the domain name contains two consecutive hyphens.
  for (int i = 0; i < strlen(domain_name) - 1; i++)
  {
    if (domain_name[i] == '-' && domain_name[i + 1] == '-')
    {
      return false;
    }
  }

  // Check if the domain name contains a top-level domain (TLD).
  if (!strstr(domain_name, "."))
  {
    return false;
  }

  // The domain name is valid.
  return true;
}

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
    printf("Could not resolve domain name '%s': %s\n", param, gai_strerror(err));
    exit(1);
  }

  // Print the IP addresses of the host.
  printf("The IP addresses of '%s' are:\n", param);
  for (struct addrinfo *p = res; p != NULL; p = p->ai_next)
  {
    char ip_address[16];
    inet_ntop(p->ai_family, &((struct sockaddr_in *)p->ai_addr)->sin_addr, ip_address, sizeof(ip_address));

    printf("  %s\n", ip_address);
  }

  freeaddrinfo(res);
}
