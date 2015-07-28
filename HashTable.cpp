#include "HashTable.h"



HashTable::HashTable ( )
:is_empty(true) 
{
    for (unsigned j=0; j<SIZE; j++)
        bucket_sizes[j] = 0;
}

HashTable::~HashTable ( )
{}

void HashTable::Insert (const ItemType& it)
{
    const unsigned index = hash_function(it.Key());
    DLList* bucket = &hash[index];
    if (!bucket->IsEmpty()) bucket->Reset();
    bucket->InsertBefore(it);

    bucket_sizes[index]++;
    is_empty = false;
}

ItemType HashTable::Retrieve (const KeyType& key)
{
    if (IsEmpty()) return KNF;

    const unsigned index = hash_function(key);
    DLList* bucket = &hash[index];

    if (bucket->IsEmpty()) return KNF;
    bucket->Reset();
    while (!bucket->EndOfList())
    {
        if (bucket->CurrentItem().Key() == key) return bucket->CurrentItem();
        else bucket->Advance();
    }
    return KNF;
}

void HashTable::Delete (const KeyType& key)
{
    if (IsEmpty()) return;

    const unsigned index = hash_function(key);
    DLList* bucket = &hash[index];

    if (bucket->IsEmpty()) return;
    bucket->Reset();
    while (!bucket->EndOfList())
    {
        if (bucket->CurrentItem().Key() == key)
        {
            bucket->Delete();
            bucket_sizes[index]--;
            SetEmpty();
        }
        bucket->Advance();
    }
}

bool HashTable::IsEmpty ( ) const
{
    return is_empty;
}

void HashTable::SetEmpty ( )
{
    bool flag = true;
    for (unsigned j=0; j < SIZE; j++)
        if (bucket_sizes[j] > 0) flag = false;
    is_empty = flag;
}

unsigned HashTable::hash_function (const KeyType& key) const {
    const unsigned LENGTH = key.length();

    unsigned hash = 1;
    for (unsigned j=0; j < LENGTH; j++) 
        hash *= key[j] * 5;

    return hash % SIZE;
}




