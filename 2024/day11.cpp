#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <memory>

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


class Stone
{
    public:

        long long dat;
        shared_ptr<Stone> SubStone1;
        shared_ptr<Stone> SubStone2;
        Stone(long long dat)
        {
            this->dat = dat;
            SubStone1 = nullptr;
            SubStone2 = nullptr;
        }

        auto calc_sub_stones(vector<shared_ptr<Stone>>& Stones)
        {
            shared_ptr<Stone> left = nullptr;
            shared_ptr<Stone> right = nullptr;

            if (dat == 0)
            {
                right = make_shared<Stone>(1);
            }
            
            else if (digits(dat) % 2 == 0)
            {
                auto stone_str = to_string(dat);
                auto half = stone_str.length() / 2;

                left = make_shared<Stone>(atoll(stone_str.substr(half, half).data()));
                right = make_shared<Stone>(atoll(stone_str.substr(0, half).data()));

                if (find_if(Stones.begin(), Stones.end(), [& left](const shared_ptr<Stone>& S){return S->dat == left->dat;}) == Stones.end())
                {
                    SubStone1 = left;
                    Stones.push_back(SubStone1);
                    
                }
                else
                {
                    SubStone1 = *find_if(Stones.begin(), Stones.end(), [& left](shared_ptr<Stone>& S){return S->dat == left->dat;});
                }
            }

            else
            {
                right = make_shared<Stone>(dat * 2024);
            }

            if (find_if(Stones.begin(), Stones.end(), [& right](const shared_ptr<Stone>& S){return S->dat == right->dat;}) == Stones.end())
            {
                SubStone2 = right;
                Stones.push_back(SubStone2);
            }
            else
            {
                SubStone2 = *find_if(Stones.begin(), Stones.end(), [&right](const shared_ptr<Stone>& S){return S->dat == right->dat;});
            }
        }

        auto size() const
        {
            return (SubStone1 != nullptr) + (SubStone2 != nullptr);
        }
};


auto calc_size(const Stone& Stone, int iter, int maxiter)
{
    if (iter == maxiter) return Stone.size();

    auto size = 0;
    
    if (Stone.SubStone1 != nullptr)
        size += calc_size(*Stone.SubStone1, iter + 1, maxiter);
    
     size += calc_size(*Stone.SubStone2, iter + 1, maxiter);

     return size;
}

int main(int argc, char** argv)
{
    if (argc <= 1) return 1;
    ifstream file(argv[1]);

    string line;
    getline(file, line);
    file.close();

    istringstream stream(line);

    vector<shared_ptr<Stone>> init;

    int dat;
    while (stream >> dat) 
    {
        init.push_back(make_shared<Stone>(dat));
    }

    vector<shared_ptr<Stone>> Stones = init;

    for (size_t i = 0; i < Stones.size(); i++)
    {
        Stones.at(i)->calc_sub_stones(Stones);
    }
    
    auto size = 0;

    for (auto& Stone : init)
    {
        size += calc_size(*Stone, 1, 25);
    }

    cout << "Stones after 25 blinks: " << size << '\n';


    for (auto& Stone : init)
    {
        size += calc_size(*Stone, 1, 55);
    }

    cout << "Stones after 75 blinks: " << size << '\n';

    return 0;
}