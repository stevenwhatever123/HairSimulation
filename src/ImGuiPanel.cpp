#include "pch.h"
#include "ImGuiPanel.h"

void SystemUI::init_imgui(GLFWwindow* window)
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    const char* glsl_version = "#version 450";

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void SystemUI::update_imgui(SystemManager* sys)
{
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Hello World");

    ImGui::SetWindowSize(ImVec2(200, 300));

    SystemUI::import_head_handle(sys);

    SystemUI::single_strand(sys);

    ImGui::End();

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void SystemUI::import_head_handle(SystemManager* sys)
{
    if (sys->models.size() < 1)
    {
        if (ImGui::Button("Load Model"))
        {
            bool readSuccess;
            std::string modelFilename;
            std::string materialFilename;
            std::tie(readSuccess, modelFilename) = SystemUtils::selectFile();

            sys->hairManager->numMassPointPerStrand = 4;

            bool materialReadSuccess = false;
            materialFilename = modelFilename.substr(0, modelFilename.find_last_of('.')) + ".mtl";
            if (std::filesystem::exists(materialFilename)) materialReadSuccess = true;

            if (readSuccess)
            {
                //printf("===============================\n");

                printf("Success reading: %s\n", modelFilename.c_str());

                Model* modelScene = SystemUtils::readModel(modelFilename.c_str());

                sys->models.push_back(modelScene);

                sys->renderer->addMeshScene(modelScene);
            }
        }
    }

    if (sys->models.size() > 0 && sys->hairManager->springs.size() < 1)
    {
        ImGui::SliderInt("Number of mass point per strand", &sys->hairManager->numMassPointPerStrand, 1, 15);

        if (ImGui::Button("Generate Hair"))
        {
            for (Mesh* mesh : sys->models[0]->meshes)
            {
                if (mesh->isHead || mesh->isForeHead)
                {
                    sys->hairManager->generateHairRootMassPoints(mesh);
                }
            }

            sys->hairManager->generateHairStrandMassPoints(sys->hairManager->numMassPointPerStrand);

            // Hair Strand rendering
            Mesh* hairStrandMesh = sys->hairManager->getHairStrandSpringsAsMeshes();
            hairStrandMesh->generateBuffers(sys->currentProgram, 1);
            sys->renderer->addMesh(hairStrandMesh);
        }
    }

    if (sys->models.size() > 0 && sys->hairManager->springs.size() > 0)
    {
        f32 stiffness = sys->hairManager->stiffness;
        f32 damping = sys->hairManager->damping;

        ImGui::SliderFloat("Stiffness", &stiffness, 0.0f, 1.0f);
        ImGui::SliderFloat("Damping", &damping, 0.0f, 1.0f);

        if (stiffness != sys->hairManager->stiffness)
        {
            sys->hairManager->setStiffness(stiffness);
        }
        if (damping != sys->hairManager->damping)
        {
            sys->hairManager->setDamping(damping);
        }

        if (!sys->simulate)
        {
            if (ImGui::Button("Simulate"))
            {
                sys->simulate = !sys->simulate;
                sys->collisionManager->detectCollision();
            }
        }
        else
        {
            if (ImGui::Button("Stop"))
            {
                sys->simulate = !sys->simulate;
                sys->collisionManager->undetectCollision();
            }
        }
    }
}

void SystemUI::single_strand(SystemManager* sys)
{
    if (sys->hairManager->mass_points.size() < 1)
    {
        if (ImGui::Button("Single Strand"))
        {
            sys->hairManager->generateSingleHairStrand();
            //Mesh* hairStrandMesh = sys->hairManager->getHairStrandSpringsAsMeshes();
            Mesh* hairStrandMesh = sys->hairManager->getHairStrandSpringsAsCurveMeshes();
            hairStrandMesh->generateBuffers(sys->currentProgram, 1);
            sys->renderer->addMesh(hairStrandMesh);
        }
        return;
    }

    if (!sys->simulate)
    {
        if (ImGui::Button("Simulate"))
        {
            sys->simulate = !sys->simulate;
            sys->collisionManager->detectCollision();
        }
    }
    else
    {
        if (ImGui::Button("Stop"))
        {
            sys->simulate = !sys->simulate;
            sys->collisionManager->undetectCollision();
        }
    }
}