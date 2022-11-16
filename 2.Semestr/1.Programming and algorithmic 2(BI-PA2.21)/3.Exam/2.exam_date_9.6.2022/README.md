## Table using BST

Create a table (map) using Binary Search Trees without balancing, both the key and the value is string. The location of the element in the tree is derived from the lexicographic ordering of the keys (operator`>`). A constructor implemented from Ladi, a copy constructor, or an assignment operator does not need to be implemented. The table allows you to insert elements (your implementation) and additionally store the order of their insertion. To do this, use the m_nextorder pointer in the CNode instance (it forms a contiguous list) and the m_first, m_last pointers in CTree.

### Stored data in classes:

CNode (string m_key, string m_val, CNode* m_L, CNode* m_R, CNode* m_nextOrder);

CTree (CNode* m_first, CNode* m_last, CNode* m_root);

### Need to implement:

destructor
bool insert (key, val)... inserts the element in the correct place in the tree, returns true if successful (the key is not yet in the tree)
bool isSet (key)... returns true for the contained key
operator " ... list pairs (key, value) in order of insertion into the table"

