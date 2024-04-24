#include <iostream>
#include <fstream>
#include <vector>
#include <httplib.h>

using namespace std;
using namespace httplib;

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

void handleAddBlog(const Request &req, Response &res)
{
    if (req.has_param("title") && req.has_param("content"))
    {
        string title = req.get_param_value("title");
        string content = req.get_param_value("content");
        int index = blogs.empty() ? 1 : blogs.back().index + 1;
        blogs.push_back({index, title, content});
        saveBlogsToFile();
        res.set_content("Blog added successfully.", "text/plain");
    }
    else
    {
        res.set_content("Error: Missing 'title' or 'content' parameter.", "text/plain");
    }
}

void handleShowBlog(const Request &req, Response &res)
{
    string content;
    for (const auto &blog : blogs)
    {
        content += "Index: " + to_string(blog.index) + "\nTitle: " + blog.title + "\nContent: " + blog.content + "\n\n";
    }
    res.set_content(content, "text/plain");
}

void handleDeleteBlog(const Request &req, Response &res)
{
    if (req.has_param("index"))
    {
        int index = stoi(req.get_param_value("index"));
        auto it = find_if(blogs.begin(), blogs.end(), [index](const Blog &blog)
                          { return blog.index == index; });
        if (it != blogs.end())
        {
            blogs.erase(it);
            saveBlogsToFile();
            res.set_content("Blog deleted successfully.", "text/plain");
        }
        else
        {
            res.set_content("Error: Blog with specified index not found.", "text/plain");
        }
    }
    else
    {
        res.set_content("Error: Missing 'index' parameter.", "text/plain");
    }
}

int main()
{
    loadBlogsFromFile();

    Server server;

    server.Post("/addBlog", [](const Request &req, Response &res)
                { handleAddBlog(req, res); });

    server.Get("/showBlog", [](const Request &req, Response &res)
               { handleShowBlog(req, res); });

    server.Delete("/deleteBlog", [](const Request &req, Response &res)
                  { handleDeleteBlog(req, res); });

    cout << "Server started at http://localhost:8080" << endl;

    server.listen("localhost", 8080);

    return 0;
}
