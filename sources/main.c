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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	context->primary = glfwGetPrimaryMonitor();
	context->video_mode = glfwGetVideoMode(context->primary);
	context->vertices = NULL;
	context->amount_vertices = 0;
	context->obj = obj;
	context->vertex_shader_source = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";
	context->fragment_shader_source = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";
	return (1); 
}

int compile_shader_progs(void)
{
	scop_t *context = ft_get_context();
	int  success;
	char infoLog[512];

	printf("here1\n");
	context->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(context->vertex_shader, 1, &(context->vertex_shader_source), NULL);
	printf("here2\n");
	glCompileShader(context->vertex_shader);
	printf("here3\n");
	glGetShaderiv(context->vertex_shader, GL_COMPILE_STATUS, &success);
	printf("here4\n");
	if (!success)
	{
		glGetShaderInfoLog(context->vertex_shader, 512, NULL, infoLog);
		printf("Error: %s\n", infoLog);
		return (-1);
	}

	printf("here5\n");
	context->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(context->fragment_shader, 1, &(context->fragment_shader_source), NULL);
	glCompileShader(context->fragment_shader);
	glGetShaderiv(context->fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(context->fragment_shader, 512, NULL, infoLog);
		printf("Error: %s\n", infoLog);
		return (-1);
	}
	context->shader_program = glCreateProgram();
	glAttachShader(context->shader_program, context->vertex_shader);
	glAttachShader(context->shader_program, context->fragment_shader);
	glLinkProgram(context->shader_program);
	glGetProgramiv(context->shader_program, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(context->shader_program, 512, NULL, infoLog);
		printf("Error: %s\n", infoLog);
		return (-1);
	}
	glUseProgram(context->shader_program);
	return (0);
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
		// int i = 0;
		// while(i < context->amount_vertices)
			printf("width : %d | height : %d | \n", context->video_mode->width, context->video_mode->height);
		context->window = glfwCreateWindow(context->video_mode->width,
			context->video_mode->height, "Scop", NULL, NULL);
		if (!context->window)
		{
			printf("window is null\n");
			glfwTerminate();
			return (-1);
		}
		glViewport(0, 0, context->video_mode->width, context->video_mode->height);
		glfwMakeContextCurrent(context->window);
		glfwSetFramebufferSizeCallback(context->window, set_window_framebuffer);
		printf("%s\n", glGetString(GL_VERSION));
		if (compile_shader_progs() < 0)
			exit(-1);

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
