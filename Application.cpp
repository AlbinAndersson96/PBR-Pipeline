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

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, true);
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
    Material material("Resources/Textures/grass.tga");
    Tag tag = Mesh;
    Renderable object("Resources/Models/sphere.obj", material, tag);

    _masterRenderer = new MasterRenderer(&_mainCamera);

    glfwSetKeyCallback(_window, keyCallback);
    glfwSetCursorPosCallback(_window, cursorMoveCallback);
    glfwSetMouseButtonCallback(_window, mouseKeyCallback);
    glfwSetScrollCallback(_window, scrollCallback);

    double lastTime = glfwGetTime();
    int nbFrames = 0;
    while(!glfwWindowShouldClose(_window))
    {   
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if((lastMouseX != mouseX || lastMouseY != mouseY) && mouseIsDown)
        {
            _mainCamera.orbit((lastMouseX - mouseX)*orbitSpeed/WINDOW_WIDTH, (mouseY - lastMouseY)*orbitSpeed/WINDOW_HEIGHT);
            lastMouseY = mouseY;
            lastMouseX = mouseX;
        }

        _masterRenderer->render(object);

        glfwSwapBuffers(_window);
        glfwPollEvents();

        double currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
            std::cout << "\r" << 1000.0/double(nbFrames) << " ms/frame.   " << 1000/(1000/double(nbFrames)) << " FPS " << std::flush;
            nbFrames = 0;
            lastTime += 1.0;
        }
    }
    glfwTerminate();
}