#include "utils.h"

void view_blog (char* blog_name) {
    strcat(blog_name, ".txt");

    FILE *fp=fopen(blog_name, "r");
    char *line = NULL;
    size_t len = 0;

    getline (&line, &len, fp);
    fclose(fp);

    printf("%s", line );
    
}


void updowngrade(char *username, int isup) {

    char usernames[40][12];
   int ratings[40];
   char ratingstr[10];

    char *line = NULL; 
    size_t len = 0;
    ssize_t nread;
    int i=0;

    FILE *fp=fopen("ratings.txt", "r");    
    
    if (fp!= NULL) {
        
        while ((nread = getline (&line, &len, fp)) != -1) {
            sscanf(line, "%s %s", usernames[i], ratingstr);
            ratings[i]=atoi(ratingstr);
	        if (strcmp(usernames[i], username)==0) {
                ratings[i]+= (isup) ? 1: -1; 
	        }
            i++;
        }
    }
    fclose(fp);

    FILE *fp2=fopen("ratings.txt", "w");
    if (fp2 != NULL) {
        for (int j =0; j < i; j++) {
             fprintf(fp2, "%s %d\n", usernames[j], ratings[j]);
        }
    }
    fclose(fp2);
    
}


int check_password(char* username, char* password_to_check) {

    char read_username[12];
    char read_password[12];
    char decrypted_password[12];

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;


    FILE *fp=fopen("pwds.txt", "r");    
    if (fp!= NULL) {
        
        while ((nread = getline (&line, &len, fp)) != -1) {
            sscanf(line, "%s %s", read_username, read_password); 
            
            decrypt(read_password, decrypted_password);
            
            
            if ((strcmp(read_username, username) ==0) && (strcmp(password_to_check, decrypted_password) ==0)) {
                fclose(fp);
                return 1;
            }
        }

    fclose(fp);
    return 0;
    }

}

void decrypt(char *password, char *decrypted) {
    int i=0;
    while (password[i]!='\0') {
        decrypted[i] = password[i]+1;
        i++;
    }
    decrypted[i]='\0';

}

void encrypt(char *password, char *encrypted) {
    int i=0;
    while (password[i]!=0) {
        encrypted[i]=password[i]-1;
        i++;
    }
    encrypted[i]='\0';

}


void update_blog(char *username) {
    char filename[12];
    char *line;
    size_t size;
    strcpy(filename, username);
    strcat(filename, ".txt");

    line = (char*) malloc (MAX_SIZE_BLOG_POST);
    
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    ;
    
    printf("Enter new blog post: ");
    getline(&line, &size, stdin);

    FILE *fp=fopen(filename, "w");
    if (fp!=NULL) {
	    fprintf(fp,"%s",line); 
    }

}


void make_new_user(char *new_username, char *new_password) {
    FILE *fp;
    char filename[12];
    strcpy(filename, new_username);
    strcat(filename, ".txt");

    fp =fopen(filename, "w");
    fclose(fp);

    fp =fopen("pwds.txt", "a");
    fprintf(fp, "%s %s\n", new_username, new_password);
    fclose(fp);

    fp =fopen("ratings.txt", "a");
    fprintf(fp, "%s %d\n", new_username, 0);
    fclose(fp);
}
