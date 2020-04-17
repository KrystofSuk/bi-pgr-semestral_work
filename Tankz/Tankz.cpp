#include <iostream>
#include <string>

#include "pgr.h"
#include "Engine/Utils/debug.h"
#include "Engine/Core/game_object.h"
#include "Engine/Components/transform.h"
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

GameObject* asteroid;
GameObject* asteroid2;

GameObject* directionLight;
GameObject* pointLight;
GameObject* pointLight2;

GameObject* spotLight;

GameObject* camera;

Skybox* s;

std::vector<Light*> lights;

bool pressedKeys[255];

void init() {
	glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	//SHADER LOADING
	resources.AddShader("debug", "./Data/Shaders/default.vert", "./Data/Shaders/default.frag");
	resources.AddShader("per_fragment", "./Data/Shaders/per_fragment.vert", "./Data/Shaders/per_fragment.frag");
	resources.AddShader("skybox", "./Data/Shaders/skybox.vert", "./Data/Shaders/skybox.frag");

	//MATERIAL LOADING
	//resources.AddMaterial("Asteroid1", "debug");
	resources.AddMaterial("Asteroid2", "per_fragment");
	resources.AddMaterial("Asteroid3", "debug");
	resources.GetMaterial("Asteroid2")->diffuse = glm::vec3(0.0f, 1.0f, 0.0f);
	resources.GetMaterial("Asteroid3")->diffuse = glm::vec3(1.0f, 0.0f, 1.0f);

	//MESH LOADING
	resources.AddMesh("Asteroid_Mesh", "./Data/asteroid.obj", "debug");
	resources.AddMesh("Terrain_Grass", "./Data/Models/Terrain_Grass.obj", "per_fragment");
	//resources.AddMesh("hoverboard_smoothed", "./Data/hoverboard_smoothed.obj", "per_fragment"); 
	resources.AddMesh("hoverboard_smoothed", "./Data/strom1.obj", "per_fragment");


	//GAMEOBJECTS LOADING
	s = new Skybox("./Data/Textures/CloudyCrown_Midday", resources.GetShader("skybox"));

	camera = new GameObject("Camera");
	camera->transform->Move(glm::vec3(-2.0f, 0.0f, 0.0f));

	directionLight = new GameObject("Direction Light");
	directionLight->transform->Move(glm::vec3(-10.0f, 5.0f, 10.0f));
	directionLight->transform->Scale(glm::vec3(-0.9f, -0.9f, -0.9f));
	MeshRenderer* ms3 = new MeshRenderer(resources.GetMesh("Asteroid_Mesh"), resources.GetMaterial("Asteroid3"));
	DirectionLight* dl = new DirectionLight();
	directionLight->AddComponent(dl);
	directionLight->AddComponent(ms3);
	lights.emplace_back(dl);

	pointLight = new GameObject("Point Light");
	pointLight->transform->Move(glm::vec3(0.0f, -3.0f, 0.0f));
	pointLight->transform->Scale(glm::vec3(-0.9f, -0.9f, -0.9f));
	MeshRenderer* ms4 = new MeshRenderer(resources.GetMesh("Asteroid_Mesh"), resources.GetMaterial("Asteroid3"));
	PointLight* dl2 = new PointLight();
	dl2->intensity = 1.0f;
	pointLight->AddComponent(dl2);
	pointLight->AddComponent(ms4);
	lights.emplace_back(dl2);


	pointLight2 = new GameObject("Point Light");
	pointLight2->transform->Move(glm::vec3(18.0f, -2.0f, 9.0f));
	pointLight2->transform->Scale(glm::vec3(-0.9f, -0.9f, -0.9f));
	MeshRenderer* ms5 = new MeshRenderer(resources.GetMesh("Asteroid_Mesh"), resources.GetMaterial("Asteroid3"));
	PointLight* dl3 = new PointLight();
	dl3->intensity = 1.0f;
	pointLight2->AddComponent(dl3);
	pointLight2->AddComponent(ms5);
	lights.emplace_back(dl3);

	spotLight = new GameObject("Spot Light");
	spotLight->transform->Move(glm::vec3(30.0f, -2.0f, 9.0f));
	spotLight->transform->Rotate(glm::vec3(-30.0f, 0.0f, 0.0f));
	spotLight->transform->Scale(glm::vec3(-0.9f, -0.9f, -0.9f));
	MeshRenderer* ms6 = new MeshRenderer(resources.GetMesh("Asteroid_Mesh"), resources.GetMaterial("Asteroid3"));
	SpotLight* dl4 = new SpotLight();
	dl4->intensity = 1.0f;
	spotLight->AddComponent(dl4);
	spotLight->AddComponent(ms6);
	lights.emplace_back(dl4);

	asteroid = new GameObject("Terrain_Grass");
	asteroid->transform->Move(glm::vec3(0.0f, 0.0f, 0.0f));
	asteroid->transform->Rotate(glm::vec3(0.0f, 0.0f, 0.0f));
	asteroid->transform->Scale(glm::vec3(100.0f, 100.0f, 100.0f));
	MeshRenderer* ms = new MeshRenderer(resources.GetMesh("Terrain_Grass"), resources.GetMaterial("Asteroid2"));
	asteroid->AddComponent(ms);


	asteroid2 = new GameObject("Asteroid2");
	asteroid2->transform->Move(glm::vec3(5.0f, -2.0f, -2.0f));
	asteroid2->transform->Rotate(glm::vec3(90.0f, 0.0f, 0.0f));
	MeshRenderer* ms2 = new MeshRenderer(resources.GetMesh("hoverboard_smoothed"), resources.GetMaterial("Asteroid3"));
	asteroid2->AddComponent(ms2);
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 orthoProjectionMatrix = glm::ortho(
		-10.0f, 10.0f,
		-10.0f, 10.0f,
		-10.0f * 1, 10.0f * 1.0f
	);
	// static viewpoint - top view
	glm::mat4 orthoViewMatrix = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

	glm::mat4 viewMatrix = orthoViewMatrix;
	glm::mat4 projectionMatrix = orthoProjectionMatrix;

	glm::vec3 cameraPos = camera->transform->position;

	viewMatrix = glm::lookAt(
		cameraPos,
		cameraPos + camera->transform->Front(),
		camera->transform->Up()
	);

	projectionMatrix = glm::perspective(glm::radians(60.0f), WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);

	s->Draw(projectionMatrix, viewMatrix, camera->transform);


	asteroid->GetComponent<MeshRenderer>()->Draw(projectionMatrix, viewMatrix, asteroid->transform, lights, camera->transform);
	asteroid2->GetComponent<MeshRenderer>()->Draw(projectionMatrix, viewMatrix, asteroid2->transform, lights, camera->transform);
	//directionLight->GetComponent<MeshRenderer>()->Draw(projectionMatrix, viewMatrix, directionLight->transform, lights, camera->transform);
	pointLight->GetComponent<MeshRenderer>()->Draw(projectionMatrix, viewMatrix, pointLight->transform, lights, camera->transform);
	pointLight2->GetComponent<MeshRenderer>()->Draw(projectionMatrix, viewMatrix, pointLight2->transform, lights, camera->transform);
	spotLight->GetComponent<MeshRenderer>()->Draw(projectionMatrix, viewMatrix, spotLight->transform, lights, camera->transform);



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

void keyboardUpCallback(unsigned char keyReleased, int mouseX, int mouseY) {

	pressedKeys[keyReleased] = false;
}

void timerCallback(int) {
	//asteroid->transform->Rotate(glm::vec3(3.0f, 0.0f, 0.0f));
	if (pressedKeys['a'] == true)
		camera->transform->Move(camera->transform->Right() * 0.1f);
	if (pressedKeys['d'] == true)
		camera->transform->Move(camera->transform->Right() * -0.1f);
	if (pressedKeys['w'] == true)
		camera->transform->Move(camera->transform->Front() * 0.1f);
	if (pressedKeys['s'] == true)
		camera->transform->Move(camera->transform->Front() * -0.1f);
	if (pressedKeys['q'] == true)
		camera->transform->Move(camera->transform->Up() * 0.1f);
	if (pressedKeys['z'] == true)
		camera->transform->Move(camera->transform->Up() * -0.1f);

	glutTimerFunc(8, timerCallback, 0);
	glutPostRedisplay();
}

void glutMotionCallback(int x, int y) {
	//std::cout << "Move " << x << " " << y << std::endl;
}

void glutPassiveMotionCallback(int x, int y) {

	float deltaX = 0.1f * (x - WIN_WIDTH / 2);
	float deltaY = 0.1f * (y - WIN_HEIGHT / 2);
	if (deltaX > 10 || deltaX < -10)
		deltaX = 0;
	if (deltaY > 10 || deltaY < -10)
		deltaY = 0;

	//std::cout << deltaX << " " << deltaY << std::endl;

	camera->transform->Rotate(glm::vec3(1.0f * -deltaY, 1.0f * deltaX, 0.0f));

	glutWarpPointer(WIN_WIDTH / 2, WIN_HEIGHT / 2);	
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutCreateWindow(WIN_TITLE);

	glutKeyboardFunc(keyboardCallback);
	glutKeyboardUpFunc(keyboardUpCallback);
	glutDisplayFunc(draw);
	glutMotionFunc(glutMotionCallback);
	glutPassiveMotionFunc(glutPassiveMotionCallback);
	glutTimerFunc(8, timerCallback, 0);

	if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
		pgr::dieWithError("pgr init failed, required OpenGL not supported?");

	init();


	glutMainLoop();

	delete asteroid;
	return 0;
}
