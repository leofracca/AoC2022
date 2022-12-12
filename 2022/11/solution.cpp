#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

struct Operation
{
    std::string m_operator;
    int m_operand;
};

struct Monkey
{
    std::vector<long> m_items{};
    Operation m_operation;
    int m_test;
    int m_newMonkeyIfTestTrue;
    int m_newMonkeyIfTestFalse;
    long m_inspectedItems = 0;
};

void parseInput(std::ifstream &input, std::vector<Monkey> &monkeys, int &LCM)
{
    std::string line;
    int monkeyCounter = -1;
    while (std::getline(input, line))
    {
        std::stringstream buffer(line);
        std::string tmp;
        std::vector<std::string> currentLine;

        while (buffer >> tmp)
            currentLine.push_back(tmp);

        if (currentLine.empty())
            continue;

        if (currentLine[0] == "Monkey")
        {
            monkeys.push_back({});
            monkeyCounter++;
        }
        else if (currentLine[0] == "Starting")
        {
            for (int i = 2; i < currentLine.size(); i++)
            {
                int item = std::stoi(currentLine[i].substr(0, currentLine[i].find(',')));
                monkeys[monkeyCounter].m_items.push_back(item);
            }
        }
        else if (currentLine[0] == "Operation:")
        {
            Operation op;
            op.m_operator = currentLine[4];
            if (currentLine[5] != "old")
                op.m_operand = std::stoi(currentLine[5]);
            else
                op.m_operand = -1;
            monkeys[monkeyCounter].m_operation = op;
        }
        else if (currentLine[0] == "Test:")
        {
            monkeys[monkeyCounter].m_test = std::stoi(currentLine[3]);
            LCM *= monkeys[monkeyCounter].m_test; // <- For part 2
        }
        else if (currentLine[1] == "true:")
            monkeys[monkeyCounter].m_newMonkeyIfTestTrue = std::stoi(currentLine[5]);
        else if (currentLine[1] == "false:")
            monkeys[monkeyCounter].m_newMonkeyIfTestFalse = std::stoi(currentLine[5]);
    }
}

long solution(std::vector<Monkey> monkeys, int rounds, int divisor = 3, int LCM = 0)
{
    for (int j = 0; j < rounds; j++)
    {
        for (int m = 0; m < monkeys.size(); m++)
        {
            for (int i = 0; i < monkeys[m].m_items.size(); i++)
            {
                monkeys[m].m_inspectedItems++;
                long worryLevel = 0;
                if (monkeys[m].m_operation.m_operator == "*")
                {
                    if (monkeys[m].m_operation.m_operand != -1)
                        worryLevel = monkeys[m].m_items[i] * monkeys[m].m_operation.m_operand;
                    else
                        worryLevel = monkeys[m].m_items[i] * monkeys[m].m_items[i];
                }
                else
                {
                    if (monkeys[m].m_operation.m_operand != -1)
                        worryLevel = monkeys[m].m_items[i] + monkeys[m].m_operation.m_operand;
                    else
                        worryLevel = monkeys[m].m_items[i] + monkeys[m].m_items[i];
                }

                if (LCM == 0)
                    worryLevel /= divisor;
                else
                    worryLevel %= LCM;

                if (worryLevel % monkeys[m].m_test == 0)
                    monkeys[monkeys[m].m_newMonkeyIfTestTrue].m_items.push_back(worryLevel);
                else
                    monkeys[monkeys[m].m_newMonkeyIfTestFalse].m_items.push_back(worryLevel);
            }
            monkeys[m].m_items.clear();
        }
    }

    std::sort(monkeys.begin(), monkeys.end(), [&](Monkey a, Monkey b){ return a.m_inspectedItems > b.m_inspectedItems; });
    
    return monkeys[0].m_inspectedItems * monkeys[1].m_inspectedItems;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<Monkey> monkeys;
    int LCM = 1;

    parseInput(input, monkeys, LCM);

    std::cout << solution(monkeys, 20, 3) << std::endl;
    std::cout << solution(monkeys, 10000, 0, LCM) << std::endl;

    return 0;
}