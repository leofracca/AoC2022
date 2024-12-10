#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <set>

void parseInput(std::ifstream& input, std::vector<std::vector<int>>& map)
{
    std::string line;
    while(std::getline(input, line))
    {
        map.push_back({});

        for (char c : line)
        {
            map[map.size() - 1].push_back(c - '0');
        }
    }
}

void bfs1(const std::vector<std::vector<int>>& map, int i, int j, std::set<std::pair<int, int>>& visited)
{
    if (map[i][j] == 9)
    {
        visited.insert({i, j});
        return;
    }

    if (visited.count({i, j}) == 1)
        return;

    // Right
    if (j + 1 < map[0].size() && map[i][j + 1] == map[i][j] + 1)
        bfs1(map, i, j + 1, visited);
    // Left
    if (j - 1 >= 0 && map[i][j - 1] == map[i][j] + 1)
        bfs1(map, i, j - 1, visited);
    // Down
    if (i + 1 < map.size() && map[i + 1][j] == map[i][j] + 1)
        bfs1(map, i + 1, j, visited);
    // Up
    if (i - 1 >= 0 && map[i - 1][j] == map[i][j] + 1)
        bfs1(map, i - 1, j, visited);
}

void bfs2(const std::vector<std::vector<int>>& map, int i, int j, std::vector<std::pair<int, int>>& visited)
{
    if (map[i][j] == 9)
    {
        visited.push_back({i, j});
        return;
    }

    // Right
    if (j + 1 < map[0].size() && map[i][j + 1] == map[i][j] + 1)
        bfs2(map, i, j + 1, visited);
    // Left
    if (j - 1 >= 0 && map[i][j - 1] == map[i][j] + 1)
        bfs2(map, i, j - 1, visited);
    // Down
    if (i + 1 < map.size() && map[i + 1][j] == map[i][j] + 1)
        bfs2(map, i + 1, j, visited);
    // Up
    if (i - 1 >= 0 && map[i - 1][j] == map[i][j] + 1)
        bfs2(map, i - 1, j, visited);
}

int solution1(const std::vector<std::vector<int>>& map)
{
    int ans = 0;

    std::set<std::pair<int, int>> visited;

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            if (map[i][j] == 0)
            {
                bfs1(map, i, j, visited);
            }
            ans += visited.size();
            visited.clear();
        }
    }

    return ans;
}

int solution2(const std::vector<std::vector<int>>& map)
{
    int ans = 0;

    std::vector<std::pair<int, int>> visited;

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            if (map[i][j] == 0)
            {
                bfs2(map, i, j, visited);
            }
            ans += visited.size();
            visited.clear();
        }
    }

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<std::vector<int>> map;
    parseInput(input, map);

    std::cout << solution1(map) << std::endl;
    std::cout << solution2(map) << std::endl;
}