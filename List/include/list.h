/**
 * @file list.h
 * @authors Anderson Caio & Rayan Avelino
 * @date 01/06/2017
 */
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <cassert>

namespace ls{
	
template<typename T>
	class list{

		/// Aliases
		public:
			using size_type = unsigned long;
			using value_type = T;

		private:
			/// Node structure
			struct Node{

				value_type data;
				Node *prev;
				Node *next;

				Node(const T & d = T(), Node * p = nullptr, Node * n = nullptr)
					: data(d)
					, prev(p)
					, next(n)
				{/* Empty */}

			};
			/// Members
			int m_size;
			Node *m_head;
			Node *m_tail;

		public:
			class const_iterator{
				
				protected:
					Node * current;
					const_iterator(Node * p) : current(p){
						/* Empty */
					}
					friend class list<value_type>;

				public:

					const value_type & operator*() const{
						assert(current != nullptr);
						return current->data;
					}

					const_iterator & operator++(){
						current = current->next;
						return *this;
					}

					const_iterator operator++(int){
						const_iterator temp = *this;
						current = current->next;
						return temp;
					}

					const_iterator & operator--(){
						current = current->prev;
						return *this;
					}

					const_iterator operator--(int){
						const_iterator temp = *this;
						current = current->prev;
						return temp;
					}

					bool operator==(const const_iterator & rhs) const{
						return current == rhs.current;
					}

					bool operator!=(const const_iterator & rhs) const{
						return current != rhs.current;
					}

			};

			class iterator : public const_iterator{

				protected:
					Node *current;
					iterator(Node * p)
						: const_iterator(p)
					{/*empty*/}
					friend class list<value_type>;

				public:

					const value_type & operator*() const{
						assert(const_iterator::current != nullptr);
						return const_iterator::current->data;
					}

					value_type & operator*(){
						assert(const_iterator::current != nullptr);
						return const_iterator::current->data;
					}

					iterator & operator++(){
						const_iterator::current = const_iterator::current->next;
						return *this;
					}

					iterator operator++(int){
						iterator temp = *this;
						const_iterator::current = const_iterator::current->next;
						return temp;
					}

					iterator & operator--(){
						const_iterator::current = const_iterator::current->prev;
						return *this;
					}

					iterator operator--(int){
						iterator temp = *this;
						const_iterator::current = const_iterator::current->prev;
						return temp;
					}

			};

			/// [I] SPECIAL MEMBERS
			/// Defautl constructor 
			list() 
				: m_size(0)
				, m_head(new Node())
				, m_tail(new Node())
			{
				m_head->next = m_tail;
				m_tail->prev = m_head;
			}
			explicit list(size_type count)
				: m_size(count)
				, m_head(new Node())
				, m_tail(new Node())
			{
				m_head->next = m_tail;
				m_tail->prev = m_head;
			}
			/// Range constructor
			template<typename InputIt>
			list(InputIt first, InputIt last)
				: m_size(0)
				, m_head(new Node())
				, m_tail(new Node())
			{
				m_head->next = m_tail;
				m_tail->prev = m_head;

				for(auto i(first); i != last; i++){
					push_back(*i);
				}
			}
			/// Copy constructor
			list(const list & other)
				: m_size(other.size())
				, m_head(new Node())
				, m_tail(new Node())
			{
				m_head->next = m_tail;
				m_tail->prev = m_head;

				for(auto i(other.cbegin()); i != other.cend(); i++){
					push_back(*i);
				}
			}
			/// Initializer List constructor
			list(std::initializer_list<T> ilist){

				m_size = 0;
				m_head = new Node();
				m_tail = new Node();
				m_head->next = m_tail;
				m_tail->prev = m_head;

				for(auto i = ilist.begin(); i != ilist.end(); i++){
					push_back(*i);
				}

			}
			/// Destructor
			~list(){

				clear();
				delete m_head;
				delete m_tail;

			}
			/// Equals constructor
			list & operator=(const list & rhs){

				m_size = rhs.m_size;
				m_head = rhs.m_head;
				m_tail = rhs.m_tail;
				for(auto i(rhs.begin()); i != rhs.end(); i++){
					push_back(*i);
				}

			}
			list & operator=(std::initializer_list<T> ilist){

				m_size = 0;
				m_head = new Node();
				m_tail = new Node();
				m_head->next = m_tail;
				m_tail->prev = m_head;

				for(auto i = ilist.begin(); i != ilist.end(); i++){
					push_back(*i);
				}
				return *this;

			}
			
			/// [II] ITERATORS
			/// Returns an iterator to the first element in the list.
			iterator begin(void){
				return iterator(m_head->next);
			}
			/// Returns a constant iterator to the first element in the list.
			const_iterator cbegin(void) const{
				return const_iterator(m_head->next);
			}
			/// Returns an iterator to the last element in the list.
			iterator end(void){
				return iterator(m_tail);
			}
			/// Returns a constant iterator to the last element of the list.
			const_iterator cend(void) const{
				return const_iterator(m_tail);
			}

			/// [III] CAPACITY
			/// Returns the logical size of the list.
			size_type size() const{
				return m_size;
			}
			/// Returns T if the list is empty.
			bool empty() const{
				return m_size == 0;
			}

			/// [IV] MODIFIERS
			void clear(){

				erase(cbegin(), cend());
				
				m_size = 0;
				m_head->next = m_tail;
				m_tail->prev = m_head;

			}
			/// Returns the first element in the list.
			T & front(){

				auto aux = begin();
				return *aux;

			}
			const T & front() const{

				auto aux = cbegin();
				return *aux;

			}
			/// Returns the last element in the list.
			T & back(){

				auto aux = end();
				aux--;
				return *aux;

			}
			const T & back() const{

				auto aux = cend();
				aux--;
				return *aux;

			}
			/// Adds an element to the begin of the list.
			void push_front(const T & value){
				insert(cbegin(), value);
			}
			/// Adds an element in the end of the list.
			void push_back(const T & value){
				insert(cend(), value);
			}
			/// Withdraws the first element in the list.
			void pop_front(){
				erase(begin());
			}
			/// Withdraws the last element in the list.
			void pop_back(){

				auto aux = end();
				aux--; //aux.current = (aux.current)->prev;
				erase(aux);

			}

			/// Assigns new elements to the list, replacing the current ones.
			void assign(const T & value){

				auto aux = m_head;

				while(aux->next != m_tail){
					aux = aux->next;
					aux->data = value;
				}
				
			}
			template<class InItr>
			void assign(InItr first, InItr last){
				
				auto aux = m_head;
				auto return_ = first;

				while(aux->next != m_tail){
					if(first == last){
						first = return_;
					}
					aux = aux->next;
					aux->data = *first;
					first++;
				}

			}
			void assign(std::initializer_list<T> ilist){

				auto aux = m_head;
				auto aux_2 = ilist.begin();
				auto return_ = ilist.begin();

				while(aux->next != m_tail){
					if(aux_2 == ilist.end()){
						aux_2 = return_;
					}
					aux = aux->next;
					aux->data = *aux_2;
					aux_2++;
				}
				
			}

			/// Inserts new elements to the list
			iterator insert(const_iterator itr, const T & value){

				m_size++;

				auto new_node = new Node(value);
				//new_node->data = value;
				new_node->next = itr.current;
				new_node->prev = (itr.current)->prev;

				((itr.current)->prev)->next = new_node;
				(itr.current)->prev = new_node;

				return iterator(new_node);

			}
			iterator insert(const_iterator pos, std::initializer_list<T> ilist){

				auto i = ilist.begin();

				for(/* Empty */; i != ilist.end(); i++){
					insert(pos, *i);
				}

				return(pos.current);

			}

			/// Removes an element or elements from the list.
			iterator erase(const_iterator itr){

				if(itr != cend()){

					auto before = (itr.current)->prev;
					auto post = (itr.current)->next;

					before->next = post;
					post->prev = before;
					m_size--;

					delete itr.current;

					return iterator(post);
				}

				return iterator(itr.current);

			}
			iterator erase(const_iterator first, const_iterator last){

				while(first != last){
					erase(first);
					first++;
				}

			}

			/// Searches for an elements in the list.
			const_iterator find(const T & value) const{

				auto aux = cbegin();
				
				while(aux != cend()){
					if(*aux == value){
						return aux;
					}
					aux.current = (aux.current)->next;
				}

			}

	};

}