#ifndef _GEODE_H_
#define _GEODE_H_
#include "Node.h"
class Geode: public Node
{
public:
	glm::mat4 M;
	Geode();
	~Geode();
	virtual void update(glm::mat4 C) = 0;
	virtual void draw(GLuint shaderProgram) = 0;
};
#endif
