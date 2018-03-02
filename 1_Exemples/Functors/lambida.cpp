#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

struct Multiplier{

	private:
		int factor;

	public:
		Multiplier(int f) 
			: factor(f)
		{ /* Empty */ }
	
		int operator()(const int & v){
			if(v % 2 == 0){
				return v * 10;		
			}else{
				return v * factor;
			}
		}

};

int main(){
	
	std::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	std::cout << ">>> Array: ";
	std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, "|"));
	std::cout << "\n";

	/// Lambda Functor
	auto func = [](){
		std::cout << "Hello World!\n";
	};

	std::transform(a.begin(), a.end(), a.begin(), 
		[factor](int v){
			return factor * v;
		}
	);

	std::cout << ">>> Transformed Array: ";
	std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, "|"));
	std::cout << "\n";

	std::cout << "\n\n>>> Normal Exeiting...\n";
	return 0;

}