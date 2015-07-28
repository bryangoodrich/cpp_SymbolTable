# Elementary Symbol Table

A symbol table is a data type that we use to associate *keys* and *values*. Clients can store these key-value pairs within the symbol table and then retrieve the value corresponding to a requested key. The API for an elementary symbol table includes get and put methods to store the key-value pairs and retrive the values according to the key. There are also methods for checking if a key is contained in the symbol table. 

Additional methods may include being able to compare keys. If this behavior is not required, a Hash Table implementation of a symbol table is often efficient for large number of keys. If having comparable keys is required behavior, a common implementation is the Binary Search Tree. 

For more, read http://introcs.cs.princeton.edu/java/44st/

My API
----------

The code here is non-functional because it depends on a Record data type provided in the class. It can be thought of as something like this

```
struct
{
    const KeyType    key;
          DataType value;
    // (String keys, String data)
    // Comparable methods, get/put methods for Key() and Data()
    // etc.
};
```

It has been too long since I worked on this code for class that I don't fully recall what was needed in its API, but I know things are missing. I have considered adopting the `std::pair <utility>` data type, but at this point, that will be a waste of time for something *I* already understand, and rather put effort into building in Java or C# (Sorry C++, I don't have fun with you!). Additionally, I never solved the delete requirement for the BSTree. It's not too difficult, but I never had time. Again, at this point is just isn't worth the effort. Try deleting in a Red-Black Tree instead! 

This API is left here as a demonstration of the pedogogical work performed in my CISP 400 Data Structures class from American River College, taught by the great David Fox. I would definitely say the main.cpp files need cleaning, use a different data set (simpler data set, like names and ages), and redesign the APIs to use core C++ data types like string and pairs, appropriately. 

Report and Stuff and Junk
------------

When my code did work, I ran some tests and compiled a report of the performance between the two implementations. Including in the code files is a list of hash functions that could be utilized in the Hash Table. This is an area I would definitely want to learn more about, because it is far from intuitive. Maybe a class on cryptography would be in order??

The one nice thing about this last (HashTable) assignment was that we utilized everything we coded (see my String and DDList classes), as well as it incorporated the Record data type provided by the professor. In this assignment, we put our working HashTable up against our previous assignment for the binary search tree (included together here). As a course design, this really reinforced our work effort, to build up a large working program from various parts, and it forced us to ensure our code worked along the way! Kudos for that. 

