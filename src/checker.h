#ifndef CHECKER_H
#define CHECKER_H
#include <bits/stdc++.h>

namespace poker {

struct HighestDeck {
    std::string hand;
    std::vector<std::string> cards;
};

class Checker {
public:
    static HighestDeck check(std::vector<std::string> deck);

private:
    static std::vector<int> freqR;
    static std::vector<int> freqS;

    static inline int rton(std::string r);
    static inline std::string ntor(int n);
    static inline int sotn(char s);
    static inline char ntos(int n);
    static inline void initFreq();
    static void cardSplitter(std::vector<int>& ranks, std::vector<int>& suites, std::vector<std::string> deck);
    static void fillFreq(std::vector<int>& ranks, std::vector<int>& suites);
    static std::vector<std::string> isFullHouse(const std::vector<int>& ranks, const std::vector<int>& suites);
    static std::vector<std::string> isFlush(const std::vector<int>& ranks, const std::vector<int>& suites);
    static std::vector<std::string> isStraight(const std::vector<int>& ranks, const std::vector<int>& suites);
    static std::vector<std::string> isThreeOfaKind(const std::vector<int>& ranks, const std::vector<int>& suites);
    static std::vector<std::string> isTwoPair(const std::vector<int>& ranks, const std::vector<int>& suites);
    static std::vector<std::string> isPair(const std::vector<int>& ranks, const std::vector<int>& suites);
};

}

#endif