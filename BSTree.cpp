#include "BSTree.h"

// Static Global "Key Not Found" Record
static const Record KNF = Record("KEY NOT FOUND", "KEY NOT FOUND");

BSTree::node::node (node* lc = NULL, node* rc = NULL, const Record& r = KNF)
:left_child(lc), right_child(rc), record(r) {}

BSTree::BSTree ( )
{
    root = NULL;
}

BSTree::~BSTree ( )
{
    if ( !IsEmpty() ) 
        PostDelete(root);
}

bool BSTree::IsEmpty ( ) const
{
    return !root;
}

Record BSTree::Find (const KeyType& key) const
{
    if ( IsEmpty() ) return KNF;

    return _Find(key, root);
}

void BSTree::Insert (const Record& r)
{
    if ( IsEmpty() )
        root = new node(NULL, NULL, r);
    else
        _Insert(r, root);
}

void BSTree::Delete (const KeyType& key)
{
    // if (!IsEmpty()) ...
}

void BSTree::InOrderTraversal (void (*FUN)(const Record&))
{
    if ( !IsEmpty() ) 
        _InOrd(root, FUN);
}

void BSTree::PreOrderTraversal (void (*FUN)(const Record&))
{
    if ( !IsEmpty() ) 
        _PreOrd(root, FUN);
}

void BSTree::PostOrderTraversal (void (*FUN)(const Record&))
{
    if ( !IsEmpty() ) 
        _PostOrd(root, FUN);
}

unsigned BSTree::Depth ( ) const
{
    return ( (IsEmpty() ) ? 0 : _Depth(root));
}



// I HAZ FRIENDS!
Record _Find(const KeyType& key, const BSTree::node* n)
{
    if (key == n->record.Key()) return n->record;
    if (key <  n->record.Key())
    {
        if (n->left_child) return _Find(key, n->left_child);
        else return KNF;
    }
    else
    {
        if (n->right_child) return _Find(key, n->right_child);
        else return KNF;
    }
}

void _Insert (const Record& r, BSTree::node* n)
{
    if (r.Key() == n->record.Key()) return;
    if (r.Key() <  n->record.Key())
    {
        if (!n->left_child) n->left_child = new BSTree::node(NULL, NULL, r);
        else _Insert(r, n->left_child);
    }
    else
    {
        if (!n->right_child) n->right_child = new BSTree::node(NULL, NULL, r);
        else _Insert(r, n->right_child);
    }
}

unsigned _Depth (const BSTree::node* n)
{
    unsigned left_depth  = ((!n->left_child)  ? 0 : _Depth(n->left_child));
    unsigned right_depth = ((!n->right_child) ? 0 : _Depth(n->right_child));

    return 1 + ((left_depth > right_depth) ? left_depth : right_depth);
}

void _InOrd (const BSTree::node* n, void (*FUN)(const Record&))
{
    if (n->left_child)  _InOrd(n->left_child, FUN);
    FUN(n->record);
    if (n->right_child) _InOrd(n->right_child, FUN);
}

void _PreOrd (const BSTree::node* n, void (*FUN)(const Record&))
{
    FUN(n->record);
    if (n->left_child)  _PreOrd(n->left_child, FUN);
    if (n->right_child) _PreOrd(n->right_child, FUN);
}

void _PostOrd (const BSTree::node* n, void (*FUN)(const Record&))
{
    if (n->left_child)  _PostOrd(n->left_child, FUN);
    if (n->right_child) _PostOrd(n->right_child, FUN);
    FUN(n->record);
}

void PostDelete (BSTree::node* n)
{
    if (n->left_child) PostDelete(n->left_child);
    if (n->right_child) PostDelete(n->right_child);
    delete n;
}
