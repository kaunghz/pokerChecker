#include "test.h"
#include "colors.h"
#include "checker.h"
using namespace std;

namespace tester {

inline void printDeck(vector<string>& deck) {
    cout << '{';
    for (auto& d: deck) cout << d << ", ";
    cout << "}\n";
}

void assertTest(vector<string> expectedCards, string expectedName, poker::HighestDeck actual, const string& testName) {
    if (expectedName != actual.hand) {
        cerr << BOLDRED;
        cerr << "Test " << testName << " failed: expected hand " << expectedName << "\n";
        cerr << "Actual hand: " << actual.hand << "\n";
        cerr << RESET;
        exit(1);
    }
    sort(expectedCards.begin(), expectedCards.end());
    sort(actual.cards.begin(), actual.cards.end());
    if (expectedCards != actual.cards) {
        cerr << BOLDRED;
        cerr << "Test " << testName << " failed: expected cards ";
        printDeck(expectedCards);
        cerr << "Actual cards: ";
        printDeck(actual.cards);
        cerr << RESET;
        exit(1);
    }
}

void test() {
    {
        vector<string> deck = {"2H", "3D", "5S", "9C", "KD", "4H", "7C"};
        poker::HighestDeck result = poker::Checker::check(deck);
        assertTest(vector<string>{"KD"}, "High Card", result, "Test 1");
        cout << BOLDGREEN;
        cout << "Test case 1 passed: High Card\n";
    }

    {
        vector<string> deck = {"2H", "2D", "5S", "9C", "KD", "4H", "7C"};
        poker::HighestDeck result = poker::Checker::check(deck);
        assertTest(vector<string>{"2D", "2H"}, "Pair", result, "Test 2");
        cout << BOLDGREEN;
        cout << "Test case 2 passed: Pair\n";
    }

    {
        vector<string> deck = {"2H", "2D", "5S", "5C", "KD", "4H", "7C"};
        poker::HighestDeck result = poker::Checker::check(deck);
        assertTest(vector<string>{"2H", "2D", "5S", "5C"}, "Two Pair", result, "Test 3");
        cout << BOLDGREEN;
        cout << "Test case 3 passed: Two Pair\n";
    }

    {
        vector<string> deck = {"2H", "2D", "2S", "9C", "KD", "4H", "7C"};
        poker::HighestDeck result = poker::Checker::check(deck);
        assertTest(vector<string>{"2H", "2D", "2S"}, "Three of a Kind", result, "Test 4");
        cout << BOLDGREEN;
        cout << "Test case 4 passed: Three of a Kind\n";
    }

    {
        vector<string> deck = {"2H", "3D", "4S", "5C", "6H", "9C", "KD"};
        poker::HighestDeck result = poker::Checker::check(deck);
        assertTest(vector<string>{"2H", "3D", "4S", "5C", "6H"}, "Straight", result, "Test 5");
        cout << BOLDGREEN;
        cout << "Test case 5 passed: Straight\n";
    }

    {
        vector<string> deck = {"2H", "4H", "6H", "8H", "KH", "9C", "QD"};
        poker::HighestDeck result = poker::Checker::check(deck);
        assertTest(vector<string>{"2H", "4H", "6H", "8H", "KH"}, "Flush", result, "Test 6");
        cout << BOLDGREEN;
        cout << "Test case 6 passed: Flush\n";
    }

    {
        vector<string> deck = {"2H", "2D", "2S", "3C", "3D", "4H", "5S"};
        poker::HighestDeck result = poker::Checker::check(deck);
        assertTest(vector<string>{"2H", "2D", "2S", "3C", "3D"}, "Full House", result, "Test 7");
        cout << BOLDGREEN;
        cout << "Test case 7 passed: Full House\n";
    }

    cout << "All specific test cases passed!" << endl;
}

}
