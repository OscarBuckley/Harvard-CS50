#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int greyscale = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            greyscale = (int)round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtRed = greyscale;
            image[i][j].rgbtGreen = greyscale;
            image[i][j].rgbtBlue = greyscale;

        }

    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed = 0;
    int sepiaBlue = 0;
    int sepiaGreen = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            sepiaRed = (int)round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = (int)round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = (int)round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
            {

                image[i][j].rgbtRed = 255;

            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            if (sepiaGreen > 255)
            {

                image[i][j].rgbtGreen = 255;

            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            if (sepiaBlue > 255)
            {

                image[i][j].rgbtBlue = 255;

            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }

        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int reflectRed = 0;
    int reflectBlue = 0;
    int reflectGreen = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {

            reflectRed = image[i][j].rgbtRed;
            reflectGreen = image[i][j].rgbtGreen;
            reflectBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = reflectRed;
            image[i][width - j - 1].rgbtGreen = reflectGreen;
            image[i][width - j - 1].rgbtBlue = reflectBlue;

        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;

        }

    }



    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0;
            int sumBlue = 0;
            int sumGreen = 0;
            float pixels = 0;
            //height of 3*3 matrix (i)
            for (int k = -1; k <= 1 ; k++)
            {
                if (i + k < 0 || i + k >= height)
                {

                    continue;

                }

                //width of 3*3 matrix (j)
                for (int l = -1; l <= 1 ; l++)
                {
                    if (j + l < 0 || j + l >= width)
                    {

                        continue;

                    }

                    sumRed += copy[i + k][j + l].rgbtRed;
                    sumGreen += copy[i + k][j + l].rgbtGreen;
                    sumBlue += copy[i + k][j + l].rgbtBlue;
                    pixels++;

                }

            }

            image[i][j].rgbtRed = (int)round(sumRed / pixels);
            image[i][j].rgbtGreen = (int)round(sumGreen / pixels);
            image[i][j].rgbtBlue = (int)round(sumBlue / pixels);

        }

    }


    return;
}
