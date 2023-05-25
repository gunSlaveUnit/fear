//
// Created by gunSlaveUnit on 24.05.2023.
//

#include "fear.hpp"

namespace fear {
    void Fear::init() {
        glfwInit();
        _init_window();
        _create_instance();
    }

    void Fear::_init_window() {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        _window = glfwCreateWindow(800, 400, "FEAR", nullptr, nullptr);
        if (_window)
            std::cout << "A GLFW window was created.\n";
        else
            std::clog << "ERROR: GLFW can't create a window.\n";
    }

    void Fear::_create_instance() {
        VkApplicationInfo application_info{
                .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                .pNext = nullptr,
                .pApplicationName = "FEAR",
                .applicationVersion = VK_MAKE_API_VERSION(0, 0, 1, 0),
                .pEngineName = "RAYNEVIR",
                .engineVersion = VK_MAKE_API_VERSION(0, 0, 1, 0),
                .apiVersion = VK_VERSION_1_3
        };

        VkInstanceCreateInfo instance_create_info{
                .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                .pNext = nullptr,
                .flags = 0,
                .pApplicationInfo = &application_info,
                .enabledLayerCount = 0,
                .ppEnabledLayerNames = nullptr,
                .enabledExtensionCount = 0,
                .ppEnabledExtensionNames = nullptr,
        };

        if (vkCreateInstance(&instance_create_info, nullptr, &_instance) == VK_SUCCESS)
            std::cout << "A Vulkan instance was created.\n";
        else
            std::clog << "ERROR: Vulkan can't create an instance.\n";
    }

    void Fear::run() {
        while (!glfwWindowShouldClose(_window)) {
            glfwPollEvents();
        }
    }

    void Fear::terminate() {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }
}
