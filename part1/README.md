# Security flaws in provided code

1. **Buffer Overflow Vulnerability:**
    - In several places, you're using fixed-size character arrays (username, password, new_username, new_password, filename, blog_name) without bounds checking. This can lead to buffer overflow if the input exceeds the allocated space.
    
        For example, in main(), scanf("%s", username) doesn't ensure that the input won't exceed the size of username[12].
1. **Insecure File Handling:**
    - The code deals with file names directly based on user input without proper validation. This can lead to directory traversal attacks or overwriting unintended files. For example, in view_blog() and update_blog(), you concatenate user input with ".txt" to create file names (blog_name and filename).
1. **Insecure Password Handling:**
    - Passwords are stored in plaintext in the pwds.txt file. Storing passwords in plaintext is highly insecure and can lead to compromise if the file is accessed by unauthorized users.

    - Additionally, the encryption and decryption methods (encrypt() and decrypt()) are very weak. Simple addition/subtraction is not sufficient for secure encryption. A stronger encryption algorithm like AES should be used.
    - There's also no salt used in password hashing, which makes it vulnerable to dictionary attacks and rainbow table attacks.
1. **Improper Input Validation:**
    - The code doesn't properly validate user inputs. For example, in get_menu_choice(), there's no check for non-integer inputs. Invalid inputs can lead to undefined behavior or unexpected program termination.
1. **No Input Sanitization:**
    - User inputs are directly used in functions like scanf() and printf(), leaving the program vulnerable to format string vulnerabilities or injection attacks.
1. **Lack of Proper Authentication:**
    - The authentication mechanism is rudimentary and doesn't provide strong security. It's merely based on comparing plaintext passwords stored in a file.
1. **Lack of Error Handling:**
    - The code lacks proper error handling for file operations (fopen(), fclose(), etc.). Failure to open or close files is not properly handled, which can lead to resource leaks or unexpected behavior.
1. **Insecure Data Storage:**
    - User ratings are stored in a plaintext file (ratings.txt) without any form of access control or encryption.

## Code Explanations for the Flaws

```C
// Vulnerable code snippet demonstrating buffer overflow
void view_blog(char *blog_name)
{
    // Potential buffer overflow vulnerability
    strcat(blog_name, ".txt");

    FILE *fp = fopen(blog_name, "r");
    char *line = NULL;
    size_t len = 0;

    getline(&line, &len, fp);  // If blog_name length exceeds 12 characters, buffer overflow can occur
    fclose(fp);

    printf("%s", line);
}

```