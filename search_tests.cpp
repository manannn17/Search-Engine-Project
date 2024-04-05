#include <gtest/gtest.h>

#include "search.h"
#include "tests/build_index.h"
#include "tests/clean_token.h"
#include "tests/find_query_matches.h"
#include "tests/gather_tokens.h"

// TODO_STUDENT: write your tests here!

TEST(CleanToken, ExampleEmptyTest) {
    cout << "Hi! This shows up in the terminal." << endl;
}

// TEST(cleanToken, PunctuationInMiddleAndStart) {
    
//     map<string, set<string>> tests;
//     tests["!he!llo"].insert("he!llo");
//     testCleanToken(tests);
// }

TEST(CleanToken, PunctuationInMiddleNotAtEitherEnd) {
    //EXPECT_EQ(cleanToken("he!llo"), "he!llo");
    map<string, set<string>> tests;
    tests["he!llo"].insert("he!llo");
    // tests["m@n!go"].insert("M@n!g0");
    // tests["he!ll!o"].insert("he!ll!o");
    testCleanToken(tests);
}

TEST(CleanToken, PunctuationInMiddleAndStart) {
    //EXPECT_EQ(cleanToken("!he!llo"), "he!llo");
    map<string, set<string>> tests;
    tests["he!llo"].insert("!he!llo");
    // tests["!he@llo"].insert("He@llo");
    // tests["?m@ngo"].insert("M@ngo");
    testCleanToken(tests);
}

TEST(CleanToken, PunctuationInMiddleAndEnd) {
    //EXPECT_EQ(cleanToken("he!llo!"), "he!llo");
    map<string, set<string>> tests;
    tests["he!llo"].insert("he!llo!");
    testCleanToken(tests);
}

TEST(CleanToken, PunctuationInBothEnd) {
    map<string, set<string>> tests;

    tests["hello"].insert(".hello.");
    tests["hello"].insert("...hello...");
    tests["hello"].insert("?!/hello.!?");

    tests["timesheet"].insert(";timesheet;");
    tests["timesheet"].insert("!.;timesheet;.!");
    tests["timesheet"].insert("?!.,.timesheet.,.!?");

    testCleanToken(tests);
}

TEST(gatherTokens, LeadingSpaces) {
    set<string> tokens=gatherTokens("  hello world");
    set<string> expected={"hello", "world"};
    EXPECT_EQ(tokens, expected);
}

TEST(gatherTokens, TrailingSpaces) {
    set<string> tokens=gatherTokens("hello world  ");
    set<string> expected={"hello", "world"};
    EXPECT_EQ(tokens, expected);
}

TEST(gatherTokens, MultipleSpacesBetweenWords) {
    set<string> tokens=gatherTokens("hello   world");
    set<string> expected={"hello", "world"};
    EXPECT_EQ(tokens, expected);
}

TEST(buildIndex, TinyTxt) {
    string filename = "tiny.txt";
    map<string, set<string>> expected ={ 
      
        // {"blue", {"www.dr.seuss.net", "www.rainbow.org"}},
        // {"be", {"www.example.com", "www.otherexample.com"}},
        // {"free", {"www.otherexample.com"}},
        // {"ora", {"www.example.com"}},
        // {"not", {"www.example.com"}},
        // {"want", {"www.otherexample.com"}}
      
        { "blue", { "www.dr.seuss.net", "www.rainbow.org" }}, 
        {"bread", { "www.shoppinglist.com" }}, 
        {"cheese", { "www.shoppinglist.com" }}, 
        {"eat", { "www.bigbadwolf.com" }}, 
        {"eggs", { "www.shoppinglist.com" }}, 
        {"fish", { "www.dr.seuss.net", "www.shoppinglist.com" }}, 
        {"green", { "www.rainbow.org" }}, 
        {"i'm", { "www.bigbadwolf.com" }}, 
        {"indigo", { "www.rainbow.org" }}, 
        {"milk", { "www.shoppinglist.com" }}, 
        {"not", { "www.bigbadwolf.com" }}, 
        {"one", { "www.dr.seuss.net" }}, 
        {"orange", { "www.rainbow.org" }}, 
        {"red", { "www.dr.seuss.net", "www.rainbow.org" }}, 
        {"to", { "www.bigbadwolf.com" }}, 
        {"trying", { "www.bigbadwolf.com" }}, {"two", { "www.dr.seuss.net" }}, 
        {"violet", { "www.rainbow.org" }}, 
        {"yellow", { "www.rainbow.org" }}, {"you", { "www.bigbadwolf.com" }} 
    };
    map<string, set<string>> studentIndex;
    int studentNumProcesed = buildIndex(filename, studentIndex);
}

TEST(buildIndex, FileNotFound) {
    map<string, set<string>> index;
    int pages=buildIndex("nonexistent.txt", index);
    EXPECT_EQ(pages, 0);
    EXPECT_TRUE(index.empty());
}

TEST(findQueryMatches, MissingFirstTerm) {
  map<string, set<string>> index {
    {"hello", {"example.com", "uic.edu"}},
    {"world", {"example.com"}}
  };
  
  set<string> expected;

  EXPECT_EQ(findQueryMatches(index, "missing"), expected);
}

// Modified search term not in map 
TEST(findQueryMatches, MissingModifiedTerm) {
  map<string, set<string>> index {
    {"hello", {"example.com", "uic.edu"}},
    {"world", {"example.com"}} 
  };

  set<string> expected;

  EXPECT_EQ(findQueryMatches(index, "hello +missing"), expected);
}

// Unmodified search term not in map
TEST(findQueryMatches, MissingUnmodifiedTerm) {
  map<string, set<string>> index {
    {"hello", {"example.com", "uic.edu"}},
    {"world", {"example.com"}}
  };
  
  set<string> expected = {"example.com", "uic.edu"};

  EXPECT_EQ(findQueryMatches(index, "hello missing"), expected); 
}

// Search term with '-' not in map
TEST(findQueryMatches, MissingDifferenceTerm) {
  map<string, set<string>> index {
    {"hello", {"example.com", "uic.edu"}},
    {"world", {"example.com"}}
  };

  set<string> expected = {"example.com", "uic.edu"}; 

  EXPECT_EQ(findQueryMatches(index, "hello -missing"), expected);
}