#include "App.h"

void App::init()
{
    // Image
    std::shared_ptr<Image> image = std::make_shared<Image>(256);

    // Camera
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(image);

    // Render
    std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(camera);
    renderer->render();
}
