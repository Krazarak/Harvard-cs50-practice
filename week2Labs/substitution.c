#import <stdio.h>
#import <cs50.h>
#import <ctype.h>
#import <string.h>
int main(int argc, string argv[])
{
    const int ALPHABET_LEN = 26;
    const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // Check for error - if none or more than 1 command-line argument is passed in
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Check validity (26 char, not alphabetical, & not containing a letter once)
    int argLength = strlen(argv[1]);
    // Check if key is 26 characters
    if (argLength != ALPHABET_LEN)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int x = 0, len = strlen(argv[1]); x < len; x++)
    {
        // Check if character is alphabetical
        if (!isalpha(argv[1][x]))
        {
            printf("Key must be alphabetical.\n");
            return 1;
        }
        // Check if each letter is only used once
        int letters[ALPHABET_LEN];
        for (int j = 0; j < ALPHABET_LEN; j++)
        {
            // Loops through current letters and returns error if repeated match is found
            if (argv[1][x] == letters[j])
            {
                printf("Key must contain each letter exactly once.\n");
                return 1;
            }
        }
        // Stores character for next loop to check for match
        letters[x] = argv[1][x];
    }
    string plaintext = get_string("plaintext: ");
    char ciphertext[strlen(plaintext) + 1];
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        // if uppercase...
        if (isupper(plaintext[i]))
        {
            // loop through alphabet to find matching character
            for (int j = 0; j < ALPHABET_LEN; j++)
            {
                if (plaintext[i] == ALPHABET[j])
                {
                    ciphertext[i] = toupper(argv[1][j]);
                    break;
                }
            }
        }
        // if lowercase ...
        else if (islower(plaintext[i]))
        {
            // loop through lowercase alphabet to find matching character
            for (int j = 0; j < ALPHABET_LEN; j++)
            {
                if (plaintext[i] == tolower(ALPHABET[j]))
                {
                    ciphertext[i] = tolower(argv[1][j]);
                    break;
                }
            }
        }
        // if non-letter character, print as plain text
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    // turn char into string
    ciphertext[strlen(plaintext)] = '\0';
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}