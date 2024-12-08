#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std; 

int main(int argc, char** argv)
{
    if (argc <= 1) return 1;
    ifstream file(argv[1]);

    int cnt = 0;
    int mas_cnt = 0;

    vector<string> lines;
    string line;

    while (getline(file, line))
    {
        lines.push_back(line);

        for (size_t pos = 0; pos != string::npos;)
        {
            pos = line.find("XMAS", pos);
            if (pos != string::npos) 
            {
                pos++; cnt++;
            }
            
        }
        for (size_t pos = 0; pos != string::npos;)
        {
            pos = line.find("SAMX", pos);
            if (pos != string::npos) 
            {
                pos++; cnt++;
            }
        }
    }

    for (size_t i = 0; i < lines.size(); i++)
    {
        for (size_t j = 0; j < lines.at(i).size(); j++)
        {
            switch (lines.at(i).at(j))
            {
            case 'X':
                if (i >= 3)
                {
                    cnt += !(string("X") + lines.at(i-1).at(j) + lines.at(i-2).at(j) + lines.at(i-3).at(j)).compare("XMAS");
                    cnt += j >= 3 and !(string("X") + lines.at(i-1).at(j-1) + lines.at(i-2).at(j-2) + lines.at(i-3).at(j-3)).compare("XMAS");
                    cnt += j <= lines.size() - 4 and !(string("X") + lines.at(i-1).at(j+1) + lines.at(i-2).at(j+2) + lines.at(i-3).at(j+3)).compare("XMAS");
                }

                if (i <= lines.size() - 4)
                {
                    cnt += !(string("X") + lines.at(i+1).at(j) + lines.at(i+2).at(j) + lines.at(i+3).at(j)).compare("XMAS");
                    cnt += j >= 3 and !(string("X") + lines.at(i+1).at(j-1) + lines.at(i+2).at(j-2) + lines.at(i+3).at(j-3)).compare("XMAS");
                    cnt += j <= lines.at(i).size() - 4 and !(string("X") + lines.at(i+1).at(j+1) + lines.at(i+2).at(j+2) + lines.at(i+3).at(j+3)).compare("XMAS");
                }
                break;

            case 'A':
                mas_cnt +=  (i != 0 and j != 0 and i != lines.size() -1 and j != lines.at(i).size() - 1) and
                            ((lines.at(i-1).at(j-1) == 'M' and lines.at(i+1).at(j+1) == 'S') or (lines.at(i-1).at(j-1) == 'S' and lines.at(i+1).at(j+1) == 'M')) and
                            ((lines.at(i+1).at(j-1) == 'M' and lines.at(i-1).at(j+1) == 'S') or (lines.at(1+i).at(j-1) == 'S' and lines.at(i-1).at(j+1) == 'M'));
            }
        }  
    }
    

    file.close();

    cout << "Puzzle Answer: " << cnt << "\n";
    cout << "Correct Puzzle Answer: " << mas_cnt << "\n";

    return 0;
}