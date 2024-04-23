#include <iostream>
#include <cstring>

// This code is for API sample solution for 2nd part of assignment
using namespace std;

void handleAddItem()
{
    // Logic for handling addItem endpoint

    cout << "Handling addItem endpoint" << endl;
}

void handleGetItem()
{
    // Logic for handling getItem endpoint

    cout << "Handling getItem endpoint" << endl;
}

void handleDeleteItem()
{
    // Logic for handling deleteItem endpoint

    cout << "Handling deleteItem endpoint" << endl;
}

int main()
{
    cout << "Content-type:application/json\n\n";

    char *requestMethod = getenv("REQUEST_METHOD");
    char *requestURI = getenv("REQUEST_URI");

    if (requestMethod != nullptr && requestURI != nullptr)
    {
        if (strcmp(requestMethod, "POST") == 0)
        {
            if (strcmp(requestURI, "/addItem") == 0)
            {
                handleAddItem();
            }
            else
            {
                cout << "Invalid endpoint for POST request";
            }
        }
        else if (strcmp(requestMethod, "GET") == 0)
        {
            if (strcmp(requestURI, "/getItem") == 0)
            {
                handleGetItem();
            }
            else if (strcmp(requestURI, "/deleteItem") == 0)
            {
                handleDeleteItem();
            }
            else
            {
                cout << "Invalid endpoint for GET request";
            }
        }
        else
        {
            cout << "Unsupported request method";
        }
    }
    else
    {
        cout << "Unable to determine request method or URI";
    }

    return 0;
}