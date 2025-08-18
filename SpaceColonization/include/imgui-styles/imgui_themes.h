#pragma once
#include <imgui/imgui.h>
#include <string>
#include <unordered_map>

void ApplyClassicTheme(ImGuiStyle* style);
void ApplyLightTheme(ImGuiStyle* style);
void ApplyDarkTheme(ImGuiStyle* style);
void ApplyCherryTheme(ImGuiStyle* style);
void ApplyDarculaTheme(ImGuiStyle* style);
void ApplyPhotoshopTheme(ImGuiStyle* style);
void ApplyUnrealTheme(ImGuiStyle* style);
void ApplyGoldTheme(ImGuiStyle* style);
void ApplyVisualStudioTheme(ImGuiStyle* style);
void ApplyGreenFontTheme(ImGuiStyle* style);
void ApplyRedFontTheme(ImGuiStyle* style);
void ApplyDeepDarkTheme(ImGuiStyle* style);
void ApplySonicRidersTheme(ImGuiStyle* style);
void ApplyClassicSteamTheme(ImGuiStyle* style);
void ApplyDarkRudaTheme(ImGuiStyle* style);
void ApplyMicrosoftTheme(ImGuiStyle* style);
void ApplySoftCherryTheme(ImGuiStyle* style);
void ApplyledSynthmasterTheme(ImGuiStyle* style);
void ApplyEnemymouseTheme(ImGuiStyle* style);
void ApplyMaterialFlatTheme(ImGuiStyle* style);
void ApplyDiscordDarkTheme(ImGuiStyle* style);
void ApplyBlackDevilTheme(ImGuiStyle* style);
void ApplyRoundedVisualStudioTheme(ImGuiStyle* style);
void ApplyComfyTheme(ImGuiStyle* style);
void ApplyQuickminimallookTheme(ImGuiStyle* style);
void ApplyFutureDarkTheme(ImGuiStyle* style);
void ApplyCleanDarkRedTheme(ImGuiStyle* style);
void ApplyBootstrapDarkTheme(ImGuiStyle* style);
void ApplyMoonlightTheme(ImGuiStyle* style);
void ApplyPurpleComfyTheme(ImGuiStyle* style);
void ApplyRedOniTheme(ImGuiStyle* style);
void ApplyDarkyTheme(ImGuiStyle* style);
void ApplyModernTheme(ImGuiStyle* style);
void ApplyDUCKREDnopeisDARKREDTheme(ImGuiStyle* style);
void ApplyHazyDarkTheme(ImGuiStyle* style);
void ApplyGreenLeafTheme(ImGuiStyle* style);
void ApplyAdobeInspiredTheme(ImGuiStyle* style);
void ApplyEverforestTheme(ImGuiStyle* style);
void ApplyWindarkTheme(ImGuiStyle* style);
void ApplyRestTheme(ImGuiStyle* style);
void ApplyComfortableDarkCyanTheme(ImGuiStyle* style);
void ApplyComfortableLightOrangeTheme(ImGuiStyle* style);
void ApplyVullmadDarkTheme(ImGuiStyle* style);
void ApplyayudarkTheme(ImGuiStyle* style);
void ApplyExcellencyTheme(ImGuiStyle* style);

extern std::unordered_map<std::string, void(*)(ImGuiStyle*)> ThemeRegistry;
