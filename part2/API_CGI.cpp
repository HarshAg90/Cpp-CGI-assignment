#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

using namespace std;
using namespace rapidjson;

const char *BLOG_FILE = "blogs.json";

// Function to generate a unique ID for a blog post
int generateUniqueId()
{
    static int id = 0;
    return ++id;
}

// Function to save a blog post to the file
void saveBlog(const Value &blog)
{
    ofstream outputFile(BLOG_FILE, ios::app);
    if (outputFile.is_open())
    {
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        blog.Accept(writer);
        outputFile << buffer.GetString() << endl;
        outputFile.close();
        cout << "Blog created successfully" << endl;
    }
    else
    {
        cout << "Unable to open file for writing" << endl;
    }
}

// Function to read all blogs from the file
void readAllBlogs()
{
    ifstream inputFile(BLOG_FILE);
    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            cout << line << endl;
        }
        inputFile.close();
    }
    else
    {
        cout << "Unable to open file for reading" << endl;
    }
}

// Function to delete a blog post by its ID
void deleteBlogById(int id)
{
    ifstream inputFile(BLOG_FILE);
    ofstream tempFile("temp.json");
    if (inputFile.is_open() && tempFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            Document doc;
            doc.Parse(line.c_str());
            if (!doc.HasParseError() && doc.IsObject() && doc.HasMember("id"))
            {
                int blogId = doc["id"].GetInt();
                if (blogId != id)
                {
                    tempFile << line << endl;
                }
            }
        }
        inputFile.close();
        tempFile.close();
        remove(BLOG_FILE);
        rename("temp.json", BLOG_FILE);
        cout << "Blog deleted successfully" << endl;
    }
    else
    {
        cout << "Unable to delete blog" << endl;
    }
}

int main()
{
    cout << "Content-type:application/json\n\n";

    char *requestMethod = getenv("REQUEST_METHOD");
    char *requestURI = getenv("REQUEST_URI");

    if (requestMethod != nullptr)
    {
        if (strcmp(requestMethod, "POST") == 0)
        {
            int len;
            char *lenstr = getenv("CONTENT_LENGTH");
            if (lenstr != NULL && (len = atoi(lenstr)) != 0)
            {
                char *post_data = new char[len];
                fgets(post_data, len + 1, stdin);
                Document blog;
                blog.Parse(post_data);
                if (!blog.HasParseError())
                {
                    int id = generateUniqueId();
                    blog.AddMember("id", id, blog.GetAllocator());
                    saveBlog(blog);
                }
                else
                {
                    cout << "Invalid JSON data" << endl;
                }
                delete[] post_data;
            }
            else
            {
                cout << "Invalid POST request" << endl;
            }
        }
        else if (strcmp(requestMethod, "GET") == 0)
        {
            if (requestURI != nullptr)
            {
                if (strcmp(requestURI, "/readAllBlogs") == 0)
                {
                    readAllBlogs();
                }
                else
                {
                    cout << "Invalid endpoint for GET request" << endl;
                }
            }
            else
            {
                cout << "Unable to determine request URI" << endl;
            }
        }
        else if (strcmp(requestMethod, "DELETE") == 0)
        {
            if (requestURI != nullptr && strncmp(requestURI, "/deleteBlog/", 12) == 0)
            {
                int id = atoi(requestURI + 12);
                deleteBlogById(id);
            }
            else
            {
                cout << "Invalid endpoint for DELETE request" << endl;
            }
        }
        else
        {
            cout << "Unsupported request method" << endl;
        }
    }
    else
    {
        cout << "Unable to determine request method" << endl;
    }

    return 0;
}

// #include <iostream>
// #include <cstring>

// // Creating GET and POST requests over multiple Endpoints
// using namespace std;

// void handleAddItem() {
//     // Logic for handling addItem endpoint

//     cout << "Handling addItem endpoint" << endl;
// }

// void handleGetItem() {
//     // Logic for handling getItem endpoint

//     cout << "Handling getItem endpoint" << endl;
// }

// void handleDeleteItem() {
//     // Logic for handling deleteItem endpoint

//     cout << "Handling deleteItem endpoint" << endl;
// }

// int main() {
//     cout << "Content-type:application/json\n\n";

//     char *requestMethod = getenv("REQUEST_METHOD");
//     char *requestURI = getenv("REQUEST_URI");

//     if (requestMethod != nullptr && requestURI != nullptr) {
//         if (strcmp(requestMethod, "POST") == 0) {
//             if (strcmp(requestURI, "/addItem") == 0) {
//                 handleAddItem();
//             } else {
//                 cout << "Invalid endpoint for POST request";
//             }
//         } else if (strcmp(requestMethod, "GET") == 0) {
//             if (strcmp(requestURI, "/getItem") == 0) {
//                 handleGetItem();
//             } else if (strcmp(requestURI, "/deleteItem") == 0) {
//                 handleDeleteItem();
//             } else {
//                 cout << "Invalid endpoint for GET request";
//             }
//         } else {
//             cout << "Unsupported request method";
//         }
//     } else {
//         cout << "Unable to determine request method or URI";
//     }

//     return 0;
// }

// #include <iostream>
// #include <cstring>

// using namespace std;

// int main()
// {
//     cout << "Content-type:application/json\n\n";

//     if (strcmp(getenv("REQUEST_METHOD"), "POST") == 0)
//     {
//         int len;
//         char *lenstr = getenv("CONTENT_LENGTH");

//         if (lenstr != NULL && (len = atoi(lenstr)) != 0)
//         {
//             char *post_data = new char[len];
//             fgets(post_data, len + 1, stdin);
//             cout << post_data;
//         }
//     }
//     else if (strcmp(getenv("REQUEST_METHOD"), "GET") == 0)
//     {
//         cout << getenv("QUERY_STRING") << endl;
//     }
//     else
//     {
//         cout << "request is not supported";
//     }
//     return 0;
// }
