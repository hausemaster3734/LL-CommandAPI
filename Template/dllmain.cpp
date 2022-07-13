#include "pch.h"

#include <LLAPI.h>

#include "hausemaster3734/CommandAPI.h"

#pragma comment(lib, "../SDK/Lib/bedrock_server_api.lib")
#pragma comment(lib, "../SDK/Lib/bedrock_server_var.lib")
#pragma comment(lib, "../SDK/Lib/SymDBHelper.lib")
#pragma comment(lib, "../SDK/Lib/LiteLoader.lib")

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if(ul_reason_for_call == DLL_PROCESS_ATTACH) {
        LL::registerPlugin(
                "CommandAPI",
                 "daplforll",
                LL::Version(1, 0, 0, LL::Version::Release),
                std::map<std::string, std::string>{{"Author", "Hausemaster3734"}}
        );
    }
    return TRUE;
}

extern "C" _declspec(dllexport) void onPostInit() {
    std::ios::sync_with_stdio(false);
    auto* loader = new CommandAPI();
    loader->onEnable();
}
