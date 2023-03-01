unsigned char NR_ASCII_CHARS = 16;
char asciiChars[] = {' ','.',':','-','=','+','/','t','z','U','w','*','0','#','%','@'};

void grayscale(unsigned char* base, unsigned char* graydata)
{
	int x, y;
	unsigned char r, g, b;

	int size_x = *base++;
	int size_y = *base++;
	int max_col= *base++;

	unsigned char* gray;
	gray = graydata;

	for(y = 0; y < size_y; y++)
	{
		for(x = 0; x < size_x; x++)
		{
			r = ((*base)>>2) + ((*base)>>4);
			base++; 
			g = ((*base)>>1) + ((*base)>>4);
			base++;
			b = (*base)>>3;
			base++;
			*gray++ = r + g + b;
		}
	}
}

/**
 * @brief Prints out an image of gray values into ASCII art format
 * @param image pointer to an image
 * @param x_dim image X dimention
 * @param y_dim image Y dimention
 */
void printAscii(unsigned char* image, int x_dim, int y_dim) {
  int k = 0;
  int l = 0;
  for(k = 0; k < y_dim; k++) {
    for(l = 0; l < x_dim; l++) {
      unsigned char pixel = image[k * y_dim + l];
      // Clamp pixel value to 255
      unsigned char c_pixel = pixel > 255 ? 255 : pixel;
      // Print normalized value as ASCII character
      printf("%4c", asciiChars[((NR_ASCII_CHARS - 1) * c_pixel) / 255]);
    }
    printf("\n");
  }
}
