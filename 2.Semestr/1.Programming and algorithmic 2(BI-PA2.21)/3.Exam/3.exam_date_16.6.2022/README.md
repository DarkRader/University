## Set using BST II

The CTree class implements the "set" structure, the planks themselves are strings. The implementation uses BST. Your task is to supplement the methods for inserting and removing elements and the destroyer. Balancing the tree is not necessary. At the same time, a bidirectional connector of inserted elements is stored, which stores the order of their insertion. The class has an interface:

constructor

Set to default, no need to change it.
destructor

He must correctly release the memory. Implementation is your task.
copy constructor

=delete, disabled.
operator=

=delete, disabled.
bool insert (string key)

To add a key element to the set, it must add it to the correct place in the tree. The comparison is made by relational string operators, lexicographically, smaller strings are stored in the left subtree, larger ones in the right. Also, it must correctly process and remember the insertion order (variables m_First and m_Last). Returns true for success or false if the element already exists. Implementation is your task.
bool erase (string key)

Removes a key from the set. Returns true for success, false if element not found. It must remove the element from the tree and at the same time from the Linked List, which monitors the order-update correctly m_NextOrder and m_PrevOrder. It is necessary to preserve the properties of the tree and at the same time the mutual order in the linked list. Implementation is your task.
m_Root

Pointer to CNode for tree root.
m_First

Pointer to CNode pointing to the first inserted element. Using m_First → m_NextOrder .. → m_NextOrder → nullptr should go through all elements according to the insertion order.
m_Last

Pointer to CNode pointing to the last inserted element.
CNode

An auxiliary class for a node in a tree. Contains variables:
m_Key = string of the element.
m_L = pointer to the left subtree if nullptr does not exist.
m_R = pointer to the right subtree if nullptr does not exist.
m_NextOrder = pointer to the next element in the order of insertion, or nullptr for the last element.
m_PrevOrder = pointer to the previous element according to the insertion order, or nullptr for the first element.
