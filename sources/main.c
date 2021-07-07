#include "scop.h"

void processInput(GLFWwindow *window, scop_t *context)
{
	float time = 0;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		time = glfwGetTime();
		context->rotation_speed = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		if (time)
			glfwSetTime(time);
		context->rotation_speed = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	
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
	context->rotation_speed = 0;
	reset_matrice(context->rotation_matrice);
	reset_matrice(context->color_matrice);
	reset_matrice(context->center_matrice);
	return (1); 
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
		int i = 0;
		glfwSetTime(1);
		glEnable(GL_DEPTH_TEST);
		// glDepthFunc(GL_LESS);
		while (!glfwWindowShouldClose(context->window))
		{
			processInput(context->window, context);
			// /* Render here */
			glClearColor(0.1, 0.1, 0.1, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// coloring(context);
			glUseProgram(context->shader_program);
			update_buffers(context);
			glBindVertexArray(context->VAO);
			glDrawElements(GL_TRIANGLES, context->amount_faces, GL_UNSIGNED_INT, 0);
			/* Swap front and back buffers */

			glfwPollEvents();
			glfwSwapBuffers(context->window);
			if (i%60 == 0)
				printf("%d | %f\n", i, glfwGetTime());
			i++;
			// sleep(5);
		}
		glDeleteVertexArrays(1, &(context->VAO));
		glDeleteBuffers(1, &(context->VBO));
		glDeleteBuffers(1, &(context->EBO));
		glDeleteProgram(context->shader_program);
		glfwTerminate();
		exit(0);
		return 0;
	}
	else
		write(1, "wrong amount of arguments to the program:\n\tusage: ./scop [*.obj]\n", 65);
}
