#include <vector>
#include <fstream>
#include <iostream>

constexpr int SIZE = 130 + 2; // Actual size + borders

std::pair<int, int> parseInput(std::ifstream& input, char map[SIZE][SIZE])
{
    std::pair<int, int> guardPosition;
    std::string line;
    int i = 1;
    while (std::getline(input, line))
    {
        int j = 1;
        for (char c : line)
        {
            map[i][j] = c;

            if (c == '^')
                guardPosition = {i, j};
            j++;
        }
        i++;
    }

    // Padding
    for (int i = 0; i < SIZE; i++)
    {
        map[i][0] = '0';
        map[i][SIZE - 1] = '0';
    }
    for (int i = 0; i < SIZE; i++)
    {
        map[0][i] = '0';
        map[SIZE - 1][i] = '0';
    }

    return guardPosition;
}

int solution1(char map[SIZE][SIZE], std::pair<int, int>& guardPosition)
{
    int ans = 0;
    int y = guardPosition.first, x = guardPosition.second;
    char guardDirection = map[y][x];
    char cell = map[y][x];

    while (cell != '0')
    {
        switch (guardDirection)
        {
        case '^':
            if (map[y - 1][x] != '#')
            {
                map[y][x] = 'X';
                y--;
            }
            else
                guardDirection = '>';
            break;
        case '>':
            if (map[y][x + 1] != '#')
            {
                map[y][x] = 'X';
                x++;
            }
            else
                guardDirection = 'v';
            break;
        case 'v':
            if (map[y + 1][x] != '#')
            {
                map[y][x] = 'X';
                y++;
            }
            else
                guardDirection = '<';
            break;
        case '<':
            if (map[y][x - 1] != '#')
            {
                map[y][x] = 'X';
                x--;
            }
            else
                guardDirection = '^';
            break;
        default:
            break;
        }

        cell = map[y][x];
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            if (map[i][j] == 'X')
                ans++;
    }

    return ans;
}

int solution2(char map[SIZE][SIZE], std::pair<int, int>& guardPosition)
{
    int ans = 0;

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    char map[SIZE][SIZE];
    std::pair<int, int> guardPosition = parseInput(input, map);

    std::cout << solution1(map, guardPosition) << std::endl;
    std::cout << solution2(map, guardPosition) << std::endl;
}