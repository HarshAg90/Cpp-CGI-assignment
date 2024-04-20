#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    cout << "Content-type:application/json\n\n";

    if (strcmp(getenv("REQUEST_METHOD"), "POST") == 0)
    {
        int len;
        char *lenstr = getenv("CONTENT_LENGTH");

        if (lenstr != NULL && (len = atoi(lenstr)) != 0)
        {
            char *post_data = new char[len];
            fgets(post_data, len + 1, stdin);
            cout << post_data;
        }
    }
    else if (strcmp(getenv("REQUEST_METHOD"), "GET") == 0)
    {
        cout << getenv("QUERY_STRING") << endl;
    }
    else
    {
        cout << "request is not supported";
    }
    return 0;
}

// #include<iostream>
// using namespace std;

// int main(){
//     cout<< "Content type:text/html \n\n";
//     cout<< "<html>";
//     cout<< "<head><title>stupid webpage</title><head>";
//     cout<< "<body>";
//     cout<< "<h1>this works</h1>";
//     cout<< "<h1>here is your website</h1>";
//     cout<< "<p>i am in love with the fairytale</p>";
//     cout<< "</body>";
//     cout<< "</html>";
// }