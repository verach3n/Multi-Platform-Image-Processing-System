void resize(unsigned char* image, unsigned char* resizedata, int x_dim, int y_dim) {
    int i, j;

    for (i = 0; i < x_dim/2; i++) {
        for (j = 0; j < y_dim/2; j++) {
           resizedata[i * y_dim/2 + j] = (image[2*i*y_dim + 2*j] + image[2*i*y_dim + 2*j+1] + image[(2*i+1)*y_dim + 2*j] + image[(2*i+1)*y_dim + 2*j+1])/4;
        }
    }
}
