#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through every pixel
    float buffer;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *pixel = &image[i][j];

            // Calculate the average
            buffer = (pixel->rgbtRed + pixel->rgbtGreen + pixel->rgbtBlue) / 3.0;
            buffer = round(buffer);

            // Update pixel
            pixel->rgbtRed = buffer;
            pixel->rgbtGreen = buffer;
            pixel->rgbtBlue = buffer;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through every pixel
    float sepiaRed, sepiaGreen, sepiaBlue;
    RGBTRIPLE *pixel;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            pixel = &image[i][j];

            // Calculate the sepia
            sepiaRed = .393 * pixel->rgbtRed + .769 * pixel->rgbtGreen + .189 * pixel->rgbtBlue;
            sepiaGreen = .349 * pixel->rgbtRed + .686 * pixel->rgbtGreen + .168 * pixel->rgbtBlue;
            sepiaBlue = .272 * pixel->rgbtRed + .534 * pixel->rgbtGreen + .131 * pixel->rgbtBlue;

            // Update pixel
            pixel->rgbtRed = sepiaRed < 255 ? round(sepiaRed) : 255;
            pixel->rgbtGreen = sepiaGreen < 255 ? round(sepiaGreen) : 255;
            pixel->rgbtBlue = sepiaBlue < 255 ? round(sepiaBlue) : 255;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer;

    // Loop through every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {

            // Store the pixel and its reverse;
            int newPosition = width - j - 1;
            RGBTRIPLE *pixel = &image[i][j];
            RGBTRIPLE *reversedPixel = &image[i][newPosition];

            // Store buffer
            buffer = *pixel;

            // Update pixel
            pixel->rgbtRed = reversedPixel->rgbtRed;
            pixel->rgbtGreen = reversedPixel->rgbtGreen;
            pixel->rgbtBlue = reversedPixel->rgbtBlue;

            // Update reverse pixel
            reversedPixel->rgbtRed = buffer.rgbtRed;
            reversedPixel->rgbtGreen = buffer.rgbtGreen;
            reversedPixel->rgbtBlue = buffer.rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the original image
    RGBTRIPLE originalImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalImage[i][j] = image[i][j];
        }
    }

    // Loop through every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Loop around the pixel
            int sumPixels = 0, sumRed = 0, sumGreen = 0, sumBlue = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {
                        // Store the value of the pixels
                        sumRed += originalImage[k][l].rgbtRed;
                        sumGreen += originalImage[k][l].rgbtGreen;
                        sumBlue += originalImage[k][l].rgbtBlue;

                        sumPixels++;
                    }
                }
            }

            // Update pixel
            image[i][j].rgbtRed = round(sumRed / (float) sumPixels);
            image[i][j].rgbtGreen = round(sumGreen / (float) sumPixels);
            image[i][j].rgbtBlue = round(sumBlue / (float) sumPixels);
        }
    }
    return;
}
