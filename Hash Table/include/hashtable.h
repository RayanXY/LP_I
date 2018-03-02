#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <forward_list>
#include <iostream>
#include <cmath>

template<class KeyType, class DataType>
class HashEntry{
		
	public:
		HashEntry (KeyType k_, DataType d_)
			: m_key(k_)
			, m_data(d_)
		{ /* Empty */ }
		KeyType m_key;
		DataType m_data;

};

template<typename KeyType, 
		 typename DataType, 
		 typename KeyHash = std::hash<KeyType>,
		 typename KeyEqual = std::equal_to<KeyType>>

class HashTbl{

	using Entry = HashEntry<KeyType, DataType>; 
	
	public:

		/// Constructor 
		HashTbl(int tbl_size_ = DEFAULT_SIZE)
			: m_size (tbl_size_) 								  //!< Actual size of the table.
			, m_count(0)										  //!< Count the elements storaged int the elements.
			, m_data_table(new std::forward_list<Entry>[m_size])  //!< Store data.
		{/* Empty */}
		/// Desconstructor 
		virtual ~HashTbl(){

			clear();
			delete [] m_data_table;

		}
		/// Functions
		bool insert(const KeyType & k_, const DataType & d_);
		bool remove(const KeyType & k_);
		bool retrieve(const KeyType & k_, DataType & d_) const;
		bool empty(void) const;
		void clear(void);
		void print() const;
		size_t size(void);
		unsigned long int count(void) const;

	private:
		void rehash();
		unsigned int m_size;
		unsigned int m_count;
		std::forward_list< Entry > * m_data_table;
		static const short DEFAULT_SIZE = 11;

};

#include "hashtable.cpp"

#endif