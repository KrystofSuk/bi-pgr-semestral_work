#include <iostream>
#include <string>

#include <Windows.h>

#include "pgr.h"
#include "Engine/Core/loader.h"
#include "Engine/Utils/debug.h"
#include "Engine/Core/game_object.h"
#include "Engine/Core/transform.h"
#include "Engine/Components/direction_light.h"
#include "Engine/Components/mesh_renderer.h"
#include "Engine/Core/resources.h"
#include "Engine/Components/point_light.h"
#include "Engine/Components/spot_light.h"
#include "Engine/Components/skybox.h"

const int WIN_WIDTH = 1600;
const int WIN_HEIGHT = 900;
const char* WIN_TITLE = "Hello World";

Resources resources;
Scene scene;
AppData appData;

Skybox* s;

std::vector<Light*> lights;

bool pressedKeys[255];

void init() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	std::cout << "---------INIT---------" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

	glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	//RESOURCES LOADING
	Loader::LoadResources("./Data/resources_config.json", resources);


	//GAMEOBJECTS LOADING
	Loader::LoadScene("./Data/scene_config.json", scene, resources);

	s = new Skybox("./Data/Textures/CloudyCrown_Midday", resources.GetShader("skybox"));
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	glm::vec3 cameraPos = scene.camera->transform->position;

	viewMatrix = glm::lookAt(
		cameraPos,
		cameraPos + scene.camera->transform->Front(),
		scene.camera->transform->Up()
	);

	projectionMatrix = glm::perspective(glm::radians(60.0f), appData.width / (float)appData.height, 0.1f, 100.0f);

	s->Draw(projectionMatrix, viewMatrix, scene.camera->transform);

	scene.Render(projectionMatrix, viewMatrix);

	glutSwapBuffers();
}

void keyboardCallback(unsigned char keyPressed, int mouseX, int mouseY) {

	pressedKeys[keyPressed] = true;

	switch (keyPressed) {
	case 27:
		glutLeaveMainLoop();
		break;
	}
}

void keyboardCallback(int keyPressed, int mouseX, int mouseY) {

	pressedKeys[keyPressed] = true;

	switch (keyPressed) {
	case 27:
		glutLeaveMainLoop();
		break;
	}
}

void keyboardUpCallback(int keyReleased, int mouseX, int mouseY) {

	pressedKeys[keyReleased] = false;
}

void keyboardUpCallback(unsigned char keyReleased, int mouseX, int mouseY) {

	pressedKeys[keyReleased] = false;
}

void timerCallback(int) {

	if (pressedKeys['a'] == true)
		scene.camera->transform->Move(scene.camera->transform->Right() * 0.1f);
	if (pressedKeys['d'] == true)
		scene.camera->transform->Move(scene.camera->transform->Right() * -0.1f);
	if (pressedKeys['w'] == true)
		scene.camera->transform->Move(scene.camera->transform->Front() * 0.1f);
	if (pressedKeys['s'] == true)
		scene.camera->transform->Move(scene.camera->transform->Front() * -0.1f);
	if (pressedKeys['q'] == true)
		scene.camera->transform->Move(scene.camera->transform->Up() * 0.1f);
	if (pressedKeys['z'] == true)
		scene.camera->transform->Move(scene.camera->transform->Up() * -0.1f);

	glutTimerFunc(8, timerCallback, 0);
	glutPostRedisplay();
}

void glutMotionCallback(int x, int y) {
}

void glutPassiveMotionCallback(int x, int y) {

	float deltaX = 0.1f * (x - appData.width / 2);
	float deltaY = 0.1f * (y - appData.height / 2);
	if (deltaX > 10 || deltaX < -10)
		deltaX = 0;
	if (deltaY > 10 || deltaY < -10)
		deltaY = 0;


	scene.camera->transform->Rotate(glm::vec3(1.0f * -deltaY, 1.0f * deltaX, 0.0f));

	glutWarpPointer(appData.width / 2, appData.height / 2);
	glutPostRedisplay();
}

void OnReshape(GLint newWidth, GLint newHeight) {
	appData.width = newWidth;
	appData.height = newHeight;
	glViewport(0, 0, (GLsizei)appData.width, (GLsizei)appData.height);
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	Loader::LoadApp("./Data/app_config.json", appData);

	glutInit(&argc, argv);
	glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(appData.width, appData.height);
	glutCreateWindow(appData.name.c_str());

	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(keyboardCallback);
	glutKeyboardUpFunc(keyboardUpCallback);
	glutSpecialFunc(keyboardCallback);
	glutSpecialFunc(keyboardUpCallback);
	glutDisplayFunc(draw);
	glutMotionFunc(glutMotionCallback);
	glutPassiveMotionFunc(glutPassiveMotionCallback);
	glutTimerFunc(8, timerCallback, 0);

	if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
		pgr::dieWithError("pgr init failed, required OpenGL not supported?");

	init();
	//glutFullScreen();


	glutMainLoop();
	return 0;
}
