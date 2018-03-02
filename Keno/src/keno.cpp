/**
 * @file keno.h
 * @author Anderson Caio & Rayan Avelino
 * @date /27/04/2017
 * @version README.md<v1.5>
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../include/keno.h"

int main(int argc, char * argv[]){


	/// Variables
	number_type i, j, round, number_rounds, sz, hits, payout;
	cash_type initial_credits, wage_per_round, round_wage, new_wage;
	set_of_numbers_type spots, round_draw, round_hits;
	std::string n;

	/// Class object
	KenoBet player;
	
	/// Opening the file
	std::ifstream file;
	file.open(argv[1]);
	
	/// Reading the bet file
	std::cout << std::endl;
	std::cout << ">>> Preparing to read bet file [" << argv[1] << "], please wait...\n";
	std::cout << "----------------------------------------------------------------\n";

	if(file){	

		i = 0;
		while(file >> n){
			if(i == 0){
				player.set_wage(std::stod(n));
				i++;
			}else if(i == 1){
				if(std::stoi(n) > 0){									 //!< Number of rounds must be greater than 0;	
					number_rounds = std::stoi(n);
					i++;
				}else{
					std::cout << ">>> Invalid number of rounds.\n";
					std::cout << std::endl;
					return EXIT_SUCCESS;
				}
			}else{
				player.add_number(std::stoi(n));
			}
		}

		/// Setting the variables
		spots = player.get_spots();                						 //!< Spots of the bet
		initial_credits = player.get_wage();	   						 //!< Inicial Wage
		if(player.size() <= 0){
			std::cout << ">>> Invalid or not passed any number(s).\n";	 //!< The bet must contain between 1 and 15 spotss
			std::cout << std::endl;
			return EXIT_SUCCESS;
		}else if(player.size() > 15){										
			sz = 15;
		}else{
			sz = player.size();
		}
		wage_per_round = initial_credits/number_rounds;					 //!< Valor per round

		/// Starting the game
		std::cout << ">>> Bet successfully read!\n";
		std::cout << "    You are going to wage a total of $" << initial_credits << " dollar(s).\n";
		std::cout << "    Going for a total of " << number_rounds << " rounds, waging $" << wage_per_round << " per round.\n";
		std::cout << std::endl;

		/// Printing the bet's spot(s)
		std::cout << "    Your bet has " << sz << " number(s). They are\\It is: [ "; 
		print_(spots, sz);
		std::cout << "]\n";

		/// Printing the payout for the bet
		print_payout(sz);

		/// Starting the rounds
		new_wage = initial_credits;
		for(round = 1; round <= number_rounds; round++){

			std::cout << "    ------------------------------------------------------------\n";
			std::cout << "    This is round #" << round << " of " << number_rounds << ", and your wage is $" << wage_per_round << ". Good luck!\n";
			
			/// Randon draw
			round_draw = draw();

			/// Printing the draw
			std::cout << "    The hits are: [ ";
			print_(round_draw, round_draw.size());
			std::cout << "]\n";
			std::cout << std::endl;

			/// Getting the hits
			round_hits = player.get_hits(round_draw);

			/// Printing the hits
			std::cout << "    You hit the following number(s) [ "; 
			print_(round_hits,round_hits.size());

			/// Number of hits
			hits = round_hits.size(); 								 			
			std::cout << "], a total of " << hits << " hit(s) out of " << sz << ".\n";

			/// Getting and printing the results of the round
			payout = get_payout(sz, hits);
			round_wage = wage_per_round * payout;
			new_wage = (new_wage - wage_per_round) + round_wage;
			std::cout << "    Payout rate is " << payout << ", thus you came out with: $" << round_wage << ".\n";
			std::cout << "    Your net balance so far is: $" << new_wage << " dollar(s).\n";

		}

		std::cout << ">>> End of rounds!\n";
		std::cout << "----------------------------------------------------------------\n";
		std::cout << std::endl;

		/// Setting the new wage for the player
		player.set_wage(new_wage);

		/// Printing the results of the game
		std::cout << "===== SUMMARY =====\n";
		std::cout << ">>> You spent in this game a total of $" << initial_credits << " dollar(s).\n";
		std::cout << ">>> Hooray, you won $" << player.get_wage() - initial_credits << " dollar(s). See you next time!\n";
		std::cout << ">>> You are leaving the Keno table with $" << player.get_wage() << " dollar(s).\n";
		std::cout << std::endl;

		/// Reseting the player and closing the bet file
		player.reset();
		file.close();

		return EXIT_SUCCESS;

	}else{

		std::cout << ">>> Couldn't open the bet file\n";
		std::cout << std::endl;
		
		file.close();

		return EXIT_SUCCESS;

	}

}