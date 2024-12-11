#include <iostream>
#include <fstream>
#include <vector>
#define FREE -1

using namespace std; 

auto mov_block(vector<int>& disk, int i)
{
    if (disk.back() == disk.at(i))
    {
        disk.pop_back();
        return;
    }

    while (disk.back() == FREE) disk.pop_back();

    if (disk.at(i) == FREE)
    {
        disk.at(i) = disk.back();
        disk.pop_back();
    }
}

int main(int argc, char** argv)
{
    if (argc <= 1) return 1;
    ifstream file(argv[1]);

    vector<int> disk;
    char num;
    
    for (auto ID = 0; file.get(num); ID++)
    {
        disk.insert(disk.end(), num - '0', ID);
        
        if (file.get(num))
            disk.insert(disk.end(), num - '0', FREE);
    }

    file.close();
    auto checksum = 0;

    for (size_t i = 0; i < disk.size(); i++)
    {
        mov_block(disk, i);
        if (i < disk.size()) checksum += i * disk.at(i);
    }

    cout << "Checksum: " << checksum << '\n';   

    return 0;
}