#include <vector>
#include <algorithm>
#include<stack>
#include<queue>
#include<iostream>
using namespace std;
template <class itemtype>
class sjf
{

public:
int avg_turnaround_time = 0;
sjf();
~sjf();
//static bool customComparison(const struct, const struct);
void schedule(vector<itemtype>&);
void run(vector<itemtype>&);
int get_att();

};