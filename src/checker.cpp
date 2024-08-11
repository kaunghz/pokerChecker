#include "checker.h"
using namespace std;

namespace poker {

vector<int> Checker::freqR(15, 0); // Initialize freqR with size 15
vector<int> Checker::freqS(4, 0);  // Initialize freqS with size 4

HighestDeck Checker::check(vector<string> deck) {
    HighestDeck result;
    vector<int> ranks, suites;
    initFreq();
    cardSplitter(ranks, suites, deck);
    fillFreq(ranks, suites);
    vector<string> cards = isFullHouse(ranks, suites);
    if (!cards.empty()) {
        result.hand = "Full House";
        result.cards = cards;
        return result;
    }
    cards = isFlush(ranks, suites);
    if (!cards.empty()) {
        result.hand = "Flush";
        result.cards = cards;
        return result;
    }
    cards = isStraight(ranks, suites);
    if (!cards.empty()) {
        result.hand = "Straight";
        result.cards = cards;
        return result;
    }
    cards = isThreeOfaKind(ranks, suites);
    if (!cards.empty()) {
        result.hand = "Three of a Kind";
        result.cards = cards;
        return result;
    }
    cards = isTwoPair(ranks, suites);
    if (!cards.empty()) {
        result.hand = "Two Pair";
        result.cards = cards;
        return result;
    }
    cards = isPair(ranks, suites);
    if (!cards.empty()) {
        result.hand = "Pair";
        result.cards = cards;
        return result;
    }
    result.hand = "High Card";
    int cmp = 0;
    int rank, suite;
    for (int i = 0; i < ranks.size(); i++) {
        if ((ranks[i] * 100) + (4 - suites[i]) > cmp) {
            cmp = (ranks[i] * 100) + (4 - suites[i]);
            rank = ranks[i];
            suite = suites[i];
        }
    }
    result.cards = {ntor(rank) + ntos(suite)};
    return result;
}

inline int Checker::rton (string r) {
    if (r == "J") return 11;
    if (r == "Q") return 12;
    if (r == "K") return 13;
    if (r == "A") return 14;
    return stoi(r);
}

inline string Checker::ntor (int n) {
    if (n == 11) return "J";
    if (n == 12) return "Q";
    if (n == 13) return "K";
    if (n == 14) return "A";
    return to_string(n);
}

inline int Checker::sotn (char s) {
    if (s == 'S') return 0;
    if (s == 'H') return 1;
    if (s == 'D') return 2;
    if (s == 'C') return 3;
    throw runtime_error("suite name unrecognized!\n");
    return -1;
}

inline char Checker::ntos (int n) {
    if (n == 0) return 'S';
    if (n == 1) return 'H';
    if (n == 2) return 'D';
    return 'C';
}

void Checker::initFreq() {
    freqR = vector<int>(15, 0);
    freqS = vector<int>(4, 0);
}

void Checker::cardSplitter (vector<int>& ranks, vector<int>& suites, vector<string> deck) {
    for (auto& card: deck) {
        int rank = rton(card.substr(0, card.size() - 1));
        int suite = sotn(card.back());
        ranks.push_back(rank);
        suites.push_back(suite);
    }
}

void Checker::fillFreq (vector<int>& ranks, vector<int>& suites) {
    for (auto& r: ranks) {
        freqR[r]++;
    }
    for (auto& s: suites) {
        freqS[s]++;
    }
}

vector<string> Checker::isFullHouse(const vector<int>& ranks, const vector<int>& suites) {
    int three = 0;
    int two = 0;
    for (int rank=2; rank<=14; ++rank) {
        if (freqR[rank] >= 3) {
            three = rank;
        }
    }
    for (int rank=2; rank<=14; ++rank) {
        if (freqR[rank] >= 2 && rank != three) {
            two = rank;
        }
    }
    if (three == 0 || two == 0) return {};
    vector<int> threeS;
    vector<int> twoS;
    for (int i=0; i<ranks.size(); ++i) {
        if (ranks[i] == three) {
            threeS.push_back(suites[i]);
        } else if (ranks[i] == two) {
            twoS.push_back(suites[i]);
        }
    }
    sort(threeS.begin(), threeS.end(), greater<int>());
    sort(twoS.begin(), twoS.end(), greater<int>());
    vector<string> result;
    for (int i=0; i<3; ++i) {
        result.push_back(ntor(three) + ntos(threeS[i]));
    }
    for (int i=0; i<2; ++i) {
        result.push_back(ntor(two) + ntos(twoS[i]));
    }
    return result;
}

vector<string> Checker::isFlush(const vector<int>& ranks, const vector<int>& suites) {
    for (int i=3; i>=0; --i) {
        if (freqS[i] >= 5) {
            vector<string> result;
            vector<int> flushR;
            for (int j=0; j<ranks.size(); ++j) {
                if (suites[j] == i) {
                    flushR.push_back(ranks[j]);
                }
            }
            sort(flushR.begin(), flushR.end(), greater<int>());
            for (int j=0; j<5; ++j) {
                result.push_back(ntor(flushR[j]) + ntos(i));
            }
            return result;
        }
    }
    return {};
}

vector<string> Checker::isStraight(const vector<int>& ranks, const vector<int>& suites) {
    for (int i=10; i>=2; --i) {
        int cnt = 0;
        for (int j=0; j<5; ++j) {
            if (freqR[i+j] == 0) break;
            ++cnt;
        }
        if (cnt == 5) {
            vector<int> v(5);
            for (int j=0; j<ranks.size(); ++j) {
                if (ranks[j] >= i && ranks[j] <= i+4) {
                    v[ranks[j] - i] = max(v[ranks[j] - i], suites[j]);
                }
            }
            vector<string> result;
            for (int j=0; j<5; ++j) {
                result.push_back(ntor(i+j) + ntos(v[j]));
            }
            return result;
        }
    }
    return {};
}

vector<string> Checker::isThreeOfaKind(const vector<int>& ranks, const vector<int>& suites) {
    int three = 0;
    for (int rank=2; rank<=14; ++rank) {
        if (freqR[rank] >= 3) {
            three = rank;
        }
    }
    if (three == 0) return {};
    vector<int> threeS;
    for (int i=0; i<ranks.size(); ++i) {
        if (ranks[i] == three) {
            threeS.push_back(suites[i]);
        }
    }
    sort(threeS.begin(), threeS.end(), greater<int>());
    vector<string> result;
    for (int i=0; i<3; ++i) {
        result.push_back(ntor(three) + ntos(threeS[i]));
    }
    return result;
}

vector<string> Checker::isTwoPair(const vector<int>& ranks, const vector<int>& suites) {
    int first = 0;
    int second = 0;
    for (int rank=2; rank<=14; ++rank) {
        if (freqR[rank] >= 2) {
            first = rank;
        }
    }
    for (int rank=2; rank<=14; ++rank) {
        if (freqR[rank] >= 2 && rank != first) {
            second = rank;
        }
    }
    if (first == 0 || second == 0) return {};
    vector<int> firstS;
    vector<int> secondS;
    for (int i=0; i<ranks.size(); ++i) {
        if (ranks[i] == first) {
            firstS.push_back(suites[i]);
        }
        if (ranks[i] == second) {
            secondS.push_back(suites[i]);
        }
    }
    sort(firstS.begin(), firstS.end(), greater<int>());
    sort(secondS.begin(), secondS.end(), greater<int>());
    vector<string> result;
    for (int i=0; i<2; ++i) {
        result.push_back(ntor(first) + ntos(firstS[i]));
    }
    for (int i=0; i<2; ++i) {
        result.push_back(ntor(second) + ntos(secondS[i]));
    }
    return result;
}

vector<string> Checker::isPair(const vector<int>& ranks, const vector<int>& suites) {
    int two = 0;
    for (int rank=2; rank<=14; ++rank) {
        if (freqR[rank] >= 2) {
            two = rank;
        }
    }
    if (two == 0) return {};
    vector<int> twoS;
    for (int i=0; i<ranks.size(); ++i) {
        if (ranks[i] == two) {
            twoS.push_back(suites[i]);
        }
    }
    sort(twoS.begin(), twoS.end(), greater<int>());
    vector<string> result;
    for (int i=0; i<2; ++i) {
        result.push_back(ntor(two) + ntos(twoS[i]));
    }
    return result;
}
}