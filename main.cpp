#include "game.h"
#include <chrono>

int main(int argc, char* args[]) {
	srand(std::chrono::system_clock::now().time_since_epoch().count());
	Game game;
	return 0;
}