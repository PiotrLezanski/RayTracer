//#include <GLFW/glfw3.h>
//#include "imgui.h"
//#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl3.h"
#include <iostream>

#include "utils/Vec3.h"
#include "utils/color.h"

using color = Vec3<double>;

int main() {

    // Image
    int image_width = 256;
    int image_height = 256;

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = 0; j < image_height; j++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) 
        {
            const color& pixelColor = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.0);
            ColorUtils::printColor(std::cout, pixelColor);
        }
    }
    std::clog << "\rDone.                 \n";
}