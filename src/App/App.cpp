#include "App.h"

void App::init()
{
    // Image
    std::shared_ptr<Image> image = std::make_shared<Image>(256, 256);

    // Render
    std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(image);
    renderer->render();
}
