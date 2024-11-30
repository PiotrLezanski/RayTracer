#include "MainUI.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

MainUI::MainUI()
{
    m_windowsBuilder = std::make_unique<WindowsBuilder>();
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

void MainUI::setupOpenGL()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }
}

void MainUI::initializeWindow()
{
	m_mainWindow = glfwCreateWindow(1280, 720, "ImGui Demo", nullptr, nullptr);
	if (!m_mainWindow)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_mainWindow);
	glfwSwapInterval(1); // Enable vsync
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
    /*if (!io.Fonts->AddFontFromFileTTF("C:/pv/uj/RayTracer/Resources/RobotoMedium.ttf", 20.0f))
        std::cerr << "Failed to load font!" << std::endl;*/

    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(m_mainWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void MainUI::setupUI()
{
    while (!glfwWindowShouldClose(m_mainWindow))
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
        glfwGetFramebufferSize(m_mainWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(m_mainWindow);
    }
}

void MainUI::buildUI()
{
    m_windowsBuilder->buildUI();
}

void MainUI::cleanup()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_mainWindow);
	glfwTerminate();
}
