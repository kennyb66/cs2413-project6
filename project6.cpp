// Project 6
// CS 2413 Data Structures
// Spring 2023
#include <iostream>
#include <string> // for storing string
#include <fstream> // for reading a file again and again
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

void mapDisplay(map<int, vector<string>> m) { // display function for ordered map
    cout << "Map: " << endl; // printing that the display is for the ordered map
    for(auto& it : m) { // nested for loop that iterates through each pair in the map
        if(!it.second.empty()) { // checks to see if the vector<string> value in the map is empty
            cout << it.first << ": "; // if the vector is not empty, print the key associated with it
            for(auto& name : it.second) { // for loop to iterate through the vector of strings
                cout << name << " "; // print each name in the vector
            }
            cout << endl; // print a new line
        }
    }
}
void unorderedMapDisplay(unordered_map<int, vector<string>> m) { // display function for unordered map
    cout << "Unordered Map: " << endl; // printing that the display is for the unordered map
    for(auto& it : m) { // nested for loop that iterates through each pair in the map
        if(!it.second.empty()) { // checks to see if the vector<string> value in the map is empty
            cout << it.first << ": "; // if the vector is not empty, print the key associated with it
            for(auto& name : it.second) { // for loop to iterate through the vector of strings
                cout << name << " "; // print each name in the vector
            }
            cout << endl; // print a new line
        }
    }
}
int hashFunction(string s) { // hash function for both the ordered and unordered maps
    int multiplication; // value to store the multiplication
    int sum = 0; // int value to be returned
    char c; // char variable used for hashing
    for(int i = 0; i < s.size(); i++) { // for loop to iterate through the characters in the string s parameter
        c = s[i]; // setting char c = to the char at index i of the string s
        multiplication = c * i / 10; // multiplying the value of char by i to ensure that the weight of each character in the string is taken into account to avoid collisions
        sum += multiplication; // adding the value of the char to sum
    }
    return sum; // int value that contains the sum of each char from the string parameter
}
using namespace std;

int main()
{
    string fileName; // to read in the name of the fileInput from redirected input
    cin >> fileName; // reading in the filename
    cout << "Name of fileInput: " << fileName << endl; // printing the filename
    map <int, vector<string>> m1; // map object
    ifstream fI; // ifstream object used for file opening
    fI.open(fileName); // opening the file
    char option; // char variable used to check if there is an insertion or removal
    string temp; // temp variable used to store a name from the file
    while(fI >> option) { // while the file has more operations
        fI >> temp; // read in the name from the file
        if (option == 'I') { // if the option is an insertion
            vector<string> v; // create a vector of strings object
            if(m1[hashFunction(temp)].size() >= 1) { // if the vector<string> at a given key already contains a value (collision)
                m1[hashFunction(temp)].push_back(temp); // add the string to the vector at that key
            }
            else { // if the vector<string> is empty
                v.push_back(temp); // add the name to the vector
                m1[hashFunction(temp)] = v; // call hashFunction on the name, then set m1 at the returned key value equal to the vector of strings
            }
        }
            else if (option == 'R') { // if the option is a removal
                for(int i = 0; i < 10000; i++) { // for loop to check each key of m1
                    if(m1.find(i) != m1.end()) { // if there is an iterator returned from find, and that iterator is not pointing to the end of m1
                        if(m1.at(i).at(0) == temp) { // if the vector contains temp
                            m1.erase(i); // erase the pair at index i from m1
                        }
                    }
                }
            }
        }
     mapDisplay(m1); // calling display function for m1
    fI.close(); // close the opened file
    unordered_map<int, vector<string>> m2; // unordered map
    fI.open(fileName); // open a file again in read mode
    while(fI >> option) // while the file has more operations
    {
        fI >> temp; // read in the name from the file
        if(option == 'I') { // if the option is an insertion
            vector<string> v; // create a vector of strings object
            if(m2[hashFunction(temp)].size() >= 1) { // if the vector<string> at a given key already contains a value (collision)
                m2[hashFunction(temp)].push_back(temp); // add the string to the vector at that key
            }
            else {
                v.push_back(temp); // add the name to the vector
                m2[hashFunction(temp)] = v; // call hashFunction on the name, then set m2 at the returned key value equal to the vector of strings
            }
        }
        else if(option == 'R') { // if the option is a removal
                for(int j = 0; j < 10000; j++) { // for loop to check each key of m2
                    if(m2.find(j) != m2.end()) { // if there is an iterator returned from find, and that iterator is not pointing to the end of m2
                        if(m2.at(j).at(0) == temp) { // if the vector contains temp
                            m2.erase(j); // erase the pair at index i from m2
                        }
                    }
                }
        }
    }
   unorderedMapDisplay(m2); // calling display function for m2
    fI.close(); // close the opened file
    return 0;
}