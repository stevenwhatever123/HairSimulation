#include <pch.h>

#include <Managers/SystemManager.h>
#include <Camera.h>

SystemManager::SystemManager() : 
    keys(),
    left_mouse_clicked(0),
    right_mouse_clicked(0),
    mouseX(0),
    mouseY(0),
    modelRotation(0)
{
    window = nullptr;
    closeWindow = false;
}

void SystemManager::init()
{
    init_window();
    init_shaders();
    init_hair_manager();
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
    auto key_callback = [](GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods)
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

    // Mouse key handler
    auto mouse_key_callback = [](GLFWwindow* window, i32 key, i32 action, i32 mods)
    {
        glfwGetWindowUserPointer(window);

        SystemManager* system = (SystemManager*)glfwGetWindowUserPointer(window);
        if (key == GLFW_MOUSE_BUTTON_LEFT)
        {
            if (action == GLFW_PRESS) system->left_mouse_clicked = 1;
            else if (action == GLFW_RELEASE) system->left_mouse_clicked = 0;
        }
        if (key == GLFW_MOUSE_BUTTON_RIGHT)
        {
            if (action == GLFW_PRESS) system->right_mouse_clicked = 1;
            else if (action == GLFW_RELEASE) system->right_mouse_clicked = 0;
        }
    };
    glfwSetMouseButtonCallback(window, mouse_key_callback);
    
    // Mouse movement handler
    auto mouse_pos_callback = [](GLFWwindow* window, double xpos, double ypos)
    {
        glfwGetWindowUserPointer(window);

        SystemManager* system = (SystemManager*)glfwGetWindowUserPointer(window);

        if (system->left_mouse_clicked)
        {
            double lastMouseX = system->mouseX;
            double lastMouseY = system->mouseY;

            double rotateX = xpos - lastMouseX;
            double rotateY = ypos - lastMouseY;

            system->modelRotation.x += rotateX;
            system->modelRotation.y += rotateY;
        }

        system->mouseX = xpos;
        system->mouseY = ypos;
    };
    glfwSetCursorPosCallback(window, mouse_pos_callback);
}

void SystemManager::init_shaders()
{
    // The mesh shader      - 0
    GLShader* meshShaderProgram = new GLShader();
    meshShaderProgram->loadShader("shader/headVertexShader.glsl", "shader/headFragmentShader.glsl");

    shaderPrograms.emplace_back(meshShaderProgram);

    currentProgram = shaderPrograms[0];

    // The hair root shader     - 1
    GLShader* hairRootShaderProgram = new GLShader();
    hairRootShaderProgram->loadShader("shader/hairRootVertexShader.glsl", "shader/hairRootFragmentShader.glsl");

    shaderPrograms.emplace_back(hairRootShaderProgram);
}

void SystemManager::init_hair_manager()
{
    hairManager = new HairManager();
}

void SystemManager::init_renderer()
{
    Camera* camera = new Camera(vec3(0, 0, 0), vec3(0, 0, -1));

    renderer = new Renderer(width, height, camera);
    
    glfwGetFramebufferSize(window, &width, &height);

    renderer->setFramebufferSize(width, height);

    renderer->addShaderPrograms(shaderPrograms);
}

void SystemManager::update()
{
    update_inputs();

    if (glfwWindowShouldClose(window))
    {
        closeWindow = true;

        glfwTerminate();
    }

    update_camera();
    update_renderer();

    glfwSwapBuffers(window);
}

void SystemManager::update_inputs()
{
    /* Poll for and process events */
    glfwPollEvents();

    if (keys['W']) { renderer->getCamera()->moveForward(0.01f); }
    if (keys['S']) { renderer->getCamera()->moveForward(-0.01f); }
    if (keys['A']) { renderer->getCamera()->moveRight(-0.01f); }
    if (keys['D']) { renderer->getCamera()->moveRight(0.01f); }
    if (keys['E']) { renderer->getCamera()->moveUp(0.01f); }
    if (keys['Q']) { renderer->getCamera()->moveUp(-0.01f); }

    if (keys['L']) { loadModel(); }
}

void SystemManager::update_camera()
{
    renderer->getCamera()->updateTransformation();
}

void SystemManager::update_renderer()
{
    glfwGetFramebufferSize(window, &width, &height);

    renderer->setFramebufferSize(width, height);

    renderer->set_all_rendable_rotation(modelRotation);

    renderer->draw();
}

void SystemManager::readFile()
{
    SystemUtils::selectFile();
}

void SystemManager::loadModel()
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
        //printf("===============================\n");

        printf("Success reading: %s\n", modelFilename.c_str());

        Model* modelScene = SystemUtils::readModel(modelFilename.c_str());

        //printModelDetails(*modelScene);

        for (Mesh* mesh : modelScene->meshes)
        {
            if (mesh->isSkull)
            {
                hairManager->generateHairRootMassPoints(mesh);
            }
        }

        hairManager->generateHairStrandMassPoints();

        // Hair Strand rendering
        Mesh* hairStrandMesh = hairManager->getHairStrandSpringsAsMeshes();
        hairStrandMesh->generateBuffers(currentProgram, 1);
        renderer->addMesh(hairStrandMesh);


        renderer->addMeshScene(modelScene);
        for (Mesh* mesh : modelScene->meshes)
        {
            mesh->clear_cpu_memory();
        }

        // Clear mesh data from cpu
        for (Mesh* mesh : modelScene->meshes)
        {
            delete mesh;
        }
        // Clear material data from gpu
        for (Material* material : modelScene->materials)
        {
            delete material;
        }

        modelScene->meshes.clear();
        modelScene->materials.clear();
    }
    else
    {
        std::cout << "Error reading: " << modelFilename << "\n";
    }
}

void SystemManager::printModelDetails(const Model& modelScene)
{
    printf("Nubmer of Meshes: %i\n", modelScene.meshes.size());

    for (u32 i = 0; i < modelScene.meshes.size(); i++)
    {
        printf("Mesh %i\n", i);
        printf("Name: %s\n", modelScene.meshes[i]->name.c_str());
        printf("Primitive type: %i\n", modelScene.meshes[i]->primitive_type);
        printf("Material index: %i\n", modelScene.meshes[i]->material_index);
        printf("===============================\n");
    }

    for (u32 i = 0; i < modelScene.materials.size(); i++)
    {
        printf("Material %i\n", i);
        printf("Name: %s\n", modelScene.materials[i]->name.c_str());
        printf("Color: %s\n", glm::to_string(modelScene.materials[i]->color).c_str());
        printf("Has Texture: %i\n", modelScene.materials[i]->has_texture);
        printf("Texture Name: %s\n", modelScene.materials[i]->texture_name.c_str());
        printf("===============================\n");
    }
}