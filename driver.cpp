#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "MovieHashTable.hpp"
#include "DirectorSkipList.hpp"
#include "MovieNode.hpp"

using namespace std;

// Function prototypes
MovieNode* parseMovieLine(string line);
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList);
void display_menu();

// Main function
int main(int argc, char* argv[]) {
    MovieHashTable movie_hash_table = MovieHashTable(stoi(argv[2]));
    DirectorSkipList director_skip_list = DirectorSkipList(stoi(argv[3]), DEFAULT_LEVELS);
    if(argc != 4){ // Conditional to check the number of arguments inputted
        cout << "Invalid number of arguments." << endl;
        cout << "Correct usage: ./<program name> <csv file> <hashTable size> <skipList size>" << endl;
        return 1;
    }

    readMovieCSV(argv[1], movie_hash_table, director_skip_list);
    director_skip_list.prettyPrint();
    cout << "NUMBER OF COLLISIONS: " << movie_hash_table.getCollisions() << endl;
    bool running = true; // boolean for keeping the program running
    string user_input = ""; // string that stores the user input for the menu
    while (running){
        display_menu(); // displays the menu for the user
        getline(cin, user_input); // gets user input
        if (user_input == "1"){
            cout << "Please input the title of the movie(Case sensitive):" << endl;
            cout << "Title: ";
            getline(cin, user_input);
            MovieNode* temp = movie_hash_table.search(user_input);
            if (temp != nullptr){
                cout << "The director of that movie is: " << temp->director << endl;
            } else {
                cout << "Movie couldn't be found!" << endl;
            }
        } else if (user_input == "2"){
            cout << "Please enter the name of a director below:" << endl;
            cout << "Name:";
            getline(cin, user_input);
            DirectorSLNode* temp = director_skip_list.search(user_input);
            if (temp != nullptr){
                cout << user_input << " has directed " << temp->movies.size() << " movies." << endl;
            } else {
                cout << "DIRECTOR COULD NOT BE FOUND." << endl;
            }
        } else if (user_input == "3"){
            cout << "Please input the title of the movie(Case sensitive):" << endl;
            cout << "Title: ";
            getline(cin, user_input);
            MovieNode* temp = movie_hash_table.search(user_input);
            if (temp != nullptr){
                cout << "Summary: " << temp->title << "(" << temp->genre << ") was released in " << temp->year << " and features " << temp->actors << endl;
                cout << "Plot: " << temp->description << endl;
            } else {
                cout << "Movie couldn't be found!" << endl;
            }
        } else if (user_input == "4"){
            cout << "Please enter the title of the director(Case sensitive):" << endl;
            cout << "Name:";
            getline(cin, user_input);
            DirectorSLNode* temp = director_skip_list.search(user_input);
            if (temp != nullptr){
                cout << user_input << " has made the following movies:" << endl;
                for (int i = 0; i < temp->movies.size(); i++){
                    cout << i+1 << ": " << temp->movies[i]->title << endl;
                }
            } else {
                cout << "DIRECTOR COULD NOT BE FOUND" << endl;
            }
        } else if (user_input == "5"){
            cout << "QUITTING..." << endl;
            running = false;
        } else { // checks that the user has entered a valid input
            cout << "Please enter a valid input. (1-5)" << endl;
        }
    }
    return 0;
}

// Function to parse a CSV line into a MovieNode object
MovieNode* parseMovieLine(string line) {
    stringstream ss(line);
    vector<string> fields;
    string field;

    // Loop through the characters in the line
    bool in_quotes = false;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '\"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            // add field to vector and reset for next field
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
            // handle double quotes inside a quoted field
            if (in_quotes && c == '\"' && i < line.length() - 1 && line[i+1] == '\"') {
                field += '\"'; // add the second double quote and skip it
                ++i;
            }
        }
    }
    fields.push_back(field);

    if (fields.size() != 12) {
        cerr << "Error: Invalid movie line format" << line << endl;
        return nullptr;
    }

    int rank = stoi(fields[0]);
    string title = fields[1];
    string genre = fields[2];
    string description = fields[3];
    string director = fields[4];
    string actors = fields[5];
    int year = stoi(fields[6]);
    int runtime = stoi(fields[7]);
    float rating = stof(fields[8]);
    int votes = stoi(fields[9]);
    float revenue = stof(fields[10]);
    int metascore = stoi(fields[11]);

    // Create a new MovieNode object with the parsed fields
    MovieNode* movie = new MovieNode(rank, title, genre, description, director, actors, year, runtime, rating, votes, revenue, metascore);
    return movie;
}

/**
 * readMovieCSV() takes in the filename, hash table and director list and populates them with the data from the file.
 * First, the firle is opened 
 */
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList) {
    ifstream myfile;
    myfile.open(filename);
    if (myfile.is_open()){
        string line; // stores data from each line in the csv file
        getline(myfile, line); // gets the first line of the csv file, which doesn't contain data.
        while(getline(myfile, line)){ // gets all lines from the inputted file.
            MovieNode* new_movie = parseMovieLine(line);
            movieTable.insert(new_movie->title, new_movie);
            directorList.insert(new_movie->director, new_movie);
        }
    } else {
        cout << "FILE COULD NOT OPEN." << endl;
    }
}

// Function to display the menu options
void display_menu() {
    cout << "Please select an option:" << endl;
    cout << "1. Find the director of a movie" << endl;
    cout << "2. Find the number of movies by a director" << endl;
    cout << "3. Find the description of a movie" << endl;
    cout << "4. List movies by director" << endl;
    cout << "5. Quit" << endl << endl;
    cout << "Enter an option:";
}
