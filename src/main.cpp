#include <Nexus.h>
#include <iostream>
#include <string>
#include <synchapi.h>
#include <winuser.h>

#include "http.hpp"

AddonAPI* g_addon_api = nullptr;

void simulate_input(DWORD type, WORD virtual_key) {
    WORD scan_code = (WORD)MapVirtualKey(virtual_key, MAPVK_VK_TO_VSC);
    INPUT inputs[2]{};

    for (int i = 0; i < 2; i++) {
        inputs[i].type = type;

        if (type == INPUT_KEYBOARD) {
            inputs[i].ki.wVk = 0;
            inputs[i].ki.wScan = scan_code;
            inputs[i].ki.dwFlags = KEYEVENTF_SCANCODE | (i == 1 ? KEYEVENTF_KEYUP : 0);
        }
    }

    SendInput(2, inputs, sizeof(INPUT));
}

void handle_keybinds(const char* keybind_identifier, bool release) {
    std::string keybind_identifier_string = std::string{keybind_identifier};

    if (keybind_identifier_string == "show_popup" && !release) {
        simulate_input(INPUT_KEYBOARD, 'B');
    }
}

void load_addon(AddonAPI* addon_api) {
    g_addon_api = addon_api;

    g_addon_api->InputBinds.RegisterWithString("show_popup", handle_keybinds, "CTRL+Z");
}

void unload_addon() {
    g_addon_api->InputBinds.Deregister("show_popup");
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
    RareUnidData data = get_rare_unid_fast_farming_profits();
    std::cout << data.tp_profit << "\n";
    std::cout << data.tp_tax_profit << "\n";
    std::cout << data.opened_salvage_profit << "\n";
    std::cout << data.unopened_salvage_profit << "\n";
    std::cout << data.open_extract_salvage_profit << "\n";
}