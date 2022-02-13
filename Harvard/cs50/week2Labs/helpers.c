#include "helpers.h"
#include <math.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Grayscale each pixel by applying same color value based on the average of the colors
            int grayScale = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = grayScale;
            image[i][j].rgbtGreen = grayScale;
            image[i][j].rgbtBlue = grayScale;
        }
    }
    return;
}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each row and half of the width
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Temporarily store the reflected pixel of the current pixel on the right side of the image
            // Then swap pixel locations to reflect the image
            RGBTRIPLE tmpReplace = image[i][width - 1 - j];
            image[i][width - 1 - j] = image[i][j];
            image[i][j] = tmpReplace;
        }
    }
    return;
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];
    double red, green, blue;
    int count = 0;
    int BOX = 1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Reset average color values for current pixel
            red = 0;
            green = 0;
            blue = 0;
            count = 0;
// Loop through a 3x3 box surrounding current pixel by looping from the upper left corner to the bottom right corner
            for (int row = i - BOX; row <= i + BOX; row++)
            {
                for (int col = j - BOX; col <= j + BOX; col++)
                {
                    if ((row >= 0 && row < height) && (col >= 0 && col < width))
                    {
                        // Update average count and add the color values to the existing averages
                        blue += image[row][col].rgbtBlue;
                        green += image[row][col].rgbtGreen;
                        red += image[row][col].rgbtRed;
                        count++;
                    }
                }
            }
// Calculate average color values and assign to temp image
            blue =  round(blue / (double) count);
            green = round(green / (double)  count);
            red = round(red / (double) count);
            tmp_image[i][j].rgbtBlue = blue;
            tmp_image[i][j].rgbtGreen = green;
            tmp_image[i][j].rgbtRed = red;
        }
    }
// Loop through each pixel and replace original image with modified temp image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp_image[i][j];
        }
    }
    return;
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int BOX = 1;
// Loop through each pixel and copy original image to modified temp image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp_image[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Reset xy color values for current pixel
            float redx = 0,  greenx = 0, bluex = 0, redy = 0, greeny = 0, bluey = 0;
// Loop through a 3x3 box surrounding current pixel by looping from the upper left corner to the bottom right corner
            for (int row = -1; row < 2; row++)
            {
                for (int col = -1; col < 2; col++)
                {
                    // Check for extra cases and continue loop
                    if (i + row < 0 || i + row >= height || j + col < 0 || j + col >= width)
                    {
                        continue;
                    }
                    // multiply image values to weighted sums
                    redx   += tmp_image[i + row][j + col].rgbtRed   * Gx[row + 1][col + 1];
                    greenx += tmp_image[i + row][j + col].rgbtGreen * Gx[row + 1][col + 1];
                    bluex  += tmp_image[i + row][j + col].rgbtBlue  * Gx[row + 1][col + 1];
                    redy   += tmp_image[i + row][j + col].rgbtRed   * Gy[row + 1][col + 1];
                    greeny += tmp_image[i + row][j + col].rgbtGreen * Gy[row + 1][col + 1];
                    bluey  += tmp_image[i + row][j + col].rgbtBlue  * Gy[row + 1][col + 1];
                }
            }
// Update current pixel values to edge after rounding
            int combineRed = round(sqrt((redx * redx) + (redy * redy)));
            int combineGreen = round(sqrt((greenx * greenx) + (greeny * greeny)));
            int combineBlue = round(sqrt((bluex * bluex) + (bluey * bluey)));
// Cap values at 255
            if (combineRed > 255)
            {
                combineRed = 255;
            }
            if (combineGreen > 255)
            {
                combineGreen = 255;
            }
            if (combineBlue > 255)
            {
                combineBlue = 255;
            }
            image[i][j].rgbtRed = combineRed;
            image[i][j].rgbtGreen = combineGreen;
            image[i][j].rgbtBlue = combineBlue;
        }
    }
    return;
}