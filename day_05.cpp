
// day_05.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>


std::vector<std::uint64_t> get_seeds(const std::string& line, std::vector<std::uint64_t>& seeds)
{
    std::stringstream ss(line);
    std::string to_remove;
    std::uint64_t seed;

    ss >> to_remove;
    while (ss >> seed)
        seeds.push_back(seed);

    return seeds;
}

std::pair<std::uint64_t, std::uint64_t> get_intersection(const std::pair<std::uint64_t, std::uint64_t>& lhi, const std::pair<std::uint64_t, std::uint64_t>& rhi)
{
    if(lhi.second < rhi.first && lhi.first > rhi.second)
        return std::make_pair(-1, -1);
    return std::make_pair(std::max(lhi.first, rhi.first), std::min(lhi.second, rhi.second));
}

std::pair<std::uint64_t, std::uint64_t> get_interval(const std::uint64_t& lhs, const std::uint64_t& width)
{
    return std::make_pair(lhs, lhs + width);
}

std::vector<std::pair<std::uint64_t, std::uint64_t>> get_intervals(const std::vector<std::uint64_t>& seeds, std::vector<std::pair<std::uint64_t, std::uint64_t>>& intervals)
{
    for (size_t i = 0; i < seeds.size(); i+=2)
    {
        intervals.emplace_back(std::minmax(seeds[i], seeds[i + 1]));
    }
    return intervals;
}
int main()
{
    std::ifstream file("input\\day_05.txt");
    if (!file)
    {
        std::cerr << "Unvalid file path" << '\n';
        exit(-1);
    }

    std::string line;
    std::vector<std::uint64_t> seeds;
    std::vector<std::uint64_t> destination;
    std::vector<std::vector<std::uint64_t>> maps;
    std::vector<std::uint64_t> map;

    getline(file, line);
    get_seeds(line, seeds);

    while (getline(file, line))
    {
        if (line == "")
        {
            maps.push_back(map);
            map.clear();
            continue;
        }
        if (line.find("map") != std::string::npos)
            continue;
        std::stringstream ss(line);
        std::uint64_t num;

        while (ss >> num)
        {
            map.push_back(num);
        }
    }
    maps.push_back(map);


    //PART 1

    //for (const auto& map : maps)
    //{
    //    for (std::uint64_t& seed : seeds)

    //    {
    //        for (size_t i = 0; i < map.size(); i+= 3)
    //        {
    //            if (seed >= map[i+1] && seed < map[i+1] + map[i + 2] )
    //            {
    //                seed += map[i] - map[i + 1];
    //                break;
    //            }
    //        }
    //    }

    //    for (size_t i = 0; i < seeds.size(); i++)
    //    {
    //        std::cout << seeds[i] << '\t';
    //    }
    //    std::cout << '\n';
    //}

    //std::cout << *std::min_element(seeds.begin(), seeds.end());

    std::vector<std::pair<std::uint64_t, std::uint64_t>> intervals;
    get_intervals(seeds, intervals);

    for (const auto& map : maps)
    {
        for (auto& interval : intervals)
        {
            for (size_t i = 0; i < map.size(); i+=3)
            {
                auto map_interval = get_interval(map[i], map[i + 2]);
                auto intersection = get_intersection(interval, map_interval);

                if (intersection.first != -1 && intersection.second != -1)
                {
                    interval = std::make_pair(interval.first + map[i] - map[i + 1], interval.second + map[i] - map[i + 1]);
                    break;
                }
            }
        }
    }

    std::sort(intervals.begin(), intervals.end(), [](const auto& lhi, const auto& rhi) {return lhi.first < rhi.first; });

    std::cout << intervals[0].first << '\n';
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
