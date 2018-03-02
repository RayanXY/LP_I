#include <iostream>
#include <cstring>

using byte = unsigned char;

void print(int * first, int * last){
	
	while(first != last){
		std::cout << "|" << *first;
		first++;
	}
	std::cout << "|\n";

}

bool pred(const void *a){
	/// Condição
	return true;	
}

using UnaryPredicate = bool (*)(const void *);
void * Find_If(const void *first, const void *last, UnaryPredicate p, size_t size){

	auto f = (byte *) first;
	auto l = (byte *) last;

	for( /*Empty*/; f != l; f += size){
		if(p(f)){
			return f;
		}else{
			return l;
		}
	}

}

bool cmp(const void *a, const void *b){

	auto x = (int *) a;
	auto y = (int *) b;

	if(*x < *y){
		return true;
	}else{
		return false;
	}

}

using Compare = bool (*)(const void *, const void *);
void * Min(const void *first, const void *last, Compare cpm, size_t size){

	auto f = (byte *) first;
	auto l = (byte *) last;
	auto minor = f;

	for(/*Empty*/; f != l; f += size){
		if(cpm(f, minor)){
			minor = f;
		}
	}

	return minor;

}

void * Copy(const void *first, const void *last, void *d_first, size_t size){

	auto f = (byte *) first;
	auto l = (byte *) last;
	auto d = (byte *) d_first;

	for(/*Empty*/; f != l; f += size){
		std::memcpy(d, f, size);
		d += size;
	}

}

bool media(const void * first, const void * last, const void *key, size_t size){

	auto f = (byte *) first;
	auto l = (byte *) last;
	auto k = (byte *) key;

	auto media = (byte *) first;

	while(f != l){
		*media = media + f;
		f+=size;
	}
	media = media/10;

	if(*k > media){
		return true;
	}

	return false;

}

using r_Condition = bool(*)(const void *);
void * Remove_If(const void *first, const void *last, r_Condition r, size_t size){

	auto f = (byte *) first;
	auto l = (byte *) last;

	auto fast = f;
	auto slow = f;

	for(/**/; fast != l; fast += size){
		if(r(f, l, fast, sizeof(int))){
			std::memmove(slow, fast, size);
			slow += size;
		}
	}
	return slow;
}

int main(){

	int A[10] = {15, 27, 33, 44, 55, 96, 197, 80, 100, 410};
	int B[10], i;
	/// Copy
	std::cout << ">>>Copy: \n";
	Copy(std::begin(A), std::end(A), std::begin(B), sizeof(int));
	std::cout << "B: ";
	print(std::begin(B), std::end(B));
	std::cout << "\n";
	/// Remove_If
	std::cout << ">>> Remove_If: \n";
	auto remove = (int*) Remove_If(std::begin(B), std::end(B), media, sizeof(int));
	std::cout << "R: ";
	print(std::begin(B), remove);
	std::cout << "\n";

}