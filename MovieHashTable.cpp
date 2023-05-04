#include<iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include "MovieHashTable.hpp"
using namespace std;

/**
 * MovieHashTable() is the default constructor for the hash table.
 * Uses the default capactiy given.
 * Sets all indices of the table to a nullptr.
 * @param none
 * @return none
 */
MovieHashTable::MovieHashTable() {
    table_size = DEFAULT_HTABLE_CAPACITY;
    table = new MovieNode*[DEFAULT_HTABLE_CAPACITY];
    for (int i = 0; i < DEFAULT_HTABLE_CAPACITY; i++){
        table[i] = nullptr;
    }
}

/**
 * MovieHashTable() is the constructor with a specified size s.
 * Sets the table_size to the int s and sets all table values to nullptr.
 * @param s
 * @return none
 */
MovieHashTable::MovieHashTable(int s) {
    table_size = s;
    table = new MovieNode*[s];
    for (int i = 0; i < s; i++){
        table[i] = nullptr;
    }
}

/**
 * 
 */
MovieHashTable::~MovieHashTable() {
    delete table;
}

/**
 * AsciiSum() takes an input string and sums all of the ASCII values of the string.
 * @param input_string
 * @return int
 */
int MovieHashTable::AsciiSum(string input_string){
    int sum = 0; // sum keeps track of the sum of the ASCII characters of the input_string
    for (int i = 0; i < input_string.length(); i++){
        sum += input_string[i];
    }
    return sum;
}

/**
 * hash() takes the title of a movie and hashes the string into a key.
 * @param title
 * @return int
 */
int MovieHashTable::hash(string title) {
    int sum = 0;
    string identikey = "qutu4904";

    for (int i = 0; i < title.length(); i++){
        sum += title[i] + AsciiSum(identikey);
    }
    return (sum % table_size);
}

/**
 * 
 */
void MovieHashTable::insert(string title, MovieNode* movie) {
    int key = hash(title);
    if (table[key] == nullptr){
        table[key] = movie;
    } else {
        movie->next = table[key];
        table[key] = movie;
        setCollisions();
    }
}

/**
 * search() finds a node in the table by hashing the title that is being searched for and checking if the movie exists at that index in the table.
 * @param title
 * @return MovieNode*
 */
MovieNode* MovieHashTable::search(string title) {
    int search_key = hash(title);
    if (table[search_key] != nullptr){
        MovieNode* temp = table[search_key];
        while (temp->title != title && temp->next != nullptr){
            temp = temp->next;
        }
        if (temp->title == title){
            return temp;
        } else {
            return nullptr;
        }
    }
    return nullptr;
}

/**
 * getCollisions() returns the num of collisions.
 * @param none
 * @return int
 */
int MovieHashTable::getCollisions() {
    return n_collisions;
}

/**
 * setCollisions() increments collisions by 1.
 * @param none
 * @return none
 */
void MovieHashTable::setCollisions() {
    n_collisions++;
}
