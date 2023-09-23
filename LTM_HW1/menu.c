#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#define MAX_ARRAY_LENGTH 1024
#define MAX_STRING_LENGTH 256

FILE *f;
int number_of_users;

// MSSV
const char my_activation_code[] = "20204998";

char menu_options[7][101] = {
    "Register",
    "Activate",
    "Sign in",
    "Search",
    "Change password",
    "Sign out",
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
} User;

// Element type :))
typedef struct User ElmType;

#include "./lib/linked_list.h"

node *current_user;

#include "./utils/validators.h"
#include "./utils/status_converter.h"
#include "./utils/file_actions.h"
#include "./include/register_user.h"
#include "./include/activate.h"
#include "./include/sign_in.h"
#include "./include/search_user.h"
#include "./include/change_password.h"
#include "./include/sign_out.h"

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
    default:
        // printf("Are you sure you want to exit (1 - yes | 0 - no): ");
        // scanf("%d", &exit_option);
        // while (exit_option != 0 && exit_option != 1) {
        //     printf("Invalid exit option! Enter again: ");
        //     scanf("%d", &exit_option);
        // }
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
        for (int i = 0; i < 6; ++i)
        {
            printf("%d. %s\n", i + 1, menu_options[i]);
        }
        printf("Your choice (1-6, other to quit): ");
        fflush(stdin);
        scanf("%d", &option);
        handle_option(option);
        // printf("You entered: %d\n", option);
    } while (option >= 1 && option <= 6);
}

int main(int argc, char *argv[])
{
    menu();
    return 0;
}
