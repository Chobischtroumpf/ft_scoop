#include <GLFW/glfw3.h>
#include "ppm_img.h"

int main(int argc, char **argv)
{
    t_ppm_img *img = load_PPM(argv[1]);
    
    if (img == NULL)
    {
        printf("Error: Could not load image, exiting.\n");
        return 1;
    }
    if (!glfwInit())
    {
        printf("Error: Could not initialize GLFW, exiting.\n");
        return 1;
    }
    GLFWwindow *window = glfwCreateWindow(img->width, img->height, "test", NULL, NULL);
    if (window == NULL)
    {
        printf("Error: Could not create window, exiting.\n");
        return 1;
    }
    glfwMakeContextCurrent(window);
    glDrawPixels(img->width, img->height, GL_RGB, GL_UNSIGNED_BYTE, img->pixels);
    glfwSwapBuffers(window);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        // sleep(1);
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    if (img != NULL)
        unload_PPM(img);
    return 0;
}