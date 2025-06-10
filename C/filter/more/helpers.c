#include "helpers.h"
#include <math.h>
#include <stdio.h>

void calculate_sobel_operator(RGBTRIPLE pixel, int *SumRed, int *SumGreen, int *SumBlue,
                              int operator);

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Sobel–Feldman kernel
    int gxKernel[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1},
    };

    int gyKernel[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1},
    };

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
            int gxSumRed = 0, gySumRed = 0, gxSumGreen = 0, gySumGreen = 0, gxSumBlue = 0,
                gySumBlue = 0;
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    if (k >= 0 && k < height && l >= 0 && l < width)
                    {
                        RGBTRIPLE *pixel = &originalImage[k][l];

                        // Calculate new pixel position relative to the old one
                        int xRelativePosition = i - k + 1;
                        int yRelativePosition = j - l + 1;

                        // Get weight based on position
                        int gxWeight = gxKernel[xRelativePosition][yRelativePosition];
                        int gyWeight = gyKernel[xRelativePosition][yRelativePosition];

                        calculate_sobel_operator(*pixel, &gxSumRed, &gxSumGreen, &gxSumBlue,
                                                 gxWeight);
                        calculate_sobel_operator(*pixel, &gySumRed, &gySumGreen, &gySumBlue,
                                                 gyWeight);
                    }
                }
            }

            // Calculate pixel - sqrt of Gx^2 + Gy^2
            int red = round(sqrt(pow(gxSumRed, 2) + pow(gySumRed, 2)));
            int green = round(sqrt(pow(gxSumGreen, 2) + pow(gySumGreen, 2)));
            int blue = round(sqrt(pow(gxSumBlue, 2) + pow(gySumBlue, 2)));

            // Update pixel
            image[i][j].rgbtRed = red < 255 ? red : 255;
            image[i][j].rgbtGreen = green < 255 ? green : 255;
            image[i][j].rgbtBlue = blue < 255 ? blue : 255;
        }
    }
    return;
}

// Apply Sober weights
void calculate_sobel_operator(RGBTRIPLE pixel, int *SumRed, int *SumGreen, int *SumBlue,
                              int operator)
{
    *SumRed += operator * pixel.rgbtRed;
    *SumGreen += operator * pixel.rgbtGreen;
    *SumBlue += operator * pixel.rgbtBlue;
}
