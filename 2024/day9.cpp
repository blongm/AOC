#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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

auto mov_file(vector<int>& disk, size_t file_begin, int& file_end)
{
    auto file_size = file_end - file_begin;
    auto space = vector(file_size, FREE);
    auto pos = search(disk.begin(), disk.begin() + file_begin + 1, space.begin(), space.end());

    if (pos != disk.begin() + file_begin + 1)
    {
        copy_n(disk.begin() + file_begin + 1, file_size, pos);
        copy_n(space.begin(), file_size, disk.begin() + file_begin + 1);
    }

    file_end = FREE;
}

auto chk_block(vector<int>& disk, size_t& i, int& file_end)
{
    if (file_end == FREE and disk.at(i) != FREE)
        file_end = i;

    else if (file_end != FREE and disk.at(i) != disk.at(file_end))
    {
        mov_file(disk, i, file_end);
        i++;
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

    auto file_end = FREE;

    for (size_t i = disk2.size(); i --> 0;)
        chk_block(disk2, i, file_end);

    checksum = 0;
        
    for (size_t i = 0; i < disk2.size(); i++)
        if(disk2.at(i) >= 0) checksum += i * disk2.at(i);

    cout << "Part 2 Checksum: " << checksum << '\n';   

    return 0;
}