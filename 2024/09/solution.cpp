#include <vector>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <sstream>
#include <string>
#include <map>
#include <set>

void parseInput(std::ifstream& input, std::vector<int>& fileSystem)
{
    std::string line;
    input >> line;

    int fileId = 0;
    for (int i = 0; i < line.size(); i++)
    {
        int j = 0;
        while (j++ < line[i] - '0')
        {
            if (i % 2 == 0)
                fileSystem.push_back(fileId);
            else
                fileSystem.push_back(-1);
        }

        if (i % 2 == 0)
            fileId++;
    }
}

uint64_t solution1(std::vector<int>& fileSystem)
{
    uint64_t ans = 0;

    // Find the position of the first free block
    int freeBlock;
    for (int i = 0; i < fileSystem.size(); i++)
    {
        if (fileSystem[i] == -1)
        {
            freeBlock = i;
            break;
        }
    }
    
    for (int i = fileSystem.size() - 1; i >= 0; i--)
    {
        if (fileSystem[i] != -1)
        {
            fileSystem[freeBlock] = fileSystem[i];
            fileSystem[i] = -1;

            // Find next free block
            while (fileSystem[freeBlock] != -1 && freeBlock < fileSystem.size())
                freeBlock++;

            if (freeBlock + 1 > i) break;
        }
    }

    // Calculate result
    for (int i = 0; i < freeBlock; i++)
    {
        ans += (i * fileSystem[i]);
    }

    return ans;
}

uint64_t solution2(std::vector<int>& fileSystem)
{
    uint64_t ans = 0;
    std::set<int> alreadyMoved;

    // Find the position of all free blocks
    std::map<int, int> freeBlocks; // Base index, space
    for (int i = 0; i < fileSystem.size(); i++)
    {
        int baseIndex = -1, freeSpace = 0;
        while (fileSystem[i++] == -1)
        {
            if (baseIndex == -1)
                baseIndex = i - 1;
            freeSpace++;
        }
        i--;

        if (baseIndex != -1)
            freeBlocks[baseIndex] = freeSpace;
    }
    
    for (int i = fileSystem.size() - 1; i >= 0; i--)
    {
        if (fileSystem[i] != -1)
        {
            int spaceNeeded = 0;
            int fileId = fileSystem[i];
            while (fileSystem[i] == fileId)
            {
                spaceNeeded++;
                i--;
            }
            i++;
            if (fileId == 0)
                spaceNeeded--;

            if (alreadyMoved.count(fileId) == 0)
            {
                for (std::map<int, int>::iterator it = freeBlocks.begin(); it != freeBlocks.end(); it++)
                {
                    if (it->second >= spaceNeeded)
                    {
                        if (i <= it->first)
                            break;
                        alreadyMoved.insert(fileId);

                        int s = 0;
                        int newSpace = it->second - spaceNeeded;
                        for (s = 0; s < spaceNeeded; s++)
                        {
                            fileSystem[it->first + s] = fileId;
                            fileSystem[i + s] = -1;
                        }
                        freeBlocks[it->first + s] = newSpace;
                        freeBlocks.erase(it->first);
                        break;
                    }
                }
            }
        }
    }

    // Calculate result
    for (int i = 0; i < fileSystem.size(); i++)
    {
        if (fileSystem[i] != -1)
            ans += (i * fileSystem[i]);
    }

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<int> fileSystem, copy;
    parseInput(input, fileSystem);
    copy = fileSystem;

    std::cout << solution1(fileSystem) << std::endl;
    fileSystem = copy;
    std::cout << solution2(fileSystem) << std::endl;
}