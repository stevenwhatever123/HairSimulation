#include <pch.h>

#include <headers/SystemManager.h>

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