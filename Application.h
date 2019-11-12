#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "RenderEngine/Renderers/MasterRenderer.h"
#include "RenderEngine/Renderable.h"
#include "RenderEngine/Material.h"
#include "RenderEngine/Camera.h"

class Application
{
    public:
        Application();
        ~Application();
        void run();

        Camera _mainCamera;

    private:
        int _windowHeight;
        int _windowWidth;
        GLFWwindow *_window;
        MasterRenderer *_masterRenderer;
};

#endif