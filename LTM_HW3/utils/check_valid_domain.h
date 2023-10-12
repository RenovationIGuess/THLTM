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

bool is_valid_domain_name_but_not_ip_address(char *domain_name) {
  // Check if the domain name is a valid domain name.
  if (!is_valid_domain_name(domain_name)) {
    return false;
  }

  // Check if the domain name is an IP address.
  if (is_valid_ip_address(domain_name)) {
    return false;
  }

  // The domain name is a valid domain name but not an IP address.
  return true;
}