#include <iostream>
#include <fstream>
#include <algorithm>

// Points you will get based on the result
constexpr int LOSE = 0;
constexpr int DRAW = 3;
constexpr int WIN = 6;

// Points every shape gives you when you play it
constexpr int ROCK = 1;
constexpr int PAPER = 2;
constexpr int SCISSORS = 3;

int task1(const std::string &line)
{
    switch (line[0])
    {
    case 'A': // Rock
        switch (line[2])
        {
        case 'X': // Rock
            return DRAW + ROCK;
        case 'Y': // Paper
            return WIN + PAPER;
        case 'Z': // Scissors
            return LOSE + SCISSORS;
        }
    case 'B': // Paper
        switch (line[2])
        {
        case 'X': // Rock
            return LOSE + ROCK;
        case 'Y': // Paper
            return DRAW + PAPER;
        case 'Z': // Scissors
            return WIN + SCISSORS;
        }
    case 'C': // Scissors
        switch (line[2])
        {
        case 'X': // Rock
            return WIN + ROCK;
        case 'Y': // Paper
            return LOSE + PAPER;
        case 'Z': // Scissors
            return DRAW + SCISSORS;
        }
    }

    return 0;
}

int task2(const std::string &line)
{
    switch (line[0])
    {
    case 'A': // Rock
        switch (line[2])
        {
        case 'X': // Lose
            return LOSE + SCISSORS;
        case 'Y': // Draw
            return DRAW + ROCK;
        case 'Z': // Win
            return WIN + PAPER;
        }
    case 'B': // Paper
        switch (line[2])
        {
        case 'X': // Lose
            return LOSE + ROCK;
        case 'Y': // Draw
            return DRAW + PAPER;
        case 'Z': // Win
            return WIN + SCISSORS;
        }
    case 'C': // Scissors
        switch (line[2])
        {
        case 'X': // Lose
            return LOSE + PAPER;
        case 'Y': // Draw
            return DRAW + SCISSORS;
        case 'Z': // Win
            return WIN + ROCK;
        }
    }

    return 0;
}

int main()
{
    std::ifstream input("input.txt");
    int score1 = 0, score2 = 0;

    std::string line;
    while (std::getline(input, line))
    {
        score1 += task1(line);
        score2 += task2(line);
    }

    std::cout << score1 << std::endl;
    std::cout << score2 << std::endl;

    return 0;
}