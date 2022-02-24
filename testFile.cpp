#include<fstream>
#include<assert.h>
#include<map>

using namespace std;

map<string, int> Nr;

int main()
{
    ifstream fi("input.txt");

    int pax, prj;
    fi>>pax>>prj;

    for(int i=0; i<pax; i++)
    {
        string name;
        int n;
        fi>>name>>n;

        assert(n==1);

        string skill;
        int val;

        fi>>skill>>val;

        assert(val==10);

        Nr[skill]++;
        assert(Nr[skill]==1);
    }
    fi.close();

    return 0;
}