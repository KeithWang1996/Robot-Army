#include "window.h"
#include <list>
#include <time.h>
const char* window_title = "GLFW Starter Project";
Cube * cube;
Light * light;
Light * dirLight;
Light * pointLight;
Light * spotLight;
OBJObject * obj;
OBJObject * bunny;
OBJObject * bear;
OBJObject * dragon;
Geode* head;
Geode* body;
Geode* larm;
Geode* rarm;
Geode* lleg;
Geode* rleg;
Geode* leye;
Geode* reye;
Geode* lant;
Geode* rant;
Geode* sphere;
MT* hmtx;
MT* bmtx;
MT* lamtx;
MT* ramtx;
MT* llmtx;
MT* rlmtx;
MT* lemtx;
MT* remtx;
MT* lnmtx;
MT* rnmtx;
MT* modelmtx;
MT* smtx;
MT* army;
int counter;
int bit;
int walk;
int ball;
int cull;
glm::vec3 gaxis;
glm::vec3 gxaxis;
glm::vec3 gyaxis;

GLfloat gvel;
GLfloat scale;
GLfloat zoom;
Group* satellite;

Skybox * box;
GLint shaderProgram, shaderProgram_sky;

// On some systems you need to change this to the absolute path
#define VERTEX_SHADER_PATH "../shader.vert"
#define FRAGMENT_SHADER_PATH "../shader.frag"
#define VERTEX_SHADER_SKY "../shader-skybox.vert"
#define FRAGMENT_SHADER_SKY "../shader-skybox.frag"


// Default camera parameters
glm::vec3 cam_pos(0.0f, 0.0f, 100.0f);		// e  | Position of camera
glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is
int Window::hold = 0;
int Window::mode = 0;
int Window::light_mode;
int Window::width;
int Window::height;
GLdouble Window::prevx;
GLdouble Window::prevy;
GLdouble Window::currx;
GLdouble Window::curry;
glm::mat4 Window::P;
glm::mat4 Window::V;
std::list<glm::vec3> positions;
std::list<MT*> clones;
void Window::initialize_objects()
{
	
	for (int i = -100; i < 100; i+=20) {
		for (int j = -100; j < 100; j+=20) {
			positions.push_back(glm::vec3(i, 0, j));
		}
	}
	MT* temp;
	for (std::list<glm::vec3>::iterator iter = positions.begin(); iter != positions.end(); iter++) {
		temp = new MT(glm::translate(glm::mat4(1.0f), *iter));
		temp->origin = *iter;
		temp->radius = 57;
		temp->iradius = 57;
		clones.push_back(temp);
	}
	std::vector<char*> faces = std::vector<char*>{
		"city_rt.ppm",
		"city_lf.ppm",
		"city_up.ppm",
		"city_dn.ppm",
		"city_bk.ppm",
		"city_ft.ppm"
	};
	
	box = new Skybox(faces);
	walk = 0;
	counter = 0;
	bit = 0;
	ball = 0;
	scale = 1.1f;
	zoom = 1.1f;
	cull = 0;
	gxaxis = glm::vec3(1, 0, 0);
	gyaxis = glm::vec3(0, 1, 0);
	head = new OBJObject("head.obj");
	body = new OBJObject("body.obj");
	larm = new OBJObject("limb.obj");
	rarm = new OBJObject("limb.obj");
	lleg = new OBJObject("limb.obj");
	rleg = new OBJObject("limb.obj");
	leye = new OBJObject("eyeball.obj");
	reye = new OBJObject("eyeball.obj");
	lant = new OBJObject("antenna.obj");
	rant = new OBJObject("antenna.obj");
	sphere = new OBJObject("sphere.obj");
	sphere->dot = 1;
	hmtx = new MT(glm::mat4(1.0f));
	army = new MT(glm::mat4(1.0f));
	bmtx = new MT(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f)));
	lamtx = new MT(glm::translate(glm::mat4(1.0f), glm::vec3(5.5f, 0.0f, -6.0f))*
		glm::rotate(glm::mat4(1.0f), -15.0f / 180.0f * glm::pi<float>(), glm::vec3(0, 1, 0))*
	    glm::scale(glm::mat4(1.0f), glm::vec3(0.8, 0.8, 1)));
	ramtx = new MT(glm::translate(glm::mat4(1.0f), glm::vec3(-5.5f, 0.0f, -6.0f))*
		glm::rotate(glm::mat4(1.0f), 15.0f / 180.0f * glm::pi<float>(), glm::vec3(0, 1, 0))*
		glm::scale(glm::mat4(1.0f), glm::vec3(0.8, 0.8, 1)));
	llmtx = new MT(glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, -14.0f)));
	rlmtx = new MT(glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, -14.0f)));
	lemtx = new MT(glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, -2.0f, 1.5f)));
	remtx = new MT(glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, -2.0f, 1.5f)));
	lnmtx = new MT(glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 2.0f))*
		glm::rotate(glm::mat4(1.0f), 180.0f / 180.0f * glm::pi<float>(), glm::vec3(0, 0, 1)));
	rnmtx = new MT(glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.0f, 2.0f)));
	smtx = new MT(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -7.0f))*glm::scale(glm::mat4(1.0f), glm::vec3(57, 57, 57)));
	hmtx->addChild(head);
	bmtx->addChild(body);
	lamtx->addChild(larm);
	ramtx->addChild(rarm);
	llmtx->addChild(lleg);
	rlmtx->addChild(rleg);
	lemtx->addChild(leye);
	remtx->addChild(reye);
	lnmtx->addChild(lant);
	rnmtx->addChild(rant);
	smtx->addChild(sphere);
	modelmtx = new MT(glm::mat4(1.0f));
	modelmtx->addChild(hmtx);
	modelmtx->addChild(bmtx);
	modelmtx->addChild(lamtx);
	modelmtx->addChild(ramtx);
	modelmtx->addChild(llmtx);
	modelmtx->addChild(rlmtx);
	modelmtx->addChild(lemtx);
	modelmtx->addChild(remtx);
	modelmtx->addChild(lnmtx);
	modelmtx->addChild(rnmtx);
	modelmtx->update(glm::rotate(glm::mat4(1.0f), -90.0f / 180.0f * glm::pi<float>(), glm::vec3(1, 0, 0)));
	modelmtx->passing(glm::mat4(1.0f));
	
	for (std::list<MT*>::iterator iter = clones.begin(); iter != clones.end(); iter++) {
		(*iter)->addChild(modelmtx);
	}
	
	for (std::list<MT*>::iterator iter = clones.begin(); iter != clones.end(); iter++) {
		army->addChild(*iter);
	}
	

	//army->update(glm::rotate(glm::mat4(1.0f), -90.0f / 180.0f * glm::pi<float>(), glm::vec3(1, 0, 0)));
	//army->passing(glm::mat4(1.0f));
	army->passing(glm::mat4(1.0f));
	
	obj = bunny;
	//light = dirLight;
	// Load the shader program. Make sure you have the correct filepath up top
	shaderProgram = LoadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	shaderProgram_sky = LoadShaders(VERTEX_SHADER_SKY, FRAGMENT_SHADER_SKY);
	//light_mode = 0;
	//Material init
}

// Treat this as a destructor function. Delete dynamically allocated memory here.
void Window::clean_up()
{
	//delete(cube);
	
	delete(bunny);
	delete(box);
	delete(larm);
	delete(rarm);
	delete(head);
	delete(body);
	delete(lleg);
	delete(rleg);
	delete(leye);
	delete(reye);
	delete(lant);
	delete(rant);
	delete(sphere);
	delete(hmtx);
	delete(army);
	delete(bmtx);
	delete(lamtx);
	delete(ramtx);
	delete(llmtx);
	delete(rlmtx);
	delete(lemtx);
	delete(remtx);
	delete(lnmtx);
	delete(rnmtx);
	delete(modelmtx);
	delete(smtx);
	for (std::list<MT*>::iterator iter = clones.begin(); iter != clones.end(); iter++) {
		delete((*iter));
	}
	glDeleteProgram(shaderProgram);
	glDeleteProgram(shaderProgram_sky);
}

GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ // Because Apple hates comforming to standards
	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);
	
	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		fprintf(stderr, "Either GLFW is not installed or your graphics card does not support modern OpenGL.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Get the width and height of the framebuffer to properly resize the window
	glfwGetFramebufferSize(window, &width, &height);
	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	glfwGetFramebufferSize(window, &width, &height); // In case your Mac has a retina display
#endif
	Window::width = width;
	Window::height = height;
	// Set the viewport size. This is the only matrix that OpenGL maintains for us in modern OpenGL!
	glViewport(0, 0, width, height);

	if (height > 0)
	{
		P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 10000.0f);
		V = glm::lookAt(cam_pos, cam_look_at, cam_up);
	}
}

void Window::idle_callback()
{
	if(walk == 1){
		lemtx->update(glm::rotate(glm::mat4(1.0f), 1.0f / 180.0f * glm::pi<float>(), glm::vec3(0, 0, 1)));
		remtx->update(glm::rotate(glm::mat4(1.0f), -1.0f / 180.0f * glm::pi<float>(), glm::vec3(0, 0, 1)));
		lnmtx->update(glm::rotate(glm::mat4(1.0f), -2.0f / 180.0f * glm::pi<float>(), glm::vec3(0, 0, 1)));
		rnmtx->update(glm::rotate(glm::mat4(1.0f), -2.0f / 180.0f * glm::pi<float>(), glm::vec3(0, 0, 1)));
		if (counter == -30) bit = 0;
		else if (counter == 30) bit = 1;
		llmtx->update(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 6.0f)));
		rlmtx->update(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 6.0f)));
		
		if (bit == 0) {
			lamtx->update(glm::rotate(glm::mat4(1.0f), -2.0f / 180.0f * glm::pi<float>(), glm::vec3(1, 0, 0)));
			ramtx->update(glm::rotate(glm::mat4(1.0f), 2.0f / 180.0f * glm::pi<float>(), glm::vec3(1, 0, 0)));
			llmtx->update(glm::rotate(glm::mat4(1.0f), -1.0f / 180.0f * glm::pi<float>(), glm::vec3(1, 0, 0)));
			rlmtx->update(glm::rotate(glm::mat4(1.0f), 1.0f / 180.0f * glm::pi<float>(), glm::vec3(1, 0, 0)));
			counter++;
		}
		else {
			lamtx->update(glm::rotate(glm::mat4(1.0f), 2.0f / 180.0f * glm::pi<float>(), glm::vec3(1, 0, 0)));
			ramtx->update(glm::rotate(glm::mat4(1.0f), -2.0f / 180.0f * glm::pi<float>(), glm::vec3(1, 0, 0)));
			llmtx->update(glm::rotate(glm::mat4(1.0f), 1.0f / 180.0f * glm::pi<float>(), glm::vec3(1, 0, 0)));
			rlmtx->update(glm::rotate(glm::mat4(1.0f), -1.0f / 180.0f * glm::pi<float>(), glm::vec3(1, 0, 0)));
			counter--;
		}
		llmtx->update(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f)));
		rlmtx->update(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f)));
	}
	
	modelmtx->passing(glm::mat4(1.0f));
}

void Window::display_callback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use the shader of programID
	glUseProgram(shaderProgram);
	//modelmtx->draw(shaderProgram);
	//sphere->draw(shaderProgram);
	int counter = 0;
	clock_t c1 = clock();
	for (std::list<Node*>::iterator iter = army->children.begin(); iter != army->children.end(); iter++) {
		if (cull == 1) {
			if (((MT*)*iter)->culling(P, V)) {
				(*iter)->passing(glm::mat4(1.0f));
				army->draw(shaderProgram);
				counter++;
			}
		}
		else {
			(*iter)->passing(glm::mat4(1.0f));
			army->draw(shaderProgram);
		}
	}
	clock_t c2 = clock();

	//std::cout << c2-c1 << std::endl;
	glUseProgram(shaderProgram_sky);
	box->draw(shaderProgram_sky);
	
	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for a key press
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		if (key == GLFW_KEY_F1) {
			obj = bunny;
			dirLight->object_mode = 1;
			pointLight->object_mode = 1;
			spotLight->object_mode = 1;
		}

		if (key == GLFW_KEY_B) {
			if (ball == 0) {
				ball = 1;
				modelmtx->addChild(smtx);
			}
			else {
				ball = 0;
				modelmtx->removeChild();
			}
		}
		if (key == GLFW_KEY_S) {
			if (mods & GLFW_MOD_SHIFT) scale = 1.1;
			else scale = 1 / 1.1;
			for (std::list<MT*>::iterator iter = clones.begin(); iter != clones.end(); iter++) {
				(*iter)->update(glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale)));
			}
		}
		if (key == GLFW_KEY_W) {
			if (mode == 3) {
				if (mods & GLFW_MOD_SHIFT)
					light->cutoff_angle = light->cutoff_angle - 0.0001;
				else
					light->cutoff_angle = light->cutoff_angle + 0.0001;
			}
		}
		if (key == GLFW_KEY_UP) {
			if (mods & GLFW_MOD_SHIFT) {
				gaxis = gxaxis;
				gvel = 2.0f;
				glm::mat4 grotate = glm::rotate(glm::mat4(1.0f), gvel / 180.0f * glm::pi<float>(), gaxis);
				gyaxis = glm::normalize(glm::vec3(grotate*glm::vec4(gyaxis, 0)));
				for (std::list<MT*>::iterator iter = clones.begin(); iter != clones.end(); iter++) {
					(*iter)->update(grotate);
				}
			}
			else {
				box->axis = box->xaxis;
				box->vel = 2.0f;
				cam_pos = glm::vec3(box->rotate()*glm::vec4(cam_pos, 0.0));
				cam_up = glm::normalize(glm::vec3(box->rotate()*glm::vec4(cam_up, 1.0)));
				V = glm::lookAt(cam_pos, cam_look_at, cam_up);
				box->yaxis = glm::normalize(glm::vec3(box->rotate()*glm::vec4(box->yaxis, 0.0)));
			}
		}
		if (key == GLFW_KEY_DOWN) {
			if (mods & GLFW_MOD_SHIFT) {
				gaxis = gxaxis;
				gvel = -2.0f;
				glm::mat4 grotate = glm::rotate(glm::mat4(1.0f), gvel / 180.0f * glm::pi<float>(), gaxis);
				gyaxis = glm::normalize(glm::vec3(grotate*glm::vec4(gyaxis, 0)));
				for (std::list<MT*>::iterator iter = clones.begin(); iter != clones.end(); iter++) {
					(*iter)->update(grotate);
				}
			}
			else {
				box->axis = box->xaxis;
				box->vel = -2.0f;
				cam_pos = glm::vec3(box->rotate()*glm::vec4(cam_pos, 0.0));
				cam_up = glm::normalize(glm::vec3(box->rotate()*glm::vec4(cam_up, 1.0)));
				V = glm::lookAt(cam_pos, cam_look_at, cam_up);
				box->yaxis = glm::normalize(glm::vec3(box->rotate()*glm::vec4(box->yaxis, 0.0)));
			}
		}
		if (key == GLFW_KEY_RIGHT) {
			if (mods & GLFW_MOD_SHIFT) {
				gaxis = gyaxis;
				gvel = -2.0f;
				glm::mat4 grotate = glm::rotate(glm::mat4(1.0f), gvel / 180.0f * glm::pi<float>(), gaxis);
				gxaxis = glm::normalize(glm::vec3(grotate*glm::vec4(gxaxis, 0)));
				for (std::list<MT*>::iterator iter = clones.begin(); iter != clones.end(); iter++) {
					(*iter)->update(grotate);
				}
			}
			else {
				box->axis = box->yaxis;
				box->vel = -2.0f;
				cam_pos = glm::vec3(box->rotate()*glm::vec4(cam_pos, 0.0));
				cam_up = glm::normalize(glm::vec3(box->rotate()*glm::vec4(cam_up, 1.0)));
				V = glm::lookAt(cam_pos, cam_look_at, cam_up);
				box->xaxis = glm::normalize(glm::vec3(box->rotate()*glm::vec4(box->xaxis, 0.0)));
			}
		}
		if (key == GLFW_KEY_LEFT) {
			if (mods & GLFW_MOD_SHIFT) {
				gaxis = gyaxis;
				gvel = 2.0f;
				glm::mat4 grotate = glm::rotate(glm::mat4(1.0f), gvel / 180.0f * glm::pi<float>(), gaxis);
				gxaxis = glm::normalize(glm::vec3(grotate*glm::vec4(gxaxis, 0)));
				for (std::list<MT*>::iterator iter = clones.begin(); iter != clones.end(); iter++) {
					(*iter)->update(grotate);
				}
			}
			else {
				box->axis = box->yaxis;
				box->vel = 2.0f;
				cam_pos = glm::vec3(box->rotate()*glm::vec4(cam_pos, 0.0));
				cam_up = glm::normalize(glm::vec3(box->rotate()*glm::vec4(cam_up, 1.0)));
				V = glm::lookAt(cam_pos, cam_look_at, cam_up);
				box->xaxis = glm::normalize(glm::vec3(box->rotate()*glm::vec4(box->xaxis, 0.0)));
			}
		}
		if (key == GLFW_KEY_M) {
			if (walk == 0) walk = 1;
			else walk = 0;
		}
		if (key == GLFW_KEY_Z) {
			if (mods & GLFW_MOD_SHIFT) zoom = 1.1;
			else zoom = 1 / 1.1;
			cam_pos = glm::vec3(glm::scale(glm::mat4(1.0f), glm::vec3(zoom, zoom, zoom))*glm::vec4(cam_pos, 0));
			V = glm::lookAt(cam_pos, cam_look_at, cam_up);
		}
		if (key == GLFW_KEY_C) {
			if (cull == 0) cull = 1;
			else cull = 0;
		}
		if (key == GLFW_KEY_3) {
			light = spotLight;
			mode = 3;
		}
		if (key == GLFW_KEY_0) {
			mode = 0;
		}
		if (key == GLFW_KEY_N) {
			if (light_mode == 0) {
				light_mode = 1;
				light = dirLight;
			}
			else {
				light_mode = 0;
				if (mode == 2) light = pointLight;
				if (mode == 3) light = spotLight;

			}
		}
	
	}
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			if (mode == 0) {
				hold = 1;
				glfwGetCursorPos(window, &prevx, &prevy);

			}
			else if (mode == 1) {
				hold = 5;
				glfwGetCursorPos(window, &prevx, &prevy);
				light->prev = trackBallMapping(prevx, prevy);
			}
			else if (mode == 2) {
				hold = 6;
				glfwGetCursorPos(window, &prevx, &prevy);
				light->prev = trackBallMapping(prevx, prevy);
			}
			else if (mode == 3) {
				hold = 7;
				glfwGetCursorPos(window, &prevx, &prevy);
				light->prev = trackBallMapping(prevx, prevy);
			}
		}
		else if (action == GLFW_RELEASE) {
			prevx = 0;
			prevy = 0;
			currx = 0;
			curry = 0;
		    //box->temp = obj->rotate()*obj->move()*obj->temp;
			
			box->vel = 0;
			//light->temp = light->rotate()*light->temp;
		    //light->vel = 0;
			hold = 0;
		}
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			glfwGetCursorPos(window, &prevx, &prevy);
			hold = 3;
		}
		if (action == GLFW_RELEASE) {
		obj->temp = obj->rotate()*obj->move()*obj->temp;
			obj->position = glm::vec3(0);
			hold = 4;
		}
	}
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (mode == 0) {
		obj->position.z = obj->position.z + yoffset / 4;
		obj->temp = obj->rotate()*obj->move()*obj->temp;
		obj->position = glm::vec3(0);
	}
	else if (mode == 2) {
		if (yoffset == 1) {
		    light->light_pos = glm::vec3(light->light_pos.x * 1.1,
			    light->light_pos.y * 1.1,
			    light->light_pos.z * 1.1);
	    }
		else if (yoffset == -1) {
			light->light_pos = glm::vec3(light->light_pos.x / 1.1,
				light->light_pos.y / 1.1,
				light->light_pos.z / 1.1);
		}
	}
	else if (mode == 3) {
		if (yoffset == 1) {
			light->light_pos = glm::vec3(light->light_pos.x * 1.1,
				light->light_pos.y * 1.1,
				light->light_pos.z * 1.1);
		}
		else if (yoffset == -1) {
			light->light_pos = glm::vec3(light->light_pos.x / 1.1,
				light->light_pos.y / 1.1,
				light->light_pos.z / 1.1);
		}
		light->light_dir = glm::normalize(-light->light_pos);
	}
}

glm::vec3 Window::trackBallMapping(GLfloat x, GLfloat y) {
	glm::vec3 v;
	GLfloat d;
	v.x = (2.0f*x - width) / width;
	v.y = (height - 2.0f*y) / height;
	v.z = 0.0f;
	d = glm::length(v);
	d = (d<1.0f) ? d : 1.0f;
	v.z = sqrt(1.001f - d*d);
	glm::normalize(v);
	return v;
}


void Window::cursor_position_callback(GLFWwindow* window, GLdouble xpos, GLdouble ypos){
	/*
	if (hold == 1) {
		box->prev = trackBallMapping(prevx, prevy);
		glfwGetCursorPos(window, &currx, &curry);
		box->curr = trackBallMapping(currx, curry);

		float temp = glm::acos(glm::dot(box->curr, box->prev));
		if (temp > 0.0001f) box->vel = 30*temp;
		box->axis = glm::normalize(glm::cross(box->curr, box->prev));
		cam_pos = glm::vec3(box->rotate()*glm::vec4(cam_pos, 0.0));
		cam_up = glm::normalize(glm::vec3(box->rotate()*glm::vec4(cam_up, 1.0)));
		V = glm::lookAt(cam_pos, cam_look_at, cam_up);
		prevx = currx;
		prevy = curry;
	}
	*/

}
