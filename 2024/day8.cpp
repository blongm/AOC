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

typedef struct Diff
{
    int origin_x;
    int origin_y;
    int diff_x;
    int diff_y;

} Diff;

int width;
int len;
vector<Ant> Ants;
vector<Node> AntiNodes;
vector<Diff> Diffs;

auto add_anti_node(Ant A, Ant Candidate)
{
    auto x = Candidate.x;
    auto y = Candidate.y;
    auto x_diff = x - A.x;
    auto y_diff = y - A.y;

    Diffs.push_back({A.x, A.y, x_diff, y_diff});

    if (none_of(AntiNodes.begin(), AntiNodes.end(), [A, x_diff, y_diff](Node N) {return N.x == A.x - x_diff and N.y == A.y - y_diff;}))
        AntiNodes.push_back({A.x - x_diff, A.y - y_diff});   

    if (none_of(AntiNodes.begin(), AntiNodes.end(), [A, x_diff, y_diff](Node N) {return N.x == A.x + 2 * x_diff and N.y == A.y + 2 * y_diff;}))
        AntiNodes.push_back({A.x + 2 * x_diff, A.y + 2 * y_diff});  
}

auto proc_cell(Ant Candidate)
{
    if (Candidate.c != '.') 
    {
        cout << "   Antenna Found: " << Candidate.c << '\n';
        for_each(Ants.begin(), Ants.end(), [Candidate](Ant A) {if (Candidate.c == A.c) add_anti_node(A, Candidate);});

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
        cout << "Line: " << y << '\n';
        width = line.size();
        
        for (auto x = 0; x < width; x++)
            proc_cell({x, y, line.at(x)});
    }

    file.close();

    int count = 0;

    for (auto AN : AntiNodes)
        count += AN.x >= 0 and AN.y >= 0 and AN.x < width and AN.y < len;

    cout << '\n' << "Count: " << count << '\n';

    for (auto D : Diffs)
    {
        auto x = D.origin_x;
        auto y = D.origin_y;

        while (x >= 0 and y >= 0 and x < width and y < len)
        {
            if (none_of(AntiNodes.begin(), AntiNodes.end(), [x, y](Node N) {return N.x == x and N.y == y;}))
                AntiNodes.push_back({x, y});   

            x += D.diff_x;
            y += D.diff_y;
        }

        x = D.origin_x;
        y = D.origin_y;

        while (x >= 0 and y >= 0 and x < width and y < len)
        {
            if (none_of(AntiNodes.begin(), AntiNodes.end(), [x, y](Node N) {return N.x == x and N.y == y;}))
                AntiNodes.push_back({x, y});   

            x -= D.diff_x;
            y -= D.diff_y;
        }
    }

    count = 0;

    for (auto AN : AntiNodes)
        count += AN.x >= 0 and AN.y >= 0 and AN.x < width and AN.y < len;

    cout << '\n' << "Count of resonant Anti-Nodes: " << count << '\n';   

    return 0;
}