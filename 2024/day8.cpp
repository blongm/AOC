#include <iostream>
#include <fstream>
#include <vector>
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

int width;
int len;
vector<Ant> Ants;
vector<Node> AntiNodes;

auto add_anti_node(Ant A, int x, int y)
{
    if (none_of(AntiNodes.begin(), AntiNodes.end(), [A, x, y](Node N){return N.x == x and N.y == y;}))
        AntiNodes.push_back({x, y});    
}

auto chk_anti_node(Ant A, Ant Candidate)
{
    auto x = Candidate.x;
    auto y = Candidate.y;
    auto x_diff = x - A.x;
    auto y_diff = y - A.y;

    if (none_of(AntiNodes.begin(), AntiNodes.end(), [x, y](Node N){return N.x == x and N.y == y;}))
    {
        add_anti_node(A, A.x - x_diff, A.y - y_diff);
        add_anti_node(A, A.x + 2 * x_diff, A.y + 2 * y_diff);
    }
}

auto proc_cell(Ant Candidate)
{
    if (Candidate.c != '.') 
    {
        for_each(Ants.begin(), Ants.end(), [Candidate](Ant A) {if (Candidate.c == A.c) chk_anti_node(A, Candidate);});

        Ants.push_back(Candidate);
    }
}

int main(int argc, char** argv)
{
    if (argc <= 1) return 1;
    ifstream file(argv[1]);

    string line;

    for (auto y = 0; getline(file, line); len = ++y)
    {
        width = line.size();
        
        for (auto x = 0; x < width; x++)
            proc_cell({x, y, line.at(x)});
    }

    file.close();

    int count = 0;

    for (auto AN : AntiNodes)
        count += AN.x >= 0 and AN.y >= 0 and AN.x < width and AN.y < len;
    
    // 370 too low
    cout << count << '\n';

    return 0;
}