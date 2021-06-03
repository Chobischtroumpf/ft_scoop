#include <OpenGL/gl.h>
#include <GLFW/glfw3.h>
#include <unistd.h>

#define GL_SILENCE_DEPRECATION 1

int main(int argc, char ** argv)
{

	GLFWmonitor *primary;
	GLFWwindow *window;
	const GLFWvidmode *temp_struct;

	if (argc == 2)
	{
		if (!glfwInit())
			return (0);
		primary = glfwGetPrimaryMonitor();
		temp_struct = glfwGetVideoMode(primary);
		printf("monitor width = %d\n monitor height = %d\n", temp_struct->width, temp_struct->height);
		window = glfwCreateWindow(temp_struct->width, temp_struct->height, "test window", NULL, NULL);
		if (!window)
    	{
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
		glfwTerminate();
		return 0;
	}
	else
		write(1, "wrong amount of arguments to the program:\n\tusage: ./scop [*.obj]\n", 65);
}
