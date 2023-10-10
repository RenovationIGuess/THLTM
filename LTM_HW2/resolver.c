#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdbool.h>
#include <regex.h>
#include "./utils/check_valid_ip_address.h"
#include "./utils/check_valid_domain.h"
#include "./includes/ip_address.h"
#include "./includes/domain.h"

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("Usage: %s [1|2] [domain|ip]\n", argv[0]);
    exit(1);
  }

  // Make a copy of the IP address string.
  // char *parameter1 = strdup(argv[1]);
  char *parameter2 = strdup(argv[2]);
  char *second_check = strdup(argv[2]);

  // Parameter 1 could be [1, 2]
  switch (atoi(argv[1]))
  {
  case 1:
    if (is_valid_ip_address(parameter2))
      get_domain_from_ip(argv[2]);
    else if (is_valid_domain_name_but_not_ip_address(second_check))
    {
      printf("Wrong parameter\n");
    } else printf("Not found information\n"); // Because the IP address is wrong format
    break;
  case 2:
    if (is_valid_domain_name_but_not_ip_address(parameter2))
      get_ip_from_domain(argv[2]);
    else // if (is_valid_ip_address(second_check))
    {
      printf("Wrong parameter\n");
    }
    break;
  default:
    printf("Wrong parameter\n");
    break;
  }

  return 0;
}
