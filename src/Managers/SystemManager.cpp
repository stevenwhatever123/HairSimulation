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
        std::string modelFilename;
        std::string materialFilename;
        std::tie(readSuccess, modelFilename) = SystemUtils::selectFile();

        bool materialReadSuccess = false;
        materialFilename = modelFilename.substr(0, modelFilename.find_last_of('.')) + ".mtl";
        if (std::filesystem::exists(materialFilename)) materialReadSuccess = true;

        if (readSuccess)
        {
            std::cout << "Success reading: " << modelFilename << "\n";
            Model* modelScene = SystemUtils::readModel(modelFilename.c_str());
            std::cout << "Nubmer of Meshes: " << modelScene->meshes.size() << "\n";

            if (materialReadSuccess)
                std::cout << "Material Read Successfully!" << "\n";
            else
                std::cout << "Error: Cannot find: " << materialFilename << "\n";

            for (u32 i = 0; i < modelScene->meshes.size(); i++)
            {
                std::cout << "Mesh " << i << "\n";
                std::cout << "Name: " << modelScene->meshes[i]->name << "\n";
                std::cout << "Primitive type: " << 
                    modelScene->meshes[i]->primitive_type << "\n";
                std::cout << "Material index: " << 
                    modelScene->meshes[i]->material_index << "\n";
                std::cout << "===============================" << "\n";
            }

            for (u32 i = 0; i < modelScene->materials.size(); i++)
            {
                std::cout << "Material " << i << "\n";
                std::cout << "Name: " << modelScene->materials[i]->name << "\n";
                std::cout << "Color: " << 
                    glm::to_string(modelScene->materials[i]->color) << "\n";
                std::cout << "Has Texture: " << modelScene->materials[i]->has_texture << "\n";
                std::cout << "Texture Name: " << modelScene->materials[i]->texture_name << "\n";
                std::cout << "===============================" << "\n";
            }
        }
        else
        {
            std::cout << "Error reading: " << modelFilename << "\n";
        }
    }
}

void SystemManager::readFile()
{
    SystemUtils::selectFile();
}