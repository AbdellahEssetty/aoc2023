// day_03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>

struct Number {
    std::pair<int, int> coords;
    int width;
    int data;
};

struct Symbol {
    std::pair<int, int> coords;
    char data;
};

bool is_symbol(const unsigned char& c)
{
    return std::ispunct(c) && c != '.';
}

bool is_adjacent(const Symbol& symbol, const Number& number)
{
    return (symbol.coords.first >= number.coords.first -1 && symbol.coords.first <= number.coords.first+ 1) && 
        (symbol.coords.second >= number.coords.second - 1 && symbol.coords.second <= number.coords.second + number.width);
}



class Engine {
public:
    void pushNumber(const Number& number)
    {
        numbers.emplace_back(number);
    }

    void pushSymbol(const Symbol& symbol)
    {
        symbols.emplace_back(symbol);
    }
public:
    std::vector<Number> numbers;
    std::vector<Symbol> symbols;
};


int main()
{
    std::ifstream file("inputs\\day_03.txt");
    if (!file)
    {
        std::cerr << "Unvalid file location" << '\n';
        exit(-1);
    }

    std::string line;
    Engine engine;
    int row = 0;
    while (getline(file, line))
    {
        // Define a regular expression pattern to match numbers
        std::regex pattern("\\d+");

        // Use std::sregex_iterator to find all matches in the string
        auto begin = std::sregex_iterator(line.begin(), line.end(), pattern);
        auto end = std::sregex_iterator();

        // Iterate over the matches and print the number and its location
        for (std::sregex_iterator i = begin; i != end; ++i) {
            std::smatch match = *i;
            std::string number = match.str();
            int start_index = match.position();
            int end_index = start_index + match.length();

            std::cout << "Number: " << number << ", Location: " << start_index << "-" << end_index << std::endl;
            engine.pushNumber(Number{ std::make_pair(row, start_index), end_index - start_index, std::stoi(number) });
        }

        for (size_t i = 0; i < line.size(); i++)
        {
            if (is_symbol(line[i]))
                engine.pushSymbol(Symbol{ std::make_pair(row, i), line[i] });
        }
        row++;
    }
    std::uint64_t parts = 0L;
    std::uint64_t gear_ratio = 0l;

    for (const Symbol& symbol : engine.symbols)
    {
        int gear = 0;
        std::vector<int> adj_elements;
        for (const Number& number : engine.numbers)
        {
            //parts += is_adjacent(symbol, number) ? number.data : 0;
            if (is_adjacent(symbol, number))
            {
                std::cout << number.data << " is adj to " << symbol.data << ' ' << parts << '\n';
                parts += number.data;
                adj_elements.push_back(number.data);
            }
        }
        if (adj_elements.size() == 2)
        {
            gear_ratio += adj_elements[0] * adj_elements[1];
            adj_elements.clear();
        }
    }

    std::cout << parts << '\n';
    std::cout << gear_ratio << '\n';

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
