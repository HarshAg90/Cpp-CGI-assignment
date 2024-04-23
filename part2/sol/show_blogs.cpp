// show_blogs.cgi
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<html><body>";

    // Open file to read blogs
    ifstream infile("blogs.txt");
    if (!infile)
    {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    // Display all blogs
    string blog_content;
    while (getline(infile, blog_content))
    {
        cout << "<p>" << blog_content << "</p>";
    }
    infile.close();

    cout << "</body></html>";

    return 0;
}
