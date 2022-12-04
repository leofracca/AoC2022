#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

int main()
{
    std::ifstream input("input.txt");
    std::vector<std::string> lines = std::vector<std::string>(std::istream_iterator<std::string>(input), {});

    int count1 = 0;
    int count2 = 0;
    for (auto line : lines)
    {
        // Split the line in two (the separator is ',')
        auto separator = line.find(',');
        std::string first = line.substr(0, separator);
        std::string second = line.substr(separator + 1);

        // Split each part in two (the separator is '-')
        separator = first.find('-');
        int firstStart = std::stoi(first.substr(0, separator));
        int firstEnd = std::stoi(first.substr(separator + 1));

        separator = second.find('-');
        int secondStart = std::stoi(second.substr(0, separator));
        int secondEnd = std::stoi(second.substr(separator + 1));
        
        // Check if a range is completely inside the other (task 1)
        if ((firstStart <= secondStart && secondEnd <= firstEnd) ||
            (secondStart <= firstStart && firstEnd<= secondEnd))
            count1++;

        // Check if the ranges overlap in some way (task 2)
        if (firstEnd >= secondStart && secondEnd >= firstStart)
            count2++;
    }

    std::cout << count1 << std::endl;
    std::cout << count2 << std::endl;

    return 0;
}