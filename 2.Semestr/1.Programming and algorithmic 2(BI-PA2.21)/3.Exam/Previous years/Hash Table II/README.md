## Hash Table II

The CHash class implements the data type table, where both the key and the value are strings. The table works as a hash table, collisions are solved using a chain of records. The task is to add to the CHash Class A method for inserting and deleting elements.

The CHash class implements the scatter table in the standard way. In addition, it also stores information about the order of insertion of individual pairs (key, value). It will provide the following interface:

constructor
initializes the instance. The parameter is the size of the scatter table. The implementation is done in the supplied source code, it is not necessary/convenient to change it.
destructor
frees resources allocated by the instance. The destructor is implemented in the attached source code.
copy constructor
it is not tested in this role, it is disabled in the supplied implementation (= delete)
operator =
it is not tested in this role, it is disabled in the supplied implementation (= delete)
Ins (key, val)
the method adds a specified pair of strings (key, val) to the table. The method must respect the hashing algorithm, that is, add an element to such a table row that corresponds to the hash value of the key module table size. In addition, our implementation remembers the order in which elements are inserted into the table (see the member variables m_FirstOrder and m_LastOrder below), the Ins method must also correctly handle this order. The table is organized in such a way that it stores the conflicting keys in a Linked List (record concatenation, external concatenation, separate chaining). The return value is true for success or false for error (the key already exists in the table). The implementation of this method is your task.
Del (key)
the method removes the element with the specified key value from the table. The return value is true for success or false for error (the key no longer exists in the table). The implementation of this method is your task.
IsSet
the method detects whether a given key exists in the table. The method is implemented in the supplied source code, it does not need to be modified. You can use the supplied code to test the correctness of your methods, or by studying this method you can remind yourself of the operation of the hash table.
ForEach
the method goes through the entire hash table, for each element it calls the supplied function/functor / Lambda. The method goes through the elements in the order of insertion into the table. The implementation is available in the supplied source code, demonstrates the use of the m_nextorder/m_PrevOrder join list.
hashFn (str, mod)
the method calculates the hash code for a given string str and the size of the hash table mod. use the method to determine the position in the hash table where you will insert a new pair (key, value).
TItem
is an auxiliary structure that stores custom values in a hash table. Contain:
m_Key-stored key
m_Val - stored value belonging to the key
m_NextHash-a pointer to a unidirectional linked list of pairs (key, value) with the same hash code. The Linked List always starts with the corresponding index of the hash table (m_Table)and ends with NULL. The order of the elements in this list is not limited.
m_NextOrder-a pointer to the next element in the Linked List, which indicates the order of entering values in the hash table. m_NextOrder points to the next element (that is, the element inserted later), or has a NULL value for the last element inserted.
m_PrevOrder-a pointer to the previous element in the Linked List, which indicates the order of entering values in the hash table. m_PrevOrder points to the previous element (that is, the element inserted earlier), or has a NULL value for the first inserted element.
m_Table
a custom hash table, implemented as a pointer to a dynamically allocated array of pointers. Each element of this table points to the beginning of the linked list for the corresponding hash code value.
m_Size
table size m_Table
m_FirstOrder
pointer to the first inserted element, the successive iteration m_FirstOrder - m_NextOrder-m_NextOrder ... NULL can go through the elements in the table in the order of insertion (from the first inserted to the latest inserted)
m_LastOrder
pointer to the last inserted element, the successive iteration m_LastOrder - m_PrevOrder-m_PrevOrder ... NULL can go through the elements in the table in the reverse order of insertion (from the latest inserted to the first inserted)
