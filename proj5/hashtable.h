//Abygail Stiekman
//11.20.2016 
//COP4530 Proj5

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <utility>

namespace cop4530
{
template <typename K, typename V>
class HashTable{
public:
    HashTable(size_t size);   //constructor
    ~HashTable();   //destructor

    bool contains(const K &k);  //checks if key is in table
    bool match(const std::pair<K,V> &kv) ; //check if KV pair in table
    bool insert(const std::pair<K,V> &kv);  //adds kv pair into table
    bool insert(std::pair<K,V> && kv);  //move version of insert
    bool remove(const K &k);    //delete the key & corresponding value

    void clear();   //empty hash table
    bool load(const char *filename);    //load content of file into table, delim ' '
    void dump();    //display all entires in hash table
    bool write_to_file(const char *filename); //write all elements from table to file

    size_t getSize(){return currentSize;}   //member function to get currentSize

    // max_prime is used by the helpful functions provided
    // to you.
    static const unsigned int max_prime = 1301081;
    // the default_capacity is used if the initial capacity
    // of the underlying vector of the hash table is zero.
    static const unsigned int default_capacity = 11;
private:
    void makeEmpty();   //delete all elements in hash table, clear() calls this
    void rehash();  //called when num of elements in table is greater than size of vector
    size_t myhash(const K &k);  //return index of vector entry where k is stored
    unsigned long prime_below(unsigned long);   //helper function for resizing
    void setPrimes(std::vector<unsigned long> &);   //helper function for resizing

    //Private member values
    std::vector<std::list<std::pair<K,V>> > theList;    //Chain linked hashTable list
    size_t currentSize;
};
//Include the hashtable.hpp for template member definitions
#include "hashtable.hpp"
}
#endif