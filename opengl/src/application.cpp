#include <iostream>
#include <sstream>

#define GLEW_STATIC
#include "GL/glew.h"	
#include "GLFW/glfw3.h"

// Variaveis globais
const char* APP_TITLE = "Aviao";
const int gWindowWidth = 800;
const int gWindowHeight = 600;
GLFWwindow* gWindow = NULL;

// Protótipos das funções
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void glfw_onFramebufferSize(GLFWwindow* window, int width, int height);
void mostrar_fps(GLFWwindow* window);
bool iniciar_opengl();

int main()
{
	if (!iniciar_opengl()) {
		std::cerr << "OpenGL nao inicializou" << std::endl;
		return -1;
	}

	// cria as coordenadas do triangulo
	GLfloat vertices[] = {
		0.0f, 0.5f, 0.0f, // cima
		0.5f, -0.5f, 0.0f, // direita
		-0.5f, -0.5f, 0.0f // esquerda
	};

	// identificador do objeto
	GLuint vbo, vao;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // usa o buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	// Loop de renderização
	while (!glfwWindowShouldClose(gWindow))
	{
		mostrar_fps(gWindow);

		// Poll for and process events
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// Swap front and back buffers
		glfwSwapBuffers(gWindow);
	}

	// Clean up
	glfwTerminate();

	return 0;
}

/*
	Função que inicializa o OpenGL (GLEW e GLFW)
*/
bool  iniciar_opengl() {
	// Inicia GLFW
	if (!glfwInit())
	{
		// Se der errado
		std::cerr << "GLFW nao inicializou" << std::endl;
		return false;
	}

	// Versão mínima para rodar a aplicação
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// Versão máxima para rodar a aplicação
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Usar somente funções 'modernas'
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Se for rodar em MAC OS
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	// forward compatible with newer versions of OpenGL as they become available but not backward compatible (it will not run on devices that do not support OpenGL 3.3

	// Cria uma janela OpenGL
	gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);
	if (gWindow == NULL)
	{
		std::cerr << "Falhou em criar a janela GLFW" << std::endl;
		glfwTerminate();
		return false;
	}

	// Usar a janela como o contexto atual
	glfwMakeContextCurrent(gWindow);

	// Inicializa o GLEW 
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Falhou em iniciar o GLEW" << std::endl;
		return false;
	}

	// Set the required callback functions
	glfwSetKeyCallback(gWindow, glfw_onKey);
	glfwSetFramebufferSizeCallback(gWindow, glfw_onFramebufferSize);

	// Informações da versão do OpenGL
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	std::cout << "Renderer: " << renderer << std::endl;
	std::cout << "OpenGL version supported: " << version << std::endl;
	std::cout << "OpenGL Initialization Complete" << std::endl;

	// Colore o plano de fundo
	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	return true;
}

/* 
Função que é chamada quando o usuário clica em uma tecla
*/
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

/* 
Função que é chamada quando a janela é redimensionada
*/
void glfw_onFramebufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/* 
Mostra os frames por segundo e frames a cada segundo no topo da janela.
*/
void mostrar_fps(GLFWwindow* window)
{
	static double previousSeconds = 0.0;
	static int frameCount = 0;
	double elapsedSeconds;
	double currentSeconds = glfwGetTime(); // returns number of seconds since GLFW started, as double float

	elapsedSeconds = currentSeconds - previousSeconds;

	// Permite somente 4 atualizações por segundo
	if (elapsedSeconds > 0.25)
	{
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / elapsedSeconds;
		double msPerFrame = 1000.0 / fps;

		// Muda o título da janela
		std::ostringstream outs;
		outs.precision(3);
		outs << std::fixed
			<< APP_TITLE << "    "
			<< "FPS: " << fps << "    "
			<< "Frame Time: " << msPerFrame << " (ms)";
		glfwSetWindowTitle(window, outs.str().c_str());

		// Reseta
		frameCount = 0;
	}

	frameCount++;
}