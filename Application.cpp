#include "Application.h"

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

Application::Application()
:_windowWidth(WINDOW_WIDTH)
,_windowHeight(WINDOW_HEIGHT)
{
    glfwInit();

    _window = glfwCreateWindow(_windowWidth, _windowHeight, "PBR Application", glfwGetPrimaryMonitor(), NULL);
    glfwMakeContextCurrent(_window);

    glewInit();

}

Application::~Application()
{
    delete _masterRenderer;
    glfwTerminate();
}

int activeSkybox = 0;
glm::vec3 forwardVec = {1, 0, 0}, cameraPos = {-50, 0, 0};
bool usePBR = false;
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, true);
    }
    else if(key == GLFW_KEY_0 && action == GLFW_PRESS)
        activeSkybox = 0;
    else if(key == GLFW_KEY_1 && action == GLFW_PRESS)
        activeSkybox = 1;
    else if(key == GLFW_KEY_2 && action == GLFW_PRESS)
        activeSkybox = 2;
    else if(key == GLFW_KEY_3 && action == GLFW_PRESS)
        activeSkybox = 3;
    else if(key == GLFW_KEY_4 && action == GLFW_PRESS)
        activeSkybox = 4;


    if(key == GLFW_KEY_P && action == GLFW_PRESS)
        usePBR = !usePBR;

    GLfloat movementFactor = 5;
    glm::vec3 right = glm::normalize(glm::cross(forwardVec, glm::vec3(0, 1, 0)));

    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
        cameraPos += movementFactor * forwardVec;
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
        cameraPos -= movementFactor * forwardVec;
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
        cameraPos += movementFactor * right;
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
        cameraPos -= movementFactor * right;
}

bool firstMouse = true;
float lastX, lastY, yaw = 0, pitch = 0;
void MouseHandler(GLFWwindow *window, double mouseX, double mouseY)
{
    if (firstMouse)
    {
        lastX = mouseX;
        lastY = mouseY;
        firstMouse = false;
    }

    float xoffset = mouseX - lastX;
    float yoffset = lastY - mouseY;
    lastX = mouseX;
    lastY = mouseY;

    float sensitivity = 0.3f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = 89.0f;

    forwardVec.x = cos(yaw * 3.14 / 180) * cos(pitch * 3.14 / 180);
    forwardVec.y = sin(pitch * 3.14 / 180);
    forwardVec.z = sin(yaw * 3.14 / 180) * cos(pitch * 3.14 / 180);
    forwardVec = glm::normalize(forwardVec);
}

void Application::run()
{
    Material material1("Resources/Cerberus/Textures/Cerberus_A.tga",
                         "Resources/Cerberus/Textures/Cerberus_N.tga",
                         "Resources/Cerberus/Textures/Cerberus_M.tga",
                         "Resources/Cerberus/Textures/Cerberus_R.tga",
                         true);
    Material material2("Resources/Cerberus/Textures/Cerberus_A.tga",
                         "Resources/Cerberus/Textures/Cerberus_N.tga",
                         "Resources/Cerberus/Textures/Cerberus_M.tga",
                         "Resources/Cerberus/Textures/Cerberus_R.tga",
                         false);

    Cubemap cubeMap0("Resources/Textures/Tokyo_BigSight_3k.hdr");
    Cubemap cubeMap1("Resources/Textures/Frozen_Waterfall_Ref.hdr");
    Cubemap cubeMap2("Resources/Textures/Brooklyn_Bridge_Planks_2k.hdr");
    Cubemap cubeMap3("Resources/Textures/Factory_Catwalk_2k.hdr");
    Cubemap cubeMap4("Resources/Textures/Milkyway_small.hdr");


    Tag tag = Mesh;
    Renderable object1("Resources/Cerberus/Cerberus_LP.obj", material1, tag);
    Renderable object2("Resources/Cerberus/Cerberus_LP.obj", material2, tag);

    PointLight pLight1(glm::vec3(0.0f, 100.0f, 0.0f), glm::vec3(2000.0f, 2000.0f, 2000.0f));
    PointLight pointLights[1] = {pLight1};

    _masterRenderer = new MasterRenderer(&_mainCamera, pointLights, 1);

    glfwSetKeyCallback(_window, keyCallback);
    glfwSetCursorPosCallback(_window, MouseHandler);

    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    double lastTime = glfwGetTime();
    int nbFrames = 0;
    while(!glfwWindowShouldClose(_window))
    {   
        if(glfwGetTime() - lastTime > 0.0166)
        {
            lastTime = glfwGetTime();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            _mainCamera.setMatrix(cameraPos, cameraPos + forwardVec);

            if(activeSkybox == 0)
            {
                _masterRenderer->renderCubemap(cubeMap0);
                if(usePBR)
                    _masterRenderer->render(object1, cubeMap0);
                else
                    _masterRenderer->render(object2, cubeMap0);
            }
            else if(activeSkybox == 1)
            {
                _masterRenderer->renderCubemap(cubeMap1);
                if(usePBR)
                    _masterRenderer->render(object1, cubeMap1);
                else
                    _masterRenderer->render(object2, cubeMap1);
            }
            else if(activeSkybox == 2)
            {
                _masterRenderer->renderCubemap(cubeMap2);
                if(usePBR)
                    _masterRenderer->render(object1, cubeMap2);
                else
                    _masterRenderer->render(object2, cubeMap2);
            }
            else if(activeSkybox == 3)
            {
                _masterRenderer->renderCubemap(cubeMap3);
                if(usePBR)
                    _masterRenderer->render(object1, cubeMap3);
                else
                    _masterRenderer->render(object2, cubeMap3);
            }
            else if(activeSkybox == 4)
            {
                _masterRenderer->renderCubemap(cubeMap4);
                if(usePBR)
                    _masterRenderer->render(object1, cubeMap4);
                else
                    _masterRenderer->render(object2, cubeMap4);
            }
            
            glfwSwapBuffers(_window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
}