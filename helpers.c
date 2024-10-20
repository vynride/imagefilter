#include "helpers.h"
#include <math.h>

void less_than_255(int *pixel_value);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calc. general brightness or darkness for the pixel and round it to nearest int
            float temp_brightness =
                (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            int general_brightness = round(temp_brightness);

            // Assign brightness value to RGB values of pixel
            image[i][j].rgbtRed = general_brightness;
            image[i][j].rgbtGreen = general_brightness;
            image[i][j].rgbtBlue = general_brightness;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, half_width = width / 2; j < half_width; j++)
        {
            int temp_red = image[i][j].rgbtRed;
            int temp_green = image[i][j].rgbtGreen;
            int temp_blue = image[i][j].rgbtBlue;
            int pixel_index = width - (j + 1);

            image[i][j].rgbtRed = image[i][pixel_index].rgbtRed;
            image[i][j].rgbtGreen = image[i][pixel_index].rgbtGreen;
            image[i][j].rgbtBlue = image[i][pixel_index].rgbtBlue;

            image[i][pixel_index].rgbtRed = temp_red;
            image[i][pixel_index].rgbtGreen = temp_green;
            image[i][pixel_index].rgbtBlue = temp_blue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a duplicate image to retrive RGB values of original image
    RGBTRIPLE duplicate[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            duplicate[i][j] = image[i][j];
        }
    }

    // Set maximum value that [i] and [j] can take as we start counting from 0

    // Index of bottom row
    int height_max = height - 1;
    // Index of rightmost column
    int width_max = width - 1;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Keep count of RGB values and number of pixels for calculations
            int red_sum = 0, green_sum = 0, blue_sum = 0;
            int pixel_count = 0;

            // Pixel is in the top row of the image
            if (i == 0)
            {
                // Pixel is in the leftmost column
                if (j == 0)
                {
                    // Pixel directly below
                    red_sum += duplicate[1][0].rgbtRed;
                    green_sum += duplicate[1][0].rgbtGreen;
                    blue_sum += duplicate[1][0].rgbtBlue;

                    // Pixel along right diagonal downwards
                    red_sum += duplicate[1][1].rgbtRed;
                    green_sum += duplicate[1][1].rgbtGreen;
                    blue_sum += duplicate[1][1].rgbtBlue;

                    // Pixel to the right
                    red_sum += duplicate[0][1].rgbtRed;
                    green_sum += duplicate[0][1].rgbtGreen;
                    blue_sum += duplicate[0][1].rgbtBlue;

                    pixel_count += 3;
                }

                // Pixel is in the rightmost column
                else if (j == width_max)
                {
                    // Pixel directly below
                    red_sum += duplicate[1][width_max].rgbtRed;
                    green_sum += duplicate[1][width_max].rgbtGreen;
                    blue_sum += duplicate[1][width_max].rgbtBlue;

                    // Pixel along left diagonal downwards
                    red_sum += duplicate[1][width_max - 1].rgbtRed;
                    green_sum += duplicate[1][width_max - 1].rgbtGreen;
                    blue_sum += duplicate[1][width_max - 1].rgbtBlue;

                    // Pixel to the left
                    red_sum += duplicate[0][width_max - 1].rgbtRed;
                    green_sum += duplicate[0][width_max - 1].rgbtGreen;
                    blue_sum += duplicate[0][width_max - 1].rgbtBlue;

                    pixel_count += 3;
                }

                // Pixel is somewhere between leftmost and rightmost columns
                else
                {
                    // Pixel to left
                    red_sum += duplicate[0][j - 1].rgbtRed;
                    green_sum += duplicate[0][j - 1].rgbtGreen;
                    blue_sum += duplicate[0][j - 1].rgbtBlue;

                    // Pixel along left diagonal downwards
                    red_sum += duplicate[1][j - 1].rgbtRed;
                    green_sum += duplicate[1][j - 1].rgbtGreen;
                    blue_sum += duplicate[1][j - 1].rgbtBlue;

                    // Pixel directly downwards
                    red_sum += duplicate[1][j].rgbtRed;
                    green_sum += duplicate[1][j].rgbtGreen;
                    blue_sum += duplicate[1][j].rgbtBlue;

                    // Pixel to the right diagonal downwards
                    red_sum += duplicate[1][j + 1].rgbtRed;
                    green_sum += duplicate[1][j + 1].rgbtGreen;
                    blue_sum += duplicate[1][j + 1].rgbtBlue;

                    // Pixel to the right
                    red_sum += duplicate[0][j + 1].rgbtRed;
                    green_sum += duplicate[0][j + 1].rgbtGreen;
                    blue_sum += duplicate[0][j + 1].rgbtBlue;

                    pixel_count += 5;
                }
            }

            // Pixel is in the bottom row of the image
            else if (i == height_max)
            {
                // Pixel is in the leftmost column
                if (j == 0)
                {
                    // Pixel directly above
                    red_sum += duplicate[height_max - 1][0].rgbtRed;
                    green_sum += duplicate[height_max - 1][0].rgbtGreen;
                    blue_sum += duplicate[height_max - 1][0].rgbtBlue;

                    // Pixel along right diagonal upwards
                    red_sum += duplicate[height_max - 1][1].rgbtRed;
                    green_sum += duplicate[height_max - 1][1].rgbtGreen;
                    blue_sum += duplicate[height_max - 1][1].rgbtBlue;

                    // Pixel to the right
                    red_sum += duplicate[height_max][1].rgbtRed;
                    green_sum += duplicate[height_max][1].rgbtGreen;
                    blue_sum += duplicate[height_max][1].rgbtBlue;

                    pixel_count += 3;
                }

                // Pixel is in the rightmost column
                else if (j == width_max)
                {
                    // Pixel directly above
                    red_sum += duplicate[height_max - 1][width_max].rgbtRed;
                    green_sum += duplicate[height_max - 1][width_max].rgbtGreen;
                    blue_sum += duplicate[height_max - 1][width_max].rgbtBlue;

                    // Pixel along left diagonal upwards
                    red_sum += duplicate[height_max - 1][width_max - 1].rgbtRed;
                    green_sum += duplicate[height_max - 1][width_max - 1].rgbtGreen;
                    blue_sum += duplicate[height_max - 1][width_max - 1].rgbtBlue;

                    // Pixel to the left
                    red_sum += duplicate[height_max][width_max - 1].rgbtRed;
                    green_sum += duplicate[height_max][width_max - 1].rgbtGreen;
                    blue_sum += duplicate[height_max][width_max - 1].rgbtBlue;

                    pixel_count += 3;
                }

                // Pixel is somewhere between leftmost and rightmost columns
                else
                {
                    // Pixel to left
                    red_sum += duplicate[height_max][j - 1].rgbtRed;
                    green_sum += duplicate[height_max][j - 1].rgbtGreen;
                    blue_sum += duplicate[height_max][j - 1].rgbtBlue;

                    // Pixel along left diagonal upwards
                    red_sum += duplicate[height_max - 1][j - 1].rgbtRed;
                    green_sum += duplicate[height_max - 1][j - 1].rgbtGreen;
                    blue_sum += duplicate[height_max - 1][j - 1].rgbtBlue;

                    // Pixel directly upwards
                    red_sum += duplicate[height_max - 1][j].rgbtRed;
                    green_sum += duplicate[height_max - 1][j].rgbtGreen;
                    blue_sum += duplicate[height_max - 1][j].rgbtBlue;

                    // Pixel to the right diagonal upwards
                    red_sum += duplicate[height_max - 1][j + 1].rgbtRed;
                    green_sum += duplicate[height_max - 1][j + 1].rgbtGreen;
                    blue_sum += duplicate[height_max - 1][j + 1].rgbtBlue;

                    // Pixel to the right
                    red_sum += duplicate[height_max][j + 1].rgbtRed;
                    green_sum += duplicate[height_max][j + 1].rgbtGreen;
                    blue_sum += duplicate[height_max][j + 1].rgbtBlue;

                    pixel_count += 5;
                }
            }

            // Pixel is somewhere between top and bottom rows
            else
            {
                // Pixel is in the leftmost column
                if (j == 0)
                {
                    // Pixel directly above
                    red_sum += duplicate[i - 1][0].rgbtRed;
                    green_sum += duplicate[i - 1][0].rgbtGreen;
                    blue_sum += duplicate[i - 1][0].rgbtBlue;

                    // Pixel along right diagonal upwards
                    red_sum += duplicate[i - 1][1].rgbtRed;
                    green_sum += duplicate[i - 1][1].rgbtGreen;
                    blue_sum += duplicate[i - 1][1].rgbtBlue;

                    // Pixel to the right
                    red_sum += duplicate[i][1].rgbtRed;
                    green_sum += duplicate[i][1].rgbtGreen;
                    blue_sum += duplicate[i][1].rgbtBlue;

                    // Pixel along right diagonal downwards
                    red_sum += duplicate[i + 1][1].rgbtRed;
                    green_sum += duplicate[i + 1][1].rgbtGreen;
                    blue_sum += duplicate[i + 1][1].rgbtBlue;

                    // Pixel directly below
                    red_sum += duplicate[i + 1][0].rgbtRed;
                    green_sum += duplicate[i + 1][0].rgbtGreen;
                    blue_sum += duplicate[i + 1][0].rgbtBlue;

                    pixel_count = 5;
                }

                // Pixel is in the rightmost column
                else if (j == width_max)
                {
                    // Pixel directly above
                    red_sum += duplicate[i - 1][width_max].rgbtRed;
                    green_sum += duplicate[i - 1][width_max].rgbtGreen;
                    blue_sum += duplicate[i - 1][width_max].rgbtBlue;

                    // Pixel along left diagonal upwards
                    red_sum += duplicate[i - 1][width_max - 1].rgbtRed;
                    green_sum += duplicate[i - 1][width_max - 1].rgbtGreen;
                    blue_sum += duplicate[i - 1][width_max - 1].rgbtBlue;

                    // Pixel to the left
                    red_sum += duplicate[i][width_max - 1].rgbtRed;
                    green_sum += duplicate[i][width_max - 1].rgbtGreen;
                    blue_sum += duplicate[i][width_max - 1].rgbtBlue;

                    // Pixel along left diagonal downwards
                    red_sum += duplicate[i + 1][width_max - 1].rgbtRed;
                    green_sum += duplicate[i + 1][width_max - 1].rgbtGreen;
                    blue_sum += duplicate[i + 1][width_max - 1].rgbtBlue;

                    // Pixel directly below
                    red_sum += duplicate[i + 1][width_max].rgbtRed;
                    green_sum += duplicate[i + 1][width_max].rgbtGreen;
                    blue_sum += duplicate[i + 1][width_max].rgbtBlue;

                    pixel_count = 5;
                }

                // Pixel is somewhere between leftmost and rightmost columns
                else
                {
                    // Pixel to the left
                    red_sum += duplicate[i][j - 1].rgbtRed;
                    green_sum += duplicate[i][j - 1].rgbtGreen;
                    blue_sum += duplicate[i][j - 1].rgbtBlue;

                    // Pixel along left diagonal upwards
                    red_sum += duplicate[i - 1][j - 1].rgbtRed;
                    green_sum += duplicate[i - 1][j - 1].rgbtGreen;
                    blue_sum += duplicate[i - 1][j - 1].rgbtBlue;

                    // Pixel directly above
                    red_sum += duplicate[i - 1][j].rgbtRed;
                    green_sum += duplicate[i - 1][j].rgbtGreen;
                    blue_sum += duplicate[i - 1][j].rgbtBlue;

                    // Pixel along right diagonal upwards
                    red_sum += duplicate[i - 1][j + 1].rgbtRed;
                    green_sum += duplicate[i - 1][j + 1].rgbtGreen;
                    blue_sum += duplicate[i - 1][j + 1].rgbtBlue;

                    // Pixel to the right
                    red_sum += duplicate[i][j + 1].rgbtRed;
                    green_sum += duplicate[i][j + 1].rgbtGreen;
                    blue_sum += duplicate[i][j + 1].rgbtBlue;

                    // Pixel along right diagonal downwards
                    red_sum += duplicate[i + 1][j + 1].rgbtRed;
                    green_sum += duplicate[i + 1][j + 1].rgbtGreen;
                    blue_sum += duplicate[i + 1][j + 1].rgbtBlue;

                    // Pixel directly below
                    red_sum += duplicate[i + 1][j].rgbtRed;
                    green_sum += duplicate[i + 1][j].rgbtGreen;
                    blue_sum += duplicate[i + 1][j].rgbtBlue;

                    // Pixel along left diagonal downwards
                    red_sum += duplicate[i + 1][j - 1].rgbtRed;
                    green_sum += duplicate[i + 1][j - 1].rgbtGreen;
                    blue_sum += duplicate[i + 1][j - 1].rgbtBlue;

                    pixel_count += 8;
                }
            }

            // Include the pixel itself in the the blur calculation
            red_sum += duplicate[i][j].rgbtRed;
            green_sum += duplicate[i][j].rgbtGreen;
            blue_sum += duplicate[i][j].rgbtBlue;

            pixel_count++;

            // Calculate the pixel's blur settings (float)
            float temp_red = red_sum / (float) pixel_count;
            float temp_green = green_sum / (float) pixel_count;
            float temp_blue = blue_sum / (float) pixel_count;

            // Round the pixel's blur settings to nearest int and store it into the pixel
            image[i][j].rgbtRed = round(temp_red);
            image[i][j].rgbtGreen = round(temp_green);
            image[i][j].rgbtBlue = round(temp_blue);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a duplicate image to use during calculations on a pixel
    RGBTRIPLE duplicate[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            duplicate[i][j] = image[i][j];
        }
    }

    // Assign values of Gx and Gy kernels to 2D arrays with 3 rows and 3 columns
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Maximium value of i: Index of bottom row
    int max_height_index = height - 1;

    // Maximum value of j: Index of rightmost column
    int max_width_index = width - 1;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Store Gx and Gy values
            int red_Gx_value = 0, red_Gy_value = 0;
            int green_Gx_value = 0, green_Gy_value = 0;
            int blue_Gx_value = 0, blue_Gy_value = 0;

            // Check neighbour pixel that have row indexs ranging from [i - 1] to [i + 1]
            // and column indexs ranging from [j - 1] to [j + 1]
            for (int neighbour_row = -1; neighbour_row < 2; neighbour_row++)
            {
                for (int neighbour_column = -1; neighbour_column < 2; neighbour_column++)
                {
                    // Check if neighbour pixel is in image bounds

                    // If true then update Gx and Gy values for RGB channel of current pixel
                    if ((i + neighbour_row) >= 0 && (i + neighbour_row) < height &&
                        (j + neighbour_column) >= 0 && (j + neighbour_column) < width)
                    {
                        /*
                            As iterating over neighbour rows and columns, neighbour_row and
                            neighbour_column give us the index of the neighbour pixel relative to
                           the centre pixel. However the 2D Gx and Gy arrays (matrices of order 3x3)
                            store the centre pixel as Gx[1][1] and Gy[1][1]. To overcome this
                            difference in placement of neighbouring pixels we have to add 1 to the
                            pixel's index relative to centre pixel.

                            E.g. For the centre pixel the neighour pixel on its right would have
                            relative indices
                            neighbour_row = 0
                            neighbour_column = 1

                            However for Gx and Gy array the pixel has the indices:
                            Gx[1][2]
                            Gy[1][2]

                            That is "second row of third column" as first row and column are
                           numbered 0.
                        */

                        // Gx values
                        red_Gx_value += duplicate[i + neighbour_row][j + neighbour_column].rgbtRed *
                                        Gx[neighbour_row + 1][neighbour_column + 1];
                        green_Gx_value +=
                            duplicate[i + neighbour_row][j + neighbour_column].rgbtGreen *
                            Gx[neighbour_row + 1][neighbour_column + 1];
                        blue_Gx_value +=
                            duplicate[i + neighbour_row][j + neighbour_column].rgbtBlue *
                            Gx[neighbour_row + 1][neighbour_column + 1];

                        // Gy values
                        red_Gy_value += duplicate[i + neighbour_row][j + neighbour_column].rgbtRed *
                                        Gy[neighbour_row + 1][neighbour_column + 1];
                        green_Gy_value +=
                            duplicate[i + neighbour_row][j + neighbour_column].rgbtGreen *
                            Gy[neighbour_row + 1][neighbour_column + 1];
                        blue_Gy_value +=
                            duplicate[i + neighbour_row][j + neighbour_column].rgbtBlue *
                            Gy[neighbour_row + 1][neighbour_column + 1];
                    }

                    // If pixel is out of image bounds then consider it a black pixel (RGB values 0)
                    else
                    {
                        // This calculation is not necessary and can be completely skipped. However,
                        // the pset demands that the out-of-bound pixels be considered as black
                        // pixels
                        red_Gx_value +=
                            duplicate[i + neighbour_row][j + neighbour_column].rgbtRed * 0;
                        green_Gx_value +=
                            duplicate[i + neighbour_row][j + neighbour_column].rgbtGreen * 0;
                        blue_Gx_value +=
                            duplicate[i + neighbour_row][j + neighbour_column].rgbtBlue * 0;
                        // Gy values
                        red_Gy_value +=
                            duplicate[i + neighbour_row][j + neighbour_column].rgbtRed * 0;
                        green_Gy_value +=
                            duplicate[i + neighbour_row][j + neighbour_column].rgbtGreen * 0;
                        blue_Gy_value +=
                            duplicate[i + neighbour_row][j + neighbour_column].rgbtBlue * 0;
                    }
                }
            }

            // Calculate Sobel filter channel value for the pixel (sf)
            // Gx
            float temp_red_sf = sqrt(pow(red_Gx_value, 2) + pow(red_Gy_value, 2));
            float temp_green_sf = sqrt(pow(green_Gx_value, 2) + pow(green_Gy_value, 2));
            float temp_blue_sf = sqrt(pow(blue_Gx_value, 2) + pow(blue_Gy_value, 2));

            // Round the values to nearest int
            int red_sf = round(temp_red_sf);
            int green_sf = round(temp_green_sf);
            int blue_sf = round(temp_blue_sf);

            // Prevent the channel values from going open 255 (highest possible value for a channel)
            if (red_sf > 255)
            {
                red_sf = 255;
            }

            if (green_sf > 255)
            {
                green_sf = 255;
            }

            if (blue_sf > 255)
            {
                blue_sf = 255;
            }

            // Set the sobiel filter value to the pixel's respective channels
            image[i][j].rgbtRed = red_sf;
            image[i][j].rgbtGreen = green_sf;
            image[i][j].rgbtBlue = blue_sf;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /* Calculate sepia equivalent for the pixel and round it to nearest int
             Also ensure the value does not go over 255 (the maximum value for an 8-bit color value) */

            // Red
            float sepiaRedtemp = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            int sepiaRed = round(sepiaRedtemp);

            less_than_255(&sepiaRed);

            // Green
            float sepiaGreentemp = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            int sepiaGreen = round(sepiaGreentemp);

            less_than_255(&sepiaGreen);

            // Blue
            float sepiaBluetemp = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            int sepiaBlue = round(sepiaBluetemp);

            less_than_255(&sepiaBlue);

            // Set final sepiaColor values to the pixel's RGB values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Helper function to ensure the RGB value of a pixel does not go over 255 (the maximum value for an 8-bit color value)
void less_than_255(int *pixel_value)
{
    if (*pixel_value > 255)
    {
        *pixel_value = 255;
    }
}
