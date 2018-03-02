/**
 * @file snaze.h
 * @author Anderson Caio & Rayan Avelino
 * @date 21/06/2017
 */
#ifndef _SNAZE_H_
#define _SNAZE_H_

#include <iostream>			//!< cout
#include <cstdlib>			//!< system()
#include <fstream>			//!< open()
#include <random>			//!< random_device
#include <string>			//!< string
#include <chrono>			//!< chrono
#include <thread>			//!< sleep_for()
#include <deque>			//!< deque

/// Maximum size of the Maze.
#define MAX_ROW 100
#define MAX_COL 100

/// Defines the direction where the Snake is headed.
enum Direction{

	NORTH = 0,
	SOUTH,
	EAST,
	WEST

};

/// A struct to save the right position in the Maze. 
struct Position{

	int r;
	int c;

	Position()
		: r(0)
		, c(0)
	{ /*Empty */ }

	Position(int p_row, int p_col)
		:r(p_row)
		,c(p_col)
	{ /* Empty */ }

};

/**
 * @class SnakeGame
 *
 * This class constains a set of functions that read 
 * a Maze provided by the player and make the Snake
 * found all the food that will be randomly generated.
 *
 */
class SnakeGame{

	private:
		/**
		 * @class Snake
		 *
		 * This class contains a set of functions that 
		 * will represent the Snake through out the game.
		 *
		 */
		class Snake{

			private: 
				/// Size of the Snake.
				int size;

			public:
				/// [I] SPECIAL MEMBERS
				Snake();
				~Snake();

				/// [II] FUNCTIONS
				/// Returns the size of the Snake.
				int get_size();
				/// Sets the size of the Snake.
				void set_size(int);
				/// Increases the size of the Snake.
				int increase_size();

		};

		/// Members.
		int row;
		int column;
		int end_game;
		/// Food's position and amount.
		int food;
		int food_row;
		int food_column;
		/// Snake's position.
		Snake snk;
		int lives;
		int safe_row;
		int safe_col;
		int start_row;
		int start_column;
		/// Snake's body.
		std::deque<Position> body;
		///Head direction.
		int drct;
		/// Path.
		std::deque<Position> path;
		/// Maze.
		int maze[MAX_ROW][MAX_COL];

	public:
		/// [I] FUNCTIONS
		/// Reads the file and sets the game.
		void initialize_game(std::string);
		/// Welcome messenger.
		void initial_state();
		/// Waits user input.
		void press_button();
		/// Generates the food.
		void generate_food();
		/// Process all the events for the game.
		void process_events();
			/// Finds the food.
			bool find_solution(int , int );
			/// Prepares the path for the Snake.
			void prepare_path();
			/// Removes the edges of the body.
			void clear_body();
			/// Moves the snake.
			void next_move();
			/// Resets the maze.
			void clear();
		/// Prints the Maze and its contents.
		void render();
		/// Ends of the game.
		bool game_over();
		/// Prints final messenger
		void print_result();

};

#include "snaze.inl"

#endif