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
        _window = glfwCreateWindow(1000, 500, "FEAR", nullptr, nullptr);
    }

    void Fear::run() {

    }
}
