//
// Created by gunSlaveUnit on 24.05.2023.
//

#ifndef FEAR_FEAR_HPP
#define FEAR_FEAR_HPP

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

namespace fear {
    class Fear {

    public:
        void init();

        void run();

    private:
        void _init_window();

        GLFWwindow *_window;
    };
}

#endif //FEAR_FEAR_HPP
