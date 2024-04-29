#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Blog
{
    int index;
    string title;
    string content;
};

const char *BLOG_FILE_PATH = "blogs.txt";
vector<Blog> blogs;

void loadBlogsFromFile()
{
    ifstream infile(BLOG_FILE_PATH);
    blogs.clear();
    if (infile.is_open())
    {
        string line;
        int index = 1;
        while (getline(infile, line))
        {
            size_t pos = line.find(',');
            if (pos != string::npos && pos + 1 < line.length())
            {
                string title = line.substr(0, pos);
                string content = line.substr(pos + 1);
                blogs.push_back({index, title, content});
                index++;
            }
        }
        infile.close();
    }
}

void saveBlogsToFile()
{
    ofstream outfile(BLOG_FILE_PATH);
    if (outfile.is_open())
    {
        for (const auto &blog : blogs)
        {
            outfile << blog.title << "," << blog.content << endl;
        }
        outfile.close();
    }
}

void handleAddBlog()
{
    // Read the content of the blog from the request body
    string title, content;
    cout << "Content-type:text/plain\n\n";
    cout << "Enter the title of the blog: ";
    getline(cin, title);
    cout << "Enter the content of the blog: ";
    getline(cin, content);
    int index = blogs.empty() ? 1 : blogs.back().index + 1;
    blogs.push_back({index, title, content});
    saveBlogsToFile();
    cout << "Blog added successfully." << endl;
}

void handleShowBlog()
{
    cout << "Content-type:text/plain\n\n";
    for (const auto &blog : blogs)
    {
        cout << "Index: " << blog.index << "\nTitle: " << blog.title << "\nContent: " << blog.content << "\n\n";
    }
}

void handleDeleteBlog()
{
    cout << "Content-type:text/plain\n\n";
    int index;
    cout << "Enter the index of the blog to delete: ";
    cin >> index;
    auto it = find_if(blogs.begin(), blogs.end(), [index](const Blog &blog)
                      { return blog.index == index; });
    if (it != blogs.end())
    {
        blogs.erase(it);
        saveBlogsToFile();
        cout << "Blog deleted successfully." << endl;
    }
    else
    {
        cout << "Error: Blog with specified index not found." << endl;
    }
}

int main()
{
    loadBlogsFromFile();

    char *requestMethod = getenv("REQUEST_METHOD");

    if (requestMethod != nullptr)
    {
        if (strcmp(requestMethod, "POST") == 0)
        {
            handleAddBlog();
        }
        else if (strcmp(requestMethod, "GET") == 0)
        {
            handleShowBlog();
        }
        else if (strcmp(requestMethod, "DELETE") == 0)
        {
            handleDeleteBlog();
        }
        else
        {
            cout << "Status: 400 Bad Request\nContent-type:text/plain\n\n";
            cout << "Unsupported request method";
        }
    }
    else
    {
        cout << "Status: 400 Bad Request\nContent-type:text/plain\n\n";
        cout << "Unable to determine request method";
    }

    return 0;
}
