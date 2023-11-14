#include "FIFO.h"
#include <algorithm>
#include<stack>
#include<queue>
#include<iostream>
using namespace std;

template <class itemtype>
fifo<itemtype>::fifo(){}

template <class itemtype>
fifo<itemtype>::~fifo(){}

//function that sorts processes inside vector by arrival time inside struct
template <class itemtype>
struct structComparison_fifo {
    bool operator()(const itemtype& a, const itemtype& b) {
        return a.arrival_time < b.arrival_time;
    }
};

template <class itemtype>
void fifo<itemtype>::schedule(vector<itemtype>& vec) {
  structComparison_fifo<itemtype> comparisonFunction;
  // Sort the vector using the custom comparison function
  sort(vec.begin(), vec.end(), comparisonFunction);
  
}

template <class itemtype>
void fifo<itemtype>::run(vector<itemtype>& processes) {
  double fifo_att = 0;//fifo average turnaround time
  int fifo_time = 0;//time
  for(itemtype p: processes) {

    while(fifo_time<p.arrival_time) {
      fifo_time++;
    }

      cout<<"Process: "<<p.process_id<<endl;
      cout<<"Arrival Time: "<<p.arrival_time<<endl;   
      cout <<"Total CPU Time: "<< p.totalCPU_time<<endl;
    int temp_time = p.remainingCPU_time;

    while(temp_time>0) {
      fifo_time++;
      temp_time--;
    }

    p.remainingCPU_time = temp_time;
    p.turnaround_time = fifo_time - p.arrival_time;
     // fifo_att = fifo_att + p.totalCPU_time-p.arrival_time;
    cout <<"Turnaround Time: "<< p.turnaround_time<<endl;
    fifo_att = fifo_att + p.turnaround_time;
      cout<<endl;
  }
  avg_turnaround_time = fifo_att/processes.size();
  cout<<"FIFO: Average Turnaround Time : "<<avg_turnaround_time<<endl;
  cout<<"Time: "<<fifo_time<<endl;
  cout<<endl;
  
}

template <class itemtype>
int fifo<itemtype>::get_att() {
  return avg_turnaround_time;
}