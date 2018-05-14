#include <iostream>
#define GLEW_STATIC
#include "GL/glew.h" //tem o opengl
#include "GLFW/glfw3.h" //tem input e criar janelas

//variaveis para criar janela
const char* APP_TITLE = "Janela do OpenGL!";
const int gWindowWidth = 800;
const int gWindowHeight = 600;

int main() {

	//testa se o glfw inicializou 
	if (!glfwInit()) {
		std::cerr << "GLFW nao inicializou\n";
		return -1;
	}

	// define a versao minima do opengl para 3 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// nao deixa usar funcoes obsoletas
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//criar janela
	GLFWwindow* pWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);
	//se não criar a janela
	if (pWindow == NULL) {
		std::cerr << "Falhou a criacao da janela\n";
		glfwTerminate();
		return -1;
	}
	
	//deixa como a janela principal - testar sem ele
	glfwMakeContextCurrent(pWindow);

	//inicializa o glew e testa se deu certo
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Falhou a criacao do glew\n";
		glfwTerminate();
		return -1;
	}

	//loop principal
	while (!glfwWindowShouldClose(pWindow)) {
		//Verifica se tem entradas
		glfwPollEvents();
		
		/*COLOCAR O CÓDIGO PRINCIPAL AQUI!!!*/
		
		//muda a cor da janela
		glClearColor(0.23f, 0.38f, .47f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		/*FIM DO CÓDIGO PRINCIPAL!!*/

		/*
			tem 2 buffers: mostrando e pintando
			essa função separa os dois
			diminui flicker
		*/
		glfwSwapBuffers(pWindow);
	}

	//termina o código
	glfwTerminate();
	return 0;
}