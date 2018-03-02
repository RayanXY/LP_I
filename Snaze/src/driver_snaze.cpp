#include <iostream>
#include "../include/snaze.h"

int main(int argc, char * argv[]){

	SnakeGame game;

	game.initialize_game(argv[1]);

	game.initial_state();

	while(not game.game_over()){

		game.process_events();

	}

	game.print_result();

}