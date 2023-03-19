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
