// day_04.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <numeric>

int main()
{
	std::ifstream file("input\\day_04.txt");
	if (!file)
	{
		std::cerr << "Unvalid file path" << '\n';
		exit(-1);
	}

	std::string line;
	std::vector<std::vector<int>> winning_numbers;
	std::vector<std::vector<int>> actual_numbers;

	while (getline(file, line))
	{
		std::string word;
		int number;
		std::vector<int> card;
		std::vector<int> winning;

		std::stringstream ss(line);

		//Get the first 2 string "Card" and "1:"
		ss >> word >> word;

		for (size_t i = 0; i < 10; i++)
		{
			ss >> number;
			winning.push_back(number);
		}

		ss >> word;

		while (ss >> number)
			card.push_back(number);

		winning_numbers.push_back(winning);
		actual_numbers.push_back(card);
	}

	int score = 0;

	for (size_t i = 0; i < winning_numbers.size(); i++)
	{
		auto it = std::partition(actual_numbers[i].begin(), actual_numbers[i].end(),
			[&](const int& elt) 
			{return std::find(winning_numbers[i].begin(), winning_numbers[i].end(), elt) != winning_numbers[i].end(); });
		if(it != actual_numbers[i].begin())
			score += 1 << it - actual_numbers[i].begin() - 1;
	}

	std::vector<int> scratchcards_winned(actual_numbers.size(), 1);
	int factor = 1;
	std::uint64_t final_score = 0L;
	for (size_t i = 0; i < winning_numbers.size(); i++)
	{
		int copies = std::partition(actual_numbers[i].begin(), actual_numbers[i].end(),
			[&](const int& elt)
			{return std::find(winning_numbers[i].begin(), winning_numbers[i].end(), elt) != winning_numbers[i].end(); }) - actual_numbers[i].begin();
		std::cout << "factor: " << factor << " scratchcards winned: " << copies << '\n';
		for (size_t j = 1; j <= copies; j++)
		{
			scratchcards_winned[i + j] += scratchcards_winned[i];
		}
	}

	std::cout << score << '\n';
	std::cout << std::accumulate(scratchcards_winned.begin(), scratchcards_winned.end(), 0) << '\n';
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
