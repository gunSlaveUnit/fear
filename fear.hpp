//
// Created by gunSlaveUnit on 24.05.2023.
//

#ifndef FEAR_FEAR_HPP
#define FEAR_FEAR_HPP

#define GLFW_INCLUDE_VULKAN

#include <iostream>

#include <GLFW/glfw3.h>

namespace fear {
    class Fear {

    public:
        void init();

        void run();

        void terminate();

    private:
        void _init_window();

        void _create_instance();

        GLFWwindow *_window;
        VkInstance _instance;
    };
}

#endif //FEAR_FEAR_HPP
