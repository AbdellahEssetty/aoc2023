// day_06.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

std::pair<long long, long long> solve_2nd_deg_eq(const long long& a, const long long& b, const long long& c)
{
    long long delta = b * b - 4 * a * c;
    double d = std::sqrt(std::abs(delta));
    double x1 = (double)(-b - d) / (2 * a);
    double x2 = (double)(-b + d) / (2 * a);
    if (x1 == floor(x1))
        x1 = floor(x1) - 1;
    if (x2 == floor(x2))
        x2 = floor(x2);
    return std::make_pair(long long(x1), long long(x2));
}

int main()
{
    std::ifstream file("D:\\Users\\esset\\source\\repos\\aoc2023\\input\\day_06.txt");
    std::vector<long long> time = { 48938466, };
    std::vector<long long> distance = { 261119210191063, };
    std::vector<long long> score;

    std::transform(time.begin(), time.end(), distance.begin(), std::back_inserter(score), [](const long long& t, const long long& d) {
        std::pair<long long, long long> sol = solve_2nd_deg_eq(-1, t, -d);
    if (sol.first < 0 || sol.second < 0)
        return t - sol.second + 1;
    return std::abs(sol.second - sol.first);
        });

    long long res = 1;
    for (auto i : score)
    {
        std::cout << i << '\t';
        res *= i;
    }

    std::cout << '\n' << res;

    //PART TWO : just changed int to long long
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
