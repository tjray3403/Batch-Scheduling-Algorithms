#include "SJF.h"
#include <algorithm>
#include<stack>
#include<queue>
#include<iostream>
using namespace std;

template <class itemtype>
sjf<itemtype>::sjf(){}

template <class itemtype>
sjf<itemtype>::~sjf(){}

//function that sorts processes inside vector by arrival time inside struct
template <class itemtype>
struct structComparison_sjf {
    bool operator()(const itemtype& a, const itemtype& b) {
      if(a.totalCPU_time != b.totalCPU_time) {
        return a.totalCPU_time < b.totalCPU_time;
          } else {
            return a.arrival_time < b.arrival_time;
          }
    }
};

template <class itemtype>
void sjf<itemtype>::schedule(vector<itemtype>& vec) {
  structComparison_sjf<itemtype> comparisonFunction;
  // Sort the vector using the custom comparison function
  sort(vec.begin(), vec.end(), comparisonFunction);

}


template <class itemtype>
void sjf<itemtype>::run(vector<itemtype>& processes) {
  sjf<itemtype> shortestJobFirst;
    //  shortestJobFirst.run(sjf_processes);
    queue<itemtype> sjf_queue;
    for(itemtype p: processes) {
      sjf_queue.push(p);
      //cout<<"Process: "<<p.process_id<<endl;
     // cout<<"Arrival Time: "<<p.arrival_time<<endl;   
      //cout <<"Total CPU Time: "<< p.totalCPU_time<<endl;
    }
   // sjf<process> shortestJobFirst;
    //shortestJobFirst.schedule(processes);
    double sjf_att = 0;//sjf average turnaround time
    int sjf_time = 0;//time
    deque<itemtype> temp;
    vector<itemtype> active;
    vector<itemtype> finish;
    cout<<"\n\nSJF Algorithm Results:" << endl;

    while (!sjf_queue.empty() || !active.empty()) {
      if (!sjf_queue.empty() && sjf_queue.front().arrival_time <= sjf_time) {
          active.push_back(sjf_queue.front());
          sjf_queue.pop();
      }

      if (active.empty()) {
          sjf_time++;
      } else {
          shortestJobFirst.schedule(active);
          active[0].remainingCPU_time--;

          if (active[0].remainingCPU_time == 0) {
              active[0].turnaround_time = sjf_time - active[0].arrival_time;
              finish.push_back(active[0]);
            //  cout << "pushed " << active[0].process_id << endl;
              active.erase(active.begin());
          }
          sjf_time++;
      }
    }

    for (const itemtype& p : finish) {
      cout << "Process: " << p.process_id << endl;
      cout << "Arrival Time: " << p.arrival_time << endl;
      cout << "Total CPU Time: " << p.totalCPU_time << endl;
      cout << "Turnaround Time: " << p.turnaround_time << endl;
      sjf_att += p.turnaround_time;
      cout << endl;
    }

    sjf_att /= finish.size();
    avg_turnaround_time = sjf_att;

    cout << "SJF: Average Turnaround Time: " << avg_turnaround_time << endl;
    cout<<"Time: "<<sjf_time<<endl;
    cout<<endl;
}

template <class itemtype>
int sjf<itemtype>::get_att() {
  return avg_turnaround_time;
}