#include<iostream>
#include <vector>
#include "DirectorSkipList.hpp"
using namespace std;

/**
 * DirectorSkipList() is the default constructor for the class
 * Sets the capacity and levels to their default values, and size to 0.
 * Creates a head node with an empty director name, with the specified max levels of the skip list.
 * @param
 * @return
 */
DirectorSkipList::DirectorSkipList() {
    this->capacity = DEFAULT_CAPACITY;
    this->levels = DEFAULT_LEVELS;
    this->size = 0;
    head = new DirectorSLNode("", levels);
}

/**
 * DirectorSkipList() is the default constructor for the class
 * Sets the capacity and levels to their default values, and size to 0.
 * Creates a head node with an empty director name, with the specified max levels of the skip list.
 * @param _cap _levels
 * @return void
 */
DirectorSkipList::DirectorSkipList(int _cap, int _levels) {
    this->capacity = _cap;
    this->levels = _levels;
    this->size = 0;
    head = new DirectorSLNode("", levels);
}

/**
 * ~DirectorSkipList() is the deconstructor for the class
 * Begins at the head of the list, and deletes every node in the list
 * @param none
 * @return none
*/
DirectorSkipList::~DirectorSkipList() {
    DirectorSLNode* curr = head;
    while (curr != nullptr){
        DirectorSLNode* temp = curr;
        curr = curr->next[0];
        delete temp;
    }
}

/**
 * insert() takes a director name and movie node as input, and inserts this node into the skip list.
 * First, decides what the height of the node inserted is using levelPicker().
 * the vector tracker tracks which nodes come before where the new director node will be inserted using a basic traversal of the list.
 * Next, there is a check if temp is not a nullptr, or if the temp's director is the new director name, and if so, this means that the director was found.
 * If the director was found, the movieNode is added to the already existing node.
 * If not, a new DirectorSLNode is created and it is added into the skip list. Size is also incremented.
 * @param director _movie
 * @return void
*/
void DirectorSkipList::insert(string director, MovieNode* _movie) {
    DirectorSLNode* temp = head;
    int n_levels = levelPicker();
    vector <DirectorSLNode*> tracker(levels, nullptr);
    for (int i = levels - 1; i >=0; i--){
        while (temp->next[i] != nullptr && temp->next[i]->director < director){
            temp = temp->next[i];
        }
        tracker[i] = temp;
    }
    temp = temp->next[0];
    if (temp != nullptr && temp->director == director){
        temp->addMovie(_movie);
        return;
    } else {
        DirectorSLNode* new_node = new DirectorSLNode(director, n_levels);
        for (int i = 0; i < n_levels; i++){
            new_node->next[i] = tracker[i]->next[i];
            tracker[i]->next[i] = new_node;
        }
        new_node->addMovie(_movie);
        size++;
    }
}


/**
 * search() takes in a director name, traverses the skip list until the node with the director is found
 * or until there are no more nodes left to search.
 * Uses the same traversal and logic as the function insert().
 * @param director
 * @return DirectorSLNode*
*/
DirectorSLNode *DirectorSkipList::search(string director) {
    DirectorSLNode* curr = head;
    for (int i = levels - 1; i >= 0; i--)
    {
        while (curr->next[i] != nullptr && curr->next[i]->director < director)
        {
            curr = curr->next[i];
        }
    }
    curr = curr->next[0];
    if (curr != nullptr && curr->director == director)
    {
        return curr;
    }
    else
    {
        return nullptr;
    }
}

/**
 * prettyPrint() prints the skip list by layer with each node connected with an arrow.
 * @param none
 * @return none
*/
void DirectorSkipList::prettyPrint() {
    for (int i = 0; i < levels; i++){
        DirectorSLNode* temp = head->next[i];
        cout << "Level " << i + 1 << ": ";
        while (temp != nullptr){
            cout << temp->director << "-->";
            temp = temp->next[i];
        }
        cout << "NULL" << endl << endl;
    }
}

/**
 * levelPicker() uses the var n_levels and using a random number by simulating coin flips,
 * and either adding a level or finishing the process.
 * n_levels stops incrementing if n_levels reaches the max height of the skip list or if the random number isn't divisible by 2.
 * @param none
 * @return int
*/
int DirectorSkipList::levelPicker(){
    int n_levels = 1;
    while (n_levels < levels && rand() % 2 == 0){
        n_levels++;
    }
    return n_levels;
}
