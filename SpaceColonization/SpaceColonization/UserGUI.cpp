#include "UserGUI.h"

void UserGUI::Init(sf::RenderWindow* window) {

	LOG("Initializing ImGUI...");

	IMGUI_CHECKVERSION();
	ImGui::SFML::Init(*window);

	if (m_theme_names.empty()) {
		for (auto& kv : ThemeRegistry) {
			m_theme_names.emplace_back(kv.first);
		}
		std::sort(m_theme_names.begin(), m_theme_names.end()); // optional: sorted list
	}

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

void UserGUI::ThemeSelector() {

	ImGui::Text("Select Theme:");
	if (ImGui::BeginCombo("##ThemeCombo", m_theme_names[m_current_theme_index].c_str())) {

		for (int i = 0; i < m_theme_names.size(); i++) {

			bool isSelected = (m_current_theme_index == i);
			if (ImGui::Selectable(m_theme_names[i].c_str(), isSelected)) {

				m_current_theme_index = i;
				// Apply the selected theme
				ThemeRegistry[m_theme_names[i]](m_style);
			}
			if (isSelected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
}

void UserGUI::InitStyle() {

    LOG("Initializing ImGUI styles...");

    m_style = &ImGui::GetStyle();

	m_style->Alpha = 1.0f;
	m_style->DisabledAlpha = 1.0f;
	m_style->WindowPadding = ImVec2(12.0f, 12.0f);
	m_style->WindowBorderSize = 0.0f;
	m_style->WindowMinSize = ImVec2(20.0f, 20.0f);
	m_style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
	m_style->WindowMenuButtonPosition = ImGuiDir_Right;
	m_style->ChildRounding = 0.0f;
	m_style->ChildBorderSize = 1.0f;
	m_style->PopupRounding = 0.0f;
	m_style->PopupBorderSize = 1.0f;
	m_style->FramePadding = ImVec2(20.0f, 3.400000095367432f);
	m_style->FrameRounding = 11.89999961853027f;
	m_style->FrameBorderSize = 0.0f;
	m_style->ItemSpacing = ImVec2(4.300000190734863f, 5.5f);
	m_style->ItemInnerSpacing = ImVec2(7.099999904632568f, 1.799999952316284f);
	m_style->CellPadding = ImVec2(12.10000038146973f, 9.199999809265137f);
	m_style->IndentSpacing = 15.f;
	m_style->ColumnsMinSpacing = 4.900000095367432f;
	m_style->ScrollbarSize = 11.60000038146973f;
	m_style->ScrollbarRounding = 15.89999961853027f;
	m_style->GrabMinSize = 3.700000047683716f;
	m_style->GrabRounding = 20.0f;
	m_style->TabRounding = 0.0f;
	m_style->TabBorderSize = 0.0f;
	m_style->TabMinWidthForCloseButton = 0.0f;
	m_style->ColorButtonPosition = ImGuiDir_Right;
	m_style->ButtonTextAlign = ImVec2(0.5f, 0.5f);
	m_style->SelectableTextAlign = ImVec2(0.0f, 0.0f);

	m_style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.2745098173618317f, 0.3176470696926117f, 0.4509803950786591f, 1.0f);
	m_style->Colors[ImGuiCol_WindowBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	m_style->Colors[ImGuiCol_ChildBg] = ImVec4(0.09250493347644806f, 0.100297249853611f, 0.1158798336982727f, 1.0f);
	m_style->Colors[ImGuiCol_PopupBg] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	m_style->Colors[ImGuiCol_Border] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	m_style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	m_style->Colors[ImGuiCol_FrameBg] = ImVec4(0.1120669096708298f, 0.1262156516313553f, 0.1545064449310303f, 1.0f);
	m_style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	m_style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	m_style->Colors[ImGuiCol_TitleBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	m_style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	m_style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	m_style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
	m_style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	m_style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	m_style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.1568627506494522f, 0.168627455830574f, 0.1921568661928177f, 1.0f);
	m_style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	m_style->Colors[ImGuiCol_CheckMark] = ImVec4(0.9725490212440491f, 1.0f, 0.4980392158031464f, 1.0f);
	m_style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.971993625164032f, 1.0f, 0.4980392456054688f, 1.0f);
	m_style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.0f, 0.7953379154205322f, 0.4980392456054688f, 1.0f);
	m_style->Colors[ImGuiCol_Button] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	m_style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.1821731775999069f, 0.1897992044687271f, 0.1974248886108398f, 1.0f);
	m_style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.1545050293207169f, 0.1545048952102661f, 0.1545064449310303f, 1.0f);
	m_style->Colors[ImGuiCol_Header] = ImVec4(0.1414651423692703f, 0.1629818230867386f, 0.2060086131095886f, 1.0f);
	m_style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.1072951927781105f, 0.107295036315918f, 0.1072961091995239f, 1.0f);
	m_style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	m_style->Colors[ImGuiCol_Separator] = ImVec4(0.1293079704046249f, 0.1479243338108063f, 0.1931330561637878f, 1.0f);
	m_style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
	m_style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.1568627506494522f, 0.1843137294054031f, 0.250980406999588f, 1.0f);
	m_style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.1459212601184845f, 0.1459220051765442f, 0.1459227204322815f, 1.0f);
	m_style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.9725490212440491f, 1.0f, 0.4980392158031464f, 1.0f);
	m_style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.999999463558197f, 1.0f, 0.9999899864196777f, 1.0f);
	m_style->Colors[ImGuiCol_Tab] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	m_style->Colors[ImGuiCol_TabHovered] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	m_style->Colors[ImGuiCol_TabActive] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	m_style->Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0784313753247261f, 0.08627451211214066f, 0.1019607856869698f, 1.0f);
	m_style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1249424293637276f, 0.2735691666603088f, 0.5708154439926147f, 1.0f);
	m_style->Colors[ImGuiCol_PlotLines] = ImVec4(0.5215686559677124f, 0.6000000238418579f, 0.7019608020782471f, 1.0f);
	m_style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.03921568766236305f, 0.9803921580314636f, 0.9803921580314636f, 1.0f);
	m_style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8841201663017273f, 0.7941429018974304f, 0.5615870356559753f, 1.0f);
	m_style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.9570815563201904f, 0.9570719599723816f, 0.9570761322975159f, 1.0f);
	m_style->Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	m_style->Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.0470588244497776f, 0.05490196123719215f, 0.07058823853731155f, 1.0f);
	m_style->Colors[ImGuiCol_TableBorderLight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_style->Colors[ImGuiCol_TableRowBg] = ImVec4(0.1176470592617989f, 0.1333333402872086f, 0.1490196138620377f, 1.0f);
	m_style->Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.09803921729326248f, 0.105882354080677f, 0.1215686276555061f, 1.0f);
	m_style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.9356134533882141f, 0.9356129765510559f, 0.9356223344802856f, 1.0f);
	m_style->Colors[ImGuiCol_DragDropTarget] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	m_style->Colors[ImGuiCol_NavHighlight] = ImVec4(0.266094446182251f, 0.2890366911888123f, 1.0f, 1.0f);
	m_style->Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.4980392158031464f, 0.5137255191802979f, 1.0f, 1.0f);
	m_style->Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);
	m_style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.196078434586525f, 0.1764705926179886f, 0.5450980663299561f, 0.501960813999176f);

    LOG("--- ImGUI styles initialized ---\n");
}