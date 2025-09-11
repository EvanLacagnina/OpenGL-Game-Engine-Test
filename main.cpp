#include "Renderer.h"
#include "Object.h"
#include "Cube.h"
#include "Texture.h"
#include "Plane.h"
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
//#include "Window.h"


//extern struct Window window;

int main() {

	std::vector<float> cubeVertices = {
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 2.0f,  1.0f, // 00
		-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 3.0f, 1.0f, // 01
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 2.0f,  2.0f,  // 02
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 3.0f, 2.0f,  // 03
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // 04
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 2.0f,  0.0f,  // 05
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 2.0f,  4.0f,  // 06
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 3.0f, 0.0f,  // 07
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 4.0f,  1.0f, // 08
		 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 3.0f, 4.0f,  // 09
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 2.0f,  3.0f, // 10
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f,  // 11
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 4.0f,  2.0f,  // 12
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 3.0f, 3.0f, // 13
	};

	std::vector<unsigned int> indices = {
		2, 0, 1,
		2, 1, 3,

		4, 0, 11,
		11, 0, 2,

		0, 5, 7,
		0, 7, 1,

		3, 1, 8,
		3, 8, 12,

		10, 2, 3,
		10, 3, 13,

		6, 10, 13,
		6, 13, 9
	};

	std::vector<float> planeVertices = {
		-0.5f, 0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // 0 pos pos pos color color color texCoord texCoord normal normal normal
		-0.5f, 0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 5.0f, // 1
		 0.5f, 0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 5.0f, 0.0f, // 2
		 0.5f, 0.0f,  0.5f, 1.0f, 1.0f, 1.0f, 5.0f, 5.0f  // 3
	};


	std::vector<unsigned int> planeIndices = {
		1, 2, 0,
		3, 2, 1
	};

	//Object cube = Object(cubevertices, 0, 0, 0, 0, 0, 0, "Untitled.jpg");

	GLFWwindow* window = Renderer::init();

	unsigned int tileTexture = Texture::genTexture("Untitled.jpg");
	//unsigned int cubeTileTexture = Texture::genTexture("cubeTileTexture.jpg");
	unsigned int brickTexture = Texture::genTexture("Brick.png");
	unsigned int ceilingTileTexture = Texture::genTexture("Ceiling Tile.png");
	unsigned int woodTexture = Texture::genTexture("Wood.png");
	//unsigned int cubeWoodTexture = Texture::genTexture("cubeWoodTexture.jpg");
	unsigned int redTexture = Texture::genTexture("Red.png");
	unsigned int greenTexture = Texture::genTexture("Green.png");
	unsigned int blueTexture = Texture::genTexture("Blue.png");

	//objs.push_back(Cube(glm::vec3(1.1f, 0.8f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(100.0f, 100.0f, 100.0f), tileTexture));                                       

	new Plane(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), tileTexture, 0.5, 128);
	new Plane(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), tileTexture, 0.5, 128);
	new Plane(glm::vec3(10.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), tileTexture, 0.5, 128);
	new Plane(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), tileTexture, 0.5, 128);
	

	new Plane(glm::vec3(15.0f, 5.0f, 0.0f), glm::vec3(0.0f, -90.0f, -90.0f), glm::vec3(10.0f, 10.0f, 10.0f), brickTexture, 0.0f, 0.0f);
	new Plane(glm::vec3(15.0f, 5.0f, 10.0f), glm::vec3(0.0f, -90.0f, -90.0f), glm::vec3(10.0f, 10.0f, 10.0f), brickTexture, 0.0f, 0.0f);

	new Plane(glm::vec3(10.0f, 5.0f, 15.0f), glm::vec3(90.0f, 180.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), brickTexture, 0.0f, 0.0f);
	new Plane(glm::vec3(0.0f, 5.0f, 15.0f), glm::vec3(90.0f, 180.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), brickTexture, 0.0f, 0.0f);

	new Plane(glm::vec3(-5.0f, 5.0f, 10.0f), glm::vec3(0.0f, 90.0f, 90.0f), glm::vec3(10.0f, 10.0f, 10.0f), brickTexture, 0.0f, 0.0f);
	new Plane(glm::vec3(-5.0f, 5.0f, 0.0f), glm::vec3(0.0f, 90.0f, 90.0f), glm::vec3(10.0f, 10.0f, 10.0f), brickTexture, 0.0f, 0.0f);

	new Plane(glm::vec3(0.0f, 5.0f, -5.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), brickTexture, 0.0f, 0.0f);
	new Plane(glm::vec3(10.0f, 5.0f, -5.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), brickTexture, 0.0f, 0.0f);

	new Plane(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(180.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), ceilingTileTexture, 0.0f, 0.0f);
	new Plane(glm::vec3(10.0f, 10.0f, 0.0f), glm::vec3(180.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), ceilingTileTexture, 0.0f, 0.0f);
	new Plane(glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(180.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), ceilingTileTexture, 0.0f, 0.0f);
	new Plane(glm::vec3(0.0f, 10.0f, 10.0f), glm::vec3(180.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), ceilingTileTexture, 0.0f, 0.0f);

	new Cube(glm::vec3(10.0f, 1.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.25f, 2.0f, 0.25f), woodTexture, 0.3f, 16);
	new Cube(glm::vec3(14.0f, 1.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.25f, 2.0f, 0.25f), woodTexture, 0.15f, 16);
	new Cube(glm::vec3(14.0f, 1.0f, 12.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.25f, 2.0f, 0.25f), woodTexture, 0.15f, 16);
	new Cube(glm::vec3(10.0f, 1.0f, 12.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.25f, 2.0f, 0.25f), woodTexture, 0.15f, 16);
	new Cube(glm::vec3(12.0f, 2.0f, 11.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.0f, 0.25f, 3.0f), woodTexture, 0.15f, 16);

	new Plane(glm::vec3(12.0f, 2.13f, 11.0f), glm::vec3(0.0f, 36.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), tileTexture, 0.2f, 28);

	new Cube(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.1f, 0.1f), redTexture, 0.0f, 0.0f);
	new Cube(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 2.0f, 0.1f), greenTexture, 0.0f, 0.0f);
	new Cube(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.1f, 2.0f), blueTexture, 0.0f, 0.0f);

	new Cube(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), tileTexture, 1.0f, 256);


	new Cube(glm::vec3(10.0f, 2.325f, 10.5f), glm::vec3(0.0f, 24.0f, 0.0f), glm::vec3(0.4f, 0.4f, 0.4f), tileTexture, 0.4f, 16);
	new Cube(glm::vec3(10.05f, 2.725f, 10.43f), glm::vec3(0.0f, -13.0f, 0.0f), glm::vec3(0.4f, 0.4f, 0.4f), tileTexture, 0.4f, 16);

	//Cube(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), tileTexture);

	//new PointLight(cubeVertices, indices, glm::vec3(7.0f, 1.0f, 3.0f), glm::vec3(30.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), tileTexture, glm::vec3(1.0f, 1.0f, 1.0f), 30); // Color: 1.0f, 1.0f, 0.5f
	//new PointLight(cubeVertices, indices, glm::vec3(-2.0f, 3.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), tileTexture, glm::vec3(1.0f, 1.0f, 1.0f), 3); // Color: 1.0f, 1.0f, 0.5f
	//new PointLight(cubeVertices, indices, glm::vec3(10.05f, 3.125f, 10.43f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.4f, 0.4f, 0.4f), tileTexture, glm::vec3(1.0f, 1.0f, 1.0f), 10); // Color: 1.0f, 1.0f, 0.5f
	//
	//new PointLight(cubeVertices, indices, glm::vec3(1.0f, 2.0f, 11.73205080757f), glm::vec3(0.0f, -30.0f, 0.0f), glm::vec3(0.4f, 0.4f, 0.4f), redTexture, glm::vec3(1.0f, 0.0f, 0.0f), 10); // Color: 1.0f, 1.0f, 0.5f
	//new PointLight(cubeVertices, indices, glm::vec3(0.0f, 2.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.4f, 0.4f, 0.4f), greenTexture, glm::vec3(0.0f, 1.0f, 0.0f), 10); // Color: 1.0f, 1.0f, 0.5f
	//new PointLight(cubeVertices, indices, glm::vec3(-1.0f, 2.0f, 11.73205080757f), glm::vec3(0.0f, 30.0f, 0.0f), glm::vec3(0.4f, 0.4f, 0.4f), blueTexture, glm::vec3(0.0f, 0.0f, 1.0f), 10); // Color: 1.0f, 1.0f, 0.5f

	new DirectionalLight(planeVertices, planeIndices, glm::vec3(30.0f, 20.0f, 30.0f), glm::vec3(220.0f, 0.0f, -40.0f), glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(10.0f, 50.0f, 10.0f), tileTexture, glm::vec3(1.0f, 1.0f, 1.0f), 0.5f);

	
	if(window != NULL){
		Renderer::render(window);
	}
	
	return 0;
}