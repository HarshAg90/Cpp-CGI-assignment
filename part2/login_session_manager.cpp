#include <iostream>
#include <string>
#include <unordered_map>
#include <cgicc/Cgicc.h>

using namespace std;
using namespace cgicc;

class SessionManager
{
private:
    unordered_map<string, string> userSessions;
    const int sessionTimeout = 3600;

public:
    string createSession(const string &username)
    {
        string sessionToken = generateSessionToken();
        userSessions[sessionToken] = username;
        return sessionToken;
    }

    bool isValidSession(const string &sessionToken)
    {
        return userSessions.find(sessionToken) != userSessions.end();
    }

    void removeSession(const string &sessionToken)
    {
        userSessions.erase(sessionToken);
    }

private:
    string generateSessionToken()
    {
        return "SESSION_TOKEN";
    }
};

class User
{
private:
    string username;
    string password;

public:
    User(const string &_username, const string &_password) : username(_username), password(_password) {}

    bool authenticate(const string &_password) const
    {
        return password == _password;
    }

    const string &getUsername() const
    {
        return username;
    }
};

class UserManager
{
private:
    unordered_map<string, User> users;

public:
    void addUser(const string &username, const string &password)
    {
        users[username] = User(username, password);
    }

    User *getUser(const string &username)
    {
        auto it = users.find(username);
        if (it != users.end())
        {
            return &it->second;
        }
        return nullptr;
    }
};

int main()
{
    UserManager userManager;
    SessionManager sessionManager;

    Cgicc cgi;
    userManager.addUser("user1", "password1");
    userManager.addUser("user2", "password2");

    form_iterator usernameIter = cgi.getElement("username");
    form_iterator passwordIter = cgi.getElement("password");

    if (usernameIter != cgi.getElements().end() && passwordIter != cgi.getElements().end())
    {
        string username = **usernameIter;
        string password = **passwordIter;

        User *user = userManager.getUser(username);
        if (user && user->authenticate(password))
        {
            string sessionToken = sessionManager.createSession(username);
            cout << "Content-type:text/html\r\n\r\n";
            cout << "<html><body>";
            cout << "Login successful. Session token: " << sessionToken << "<br>";
            cout << "</body></html>";
        }
        else
        {
            cout << "Content-type:text/html\r\n\r\n";
            cout << "<html><body>";
            cout << "Invalid username or password.<br>";
            cout << "</body></html>";
        }
    }
    else
    {
        cout << "Content-type:text/html\r\n\r\n";
        cout << "<html><body>";
        cout << "Username or password not provided.<br>";
        cout << "</body></html>";
    }

    return 0;
}
