#include "scop.h"

void processInput(GLFWwindow *window, scop_t *context)
{
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && context->amount_objects > 0){
		context->working_object = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && context->amount_objects > 1){
		context->working_object = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && context->amount_objects > 2){
		context->working_object = 2;
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && context->amount_objects > 3){
		context->working_object = 3;
	}
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && context->amount_objects > 4){
		context->working_object = 4;
	}
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS && context->amount_objects > 5){
		context->working_object = 5;
	}
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS && context->amount_objects > 6){
		context->working_object = 6;
	}
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS && context->amount_objects > 7){
		context->working_object = 7;
	}
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS && context->amount_objects > 8){
		context->working_object = 8;
	}
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS && context->amount_objects > 9){
		context->working_object = 9;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		context->objects[context->working_object]->should_rotate = 1;
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
		context->objects[context->working_object]->should_rotate = 0;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS  || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		context->objects[context->working_object]->translation_vector.x += 0.05;
		context->objects[context->working_object]->center_vector.x += 0.05;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		context->objects[context->working_object]->translation_vector.x -= 0.05;
		context->objects[context->working_object]->center_vector.x -= 0.05;
		}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		context->objects[context->working_object]->translation_vector.y += 0.05;
		context->objects[context->working_object]->center_vector.y += 0.05;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		context->objects[context->working_object]->translation_vector.y -= 0.05;
		context->objects[context->working_object]->center_vector.y -= 0.05;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && context->objects[context->working_object]->translation_vector.z < 1.0){
		context->objects[context->working_object]->translation_vector.z += 0.05;
		context->objects[context->working_object]->center_vector.z += 0.05;
		// printf("translation vector : x : %f, y : %f, z : %f \n", context->translation_vector.x, context->translation_vector.y, context->translation_vector.z);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && context->objects[context->working_object]->translation_vector.z > -1.0){
		context->objects[context->working_object]->translation_vector.z -= 0.05;
		context->objects[context->working_object]->center_vector.z -= 0.05;
		// printf("translation vector : x : %f, y : %f, z : %f \n", context->translation_vector.x, context->translation_vector.y, context->translation_vector.z);
	}
}

void set_window_framebuffer(GLFWwindow *window, int width, int height)
{
	(void)window;
	printf("monitor width = %d\n monitor height = %d\n", width, height);
	glViewport(0, 0, width, height);
}

int	init_context(scop_t *context, char **obj, int argc)
{
	int i = 0;

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
	if (!(context->obj = (char **)malloc(sizeof(char*) * (argc-1))))
		exit(-1);
	while (i < argc-1)
	{
		if (!(context->obj[i] = ft_strdup(obj[i])))
			exit(-1);
		i++;
	}
	context->amount_objects = i;
	if (!(context->objects = (t_object**)malloc(sizeof(t_object*) * context->amount_objects)))
		exit(-1);
	context->vertices = NULL;
	context->amount_coordinates = 0;
	context->should_rotate = 1;
	context->center_vector = vec3f_init();
	context->translation_vector = vec3f_init();
	context->rotation_matrice = m4_init();
	context->color_matrice = m4_init();
	return (1); 
}

int main(int argc, char **argv)
{
	scop_t *context;

	context = ft_get_context();
	if (argc >= 2)
	{
		if (!init_context(context, argv, argc))
			return (0);
		if (parse_file(context) < 0)
			return (1);
		context->window = glfwCreateWindow(1280, 1280, "Scop", NULL, NULL);
		if (!context->window)
		{
			glfwTerminate();
			return (2);
		}
		glfwMakeContextCurrent(context->window);
		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        	printf("Failed to initialize OpenGL context\n");
        	return -1;
    	}
		glViewport(0, 0, 1280, 1280);
		glfwSetFramebufferSizeCallback(context->window, set_window_framebuffer);
		if (compile_shader_progs(context) < 0)
			exit(-1);
		create_buffers(context);
		int i = 0;
		glfwSetTime(1);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		while (!glfwWindowShouldClose(context->window))
		{
			processInput(context->window, context);
			/* Render here */
			glClearColor(0.8, 0.8, 0.8, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// coloring(context);
			glUseProgram(context->shader_program);
			update_buffers(context);
			glBindVertexArray(context->VAO);
			glDrawElements(GL_TRIANGLES, context->amount_faces, GL_UNSIGNED_INT, 0);
			/* Swap front and back buffers */
			glfwPollEvents();
			glfwSwapBuffers(context->window);
			if (context->should_rotate)
			{
				context->rotation_vector.y = i/(40*PI);
				i++;
			}
			usleep(1700);
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
