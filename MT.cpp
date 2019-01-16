#include "MT.h"
#include "Window.h"
MT::MT(glm::mat4 I)
{
	M = I;
	N = I;
	origin = glm::vec3(0.0f, 0.0f, 0.0f);
	radius = 0.0f;
	iradius = 0.0f;
}

void MT::draw(GLuint shaderProgram) {
	for (std::list<Node *>::iterator iter = children.begin(); iter != children.end(); iter++) {
		(*iter)->draw(shaderProgram);
	}
}

void MT::update(glm::mat4 C) {
	M = C*M;
	for (int i = 0; i < 3; i++) {
		origin[i] = M[3][i];
	}
	radius = iradius*M[0][0];
}

void MT::passing(glm::mat4 I) {
	N = I*M;
	for (std::list<Node *>::iterator iter = children.begin(); iter != children.end(); iter++) {
		(*iter)->passing(N);
	}
}

void MT::addChild(Node *child) {
	children.push_back(child);
}

void MT::removeChild() {
	children.pop_back();
}

bool MT::culling(glm::mat4 P, glm::mat4 V) {
	bool toreturn = true;

	glm::vec4 ndcorigin = P*V*N*glm::vec4(origin, 1);
	ndcorigin = ndcorigin/(ndcorigin.w);
	glm::mat4 inverseCameraRotation = V; 
	inverseCameraRotation[3] = glm::vec4(0, 0, 0, 1);
	glm::mat4 cameraRotation = glm::transpose(inverseCameraRotation);
	for (int i = 0; i < 6; i++) {
		glm::vec4 axis = cameraRotation * glm::vec4(planesNormals[i], 0);
		glm::vec4 theOtherSideInWorld = glm::vec4(origin, 1) + axis * radius;
		glm::vec4 theOtherSide = P*V*N*theOtherSideInWorld;
		theOtherSide = theOtherSide/(theOtherSide.w);
		float radius_in_NDC = glm::length(theOtherSide - ndcorigin);
		glm::vec4 w = glm::vec4(glm::vec3(ndcorigin) - planesPoints[i], 0);
		GLfloat distance = glm::dot(glm::vec4(planesNormals[i], 0), w)/glm::length(glm::vec4(planesNormals[i], 0));
		if (distance < -radius_in_NDC) toreturn = false;
	}
	
	return toreturn;
}

MT::~MT()
{
}
