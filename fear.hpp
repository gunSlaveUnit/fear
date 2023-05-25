//
// Created by gunSlaveUnit on 24.05.2023.
//

#ifndef FEAR_FEAR_HPP
#define FEAR_FEAR_HPP

#define GLFW_INCLUDE_VULKAN

#include <iostream>
#include <vector>

#include <GLFW/glfw3.h>

#include "types.h"

namespace fear {
    class Fear {

    public:
        void init();

        void run();

        void terminate();

    private:
        void _init_window();

        void _create_instance();

        void _pick_physical_device();

        GLFWwindow *_window;
        VkInstance _instance;
        VkPhysicalDevice _physical_device;
    };
}

#endif //FEAR_FEAR_HPP
