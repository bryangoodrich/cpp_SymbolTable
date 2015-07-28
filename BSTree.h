#ifndef CUSTOM_BSTREE_H
#define CUSTOM_BSTREE_H

#include<utility>  // std::pair, std::make_pair

class BSTree
{
    struct node
    {
        node*    left_child;
        node*   right_child;
        Record       record;
        node (node*, node*, const Record&);
    };
    node* root;

    friend Record    _Find (const KeyType&, const node*);
    friend void    _Insert (const Record&, node*);
    friend unsigned _Depth (const node*);
    friend void     _InOrd (const node*, void (*)(const Record&)); 
    friend void    _PreOrd (const node*, void (*)(const Record&));
    friend void   _PostOrd (const node*, void (*)(const Record&));
    friend void PostDelete (node*);

public:

    // PRE: None
    // POST: An empty BSTree is created
    BSTree ( );

    // PRE: None
    // POST: The BSTree is destroyed and all allocated memory is released
    ~BSTree ( );

    // PRE: None
    // POST: Function Return Value == (tree is empty)
    bool IsEmpty ( ) const;

    // PRE: NOT IsEmpty()
    // POST: Function Return Value == Record item with this key. If this key
    //   is not in tree, it returns an "empty" Record
    Record Find (const KeyType&) const;

    // PRE: None
    // POST: The Record inserted into BSTree. If the BST already contains this
    //   key, it does nothing. left_child < parent <= right_child
    void Insert (const Record&);

    // PRE: NOT IsEmpty()
    // POST: Record with this key is deleted; the tree is still a BST. If item
    //   with key is not in tree, it does nothing
    void Delete (const KeyType& key);

    // PRE: NOT IsEmpty()
    // POST: BSTree is traversed in-order and the function is applied to each node.
    void InOrderTraversal (void (*)(const Record&));

    // PRE: NOT IsEmpty()
    // POST: BSTree is traversed pre-order and the function is applied to each node.
    void PreOrderTraversal (void (*)(const Record&));

    // PRE: NOT IsEmpty()
    // POST: BSTree is traversed post-order and the function is applied to each node.
    void PostOrderTraversal (void (*)(const Record&));

    // PRE: NOT IsEmpty()
    // POST: Function Return Value == depth of the tree
    unsigned Depth ( ) const;
};
#endif // CUSTOM_BSTREE_H


