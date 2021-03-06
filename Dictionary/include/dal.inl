/// DAL
/// Constructor
template <typename Key, typename Data, typename KeyComparator>
DAL<Key, Data, KeyComparator>::DAL(int _MaxSz)
	: mi_Lenght(0)
	, mi_Capacity(_MaxSz)
	, mpt_Data(mpt_Data = new NodeAL[_MaxSz])
{ /* Empty */ }

/// Linear Search
template <typename Key, typename Data, typename KeyComparator>
int DAL<Key, Data, KeyComparator>::_search(const Key & _z) const{

	KeyComparator cmp;
	int aux;
	/// Searches
	for(int i = 0; i < mi_Lenght; i++){
		aux = mpt_Data[i].id;
		if(aux == _z){
			return i;
		}
	}
	return -1;

}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::remove(const Key & _x, Data & _s){

	/// List is empty
	if(mi_Lenght == 0){
		return false;
	}
	/// Finds the position
	auto p_ = _search(_x);
	/// If it is in the last position.
	if(p_ == (mi_Lenght-1)){
		_s = mpt_Data[p_].info;
		mi_Lenght--;
		return true;
	}else if(p_ != -1){		//!< Position exists and it's not the last.
		_s = mpt_Data[p_].info;
		std::copy(&mpt_Data[p_+1], &mpt_Data[mi_Lenght+1], &mpt_Data[p_]);
		mi_Lenght--;
		return true;
	}
	return false;

}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::search(const Key & _x, Data & _s) const{

	/// Gets the position.
	int p_ = _search(_x);
	/// Verifies if the position exists.
	if(p_ != -1){
		_s = mpt_Data[p_].info;
		return true;
	}else{
		return false;
	}

}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::insert(const Key & _newKey, const Data & _newInfo){

	/// Verifies if it has space.
	if(mi_Lenght == mi_Capacity){
		return false;
	}
	
	mpt_Data[mi_Lenght].id = _newKey;
	mpt_Data[mi_Lenght].info = _newInfo;
	mi_Lenght++;

	return true;

}

template <typename Key, typename Data, typename KeyComparator>
Key DAL<Key, Data, KeyComparator>::min() const{

	///If it's empty.
	if(mi_Lenght == 0){
		throw std::out_of_range("It's empty");
	}
	KeyComparator cmp;
	int smaller = mpt_Data[0].id;
	int a_;
	/// Searches the minor.
	for(int i = 1; i < mi_Lenght; i++){
		a_ = mpt_Data[i].id;
		if(cmp(a_, smaller)){
			smaller = a_;
		}
	}
	return smaller;

}

template <typename Key, typename Data, typename KeyComparator>
Key DAL<Key, Data, KeyComparator>::max() const{

	///If it's empty.
	if(mi_Lenght == 0){
		throw std::out_of_range("It's empty");
	}
	KeyComparator cmp;
	int larger = mpt_Data[0].id;
	int a_;
	/// Searches the minor.
	for(int i = 1; i < mi_Lenght; i++){
		a_ = mpt_Data[i].id;
		if(cmp(larger, a_)){
			larger = a_;
		}
	}
	return larger;

}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::sucessor(const Key & _x, Key & _y) const{

	/// List is empty
	if(mi_Lenght == 0){
		return false;
	}
	/// The position doesn't exist.
	if(_search(_x) == -1){
		return false;
	}
	KeyComparator cmp;
	int suc = max();
	int a_;
	/// Searches
	for(int i = 0; i < mi_Lenght; i++){
		a_ = mpt_Data[i].id;
		if(cmp(_x, a_) and cmp(a_, suc)){
			suc = a_;
		}
	}
	_y = suc;
	return true;

}

template <typename Key, typename Data, typename KeyComparator>
bool DAL<Key, Data, KeyComparator>::predecessor(const Key & _x, Key & _y) const{

	/// List is empty
	if(mi_Lenght == 0){
		return false;
	}
	/// The position doesn't exist.
	if(_search(_x) == -1){
		return false;
	}
	KeyComparator cmp;
	int pre = min();
	int a_;
	/// Searches
	for(int i = 0; i < mi_Lenght; i++){
		a_ = mpt_Data[i].id;
		if(cmp(_x, a_) and cmp(a_, pre)){
			pre = a_;
		}
	}
	_y = pre;
	return true;

}

/// DSAL
/// Binary Search
template <typename Key, typename Data, typename KeyComparator>
int DSAL<Key, Data, KeyComparator>::_search(const Key & _x) const{

	KeyComparator cmp;

	auto Sz = DAL<Key, Data, KeyComparator>::mi_Lenght;
	auto right = Sz - 1;
	auto left = 0;

	while(left <= right){

		int middle = (left + right)/2;
		auto current = DAL<Key, Data, KeyComparator>::mpt_Data[middle].id;

		if(_x == current){
			return middle;
		}else if(cmp(_x, current)){
			right = middle - 1;
		}else{
			left = middle + 1;
		}

	}

	return -1;

}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::remove(const Key & _x, Data & _s){

	auto &m_Lenght = DAL<Key, Data, KeyComparator>::mi_Lenght;
	auto &m_Data = DAL<Key, Data, KeyComparator>::mpt_Data;

	/// List is empty
	if(m_Lenght == 0){
		return false;
	}
	/// Finds the position
	auto p_ = _search(_x);
	/// If it is in the last position.
	if(p_ == (m_Lenght-1)){
		_s = m_Data[p_].info;
		m_Lenght--;
		return true;
	}else if(p_ != -1){		//!< Position exists and it's not the last.
		_s = m_Data[p_].info;
		for(auto i(p_); i < m_Lenght-1; i++){
			m_Data[i].id = m_Data[i+1].id;
			m_Data[i].info = m_Data[i+1].info;
		}
		m_Lenght--;
		return true;
	}
	return false;

}

/// OBS: Esse metódo foi feito com ajuda do aluno GABRIEL SOUZA
template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::insert(const Key & _novaID, const Data & _novaInfo){

	auto & m_Lenght = DAL<Key, Data, KeyComparator>::mi_Lenght;
	auto & m_Data = DAL<Key, Data, KeyComparator>::mpt_Data;
	auto m_Capacity = DAL<Key, Data, KeyComparator>::mi_Capacity;
	/// Gets the Key to be add.
	auto newK = _search(_novaID);
	///If it's empty or it's full.
	if(m_Lenght == m_Capacity){
		throw std::out_of_range("It's full");
	}

	KeyComparator cmp;
	Key a_;
	auto test_p = 0;
	auto p_ = -1;
	/// Searches the right position
	while(test_p < m_Lenght){
		a_ = m_Data[test_p].id;
		if(cmp(a_, _novaID)){
			p_ = test_p;
		}
		test_p++;
	}
	/// Insertion is in the end of the list.
	if(p_ == m_Lenght-1){
		m_Data[m_Lenght].id = _novaID;
		m_Data[m_Lenght].info = _novaInfo;
		m_Lenght++;

		return true;
	}else if(p_ == -1){ 		//!< Insertion is in the beginning of the list.
		for(auto i(m_Lenght); i > p_+1; i--){
			m_Data[i].id = m_Data[i-1].id;
			m_Data[i].info = m_Data[i-1].info;
		}
		m_Data[0].id = _novaID;
		m_Data[0].info = _novaInfo;
		m_Lenght++;

		return true;
	}else{
		for(auto i(m_Lenght); i > p_+1; i--){
			m_Data[i].id = m_Data[i-1].id;
			m_Data[i].info = m_Data[i-1].info;
		}
		m_Data[p_+1].id = _novaID;
		m_Data[p_+1].info = _novaInfo;
		m_Lenght++;

		return true;
	}

	return false;

}

template <typename Key, typename Data, typename KeyComparator>
Key DSAL<Key, Data, KeyComparator>::min() const{

	auto & m_Lenght = DAL<Key, Data, KeyComparator>::mi_Lenght;
	auto & m_Data = DAL<Key, Data, KeyComparator>::mpt_Data;
	///If it's empty.
	if(m_Lenght == 0){
		throw std::out_of_range("It's empty");
	}
	/// As the list is sorted, the smallest key is in the first position.
	return m_Data[0].id;

}

template <typename Key, typename Data, typename KeyComparator>
Key DSAL<Key, Data, KeyComparator>::max() const{

	auto & m_Lenght = DAL<Key, Data, KeyComparator>::mi_Lenght;
	auto & m_Data = DAL<Key, Data, KeyComparator>::mpt_Data;
	///If it's empty.
	if(m_Lenght == 0){
		throw std::out_of_range("It's empty");
	}
	/// As the list is sorted, the largest key is in the last position.
	return m_Data[m_Lenght-1].id;

}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::sucessor(const Key & _x, Key & _y) const{

	auto & m_Lenght = DAL<Key, Data, KeyComparator>::mi_Lenght;
	auto & m_Data = DAL<Key, Data, KeyComparator>::mpt_Data;
	/// Gets the position.
	int p_ = _search(_x);
	/// The position doesn't exist.
	if(p_ == -1){
		return false;
	}
	/// It's empty or is the last element, so it doesn't have a sucessor.
	if(m_Lenght == 0 or p_ == m_Lenght - 1){
		return false;
	}
	/// Since the list is sorted so the sucessor is on the next position.
	_y = m_Data[p_+1].id;
	return true;

}

template <typename Key, typename Data, typename KeyComparator>
bool DSAL<Key, Data, KeyComparator>::predecessor(const Key & _x, Key & _y) const{

	auto & m_Lenght = DAL<Key, Data, KeyComparator>::mi_Lenght;
	auto & m_Data = DAL<Key, Data, KeyComparator>::mpt_Data;
	/// Gets the position.
	int p_ = _search(_x);
	/// The position doesn't exist or is the first element, so it doesn't have a predecessor.
	if(p_ == -1 or p_ == 0){
		return false;
	}
	/// It's empty.
	if(m_Lenght == 0){
		return false;
	}
	/// Since the list is sorted so the predecessor is on the previous position.
	_y = m_Data[p_-1].id;
	return true;

}
