#include <GL/gl.h>
#include <GLFW/glfw3.h>

int main ()
{
    const char* renderer = (const char*) glGetString(GL_RENDERER);
    printf("%s\n",renderer);
    const char* version = (const char*) glGetString(GL_VERSION);
    printf("%s\n", version);
    const char* glslVersion = (const char*) glGetString(GL_SHADING_LANGUAGE_VERSION);
    printf("%s\n", glslVersion);
}