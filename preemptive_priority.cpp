#include<iostream>
#include<iomanip>

using namespace std;
typedef struct  {
    int at; // arrival
    int bt; // burst
    int priority;
    int rt; // remain
    int wt; // wait
    int tt; // turnaround
    int et; // end
} process_t;

int main()
{
    process_t p[100];
    int n;

    cout<<"Enter the number of Processes: ";  //input
    cin>>n;
    cout << endl;
    
    for(int i=0; i<n; i++)
    {
        cout<<"Enter arrival time of process P" << i << ": ";  //input
        cin>>p[i].at;

        cout<<"Enter burst time of process P" << i << ": ";  //input
        cin>>p[i].bt;
        p[i].rt = p[i].bt;
        
        cout<<"Enter priority of process P" << i << ": ";  //input
        cin>>p[i].priority;
        
        cout << endl;
    }
    
    cout << "|";
    
    int completed  = 0;  // completed process count
    int timer      = 0;  // clock
    float total_tt = 0.0;
    float total_wt = 0.0;
    
    while (completed < n) { // till all processes are completed
    
        int chosen   = -1; // chosen process
    
        for(int i=0; i<n; i++) { // go over all processes
    
            if(p[i].at <= timer && p[i].rt > 0) { // if there is some process that arrived before time, and has some rt
                if (chosen == -1) {  
                    chosen = i;
                } else if (p[chosen].priority > p[i].priority) { 
                    chosen = i;
                } else if (p[chosen].priority == p[i].priority) {
                    if (p[i].at < p[chosen].at) {
                        chosen = i;
                    }
                }
            }
        }
            
        if( chosen != -1) { // if some process was chosen for execution
            //cout << "[Time " << timer << "] Running P" << chosen << endl;
            p[chosen].rt -= 1;
            
            cout << "  P" << chosen << "  " << "|";
            
            if (p[chosen].rt == 0) { // if fully executed 
                p[chosen].et = timer + 1;
                p[chosen].wt = p[chosen].et - p[chosen].at - p[chosen].bt;
                p[chosen].tt = p[chosen].et - p[chosen].at;
                completed += 1;
                total_wt += p[chosen].wt;
                total_tt += p[chosen].tt;
                
            }
        } else {
            //cout << "[Time " << timer << "] Idle"<< endl;
            cout << " Idle |";
        }
        timer = timer + 1;
    }
    
    cout << endl;
    for (int i=0; i <= timer; i++) 
        cout << std::setw(7) << left << i;
    cout << endl << endl;
    
    cout << "Average TT is " << total_tt  << " / "  << n << " = " << total_tt/n << endl;
    cout << "Average WT is " << total_wt  << " / "  << n << " = " << total_wt/n << endl;
}
