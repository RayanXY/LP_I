#include <iostream>
#include <iterator>
#include <vector>
#include <functional>
#include <algorithm>

bool above_3(int val_){

	return val_ > 3;

}

class Above{
	private:
		int limit;
	public:
		Above(int l_ = 0) : limit(l_){
			/* Empty */
		}
		bool operator()(int val_){

			return val_ > limit;

		}

};

#define TEMPLATE

#ifdef FUNCTION_PTR
template<typename FwrdIt>
std::vector<int>
find_matching_numbers(FwrdIt first, FwrdIt last, bool (*pred_)(int))
#endif
#ifdef FUNCTIONAL
template<typename FwrdIt>
std::vector<int>
find_matching_numbers(FwrdIt first, FwrdIt last, std::function<bool(int)> pred_)
#endif 
#ifdef TEMPLATE
template<typename FwrdIt, typename UnaryPredicary>
std::vector<int>
find_matching_numbers(FwrdIt first, FwrdIt last, UnaryPredicary pred_)
#endif
{
	std::vector<int> selected;

	while(first != last){

		if(pred_(*first) == true){

			selected.push_back(*first);

		}

		first++;

	}

	return selected;

}

int main(){
	
	std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	std::cout << ">>> Original array: [";
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "]\n";

	/// Criar um subcnjunto da coleção que satifaz uma certa condição
	Above acima(5);
	auto result = find_matching_numbers(v.begin(), v.end(), acima);

	std::cout << ">>> Selected array: [";
	std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << "]\n";

	std::cout << "\n\n Normal exiting...\n";

}