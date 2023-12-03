// day_01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <map>

int main()
{
    std::ifstream file("inputs\\day_01_01.txt");
    if (!file)
    {
        std::cerr << "No file in Location" << '\n';
        exit(-1);
    }

	std::string line;
    std::uint64_t count = 0;

    //PART ONE
    /*while (getline(file, line))
    {
        auto it = std::stable_partition(line.begin(), line.end(), std::isdigit);
        int number = 0;
        number += (line[0] - '0') * 10;
        number += *(it - 1) - '0';
        count += number;
    }*/

    //PART TWO
    const std::vector<std::string> digits = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

    while (getline(file, line))
    {
        std::pair<int, int> first = std::make_pair(line.size(), 0);
        std::pair<int, int> last = std::make_pair(-1, 0);
        for (size_t i = 0; i < digits.size(); i++)
        {
            auto it = std::search(line.begin(), line.end(), digits[i].begin(), digits[i].end());

            if (it != line.end())
            {
                int index = it - line.begin();
                if (first.first > index)
                    first = std::make_pair(index, i % 10);
            }

            it = std::find_end(line.begin(), line.end(), digits[i].begin(), digits[i].end());

            if (it != line.end())
            {
                int index = it - line.begin();
                if (last.first < index)
                    last = std::make_pair(index, i % 10);
            }
        }

        
        count += first.second * 10 + last.second;
        std::cout << line << '\t' << first.second * 10 + last.second << '\n';
    }
	

    std::cout << count << '\n';
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
