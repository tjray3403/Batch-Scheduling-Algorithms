#include <vector>
#include <algorithm>
using namespace std;
template <class itemtype>
class srt
{

public:
int avg_turnaround_time = 0;
srt();
~srt();
//static bool customComparison(const struct, const struct);
void schedule(vector<itemtype>&);
void run(vector<itemtype>&);
int get_att();

};