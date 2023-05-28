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

        auto extensions = get_required_extensions();

        VkInstanceCreateInfo instance_create_info{};
        instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instance_create_info.pApplicationInfo = &application_info;
        instance_create_info.enabledExtensionCount = static_cast<ufast32>(extensions.size());
        instance_create_info.ppEnabledExtensionNames = extensions.data();

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

        std::cout << "Available Vulkan validation layers - " << validation_layer_count << ":\n";
        for (const auto &available_layer: available_layers)
            std::cout << "\t- " << available_layer.layerName << ";\n";

        std::cout << "Requested Vulkan validation layers - " << VALIDATION_LAYERS.size() << ":\n";

        for (const char *layer_name: VALIDATION_LAYERS) {
            auto is_layer_found{false};

            for (const auto &available_layer: available_layers)
                if (!strcmp(layer_name, available_layer.layerName)) {
                    is_layer_found = true;
                    std::cout << "\t- " << layer_name << " was found;\n";
                    break;
                }

            if (!is_layer_found) {
                std::clog << "ERROR: Vulkan validation layer" << layer_name << " wasn't found.\n";
                return false;
            }
        }

        return true;
    }

    std::vector<const char*> Fear::get_required_extensions() const {
        ufast32 glfw_extensions_count{0};
        const char **glfw_extension_names = glfwGetRequiredInstanceExtensions(&glfw_extensions_count);

        std::cout << "GLFW required instance extensions - " << glfw_extensions_count << ":\n";
        for (ufast32 i = 0; i < glfw_extensions_count; ++i)
            std::cout << "\t- " << glfw_extension_names[i] << ";\n";

        std::vector<const char*> extensions(glfw_extension_names, glfw_extension_names + glfw_extensions_count);

        if (ENABLE_VALIDATION_LAYERS)
            extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        return extensions;
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
