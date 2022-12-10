#include <iostream>
#include <fstream>
#include <sstream>

void sumSignalStrength(int &signalStrength, int xRegister, int elapsedCycles)
{
    if (elapsedCycles == 20 ||
        elapsedCycles == 60 ||
        elapsedCycles == 100 ||
        elapsedCycles == 140 ||
        elapsedCycles == 180 ||
        elapsedCycles == 220)
        signalStrength = signalStrength + (xRegister * elapsedCycles);
}

void draw(int spritePosition, std::string &line)
{
    if (line.size() == spritePosition - 1 ||
        line.size() == spritePosition ||
        line.size() == spritePosition + 1)
        line += "#";
    else
        line += ".";
}

void drawNewLine(int elapsedCycles, std::string &image, std::string &line)
{
    image += line + "\n";
    line = "";
}

int main()
{
    std::ifstream input("input.txt");
    int elapsedCycles = 1;
    int signalStrength = 0;
    int xRegister = 1;
    constexpr int NOOP_CYCLES = 1, ADDX_CYCLES = 2;
    std::string image = "";

    std::string line;
    std::string lineToDraw = "";
    while (std::getline(input, line))
    {
        std::string instruction = line.substr(0, line.find(' '));
        if (instruction == "noop")
        {
            draw(xRegister, lineToDraw);
            elapsedCycles += NOOP_CYCLES;
        }
        else
        {
            draw(xRegister, lineToDraw);
            if ((elapsedCycles) % 40 == 0)
                drawNewLine(elapsedCycles, image, lineToDraw);
            draw(xRegister, lineToDraw);
            elapsedCycles += ADDX_CYCLES;
            sumSignalStrength(signalStrength, xRegister, elapsedCycles - 1);
            xRegister += std::stoi(line.substr(line.find(' ')));
        }

        sumSignalStrength(signalStrength, xRegister, elapsedCycles);
        if ((elapsedCycles - 1) % 40 == 0)
            drawNewLine(elapsedCycles, image, lineToDraw);
    }

    std::cout << signalStrength << std::endl;
    std::cout << image;

    return 0;
}