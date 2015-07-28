#ifndef CUSTOM_HASHTABLE_H
#define CUSTOM_HASHTABLE_H

#include "../DLList/DLList.h"

static const unsigned SIZE = 104729;
static const ItemType  KNF = Record("KEY NOT FOUND", "KEY NOT FOUND");



typedef Record ItemType;

class HashTable
{
    DLList   hash[SIZE];
    unsigned bucket_sizes[SIZE];
    bool     is_empty;

    void     SetEmpty ( );
    unsigned hash_function (const KeyType& key) const;

public:

    // Post: An empty HashTable is created and initialized.
    HashTable ( );

    // Post: The HashTable is destroyed and all memory is released.
    ~HashTable ( );

    // Pre:  There is room in the HashTable
    // Post: The ItemType is inserted into the HashTable according to its key.
    void Insert (const ItemType&);

    // Pre:  The HashTable is not empty
    // Post: The ItemType with this key is returned. 
    //   If the table does not contain an ItemType with this key it returns
    //     ItemType (“KEY NOT FOUND”, ”KEY NOT FOUND”)
    ItemType Retrieve (const KeyType& key);

    // Pre:  The HashTable is not empty
    // Post: The ItemType with this key is removed from the HashTable. 
    //   If the key is not found, it does nothing.
    void Delete (const KeyType& key);

    // Post: Returns true if there is nothing in the HashTable.
    bool IsEmpty ( ) const;
};
#endif // CUSTOM_HASHTABLE_H




