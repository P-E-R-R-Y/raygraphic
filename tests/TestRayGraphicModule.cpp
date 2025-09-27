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

// ------------------ TESTS ------------------

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
}