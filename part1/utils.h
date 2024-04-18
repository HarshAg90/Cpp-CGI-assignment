#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE_BLOG_POST 100

void view_blog (char* blog_name);


void updowngrade(char *username, int isup);

void decrypt(char *password, char *decrypted);

void encrypt(char *password, char *encrypted);


int check_password(char* username, char* password);

void update_blog(char *username);

void make_new_user(char *new_username, char *new_password);
