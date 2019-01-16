#ifndef _GROUP_H_
#define _GROUP_H_
#include "Node.h"
#include <list>

class Group: public Node
{
public:
	Group();
	~Group();
	std::list<Node*> children;
	virtual void addChild(Node *child) = 0;
	virtual void removeChild() = 0;
	virtual void update(glm::mat4 C) = 0;
	virtual void draw(GLuint shaderProgram) = 0;
	virtual bool culling(glm::mat4 P, glm::mat4 V) = 0;
};
#endif
