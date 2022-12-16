#include <cs50.h>
#include <stdio.h>

int main(void)
{

    int height = 0;

//scan input
    do
    {

        printf("Height: ");
        scanf(" %d", &height);

    }
    while (height > 8 || height < 1);

    int i = 1;

//building pyramid
    for (i = 1; i <= height; i++)
    {

        //tabbing
        for (int g = i; g <= height - 1; g++)
        {

            printf(" ");

        }

        //left side
        for (int j = 0; j < i; j++)
        {

            printf("#");

        }
        //print space
        printf("  ");

        //right side
        for (int k = 0; k < i; k++)
        {

            printf("#");

        }

        printf("\n");

    }
}
