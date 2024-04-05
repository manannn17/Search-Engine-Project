#include <iostream>
#include <string>

#include "search.h"

using namespace std;

int main() {
    string filename;
    getline(cin, filename);

    // This will not work until we're done with the project!
    
    searchEngine(filename);
    
    string token = "Hello!"; // Example token with leading and trailing punctuation
    string cleanedToken = cleanToken(token); // Call cleanToken function
    cout << "Cleaned token: " << cleanedToken << endl;
    
    return 0;
}
