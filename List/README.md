## ls::list ##

### What is it? ###

List it is a library similar to the `std::list` library. Lists are sequence containers that allow constant time insert and erase operation anywhere in the sequence. It is usually implemented as a doubly-linked list (like ours). This way each new element is stored in unrelated storage locations, but the order is kept by associating the new element with its predecessor and its sucessor.

### Functions ###

**MODIFIERS**

`push_back()`: Adds an element to the begin of the list.

`push_front()`: Adds an element in the end of the list.

`pop_front()`: Withdraws the first element in the list.

`pop_back()`: Withdraws the last element in the list.

`assign()`: Assigns new elements to the list, replacing the current ones.

`insert()`: Inserts new elements to the list

`erase()`: Removes an element or elements from the list.

`find()`: Searches for an elements in the list.

**ITERATORS**

`begin()`: eturns an iterator to the first element in the list.

`cbegin()`: Returns a constant iterator to the first element in the list.

`end()`: Returns an iterator to the last element in the list.

`cend()`: Returns a constant iterator to the last element of the list.

### Compiling ###

To compile the program use the following code:

`make`

### Running ###

To run the program use the following code:

`./bin/list`

This program was made by ANDERSON CAIO and RAYAN AVELINO. ⒸAll rights reserved.