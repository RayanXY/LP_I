/**
 * 0 (SPACE)
 * 1 (WALL)
 * 2 (START POINT)
 * 3 (FOOD) 
 * 4 (PATH) 
 * 5 (INVISIBLE WALL)
 */

/// Snake class
/// [I] SPECIAL MEMBERS
SnakeGame::Snake::Snake(){
	size = 0;
}
SnakeGame::Snake::~Snake(){
	size = 0;
}
int SnakeGame::Snake::get_size(){
	return size;
}
void SnakeGame::Snake::set_size(int sz){
	size = sz;
}
int SnakeGame::Snake::increase_size(){
	return size++;
}

/// SnakeGame class
void SnakeGame::initialize_game(std::string n){

	/// Variables	
	food = 10;
	lives = 5;
	std::string ch;
	/// Open the file.
	std::ifstream file;
	file.open(n);
	/// Error.
	if(file.fail()){
		std::cout << "Could not open the file.\n";
	}
	/// Gets the sizes of the Maze.
	file >> row >> column;
	/// Defines the sizes of the Maze.
	maze[row][column];
	/// Reading the Maze.
	for(int r = 0; r <= row; r++){
		getline(file, ch);
		for(int c = 0; c < column; c++){
			if(ch[c] == ' '){			//!< SPACE.
				maze[r][c] = 0;
			}else if(ch[c] == '#'){		//!< WALL.
				maze[r][c] = 1;
			}else if(ch[c] == '*'){		//!< START POINT.
				start_row = r;			//!< Defines the Start Point row.
				start_column = c;		//!< Defines the Start Point column.
				safe_row = r;
				safe_col = c;
			}else if(ch[c] == '.'){		//!< INVISIBLE WALL.
				maze[r][c] = 5;
			}
		}
	}

}

void SnakeGame::initial_state(){

	std::cout << "         ---> Snake Game < ----\n";
	std::cout << "----------------------------------------\n";
	std::cout << "Lives: " << lives << " | Foods to eat: " << food << "\n";
	std::cout << "Clear the level to win! Good luck!\n";
	std::cout << "----------------------------------------\n";
	std::cout << ">>> Press ENTER to continue!\n";
	std::cout << "Lives: ";
	for(int f = 0; f < lives; f++){
		std::cout << "\u2764 ";
	}
	std::cout << "     ";
	/// Displays the food.
	std::cout << "Food: ";
	for(int f = 0; f < food; f++){
		std::cout << "\u2605 ";
	}
	std::cout << "\n";
	/// Displays the Maze.
	for(int i = 1; i <= row; i++){
		for(int j = 0; j < column; j++){
			if(maze[i][j] == 0 or maze[i][j] == 5){		//!< SPACE and INVISIBLE WALL.
				std::cout << " ";
			}else if(maze[i][j] == 1){					//!< WALL.
				std::cout << "\u16E5";
			}
		}
		std::cout << "\n";
	}
	press_button();

}

void SnakeGame::press_button(){
	std::cin.get();
}

void SnakeGame::generate_food(){

	/// Variables
	std::random_device rd;
	std::uniform_int_distribution<int> rand_r(1, row-1);
	std::uniform_int_distribution<int> rand_c(1, column-1);
	bool blocked(true);					//!< FLAG.

	while(blocked){
		/// Random position.
		auto r = rand_r(rd);
		auto c = rand_c(rd);

		if(maze[r][c] == 0){			//!< If it is a SPACE.
			/// Determines the food's position.
			food_row = r;
			food_column = c;
			/// Places the food in the Maze.
			maze[r][c] = 3;
			/// Ends the loop.
			blocked = false;
		}
	}

}

bool SnakeGame::find_solution(int s_row, int s_col){

	/// If the Start Point is outside the maze.
	if(s_row < 0 or s_row > MAX_ROW - 1 or s_col < 0 or s_col > MAX_COL - 1){
		return false;
	}
	/// Found the food.
	if(maze[s_row][s_col] == 3){
		/// New Start Point.
		start_row = s_row;
		start_column = s_col;
		
		return true;
	}
	/// Path is blocked,
	if(maze[s_row][s_col] != 0){
		return false;
	}
	/// Right path.
	maze[s_row][s_col] = 4;
	/// Saving the paht.
	Position pos(s_row, s_col);
	path.push_back(pos);
	/// Searching solution.
	if(find_solution(s_row - 1, s_col) == true){		//!< NORTH
		return true;
	}
	if(find_solution(s_row + 1, s_col) == true){		//!< SOUTH
		return true;
	}
	if(find_solution(s_row, s_col + 1) == true){		//!< EAST
		return true;
	}
	if(find_solution(s_row, s_col - 1) == true){		//!< WEST
		return true;
	} 
	/// Wrong path.
	maze[s_row][s_col] = -1;
	/// Erasing the wrong path.
	path.pop_back();
	/// No exit.
	return false;

}

void SnakeGame::next_move(){

	Position pos(start_row, start_column);
	int b = snk.get_size();
	body.push_back(pos);

	while(not path.empty()){
		/// Defines the body.
		clear_body();
		body.push_back(path.front());
		body.pop_front();
		/// Gets the right moviment.
		Position aux = path.front();
		/// Sets the right head.
		if(aux.r < pos.r){
			drct = Direction::NORTH;
		}else if(aux.r > pos.r){
			drct = Direction::SOUTH;
		}else if(aux.c > pos.c){
			drct = Direction::EAST;
		}else if(aux.c < pos.c){
			drct = Direction::WEST;
		}
		pos = aux;
		/// Leaves just the head and the food.
		prepare_path();
		/// Defines the body
		for(int i = 0; i < b+1; i++){
			maze[body[i].r][body[i].c] = 6;
		}
		/// Defines the right path.
		maze[pos.r][pos.c] = 4;
		/// Show the moviment.
		render();
		/// Remove the path walked.
		path.pop_front();
	}

}

void SnakeGame::process_events(){

	/// Creates food.
	generate_food();
	/// Finds the food.
	if(find_solution(start_row, start_column)){
		/// Leaves just the head and the food.
		prepare_path();
		/// Prints the right path.
		next_move();
		/// Decreases food.
		food--;
		/// Eats food, so the size is increased.
		snk.increase_size();
		/// Resets the Maze.
		clear();
	}else{
		/// Keep the direction until it hits a wall.
		Position pos(start_row,start_column);
		if(drct== Direction::NORTH){
			while(maze[pos.r][pos.c] != 1){
				path.push_back(pos);
				pos.r++;
			}
		}else if(drct== Direction::SOUTH){
			while( maze[pos.r][pos.c] != 1){
				path.push_back(pos);
				pos.r--;
			}
		}else if(drct== Direction::EAST){
			while(maze[pos.r][pos.c] != 1){
				path.push_back(pos);
				pos.c++;
			}
		}else if(drct== Direction::WEST){
			while(maze[pos.r][pos.c] != 1){
				path.push_back(pos);
				pos.c--;
			}
		}
		next_move();
		/// No solution time.
		std::cout << "Press <ENTER> to continue!";
		press_button();
		/// Decreases live.
		lives--;
		/// Restarts the Snake
		snk.set_size(0);
		body.clear();
		start_row = safe_row;
		start_column = safe_col;
		/// Restarts the Maze
		food = 10;
		prepare_path();
		clear();
		process_events();

	}

}

void SnakeGame::render(){

	/// Cleans the screen
	std::system("clear");
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	/// Displays the lives.
	std::cout << "Lives: ";
	for(int f = 0; f < lives; f++){
		std::cout << "\u2764 ";
	}
	std::cout << "		";
	/// Displays the food.
	std::cout << "Food: ";
	for(int f = 0; f < food; f++){
		std::cout << "\u2605 ";
	}
	std::cout << "\n";
	/// Displays the Maze.
	for(int i = 1; i <= row; i++){
		for(int j = 0; j < column; j++){
			if(maze[i][j] == 0 or maze[i][j] == 5){		//!< SPACE and INVISIBLE WALL.
				std::cout << " ";
			}else if(maze[i][j] == 1){					//!< WALL.
				std::cout << "\u16E5";
			}else if(maze[i][j] == 3){					//!< FOOD.
				std::cout << "\u2605";
			}else if(maze[i][j] == 4){					//!< PATH.
				if(drct==Direction::NORTH)
					std::cout << "\u143A"; 				//!< V
				else if(drct==Direction::SOUTH)
					std::cout <<"\u143D";				//!< ^
				else if(drct==Direction::EAST)
					std::cout << "\u1439";				//!< <
				else if(drct==Direction::WEST)
					std::cout << "\u1434";				//!< >
			}else if(maze[i][j] == 6){
				std::cout << "\u1005";
			}
		}
		std::cout << "\n";
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(75));

}

bool SnakeGame::game_over(){
	return (lives == 0) or (food == 0);			//!< The game is finished when the snake eats 5 food.
}

void SnakeGame::print_result(){

	if(lives == 0){
		std::cout << "GAME OVER\n";
	}
	if(food == 0){
		std::cout << "YOU WON\n";
	}
	
}

void SnakeGame::prepare_path(){

	for(int i = 1; i <= row; i++){
		for(int j = 0; j < column; j++){
			/// Keeps the Food's Position.
			if(i == food_row and j == food_column){
				maze[i][j] = 3;
			}
			/// Clear the paths.
			if(maze[i][j] == 4 or maze[i][j] == -1){
				maze[i][j] = 0;
			}
		}
	}

}

void SnakeGame::clear(){

	for(int i = 1; i <= row; i++){
		for(int j = 0; j < column; j++){
			/// Cleans the path.
			if(maze[i][j] == 4 or maze[i][j] == -1 or (i == food_row and j == food_column)){
				maze[i][j] = 0;
			}
		}
	}

}

void SnakeGame::clear_body(){

	for(int i = 1; i <= row; i++){
		for(int j = 0; j < column; j++){
			/// Keeps the Start Point.
			if(maze[i][j] == 6){
				maze[i][j] = 0;
			}
		}
	}

}