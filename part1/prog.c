#include <stdio.h>
#include <string.h>
#include "utils.h"

int get_menu_choice()
{
    int choice;

    do
    {
        printf("1. Uprate a blog\n");
        printf("2. Downrate a blog\n");
        printf("3. View a blog\n");
        printf("4. Replace your blog\n");
        printf("5. Make a new user (if admin)\n");
        printf("0. Quit\n");
        printf("What would you like to do: \n");

        scanf("%d", &choice);

    } while (!(0 <= choice && choice <= 5));

    return choice;
}

int main()
{

    char username[12];
    char view_username[12];
    char new_username[12];
    char new_password[12];
    char encrypted_new_password[12];
    char filename[12];
    char password[12];

    int choice;
    int already_rated = 0;

    printf("Enter your name: ");
    scanf("%s", username);

    strcpy(filename, username);
    strcat(filename, ".txt");

    printf("Enter your password: ");
    scanf("%s", password);

    int outcome = check_password(username, password);
    if (outcome == 0)
        return 0;

    do
    {
        choice = get_menu_choice();

        if ((choice == 1) || (choice == 2))
        {
            if (!already_rated)
            {
                printf("Which user: ");
                scanf("%s", view_username);
                updowngrade(view_username, (choice == 1));
                already_rated = 1;
            }
        }
        else if (choice == 3)
        {
            char blog_name[12];
            printf("Whose blog: ");
            scanf("%s", blog_name);
            view_blog(blog_name);
        }
        else if (choice == 4)
        {
            update_blog(username);
        }
        else if (choice == 5)
        { // only if admin
            if (strcmp(username, "admin") == 0)
            {
                printf("Enter new username: ");
                scanf("%s", new_username);
                printf("Enter new password: ");
                scanf("%s", new_password);
                encrypt(new_password, encrypted_new_password);

                make_new_user(new_username, encrypted_new_password);
            }
            else
            {
                printf("You need to be admin to do this action.\n");
            }
        }

    } while (choice != 0);

    return 0;
}
