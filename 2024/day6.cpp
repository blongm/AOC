#include <iostream>
#include <fstream>
#include <vector>

using namespace std; 

int main(int argc, char** argv)
{
    if (argc <= 1) return 1;
    ifstream file(argv[1]);

    vector<string> map;

    string line;
    size_t y = 0; size_t x = 0;

    for (auto i = 0; getline(file, line); i++)
    {
        map.push_back(line);

        if (line.find('^') != string::npos)
        {
            x = line.find('^');
            y = i;
            map.at(i).at(x) = 'X';
        }
    }

    enum dir {UP, DOWN, LEFT, RIGHT};
    auto g_dir = UP; 
    auto end = false;

    while (not end)
    {
        map.at(y).at(x) = 'X';
        switch (g_dir)
        {
        case UP:
            if (y == 0) end = true;
            else if (map.at(y-1).at(x) == '#') g_dir = RIGHT;
            else y--;
            break;

        case DOWN:
            if (y == map.size() - 1) end = true;
            else if (map.at(y+1).at(x) == '#') g_dir = LEFT;
            else y++;
            break;

        case LEFT:
            if (y == 0) end = true;
            else if (map.at(y).at(x-1) == '#') g_dir = UP;
            else x--;
            break;

        case RIGHT:
            if (x == map.at(y).size() - 1) end = true;
            else if (map.at(y).at(x+1) == '#') g_dir = DOWN;
            else x++;
        }
    }

    int cnt = 0;
    
    for(auto y : map)
    {
        for(auto x : y)
        {
            cnt += x == 'X';
        }
    }

    file.close();

    cout << "Count of positions: " << cnt << '\n';

    return 0;
}