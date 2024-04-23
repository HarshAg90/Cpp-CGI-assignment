// add_blog.cgi
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int main()
{
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<html><body>";

    // Read blog content from form data
    string blog_content;
    getline(cin, blog_content);

    // Open file to append new blog
    ofstream outfile("blogs.txt", ios::app);
    if (!outfile)
    {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    // Write blog content to file
    outfile << blog_content << endl;
    outfile.close();

    // Redirect back to index.html
    cout << "<script>window.location.href = 'index.html';</script>";

    cout << "</body></html>";

    return 0;
}
