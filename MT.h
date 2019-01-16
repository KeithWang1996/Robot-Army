#ifndef _MT_H_
#define _MT_H_
#include "Group.h"
#include <iostream>

class MT: public Group
{
public:
	glm::mat4 M;
	glm::mat4 N;
	glm::vec3 origin;
	GLfloat radius;
	GLfloat iradius;
	MT(glm::mat4 I);
	~MT();
	void update(glm::mat4 C);
	void passing(glm::mat4 I);
	void draw(GLuint shaderProgram);
	void addChild(Node *child);
	void removeChild();
	bool culling(glm::mat4 P, glm::mat4 V);
	const glm::vec3 planesNormals[6] =
	{
		glm::vec3(0, 0, -1),
		glm::vec3(0, 0, 1),
		glm::vec3(0, -1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(-1, 0, 0),
		glm::vec3(1, 0, 0)
	};

	const glm::vec3 planesPoints[6] =
	{
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, -1),
		glm::vec3(0, 1, 0),
		glm::vec3(0, -1, 0),
		glm::vec3(1, 0, 0),
		glm::vec3(-1, 0, 0)
	};
};
#endif
