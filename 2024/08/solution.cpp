#include <vector>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <sstream>
#include <string>
#include <unordered_map>
#include <set>

using Coordinates = std::pair<int, int>;

void parseInput(std::ifstream& input, std::vector<std::string>& map)
{
    std::string line;
    while (std::getline(input, line))
        map.push_back(line);
}

void identifyAntennaPositions(const std::vector<std::string>& map, std::unordered_map<char, std::vector<Coordinates>>& antennaPositions)
{
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            char c = map[i][j];
            if (c != '.')
            {
                antennaPositions[c].push_back({i, j});
            }
        }
    }
}

int solution1(const std::unordered_map<char, std::vector<Coordinates>>& antennaPositions, const int mapSize)
{
    int ans = 0;

    std::set<Coordinates> antinodes;

    for (const auto& [k, v] : antennaPositions)
    {
        for (int i = 0; i < v.size() - 1; i++)
        {
            for (int j = i + 1; j < v.size(); j++)
            {
                // First point
                int y = v[i].first * 2 - v[j].first;
                int x = v[i].second * 2 - v[j].second;
                if (y >= 0 && y < mapSize && x >= 0 && x < mapSize && antinodes.count({x, y}) == 0)
                {
                    antinodes.insert({x, y});
                    ans++;
                }

                // Second point
                y = v[j].first * 2 - v[i].first;
                x = v[j].second * 2 - v[i].second;
                if (y >= 0 && y < mapSize && x >= 0 && x < mapSize && antinodes.count({x, y}) == 0)
                {
                    antinodes.insert({x, y});
                    ans++;
                }
            }
        }
    }

    return ans;
}

int solution2(const std::unordered_map<char, std::vector<Coordinates>>& antennaPositions, const int mapSize)
{
    int ans = 0;

    std::set<Coordinates> antinodes;

    for (const auto& [k, v] : antennaPositions)
    {
        for (int i = 0; i < v.size() - 1; i++)
        {
            for (int j = i + 1; j < v.size(); j++)
            {
                // First point
                int y = 0, x = 0;
                int k = 1;
                y = v[i].first + k * (v[j].first - v[i].first);
                x = v[i].second + k * (v[j].second - v[i].second);
                while (y >= 0 && y < mapSize && x >= 0 && x < mapSize)
                {
                    if (antinodes.count({x, y}) == 0)
                    {
                        antinodes.insert({x, y});
                        ans++;
                    }

                    k++;
                    y = v[i].first + k * (v[j].first - v[i].first);
                    x = v[i].second + k * (v[j].second - v[i].second);
                }

                // Second point
                y = 0, x = 0;
                k = 1;
                y = v[j].first + k * (v[i].first - v[j].first);
                x = v[j].second + k * (v[i].second - v[j].second);
                while (y >= 0 && y < mapSize && x >= 0 && x < mapSize)
                {
                    if (antinodes.count({x, y}) == 0)
                    {
                        antinodes.insert({x, y});
                        ans++;
                    }

                    k++;
                    y = v[j].first + k * (v[i].first - v[j].first);
                    x = v[j].second + k * (v[i].second - v[j].second);
                }
            }
        }
    }

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<std::string> map;
    parseInput(input, map);

    std::unordered_map<char, std::vector<Coordinates>> antennaPositions;
    identifyAntennaPositions(map, antennaPositions);

    std::cout << solution1(antennaPositions, map.size()) << std::endl;
    std::cout << solution2(antennaPositions, map.size()) << std::endl;
}