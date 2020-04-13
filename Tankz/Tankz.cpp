/**
 * \file hello-world.cpp
 * \brief Your first OpenGL application.
 * \author Tomas Barak
 */

#include <iostream>

#include "pgr.h"
#include "Headers/Engine/debug.h"
#include "Headers/Engine/shader.h"
#include "Headers/Engine/game_object.h"
#include "Headers/Engine/Components/transform.h"
#include "Headers/Engine/Components/mesh_renderer.h"

const int WIN_WIDTH = 1600;
const int WIN_HEIGHT = 900;
const char* WIN_TITLE = "Hello World";

GLuint arrayBuffer = 0;
GLuint vao = 0;
Shader * perVertexShader;
MeshRenderer * ms;

void init() {
    glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

    perVertexShader = new Shader("./Data/LightPerVertex.vert", "./Data/LightPerVertex.frag");

    ms = new MeshRenderer("./Data/asteroid.obj", &(*perVertexShader));
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ms->Draw();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow(WIN_TITLE);

    glutDisplayFunc(draw);

    if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
        pgr::dieWithError("pgr init failed, required OpenGL not supported?");

    init();

    std::cout << "Hello triangle!" << std::endl;

    glutMainLoop();

    delete perVertexShader;
    delete ms;
    return 0;
}
