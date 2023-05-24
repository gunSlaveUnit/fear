//
// Created by gunSlaveUnit on 24.05.2023.
//

#include "fear.hpp"

namespace fear {
    void Fear::init() {
        glfwInit();
        _init_window();
    }

    void Fear::_init_window() {
        _window = glfwCreateWindow(800, 400, "FEAR", nullptr, nullptr);
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
