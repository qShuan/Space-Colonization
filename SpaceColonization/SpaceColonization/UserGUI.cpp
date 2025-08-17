#include "UserGUI.h"

void UserGUI::Init(sf::RenderWindow* window) {

	LOG("Initializing ImGUI...");

	IMGUI_CHECKVERSION();
	ImGui::SFML::Init(*window);

	LOG("--- ImGUI initialized ---\n");
}

void UserGUI::Update(sf::RenderWindow* window, sf::Time dt){

	ImGui::SFML::Update(*window, dt);
}

void UserGUI::ProccessEvent(sf::RenderWindow* window, const sf::Event& event){
	
	ImGui::SFML::ProcessEvent(*window, event);
}

void UserGUI::Render(sf::RenderWindow* window){

	ImGui::SFML::Render(*window);
}

void UserGUI::Close() {

	LOG("Shutting down ImGUI...");
	ImGui::SFML::Shutdown();
	LOG("--- ImGUI has been successfully shutdown ---");
}

void UserGUI::InitStyle() {

    LOG("Initializing ImGUI styles...");

    m_style = &ImGui::GetStyle();

    m_style->WindowPadding = ImVec2(10, 10);
    m_style->WindowRounding = 0.f;
    m_style->FramePadding = ImVec2(5, 5);
    m_style->FrameRounding = 4.0f;
    m_style->ItemSpacing = ImVec2(8, 8);
    m_style->ItemInnerSpacing = ImVec2(2, 6);
    m_style->TabRounding = 0.f;
    m_style->IndentSpacing = 25.0f;
    m_style->ScrollbarSize = 20.0f;
    m_style->ScrollbarRounding = 9.0f;
    m_style->GrabMinSize = 5.0f;
    m_style->GrabRounding = 3.0f;

    m_style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
    m_style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    m_style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.f);
    //m_style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    m_style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    m_style->Colors[ImGuiCol_Border] = ImVec4(0.06f, 0.05f, 0.07f, 1.f);
    m_style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    m_style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    m_style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    m_style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    m_style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    m_style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.15f);
    m_style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 0.75f);
    m_style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.40f, 0.09f, 0.12f, 1.00f);
    m_style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    m_style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    m_style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    m_style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    //m_style->Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
    m_style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    m_style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    m_style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    m_style->Colors[ImGuiCol_Button] = ImVec4(0.20f, 0.19f, 0.22f, 1.00f);
    m_style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    m_style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    m_style->Colors[ImGuiCol_Header] = ImVec4(0.15f, 0.13f, 0.16f, 1.00f);
    m_style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    m_style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    //m_style->Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    //m_style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    //m_style->Colors[ImGuiCol_] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    m_style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    m_style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    m_style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    //m_style->Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
    //m_style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
    //m_style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
    m_style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    m_style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    m_style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    m_style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    m_style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
    m_style->Colors[ImGuiCol_Tab] = ImVec4(0.10f, 0.09f, 0.15f, 1.00f);
    m_style->Colors[ImGuiCol_TabHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    m_style->Colors[ImGuiCol_TabActive] = ImVec4(0.30f, 0.30f, 0.32f, 1.00f);
    //m_style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);

    LOG("--- ImGUI styles initialized ---\n");
}