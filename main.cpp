#include "fear.hpp"

int main() {
    fear::Fear game{};
    game.init();
    game.run();
    game.terminate();
}
