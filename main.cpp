#include <iostream>
#include <vector>
#include "FIFO.cpp"
#include "SJF.cpp"
#include "SRT.cpp"
#include<stack>
#include<queue>
using namespace std;

struct process {
int process_id=0;
int arrival_time=0;
int totalCPU_time=0;
int remainingCPU_time=0;
int turnaround_time=0;
bool active = false;
};

//By Tristan Ray, Macio Toney, Jaden Thompson, Jordan Rohilliard, Mohammed Khalid
int random(int max) {/*Random Number between 1 to max*/
  int num;
  for(int i=0;i<max;i++){
    num = (rand() % max) + 1;
      //cout << num <<" ";   
  }
  return num;
}



int main() {
  srand(time(0));  
   int k = 100; // processes arrive uniformly between 0-k
  cout<< " n = ";
  //cin>>temp_num;
   
  
  int ProcessCnt = random(10); // random number of processes between 1 and 10
  cout<<ProcessCnt<< endl;
  vector<process> processes;
  int count = 1;
  
  while(count<=ProcessCnt) {
    process arrival_process;
    arrival_process.process_id = count;
    cout<<"Process: "<<arrival_process.process_id<<endl;
    
    arrival_process.arrival_time = (k/ProcessCnt) * (count-1); //Calcalates the arrival time
    cout<<"Arrival Time: "<<arrival_process.arrival_time<<endl;   
    processes.push_back(arrival_process);
    cout<<endl;
    count++;
  }

  //int d = 0;
  //cout << "Please choose the average CPU time:"<<endl;
  //cin >> d;
  int d = random(100);//
  cout << "avg CPU time 1 = " << d << endl;
  // d = average total CPU Time, ranging from 0-100
  //int v = 0;
  //cout << "Please choose a % for standard deviation:" <<endl;
  //cin >> v;
  int v = random(100);
  cout << "standard deviation = " << v << "%" << endl<<endl;
  // v = Standard deviation, a percentage of d ranging from 0-100%
  int percent = 0;
  count = 1;

  while(count<=ProcessCnt) {
    double percent = 0;
    cout <<"Process: "<< processes[count-1].process_id<<endl;

    percent = random(2 * v) -v;
    // picking a random number between 0 and 2v.Then Subtracting by v to get a random number between -v and v.
    cout << "Deviation from Avg CPU Time: " << percent << "%" << endl;
    percent = percent / 100;
    // calculating a random percentage to deviate from d. Can be at most v and at least -v.
      processes[count-1].totalCPU_time = d + (d * percent);
    //Calcalates the total CPU time, being avg CPU time + deviation.
    cout<<"Total CPU Time: "<<processes[count-1].totalCPU_time<<endl;
    processes[count-1].remainingCPU_time = processes[count-1].totalCPU_time;
    cout<< "Remaining CPU Time:" << processes[count-1].remainingCPU_time<<endl<<endl;
    count++;
  } 

  
  //FIFO
  fifo<process> firstIn_firstout;
  firstIn_firstout.schedule(processes);//sorts vector based off arrival time
  firstIn_firstout.run(processes);
 vector<process> sjf_processes = processes;//copying processes so data is the same throughout
 vector<process> srt_processes = processes;

  //SRT
  srt<process> shortestRemainingTime;
  shortestRemainingTime.run(srt_processes);

  //SJF
  sjf<process> shortestJobFirst;
  shortestJobFirst.run(sjf_processes);

  double FIFO_ATT = firstIn_firstout.get_att();
  double SRT_ATT = shortestRemainingTime.get_att();
  double SJF_ATT = shortestJobFirst.get_att();
  
  cout<<endl;
  cout << "Arrival time frequency: " << k/ProcessCnt << endl;
  cout << "Average CPU Time: " << d <<endl;
  cout << "FIFO ATT: " << FIFO_ATT <<endl;
  cout << "FIFO d/ATT: " << d/FIFO_ATT <<endl;
  cout << "SRT  ATT: " << SRT_ATT<<endl;
  cout << "SRT  d/ATT: " << d/SRT_ATT <<endl;
  cout << "SJF  ATT: " << SJF_ATT<<endl;
  cout << "SJF  d/ATT: " << d/SJF_ATT<<endl<<endl;

  double best = max(d/SJF_ATT,max(d/FIFO_ATT,d/SRT_ATT));

  cout<< "The most effecient scheduling algorithm with an average CPU time of " << d << " and a standard deviation of "<< v << "% is: " <<best;


  
  return 0;
}