#include <iostream>
#include <string>
#include <tuple>
#include "../include/hashtable.h"

using AcctKey = std::tuple<std::string, int, int, int>;

/// Account of the bank
struct Account{

	/// Elements of the account
	AcctKey key;
	std::string client_name;
	int bank;
	int agency;
	int n_account;
	float balance;

	/// Constructor
	Account(std::string c_n = "N", int bk = 0, int agc = 0000, int n_acc = 0000, float blc = 00.00)
		: key(c_n, bk, agc, n_acc)
		, client_name(c_n)
		, bank(bk)
		, agency(agc)
		, n_account(n_acc)
		, balance(blc)
	{/* Empty */}

	/// Returns the key
	AcctKey get_key(void){
		return key;
	}

};

/// Primary Hash functor
struct KeyHash{
	
	size_t operator()(const AcctKey & k_) const{

		auto c_n = std::get<0>(k_);
		auto bk = std::get<1>(k_);
		auto agc = std::get<2>(k_);
		auto n_acc = std::get<3>(k_);

		return std::hash<std::string>()(c_n) xor
			   std::hash<int>()(bk) xor
			   std::hash<int>()(agc) xor
			   std::hash<int>()(n_acc);

	}

};

/// Compare Keys functor
struct KeyEqual{
	
	bool operator()(const AcctKey & lhs, const AcctKey & rhs) const{
		return lhs == rhs;
	}

};

int main(){

	HashTbl<AcctKey, Account, KeyHash, KeyEqual> bank_table;

	/// Filling the table
	Account acc_1 = {"Gabi", 1, 3404, 29157, 3578.99};
	Account acc_2 = {"Alex", 7, 6512, 54982, 8895.89};
	Account acc_3 = {"Caio", 6, 1658, 34897, 4782.73};
	Account acc_4 = {"Igor", 5, 7985, 16589, 1025.26};
	Account acc_5 = {"Amom", 2, 4462, 76538, 7985.41};

	/// Insert
	std::cout << ">>> Inserting the data...\n";
	bank_table.insert(acc_1.get_key(), acc_1);
	bank_table.insert(acc_2.get_key(), acc_2);
	bank_table.insert(acc_3.get_key(), acc_3);
	bank_table.insert(acc_4.get_key(), acc_4);
	bank_table.insert(acc_5.get_key(), acc_5);
	/// Print
	bank_table.print();
	std::cout << std::endl;
	
	/// Remove
	std::cout << ">>> Romoving somo data...\n";
	bank_table.remove(acc_4.get_key());
	bank_table.remove(acc_2.get_key());
	bank_table.print();
	std::cout << std::endl;

	/// Retrive
	std::cout << ">>> Retriving some data...\n";
	Account d;
	bank_table.retrieve(acc_3.get_key(), d);
	std::cout << "Retrieved data: " << d.client_name << "\n";
	std::cout << std::endl;

	/// Rehash
	std::cout << ">>> Rehashing...\n";
	HashTbl<AcctKey, Account, KeyHash, KeyEqual> rehash_test(5);

	Account ac_1 = {"Kratos", 1, 3404, 29157, 3578.99};
	Account ac_2 = {"Chrono", 7, 6512, 54982, 8895.89};
	Account ac_3 = {"Wander", 6, 1658, 34897, 4782.73};
	Account ac_4 = {"Batman", 5, 7985, 16589, 1025.26};
	Account ac_5 = {"Felipe", 2, 4462, 76538, 7985.41};
	Account ac_6 = {"Carlos", 2, 4792, 61589, 3574.78};

	rehash_test.insert(ac_1.get_key(), ac_1);
	rehash_test.insert(ac_2.get_key(), ac_2);
	rehash_test.insert(ac_3.get_key(), ac_3);
	rehash_test.insert(ac_4.get_key(), ac_4);
	rehash_test.insert(ac_5.get_key(), ac_5);

	std::cout << "Size before Rehash: " << rehash_test.size() << "\n";
	rehash_test.insert(ac_6.get_key(), ac_6);
	std::cout << "Size after Rehash: " << rehash_test.size() << "\n";

	rehash_test.print();
	

}