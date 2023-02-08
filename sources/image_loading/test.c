#include "bitmap.h"

int main(int argc, char **argv)
{
    t_bmp_img *img = load_BMP(argv[1]);
    unload_BMP(img);
    return 0;
}