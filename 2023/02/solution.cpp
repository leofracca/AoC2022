#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>

constexpr int MAX_RED   = 12;
constexpr int MAX_GREEN = 13;
constexpr int MAX_BLUE  = 14;

int main()
{
    std::fstream input("input.txt");
    int solution1 = 0, solution2 = 0;

    std::string line;
    while (std::getline(input, line))
    {
        std::stringstream ss(line);
        std::string word;
        int currentCubes;
        int id = -1;
        bool toCount = true;
        int higherRed = -1, higherGreen = -1, higherBlue = -1;

        while (ss >> word)
        {
            // Get Game ID
            if (id == -1 && std::isdigit(word[0]))
                id = std::stoi(word);
            
            // Get the number of cubes
            else if (std::isdigit(word[0]))
                currentCubes = std::stoi(word);

            // Check
            else
            {
                auto pos = word.find(',');
                if (pos == std::string::npos)
                    pos = word.find(';');

                std::string color = word.substr(0, pos);

                // Part 1
                if (color == "red"   && currentCubes > MAX_RED ||
                    color == "green" && currentCubes > MAX_GREEN ||
                    color == "blue"  && currentCubes > MAX_BLUE)
                {
                    toCount = false;
                    // break;
                }

                // Part 2
                if (color == "red" && currentCubes > higherRed)
                    higherRed = currentCubes;
                else if (color == "green" && currentCubes > higherGreen)
                    higherGreen = currentCubes;
                else if (color == "blue" && currentCubes > higherBlue)
                    higherBlue = currentCubes;
            }
        }

        if (toCount)
            solution1 += id;

        solution2 += (higherRed * higherGreen * higherBlue);
    }

    std::cout << solution1 << std::endl;
    std::cout << solution2 << std::endl;

    return 0;
}