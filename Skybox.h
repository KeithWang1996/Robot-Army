#ifndef SKYBOX_H
#define SKYBOX_H

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
// Use of degrees is deprecated. Use radians instead.
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <math.h>
using namespace std;
class Skybox 
{
public:
    unsigned int textureID;
	int width, height;
	GLuint VBO, VAO, EBO;
	GLuint uProjection, uModelview, uModel;

	const GLfloat vertices[8][3] = {
		// "Front" vertices
		-5000.0, -5000.0,  5000.0, 5000.0, -5000.0,  5000.0, 5000.0,  5000.0,  5000.0, -5000.0,  5000.0,  5000.0,
		// "Back" vertices
		-5000.0, -5000.0, -5000.0, 5000.0, -5000.0, -5000.0, 5000.0,  5000.0, -5000.0, -5000.0,  5000.0, -5000.0
	};

	const GLuint indices[6][6] = {
		
		// Front face
		{ 0, 3, 2, 2, 1, 0 },
		// Top face
		{ 1, 2, 6, 6, 5, 1 },
		// Back face
		{ 7, 4, 5, 5, 6, 7 },
		// Bottom face
		{ 4, 7, 3, 3, 0, 4 },
		// Left face
		{ 4, 0, 1, 1, 5, 4 },
		// Right face
		{ 3, 7, 6, 6, 2, 3 }
		
		/*
		{ 0, 1, 2, 2, 3, 0 },
		// Top face
		{ 1, 5, 6, 6, 2, 1 },
		// Back face
		{ 7, 6, 5, 5, 4, 7 },
		// Bottom face
		{ 4, 0, 3, 3, 7, 4 },
		// Left face
		{ 4, 5, 1, 1, 0, 4 },
		// Right face
		{ 3, 2, 6, 6, 7, 3 }
		*/
	};

	glm::mat4 toWorld;
	glm::mat4 modelview;
	glm::vec3 axis;
	glm::vec3 xaxis;
	glm::vec3 yaxis;
	glm::vec3 curr;
	glm::vec3 prev;
	GLfloat vel;
	Skybox(const vector<char *> filepath);
	void parse(const vector<char *> filepath);
	unsigned char* loadPPM(const char* filename, int& width, int& height);
	void draw(GLuint);
	void update();
	void spin(GLfloat deg);
	glm::mat4 rotate();
};

#endif
