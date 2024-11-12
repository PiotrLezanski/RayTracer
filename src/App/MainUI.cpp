#include "MainUI.h"

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "../core/Windows/WindowsBuilder.h"

MainUI::MainUI(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera,
	std::shared_ptr<Renderer> renderer)
	: m_image(image), m_camera(camera), m_renderer(renderer)
{
}

void MainUI::init()
{
	initializeGLFW();
    initializeWindow();
    setupOpenGL();
    setupImGuiContext();
    setupUI();
    cleanup();
}

void MainUI::initializeGLFW()
{
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void MainUI::initializeWindow()
{
	m_window = glfwCreateWindow(1280, 720, "ImGui Demo", nullptr, nullptr);
	if (!m_window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1); // Enable vsync
}

void MainUI::setupOpenGL()
{
}

void MainUI::setupImGuiContext()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    glfwInit();
    // Load font and check if successful
    if (!io.Fonts->AddFontFromFileTTF("C:/pv/uj/RayTracer/Resources/RobotoMedium.ttf", 20.0f))
        std::cerr << "Failed to load font!" << std::endl;

    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void MainUI::setupUI()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // main method to build ImGui windows
        buildUI(); 

        // Render ImGui
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(m_window);
    }
}

void MainUI::buildUI()
{
    WindowsBuilder windowsBuilder;
    windowsBuilder.buildUI();
}

void MainUI::cleanup()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_window);
	glfwTerminate();
}