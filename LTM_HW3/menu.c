#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <netdb.h>
#include <regex.h>
#include <arpa/inet.h>

#define MAX_ARRAY_LENGTH 1024
#define MAX_STRING_LENGTH 256

FILE *f;
int number_of_users;

// MSSV
const char my_activation_code[] = "20204998";

char menu_options[9][101] = {
    "Register",
    "Activate",
    "Sign in",
    "Search",
    "Change password",
    "Sign out",
    "Homepage with domain name",
    "Homepage with IP address",
};

// This is out of scope since status is integer :))
// char valid_status_value[5][101] = {
//     "active",
//     "idle",
//     "blocked",
// };

int option;
int exit_option;
// Use to check if the user is logged in or not
bool is_authenticated = false;

// Current year
// time_t seconds = time(NULL);
// struct tm *current_time = localtime(&seconds);
// const int current_year = current_time->tm_year + 1900;
const int current_year = 2023;
const int min_year = 1956;

typedef struct User
{
    char username[MAX_STRING_LENGTH];
    char password[MAX_STRING_LENGTH];
    int status;
    char homepage[MAX_STRING_LENGTH];
} User;

// Element type :))
typedef struct User ElmType;

#include "./lib/linked_list.h"

node *current_user;

#include "./utils/validators.h"
#include "./utils/status_converter.h"
#include "./utils/file_actions.h"
#include "./utils/check_valid_ip_address.h"
#include "./utils/check_valid_domain.h"
#include "./include/register_user.h"
#include "./include/activate.h"
#include "./include/sign_in.h"
#include "./include/search_user.h"
#include "./include/change_password.h"
#include "./include/sign_out.h"
#include "./include/ip_address.h"
#include "./include/domain.h"

void handle_option()
{
    switch (option)
    {
    case 1:
        register_user();
        break;
    case 2:
        activate();
        break;
    case 3:
        sign_in();
        break;
    case 4:
        search_user();
        break;
    case 5:
        change_password();
        break;
    case 6:
        sign_out();
        break;
    case 7:
        ip_address_homepage();
        break;
    case 8:
        domain_homepage();
        break;
    default:
        break;
    }
}

void menu()
{
    // Read from file first
    read_from_file();

    // Perform the menu
    do
    {
        printf("\nUSER MANAGEMENT PROGRAM\n");
        printf("================================================================\n");
        for (int i = 0; i < 8; ++i)
        {
            printf("%d. %s\n", i + 1, menu_options[i]);
        }
        printf("Your choice (1-8, other to quit): ");
        custom_fflush_stdin();
        scanf("%d", &option);
        handle_option(option);
        // printf("You entered: %d\n", option);
    } while (option >= 1 && option <= 8);
}

int main(int argc, char *argv[])
{
    menu();
    return 0;
}