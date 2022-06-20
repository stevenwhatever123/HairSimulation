#include <pch.h>

#include <headers/SystemManager.h>

SystemManager::SystemManager()
{
    
}

void SystemManager::init()
{
    init_window();
}

void SystemManager::init_window()
{
    closeWindow = false;

    /* Initialize the library */
    if (!glfwInit())
        closeWindow = true;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        closeWindow = true;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
}

void SystemManager::update()
{
    if (glfwWindowShouldClose(window))
    {
        closeWindow = true;

        glfwTerminate();
    }

    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}