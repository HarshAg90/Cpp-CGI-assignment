#include <iostream>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

using namespace std;
using namespace cgicc;

int main()
{
    // Send HTTP header with content type
    cout << HTTPHTMLHeader() << endl;

    // Create a CGI object to handle the CGI request
    Cgicc formData;

    // Start HTML document
    cout << "<html><head><title>Form Submission</title></head><body>" << endl;

    // Check if the form has been submitted
    if (formData)
    {
        // Get form elements
        form_iterator name = formData.getElement("name");
        form_iterator email = formData.getElement("email");

        // Output submitted data
        cout << "<h2>Submitted Information:</h2>" << endl;
        cout << "<p>Name: " << **name * *->getValue() << "</p>" << endl;
        cout << "<p>Email: " << **email * *->getValue() << "</p>" << endl;
    }
    else
    {
        // If the form hasn't been submitted, display the form
        cout << "<h2>Enter your information:</h2>" << endl;
        cout << "<form method=\"post\" action=\"\">" << endl;
        cout << "Name: <input type=\"text\" name=\"name\"><br>" << endl;
        cout << "Email: <input type=\"text\" name=\"email\"><br>" << endl;
        cout << "<input type=\"submit\" value=\"Submit\">" << endl;
        cout << "</form>" << endl;
    }

    // Close HTML document
    cout << "</body></html>" << endl;

    return 0;
}
