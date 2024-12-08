#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <functional>
#include <cmath>

using namespace std; 

typedef enum OP
{
    NA,
    ADD,
    MUL,
    CON

} OP;

bool upd_ops(vector<OP>* ops)
{
    if (all_of((*ops).begin(), (*ops).end(), [](OP OP){return OP == CON;}))
    {
        return false;
    }
    if (all_of((*ops).begin(), (*ops).end(), [](OP OP){return OP == NA;}))
    {
        fill((*ops).begin(), (*ops).end(), ADD);
        return true;
    }
    for (size_t i = 0; i < (*ops).size(); i++)
    {
        switch ((*ops).at(i))
        {
        case ADD:
            (*ops).at(i) = MUL; 
            return true;
            break;
        
        case MUL:
            (*ops).at(i) = CON; 
            return true;
            break;

        case CON:
            (*ops).at(i) = ADD; 
            break;
        
        default:
            (*ops).at(i) = ADD; 
            return true;
        }  
    }
    return false;
}

int main(int argc, char** argv)
{
    if (argc <= 1) return 1;
    ifstream file(argv[1]);

    long long total = 0;
    long long con_total = 0;
    string line;

    while (getline(file, line))
    {
        replace(line.begin(), line.end(), ':', ' ');
        istringstream stream(line);

        long long res;
        stream >> res;

        vector<int> eq;

        int n;
        while (stream >> n)
        {
            eq.push_back(n);
        }

        auto matches = false;
        auto con_matches = false;

        vector<OP> ops(eq.size() - 1, NA);

        while (upd_ops(&ops))
        {
            long long calc = eq.at(0);

            for(size_t j = 0; j < ops.size(); j++)
            {
                switch (ops.at(j))
                {
                case ADD:        
                    calc += eq.at(j+1);
                    break;

                case MUL:  
                    calc *= eq.at(j+1);
                    break;
                
                case CON:  
                    calc = stoll(to_string(calc) + to_string(eq.at(j+1)));
                    break;
                
                default: break;
                }
            }

            if (calc == res) 
            {
                if (find(ops.begin(), ops.end(), CON) == ops.end())
                {
                    matches = true;
                    
                }
                
                con_matches = true;
            }
        }

        total = matches ? total + res : total;
        con_total = con_matches ? con_total + res : con_total;

    }

    file.close();

    cout << "Total: " << total << '\n';
    cout << "Total with Concat: " << con_total << '\n';

    return 0;
}