#include <iostream>
#include <fstream>
#include <regex>
#include <array>
#include <numeric>
#include <functional>
#include <bitset>

using namespace std; 

void ins_nums(string s, vector<array<int, 2>>* nums, vector<array<int, 2>>* nums_2, bool* do_mul)
{
    if (s.find("don't") != string::npos)
    {
        *do_mul = false;
        return;
    }
    if (s.find("do") != string::npos)
    {
        *do_mul = true;
        return;
    }
    s.replace(0, 4, "");
    replace(s.begin(), s.end(), ',', ' ');

    istringstream stream(s);
    int a; int b;

    stream >> a;
    stream >> b;

    if ((*do_mul))
    {
        (*nums_2).push_back({a, b});
    }

    (*nums).push_back({a, b});
}

int main(int argc, char** argv)
{
    if (argc < 1) return 1;

    ifstream file(argv[1]);
    stringstream buffer;
    buffer << file.rdbuf();
    string text = buffer.str();

    file.close();

    regex pattern("don't\\(\\)|do\\(\\)|mul\\(\\d{1,3},\\d{1,3}\\)");
    vector<string> matches;
    copy(sregex_token_iterator(text.begin(), text.end(), pattern), sregex_token_iterator(), back_inserter(matches));

    vector<array<int, 2>> nums;  
    vector<array<int, 2>> nums_2;  
    bool do_mul = true;
    for_each(matches.begin(), matches.end(), [&nums, &nums_2, &do_mul](string& s){ins_nums(s, &nums, &nums_2, &do_mul);});

    vector<int> products;
    vector<int> products_2;
    transform(nums.begin(), nums.end(), back_inserter(products), [](array<int, 2> a){return a.at(0) * a.at(1);});
    transform(nums_2.begin(), nums_2.end(), back_inserter(products_2), [](array<int, 2> a){return a.at(0) * a.at(1);});

    cout << "Part 1: " << reduce(products.begin(), products.end()) << '\n';
    cout << "Part 2: " << reduce(products_2.begin(), products_2.end()) << '\n';

    return 0;
}