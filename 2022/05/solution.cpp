#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

int main()
{
    std::ifstream input("input.txt");
    // Used for task 1
    std::vector<std::string> stacks1;
    // Used for task 2
    std::vector<std::string> stacks2;

    std::string line; // Current line
    std::string rawStacks; // Will contain the first part of the input (i.e. the stacks)
    bool crates = true; // Becomes false when the stacks have been read
    int i = 0; // To select the stacks in which the current crate needs to be added
    int nStacks = 0;
    while(std::getline(input, line))
    {
        rawStacks += line + "\n";

        // Stacks already read
        // Now read the move to do
        if (!crates)
        {
            // Split the string (separator ' ')
            std::vector<std::string> words; // Will contain all the words of this line
            std::string word; // A single word of this line
            std::istringstream stringStream(line);
            while (stringStream >> word)
                words.push_back(word);

            // The words in position 1, 3 and 5 are the numbers needed to solve this problem
            int nCrates = std::stoi(words[1]);
            int stackFrom = std::stoi(words[3]) - 1;
            int stackTo = std::stoi(words[5]) - 1;

            // Get the substring from nCrates to the end (i.e. the crates to move)
            std::string cratesToMove1 = stacks1[stackFrom].substr(stacks1[stackFrom].size() - nCrates);
            std::string cratesToMove2 = stacks2[stackFrom].substr(stacks2[stackFrom].size() - nCrates);
            
            // Remove the crates from the correct stack (task 2)
            stacks2[stackFrom].erase(stacks2[stackFrom].size() - cratesToMove2.size());
            // Add the crates to the correct stack (task 2)
            stacks2[stackTo] += cratesToMove2;

            // Then reverse it (task 1)
            std::reverse(cratesToMove1.begin(), cratesToMove1.end());
            // Remove the crates from the correct stack (task 1)
            stacks1[stackFrom].erase(stacks1[stackFrom].size() - cratesToMove1.size());
            // Add the crates to the correct stack (task 1)
            stacks1[stackTo] += cratesToMove1;
        }

        // Read the initial stacks configuration
        if (line.empty())
        {
            rawStacks.erase(rawStacks.size() - 2); // Newlines at the end
            nStacks = (rawStacks[rawStacks.size() - 2] - 48); // Get the last number (i.e. the total number of stacks)
            stacks1.resize(nStacks);
            
            std::istringstream stringStream(rawStacks);
            while (std::getline(stringStream, line))
            {
                // Loop through the current line
                for (int j = 0; j < line.size(); j++)
                {
                    if (1 + 4 * j > line.size())
                        break;

                    // Get the crateIdentifier (a letter) (this formula works because of the format of the input)
                    std::string crateIdentifier(1, line[1 + 4 * j]);
                    // Check that there is a crate (a letter, not a space)
                    if (crateIdentifier != " ")
                        // Insert the crate in the correct stack
                        stacks1[i].insert(0, crateIdentifier);
                    // Go to the next stack
                    if (i + 1 < nStacks)
                        i++;
                    else
                        i = 0;
                }
            }

            // Remove the first character (the stack number)
            for (int i = 0; i < stacks1.size(); i++)
                stacks1[i] = stacks1[i].substr(1);
            stacks2 = stacks1;
            crates = false; // Crates read
        }
    }

    for (std::string s : stacks1)
        std::cout << s[s.size() - 1];
    std::cout << '\n';

    for (std::string s : stacks2)
        std::cout << s[s.size() - 1];
    std::cout << '\n';

    return 0;
}