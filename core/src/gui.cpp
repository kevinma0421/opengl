#include "gui.h"

Gui::Gui(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}
Gui::~Gui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
void Gui::frame(Camera &camera, float &rotationSpeed)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Controls");
    ImGui::InputFloat("Precise Speed", &rotationSpeed, 0.1f, 0.1f, "%.6f");

    // Clamp to 0 - 5 range
    if (rotationSpeed < 0.0f)
        rotationSpeed = 0.0f;
    if (rotationSpeed > 3.0f)
        rotationSpeed = 3.0f;
    if (rotationSpeed == 3.0f)
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Max speed reached (3.0)");

    if (ImGui::Button("Reset"))
    {
        camera.reset();
        rotationSpeed = 2 * glm::pi<float>() / 86164.0f;
    }
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 10.0f, 10.0f), ImGuiCond_Always, ImVec2(1.0f, 0.0f));
    ImGui::SetNextWindowBgAlpha(0.35f);

    if (ImGui::Begin("FPS Overlay", nullptr,
                     ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
                         ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove))
    {
        ImGui::Text("FPS: %d", fps());
    }
    ImGui::End();
}
void Gui::render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
int Gui::fps()
{
    static double lastTime = glfwGetTime();
    static int frameCount = 0;
    static int lastFPS = 0;

    double currentTime = glfwGetTime();
    frameCount++;

    if (currentTime - lastTime >= 1.0)
    {
        lastFPS = frameCount;
        frameCount = 0;
        lastTime = currentTime;
    }

    return lastFPS;
}
