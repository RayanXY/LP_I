bool isPrime(int n){

	int i, qntDiv = 0;
	if(n == 0 || n == 1){
		return false;
	}
    for(i = 2; i <= std::sqrt(n); i++){
        if (n%i == 0) {
            return false;
        }
    }
  	return true;

}

int nextPrime(int n){

	while(not isPrime(n)){
		n++;
	}
	return n;
}

/// This method was done in collaboration with my colleague Anderson Caio
/// Inserts new elements in the table.
template<typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::insert(const KeyType & k_, const DataType & d_){
	/// If the table is full, resize with Rehash.
	if(m_count == m_size){
		rehash();
	}
	/// Functors.
	KeyHash func_hash;
	KeyEqual func_equal;
	/// Creates a new entry for the table.
	Entry new_entry(k_, d_);
	/// Calculate the address.
	auto address = func_hash(k_)%m_size;
	/// Tries to insert the new entry.
	if(m_data_table[address].empty()){
		m_data_table[address].push_front(new_entry);
		m_count++;
		return true;
	}else{
		/// Defining the begin, the end of the table and the element to be removed.
		auto b(m_data_table[address].begin());
		auto e(m_data_table[address].end());

			for(/* Empty */; b != e; b++){
			if(func_equal((*b).m_key, new_entry.m_key)){

				(*b).m_data = d_;
				return false;
			}
		}

		m_data_table[address].push_front(new_entry);
		m_count++;
		return true;
	}

}
/// Removes an elements from the table.
template<typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::remove(const KeyType & k_){
	/// Functors.
	KeyHash func_hash;
	KeyEqual func_equal;
	/// Calculate the address.
	auto address = func_hash(k_)%m_size;
	/// Defining the begin, the end of the table and the element to be removed.
	auto t = m_data_table[address].before_begin(); 
	auto b = m_data_table[address].begin();
	auto e = m_data_table[address].end();
	/// Checks if it is empty.
	if(m_data_table[address].empty()){
		return false;
	}
	/// Delesting the data.
	for(/* Empty */; b != e; b++){
		if(func_equal((*b).m_key, k_)){

			m_data_table[address].erase_after(t);
			t++;
			m_count--;
			return true;
		}	
	}
	return false;

}
/// Retrives data from the table.
template<typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::retrieve(const KeyType & k_, DataType & d_) const{
	/// Functors.
	KeyHash func_hash;
	KeyEqual func_equal;
	/// Calculate the address.
	auto address = func_hash(k_)%m_size;
	/// Checks if it is empty.
	if(m_data_table[address].empty()){
		return false;
	}
	/// Defining the begin and the end of the table.
	auto b(m_data_table[address].begin());
	auto e(m_data_table[address].end());
	/// Retriving the data.
	for(/* Empty */; b != e; b++){
		if(func_equal((*b).m_key, k_)){
			d_ = (*b).m_data;
			return true;
		}
	}
	return false;

}
/// Checks if the table is empty.
template<typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
bool HashTbl<KeyType, DataType, KeyHash, KeyEqual>::empty(void) const{

	for(auto i(0); i < m_size; i++){
		if(not m_data_table[i].empty()){
			return false;
		}
	}
	return true;

}
/// Cleans all the data storaged in the table.
template<typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::clear(void){

	for(auto i(0); i < m_size; i++){
		m_data_table[i].clear();
	}

}
/// Prints all data from the table.
template<typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::print() const{

	/// Header
	std::cout << "===================== Accounts =====================\n";
	std::cout << "| Key |  Name  | Bank | Agency | Account | Balance |\n";
	std::cout << "----------------------------------------------------\n";

	for(auto i(0); i < m_size; i++){
		/// Defining the begin and the end of the table. 
		auto b = m_data_table[i].begin();
		auto e = m_data_table[i].end();
		///Printing the current data
		for(/* Empty */; b != e; b++){
			auto data = (*b).m_data;
			std::cout << "|  " << i;
			std::cout << "  | " << data.client_name;
			std::cout << " |  " << data.bank;
			std::cout << "   |  " << data.agency;
			std::cout << "  |  " << data.n_account;
			std::cout << "  | " << data.balance << " |\n";
		}

	}

}
/// Returns the number of elements in the table.
template<typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
unsigned long int HashTbl<KeyType, DataType, KeyHash, KeyEqual>::count(void) const{
	return m_count;
}
/// Returns the actual size from the table.
template<typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
size_t HashTbl<KeyType, DataType, KeyHash, KeyEqual>::size(){
	return m_size;
}
/// Doubles the table's size.
template<typename KeyType, typename DataType, typename KeyHash, typename KeyEqual>
void HashTbl<KeyType, DataType, KeyHash, KeyEqual>::rehash(){

	KeyHash func_hash;
	/// Defines the new size and a new table.
	auto newsize = nextPrime(m_size*2);
	auto newtable = new std::forward_list<Entry>[newsize];
	/// Copies the elements to the new table.
	for(auto i(0); i != m_size; i++){
		/// Defining the begin and the end of the table. 
		auto b = m_data_table[i].begin();
		auto e = m_data_table[i].end();
		/// Doubles the size
		for(/* Empty */; b != e; b++){
			auto address = func_hash((*b).m_key) % newsize;
			newtable[address].push_front(*b);
		}
	}

	delete [] m_data_table;
	/// Redifines the data and the size.
	m_data_table = newtable;
	m_size = newsize;

}