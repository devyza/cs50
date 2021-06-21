#include "helpers.h"
#include <math.h>

float limit(float i);

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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    for (int x = 0; x < width / 2; x++)
    {
        for (int y = 0; y < height; y++)
        {
            // Swap with left side of pixel with right size of pixel
            temp = image[y][x];
            image[y][x] = image[y][width-x-1];
            image[y][width-x-1] = temp;
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

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {

            blurRed = 0;
            blurGreen = 0;
            blurBlue = 0;
            count = 0.00;

            for (int x2 = -1; x2 < 2; x2++)
            {
                // If the inner width is exceed 3x3 box, ignore it.
                if (x + x2 < 0 || x + x2 > width - 1)
                {
                    continue;
                }

                for (int y2 = - 1; y2 < 2; y2++)
                {
                    // If the inner height is exceed 3x3 box, ignore it.
                    if (y + y2 < 0 || y + y2 > height - 1)
                    {
                        continue;
                    }

                    blurRed   += image[y + y2][x + x2].rgbtRed;
                    blurGreen += image[y + y2][x + x2].rgbtGreen;
                    blurBlue  += image[y + y2][x + x2].rgbtBlue;
                    count++;

                }
            }

            // Blur image will be stored as tempoary.
            // So, the original image will note be affected.
            temp[y][x].rgbtRed   = round(blurRed / count);
            temp[y][x].rgbtGreen = round(blurGreen / count);
            temp[y][x].rgbtBlue  = round(blurBlue / count);
        }
    }

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            image[y][x].rgbtRed   = temp[y][x].rgbtRed;
            image[y][x].rgbtGreen = temp[y][x].rgbtGreen;
            image[y][x].rgbtBlue  = temp[y][x].rgbtBlue;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    float redX, blueX, greenX;
    float redY, blueY, greenY;

    // Robinson's Compass Mask - North
    float Gx[3][3] =  { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };

    // Robinson's Compass Mask - East
    float Gy[3][3] =  { {-1, -2, -1}, { 0,  0,  0}, { 1,  2,  1} };


    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            redX = 0.0;
            greenX = 0.0;
            blueX = 0.0;

            redY = 0.0;
            greenY = 0.0;
            blueY = 0.0;


            for (int x2 = -1; x2 < 2; x2++)
            {
                // If the inner width is exceed 3x3 Kernal box, ignore it.
                if (x + x2 < 0 || x + x2 > width - 1)
                {
                    continue;
                }

                for (int y2 = -1; y2 < 2; y2++)
                {

                    // If the inner height is exceed 3x3 Kernal box, ignore it.
                    if (y + y2 < 0 || y + y2 > height - 1)
                    {
                        continue;
                    }

                    redX   += image[y + y2][x + x2].rgbtRed   * Gx[y2 + 1][x2 + 1];
                    greenX += image[y + y2][x + x2].rgbtGreen * Gx[y2 + 1][x2 + 1];
                    blueX  += image[y + y2][x + x2].rgbtBlue  * Gx[y2 + 1][x2 + 1];

                    redY   += image[y + y2][x + x2].rgbtRed   * Gy[y2 + 1][x2 + 1];
                    greenY += image[y + y2][x + x2].rgbtGreen * Gy[y2 + 1][x2 + 1];
                    blueY  += image[y + y2][x + x2].rgbtBlue  * Gy[y2 + 1][x2 + 1];

                }
            }

            // Sobel Operator (the square root of Gx^2 + Gy^2)
            // Pixel will be stored in temporary array by not affecting the original image
            temp[y][x].rgbtRed   = limit(round(sqrt(redX * redX + redY * redY)));
            temp[y][x].rgbtGreen = limit(round(sqrt(greenX * greenX + greenY * greenY)));
            temp[y][x].rgbtBlue  = limit(round(sqrt(blueX * blueX + blueY * blueY)));

        }
    }


    // Replace all pixels from temporary array
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            image[y][x] = temp[y][x];
        }
    }

    return;
}

// If the value is out of range, I will set maxmium value 255.
float limit(float i)
{
    if (i > 255)
    {
        return 255;
    }

    return i;
}
