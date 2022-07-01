#include <pch.h>

#include <Managers/SystemManager.h>
#include <Renderer.h>

SystemManager::SystemManager() : keys()
{
    window = nullptr;
    closeWindow = false;
}

void SystemManager::init()
{
    init_window();
    init_renderer();
}

void SystemManager::init_window()
{
    closeWindow = false;

    /* Initialize the library */
    if (!glfwInit())
        closeWindow = true;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hair Simulation", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        closeWindow = true;
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, this);

    gladLoadGL();

    // Print hardware detils

    int CPUInfo[4] = { -1 };
    unsigned   nExIds, i = 0;
    char CPUBrandString[0x40];
    // Get the information associated with each extended ID.
    __cpuid(CPUInfo, 0x80000000);
    nExIds = CPUInfo[0];
    for (i = 0x80000000; i <= nExIds; ++i)
    {
        __cpuid(CPUInfo, i);
        // Interpret CPU brand string
        if (i == 0x80000002)
            memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000003)
            memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000004)
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
    }
    //string includes manufacturer, model and clockspeed
    printf("CPU: %s\n", CPUBrandString);

    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    printf("System Memory (RAM): %i MB\n", (statex.ullTotalPhys / 1024) / 1024);

    printf("GPU: %s\n", glGetString(GL_RENDERER));
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));

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

void SystemManager::init_renderer()
{
    renderer = new Renderer();
}

void SystemManager::update()
{
    update_inputs();

    if (glfwWindowShouldClose(window))
    {
        closeWindow = true;

        glfwTerminate();
    }

    update_renderer();

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

            renderer->addMeshScene(modelScene);

            // Clear mesh data from cpu
            for (Mesh* mesh : modelScene->meshes)
            {
                delete mesh;
            }
            modelScene->meshes.clear();
        }
        else
        {
            std::cout << "Error reading: " << modelFilename << "\n";
        }
    }
}

void SystemManager::update_renderer()
{
    renderer->draw();
}

void SystemManager::readFile()
{
    SystemUtils::selectFile();
}