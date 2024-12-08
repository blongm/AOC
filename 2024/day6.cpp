#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std; 

vector<string> map;
size_t orig_y; 
size_t orig_x;
enum dir {UP, DOWN, LEFT, RIGHT};


typedef struct vis_loc
{
    size_t x;
    size_t y;
    dir dir;
    bool operator==(vis_loc rhs) 
    {
        return x == rhs.x and y == rhs.y and dir == rhs.dir;
    }
    
} vis_loc;


auto chg_dir(bool* end, dir* g_dir, size_t* x, size_t* y)
{
    switch (*g_dir)
    {
        case UP:
            if (*y == 0) *end = true;
            else if (map.at(*y-1).at(*x) == '#') *g_dir = RIGHT;
            else (*y)--;
            break;

        case DOWN:
            if (*y == map.size() - 1) *end = true;
            else if (map.at(*y+1).at(*x) == '#') *g_dir = LEFT;
            else (*y)++;
            break;

        case LEFT:
            if (*y == 0) *end = true;
            else if (map.at(*y).at(*x-1) == '#') *g_dir = UP;
            else (*x)--;
            break;

        case RIGHT:
            if (*x == map.at(*y).size() - 1) *end = true;
            else if (map.at(*y).at(*x+1) == '#') *g_dir = DOWN;
            else (*x)++;
    }   
}

auto loop(int ob_x, int ob_y)
{
    map.at(ob_y).at(ob_x) = '#';
    auto g_dir = UP; 
    auto end = false;
    auto x = orig_x; auto y = orig_y;

    vector<vis_loc> vis_locs;

    while (not end)
    {
        vis_loc last_vis_loc = {x, y, g_dir};
        if (find(vis_locs.begin(), vis_locs.end(), last_vis_loc) != vis_locs.end()) return true;

        vis_locs.push_back({x, y, g_dir});
        
        chg_dir(&end, &g_dir, &x, &y);
    }

    return false;
}

int main(int argc, char** argv)
{
    if (argc <= 1) return 1;
    ifstream file(argv[1]);

    string line;

    for (auto i = 0; getline(file, line); i++)
    {
        map.push_back(line);

        if (line.find('^') != string::npos)
        {
            orig_x = line.find('^');
            orig_y = i;
            map.at(i).at(orig_x) = 'X';
        }
    }

    auto end = false;
    auto x = orig_x; auto y = orig_y;
    auto g_dir = UP; 

    while (not end)
    {
        map.at(y).at(x) = 'X';
        chg_dir(&end, &g_dir, &x, &y);
    }

    int cnt = 0;
    int obs = 0;
    
    for(size_t y = 0; y < map.size(); y++)
    {
        for(size_t x = 0; x < map.at(y).size(); x++)
        {
            if(map.at(y).at(x) == 'X')
            {
                cnt++;
                obs += loop(x, y);
            }
        }
    }

    file.close();

    cout << "Count of positions: " << cnt << '\n';
    cout << "Count of obstacles: " << obs << '\n';

    return 0;
}