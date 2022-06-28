#include <pch.h>

#include <Managers/SystemManager.h>

SystemManager::SystemManager() : keys()
{
    window = nullptr;
    closeWindow = false;
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

    glfwSetWindowUserPointer(window, this);

    // Keyboard handler
    auto key_callback = [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        glfwGetWindowUserPointer(window);

        SystemManager* system = (SystemManager*) glfwGetWindowUserPointer(window);
        if (key >= GLFW_KEY_SPACE && key < GLFW_KEY_ESCAPE)
        {
            if (action == GLFW_PRESS) system->keys[(char) key] = 1;
            if (action == GLFW_RELEASE) system->keys[(char) key] = 0;
        }

        if (key == GLFW_KEY_ESCAPE) system->closeWindow = true;
    };

    glfwSetKeyCallback(window, key_callback);
}

void SystemManager::update()
{
    update_inputs();

    if (glfwWindowShouldClose(window))
    {
        closeWindow = true;

        glfwTerminate();
    }

    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
}

void SystemManager::update_inputs()
{
    /* Poll for and process events */
    glfwPollEvents();

    if (keys['L'])
    {
        bool readSuccess;
        std::string filename;
        std::tie(readSuccess, filename) = SystemUtils::selectFile();
        
        if (readSuccess)
        {
            std::cout << "Success reading: " << filename << "\n";
            Model* modelScene = SystemUtils::readModel(filename.c_str());
            std::cout << "Nubmer of Meshes: " << modelScene->meshes.size() << "\n";

            for (u32 i = 0; i < modelScene->meshes.size(); i++)
            {
                std::cout << "Mesh " << i << " primitive type: " << modelScene->meshes[i]->primitive_type << "\n";
            }

            for (u32 i = 0; i < modelScene->meshes.size(); i++)
            {
                std::cout << "Mesh " << i << " material index: " << modelScene->meshes[i]->material_index << "\n";
            }
        }
        else
        {
            std::cout << "Error reading: " << filename << "\n";
        }
    }
}

void SystemManager::readFile()
{
    SystemUtils::selectFile();
}