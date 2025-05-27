#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "stb_image.h"
#include "Renderer.h"
#include "Light.h"

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

float yScroll;
float mouseX;
float mouseY;

glm::mat4 Renderer::ID = glm::mat4(1.0f);

void getColor(float count, float vertices[], int len) {
	
	float red;
	float green;
	float blue;
	if (count >= 0 && count < 255) {
		red = 1.0;
		green = count / 255;
		blue = 0;
	}
	else if (count >= 255 && count < 510) {
		red = (-count + 510) / 255;
		green = 1.0;
		blue = 0;
	}
	else if (count >= 510 && count < 765) {
		red = 0.0;
		green = 1.0;
		blue = (count - 510) / 255;
	}
	else if (count >= 765 && count < 1020) {
		red = 0.0;
		green = (-count + 1020) / 255;
		blue = 1.0;
	}
	else if (count >= 1020 && count < 1275) {
		red = (count - 1020) / 255;
		green = 0.0;
		blue = 1.0;
	}
	else {
		red = 1.0;
		green = 0.0;
		blue = (-count + 1530) / 255;
	}

	for (int i = 0; i < len / 8; i++) {
		int index = i * 8;
		vertices[index + 3] = red;
		vertices[index + 4] = green;
		vertices[index + 5] = blue;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xOff, double yOff) {
	yScroll = yOff;
}

void cursor_position_callback(GLFWwindow* window, double xPos, double yPos) {
	mouseX = xPos;
	mouseY = yPos;
}

void processInput(GLFWwindow* window) {

	int x = 0;
	int y = 0;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		glfwSetWindowOpacity(window, 0.5);
		glfwSetWindowTitle(window, "Spooky Ghost Window");
	}
	else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		glfwSetWindowOpacity(window, 1.0);
		glfwSetWindowTitle(window, "Last Time");
	}
	else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		glfwSetWindowOpacity(window, 0.0);
		glfwSetWindowTitle(window, "You Cannot See This Text");
	}
	else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glfwSetWindowTitle(window, "Wireframe");
	}
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		glfwGetWindowPos(window, &x, &y);
		glfwSetWindowPos(window, 0, y - 1);
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		glfwGetWindowPos(window, &x, &y);
		glfwSetWindowPos(window, 0, y + 1);
	}
	else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_RELEASE) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glfwSetWindowTitle(window, "Last Time");
	}

}

GLFWwindow* Renderer::init() {

	stbi_set_flip_vertically_on_load(true);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 800, "Last Time", NULL, NULL); 
	if (window == NULL) { 
		std::cout << "ERROR: GLFW window creation failed\n";
		glfwTerminate(); 
		return NULL;
	}
	glfwMakeContextCurrent(window); 

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { 
		std::cout << "ERROR: Failed to initialize GLAD\n";
		return NULL;
	}

	glViewport(0, 0, 800, 800); 

	void framebuffer_size_callback(GLFWwindow * window, int width, int height);


	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetScrollCallback(window, scroll_callback);

	glfwSetCursorPosCallback(window, cursor_position_callback);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	return window;
}

int Renderer::render(GLFWwindow* window)
{
	


	/*float vertices[] = { // Vertecies for an E in NDC
		/*
		-0.2f,  0.8f, 0.0f, 1.0f, 1.0f, 1.0f, // 0        0____2_______4
		-0.2f, -0.8f, 0.0f, 1.0f, 1.0f, 1.0f, // 1        |            |
		-0.1f,  0.8f, 0.0f, 1.0f, 0.0f, 0.0f, // 2        |    6_______|
		-0.1f, -0.8f, 0.0f, 0.0f, 0.0f, 1.0f, // 3        |    |       5
		 0.2f,  0.8f, 0.0f, 1.0f, 0.0f, 0.0f, // 4        |    |_______8
		 0.2f,  0.6f, 0.0f, 1.0f, 0.0f, 0.0f, // 5        |    7       |
		-0.1f,  0.6f, 0.0f, 1.0f, 0.0f, 0.0f, // 6        |   10_______|
		-0.1f,	0.1f, 0.0f, 0.0f, 1.0f, 0.0f, // 7        |    |        9
		 0.2f,	0.1f, 0.0f, 0.0f, 1.0f, 0.0f, // 8        |    |_______12
		 0.2f, -0.1f, 0.0f, 0.0f, 1.0f, 0.0f, // 9        |   11       |
		-0.1f, -0.1f, 0.0f, 0.0f, 1.0f, 0.0f, // 10      1|____3_______|
		-0.1f, -0.6f, 0.0f, 0.0f, 0.0f, 1.0f, // 11                    13
		 0.2f, -0.6f, 0.0f, 0.0f, 0.0f, 1.0f, // 12
		 0.2f, -0.8f, 0.0f, 0.0f, 0.0f, 1.0f  // 13
		 */
		 // positions       // colors         // texture coords
		 //0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
		 //0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
		//-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // top left
		//-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom left
		/*

		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		///////////////////////

		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

		///////////////////////

		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		///////////////////////

		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		 ///////////////////////

		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

		///////////////////////

		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
	}; */
		



	//unsigned int VBO;
	//glGenBuffers(1, &VBO);

	//unsigned int VAO;
	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);



	//glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);*/

	float count = 0;

	Shader objectShader("vertex.glsl", "objectFragment.glsl");
	Shader lightShader("vertex.glsl", "lightFragment.glsl");

	objectShader.use();
	glUniform1i(glGetUniformLocation(objectShader.ID, "texture1"), 0);
	lightShader.use();
	glUniform1i(glGetUniformLocation(lightShader.ID, "texture1"), 0);

	glm::mat4 ID = glm::mat4(1.0f);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	model = ID;

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 10000.0f);


	float angle = 0;
	float angVel = 0;
	const float friction = 0.001f;

	float lastTime = 0.0f;
	float tDiff = 0.0f;

	float angAccel = 0.9f;

	int frames = 0;
	int avgFrameNum = 4000;
	float avgFPS = 0.0f;
	float tFrames = 0.0f;

	int windowWidth = 0;
	int windowHeight = 0;

	float cameraX = 0;
	float cameraY = 0;
	float cameraZ = 0;
	float cameraSpeed = 3.0f;
	float FOV = 45.0f;

	float w = 4.5f;
	float d;
	float c = 0.0f;

	int FOVDir = -1;

	float cameraThetaY = 0;
	float cameraThetaX = 0;

	bool cursorLock = true;
	bool esc = false;


	yScroll = 0.0f;

	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	float horizontalAspect = windowWidth / windowHeight;

	float diagonalAspect = sqrt(horizontalAspect * horizontalAspect + 1);

	float theta = 0.0f;

	glEnable(GL_DEPTH_TEST);

	glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);

	//(*Light::getLights(0)).setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	//(*Light::getLights(0)).setPos(glm::vec3(cos(lastTime * 10), 3.0f, sin(lastTime * 10)));
	//std::cout << "before setPos\n";
	//std::cout << "after setPos\n";

	
	while (!glfwWindowShouldClose(window))
	{

		//std::cout << (*Light::getLights(0)).getColor().z << "\n";

		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		tDiff = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();

		tFrames += tDiff;
		frames += 1;
		if (frames > avgFrameNum) {
			avgFPS = frames / tFrames;
			std::cout << "Framerate: " << avgFPS << " FPS\n";
			frames = 0;
			tFrames = 0.0f;
		}
		


		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			angVel += angAccel * tDiff;
		}
		else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			angVel -= angAccel * tDiff;
		}
		else if (angVel > 0) {
			angVel -= friction;
		}
		else if (angVel < 0) {
			angVel += friction;
		}
		else if (angVel < friction) {
			angVel = 0;
		}
		if (angVel > 13) {
			angVel = 13;
		}
		else if (angVel < -13) {
			angVel = -13;
		}

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			cameraZ += cameraSpeed * cos(cameraThetaY) * tDiff * cos(-cameraThetaX);
			cameraX += cameraSpeed * cos(cameraThetaY) * tDiff * sin(-cameraThetaX);
			cameraY += cameraSpeed * tDiff * sin(cameraThetaY);
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			cameraZ -= cameraSpeed * cos(cameraThetaY) * tDiff * cos(-cameraThetaX);
			cameraX -= cameraSpeed * cos(cameraThetaY) * tDiff * sin(-cameraThetaX);
			cameraY -= cameraSpeed * tDiff * sin(cameraThetaY);
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			cameraZ += cameraSpeed * tDiff * sin(cameraThetaX);
			cameraX += cameraSpeed * tDiff * cos(cameraThetaX);
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			cameraZ -= cameraSpeed * tDiff * sin(cameraThetaX);
			cameraX -= cameraSpeed * tDiff * cos(cameraThetaX);
		}

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && esc) {
			cursorLock = !cursorLock;
			esc = false;
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE && !esc) {
			esc = true;
		}


		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDisable(GL_CULL_FACE);
		} else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_RELEASE) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_CULL_FACE);
		}


		cameraSpeed += 1 * yScroll;

		if (cursorLock) {
			cameraThetaX += 0.5 * (mouseX - (windowWidth / 2)) * tDiff;
			cameraThetaY += 0.5 * (mouseY - (windowHeight / 2)) * tDiff;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}


		if (yScroll != 0) {
			yScroll = 0.0f;
		}

		angVel = 0.5f;


		/*if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
			cameraThetaX += glm::radians(20.0f) * tDiff;
		}
		else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
			cameraThetaX -= glm::radians(20.0f) * tDiff;
		}
		else if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
			cameraThetaY -= glm::radians(20.0f) * tDiff;
		}
		else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
			cameraThetaY += glm::radians(20.0f) * tDiff;
		}*/



		projection = glm::perspective(glm::radians(45.0f), ((float)windowWidth) / windowHeight, 0.01f, 500.0f);

		objectShader.use();
		glUniformMatrix4fv(glGetUniformLocation(objectShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		lightShader.use();
		glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		

		if (cursorLock) {

			glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
		}

		

		//(*Light::getLights(0)).setPos(glm::vec3(9 * cos(lastTime * 2) + 5, 3 * sin(lastTime * 4) + 4, 9 * sin(lastTime * 2) + 5)); // Change light position
		
		//color = glm::vec3(fmax(fmin(abs((fmod(lastTime, 6)) - 3) - 1, 1.0f), 0.0f), fmax(fmin(-abs(fmod(lastTime, 6) - 2) + 2, 1.0f), 0.0f), fmax(fmin(-abs(fmod(lastTime, 6) - 4) + 2, 1.0f), 0.0f));
		//(*Light::getLights(0)).setColor(color); // Change light color

		
		for (int i = 0; i < Object::getObjects().size(); i++) {

			//glBufferData(GL_ARRAY_BUFFER, objects.at(i).getVertices().size() * sizeof(float), &objects.at(i).getVertices()[0], GL_STATIC_DRAW);
			//glBindVertexArray(VAO);

			//std::cout << "Vertices: " << Object::getObjects(i).getVertices().size() << "\n";

			glBindBuffer(GL_ARRAY_BUFFER, (*Object::getObjects(i)).getVBO());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*Object::getObjects(i)).getEBO());
			glBindVertexArray((*Object::getObjects(i)).getVAO());
			glBufferData(GL_ARRAY_BUFFER, (*Object::getObjects(i)).getVertices().size() * sizeof(float), &Object::getObjects().at(i).getVertices()[0], GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, (*Object::getObjects(i)).getIndices().size() * sizeof(unsigned int), &Object::getObjects().at(i).getIndices()[0], GL_STATIC_DRAW);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, (*Object::getObjects(i)).getTexture());


			model = (*Object::getObjects(i)).updateModel();

			
			view = glm::rotate(ID, cameraThetaX, glm::vec3(0.0f, 1.0f, 0.0f));
			view = glm::rotate(view, cameraThetaY, glm::vec3(cos(cameraThetaX), 0.0f, sin(cameraThetaX)));
			view = glm::translate(view, glm::vec3(cameraX, cameraY, cameraZ));
			
			if (!(*Object::getObjects(i)).getIsLight()) {
				objectShader.use();
				objectShader.setMat4("model", model);
				objectShader.setMat4("view", view);
				//objectShader.setVec3("lightColor", (*Light::getLights(0)).getColor());
				//std::cout << (*Light::getLights(0)).getColor().x << "\n";
				objectShader.setFloatArray("lightRadii", &(Light::getLightRadii()[0]), Light::getLights().size());
				objectShader.setVec3Array("lightPos", &(Light::getLightPos()[0]), Light::getLights().size());
				objectShader.setVec3Array("lightColors", &(Light::getLightColors()[0]), Light::getLights().size());
				objectShader.setInt("numLights", Light::getLights().size());
				objectShader.setVec3("cameraPos", glm::vec3(-cameraX, -cameraY, -cameraZ));
				objectShader.setFloat("specularStrength", (*Object::getObjects(i)).getSpecularStrength());
				objectShader.setFloat("specularExp", (*Object::getObjects(i)).getSpecularExp());
			}
			else {
				lightShader.use();
				lightShader.setMat4("model", model);
				lightShader.setMat4("view", view);
				lightShader.setVec3("lightColor", (*Light::getLights(0)).getColor()); // 
				//std::cout << (*Light::getLights(0)).getColor().x << "\n";
			}
			//objectShader.setVec3("lightPos", (*Light::getLights(0)).getPos());
			//objectShader.setFloat("lightRadius", (*Light::getLights(0)).getRadius());
			



			glDrawElements(GL_TRIANGLES, (*Object::getObjects(i)).getIndices().size(), GL_UNSIGNED_INT, 0);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();

	return 0;
}