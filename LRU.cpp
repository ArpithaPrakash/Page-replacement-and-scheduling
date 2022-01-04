#include<iostream>
#include<conio.h>
using namespace std;

int main() {
    int nop,nof,page[20],i,count=0;
    cout<<"Enter the number of pages: ";
    cin>>nop; 
    cout<<"\nEnter the Reference String: ";
    for(i=0;i<nop;i++) {
        cin>>page[i]; 
    }
    cout<<"\nEnter the number of frames: ";
    cin>>nof;
    int frame[nof],fcount[nof];
    for(i=0;i<nof;i++) {
        frame[i]=-1; 
        fcount[i]=0; 
    }
    i=0;
    while(i<nop) {
        int j=0,flag=0;
        while(j<nof) {
            if(page[i]==frame[j]) { 
                flag=1;
                fcount[j]=i+1;
            }
            j++;
        }
        j=0;  
        cout<<"\n--------------------------------------\n";
        cout<<page[i]<<"-->";   
        if(flag==0) {
            int min=0,k=0;
            while(k<nof-1) {
                if(fcount[min]>fcount[k+1]) 
                    min=k+1;
                k++;
            }
            frame[min]=page[i]; 
            fcount[min]=i+1;    
            count++;           
            while(j<nof) {
               cout<<"\t|"<<frame[j]<<"|";
               j++;
            }
            cout<<"\t MISS";
        }
        else
            cout<<"\t\t HIT";
        i++; 
    }
    cout<<"\n--------------------------------------\n";
    cout<<"\nNumber of Page Faults = "<<count;
    cout<<"\nMiss ratio = "<<count<<"/"<<nop;
    cout<<"\nHit ratio = "<<nop-count<<"/"<<nop;
    getch();
    return 0;
}