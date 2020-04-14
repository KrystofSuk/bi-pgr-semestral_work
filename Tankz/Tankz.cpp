/**
 * \file hello-world.cpp
 * \brief Your first OpenGL application.
 * \author Tomas Barak
 */

#include <iostream>
#include <string>

#include "pgr.h"
#include "Headers/Engine/debug.h"
#include "Headers/Engine/shader_cache.h"
#include "Headers/Engine/mesh_cache.h"
#include "Headers/Engine/material_cache.h"
#include "Headers/Engine/game_object.h"
#include "Headers/Engine/Components/transform.h"
#include "Headers/Engine/Components/mesh_renderer.h"
const int WIN_WIDTH = 1600;
const int WIN_HEIGHT = 900;
const char* WIN_TITLE = "Hello World";

GLuint arrayBuffer = 0;
GLuint vao = 0;

ShaderCache shaders;
MeshCache meshes;
MaterialCache materials;


GameObject* asteroid;
GameObject* asteroid2;

void init() {
    glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    


    //SHADER LOADING
    shaders.LoadShader("debug_shader", "./Data/LightPerVertex.vert", "./Data/LightPerVertex.frag");

    //MESH LOADING
    meshes.LoadMesh("Asteroid_Mesh", "./Data/asteroid.obj", shaders.GetShader("debug_shader"));

    //MATERIAL LOADING
    materials.LoadMaterial("Asteroid1", shaders.GetShader("debug_shader"));
    materials.LoadMaterial("Asteroid2", shaders.GetShader("debug_shader"));
    materials.LoadMaterial("Asteroid3", shaders.GetShader("debug_shader"));
    materials.GetMaterial("Asteroid2")->diffuse = glm::vec3(0.0f, 1.0f, 0.0f);
    materials.GetMaterial("Asteroid3")->diffuse = glm::vec3(1.0f, 0.0f, 1.0f);

    //GAMEOBJECTS LOADING
    asteroid = new GameObject("Asteroid1");
    MeshRenderer* ms = new MeshRenderer(meshes.GetMesh("Asteroid_Mesh"), materials.GetMaterial("Asteroid3"));
    asteroid->AddComponent(ms);


    asteroid2 = new GameObject("Asteroid2");
    asteroid2->transform->Move(glm::vec3(1.0f, -2.0f, 0.0f));
    asteroid2->transform->Rotate(glm::vec3(90.0f, 0.0f, 0.0f));
    MeshRenderer* ms2 = new MeshRenderer(meshes.GetMesh("Asteroid_Mesh"), materials.GetMaterial("Asteroid2"));
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

    // setup camera & projection transform
    glm::mat4 viewMatrix = orthoViewMatrix;
    glm::mat4 projectionMatrix = orthoProjectionMatrix;


    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUpVector = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 cameraCenter;

    glm::vec3 cameraViewDirection = glm::vec3(1.0f, 0.0f, 0.0f);

    glm::vec3 rotationAxis = glm::cross(cameraViewDirection, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 cameraTransform = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), rotationAxis);

    cameraUpVector = glm::vec3(cameraTransform * glm::vec4(cameraUpVector, 0.0f));
    cameraViewDirection = glm::vec3(cameraTransform * glm::vec4(cameraViewDirection, 0.0f));

    cameraCenter = cameraPosition + cameraViewDirection;

    viewMatrix = glm::lookAt(
        cameraPosition,
        cameraCenter,
        cameraUpVector
    );

    projectionMatrix = glm::perspective(glm::radians(60.0f), WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 10.0f);


    asteroid->GetComponent<MeshRenderer>()->Draw(projectionMatrix, viewMatrix, asteroid->transform);
    asteroid2->GetComponent<MeshRenderer>()->Draw(projectionMatrix, viewMatrix, asteroid2->transform);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow(WIN_TITLE);

    glutDisplayFunc(draw);

    if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
        pgr::dieWithError("pgr init failed, required OpenGL not supported?");

    init();
    std::cout << *asteroid->GetComponent<Transform>() << std::endl;

    std::cout << "Hello triangle!" << std::endl;

    glutMainLoop();

    delete asteroid;
    return 0;
}
