// day_02.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Determine which games would have been possible if the bag had been loaded with only 12 red cubes, 13 green cubes, and 14 blue cubes.
// What is the sum of the IDs of those games?

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <regex>
#include <numeric>

struct Condition {
    int red = 12;
    int green = 13;
    int blue = 14;

    int getPower()
    {
        return red * green * blue;
    }
};

class Pick {
public:
    Pick(int game, int red = 0, int green = 0, int blue = 0) :
        game(game), red(red), green(green), blue(blue)
    {
        //std::cout << "Pick is " << "Game " << game << "with picks : red " << red << " green " << green << " blue " << blue << '\n';
    }

    void addPick(int red, int green, int blue)
    {
        this->red = std::max(this->red, red);
        this->green = std::max(this->green, green);
        this->blue = std::max(this->blue, blue);
    }

    void updateColor(std::string color, int pick)
    {
        if (color == "red")
            this->red = std::max(this->red, pick);
        else if (color == "green")
            this->green = std::max(this->green, pick);
        else if (color == "blue")
            this->blue = std::max(this->blue, pick);
    }

    bool is_valid(const Condition& condition)
    {
        return this->red <= condition.red&&
            this->green <= condition.green&&
            this->blue <= condition.blue;
    }

    void print(Condition condition = {}) {
        std::cout << "game " << game << " is_valid " << is_valid(condition)  << " red" << red << " green " << green << " blue " << blue << '\n';
    }

    int getGame() {
        return this->game;
    }

    int getPower() const {
        return this->red * this->blue * this->green;
    }
private:
    int blue = 0;
    int red = 0;
    int green = 0;
    int game = 0;
};

int main()
{
    std::ifstream file("inputs/day_02.txt");
    if (!file)
    {
        std::cerr << "Invalid input file" << '\n';
        exit(-1);
    }

    std::string line = "Game 1: 20 green, 3 red, 2 blue; 9 red, 16 blue, 18 green; 6 blue, 19 red, 10 green; 12 red, 19 green, 11 blue";
    std::vector<int> valid_picks;
    std::vector<int> unvalid_picks;
    Condition condition;
    std::uint64_t sum = 0L;
    
    while (getline(file, line))
    {
        // Define regular expressions to match the pattern
        std::regex gameRegex(R"(Game (\d+):)");
        std::regex pickRegex(R"((\d+) (red|blue|green))");

        // Create iterators for searching the string
        std::sregex_iterator gameIt(line.begin(), line.end(), gameRegex);
        std::sregex_iterator pickIt(line.begin(), line.end(), pickRegex);

        // Iterate over each game
        while (gameIt != std::sregex_iterator()) {
            std::smatch match = *gameIt;
            std::cout << "Game: " << match[1] << std::endl;
            Pick pick(std::stoi(match[1]));

            // Iterate over each pick in the current game
            while (pickIt != std::sregex_iterator()) {
                std::smatch pickMatch = *pickIt;
                std::string color = pickMatch[2];
                int count = std::stoi(pickMatch[1]);
                //std::cout << color << ": " << count << std::endl;
                pick.updateColor(color, count);
                ++pickIt;
            }

            // Move to the next game
            pick.print();
            ++gameIt;
            pick.is_valid(condition) ? valid_picks.push_back(pick.getGame()) : unvalid_picks.push_back(pick.getGame());
            sum += pick.getPower();
        }
    }
    
    std::cout << "Valid Picks: " << valid_picks.size() << "\tUnvalid Picks: " << unvalid_picks.size() << '\n';
    std::cout << "Sum Valid: " << std::accumulate(valid_picks.begin(), valid_picks.end(), 0) << '\n';
    std::cout << "Sum Unvalid: " << std::accumulate(unvalid_picks.begin(), unvalid_picks.end(), 0) << '\n';

    std::cout << "Power Sum: " << sum << '\n';

    return 0;
    
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
