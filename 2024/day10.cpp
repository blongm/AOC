#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std; 

typedef struct Loc
{
    size_t x;
    size_t y;

} Loc;


struct Trail
{
    Loc Head;
    Loc End;

    bool operator==(Trail T)
    {
        return  T.Head.x == Head.x and 
                T.Head.y == Head.y and 
                T.End.x == End.x and 
                T.End.y == End.y;
    }

};

vector<Loc> Heads;
vector<Trail> Trails;
vector<Trail> AllTrails;

auto find_heads(size_t x, size_t y, vector<string> lines, Loc End)
{
    if (lines.at(y).at(x) == '0')
    {
        Trail Trail = {{x, y}, End};
        
        AllTrails.push_back({{x, y}, End});

        if (find(Trails.begin(), Trails.end(), Trail) == Trails.end())
            Trails.push_back({{x, y}, End});

        return;
    }

    if (x > 0 and lines.at(y).at(x - 1) == lines.at(y).at(x) - 1) 
    {
        find_heads(x - 1, y, lines, End);
    }

    if (y > 0 and lines.at(y - 1).at(x) == lines.at(y).at(x) - 1)
    {
        find_heads(x, y - 1, lines, End);
    }

    if (y < lines.size() - 1 and lines.at(y + 1).at(x) == lines.at(y).at(x) - 1)    
    {
        find_heads(x, y + 1, lines, End);
    }

    if (x < lines.at(y).size() - 1 and lines.at(y).at(x + 1) == lines.at(y).at(x) - 1) 
    {
        find_heads(x + 1, y, lines, End);
    }

}

int main(int argc, char** argv)
{
    if (argc <= 1) return 1;
    ifstream file(argv[1]);

    size_t file_len;
    size_t file_width;

    vector<string> lines;
    string line;

    for (size_t y = 0; getline(file, line); file_len = ++y)
    {
        lines.push_back(line);

        file_width = line.size();

        for (size_t x = 0; x < file_width; x++)
        {
            if (line.at(x) == '0') Heads.push_back({x, y});
        }
    }

    file.close();

    for (size_t y = 0; y < file_len; y++)
    {
        for (size_t x = 0; x < file_width; x++)
        {
            if (lines.at(y).at(x) == '9')
                find_heads(x, y, lines, {x, y});
        }
    }

    cout << "Sum : " << Trails.size() << '\n';   
    cout << "Rating Sum : " << AllTrails.size() << '\n';   


    return 0;
}