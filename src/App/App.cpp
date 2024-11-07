#include "App.h"

#include "../core/Image.h"
#include "../core/Renderer.h"
#include "../core/Camera.h"

void App::init()
{
    prepareMainUI();
    m_mainUI->init();
}

void App::prepareMainUI()
{
    // Image
    std::shared_ptr<Image> image = std::make_shared<Image>(256);

    // Camera
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(image);

    // Render
    std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(camera);

    m_mainUI = std::make_unique<MainUI>(image, camera, renderer);
}
