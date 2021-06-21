#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float limit(int i);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int gray;
    RGBTRIPLE *px;

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            px = &image[y][x];

            // Formula of Gray Scale (Average Method)
            gray = round((px->rgbtRed + px->rgbtGreen + px->rgbtBlue) / 3.000);

            px->rgbtRed = gray;
            px->rgbtGreen = gray;
            px->rgbtBlue = gray;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE *px;

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            px = &image[y][x];
            float red   = px->rgbtRed;
            float green = px->rgbtGreen;
            float blue  = px->rgbtBlue;

            // Formula of finding Sepia value
            px->rgbtRed   = limit(round(0.393 * red + 0.769 * green + 0.189 * blue));
            px->rgbtGreen = limit(round(0.349 * red + 0.686 * green + 0.168 * blue));
            px->rgbtBlue  = limit(round(0.272 * red + 0.534 * green + 0.131 * blue));
        }
    }

    return;
}

// If the value is out of range, I will set maxmium value 255.
float limit(int i)
{

    if (i > 255)
    {
        return 255;
    }

    return i;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    int mid = width / 2;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < mid; x++)
        {
            // Swap with left side of pixel with right size of pixel
            temp = image[y][x];
            image[y][x] = image[y][width - x - 1];
            image[y][width - x - 1] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float count;                    // For average value pixel
    int blurRed;                    // For total value of Red within 3x3 box
    int blurGreen;                  // For total value of Green within 3x3 box
    int blurBlue;                   // For total value of Blue within 3x3 box
    RGBTRIPLE temp[height][width];  // Temporary store for Image

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

            blurRed = 0;
            blurGreen = 0;
            blurBlue = 0;
            count = 0.00;

            for (int y2 = -1; y2 < 2; y2++)
            {
                // Inn loop for 3x3 blur-box
                if (y + y2 < 0 || y + y2 > height - 1)
                {
                    // If the inner height is exceed 3x3 box, ignore it.
                    continue;
                }

                for (int x2 = -1; x2 < 2; x2++)
                {
                    if (x + x2 < 0 || x + x2 > width - 1)
                    {
                        // If the inner width is exceed 3x3 box, ignore it.
                        continue;
                    }

                    // Sum RBG values of the pixel.
                    blurRed   += image[y + y2][x + x2].rgbtRed;
                    blurGreen += image[y + y2][x + x2].rgbtGreen;
                    blurBlue  += image[y + y2][x + x2].rgbtBlue;
                    count ++;
                }
            }

            // Blur image will be stored as tempoary.
            // So, the original image will note be affected.

            temp[y][x].rgbtRed   = round(blurRed / count);
            temp[y][x].rgbtGreen = round(blurGreen / count);
            temp[y][x].rgbtBlue  = round(blurBlue / count);
        }
    }

    // Replace all image value from temp[] array
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image[y][x] = temp[y][x];
        }
    }

    return;
}
