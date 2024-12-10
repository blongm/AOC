#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std; 

typedef struct Node
{
    int x;
    int y;

} Node;

typedef struct Ant : Node
{
    char c;

} Ant;


int main(int argc, char** argv)
{
    if (argc <= 1) return 1;
    ifstream file(argv[1]);

    string line;

    vector<Ant> Ants;
    vector<Node> AntiNodes;

    for (auto y = 0; getline(file, line); y++)
    {
        for (auto x = 0; x < line.size(); x++)
        {
            if (line.at(x) != '.')
            {
                auto c = line.at(x);

                for (auto A : Ants)
                {
                    if (c == A.c)
                    {
                        if (find_if(AntiNodes.begin(), AntiNodes.end(), [x, y](Node N){return N.x != x and N.y != y;}))
                        {
                            auto x_diff = x - A.x;
                            auto y_diff = y - A.y;
                            AntiNodes.push_back({A.x - x_diff, A.y - y_diff});
                            AntiNodes.push_back({x + x_diff, y + y_diff});
                        }

                        Ants.push_back({x, y, c});
                    }
                }
            }
        }
    }
    //  for every cell
    //      if attena
    //          if other other type of attena has been visited
    //              calc difference 
    //              calc antinodes if not out of range and not already exists
    //          add antenna to visited
    //  get number of antinodes

    file.close();

    cout << "Hello, World!\n";

    return 0;
}