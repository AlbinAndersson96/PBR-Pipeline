#include "Application.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

Application::Application()
:_windowWidth(WINDOW_WIDTH)
,_windowHeight(WINDOW_HEIGHT)
{
    glfwInit();

    _window = glfwCreateWindow(_windowWidth, _windowHeight, "PBR Application", NULL, NULL);
    glfwMakeContextCurrent(_window);

    glewInit();

}

Application::~Application()
{
    delete _masterRenderer;

    glfwTerminate();
}

int activeSkybox = 0;
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, true);
    }
    else if(key == GLFW_KEY_0 && action == GLFW_PRESS)
    {
        activeSkybox = 0;
    }
    else if(key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        activeSkybox = 1;
    }
}

bool mouseIsDown = false;
double lastMouseX = 0, lastMouseY = 0, mouseX = 0, mouseY = 0;
float orbitSpeed = 3.0f;
void mouseKeyCallback(GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        lastMouseX = mouseX;
        lastMouseY = mouseY;
        mouseIsDown = true;
    }
    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        mouseIsDown = false;
    }
}

void cursorMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
    //if(mouseIsDown)
    //{
        mouseX = mouseX = xpos;
        mouseY = mouseY = ypos;
    //}
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{

}

void Application::run()
{
    /*PBRMaterial material("Resources/Textures/grimy-metal-albedo.tga", 
                         "Resources/Textures/grimy-metal-normal-dx.tga",
                         "Resources/Textures/grimy-metal-metalness.tga",
                         "Resources/Textures/grimy-metal-roughness.tga");*/
                         
    PBRMaterial material("Resources/Cerberus/Textures/Cerberus_A.tga",
                         "Resources/Cerberus/Textures/Cerberus_N.tga",
                         "Resources/Cerberus/Textures/Cerberus_M.tga",
                         "Resources/Cerberus/Textures/Cerberus_R.tga");

    Cubemap cubeMap0("Resources/Textures/Tokyo_BigSight_3k.hdr");
    Cubemap cubeMap1("Resources/Textures/Frozen_Waterfall_Ref.hdr");

    Tag tag = Mesh;
    //Renderable object("Resources/Models/sphere.obj", material, tag);
    Renderable object("Resources/Cerberus/Cerberus_LP.obj", material, tag);

    //PointLight pLight1(glm::vec3(-50.0f, 0.0f, 0.0f), glm::vec3(2000.0f, 2000.0f, 2000.0f));
    PointLight pointLights[0] = {};

    _masterRenderer = new MasterRenderer(&_mainCamera, pointLights, 1);

    glfwSetKeyCallback(_window, keyCallback);
    glfwSetCursorPosCallback(_window, cursorMoveCallback);
    glfwSetMouseButtonCallback(_window, mouseKeyCallback);
    glfwSetScrollCallback(_window, scrollCallback);

    double lastTime = glfwGetTime();
    int nbFrames = 0;
    while(!glfwWindowShouldClose(_window))
    {   
        if(glfwGetTime() - lastTime > 0.0166)
        {
            lastTime = glfwGetTime();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if((lastMouseX != mouseX || lastMouseY != mouseY) && mouseIsDown)
            {
                _mainCamera.orbit((lastMouseX - mouseX)*orbitSpeed/WINDOW_WIDTH, (mouseY - lastMouseY)*orbitSpeed/WINDOW_HEIGHT);
                lastMouseY = mouseY;
                lastMouseX = mouseX;
            }

            if(activeSkybox == 0)
            {
                _masterRenderer->renderCubemap(cubeMap0);
                _masterRenderer->render(object, cubeMap0);
            }
            else if(activeSkybox == 1)
            {
                _masterRenderer->renderCubemap(cubeMap1);
                _masterRenderer->render(object, cubeMap1);
            }
            


            glfwSwapBuffers(_window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
}