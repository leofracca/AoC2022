#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

int solution(const std::string &input, int substrSize)
{
    bool markerFound = true;
    for (int i = 0; i < input.size() - substrSize + 1; i++)
    {
        std::string sub = input.substr(i, substrSize);
        for (int j = 0; j < substrSize; j++)
        {
            if (std::count(sub.begin(), sub.end(), sub[j]) > 1)
            {
                markerFound = false;
                break;
            }
            else
                markerFound = true;
        }

        if (markerFound)
            return i + substrSize;
    }

    return 0;
}

int main()
{
    std::string input;
    std::getline(std::ifstream("input.txt"), input);

    std::cout << solution(input, 4) << std::endl;
    std::cout << solution(input, 14) << std::endl;

    return 0;
}