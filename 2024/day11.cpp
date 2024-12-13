#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std; 

auto blink(vector<long long>& stones)
{
    for(size_t i = 0; i < stones.size(); i++)
    {
        auto stone_str = to_string(stones.at(i));

        if (stones.at(i) == 0)
        {
            stones.at(i) = 1;
        }
        
        else if (stone_str.length() % 2 == 0)
        {
            auto half = stone_str.length() / 2;
            stones.at(i) = atoll(stone_str.substr(half, half).data());
            stones.insert(stones.begin() + i, atoll(stone_str.substr(0, half).data()));
            i++;
        }
        else
        {
            stones.at(i) *= 2024;
        }
            
    }    
}

int main(int argc, char** argv)
{
    if (argc <= 1) return 1;
    ifstream file(argv[1]);

    string line;
    getline(file, line);
    file.close();

    istringstream stream(line);

    vector<long long> stones;

    int stone;
    while (stream >> stone)  stones.push_back(stone);

    for (auto i = 0; i < 25; i++)
    {
        blink(stones);
    }

    cout << stones.size() << '\n';

    return 0;
}