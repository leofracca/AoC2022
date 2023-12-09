#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <numeric>

int solution1()
{
    int result = 0;

    return result;
}

int main()
{
    std::fstream input("input.txt");
    std::vector<int> winningNumbers, myNumbers;

    int result1 = 0;
    std::vector<int> copies{0, 1, 1};
    int startingNumber = 1;

    std::string line;
    while (std::getline(input, line))
    {
        std::stringstream ss(line);
        std::string token;

        // Insert winning numbers until '|' is found
        while (ss >> token)
        {
            if (token[token.size() - 1] == ':')
            {
                int current = std::stoi(token.substr(0, token.size()));
                if (current >= copies.size())
                    copies.push_back(1);
            }
            // std::cout << token << std::endl;
            if (token == "Card" || token[token.size() - 1] == ':')
                continue;
            
            if (token == "|")
                break;
            else
                winningNumbers.push_back(std::stoi(token));
        }

        // Insert my numbers
        while (ss >> token)
        {   
            myNumbers.push_back(std::stoi(token));
        }

        // Check if I won
        int matches = 0;
        int nCopies = 0;
        for (auto& i : myNumbers)
        {
            for (auto& j : winningNumbers)
            {
                if (i == j)
                {
                    if (matches == 0)
                        matches++;
                    else
                        matches *= 2;

                    nCopies++;
                }
            }
        }
        // std::cout << nCopies << std::endl;
        // std::cout << matches << std::endl;

        result1 += matches;
        winningNumbers.clear();
        myNumbers.clear();

        for (int j = 0; j < copies[startingNumber]; j++)
        {
            for (int i = startingNumber + 1; i < startingNumber + 1 + nCopies; i++)
            {
                if (i >= copies.size())
                    copies.push_back(1);
                copies[i]++;
            }
        }
        startingNumber++;
    }

    std::cout << result1 << std::endl;
    std::cout << std::accumulate(copies.begin(), copies.end(), 0) << std::endl;

    return 0;
}
