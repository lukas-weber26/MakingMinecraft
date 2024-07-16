#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>

void window_resize(GLFWwindow * window, int idth, int height);
GLFWwindow * create_window();
void render_loop_start();
void render_loop_end(GLFWwindow * window);

int main() {
	
	GLFWwindow * window = create_window();

	//for now just render something. That way you can start worrying about the blocks, textures, cameras etc. one at at a time.
	unsigned int VAO;
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);

	float vertices [] = {-1.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0,0.0};

	unsigned int VBO;
	glGenBuffers(1,&VBO);	
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void *)0);
	glEnableVertexAttribArray(0);

	int success;

//const char * vertexShaderSource = "#version 330 core\n"
//    "layout (location = 0) in vec3 aPos;\n"
//    "void main()\n"
//    "{\n"
//    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//    "}\0";
//
//const char * fragmentShaderSource = "#version 330 core\n"
//    "out vec4 FragColor;\n"
//    "void main()\n"
//    "{\n"
//    "FragColor = vertexColor;\n"
//    "}\0";

	const char * vertex_shader_source= "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main() {\n"
	"gl_Position = vec4(aPos, 1.0);}\0";

	const char * fragment_shader_source = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main() {\n"
	"FragColor = vec4(0.9f,0.0f,0.8f,0.9f);}\0";

	unsigned int vertex_shader  = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader  , 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader,GL_COMPILE_STATUS,&success);
	assert(success);
	
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader,GL_COMPILE_STATUS,&success);
	assert(success);

	unsigned int shader_program = glCreateProgram();
	glAttachShader(shader_program, fragment_shader);
	glAttachShader(shader_program, vertex_shader);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	assert(success);

	glDeleteShader(vertex_shader);	
	glDeleteShader(fragment_shader);	

	while (!glfwWindowShouldClose(window)) {
		render_loop_start();
		
		glBindVertexArray(VAO);
		glUseProgram(shader_program);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		render_loop_end(window);
	}
}

void render_loop_end(GLFWwindow * window) {	
	glfwSwapBuffers(window);
}

void render_loop_start() {
	glfwPollEvents();
	glClearColor(0.6, 0.0, 0.1, 0.5);
	glClear(GL_COLOR_BUFFER_BIT);
}

void window_resize(GLFWwindow * window, int width, int height) {
	glViewport(0, 0, width, height);	
}

GLFWwindow * create_window() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
	
	GLFWwindow* window = glfwCreateWindow(1920,1080,"Main", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, window_resize);
	glfwPollEvents();

	glViewport(0, 0, 1920, 1080);	

	glewExperimental = GL_TRUE;
	glewInit();

	return window;
}
