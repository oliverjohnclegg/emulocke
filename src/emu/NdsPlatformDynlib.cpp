#include <Platform.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#else
#include <dlfcn.h>
#endif

namespace melonDS::Platform {

DynamicLibrary* DynamicLibrary_Load(const char* lib) {
    if (!lib) {
        return nullptr;
    }
#ifdef _WIN32
    return reinterpret_cast<DynamicLibrary*>(LoadLibraryA(lib));
#else
    return reinterpret_cast<DynamicLibrary*>(dlopen(lib, RTLD_NOW));
#endif
}

void DynamicLibrary_Unload(DynamicLibrary* lib) {
    if (!lib) {
        return;
    }
#ifdef _WIN32
    FreeLibrary(reinterpret_cast<HMODULE>(lib));
#else
    dlclose(lib);
#endif
}

void* DynamicLibrary_LoadFunction(DynamicLibrary* lib, const char* name) {
    if (!lib || !name) {
        return nullptr;
    }
#ifdef _WIN32
    return reinterpret_cast<void*>(GetProcAddress(reinterpret_cast<HMODULE>(lib), name));
#else
    return dlsym(lib, name);
#endif
}

}
