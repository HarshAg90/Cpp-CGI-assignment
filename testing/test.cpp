#include <iostream>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

// this code wont work because CGICC isnt default supported in modern C++
// and setting up CGICC is prone to more errors

using namespace std;
using namespace cgicc;

int main()
{
    cout << HTTPHTMLHeader() << endl;

    Cgicc formData;

    cout << "<html><head><title>Form Submission</title></head><body>" << endl;

    // Show Data saved
    if (formData)
    {
        form_iterator name = formData.getElement("name");
        form_iterator email = formData.getElement("email");

        cout << "<h2>Submitted Information:</h2>" << endl;
        cout << "<p>Name: " << **name * *->getValue() << "</p>" << endl;
        cout << "<p>Email: " << **email * *->getValue() << "</p>" << endl;
    }
    else
    {
        // display data
        cout << "<h2>Enter your information:</h2>" << endl;
        cout << "<form method=\"post\" action=\"\">" << endl;
        cout << "Name: <input type=\"text\" name=\"name\"><br>" << endl;
        cout << "Email: <input type=\"text\" name=\"email\"><br>" << endl;
        cout << "<input type=\"submit\" value=\"Submit\">" << endl;
        cout << "</form>" << endl;
    }
    cout << "</body></html>" << endl;

    return 0;
}
