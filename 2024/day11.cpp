#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std; 

auto digits(long long num)
{
    if (num < 10) return 1;
    if (num < 100) return 2;
    if (num < 1000) return 3;
    if (num < 10000) return 4;
    if (num < 100000) return 5;
    if (num < 1000000) return 6;
    if (num < 10000000) return 7;
    if (num < 100000000) return 8;
    if (num < 1000000000) return 9;
    if (num < 10000000000) return 10;
    if (num < 100000000000) return 11;
    if (num < 1000000000000) return 12;
    if (num < 10000000000000) return 13;
    if (num < 100000000000000) return 14;
    if (num < 1000000000000000) return 15;
    if (num < 10000000000000000) return 16;
    if (num < 100000000000000000) return 17;
    if (num < 1000000000000000000) return 18;
    return 19;
    
}

auto blink(vector<long long>& stones, map<long long, int>& memo)
{
    for(size_t i = 0; i < stones.size(); i++)
    {
        if (stones.at(i) == 0)
        {
            stones.at(i) = 1;
            continue;
        }
        
        else if (digits(stones.at(i)) % 2 == 0)
        {
            auto stone_str = to_string(stones.at(i));
            auto half = stone_str.length() / 2;
            stones.at(i) = atoll(stone_str.substr(half, half).data());
            stones.insert(stones.begin() + i, atoll(stone_str.substr(0, half).data()));
            i++;
            continue;
        }
        else
        {
            stones.at(i) *= 2024;
            continue;
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

    map<long long, int> memo;
    for (auto i = 0; i < 25; i++)
    {
        cout << "Blink " << i+1 << '\n';
        blink(stones, memo);
    }

    cout << "Stones after 25 blinks: " << stones.size() << '\n';

    for (auto i = 25; i < 75; i++)
     {
        cout << "Blink " << i+1 << '\n';
        blink(stones, memo);
    }

    cout << "Stones after 75 blinks: " << stones.size() << '\n';

    return 0;
}