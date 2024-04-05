#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include<fstream>
#include<algorithm>

using namespace std;

/**
 * Cleans a specific token by:
 * - Removing leading and trailing punctuation
 * - Converting to lowercase
 * If the token has no letters, returns the empty string.
 */
string cleanToken(string s) {
    // TODO_STUDENT
    // Initialize start and end indices to exclude leading and trailing punctuation
    size_t start=0;
    size_t end=s.length();

    while(start<s.length() && ispunct(s[start]))
    {
        start++;
    }
    
    //size_t end=s.length();  // Remove trailing punctuation
    while(end>start && ispunct(s[end - 1]))
    {    
        end--;
    }

    for(size_t i=start;i<end;i++)  // Convert to lowercase
    {
        s[i]=tolower(s[i]);
    }
    
    for(size_t i=start;i<end;i++) // Check if the token has any letters
    {
        if(isalpha(s[i])) 
        {
            return s.substr(start, end - start);
        }
    }
    return "";  // If no letters are present, return empty string
}

/**
 * Returns a set of the cleaned tokens in the given text.
 */
set<string> gatherTokens(string text) {
    // TODO_STUDENT
    set<string> tokens;
    string word;
    size_t pos=0;

    
    while(pos<text.length()) // Loop until we reach the end of the text
    { 
        while(pos<text.length() && (text[pos] == ' ' || text[pos] == '\t')) // Skip leading whitespaces
        {
            pos++;
        }
        
        size_t start=pos; // Find the end of the current word
        while(pos<text.length() && text[pos] != ' ' && text[pos] != '\t') 
        {
            pos++;
        }
        
        word=text.substr(start, pos - start);  // Extract the word between start and end positions
        string cleaned=cleanToken(word);  // Clean the word and insert it into the set of tokens
        
        if (!cleaned.empty()) 
        {
            tokens.insert(cleaned);
        }
    }
    return tokens;
}

/**
 * Builds the inverted index from the given data file. The existing contents
 * of `index` are left in place.
 */
int buildIndex(string filename, map<string, set<string>>& index) {
    // TODO_STUDENT
    ifstream file(filename);
    index.clear(); // clear index if file not found

    if(!file.is_open()) //checking if the file is open or not
    {
        cout<<"Invalid filename."<<endl;
        return 0;
    }
    string url, text;
    int pageCount=0;
    while(getline(file, url) && getline(file, text)) //taking the input
    {
        set<string> tokens=gatherTokens(text); 
        for(const string& token : tokens) 
        {
            index[token].insert(url);
        }
        pageCount++;
    }
    return pageCount;
}


/**
 * Runs a search query on the provided index, and returns a set of results.
 *
 * Search terms are processed using set operations (union, intersection, difference).
 */
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    // TODO_STUDENT

    set<string> result;

    // Process the first term
    size_t pos = sentence.find(" ");
    string term;
    if(pos != string::npos) 
    {
        term = sentence.substr(0, pos);
    } 
    else 
    {
        term = sentence;
    }
    term=cleanToken(term);
    result = index[term];

    // Process the remaining terms
    while(pos != string::npos) 
    {
        pos++;
        string modifier = "";
        if(sentence[pos] == '+' || sentence[pos] == '-') 
        {
            modifier=sentence.substr(pos, 1);
            pos++;
        }

        size_t nextPos = sentence.find(" ", pos);
        if(nextPos != string::npos) 
        {
            term=sentence.substr(pos, nextPos - pos);
        } 
        else 
        {
            term=sentence.substr(pos);
        }
        term=cleanToken(term);
        //cleanToken(term);

        set<string> matches=index[term];

        

        set<string> cleanedMatches;
        for(const string& match : matches) 
        {
            string cleanedMatch=match; // Create a copy to modify
            cleanToken(cleanedMatch); // Clean the token
            cleanedMatches.insert(cleanedMatch); // Insert the cleaned token into the new set
        }

        // Replace matches with the cleaned set
        matches=cleanedMatches;

        // Perform set operations
        if(modifier == "+") 
        {
            set<string> intersection;
            set_intersection(result.begin(), result.end(), matches.begin(), matches.end(), inserter(intersection, intersection.begin()));
            result=intersection;
        } 
        else if(modifier == "-") 
        {
            set<string> difference;
            set_difference(result.begin(), result.end(), matches.begin(), matches.end(), inserter(difference, difference.begin()));
            result = difference;
        } 
        else 
        {
            // cout << "Before: ";
            // for (const auto& res : result) {
            //     cout << res << " "<<endl;
            // }
            cout << endl;
            set<string> uni;
            set_union(result.begin(), result.end(), matches.begin(), matches.end(), inserter(uni, uni.begin()));
            result = uni;

            // cout << "after Result: ";
            // for (const auto& res : result) {
            //     cout << res << " "<<endl;
            // }
        }

        pos=nextPos;
    }

    return result;
}

/**
 * Runs the main command loop for the search program
 */
void searchEngine(string filename) {
    // TODO_STUDENT
    map<string, set<string>> index;
        int pageCount=buildIndex(filename, index);

        // Print statistics
        cout<<"Stand by while building index..."<<endl;
        cout<< "Indexed " << pageCount << " pages containing " << index.size() << " unique terms" <<endl;

        // Command loop
        while(true) 
        {
            cout<< "\nEnter query sentence (press enter to quit): ";  // Prompt the user to enter a query sentence
            string query;
            getline(cin, query);

            if(query.empty()) // Check if the query is empty
            {
                break;
            }

            set<string> matches = findQueryMatches(index, query);  // Find the matching pages and print the URLs
            cout<<"Found "<< matches.size() <<" matching pages"<<endl;
            for(const string& url : matches) 
            {
                cout<<url<<endl;
            }
        }
    // Closing message
    cout << "Thank you for searching!" << endl;
}
