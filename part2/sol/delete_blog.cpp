// delete_blog.cgi
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<html><body>";

    // Read index of blog to delete from form data
    string index_str;
    getline(cin, index_str);
    int index = stoi(index_str);

    // Read all blogs into a vector
    vector<string> blogs;
    ifstream infile("blogs.txt");
    if (!infile)
    {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }
    string blog_content;
    while (getline(infile, blog_content))
    {
        blogs.push_back(blog_content);
    }
    infile.close();

    // Remove blog at the specified index
    if (index >= 0 && index < blogs.size())
    {
        blogs.erase(blogs.begin() + index);

        // Write updated blogs to file
        ofstream outfile("blogs.txt");
        if (!outfile)
        {
            cerr << "Error: Unable to open file." << endl;
            return 1;
        }
        for (const auto &blog : blogs)
        {
            outfile << blog << endl;
        }
        outfile.close();
    }

    // Redirect back to index.html
    cout << "<script>window.location.href = 'index.html';</script>";

    cout << "</body></html>";

    return 0;
}
