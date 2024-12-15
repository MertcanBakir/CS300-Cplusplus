#include <iostream>
#include <fstream>

using namespace std;

string runLengthEncoding(string& flattened) {

    string rle = ""; // Start an empty string to store the encoded result

    if (flattened.empty()){ // Checks if the input string is empty if so, return the empty rle.
        return rle;
    }

    int count = 1; // Counter to track the frequency of consecutive characters

    char current = flattened[0]; // Start with the first character in the input string.

    // Loop through the input string starting from the second character.
    for (int i = 1; i < flattened.length(); ++i) {
        if (flattened[i] == current) { // If the current character matches the previous, increment the count
            count++;
        } else {
            // If the character changes, encode the previous run.
            if(current == '0'){
                rle += to_string(count) + 'B'; // Append the count and 'B' for black which is 0
            }
            else if(current == '1'){
                rle += to_string(count) + 'W'; // Append the count and 'W' for white which is 1
            }

            // Update current to the new character and reset the count
            current = flattened[i];
            count = 1;
        }
    }

    // adjust the final run of characters after the loop ends
    if(current == '0'){
        rle += to_string(count) + 'B';
    }
    else if(current == '1'){
        rle += to_string(count) + 'W';
    }

    return rle; // return the encoded result string
}

string formatToBack(const string& flattened) { // fix the encoded string to the normal image form
    string formatted = "";
    for (int i = 0; i < flattened.size(); i++) {
        formatted += flattened[i];
        if ((i + 1) % 28 == 0 && i + 1 != flattened.size()) {
            formatted += '\n';
        }
    }
    return formatted;
}

class HashTable{
public:
    int hashFunction(const string& encoded){ // its a hash function to put the element to array according to this function
        char last_char = encoded.at(encoded.size() - 2); // takes the last number from the encoded string
        int last_int = last_char - '0'; // change to int from char
        if(list[last_int] != ""){ // if the element is not empty according to this function do linear probing
            last_int = linearProbing(last_int);
        }
        return last_int;
    }
    int linearProbing(int& index) { // doing linear probing, checks if the next element in the sequence is empty and put it if it is empty
        for (int i = 0; i < 23; i++) {
            if (list[(index + i) % 23] == "") {
                return ((index + i) % 23);
            }
        }
        return -1;
    }
    void insert(const string& key, const int& index){ // insert to the array
        list[index] = key;
    }

    string find(const string& key) {
        char last_char = key.at(key.size() - 2); // Get the second last character of the key
        int base_index = last_char - '0'; // Convert character to integer
        int index;

        for (int i = 0; i < 23; i++) {
            index = (base_index + i) % 23; // Calculate the circular index for linear probing

            if (list[index] == key) {
                return "true"; // Key found
            }
            if (list[index] == "") {
                break; // Empty slot encountered, key cannot exist beyond this point
            }
        }

        return "false"; // Key not found
    }
private:

    string list[23]; // array that store the elements
};


int main() {
    string N, filename, answer;
    HashTable hash;
    cout << "Enter image number to insert into the hash table (or 'query' to continue): \n";
    cin >> N;  // take a input for image file
    while(N != "query"){ // take input until input is query
        filename = "image" + N + ".txt";
        ifstream file(filename); // open file
        string flattened = "";
        char chr;
        while (file.get(chr)) { // read the image char by char
            if (chr == '0' || chr == '1') { // add to the string if it 0 or 1
                flattened += chr;
            }
        }
        file.close();
        string encoded = runLengthEncoding(flattened); // convert the image text to the encoded
        hash.insert(encoded, hash.hashFunction(encoded)); // insert to hash
        cout << "Image " + N + " inserted into the hash table." << endl;
        cout << "Enter image number to insert into the hash table (or 'query' to continue): \n";
        cin >> N;
    }


    cout <<"Enter image number to query (or 'exit' to quit): \n";
    cin >> answer; // take input for query file
    while(answer != "exit"){ // take the input until exit is entered
        filename = "query" + answer + ".txt";
        ifstream file(filename);
        string flattened = "";
        char chr;
        while (file.get(chr)) { // read the image char by char
            if (chr == '0' || chr == '1') { // add to the string if it 0 or 1
                flattened += chr;
            }
        }
        file.close();
        string encoded = runLengthEncoding(flattened);// convert the image text to the encoded
        if (hash.find(encoded) == "true") { // checks that query image is in the hash
            cout << "RLE String for query" << answer << ".txt found in hash table." << endl;
            cout << formatToBack(flattened) << endl; // convert the encoded to the back to image
        } else { // means it is not in the hash
            cout << "No match for the image with encoding: " << encoded << endl;
        }
        cout <<"Enter image number to query (or 'exit' to quit): \n";
        cin >> answer;
    }

    cout << "Exiting the program!" << endl;



    return 0;
}
