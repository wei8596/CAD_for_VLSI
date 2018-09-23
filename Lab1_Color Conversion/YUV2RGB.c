#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int overflow(double data);

int main()
{
    double Y, U, V;
    unsigned int countnum = 0;
    unsigned int x, y;
    unsigned int width, height;
    unsigned char *image = NULL; // source image array
    unsigned char *image_Y = NULL; // target image array
    unsigned char *image_U = NULL; // target image array
    unsigned char *image_V = NULL; // target image array
    unsigned char R, G, B;         // color of R, G, B

    unsigned int file_size;           // file size
    unsigned int rgb_raw_data_offset; // RGB raw data offset
    unsigned short bit_per_pixel;     // bit per pixel
    unsigned short byte_per_pixel;

    unsigned char header[54] =
    {
        0x42,        // identity : B
        0x4d,        // identity : M
        0, 0, 0, 0,  // file size
        0, 0,        // reserved1
        0, 0,        // reserved2
        54, 0, 0, 0, // RGB data offset
        40, 0, 0, 0, // struct BITMAPINFOHEADER size
        0, 0, 0, 0,  // bmp width
        0, 0, 0, 0,  // bmp height
        1, 0,        // planes
        24, 0,       // bit per pixel
        0, 0, 0, 0,  // compression
        0, 0, 0, 0,  // data size
        0, 0, 0, 0,  // h resolution
        0, 0, 0, 0,  // v resolution
        0, 0, 0, 0,  // used colors
        0, 0, 0, 0   // important colors
    };

    FILE *fp_Y = fopen("mountain256_Y.bmp", "rb");
    FILE *fp_U = fopen("mountain256_U.bmp", "rb");
    FILE *fp_V = fopen("mountain256_V.bmp", "rb");

    if( fp_Y == NULL )
    {
        printf( "open fail.\n" );
        return -1;
    }
    if( fp_U == NULL )
    {
        printf( "open fail.\n" );
        return -1;
    }
    if( fp_V == NULL )
    {
        printf( "open fail.\n" );
        return -1;
    }
    fseek(fp_Y, 10, SEEK_SET);
    fread(&rgb_raw_data_offset, sizeof(unsigned int), 1, fp_Y);
     // move offset to 18    to get width & height;
    fseek(fp_Y, 18, SEEK_SET);
    fread(&width,  sizeof(unsigned int), 1, fp_Y);
    fread(&height, sizeof(unsigned int), 1, fp_Y);
    // get  bit per pixel
    fseek(fp_Y, 28, SEEK_SET);
    fread(&bit_per_pixel, sizeof(unsigned short), 1, fp_Y);
    byte_per_pixel = bit_per_pixel / 8;
    fseek(fp_Y, rgb_raw_data_offset, SEEK_SET);
    
    fseek(fp_U, 10, SEEK_SET);
    fread(&rgb_raw_data_offset, sizeof(unsigned int), 1, fp_U);
     // move offset to 18    to get width & height;
    fseek(fp_U, 18, SEEK_SET);
    fread(&width,  sizeof(unsigned int), 1, fp_U);
    fread(&height, sizeof(unsigned int), 1, fp_U);
    // get  bit per pixel
    fseek(fp_U, 28, SEEK_SET);
    fread(&bit_per_pixel, sizeof(unsigned short), 1, fp_U);
    byte_per_pixel = bit_per_pixel / 8;
    fseek(fp_U, rgb_raw_data_offset, SEEK_SET);
    
    fseek(fp_V, 10, SEEK_SET);
    fread(&rgb_raw_data_offset, sizeof(unsigned int), 1, fp_V);
     // move offset to 18    to get width & height;
    fseek(fp_V, 18, SEEK_SET);
    fread(&width,  sizeof(unsigned int), 1, fp_V);
    fread(&height, sizeof(unsigned int), 1, fp_V);
    // get  bit per pixel
    fseek(fp_V, 28, SEEK_SET);
    fread(&bit_per_pixel, sizeof(unsigned short), 1, fp_V);
    byte_per_pixel = bit_per_pixel / 8;
    fseek(fp_V, rgb_raw_data_offset, SEEK_SET);

    image = (unsigned char *)malloc((size_t)width * height * byte_per_pixel);
    image_Y = (unsigned char *)malloc((size_t)width * height * byte_per_pixel);
    image_U = (unsigned char *)malloc((size_t)width * height * byte_per_pixel);
    image_V = (unsigned char *)malloc((size_t)width * height * byte_per_pixel);


    fread(image_Y, sizeof(unsigned char), (size_t)(long)width * height * byte_per_pixel, fp_Y);
    fread(image_U, sizeof(unsigned char), (size_t)(long)width * height * byte_per_pixel, fp_U);
    fread(image_V, sizeof(unsigned char), (size_t)(long)width * height * byte_per_pixel, fp_V);

    //printf("%d\n", (size_t)(long)width * height * byte_per_pixel);
    FILE *fp_YUV = fopen( "YUV_value.txt", "w" );
    FILE *fp_RGB = fopen( "RGB_value.txt", "w" );

    
    
    // ...
    const int SIZE = width * height * byte_per_pixel;
    int i;
    for(i = 0; i < SIZE; i += 3) {
    	Y = image_Y[i];
    	U = image_U[i];
    	V = image_V[i];
    	
    	B = Y + 1.7718*(U-128);
    	G = Y - 0.34414*(U-128) - 0.71414*(V-128);
    	R = Y + 1.4021*(V-128);
		
    	B = overflow(B);
    	G = overflow(G);
    	R = overflow(R);
    	
    	image[i] = B;
    	image[i+1] = G;
    	image[i+2] = R;
	}
    
    

    // write to new bmp
    FILE *fp = fopen( "converted_mountain256.bmp", "wb");

    // file size
    file_size = width * height * byte_per_pixel + rgb_raw_data_offset;
    header[2] = (unsigned char)(file_size & 0x000000ff);
    header[3] = (file_size >> 8)  & 0x000000ff;
    header[4] = (file_size >> 16) & 0x000000ff;
    header[5] = (file_size >> 24) & 0x000000ff;

    // width
    header[18] = width & 0x000000ff;
    header[19] = (width >> 8)  & 0x000000ff;
    header[20] = (width >> 16) & 0x000000ff;
    header[21] = (width >> 24) & 0x000000ff;

    // height
    header[22] = height &0x000000ff;
    header[23] = (height >> 8)  & 0x000000ff;
    header[24] = (height >> 16) & 0x000000ff;
    header[25] = (height >> 24) & 0x000000ff;

    // bit per pixel
    header[28] = bit_per_pixel;

    // write header
    fwrite(header, sizeof(unsigned char), rgb_raw_data_offset, fp);
    // write image
    fwrite(image, sizeof(unsigned char), (size_t)(long)width * height * byte_per_pixel, fp);

    fclose(fp);
    fclose(fp_Y);
    fclose(fp_U);
    fclose(fp_V);
    fclose(fp_RGB);
    fclose(fp_YUV);

    return 0;
}

int overflow(double data) {
	if(data > 255) {
		return 255;
	}
	else if(data < 0) {
		return 0;
	}
	
	return data;
}
