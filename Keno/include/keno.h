/**
 * @file keno.h
 * @author Anderson Caio & Rayan Avelino
 * @date /27/04/2017
 * @version README.md<v1.5>
 */

#include <iostream>     //!< cin, cout
#include <algorithm>	//!< find()
#include <vector>		//!< begin(), end(), size()
#include <chrono>		//!< system_clock.now()
#include <random>		//!< default_random_engine

using number_type = unsigned short int;
using cash_type = float;
using set_of_numbers_type = std::vector<number_type>;
using matrix = std::vector <std::vector<float> >;      			//<! Payout matrix

/**
 * @class KenoBet
 *
 * This class contains a set of function for controlling
 * the money and the numbers choosen in the bet by the 
 * player. We need only one KenoBet player in our program.
 *
 */

class KenoBet{
	
	private:
		set_of_numbers_type m_spots;  							//<! The player's bet.
		cash_type m_wage;			  							//<! The player's wage.
	
	public:
	
		/// Creates an empty Keno bet.
		KenoBet(): m_wage(0){
			/*Empty*/
		};

		/**
		 * Adds a number to the spots only if the number is not already there. 
		 * @param spot The number we wish to include in the bet.
		 * @return T if number chose is successfully inserted; F otherwise
		 */
		bool add_number(number_type spot){
			if(spot >= 1 && spot <= 80){
				if(std::find(m_spots.begin(), m_spots.end(), spot) != m_spots.end()){
					return false;
				}else{
					m_spots.push_back(spot);
					return true;					
				}
			}
		}
		
		/**
		 * Sets the amount of money the player is betting.
		 * @param wage The wage.
		 * @return T if we have a wage above zero; false otherwise.
		 */
		bool set_wage(cash_type wage){
			if(wage > 0.0){
				m_wage = wage;
				return true;
			}else{
				return false;
			}
		}

		/**
		 * Resets a bet to an empty state.
		 */
		void reset(void){
			m_spots.clear();
			m_wage = 0;
		}

		/**
		 * Retrieves the player's wage on this bet.
		 * @return The wage value.
		 */
		cash_type get_wage(void) const{
			return m_wage;
		}

		/**
		 * Returns ot the current number of spots in the player's bet.
		 * @return Number of spots present in the bet.
		 */
		size_t size(void) const{
			int sz = m_spots.size();
			return sz;
		}

		/**
		 * Determine how many spots match the hits passed an argument.
		 * @param hits List of hits randomly chosen by the computer.
		 * @return Number of spots present in the bet.
		 */
		set_of_numbers_type get_hits(const set_of_numbers_type & hits) const{
			int i;
			set_of_numbers_type matched;
			//std::find(m_spots.begin(), m_spots.end(), spot) != m_spots.end();
			for(i = 0; i < m_spots.size(); i++){
				if(std::find(hits.begin(), hits.end(), m_spots[i]) != hits.end()){
					matched.push_back(m_spots[i]);
				}
			}
			return matched;
		}

		/**
		 * Return a vector<spot_type> with the spots the player has picked so far.
		 * @return The vector<spot_type> with the player's spots picked so far.
		 */
		set_of_numbers_type get_spots(void) const{
			return m_spots;
		}

};

/// Creates the payout table
matrix creating_payout(void){

	//Creating and initializing the vector
	matrix payout(15, std::vector<float>(16, 0));

	payout[0][1] = 3;
	payout[1][1] = 1;
	payout[1][2] = 9;
	payout[2][1] = 1;
	payout[2][2] = 2;
	payout[2][3] = 16;
	payout[3][1] = 0.5;
	payout[3][2] = 2;
	payout[3][3] = 6;
	payout[3][4] = 12;
	payout[4][1] = 0.5;
	payout[4][2] = 1;
	payout[4][3] = 3;
	payout[4][4] = 15;
	payout[4][5] = 50;
	payout[5][1] = 0.5;
	payout[5][2] = 1;
	payout[5][3] = 2;
	payout[5][4] = 3;
	payout[5][5] = 30;
	payout[5][6] = 75;
	payout[6][1] = 0.5;
	payout[6][2] = 0.5;
	payout[6][3] = 1;
	payout[6][4] = 6;
	payout[6][5] = 12;
	payout[6][6] = 36;
	payout[6][7] = 100;
	payout[7][1] = 0.5;
	payout[7][2] = 0.5;
	payout[7][3] = 1;
	payout[7][4] = 3;
	payout[7][5] = 6;
	payout[7][6] = 19;
	payout[7][7] = 90;
	payout[7][8] = 720;
	payout[8][1] = 0.5;
	payout[8][2] = 0.5;
	payout[8][3] = 1;
	payout[8][4] = 2;
	payout[8][5] = 4;
	payout[8][6] = 8;
	payout[8][7] = 20;
	payout[8][8] = 80;
	payout[8][9] = 1200;
	payout[9][2] = 0.5;
	payout[9][3] = 1;
	payout[9][4] = 2;
	payout[9][5] = 3;
	payout[9][6] = 5;
	payout[9][7] = 10;
	payout[9][8] = 30;
	payout[9][9] = 600;
	payout[9][10] = 1800;
	payout[10][2] = 0.5;
	payout[10][3] = 1;
	payout[10][4] = 1;
	payout[10][5] = 2;
	payout[10][6] = 6;
	payout[10][7] = 15;
	payout[10][8] = 25;
	payout[10][9] = 180;
	payout[10][10] = 1000;
	payout[10][11] = 3000;
    payout[11][3] = 0.5;
    payout[11][4] = 1;
    payout[11][5] = 2;
    payout[11][6] = 4;
    payout[11][7] = 24;
    payout[11][8] = 72;
    payout[11][9] = 250;
    payout[11][10] = 500;
    payout[11][11] = 2000;
    payout[11][12] = 4000;
    payout[12][3] = 0.5;
    payout[12][4] = 0.5;
    payout[12][5] = 3;
    payout[12][6] = 4;
    payout[12][7] = 5;
    payout[12][8] = 20;
    payout[12][9] = 80;
    payout[12][10] = 240;
    payout[12][11] = 500;
    payout[12][12] = 3000;
    payout[12][13] = 6000;
    payout[13][3] = 0.5;
    payout[13][4] = 0.5;
    payout[13][5] = 2;
    payout[13][6] = 3;
    payout[13][7] = 5;
    payout[13][8] = 12;
    payout[13][9] = 50;
    payout[13][10] = 150;
    payout[13][11] = 500;
    payout[13][12] = 1000;
    payout[13][13] = 2000;
    payout[13][14] = 7500;
    payout[14][3] = 0.5;
    payout[14][4] = 0.5;
    payout[14][5] = 1;
    payout[14][6] = 2;
    payout[14][7] = 5;
    payout[14][8] = 15;
    payout[14][9] = 50;
    payout[14][10] = 150;
    payout[14][11] = 300;
    payout[14][12] = 600;
    payout[14][13] = 1200;
    payout[14][14] = 2500;
    payout[14][15] = 10000;

    return payout;
	
}

/**
 * Printing the payout table based on the number of spots present in the bet
 * @param spots Number of spots present in the bet
 */
void print_payout(number_type spots){

	int i;
	matrix p = creating_payout();

	std::cout << "        --------+--------\n          Hits  | Payout  \n        --------+--------\n";
	for(i = 0; i <= spots; i++){
		if(i < 10){
			std::cout << "            " << i << "   |   " << p[spots-1][i] << " \n";
		}else{
			std::cout << "           " << i << "   |   " << p[spots-1][i] << " \n";
		}
	}

}

/**
 * Return the payout value based on the player's hits
 * @param sz Number of spots picked by the player
 * @param totalHits Number of player's hits
 * @return The payout value
 */
int get_payout(int sz, int totalHits){

	matrix p = creating_payout();

	return p[sz-1][totalHits];

}

/**
 * Create a <vector> between 1 and 80, shuffle it and then returns the 20 first numbers
 * @return The <vector> with 20 numbers
 */
set_of_numbers_type draw(){
	
	std::vector<number_type> A;

	for(auto i(0); i<80; i++){
		A.push_back(i+1);
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(A.begin(), A.end(),std::default_random_engine(seed));
	A.resize(20);

	return A;

}

/**
 * Print an <vector>
 * @param A <vector> that to be printed
 * @param sz Size of the <vector> to be printed
 */
void print_(set_of_numbers_type A, number_type sz_){

	int i;

	for(i = 0; i < sz_; i++){
		std::cout << A[i] << " ";
	}

}