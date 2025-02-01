#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "stb_image.h"
#include "Renderer.h"

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

void processInput(GLFWwindow* window) { // Function to process input

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
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe - (side (it is in 3d), draw as lines)
		glfwSetWindowTitle(window, "Wireframe");
		//std::cout << "M\n";
	}
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		glfwGetWindowPos(window, &x, &y);
		glfwSetWindowPos(window, 0, y - 1);
		//std::cout << "M\n";
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		glfwGetWindowPos(window, &x, &y);
		glfwSetWindowPos(window, 0, y + 1);
		//std::cout << "M\n";
	}
	else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_RELEASE) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glfwSetWindowTitle(window, "Last Time");
	}

}

GLFWwindow* Renderer::init() {

	stbi_set_flip_vertically_on_load(true);

	glfwInit(); // Initialize glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // GL V3.3 - if the user does not have the proper OpenGL version, GLFW won't even run
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Core profile set
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For Mac


	GLFWwindow* window = glfwCreateWindow(800, 800, "Last Time", NULL, NULL); // Creates a pointer to a 
	//window called 'window' with a width of 800 & a height of 600 called "Last Time"
	if (window == NULL) { // If the window pointer was never set (no window created)
		std::cout << "ERROR: GLFW window creation failed\n";
		glfwTerminate(); // Stops glfw
		return NULL;
	}
	glfwMakeContextCurrent(window); // Sets the current context (where our code will run) to the window

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // We give GLAD function to load address of OpenGL function pointers - GLFW does this with glfwGetProcAddress
		std::cout << "ERROR: Failed to initialize GLAD\n";
		return NULL;
	}

	glViewport(0, 0, 800, 800); // Creates a viewport (place to do the graphics in) at (0, 0) with width 800 and height 600

	void framebuffer_size_callback(GLFWwindow * window, int width, int height); // Declares a function to resize viewport every time window size is changed


	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Calls our function every time the window size changes - passes in reference to that block of code (function) for the glfw function to call

	glfwSetScrollCallback(window, scroll_callback);

	glfwSetCursorPosCallback(window, cursor_position_callback);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	return window;
}

int Renderer::render(GLFWwindow* window, std::vector<Object> objects)
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
	unsigned int indicies[] = {
		0, 0, 0
	};
	glm::vec3 cubePositions[] = {
		glm::vec3( 1.1f,  0.8f, -1.0f),
		glm::vec3(-1.0f,  1.3f, -1.5f),
		glm::vec3(-2.4f, -2.1f, -3.6f),
		glm::vec3(-2.1f,  2.7f, -3.3f),
		glm::vec3( 3.2f, -1.4f, -4.5f),
		glm::vec3( 2.1f, -4.1f, -5.9f),
		glm::vec3(-2.5f,  2.4f, -6.0f),
		glm::vec3( 5.6f, -3.5f, -8.9f),
		glm::vec3(-2.7f,  1.2f, -10.2f),
		glm::vec3( 4.6f, -3.6f, -10.9f)
	};


	//float texCoords[] = { // (s, t, r) axes = (x, y, z) axes - usually only (s, t) axes
	//	0.0f, 0.0f, // Lower-left corner
	//	1.0f, 0.0f, // Lower-right corner
	//	0.5f, 1.0f  // Top-center corner
	//};



	// What if coords outside range?

	// GL_REPEAT - repeats texture - DEFAULT
	// GL_MIRRORED_REPEAT - same as GL_REPEAT but mirrored each repeat
	// GL_CLAMP_TO_EDGE - further coords become whatever the nearest edge is - stretched edge pattern
	// GL_CLAMP_TO_BORDER - User specified border color everything is set to
	// Change these with glTexParameteri(target, option/axis, mode)
	// ex: glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // sets a 2d texture's wrapping on the s (x) axis to 'clamp to edge'
	// Check Khronos documentation for all versions

	// FILTERING
	// GL_NEAREST - aka nearest-neighbor/point filtering - pixelated
	// GL_LINEAR - aka bilinear filtering - 2000's video game style (blurred)
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // Sets filtering to nearest-neighbor FOR MINIFYING THE IMAGE

	//                                                                                                            __________________________________
	// MIPMAPS                                                                                                   |                      |           |
	// If we have faraway textures, we don't need them to have the same resolution as the near ones              |                      |   |\ /|   |
	// We can have a series of textures in which each one is twice as small (1/4 the area ) of the last          |      |\      /|      |   | V |   |
	// It would be annoying to do this manually                                                                  |      | \    / |      |           |
	// We can do glGenerateMipmaps() to do this for us                                                           |      |  \  /  |      |-----------'
	//                                                                                                           |      |   \/   |      |  M  |
	//                                                                                                           |                      |_____|
	//                                                                                                           |                      |__|   
	//                                                                                                           |______________________|-'

	// We can filter in between mipmaps via: glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);


	// LOADING TEXTURES

	// To load textures, we will use stb_image.h - This allows us to use many formats and so we don't have to code an image loader


	

	/*
	glGenTextures(1, &texture2);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	data = stbi_load("Untitled.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	*/
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Bind EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW); // Set buffer data - ONLY INDEX DATA


	// Now, we need to create a vertex buffer object (VBO)
	// Stores all vertex data in an array - makes it so we can send it to the GPU (shaders) all at once - faster
	// Not a "real object" - an OpenGL object - a buffer or array


	unsigned int VBO; // VBO ID
	glGenBuffers(1, &VBO); // Generates the OpenGL object as a buffer

	// Generating VAO

	unsigned int VAO;
	glGenVertexArrays(1, &VAO); // Generate Buffer
	glBindVertexArray(VAO); // Binds VAO to current context



	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Binds VBO to current context - we can bind multiple buffers as long as they are of a separate type
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copies vertex data into the buffer's memory
	// GL_STREAM_DRAW - Data set once and only used once
	// GL_STATIC_DRAW - Data set once used many times
	// GL_DYNAMIC_DRAW - Data changed a lot and used many times


	// SHADER

	Shader shader("vertex.glsl", "fragment.glsl");






	// LINKING VERTEX ATTRIBUTES

	// We can format our VBO however we want - means more flexibility, but we also need to tell OpenGL how we formatted it
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//Parameter 1: Specifies which attribute we are configuring - in our vertex shader, we said: layout (location = 0), specifying that 0 is the location attribute
	//Parameter 2: Specifies size of attribute - 3 values
	//Parameter 3: Type of data
	//Parameter 4: Says if we want to normalize these values (such as an integer representing color values), but our coordinates are already normalized
	//Parameter 5: Stride - space between each vertex attribute - length of a vertex - ours is 3 floats
	//Parameter 6: Of type void* - offset of where data begins in buffer

	// When calling glVertexAttribPointer, it depends on which buffer is bound to GL_ARRAY_BUFFER (you can only have one of each type)

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // Textures
	glEnableVertexAttribArray(2);
	// We have to do ALL of this (bindBuffer, bufferData, vertexAttribPointer, enableVertexAttribArray, useProgram, draw stuf)
	// EACH time we want to draw ONE object (and call vertexAttribPointer for each attribute)

	// Easier solution? - YES - store these state configurations


	// VERTEX ARRAY OBJECT (VAO)
	// Can be bound like a vertex buffer object
	// Any subsequent vertex attrib calls will be stored in the VAO
	// You only need to configure vertex attrib pointers once
	// Whenever we want to draw the current object, we just bind the corresponding VAO
	// Stores:
	// - Calls to glEnable/Disable VertexAttribArray
	// - Vertex attrib configurations via glVertexAttribPointer
	// - VBOs associated w/ vertex atribs by calls to glVertexAttribPointer



	/*
	ELEMENT BUFFER OBJECT (EBO)

	- We want to draw a rectangle - two triangles
	- W/out an EBO, we define two separate triangles - this means we re-define TWO vertices - 50% overhead
	- VBO stores ONLY UNIQUE vertices - EBO stores ONLY the ORDER IN WHICH WE WOULD LIKE TO DRAW THEM

	*/



	/*float timeValue;
	float redValue;
	float greenValue;
	float blueValue;
	int vertexColorLocation;*/

	float count = 0;

	shader.use();
	glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0); // manually
	//shader.setInt("texture2", 1); // or with shader class
	//shader.setFloat("mix", 0.5);

	glm::mat4 ID = glm::mat4(1.0f);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	model = ID;

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
	//view = ID;

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

	//int rainbowEnd = sizeof(vertices) / sizeof(float);



	yScroll = 0.0f;

	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	float horizontalAspect = windowWidth / windowHeight;

	float diagonalAspect = sqrt(horizontalAspect * horizontalAspect + 1);

	float theta = 0.0f;

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) // Keeps window open until glfw says it should close
	{


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


		/*
		for (int i = 0; i < sizeof(vertices) / sizeof(float); i++) {
			std::cout << vertices[i] << ", ";
			if ((i + 1) % 8 == 0) {
				std::cout << "\n";
			}
		}
		*/

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
		//angle += angVel;
		//std::cout << angVel << "\n";


		//count += angVel * 0.1f;
		//transform = glm::rotate(transform, 0.001f * angVel, glm::vec3(0.0f, 0.0f, 1.0f));

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			cameraZ += cameraSpeed * cos(cameraThetaY) * tDiff * cos(cameraThetaX);
			cameraX += cameraSpeed * cos(cameraThetaY) * tDiff * sin(cameraThetaX);
			cameraY += cameraSpeed * tDiff * sin(cameraThetaY);
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			cameraZ -= cameraSpeed * cos(cameraThetaY) * tDiff * cos(cameraThetaX);
			cameraX -= cameraSpeed * cos(cameraThetaY) * tDiff * sin(cameraThetaX);
			cameraY -= cameraSpeed * tDiff * sin(cameraThetaY);
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			cameraZ += cameraSpeed * tDiff * sin(-cameraThetaX);
			cameraX += cameraSpeed * tDiff * cos(-cameraThetaX);
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			cameraZ -= cameraSpeed * tDiff * sin(-cameraThetaX);
			cameraX -= cameraSpeed * tDiff * cos(-cameraThetaX);
		}

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && esc) {
			cursorLock = !cursorLock;
			esc = false;
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE && !esc) {
			esc = true;
		}

		/*if (glfwGetKey(window, GLFW_MOUSE_) == GLFW_PRESS) {
			FOV += 3.0 * tDiff;
		} else if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
			FOV -= 3.0 * tDiff;
		}*/

		cameraSpeed += 1 * yScroll;

		if (cursorLock) {
			cameraThetaX += 0.5 * (mouseX - (windowWidth / 2)) * tDiff;
			cameraThetaY += 0.5 * (mouseY - (windowHeight / 2)) * tDiff;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}


		/*
		if (FOV > 160) {
			FOVDir = -1;
		}
		else if (FOV < 8) {
			FOVDir = 1;
		}
		*/

		//FOV += FOVDir * 30 * tDiff;

		//std::cout << FOV << "\n";

		if (yScroll != 0) {
			yScroll = 0.0f;
		}
		/*
		d = -w / (tan(glm::radians(FOV / 2)));

		if (d > -0.78f) {
			d = -0.78f;
		}
		*/
		angVel = 0.5f;


		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
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
		}

		//  // 

		projection = glm::perspective(glm::radians(45.0f), ((float)windowWidth) / windowHeight, 0.01f, 500.0f);


		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		
		//vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor"); // Querys location of our uniform (in memory)


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Bind EBO
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW); // Set buffer data - ONLY INDEX DATA

		glBindBuffer(GL_ARRAY_BUFFER, VBO); // Binds VBO to current context - we can bind multiple buffers as long as they are of a separate type
		//glBufferData(GL_ARRAY_BUFFER, objects.at(0).getNumVertices() * sizeof(float), vertices, GL_STATIC_DRAW); // Copies vertex data into the buffer's memory


		//processInput(window); // Calls our process input loop

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Sets the color we will clear to - classis OpenGL color EVERY TUTORIAL USES FOR SOME REASON - state-setting function
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clears the color and sets it to out prevoiusly specified color - state-using function - uses current state to retrieve color

		shader.use();
		//glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f); // Set uniform value
		// glUniform has prefixes for each type of value
		// f  - float
		// i  - int
		// ui - unsigned int
		// 3f - 3 floats
		// 4f - 4 floats
		// fv - float vector/array
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, texture2);


		//glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		

		if (cursorLock) {

			glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
		}

		for (int i = 0; i < objects.size(); i++) {

			//std::cout << "0: " << objects.at(i).getVertices()[1] << "\n";

			//float* test = &objects.at(i).getVertices()[0];

			
			//glGenBuffers(1, &VBO); // Generates the OpenGL object as a buffer

			//glBindBuffer(GL_ARRAY_BUFFER, objects.at(i).getVBO()); // Binds VBO to current context - we can bind multiple buffers as long as they are of a separate type
			glBufferData(GL_ARRAY_BUFFER, objects.at(i).getVertices().size() * sizeof(float), &objects.at(i).getVertices()[0], GL_STATIC_DRAW); // Copies vertex data into the buffer's memory

			glBindVertexArray(VAO); // Binds VAO
			// Render stuf ici

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

			//glBindBuffer(GL_ARRAY_BUFFER, VBO);
			//glBufferData(GL_ARRAY_BUFFER, objects.at(i).getNumVertices() * sizeof(float), objects.at(i).getVertices(), GL_STATIC_DRAW);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, objects.at(i).getTexture());

			

			//std::cout << "(" << cameraX << ", " << cameraY << ", " << cameraZ << ")\n";

			model = objects.at(i).updateModel(glm::vec3(cameraX, cameraY, cameraZ));

			

			view = glm::rotate(ID, -cameraThetaX, glm::vec3(0.0f, 1.0f, 0.0f));
			view = glm::rotate(view, cameraThetaY, glm::vec3(cos(-cameraThetaX), 0.0f, sin(-cameraThetaX)));

			shader.setMat4("model", model);
			shader.setMat4("view", view);



			glDrawArrays(GL_TRIANGLES, 0, objects.at(i).getNumVertices());
		}

		glfwSwapBuffers(window); // Swaps buffers (double buffer)
		glfwPollEvents(); // Checks if anything is happening

	}

	glfwTerminate();

	return 0;
}