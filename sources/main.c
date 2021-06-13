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

int	init_context(scop_t *context, char *obj)
{
	if (!glfwInit())
		return (0);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	context->primary = glfwGetPrimaryMonitor();
	context->video_mode = glfwGetVideoMode(context->primary);
	context->vertices = NULL;
	context->amount_vertices = 0;
	context->obj = obj;
	return (1); 
}

int main(int argc, char **argv)
{
	scop_t *context;
	vertices_t *vertices;

	context = ft_get_context();
	if (argc == 2)
	{
		if (!init_context(context, argv[1]))
			return (0);
		if (parse_file(context) < 0)
			return (-1);
		context->vertices = rewind_vertices(context->vertices);
		vertices = context->vertices;
		while (vertices)
		{
			printf("x : %f, y : %f, z : %f\n", vertices->coordinates[0], vertices->coordinates[1], vertices->coordinates[2]);
			vertices = vertices->next;
			 glGenBuffers(1, &vertices->VBO);
			// vertices = vertices->next;
		}
		context->vertices = rewind_vertices(context->vertices);
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
