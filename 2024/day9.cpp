#include <iostream>
#include <fstream>
#include <vector>
#define FREE -1

using namespace std; 

auto mov_block(vector<int>& disk, size_t i)
{
    if (disk.back() == FREE and i == disk.size() - 1)
    {
        disk.pop_back();
        return;
    }

    while (disk.back() == FREE)
    {
        disk.pop_back();
    }

    if (i <= disk.size() - 1 and disk.at(i) == FREE)
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

    auto disk2  = disk;

    long long checksum = 0;

    for (size_t i = 0; i < disk.size(); i++)
    {
        mov_block(disk, i);
        if (i < disk.size()) checksum += i * disk.at(i);
    }

    cout << "Checksum: " << checksum << '\n';   

    for (size_t i = disk.size() - 1; i <= 0; i--)
    {
    //  if no end position recorded and not free
    //      record end position
    //  if end position recorded and free
    //      record start position
    //      calc difference
    //      if free spot exists for the whole file
    //          move file over
    //      reset end and start positions
    }  

    return 0;
}