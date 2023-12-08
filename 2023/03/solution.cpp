#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>

int solution1(const std::vector<std::string>& engine, int rows, int columns)
{
    int result = 0;

    for (int i = 1; i < rows; i++)
    {
        std::string currentNumber = "";
        int currNum;
        int startCol = -1, endCol = -1;

        for (int j = 1; j < columns; j++)
        {
            char symbol = engine[i][j];

            if (std::isdigit(symbol))
            {
                if (startCol == -1)
                    startCol = j;
                currentNumber += symbol;
            }
            else if (!currentNumber.empty())
            {
                currNum = std::stoi(currentNumber);
                if (startCol != -1)
                {
                    endCol = j - 1;
                    currentNumber.clear();
                    bool symbolFound = false;
                    for (int y = -1; y <= 1; y++)
                    {
                        for (int x = startCol - 1; x <= endCol + 1; x++)
                        {
                            if (!std::isdigit(engine[i + y][x]) && engine[i + y][x] != '.')
                            {
                                // std::cout << engine[i + y][x] << std::endl;
                                // std::cout << currNum << "\n";
                                result += currNum;
                                currNum = 0;
                                symbolFound = true;
                                break;
                            }
                        }
                        if (symbolFound)
                            break;
                    }

                    startCol = -1;
                    endCol = -1;
                }
            }
        }
    }

    return result;
}

struct Coordinate
{
    int x;
    int y;

    // == operator
    bool operator==(const Coordinate& other) const
    {
        return (x == other.x && y == other.y);
    }
};

struct CoordinateHash
{
    std::size_t operator()(const Coordinate& c) const
    {
        return std::hash<int>()(c.x) ^ std::hash<int>()(c.y);
    }
};

int solution2(const std::vector<std::string>& engine, int rows, int columns)
{
    unsigned long long result = 0;

    int gearX, gearY;
    std::unordered_map<Coordinate, int, CoordinateHash> gears;
    for (int i = 1; i < rows; i++)
    {
        std::string currentNumber = "";
        int currNum;
        int startCol = -1, endCol = -1;

        for (int j = 1; j < columns; j++)
        {
            char symbol = engine[i][j];

            if (std::isdigit(symbol))
            {
                if (startCol == -1)
                    startCol = j;
                currentNumber += symbol;
            }
            else if (!currentNumber.empty())
            {
                currNum = std::stoi(currentNumber);
                if (startCol != -1)
                {
                    endCol = j - 1;
                    currentNumber.clear();
                    for (int y = -1; y <= 1; y++)
                    {
                        for (int x = startCol - 1; x <= endCol + 1; x++)
                        {
                            if (engine[i + y][x] == '*')
                            {
                                gearX = x;
                                gearY = i + y;
                                if (gears.find(Coordinate{gearX, gearY}) != gears.end())
                                {
                                    result = result + (currNum * gears[Coordinate{gearX, gearY}]);
                                }
                                else
                                {
                                    gearX = x;
                                    gearY = i + y;
                                    gears[Coordinate{gearX, gearY}] = currNum;
                                }
                            }
                        }
                    }

                    startCol = -1;
                    endCol = -1;
                }
            }
        }
    }

    return result;
}

int main()
{
    std::fstream input("input.txt");
    std::vector<std::string> engine;

    // Create the engine (a matrix)
    std::string line;
    int row = 0;
    while (std::getline(input, line))
        engine.push_back('.' + line + '.');

    // Add first and last line of dots
    std::string dummy = "..";
    for (int i = 0; i < line.size(); i++)
        dummy += '.';
    engine.insert(engine.begin(), dummy);
    engine.push_back(dummy);

    // for (auto& v : engine)
    // {
    //     for (char c : v)
    //         std::cout << c;
    //     std::cout << "\n";
    // }

    std::cout << solution1(engine, engine.size(), engine[0].size()) << std::endl;
    std::cout << solution2(engine, engine.size(), engine[0].size()) << std::endl;

    return 0;
}
