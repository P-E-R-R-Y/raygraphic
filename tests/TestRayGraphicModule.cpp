/**
 * @file TestRayGraphicModule.cpp
 * @author Perry Chouteau (perry.chouteau@outlook.com)
 * @brief raygraphic dll testing
 * @date 2025-09-26
 */

#include <gtest/gtest.h>

#include <dlfcn.h>
#include "IGraphicModule.hpp"
#include <iostream>
/*
// function pointer types
using CreateModuleFn = IModule* (*)();
using DestroyModuleFn = void (*)(IModule*);

// shared test fixture
class RaylibEnv : public ::testing::Environment {
public:
    static void* handle;
    static CreateModuleFn createFn;
    static DestroyModuleFn destroyFn;

    void SetUp() override {
        if (handle) return; // already loaded

        const char* libPath =
        #if defined(__APPLE__)
            "libraygraphic.dylib";
        #else
            "libraygraphic.so";
        #endif

        handle = dlopen(libPath, RTLD_LAZY);
        if (!handle) {
            FAIL() << "dlopen failed: " << dlerror();
        }

        createFn = reinterpret_cast<CreateModuleFn>(dlsym(handle, "createModule"));
        destroyFn = reinterpret_cast<DestroyModuleFn>(dlsym(handle, "deleteModule"));
        if (!createFn || !destroyFn) {
            FAIL() << "dlsym failed: " << dlerror();
        }
    }

    void TearDown() override {
        if (handle) {
            dlclose(handle);
            handle = nullptr;
        }
    }
};

// static storage
void* RaylibEnv::handle = nullptr;
CreateModuleFn RaylibEnv::createFn = nullptr;
DestroyModuleFn RaylibEnv::destroyFn = nullptr;

// Register environment
::testing::Environment* const raylib_env = ::testing::AddGlobalTestEnvironment(new RaylibEnv);
*/
// ------------------ TESTS ------------------

using CreateModuleFn = IModule* (*)();
using DestroyModuleFn = void (*)(IModule*);

TEST(RayGraphicModuleTest, LoadLibrary) {
#if defined(__APPLE__)
    const char* libPath = "libraygraphic.dylib";
#elif defined(__linux__)
    const char* libPath = "libraygraphic.so";
#else
    GTEST_FAIL() << "Unsupported platform";
#endif

    std::cerr << "[DEBUG] Trying dlopen: " << libPath << std::endl;

    void* handle = dlopen(libPath, RTLD_LAZY);
    ASSERT_NE(handle, nullptr) << "dlopen failed: " << dlerror();

    dlclose(handle);
}

TEST(RayGraphicModuleTest, ResolveSymbols) {
#if defined(__APPLE__)
    const char* libPath = "libraygraphic.dylib";
#elif defined(__linux__)
    const char* libPath = "libraygraphic.so";
#else
    GTEST_FAIL() << "Unsupported platform";
#endif

    void* handle = dlopen(libPath, RTLD_LAZY);
    ASSERT_NE(handle, nullptr) << "dlopen failed: " << dlerror();

    dlerror(); // clear old errors

    CreateModuleFn createFn =
        reinterpret_cast<CreateModuleFn>(dlsym(handle, "createModule"));
    const char* err1 = dlerror();
    ASSERT_TRUE(createFn != nullptr && !err1)
        << "dlsym(createModule) failed: " << (err1 ? err1 : "null fn");

    DestroyModuleFn destroyFn =
        reinterpret_cast<DestroyModuleFn>(dlsym(handle, "deleteModule"));
    const char* err2 = dlerror();
    ASSERT_TRUE(destroyFn != nullptr && !err2)
        << "dlsym(deleteModule) failed: " << (err2 ? err2 : "null fn");

    dlclose(handle);
}

TEST(RayGraphicModuleTest, CreateDeleteModule) {
#if defined(__APPLE__)
    const char* libPath = "libraygraphic.dylib";
#elif defined(__linux__)
    const char* libPath = "libraygraphic.so";
#else
    GTEST_FAIL() << "Unsupported platform";
#endif

    void* handle = dlopen(libPath, RTLD_LAZY);
    ASSERT_NE(handle, nullptr) << "dlopen failed: " << dlerror();

    auto createFn = reinterpret_cast<CreateModuleFn>(dlsym(handle, "createModule"));
    auto destroyFn = reinterpret_cast<DestroyModuleFn>(dlsym(handle, "deleteModule"));
    ASSERT_NE(createFn, nullptr) << "Missing createModule";
    ASSERT_NE(destroyFn, nullptr) << "Missing deleteModule";

    IGraphicModule* mod = dynamic_cast<IGraphicModule*>(createFn());
    ASSERT_NE(mod, nullptr) << "createModule returned null";

    destroyFn(mod);

    dlclose(handle);
}
/*
TEST(RayGraphicModuleTest, LoadLibrary) {
    ASSERT_NE(RaylibEnv::handle, nullptr);
    ASSERT_NE(RaylibEnv::createFn, nullptr);
    ASSERT_NE(RaylibEnv::destroyFn, nullptr);
}

TEST(RayGraphicModuleTest, CreateDeleteModule) {
    ASSERT_NE(RaylibEnv::createFn, nullptr);
    ASSERT_NE(RaylibEnv::destroyFn, nullptr);

    IGraphicModule* m = dynamic_cast<IGraphicModule *>(RaylibEnv::createFn());
    ASSERT_NE(m, nullptr);
    RaylibEnv::destroyFn(m);
}*/