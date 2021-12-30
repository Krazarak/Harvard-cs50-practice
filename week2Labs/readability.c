# import <stdio.h>
# import <cs50.h>
# import <math.h>
# import <ctype.h>
# import <string.h>
int main(void)
{
    string text = get_string("Text: ");
    int letters = 0;
    int sentences = 0;
    int word = 0;
    // Loop through text & count variables
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // if a letter, increment letter count
        if (isalnum(text[i]))
        {
            letters++;
        }
        // if space, increment word count
        else if (isspace(text[i]))
        {
            word++;
        }
        // check for period, exclamation point or question mark, increment sentence count
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        // if next character after grammar point is empty (end of string), increment word count
            if (text[i + 1] == '\0')
            {
                word++;
            }
        }
    }
// Get grade
    float avgLetters = letters * 100.0 / word;
    float avgSentence = sentences * 100.0 / word;
int grade = round(0.0588 * avgLetters - 0.296 * avgSentence - 15.8);
// Print grade
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}