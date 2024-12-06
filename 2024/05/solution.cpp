#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <regex>
#include <sstream>

void parseInput(std::ifstream& input, std::set<std::pair<int, int>>& rules, std::vector<std::vector<int>>& udpates)
{
    bool parseRules = true;
    std::string line;
    while (std::getline(input, line))
    {
        if (parseRules)
        {
            const std::regex patternRules{R"((\d+)\|(\d+))"};
            std::smatch matches;

            parseRules = false;
            auto searchStart = line.cbegin();
            while (std::regex_search(searchStart, line.cend(), matches, patternRules))
            {
                parseRules = true;
                rules.insert({stoi(matches[1]), stoi(matches[2])});
                // std::cout << matches[1] << matches[2] << std::endl;
                searchStart = matches.suffix().first;
            }
        }
        else
        {
            std::stringstream ss(line);
            int n;

            udpates.push_back({});
            while (ss >> n)
            {
                udpates[udpates.size() - 1].push_back(n);
                if (ss.peek() == ',')
                    ss.ignore();
            }
        }
    }
}

int solution1(std::set<std::pair<int, int>>& rules, std::vector<std::vector<int>>& udpates)
{
    int ans = 0;

    for (const auto& update : udpates)
    {
        bool valid = true;
        for (int i = 0; i < update.size() - 1; i++)
        {
            for (int j = i + 1; j < update.size(); j++)
            {
                if (rules.count(std::make_pair(update[j], update[i])))
                {
                    valid = false;
                    break;
                }
            }
        }
        if (valid)
            ans += update[update.size() / 2];
    }

    return ans;
}

int solution2(std::set<std::pair<int, int>>& rules, std::vector<std::vector<int>>& udpates)
{
    int ans = 0;

    for (auto& update : udpates)
    {
        bool valid = true;
        for (int i = 0; i < update.size() - 1; i++)
        {
            for (int j = i + 1; j < update.size(); j++)
            {
                if (rules.count(std::make_pair(update[j], update[i])))
                {
                    valid = false;
                    std::swap(update[i], update[j]);
                }
            }
        }
        if (!valid)
            ans += update[update.size() / 2];
    }

    return ans;
}

int main()
{
    std::ifstream input("input.txt");
    std::set<std::pair<int, int>> rules;
    std::vector<std::vector<int>> updates;
    parseInput(input, rules, updates);

    std::cout << solution1(rules, updates) << std::endl;
    std::cout << solution2(rules, updates) << std::endl;
}