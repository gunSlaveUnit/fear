//
// Created by gunSlaveUnit on 24.05.2023.
//

#ifndef FEAR_FEAR_HPP
#define FEAR_FEAR_HPP

#define GLFW_INCLUDE_VULKAN

#include <iostream>
#include <vector>
#include <cstring>
#include <set>

#include <GLFW/glfw3.h>

#include "types.h"
#include "queue_family_indices.hpp"

namespace fear {
    class Fear {

    public:
        void init();

        void run();

        void terminate();

    private:
        void _init_window();

        void _create_instance();

        bool _check_validation_layers_support();

        [[nodiscard]] std::vector<const char*> get_required_extensions() const;

        void _pick_physical_device();

        bool _is_physical_device_suitable(const VkPhysicalDevice &candidate);

        void _create_logical_device();

#ifdef NDEBUG
        const bool ENABLE_VALIDATION_LAYERS = false;
#else
        const bool ENABLE_VALIDATION_LAYERS = true;
#endif
        const std::vector<const char *> VALIDATION_LAYERS = {
                "VK_LAYER_KHRONOS_validation",
                "VK_LAYER_LUNARG_monitor"
        };

        GLFWwindow *_window;
        VkInstance _instance;
        VkPhysicalDevice _physical_device;
        QueueFamilyIndices _queue_family_indices;
        VkDevice _logical_device;
        VkQueue _graphics_queue;
    };
}

#endif //FEAR_FEAR_HPP
