#include <iostream>
#include <ostream>
#include <iterator>
#include <algorithm>
#include <initializer_list>
#include <cassert>

class vector;

template <typename T>
class MyIterator{

	private:
		T *current;

	public:
		MyIterator(T * ptr_ = nullptr)
			: current(ptr_)
		{/* Empty */}

		const T & operator*() const{
			assert(current 	!= nullptr);
			return *current;
		}

		MyIterator & operator++(){
			current++;
			return *this;
		}

		MyIterator operator++(int){
			MyIterator temp = *this;
			current++;
			return temp;
		}

		MyIterator & operator--(){
			current--;
			return *this;
		}

		MyIterator operator--(int){
			MyIterator temp = *this;
			current--;
			return temp;
		}

		bool operator==(const MyIterator & rhs) const{
			return current == rhs.current;
		}

		bool operator!=(const MyIterator & rhs) const{
			return current != rhs.current;
		}

};

namespace ls{

	template<typename T>
	class vector{

		public:
			using size_type = size_t;
			using value_type = T;
			const static size_type DEFAULT_SIZE = 1;
			using iterator = MyIterator<T>;
			using const_iterator = MyIterator<const T>;
			using reference = T &;
			using const_reference = const T &;
			using pointer = T *;

		private:
			size_type m_end;			//Quantidade de elementos
			size_type m_capacity;		//Capacidade de armazenamento
			T * m_storage;				//Armazenamento

		public:

			/// [I] SEPECIAL MEMBERS
			vector()
				: m_end(0)
				, m_capacity(DEFAULT_SIZE)
				, m_storage(new T[m_capacity])
			{ /* Empty */ }
			~vector(){
				delete [] m_storage;
			}
			vector(const vector & other)
				: m_end(other.m_end)
				, m_capacity(other.m_capacity)
				, m_storage(new T[m_capacity])
			{
				for(auto i(0u); i != m_end; i++){
					m_storage[i] = other.m_storage[i];
				}
			}
			vector(size_type n)
				:m_end(0)
				,m_capacity(n)
				,m_storage (new T[m_capacity])
			{/*empty*/}	
			/// Values
			template<typename InputItr>
			vector(InputItr f_, InputItr l_){

				auto distance = l_- f_;
				m_end = size_t(distance);
				m_capacity = size_t(distance);
				m_storage = new T[m_capacity];
 
				for(auto i=0; i!=distance; i++){
					m_storage[i] = i+f_;
				}

			}
			/// Iterators
			vector(iterator f_, iterator l_)
			{

				auto x = f_;
				int count = 0;
				while(x!=l_){
					x++;
					count++;
				}
				m_end = size_type(count);
				m_capacity = size_type(count);
				m_storage = new T[m_capacity];
 				auto y_ = f_;
				for(auto i=0; i!=count; i++){
					m_storage[i] = *y_;
					y_++;
				}

			}
			vector & operator=(const vector & other){

				m_end(other.m_end);
				m_capacity(other.m_capacity);
				m_storage(new T[m_capacity]);
				for(auto i(0u); i != m_end; i++){
					m_storage[i] = other.m_storage[i];
				}
				return *this;

			}

			/// [II] ITERATORS
			/// Returns a iterator to the first element of the vector
			iterator begin(void){
				return iterator(&m_storage[0]);
			}
			/// Returns a iterator to the last element of the vector
			iterator end(void){
				return iterator(&m_storage[m_end]);
			}
			/// Returns a constant iterator to the first element of the vector
			const_iterator cbegin(void) const{
				return const_iterator(&m_storage[0]);
			}
			/// Returns a constant iterator to the last element of the vector
			const_iterator cend(void) const{
				return const_iterator(&m_storage[m_end]);
			}

			/// [III] CAPACITY
			/// Return the logical size of the vector
			size_type size(void) const{
				return m_end;
			}
			/// Return the total capacity of the vector
			size_type capacity(void) const{
				return m_capacity;
			}
			/// Check if the vector is empty
			bool empty(void) const{
				return m_end == 0;
			}
			/// Check if the vector is full
			bool full(void) const{
				return m_end == m_capacity;
			}

			/// [IV] MODIFIERS
			void clear (void){

				delete [] m_storage;
				m_end = 0;
				m_capacity = 0; 
				m_storage = nullptr;

			}
			/// Adds a element to the begin of the vector
			void push_front(const_reference v_){

				if(full())
                   reserve(m_capacity*2);
                for(auto i(m_end+1); i != 0; i--){
                    m_storage[i] = m_storage[i-1];
                }
                m_end++;
                m_storage[0] = v_;

			}
			/// Adds a element to the end of the vector
			void push_back(const_reference v_){

				if(full()){
					reserve(2*m_capacity);
				}
				m_storage[m_end++] = v_;

			}
			/// Withdraw the last element in the vector
			void pop_back(void){
			
				if(empty()){
					throw std::out_of_range("Cannot recover an element from an empty vector!.\n");
				}
				m_storage[--m_end];

			}
			/// Withdraw the last element in the vector
			void pop_front(void){

				for(auto i(0); i != m_end; i++)
				{
                    m_storage[i] = m_storage[i+1];
                }
                m_end--;

			}
			/// Inserts a element, range of elements, or list to an especific point in the vector
			iterator insert(iterator pos, const_reference value){
				
				auto x = begin();
				int count=0;
				while( pos != x){
					x++;
					count++;
				}
				if(full())
					{reserve(2*m_capacity);}
				for(auto i(m_end+1); i!=count; i--)
				{
					m_storage[i] = m_storage[i-1]; 
				}
				m_storage[count] = value;
				m_end++;
				return x;

			}
			template<typename InputItr>
			iterator insert(iterator pos, InputItr f_, InputItr l_){
				
				int dist = l_ - f_;
				auto x = f_;
				auto y = begin();
				int start = 0;

				while(y != pos){
					y++;
					start++;
				}
				while(m_end + dist > m_capacity){
					reserve(2*m_capacity);
				}
				for(auto i(m_end + dist); i != start; i--){
					m_storage[i] = m_storage[i - dist]; 
				}
				for(auto i(start); i != start+dist; i++){
					m_storage[i] = x;
					x++;
				}
				m_end += dist;

				return y;
			}
			iterator insert(iterator pos, std::initializer_list<value_type> l_){
				
				auto dist = l_.size();

				auto y = begin();
				int start = 0;

				while(y != pos){
					y++;
					start++;
				}
				while(m_end + dist > m_capacity){
					reserve(2*m_capacity);
				}
				for(auto i(m_end + dist); i != start; i--){
					m_storage[i] = m_storage[i - dist]; 
				}
				for(auto &v_: l_){
					m_storage[start++] = v_;
				}
				m_end += dist;

				return y;

			}
			/// Increases de capacity of the vector
			void reserve(size_type n_){
				
				if(n_ <= m_capacity) return; //!< It's not full
				/// Creates the new Storage area
				T * temp = new T[n_];  
				/// Backup the data to the new storage area
				for(auto i(0u); i < m_capacity; i++){
					temp[i] = m_storage[i];
				}
				/// Delete the old storage area
				delete [] m_storage;
				/// Reassings the storage area
				m_storage = temp;
				/// Updates the vector's storage capacity
				m_capacity = n_;

			}
			/// Makes the capacity of the vector equal to its logical lenght
			void shrink_to_fit(void){

				T * temp = new T[m_end];  
				for(auto i(0); i < m_end; i++){
					temp[i] = m_storage[i];
				}
				delete [] m_storage;
				m_storage = temp;
				m_capacity = m_end;

			}
			/// Fill the vector with a especific element, range of elements or list
			void assign(const_reference v_){

				if(empty()){
					throw std::out_of_range("Cannot replace an element from an empty vector!.\n");
				}
				for(auto i(0u); i != m_end; i++){
					m_storage[i] = v_;
				}

			}
			void assign(std::initializer_list<T> l_){
				
				size_type i = 0;
				auto j(0u);
				if(empty()){
					throw std::out_of_range("Cannot replace an element from an empty vector!.\n");
				}
				while(j < m_end){
					for(auto &v_: l_){
						m_storage[i++] = v_;
						j++;
					}
				}

			}
			template<typename InputItr>
			void assign(InputItr f_, InputItr l_){
				
				auto distance = l_- f_;
				m_end = size_t(distance);
				m_capacity = size_t(distance);
				m_storage = new T[m_capacity];

				for(auto i=0; i!=distance; i++){
					m_storage[i] = i+f_;
				}

			}
			/// Erases a element in a especific place in the vector
			iterator erase(iterator f_, iterator l_){

				auto x = f_;
				auto y = begin();
				int start = 0;
				int count = 0;

				while(x != l_){
					x++;
					count++;
				}
				while(y != f_){
					start++;
				}

				for(auto i(start); i != m_end-count; i++){
					m_storage[i] = m_storage[i+count];
				}
				m_end -= count;
				return x;

			}

			iterator erase(iterator p_){

				auto x = begin();
				int count=0;
				while( p_ != x){
					x++;
					count++;
				}
				for(auto i(count); i != m_end-1;++i){
					m_storage[i] = m_storage[i+1];
				}
				m_end--;
				return iterator(x);

			}

			/// [V] ELEMENT ACCESS
			/// Returns the last element in the vector
			const_reference back(void) const{
				return m_storage[m_end-1];
			}
			/// Returns the first element in the vector
			const_reference front(void) const{
				return m_storage[0];
			}
			/// Returns the constant content of the position pos (exemple: myvector[3])
			const_reference operator[](size_type pos) const{
				return m_storage[pos];
			}
			/// Returns the content of the position pos (exemple: myvector[3])
			reference operator[](size_type pos){
				return m_storage[pos];
			}
			/// Returns the content of the position pos after check if the element exists
			const_reference at(size_type pos){

				if(pos >= m_end){
					throw std::out_of_range("Cannot replace an element from an empty vector!.\n");
				}
				return m_storage[pos];

			}
			/// Returns a pointer to the vector data
			pointer data(void){
				return m_storage;
			}
			/// Returns a constant pointer to the vector data
			const_reference data(void) const{
				return m_storage;
			}

			void print(void) const{

				if(empty()){
					std::cout << "Empty!\n";
					return;
				}
				std::cout << "|";
				std::copy(&m_storage[0], &m_storage[m_end], std::ostream_iterator<int>(std::cout, "|"));
				std::cout << std::endl;

			}

			/// [VI] OPERATORS
			/// Checks if two vectors have the same capacity logical size and contents
			bool operator==(const vector & rhs) const{

				if(this->m_capacity != rhs.m_capacity){
					return false;
				}
				if(this->m_end != rhs.m_end){
					return false;
				}
				for(auto i(0u); i!=m_end; i++){
					if(m_storage[i] != rhs.m_storage[i])
						return false;
				}
				return true;

			}
			/// Oposit logic of operator==
			bool operator!=(const vector & rhs) const{

				if(m_capacity != rhs.m_capacity){
					return true;
				}
				if(m_end != rhs.m_end){
					return true;
				}
				for(auto i(0u); i != m_end; i++){
					if(m_storage[i] != rhs.m_storage[i])
						return true;
				}
				return false;

			}

	};

}