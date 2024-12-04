#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>

constexpr int SIZE = 140 + 2; // Actual size + borders

void parseInput(std::ifstream& input, char words[SIZE][SIZE])
{
    std::string line;
    int i = 1;
    while (std::getline(input, line))
    {
        int j = 1;
        for (char c : line)
            words[i][j++] = c;
        i++;
    }

    // Fill the borders with 0s
    for (int i = 0; i < SIZE; i++)
    {
        words[i][0] = '0';
        words[i][SIZE - 1] = '0';
    }
    for (int i = 0; i < SIZE; i++)
    {
        words[0][i] = '0';
        words[SIZE - 1][i] = '0';
    }
}

int solution1(const char words[SIZE][SIZE])
{
    int ans = 0;
    
    for (int i = 1; i < SIZE; i++)
    {
        for (int j = 1; j < SIZE; j++)
        {
            if (words[i][j] == 'X')
            {
                // Right
                if (j + 3 < SIZE && words[i][j + 1] == 'M' && words[i][j + 2] == 'A' && words[i][j + 3] == 'S')
                    ans++;
                // Left
                if (j - 3 > 0 && words[i][j - 1] == 'M' && words[i][j - 2] == 'A' && words[i][j - 3] == 'S')
                    ans++;
                // Up
                if (i + 3 < SIZE && words[i + 1][j] == 'M' && words[i + 2][j] == 'A' && words[i + 3][j] == 'S')
                    ans++;
                // Down
                if (i - 3 > 0 && words[i - 1][j] == 'M' && words[i - 2][j] == 'A' && words[i - 3][j] == 'S')
                    ans++;
                // Right - Up
                if (j + 3 < SIZE && i - 3 > 0 && words[i - 1][j + 1] == 'M' && words[i - 2][j + 2] == 'A' && words[i - 3][j + 3] == 'S')
                    ans++;
                // Right - Down
                if (j + 3 < SIZE && i + 3 < SIZE && words[i + 1][j + 1] == 'M' && words[i + 2][j + 2] == 'A' && words[i + 3][j + 3] == 'S')
                    ans++;
                // Left - Up
                if (j - 3 > 0 && i - 3 > 0 && words[i - 1][j - 1] == 'M' && words[i - 2][j - 2] == 'A' && words[i - 3][j - 3] == 'S')
                    ans++;
                // Left - Down
                if (j - 3 > 0 && i + 3 < SIZE && words[i + 1][j - 1] == 'M' && words[i + 2][j - 2] == 'A' && words[i + 3][j - 3] == 'S')
                    ans++;
            }
        }
    }

    return ans;
}

int solution2(const char words[SIZE][SIZE])
{
    int ans = 0;

    for (int i = 1; i < SIZE - 1; i++)
    {
        for (int j = 1; j < SIZE - 1; j++)
        {
            if (words[i][j] == 'A')
            {
                if ((words[i - 1][j + 1] == 'M' && words[i + 1][j - 1] == 'S') &&
                    ((words[i - 1][j - 1] == 'M' && words[i + 1][j + 1] == 'S') ||
                    (words[i - 1][j - 1] == 'S' && words[i + 1][j + 1] == 'M')))
                    ans++;
                if ((words[i - 1][j + 1] == 'S' && words[i + 1][j - 1] == 'M') &&
                    ((words[i - 1][j - 1] == 'M' && words[i + 1][j + 1] == 'S') ||
                    (words[i - 1][j - 1] == 'S' && words[i + 1][j + 1] == 'M')))
                    ans++;
            }
        }
    }

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    char words[SIZE][SIZE];
    parseInput(input, words);

    std::cout << solution1(words) << std::endl;
    std::cout << solution2(words) << std::endl;
}