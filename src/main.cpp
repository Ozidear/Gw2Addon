#include <httplib.h>
#include <iostream>
#include <Nexus.h>
#include <string>

AddonAPI* g_addon_api = nullptr;

void https() {
    httplib::Client client{"https://api.farming-community.eu"};

    auto res = client.Get("/api/v1/details/salvaging/unid-gear/piece-of-rare-unidentified-gear");
    
    // Check result and print raw response
    if (res) {
        std::cout << "HTTP " << res->status << "\n";
        std::cout << res->body << "\n";
    } else {
        std::cerr << "Request failed\n";
    }
}

void handle_keybinds(const char* keybind_identifier, bool release) {
    std::string keybind_identifier_string = std::string(keybind_identifier);

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

