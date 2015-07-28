#include <iostream>
using namespace std;
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <sys/timeb.h>
#include <vector>
#include <algorithm>

#include "HashTable.h"
#include "BSTree.h"



template <class T>
void mix (T* r, unsigned n, const vector<int>& v);
double TIME (void);



// For Swapping
// const unsigned IND_CNT = 1050001;
// unsigned ind[IND_CNT];

// For Storing Records and Keys in Search and Retrieval
const unsigned MAX_RECS = 500000;
KeyType keys[MAX_RECS];
Record  recs[MAX_RECS];
vector<int> indices(MAX_RECS);



int main()
{
  BSTree       bst;
  HashTable   htbl;
  double    tstart, total_time;  // For time keeping



/*
  ifstream inI("ind.dat", ios::in|ios::binary);
  if ( !inI )
  {
    cout << "file open error: ind.dat"<<endl;
    cout << "Make sure that this file is in the working directory"<<endl;
    cin.get();  exit(1);
  }
  inI.read(reinterpret_cast<char*>(ind), IND_CNT*sizeof(unsigned));
  inI.close();
*/
  ifstream in ("CISP430records.dat", ios::in|ios::binary );
  if (!in)
  {
    cout << "file open error: CISP430records.dat"<<endl;
    cout << "Make sure that this file is in the working directory"<<endl;
    cin.get();  exit(1);
  }
  cout << "Done: Open Files" << endl << "*************************" << endl;



/*
  recs[recs_read].read(in);
  keys[recs_read] = recs[recs_read].Key();
  recs_read++;
*/
  cout << "Read Files"<<endl;
  unsigned recs_read = 0;
  while (recs_read < MAX_RECS)
  {
    // if (!(recs_read % ((MAX_RECS/10) ? MAX_RECS/10 : 1)))  cout << recs_read <<endl;
    Record rec;
    rec.read(in);
    if (!in.eof())
    {
      recs[recs_read] = rec;
      keys[recs_read] = rec.Key();
      recs_read++;
    }
  }
  in.close();
  cout << "Done: Read files" << endl << "*************************" << endl;


  for (unsigned j=0; j < recs_read; j++)  // populate preallocated indices vector
    indices.push_back(j);  // 0, 1, 2, ..., recs_read-1
  srand(12345);  // Set seed for indices shuffle
  random_shuffle (indices.begin(), indices.end());  // Shuffle idx for mix
  mix(recs, recs_read, indices);
  mix(keys, recs_read, indices);



  cout << "Insert data into Binary Search Tree" << endl;
  tstart = TIME();
  for ( unsigned i=0; i<recs_read; i++ )
  {
    bst.Insert(recs[i]);
  }
  cout << std::setprecision(4) << "Done: Insert (" << ((TIME() - tstart) / 1000) << "s)" << endl << "*************************" << endl;

  cout << "Insert data into Hash Table" << endl;
  tstart = TIME();
  for ( unsigned i=0; i<recs_read; i++ )
  {
    htbl.Insert(recs[i]);
  }
  cout << "Done: Insert (" << ((TIME() - tstart) / 1000) << "s)" << endl << "*************************" << endl;


  cout << "Test: Find in Binary Search Tree" << endl;
  tstart = TIME();
  for ( unsigned i=0; i<recs_read; i++ )
  {
    //if (!(i % ((recs_read/10) ? recs_read/10 : 1)))  cout << i <<endl;
    Record ret = bst.Find(keys[i]);
    if (ret.Key() != keys[i])
    {

      cout << i << "  Find Error. You found the Record with key: "
      << ret.Key() << endl << " when searching for key: "
      << keys[i] << endl
      << "<enter> to continue" << endl;
      cin.get();
    }
  }
  cout << "Done: Find (" << ((TIME() - tstart) / 1000) << "s)" << endl << "*************************" << endl;


  cout << "Test: Find in Hash Table" << endl;
  tstart = TIME();
  for ( unsigned i=0; i<recs_read; i++ )
  {
    //if (!(i % ((recs_read/10) ? recs_read/10 : 1)))  cout << i <<endl;
    Record ret = htbl.Retrieve(keys[i]);
    if (ret.Key() != keys[i])
    {
      cout << i << "  Find Error. You found the Record with key: "
      << ret.Key() << endl << " when searching for key: "
      << keys[i] << endl
      << "<enter> to continue" << endl;
      cin.get();
    }
  }
  cout << "Done: Find (" << ((TIME() - tstart) / 1000) << "s)" << endl << "*************************" << endl;


// 633 ms
  cout << "Test: Random Finds in Binary Search Tree" << endl;
  total_time = 0.0;
  for (unsigned j=0; j < 1000; j++)
  {
    srand(time(NULL));  // Random seed for sampling
    random_shuffle (indices.begin(), indices.end());
    unsigned idx;
    tstart = TIME();
    for (unsigned i=0; i < 100000; i++)
    {
      idx = indices[i];
      Record ret = bst.Find(keys[idx]);
      if (ret.Key() != keys[idx])
      {
        cout << i << "  Find Error. You found the Record with key: "
        << ret.Key() << endl << " when searching for key: "
        << keys[idx] << endl
        << "<enter> to continue" << endl;
        cin.get();
      }
    }
    total_time += (double)(TIME() - tstart);
  }
  total_time = total_time / 1000;  // Average
  cout << "Done: Random Finds (Average 100,000 finds in " << total_time << "ms)" << endl << "*************************" << endl;


// 600 ms
  cout << "Test: Random Finds in Hash Table" << endl;
  total_time = 0.0;
  for (unsigned j=0; j < 1000; j++)
  {
    srand(time(NULL));  // Random seed for sampling
    random_shuffle (indices.begin(), indices.end());
    unsigned idx;
    tstart = TIME();
    for (unsigned i=0; i < 100000; i++)
    {
      idx = indices[i];
      Record ret = htbl.Retrieve(keys[idx]);
      if (ret.Key() != keys[idx])
      {
        cout << i << "  Find Error. You found the Record with key: "
        << ret.Key() << endl << " when searching for key: "
        << keys[idx] << endl
        << "<enter> to continue" << endl;
        cin.get();
      }
    }
    total_time += (double)(TIME() - tstart);
  }
  total_time = total_time / 1000;  // Average
  cout << "Done: Random Finds (Average 100,000 finds in " << total_time << "ms)" << endl << "*************************" << endl;



  cout << endl << "*************************" 
       << endl << "**********done***********" 
       << endl << "*************************" << endl;
  return 0;

} // End Main



template <class T>
void swap ( T* r, unsigned i, unsigned s )
{
  T temp = r[i];
  r[i] = r[s];
  r[s] = temp;
}

template <class T>
void mix (T* r, unsigned n, const vector<int>& v)
{

  for (unsigned j=0; j < n; j++)
  {
    unsigned s = v[j];
    swap(r,j,s);
  }
}

double TIME (void)
{
    struct timeb t;
    ftime(&t);
    return (((1000.0 * t.time) + t.millitm));
}




