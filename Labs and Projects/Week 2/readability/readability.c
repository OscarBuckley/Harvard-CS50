u#include <cs50.h>
#include <stdio.h>
#include <math.h>

int count_letters(string text)
{

    int letterlength = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {

        //if character is upper of lower case alphabet cound as letter
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            letterlength ++;
        }

    }

    return letterlength;

}

int count_words(string text)
{

    int wordlength = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {

        //if character is space cound as word
        if (text[i] == ' ')
        {
            wordlength ++;
        }

    }

    //add 1 for final word
    return wordlength + 1;

}

int count_sentences(string text)
{

    int sentencelength = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {

        //if character is . ! or ? cound as sentence
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentencelength ++;
        }

    }

    return sentencelength;

}

int main(void)
{

    string text = get_string("Write sample text here:\n");

    //get lengths
    int letterlength = count_letters(text);
    int wordlength = count_words(text);
    int sentencelength = count_sentences(text);

    //calculate index
    float L = (float) letterlength / (float) wordlength * 100;
    float S = (float) sentencelength / (float) wordlength * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;


    //format output
    if (index >= 16)
    {

        printf("Grade 16+\n");

    }
    else if (index < 1)
    {

        printf("Before Grade 1\n");

    }
    else
    {

        int grade = round(index);
        printf("Grade %d\n", grade);

    }
}