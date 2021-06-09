#include "scop.h"

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 20, 2560, 1440, 60);
}

void set_window_framebuffer(GLFWwindow *window, int width, int height)
{
	(void)window;
	printf("monitor width = %d\n monitor height = %d\n", width, height);
	glViewport(0, 0, width, height);
}

int	init_glfw(scop_t *context)
{
	if (!glfwInit())
		return (0);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	context->primary = glfwGetPrimaryMonitor();
	context->video_mode = glfwGetVideoMode(context->primary);
	return (1); 
}

int main(int argc, char **argv)
{
	scop_t *context;
	vertices_t *vertices;
	(void)argv;

	context = ft_get_context();
	if (argc == 2)
	{
		if (!init_glfw(context))
			return (0);
		parse_file(context);
		printf("monitor width = %d\n monitor height = %d\n", context->video_mode->width, context->video_mode->height); //to remove
		context->window = glfwCreateWindow(context->video_mode->width,
			context->video_mode->height, "Scop", NULL, NULL);
		if (!context->window)
		{
			glfwTerminate();
			return (-1);
		}
		glViewport(0, 0, context->video_mode->width, context->video_mode->height);
		glfwMakeContextCurrent(context->window);
		glfwSetFramebufferSizeCallback(context->window, set_window_framebuffer);
		while (!glfwWindowShouldClose(context->window))
		{
			processInput(context->window);
			// /* Render here */
			glClearColor(0.2f, 0.3f, 0.01f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			vertices = context->vertices;
			while (vertices)
			{
				glGenBuffers(1, &vertices->VBO);
				vertices = vertices->next;
			}
			// /* Swap front and back buffers */
			glfwPollEvents();
			glfwSwapBuffers(context->window);

		}
		glfwTerminate();
		return 0;
	}
	else
		write(1, "wrong amount of arguments to the program:\n\tusage: ./scop [*.obj]\n", 65);
}
