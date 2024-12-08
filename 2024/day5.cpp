#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <functional>

using namespace std; 

vector<array<int, 2>> rules;

auto chk_ord(vector<int> update)
{
    for (auto r : rules)
    {
        auto p1 = find(update.begin(), update.end(), r.at(0));
        auto p2 = find(update.begin(), update.end(), r.at(1));

        if (p1 != update.end() and p2 != update.end() and p1 > p2)
        {
            return false;
        }
    }

    return true;
}

auto reorder(vector<int>* update)
{
    while (!chk_ord(*update))
    {
        for (auto r : rules)
        {
            auto p1 = find((*update).begin(), (*update).end(), r.at(0));
            auto p2 = find((*update).begin(), (*update).end(), r.at(1));

            while (p1 != (*update).end() and p2 != (*update).end() and p1 > p2)
            {
                //cout << '\n';
                //for(auto u : *update)  cout << u << ',';
                auto prev = p1-1;
                swap(*p1, *prev);

                p1 = find((*update).begin(), (*update).end(), r.at(0));
                p2 = find((*update).begin(), (*update).end(), r.at(1));
            } 
        }
    }
    
}

int main(int argc, char** argv)
{
    if (argc <= 1) return 1;
    ifstream file(argv[1]);

    vector<vector<int>> updates;

    string line;

    while (getline(file, line))
    {
        if (line.find('|') != string::npos)
        {
            replace(line.begin(), line.end(), '|', ' ');
            istringstream stream(line);

            int a; int b;

            stream >> a;
            stream >> b;

            rules.push_back({a, b});
        }
        else if (line.find(',') != string::npos)
        {
            replace(line.begin(), line.end(), ',', ' ');
            istringstream stream(line);

            vector<int> update;

            for (int n; stream >> n;)
            {
                update.push_back(n);
            }

            updates.push_back(update);
        }
    }

    file.close();

    auto sum = 0;
    auto sum_inc = 0;

    for(auto u : updates)
    {
        if (chk_ord(u))
        {
            sum += u.at(u.size() / 2);
        }
        else
        {
            reorder(&u);
            sum_inc += u.at(u.size() / 2);
        }
        
    }
    
    cout << "Sum: " << sum << '\n';
    cout << "Sum of incorrectly-ordered: " << sum_inc << '\n';

    return 0;
}