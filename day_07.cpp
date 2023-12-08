// day_07.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

enum HandRank
{
    high_card = 1,
    one_pair = 2,
    two_pair = 3,
    three_of_a_kind = 4,
    full_house = 5, 
    four_of_a_kind = 6,
    five_of_a_kind = 7
};


bool compare_hands(const std::string& lhs, const std::string& rhi)
{
    for (size_t i = 0; i < lhs.size(); i++)
    {
        if (lhs[i] < rhi[i])
            return true;
        else if (lhs[i] > rhi[i])
            return false;
    }
    return true;
}

// A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, or 2
//Part One
const std::map<char, int> dict_part_one = {
    {'A', 13},
    {'K', 12},
    {'Q', 11},
    {'J', 10},
    {'T', 9},
    {'9', 8},
    {'8', 7},
    {'7', 6},
    {'6', 5},
    {'5', 4},
    {'4', 3},
    {'3', 2},
    {'2', 1}
};

//Part Two
const std::map<char, int> dict = {
    {'A', 13},
    {'K', 12},
    {'Q', 11},
    {'T', 9},
    {'9', 8},
    {'8', 7},
    {'7', 6},
    {'6', 5},
    {'5', 4},
    {'4', 3},
    {'3', 2},
    {'2', 1},
    {'J', 0}
};

class Hand
{
public:
    Hand(std::string cards, int bet):
    cards(cards), bet(bet){
        //added for part two.
        int jockers = 0;

        for (char c : this->cards)
        {
            if (c != 'J')
                map[c]++;
            //added for part two.
            else 
                jockers++;
        }

        //added for part two.
        if (jockers > 0)
        {
            if (jockers == 5)
                map['J'] = 5;
            else
            {
                auto elt = std::max_element(map.begin(), map.end(), [](const auto& lhs, const auto& rhs)
                    {
                        return lhs.second < rhs.second;
                    });
                //if(elt != map.end())
                map[elt->first] += jockers;
            }
               
        }
        
        this->set_rank();
    }
    
    bool operator < (const Hand& rhs)
    {
        if (this->rank < rhs.rank)
            return true;
        if (this->rank > rhs.rank)
            return false;

        for (size_t i = 0; i < cards.size(); i++)
        {
            if (dict.at(cards[i]) < dict.at(rhs.cards[i]))
                return true;
            if (dict.at(cards[i]) > dict.at(rhs.cards[i]))
                return false;
        }
        return true;
    }
    int get_bet() const 
    {
        return this->bet;
    }
private:

    void set_rank()
    {
        this->rank = get_rank(this->map);
    }
    HandRank get_rank(const std::map<char, int>& map)
    {
        if (map.size() == 1)
            return HandRank::five_of_a_kind;

        //Either 3,2 or 4,1
        if (map.size() == 2)
            for (const auto& p : map)
            {
                if (p.second == 1 || p.second == 4)
                    return HandRank::four_of_a_kind;
                return HandRank::full_house;
            }
        //Either 3,1,1 or 2,2,1 
        if (map.size() == 3)
            for (const auto& p : map)
            {
                if (p.second == 3)
                    return HandRank::three_of_a_kind;
                if (p.second == 2)
                    return HandRank::two_pair;
            }
        if (map.size() == 4)
            return HandRank::one_pair;
        return HandRank::high_card;
    }
private:
    std::string cards;
    int bet;
    int rank = 0;
    std::map<char, int> map;
};


int main()
{
    std::ifstream file("input\\day_07.txt");
    std::string line;
    std::vector < Hand > game;

    while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string hand;
        int bet;
        ss >> hand >> bet;
        game.emplace_back(Hand{hand, bet});
    }

    std::sort(game.begin(), game.end());
    int result = 0;
    int coefficient = 0;
    for (int i = 0; i < game.size(); i++)
    {
        result += (i+1) * game[i].get_bet();
    }

    std::cout << result << '\n';
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
