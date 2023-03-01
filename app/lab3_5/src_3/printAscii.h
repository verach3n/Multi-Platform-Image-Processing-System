unsigned char NR_ASCII_CHARS = 16;
char asciiChars[] = {' ','.',':','-','=','+','/','t','z','U','w','*','0','#','%','@'};

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
