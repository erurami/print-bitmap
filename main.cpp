
#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include "libs\surface.h"

int power(int base, int power)
{
    int retval = 1;
    for (int i = 0; i < power; i++)
    {
        retval *= base;
    }
    return retval;
}

long getImageSizeOfBitmap(unsigned char* bitmap_header)
{
    long file_size = 0;
    for (int i = 0x22; i < 0x26; i++)
    {
        file_size += bitmap_header[i] * power(256, (i - 0x22));
    }
    return file_size;
}

long getWidthOfBitmap(unsigned char* bitmap_header)
{
    long width = 0;
    for (int i = 0x12; i < 0x16; i++)
    {
        width += bitmap_header[i] * power(256, (i - 0x12));
    }
    return width;
}

long getHeightOfBitmap(unsigned char* bitmap_header)
{
    long height = 0;
    for (int i = 0x16; i < 0x1a; i++)
    {
        height += bitmap_header[i] * power(256, (i - 0x16));
    }
    return height;
}

int main(int argc, char **argv)
{
    system("cls");
    if (argc < 2)
    {
        printf("need command line arguments to open file\n");
    }

    unsigned char bitmap_header[54];

    FILE* image_file;
    image_file = fopen(argv[1], "rb");

    if (image_file == NULL)
    {
        printf("couldn't open the file");
        return -1;
    }

    fread(bitmap_header, sizeof(bitmap_header), 1, image_file);


    int image_data_length = getImageSizeOfBitmap(bitmap_header);

    int image_width = getWidthOfBitmap(bitmap_header);
    int image_height = getHeightOfBitmap(bitmap_header);

    int data_length_per_row = image_data_length / image_height;

    unsigned char bitmap_main_data[image_data_length];
    fread(bitmap_main_data, sizeof(bitmap_main_data), 1, image_file);

    int seeking_data_index = 0;


    Surface main_surface(image_width * 2, image_height);
    Pixel pixel_just_set;


    for (int i = image_height - 1; i >= 0; i--)
    {
        seeking_data_index = data_length_per_row * (image_height - i - 1);
        for (int j = 0; j < image_width; j++)
        {
            main_surface.SetBackgroundAt(j * 2, i,
                                         bitmap_main_data[seeking_data_index++],
                                         bitmap_main_data[seeking_data_index++],
                                         bitmap_main_data[seeking_data_index++]);

            pixel_just_set = main_surface.GetPixelAt(j * 2, i);
            main_surface.SetPixelAt(j * 2 + 1, i, &pixel_just_set);
        }
    }

    main_surface.Print();
    Sleep(500);

    system("cls");

    return 0;
}
