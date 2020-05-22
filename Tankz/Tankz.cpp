#include <iostream>
#include <string>
#include <Windows.h>
#include <time.h>

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
#include "Engine/Components/Custom/animator.h"
#include "Engine/Components/skybox.h"
#include "Engine/Components/Custom/day_night.h"
#include "Engine/Core/spline.h"

const int WIN_WIDTH = 1600;
const int WIN_HEIGHT = 900;
const char* WIN_TITLE = "Hello World";

Resources resources;
Scene scene;
AppData appData;

Skybox* s = nullptr;

Spline* sp;
Spline* cameraSp;

std::vector<Light*> lights;
bool pressedKeys[255];

bool inMode = true;
bool fixedCam = false;

void SceneInit() {

	std::vector<glm::vec3> v;
	v.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	v.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	v.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	v.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	v.push_back(glm::vec3(1.0f, 2.0f, 1.0f));
	v.push_back(glm::vec3(0.0f, 2.0f, 1.0f));
	v.push_back(glm::vec3(1.0f, 2.0f, -1.0f));
	v.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));


	std::vector<glm::vec3> v2;
	v2.push_back(glm::vec3(-14.0f, 3.5f, 3.2f));
	v2.push_back(glm::vec3(-7.4f, 2.8f, -5.9f));
	v2.push_back(glm::vec3(-1.5f, 4.8f, -13.8f));
	v2.push_back(glm::vec3(15.5f, 7.3f, -9.9f));
	v2.push_back(glm::vec3(11.9f, 9.8f, 14.9f));

	sp = new Spline(v);
	cameraSp = new Spline(v2);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	std::cout << "---------SCENE INIT---------" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

	scene.Clear();

	//GAMEOBJECTS LOADING
	Loader::LoadScene("./Data/scene_config.json", scene, resources);

	if (s != nullptr)
		delete s;
	s = new Skybox("./Data/Textures/bkg1", resources.GetShader("skybox"));

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	std::cout << "---------INIT DONE---------" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);


	//Animations
	Animator* ico = new Animator(sp, "position");
	Animator* cam = new Animator(cameraSp, "position");
	cam->speed = 0.2f;
	scene.GetGameObject("Ico Sphere")->AddComponent(ico);
	scene.camera->AddComponent(cam);
	scene.camera->GetComponent<Animator>()->animating = false;

}

void init() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	std::cout << "---------INIT---------" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

	glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	//RESOURCES LOADING
	Loader::LoadResources("./Data/resources_config.json", resources);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	std::cout << "---------INIT DONE---------" << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	SceneInit();

	appData.freeCamera = true;
}



void draw() {
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	viewMatrix = glm::lookAt(
		scene.camera->transform->position,
		scene.camera->transform->position + scene.camera->transform->Front(),
		scene.camera->transform->Up()
	);

	projectionMatrix = glm::perspective(glm::radians(60.0f), appData.width / (float)appData.height, 0.1f, 1000.0f);

	s->Draw(projectionMatrix, viewMatrix, scene.camera->transform);

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	scene.Render(projectionMatrix, viewMatrix, inMode);
	//std::cout << scene.camera->transform->position.x << " " << scene.camera->transform->position.y << " " << scene.camera->transform->position.z << std::endl;
	//std::cout << scene.camera->transform->rotation.x << " " << scene.camera->transform->rotation.y << " " << scene.camera->transform->rotation.z << std::endl << std::endl;
	glutSwapBuffers();
}

void keyboardCallback(unsigned char keyPressed, int mouseX, int mouseY) {
	//std::cout << tolower(keyPressed) << std::endl;
	pressedKeys[tolower(keyPressed)] = true;

	switch (keyPressed) {
	case 27:
		glutLeaveMainLoop();
		break;
	}
}

void keyboardSpecialCallback(int keyPressed, int mouseX, int mouseY) {

}

void keyboardSpecialUpCallback(int keyReleased, int mouseX, int mouseY) {
	pressedKeys[keyReleased] = false;

	if (keyReleased == 1) {
		glutWarpPointer(appData.width / 2, appData.height / 2);
		appData.freeCamera = true;
	}
	if (keyReleased == 2) {
		scene.camera->transform->SetPos(scene.GetGameObject("Static Pos 1")->transform->position);
		scene.camera->transform->SetRot(scene.GetGameObject("Static Pos 1")->transform->rotation);
		appData.freeCamera = false;
	}
	if (keyReleased == 3) {
		scene.camera->transform->SetPos(scene.GetGameObject("Static Pos 2")->transform->position);
		scene.camera->transform->SetRot(scene.GetGameObject("Static Pos 2")->transform->rotation);
		appData.freeCamera = false;
	}
}

void keyboardUpCallback(unsigned char keyReleased, int mouseX, int mouseY) {

	pressedKeys[tolower(keyReleased)] = false;
}


void timerCallback(int) {

	if (pressedKeys['r'] == true) {
		SceneInit();
	}

	if (appData.freeCamera) {
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
	}

	scene.Update();

	//scene.GetGameObject("Ico Sphere")->transform->position = sp->Evaluate(0.001f * (float)glutGet(GLUT_ELAPSED_TIME));
	if(fixedCam)
		scene.camera->transform->position = scene.GetGameObject("Ico Sphere")->transform->position + glm::vec3(0.0f,2.5f,0.0f);
	glutTimerFunc(8, timerCallback, 0);
	glutPostRedisplay();
}

void glutMotionCallback(int x, int y) {
}

void MenuProcess(int i) {
	if (i == 1) {
		scene.camera->GetComponent<Animator>()->animating = false;
		glutWarpPointer(appData.width / 2, appData.height / 2);
		appData.freeCamera = true;
		fixedCam = false;
	}
	if (i == 2) {
		scene.camera->GetComponent<Animator>()->animating = false;
		scene.camera->transform->SetPos(scene.GetGameObject("Static Pos 1")->transform->position);
		scene.camera->transform->SetRot(scene.GetGameObject("Static Pos 1")->transform->rotation);
		appData.freeCamera = false;
		fixedCam = false;
	}
	if (i == 3) {
		scene.camera->GetComponent<Animator>()->animating = false;
		scene.camera->transform->SetPos(scene.GetGameObject("Static Pos 2")->transform->position);
		scene.camera->transform->SetRot(scene.GetGameObject("Static Pos 2")->transform->rotation);
		appData.freeCamera = false;
		fixedCam = false;
	}
	if (i == 5) {
		scene.camera->GetComponent<Animator>()->animating = false;
		scene.camera->transform->SetPos(scene.GetGameObject("Ico Sphere")->transform->position + glm::vec3(0.0f, 2.5f, 0.0f));
		fixedCam = true;
	}
	if (i == 6) {
		scene.camera->GetComponent<Animator>()->animating = true;
		appData.freeCamera = true;
		fixedCam = false;
	}
	if (i == 4) {
		scene.GetGameObject("Direction Light")->GetComponent<DayNight>()->use = !scene.GetGameObject("Direction Light")->GetComponent<DayNight>()->use;
	}
	if (i == 98) {
		inMode = !inMode;
	}
	if (i == 99) {
		glutLeaveMainLoop();
	}
}

void createMenu() {
	int cameraSub = glutCreateMenu(MenuProcess);
	glutAddMenuEntry("Free", 1);
	glutAddMenuEntry("Static 1.", 2);
	glutAddMenuEntry("Static 2.", 3);
	glutAddMenuEntry("Dynamic 1.", 5);
	glutAddMenuEntry("Dynamic 2.", 6);

	int lightningSub = glutCreateMenu(MenuProcess);
	glutAddMenuEntry("Day Night Cycle", 4);

	glutCreateMenu(MenuProcess);
	glutAddSubMenu("Camera", cameraSub);
	glutAddSubMenu("Lightning", lightningSub);
	glutAddMenuEntry("Mode", 98);
	glutAddMenuEntry("Exit", 99);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void glutPassiveMotionCallback(int x, int y) {

	float deltaX = 0.1f * (x - appData.width / 2);
	float deltaY = 0.1f * (y - appData.height / 2);
	if (deltaX > 10 || deltaX < -10)
		deltaX = 0;
	if (deltaY > 10 || deltaY < -10)
		deltaY = 0;


	if (appData.freeCamera) {
		scene.camera->transform->Rotate(glm::vec3(1.0f * -deltaY, 1.0f * deltaX, 0.0f));
		if (scene.camera->transform->rotation[0] > 89.0) {
			scene.camera->transform->SetRot(glm::vec3(89.0, scene.camera->transform->rotation[1], scene.camera->transform->rotation[2]));
		}
		if (scene.camera->transform->rotation[0] < -89.0) {
			scene.camera->transform->SetRot(glm::vec3(-89.0, scene.camera->transform->rotation[1], scene.camera->transform->rotation[2]));
		}

		glutWarpPointer(appData.width / 2, appData.height / 2);
	}
	glutPostRedisplay();
}

void mouseCallback(int button, int state, int x, int y){

	if (state != GLUT_DOWN)
		return;

	GLbyte color[4];
	GLfloat depth;
	GLuint index;

	glReadPixels(x, appData.width - y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(x, appData.height - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
	glReadPixels(x, appData.height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

	printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n",
		x, y, color[0], color[1], color[2], color[3], depth, index);

	scene.Click(index);
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
	glutMouseFunc(mouseCallback);
	glutKeyboardUpFunc(keyboardUpCallback);
	glutSpecialFunc(keyboardSpecialCallback);
	glutSpecialFunc(keyboardSpecialUpCallback);
	glutDisplayFunc(draw);
	glutMotionFunc(glutMotionCallback);
	glutPassiveMotionFunc(glutPassiveMotionCallback);
	glutTimerFunc(8, timerCallback, 0);

	if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
		pgr::dieWithError("pgr init failed, required OpenGL not supported?");

	init();
	createMenu();
	//glutFullScreen();


	glutMainLoop();
	return 0;
}
