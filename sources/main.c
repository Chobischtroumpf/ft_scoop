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
	{
		printf("glfwInit failed\n");
		return (0);
	}
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	context->primary = glfwGetPrimaryMonitor();
	context->video_mode = glfwGetVideoMode(context->primary);
	context->vertices = NULL;
	context->amount_coordinates = 0;
	context->obj = obj;
	return (1); 
}

void coloring(scop_t *context)
{	
	// float time_value = glfwGetTime();
	// float green_value = fabs((sin(time_value) / 2.0f) + 0.5f);
	// float blue_value = fabs((cos(time_value) / 2.0f) + 0.5f);
	// float red_value = fabs((tan(time_value) / 2.0f) + 0.5f);
	int vertex_color_location = glGetUniformLocation(context->shader_program, "ourColor");
	glUseProgram(context->shader_program);
	glUniform4f(vertex_color_location, 1, 0.6, 1, 1.0f);
}

int main(int argc, char **argv)
{
	scop_t *context;

	context = ft_get_context();
	if (argc == 2)
	{
		if (!init_context(context, argv[1]))
			return (0);
		if (parse_file(context) < 0)
			return (-1);
		context->window = glfwCreateWindow(1280, 1280, "Scop", NULL, NULL);
		if (!context->window)
		{
			glfwTerminate();
			return (-1);
		}
		glViewport(0, 0, 1280, 1280);
		glfwMakeContextCurrent(context->window);
		glfwSetFramebufferSizeCallback(context->window, set_window_framebuffer);
		if (compile_shader_progs(context) < 0)
			exit(-1);
		create_buffers(context);
		// printf("%d\n",context->amount_coordinates);
		// printf("context->amount_faces : %d\n", context->amount_faces);
		while (!glfwWindowShouldClose(context->window))
		{
			processInput(context->window);
			// /* Render here */
			// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glClearColor(0.3, 0.3, 0.3, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			coloring(context);
			update_buffers(context);
			glBindVertexArray(context->VAO);
			glDrawElements(GL_TRIANGLES, context->amount_faces, GL_UNSIGNED_INT, 0);
			/* Swap front and back buffers */

			glfwPollEvents();
			glfwSwapBuffers(context->window);

		}
		glDeleteVertexArrays(1, &(context->VAO));
		glDeleteBuffers(1, &(context->VBO));
		glDeleteBuffers(1, &(context->EBO));
		glDeleteProgram(context->shader_program);
		glfwTerminate();
		return 0;
	}
	else
		write(1, "wrong amount of arguments to the program:\n\tusage: ./scop [*.obj]\n", 65);
}
