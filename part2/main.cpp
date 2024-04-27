#include <iostream>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

using namespace std;
using namespace cgicc;

int main()
{
    // Send HTTP header
    cout << HTTPHTMLHeader() << endl;

    // Start HTML
    cout << html() << head(title("Simple Blog")) << endl;
    cout << body() << endl;

    // Main content
    cout << "<h1>Welcome to My Simple Blog</h1>" << endl;

    // Check for submitted form data
    Cgicc formData;
    form_iterator title = formData.getElement("title");
    form_iterator content = formData.getElement("content");

    if (title != formData.getElements().end() &&
        content != formData.getElements().end())
    {
        // Display submitted blog post
        cout << "<h2>" << **title << "</h2>" << endl;
        cout << "<p>" << **content << "</p>" << endl;
    }

    // Blog post form
    cout << "<form method=\"post\" action=\"blog.cgi\">" << endl;
    cout << "Title: <input type=\"text\" name=\"title\"><br>" << endl;
    cout << "Content: <br><textarea name=\"content\" rows=\"4\" cols=\"50\"></textarea><br>" << endl;
    cout << "<input type=\"submit\" value=\"Submit\">" << endl;
    cout << "</form>" << endl;

    // End HTML
    cout << body() << html();

    return 0;
}
