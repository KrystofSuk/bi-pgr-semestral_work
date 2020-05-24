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


/**
 * @brief My namespace for BI-PGR semestral work 
 * 
 */
namespace sukkryst {

	//Helper holders
	Resources resources;
	Scene scene;
	AppData appData;

	//Skybox
	Skybox* s = nullptr;

	//Animations
	Spline* sp;
	Spline* sp2;
	Spline* cameraSp;

	//Lights
	std::vector<Light*> lights;

	//Keymap
	bool pressedKeys[255];

	//Status booleans
	bool inMode = true;
	bool fixedCam = false;

	/**
	 * @brief Procedure for initializing scene, animation curve and calls loaders for configs
	 * 
	 */
	void SceneInit() {

		//Animation curves
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

		std::vector<glm::vec3> v3;
		v3.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		v3.push_back(glm::vec3(-90.0f, 0.0f, 90.0f));
		v3.push_back(glm::vec3(-180.0f, 90.0f, -180.0f));
		v3.push_back(glm::vec3(90.0f, -90.0f, 0.0f));

		sp = new Spline(v);
		sp2 = new Spline(v3);
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


		//Animations appending
		Animator* ico = new Animator(sp, "position");
		Animator* cam = new Animator(cameraSp, "position");
		Animator* tor = new Animator(sp2, "rotation");
		cam->speed = 0.2f;
		scene.GetGameObject("Ico Sphere")->AddComponent(ico);
		scene.GetGameObject("Torus")->AddComponent(tor);
		scene.camera->AddComponent(cam);
		scene.camera->GetComponent<Animator>()->animating = false;

	}

	/**
	 * @brief Init method called after GLUT setup, sets the basic gl properties and loads resources then calls SceneInit
	 * 
	 */
	void Init() {
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

	/**
	 * @brief Draw procedure for drawing all drawable elements
	 * 
	 */
	void DrawCallback() {
		glClearStencil(0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//Matricies
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

		glutSwapBuffers();
	}

	/**
	 * @brief On key reaction for movement and exitin app
	 * 
	 * @param keyPressed which key was pressed
	 * @param mouseX x position of mouse
	 * @param mouseY y position of mouse
	 */
	void KeyboardCallback(unsigned char keyPressed, int mouseX, int mouseY) {
		pressedKeys[tolower(keyPressed)] = true;

		switch (keyPressed) {
		case 27:
			glutLeaveMainLoop();
			break;
		}
	}

	/**
	 * @brief On key up reaction for removing key from keymap
	 * 
	 * @param keyPressed which key was pressed
	 * @param mouseX x position of mouse
	 * @param mouseY y position of mouse
	 */
	void KeyboardUpCallback(unsigned char keyReleased, int mouseX, int mouseY) {

		pressedKeys[tolower(keyReleased)] = false;
	}

	/**
	 * @brief Basic update callback, which updates the scene, movement and animations and calls redisplay
	 * 
	 */
	void TimerCallback(int) {

		if (pressedKeys['r'] == true) {
			//Scene reload
			SceneInit();
		}

		//Movement
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

		if (fixedCam)
			scene.camera->transform->position = scene.GetGameObject("Ico Sphere")->transform->position + glm::vec3(0.0f, 2.5f, 0.0f);

		glutTimerFunc(8, TimerCallback, 0);

		glutPostRedisplay();
	}

	/**
	 * @brief Processing of the GUI menu 
	 * 
	 * @param id pressed button index
	 */
	void MenuProcess(int id) {
		if (id == 1) {
			scene.camera->GetComponent<Animator>()->animating = false;
			glutWarpPointer(appData.width / 2, appData.height / 2);
			appData.freeCamera = true;
			fixedCam = false;
		}
		if (id == 2) {
			scene.camera->GetComponent<Animator>()->animating = false;
			scene.camera->transform->SetPos(scene.GetGameObject("Static Pos 1")->transform->position);
			scene.camera->transform->SetRot(scene.GetGameObject("Static Pos 1")->transform->rotation);
			appData.freeCamera = false;
			fixedCam = false;
		}
		if (id == 3) {
			scene.camera->GetComponent<Animator>()->animating = false;
			scene.camera->transform->SetPos(scene.GetGameObject("Static Pos 2")->transform->position);
			scene.camera->transform->SetRot(scene.GetGameObject("Static Pos 2")->transform->rotation);
			appData.freeCamera = false;
			fixedCam = false;
		}
		if (id == 5) {
			scene.camera->GetComponent<Animator>()->animating = false;
			scene.camera->transform->SetPos(scene.GetGameObject("Ico Sphere")->transform->position + glm::vec3(0.0f, 2.5f, 0.0f));
			fixedCam = true;
		}
		if (id == 6) {
			scene.camera->GetComponent<Animator>()->animating = true;
			appData.freeCamera = true;
			fixedCam = false;
		}
		if (id == 4) {
			scene.GetGameObject("Direction Light")->GetComponent<DayNight>()->use = !scene.GetGameObject("Direction Light")->GetComponent<DayNight>()->use;
		}
		if (id == 98) {
			inMode = !inMode;
		}
		if (id == 99) {
			glutLeaveMainLoop();
		}
	}

	/**
	 * @brief Create a GUI menu
	 * 
	 */
	void CreateMenu() {
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

	/**
	 * @brief Movement of mouse processing
	 * 
	 * @param x position of mouse
	 * @param y position of mouse
	 */
	void PassiveMotionCallback(int x, int y) {

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

	/**
	 * @brief Mouse click reaction 
	 * 
	 * @param button id of mouse button
	 * @param state state of click
	 * @param x position
	 * @param y position
	 */
	void MouseCallback(int button, int state, int x, int y) {

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

	/**
	 * @brief Reshape reaction on window reshape
	 * 
	 * @param newWidth new x in pixels 
	 * @param newHeight new y in pixels
	 */
	void ReshapeCallback(GLint newWidth, GLint newHeight) {
		appData.width = newWidth;
		appData.height = newHeight;
		glViewport(0, 0, (GLsizei)appData.width, (GLsizei)appData.height);
		glutPostRedisplay();
	}
	
	/**
	 * @brief Pseudo main for initialization of glut callbacks and initializations
	 * 
	 * @param argc argument count
	 * @param argv arguments
	 * @return int status
	 */
	int Main(int argc, char** argv) {
		Loader::LoadApp("./Data/app_config.json", appData);

		glutInit(&argc, argv);
		glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
		glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
		glutInitWindowSize(appData.width, appData.height);
		glutCreateWindow(appData.name.c_str());

		glutReshapeFunc(ReshapeCallback);
		glutKeyboardFunc(KeyboardCallback);
		glutMouseFunc(MouseCallback);
		glutKeyboardUpFunc(KeyboardUpCallback);
		glutDisplayFunc(DrawCallback);
		glutPassiveMotionFunc(PassiveMotionCallback);
		glutTimerFunc(8, TimerCallback, 0);

		if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
			pgr::dieWithError("pgr init failed, required OpenGL not supported?");

		Init();
		CreateMenu();


		glutMainLoop();
		return 0;
	}
}

int main(int argc, char** argv) {
	return sukkryst::Main(argc, argv);
}

