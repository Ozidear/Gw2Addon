#include <Nexus.h>
#include <string>

#include "http.h"

AddonAPI* g_addon_api = nullptr;

void handle_keybinds(const char* keybind_identifier, bool release) {
    std::string keybind_identifier_string = std::string{keybind_identifier};

    if (keybind_identifier_string == "test") {
        g_addon_api->UI.SendAlert("Test alert!!!");
    }
}

void load_addon(AddonAPI* addon_api) {
    g_addon_api = addon_api;

    g_addon_api->InputBinds.RegisterWithString("test", handle_keybinds, "CTRL+N");
}

void unload_addon() {
    // Addon unloading logic here
}

extern "C" __declspec(dllexport)
AddonDefinition* GetAddonDef() {
    return new AddonDefinition{
        .Signature=-1012,
        .APIVersion=NEXUS_API_VERSION,
        .Name="TestAddon",
        .Version=AddonVersion{1, 0, 0, 0},
        .Author="Ozidear",
        .Description="Testing description",
        .Load=load_addon,
        .Unload=unload_addon,
        .Flags=EAddonFlags_None,
        // .Provider=EUpdateProvider_GitHub,
        // .UpdateLink="https://github.com/RaidcoreGG/GW2-Compass"
    };
}

int main() {
    https();
}

