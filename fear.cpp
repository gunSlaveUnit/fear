//
// Created by gunSlaveUnit on 24.05.2023.
//

#include "fear.hpp"

namespace fear {
    void Fear::init() {
        glfwInit();
        _init_window();
        _create_instance();
        _pick_physical_device();
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
        if (ENABLE_VALIDATION_LAYERS && !_check_validation_layers_support())
            std::clog << "ERROR: Vulkan validation layers were requested but not available.\n";

        VkApplicationInfo application_info{
                .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                .pNext = nullptr,
                .pApplicationName = "FEAR",
                .applicationVersion = VK_MAKE_API_VERSION(0, 0, 1, 0),
                .pEngineName = "RAYNEVIR",
                .engineVersion = VK_MAKE_API_VERSION(0, 0, 1, 0),
                .apiVersion = VK_VERSION_1_3
        };

        ufast32 glfw_extensions_count{0};
        const char **glfw_extension_names = glfwGetRequiredInstanceExtensions(&glfw_extensions_count);

        VkInstanceCreateInfo instance_create_info{};
        instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instance_create_info.pApplicationInfo = &application_info;
        instance_create_info.enabledExtensionCount = glfw_extensions_count;
        instance_create_info.ppEnabledExtensionNames = glfw_extension_names;

        if (ENABLE_VALIDATION_LAYERS) {
            instance_create_info.enabledLayerCount = static_cast<ufast32>(VALIDATION_LAYERS.size());
            instance_create_info.ppEnabledLayerNames = VALIDATION_LAYERS.data();
        }

        if (vkCreateInstance(&instance_create_info, nullptr, &_instance) == VK_SUCCESS)
            std::cout << "A Vulkan instance was created.\n";
        else
            std::clog << "ERROR: Vulkan can't create an instance.\n";
    }

    bool Fear::_check_validation_layers_support() {
        ufast32 validation_layer_count;
        vkEnumerateInstanceLayerProperties(&validation_layer_count, nullptr);

        std::vector<VkLayerProperties> available_layers(validation_layer_count);
        vkEnumerateInstanceLayerProperties(&validation_layer_count, available_layers.data());

        for (const char *layer_name: VALIDATION_LAYERS) {
            auto is_layer_found{false};

            for (const auto &available_layer: available_layers)
                if (!strcmp(layer_name, available_layer.layerName)) {
                    is_layer_found = true;
                    break;
                }

            if (!is_layer_found) return false;
        }

        return true;
    }

    void Fear::_pick_physical_device() {
        ufast32 physical_devices_count{0};
        vkEnumeratePhysicalDevices(_instance, &physical_devices_count, nullptr);

        std::vector<VkPhysicalDevice> physical_devices{physical_devices_count};
        vkEnumeratePhysicalDevices(_instance, &physical_devices_count, physical_devices.data());

        std::cout << "Number of found physical devices: " << physical_devices_count << ".\n";
        // TODO: I want to display a list of devices

        // TODO: We need a normal choice of device based on performance, features and other things
        _physical_device = physical_devices[0];
    }

    void Fear::run() {
        while (!glfwWindowShouldClose(_window)) {
            glfwPollEvents();
        }
    }

    void Fear::terminate() {
        vkDestroyInstance(_instance, nullptr);
        glfwDestroyWindow(_window);
        glfwTerminate();
    }
}
