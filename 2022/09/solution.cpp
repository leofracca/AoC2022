#include <iostream>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <sstream>

struct Knot
{
    int x, y;

    bool operator==(const Knot &obj) const
    {
        return x == obj.x && y == obj.y;
    }

    struct HashFunction
    {
        size_t operator()(const Knot& knot) const
        {
            return knot.x ^ knot.y;
        }
    };
};

void moveHead(char direction, Knot &head)
{
    switch (direction)
    {
    case 'U': head.y += 1; break;
    case 'D': head.y -= 1; break;
    case 'R': head.x += 1;  break;
    case 'L': head.x -= 1;  break;
    }
}

void moveTail(Knot &head, Knot &tail)
{
    if (std::abs(head.x - tail.x) > 1 && std::abs(head.y - tail.y) > 1)
    {
        tail.x += (tail.x < head.x) ? 1 : -1;
        tail.y += (tail.y < head.y) ? 1 : -1;
    }
    else if (std::abs(head.x - tail.x) > 1)
    {
        tail.x += (head.x > tail.x) ? 1 : -1;
        tail.y = head.y;
    }
    else if (std::abs(head.y - tail.y) > 1)
    {
        tail.x = head.x;
        tail.y += (head.y > tail.y) ? 1 : -1;
    }
}

int task1(std::vector<std::string> &input, int numberOfKnots)
{
    std::vector<Knot> knots(numberOfKnots + 1); // + 1 because there is also the head
    std::unordered_set<Knot, Knot::HashFunction> visited{{0, 0}};

    for (auto move : input)
    {
        char direction = move[0];
        int steps = std::stoi(move.substr(move.find(' ')));
        for (int i = 0; i < steps; i++)
        {
            moveHead(direction, knots[0]);
            for (int j = 1; j < knots.size(); j++)
                moveTail(knots[j - 1], knots[j]);
            visited.insert(knots[knots.size() - 1]);
        }
    }

    return visited.size();
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<std::string> inputSteps;

    std::string line;
    while (std::getline(input, line))
        inputSteps.push_back(line);

    std::cout << task1(inputSteps, 1) << std::endl;
    std::cout << task1(inputSteps, 9) << std::endl;

    return 0;
}