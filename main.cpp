#include "Renderer.h"
#include "Object.h"
#include "Cube.h"
#include "Texture.h"
#include "Plane.h"


int main() {


	//Object cube = Object(cubevertices, 0, 0, 0, 0, 0, 0, "Untitled.jpg");

	std::vector<Object> objs;

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

	objs.push_back(Plane(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), tileTexture));
	objs.push_back(Plane(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), tileTexture));
	objs.push_back(Plane(glm::vec3(10.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), tileTexture));
	objs.push_back(Plane(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), tileTexture));

	objs.push_back(Plane(glm::vec3(15.0f, 5.0f, 0.0f), glm::vec3(0.0f, -90.0f, -90.0f), glm::vec3(10.0f, 10.0f, 10.0f), brickTexture));
	objs.push_back(Plane(glm::vec3(15.0f, 5.0f, 10.0f), glm::vec3(0.0f, -90.0f, -90.0f), glm::vec3(10.0f, 10.0f, 10.0f), brickTexture));

	objs.push_back(Plane(glm::vec3(10.0f, 5.0f, 15.0f), glm::vec3(90.0f, 180.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), brickTexture));
	objs.push_back(Plane(glm::vec3(0.0f, 5.0f, 15.0f), glm::vec3(90.0f, 180.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), brickTexture));

	objs.push_back(Plane(glm::vec3(-5.0f, 5.0f, 10.0f), glm::vec3(0.0f, 90.0f, 90.0f), glm::vec3(10.0f, 10.0f, 10.0f), brickTexture));
	objs.push_back(Plane(glm::vec3(-5.0f, 5.0f, 0.0f), glm::vec3(0.0f, 90.0f, 90.0f), glm::vec3(10.0f, 10.0f, 10.0f), brickTexture));

	objs.push_back(Plane(glm::vec3(0.0f, 5.0f, -5.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), brickTexture));
	objs.push_back(Plane(glm::vec3(10.0f, 5.0f, -5.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), brickTexture));

	objs.push_back(Plane(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(180.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), ceilingTileTexture));
	objs.push_back(Plane(glm::vec3(10.0f, 10.0f, 0.0f), glm::vec3(180.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), ceilingTileTexture));
	objs.push_back(Plane(glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(180.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), ceilingTileTexture));
	objs.push_back(Plane(glm::vec3(0.0f, 10.0f, 10.0f), glm::vec3(180.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 10.0f), ceilingTileTexture));

	objs.push_back(Cube(glm::vec3(10.0f, 1.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.25f, 2.0f, 0.25f), woodTexture));
	objs.push_back(Cube(glm::vec3(14.0f, 1.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.25f, 2.0f, 0.25f), woodTexture));
	objs.push_back(Cube(glm::vec3(14.0f, 1.0f, 12.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.25f, 2.0f, 0.25f), woodTexture));
	objs.push_back(Cube(glm::vec3(10.0f, 1.0f, 12.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.25f, 2.0f, 0.25f), woodTexture));
	objs.push_back(Cube(glm::vec3(12.0f, 2.0f, 11.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.0f, 0.25f, 3.0f), woodTexture));

	objs.push_back(Plane(glm::vec3(12.0f, 2.13f, 11.0f), glm::vec3(0.0f, 36.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), tileTexture));

	objs.push_back(Cube(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 0.1f, 0.1f), redTexture));
	objs.push_back(Cube(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 2.0f, 0.1f), greenTexture));
	objs.push_back(Cube(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.1f, 2.0f), blueTexture));

	objs.push_back(Cube(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), tileTexture));
	;

	if(window != NULL){
		Renderer::render(window, objs);
	}
	return 0;
}