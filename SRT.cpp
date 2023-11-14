#include "SRT.h"
#include <algorithm>
#include<stack>
#include<queue>
#include<iostream>
using namespace std;

template <class itemtype>
srt<itemtype>::srt(){}

template <class itemtype>
srt<itemtype>::~srt(){}

//function that sorts processes inside vector by arrival time inside struct
template <class itemtype>
struct structComparison_srt {
    bool operator()(const itemtype& a, const itemtype& b) {
      return a.remainingCPU_time < b.remainingCPU_time;
      
    }
};

template <class itemtype>
void srt<itemtype>::schedule(vector<itemtype>& vec) {
  structComparison_srt<itemtype> comparisonFunction;
  // Sort the vector using the custom comparison function
  sort(vec.begin(), vec.end(), comparisonFunction);

}

template <class itemtype>
void srt<itemtype>::run(vector<itemtype>& processes) {
  queue<itemtype> srt_queue;
  for(itemtype p: processes) {
    srt_queue.push(p);
    //cout<<"Process: "<<p.process_id<<endl;
   // cout<<"Arrival Time: "<<p.arrival_time<<endl;   
    //cout <<"Total CPU Time: "<< p.totalCPU_time<<endl;
  }
  srt<itemtype> shortestRemainingTime;
  //shortestJobFirst.schedule(processes);
  double srt_att = 0;//sjf average turnaround time
  int srt_time = 0;//time
  vector<itemtype> active;
  vector<itemtype> finish;
  cout<<"\n\nSRT Algorithm Results:" << endl;

  while (true) {
    if(srt_queue.empty() && active.empty())break;
    if(srt_queue.front().arrival_time == srt_time) {
      active.push_back(srt_queue.front());
      srt_queue.pop();

    }
      shortestRemainingTime.schedule(active);
    if(!active.empty())active.back().remainingCPU_time--;
    srt_time++;
    if(!active.empty() && active.back().remainingCPU_time==0) {
      active.back().turnaround_time = srt_time - active.back().arrival_time;
      finish.push_back(active.back());
      active.pop_back();
    }

    //cout << sjf_time << endl;
  }
    for(itemtype p: finish) {
      cout<<"Process: "<<p.process_id<<endl;
      cout<<"Arrival Time: "<<p.arrival_time<<endl;   
      cout <<"Total CPU Time: "<< p.totalCPU_time<<endl;
      cout <<"Turnaroundtime: "<< p.turnaround_time<<endl;
      srt_att+= p.turnaround_time;
      cout<<endl;
    }
    srt_att = srt_att/finish.size();


    avg_turnaround_time = srt_att;

    cout<<"SRT: Average Turnaround Time : "<<avg_turnaround_time<<endl;
    cout<<"Time: "<<srt_time<<endl;
    cout<<endl;
}

template <class itemtype>
int srt<itemtype>::get_att() {
  return avg_turnaround_time;
}