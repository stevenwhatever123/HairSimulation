#include <pch.h>

#include <SystemManager.h>

#include <assimp/Importer.hpp>

int main(void)
{
    SystemManager* systemManager = new SystemManager();

    systemManager->init();

    while (!systemManager->shouldCloseWindow())
    {
        systemManager->update();
    }

    return 0;
}