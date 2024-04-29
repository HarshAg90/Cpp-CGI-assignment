#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../json-develop/include/nlohmann/json.hpp"

using json = nlohmann::json;

// Structure to represent a blog entry
struct BlogEntry
{
    int id;
    std::string title;
    std::string content;
};

// Function to generate a unique ID for new blog entries
int generateId(const std::vector<BlogEntry> &blogs)
{
    int maxId = 0;
    for (const BlogEntry &blog : blogs)
    {
        maxId = std::max(maxId, blog.id);
    }
    return maxId + 1;
}

// Function to load blogs from JSON file
std::vector<BlogEntry> loadBlogs(const std::string &filename)
{
    std::vector<BlogEntry> blogs;
    std::ifstream inFile(filename);

    if (inFile.is_open())
    {
        std::string line;
        while (std::getline(inFile, line))
        {
            blogs.push_back(json::parse(line).get<BlogEntry>());
        }
        inFile.close();
    }

    return blogs;
}

// Function to save blogs to JSON file
void saveBlogs(const std::vector<BlogEntry> &blogs, const std::string &filename)
{
    std::ofstream outFile(filename);

    if (outFile.is_open())
    {
        for (const BlogEntry &blog : blogs)
        {
            outFile << json(blog) << std::endl;
        }
        outFile.close();
    }
}

// Function to handle adding a new blog entry
void addBlog(std::vector<BlogEntry> &blogs)
{
    std::string title, content;

    std::cout << "Enter blog title: ";
    std::getline(std::cin, title);

    std::cout << "Enter blog content: ";
    std::getline(std::cin, content);

    blogs.push_back({generateId(blogs), title, content});
    saveBlogs(blogs, "blogs.json");

    std::cout << "Blog added successfully!" << std::endl;
}

// Function to handle deleting a blog entry by ID
void deleteBlog(std::vector<BlogEntry> &blogs)
{
    int id;

    std::cout << "Enter ID of the blog to delete: ";
    std::cin >> id;

    std::vector<BlogEntry> filteredBlogs;
    for (const BlogEntry &blog : blogs)
    {
        if (blog.id != id)
        {
            filteredBlogs.push_back(blog);
        }
    }

    blogs = filteredBlogs;
    saveBlogs(blogs, "blogs.json");

    std::cout << "Blog deleted successfully (if it existed)." << std::endl;
}

// Function to display all blogs
void viewBlogs(const std::vector<BlogEntry> &blogs)
{
    if (blogs.empty())
    {
        std::cout << "No blogs found." << std::endl;
        return;
    }

    for (const BlogEntry &blog : blogs)
    {
        std::cout << "ID: " << blog.id << std::endl;
        std::cout << "Title: " << blog.title << std::endl;
        std::cout << "Content: " << blog.content << std::endl
                  << std::endl;
    }
}

int main()
{
    const std::string filename = "blogs.json";
    std::vector<BlogEntry> blogs = loadBlogs(filename);

    // Get action from environment variable (assuming CGI environment)
    const char *action = std::getenv("QUERY_STRING");

    if (action)
    {
        std::string actionStr(action);
        if (actionStr == "add")
        {
            addBlog(blogs);
        }
        else if (actionStr == "delete")
        {
            deleteBlog(blogs);
        }
        else
        {
            std::cerr << "Invalid action." << std::endl;
        }
    }
    else
    {
        viewBlogs(blogs);
    }

    return 0;
}