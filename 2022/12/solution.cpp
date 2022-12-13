#include <iostream>
#include <fstream>
#include <vector>

using Coordinates = std::pair<int, int>;

struct Node
{
    char height;
    long dist;
    Coordinates coordinates;
    bool visited;
};

long BFS(std::vector<std::vector<Node>> grid, Coordinates start, Coordinates end, bool reverse = false)
{
    if (!reverse)
    {
        grid[start.first][start.second].height = 'a';
        grid[end.first][end.second].height = 'z';
    }
    else
    {
        grid[end.first][end.second].height = 'a';
        grid[start.first][start.second].height = 'z';
    }

    // Mark the start node as visited
    grid[start.first][start.second].dist = 0;
    grid[start.first][start.second].visited = true;

    std::vector<Coordinates> queue;
    queue.push_back(start);

    while (!queue.empty())
    {
        Coordinates current = queue.front();
        queue.erase(queue.begin());

        if (current == end || (reverse && grid[current.first][current.second].height == 'a'))
            return grid[current.first][current.second].dist;

        // Check all 4 directions
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                // Don't check the current node
                if (i == 0 && j == 0)
                    continue;
                
                // Diagonal movement is not allowed
                if (i != 0 && j != 0)
                    continue;

                int x = current.first + i,
                    y = current.second + j;

                // Check if the node is out of bounds
                if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size())
                    continue;

                // Check if the node has already been visited
                if (grid[x][y].visited)
                    continue;

                if (!reverse)
                {
                    if (grid[x][y].height - grid[current.first][current.second].height > 1)
                        continue;
                }
                else
                {
                    if (grid[current.first][current.second].height - grid[x][y].height > 1)
                        continue;
                }

                // Visit the node
                grid[x][y].visited = true;
                grid[x][y].dist = grid[current.first][current.second].dist + 1;
                queue.push_back({x, y});
            }
        }
    }

    return -1;
}

int main()
{
    std::ifstream input("input.txt");
    std::vector<std::vector<Node>> grid;
    Coordinates start, end;

    std::string line;
    int i = 0;
    while(std::getline(input, line))
    {
        int possibleYStart = line.find('S'),
            possibleXStart,
            possibleYEnd = line.find('E'),
            possibleXEnd;
        if (possibleYStart != std::string::npos)
            start = {i, possibleYStart};
        if (possibleYEnd != std::string::npos)
            end = {i, possibleYEnd};

        grid.push_back({});

        for (char c : line)
        {
            int pos = 0;
            Node n;
            n.height = c;
            n.coordinates = {i, pos++};
            n.dist = INTMAX_MAX;
            n.visited = false;
            grid[i].push_back(n);
        }
        i++;
    }

    std::cout << BFS(grid, start, end) << "\n";
    std::cout << BFS(grid, end, start, true) << "\n";
}