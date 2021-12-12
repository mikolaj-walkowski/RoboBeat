/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#define GLM_FORCE_RADIANS

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "Pipeline.h"


//TODO KeyCallback i Movment atachment dla gracza mo¿e dekorator 
//TODO Textury
std::map<std::string, bool> inputs;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_W) inputs["W"] = 1;
		if (key == GLFW_KEY_A) inputs["A"] = 1;
		if (key == GLFW_KEY_D) inputs["D"] = 1;
	//	if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(true);
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_W) inputs["W"] = 0;
		if (key == GLFW_KEY_A) inputs["A"] = 0;
		if (key == GLFW_KEY_D) inputs["D"] = 0;
	}
}


//Error processing callback procedure
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Initialization code procedure
void initOpenGLProgram(GLFWwindow* window) {
	//initShaders();
	//glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);
	glfwSetKeyCallback(window, key_callback);
	//************Place any code here that needs to be executed once, at the program start************
	auto pipeline = Pipeline::getInstance();
	pipeline->initializeSPs();
	pipeline->attachKey(&inputs);
	pipeline->initalizeEnts();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//Release resources allocated by the program
void freeOpenGLProgram(GLFWwindow* window) {
    //freeShaders();
	//************Place any code here that needs to be executed once, after the main loop ends************
	Pipeline::getInstance()->deleteSPs();
}

//Drawing procedure
void drawScene(GLFWwindow* window,float dT) {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	Pipeline::getInstance()->draw();
	glfwSwapBuffers(window);
	//************Place any code here that draws something inside the window******************
	
}

int main(void)
{
	GLFWwindow* window; //Pointer to object that represents the application window

	glfwSetErrorCallback(error_callback);//Register error processing callback procedure

	if (!glfwInit()) { //Initialize GLFW library
		fprintf(stderr, "Can't initialize GLFW.\n");
		exit(EXIT_FAILURE); 
	}

	window = glfwCreateWindow(1600, 900, "OpenGL", NULL, NULL);  //Create a window 500pxx500px titled "OpenGL" and an OpenGL context associated with it. 

	if (!window) //If no window is opened then close the program
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Since this moment OpenGL context corresponding to the window is active and all OpenGL calls will refer to this context.
	glfwSwapInterval(1); //During vsync wait for the first refresh

	GLenum err;
	if ((err=glewInit()) != GLEW_OK) { //Initialize GLEW library
		fprintf(stderr, "Can't initialize GLEW: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}
	

	initOpenGLProgram(window); //Call initialization procedure
	//Pipeline::getInstance()->worldSize();
	//Main application loop
	glfwSetTime(0);
	while (!glfwWindowShouldClose(window)) //As long as the window shouldnt be closed yet...
	{		
		float dT = glfwGetTime();
		glfwSetTime(0);
		Pipeline::getInstance()->proccesColisions();
		Pipeline::getInstance()->proccesKeyinput();
		Pipeline::getInstance()->processPhysics(dT);
		drawScene(window,dT);
		glfwPollEvents(); //Process callback procedures corresponding to the events that took place up to now
	}
	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Delete OpenGL context and the window.
	glfwTerminate(); //Free GLFW resources
	exit(EXIT_SUCCESS);
}
