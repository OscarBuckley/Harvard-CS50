#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{

    //no of arguments check
    if (argc != 2)
    {

        printf("Enter only 1 argument\n");
        return 1;

    }

    string key = argv[1];
    int length = strlen(key);

    //numerical character check
    for (int i = 0; i < length; i++)
    {

        if (!(key[i] >= 48 && key[i] <= 57))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

    }

    //convert key to string
    int keyint = atoi(key);
    if (keyint > 26)
    {
        keyint = keyint % 26;
    }

    //enter plain text
    string plaintext = get_string("Enter Plain Text:");
    string ciphertext = plaintext;

    //cipher conversion
    for (int i = 0; ciphertext[i] != '\0'; i++)
    {

        //lower case cipher
        if (ciphertext[i] >= 97 && ciphertext[i] <= 122)
        {

            ciphertext[i] += keyint - 26;

            if (ciphertext[i] <= 96)
            {

                ciphertext[i] += 26;

            }

        }

        //upper case cipher
        if (ciphertext[i] >= 65 && ciphertext[i] <= 90)
        {

            ciphertext[i] += keyint - 26;

            if (ciphertext[i] <= 64)
            {

                ciphertext[i] += 26;

            }

        }

    }

    //output
    printf("plaintext: %s\n", plaintext);
    printf("ciphertext: %s\n", ciphertext);
    return 0;

}