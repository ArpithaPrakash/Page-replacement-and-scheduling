#include <iostream>
#include <algorithm>
using namespace std;

int k = 0, f = 0, r = 0;

struct node
{
    char pId;
    int at;
    int bt;
    int priority;
    int rt = 0;
    int ct = 0;
    int wt = 0;
} a[1000], b[1000], c[1000];

void insert(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        cin >> a[i].pId;
        cin >> a[i].at;
        cin >> a[i].bt;
        cin >> a[i].priority;
        a[i].wt = -a[i].at + 1;
    }
}

bool btSort(node a, node b)
{
    return a.bt < b.bt;
}

bool atSort(node a, node b)
{
    return a.at < b.at;
}

bool prioritySort(node a, node b)
{
    return a.priority < b.priority;
}

void disp(int nop, int quanta)
{
    int n = nop, q;
    sort(a, a + n, atSort);
    int ttime = 0;
    int i, j, tArray[1000];
    int alltime = 0; // contains total burst time
    bool moveLast = false;
    for (i = 0; i < n; i++)
    {
        alltime += a[i].bt;
    }
    alltime += a[0].at; // useful when arrival time doesn't start from 0
    for (i = 0; ttime <= alltime;)
    {
        j = i;
        // checks for processes with arrival time = 0 and not exceeding total number of processes
        while (a[j].at <= ttime && j != n)
        {
            b[r] = a[j]; // makes copy of node with arrival time = 0
            j++;
            r++;
        }
        if (r == f) // if no processes have arrival time as 0
        {
            c[k].pId = 'i';
            c[k].bt = a[j].at - ttime;
            c[k].at = ttime;
            ttime += c[k].bt;
            k++;
            continue;
        }
        i = j; // i = last process with arrival time = 0
        if (moveLast == true)
        {
            sort(b + f, b + r, prioritySort);
        }
        j = f;
        if (b[j].bt > quanta)
        {
            c[k] = b[j];
            c[k].bt = quanta;
            k++;
            b[j].bt = b[j].bt - quanta;
            ttime += quanta;
            moveLast = true;
            for (q = 0; q < n; q++)
            {
                if (b[j].pId != a[q].pId)
                {
                    a[q].wt += quanta;
                }
            }
        }
        else
        {
            c[k] = b[j];
            k++;
            f++;
            ttime += b[j].bt;
            moveLast = false;
            for (q = 0; q < n; q++)
            {
                if (b[j].pId != a[q].pId)
                {
                    a[q].wt += b[j].bt;
                }
            }
        }
        if (f == r && i >= n)
            break;
    }
    tArray[i] = ttime;
    ttime += a[i].bt;
    for (i = 0; i < k - 1; i++)
    {
        if (c[i].pId == c[i + 1].pId)
        {
            c[i].bt += c[i + 1].bt;
            for (j = i + 1; j < k - 1; j++)
                c[j] = c[j + 1];
            k--;
            i--;
        }
    }

    int rtime = 0;
    for (j = 0; j < n; j++)
    {
        rtime = 0;
        for (i = 0; i < k; i++)
        {
            if (c[i].pId == a[j].pId)
            {
                a[j].rt = rtime;
                break;
            }
            rtime += c[i].bt;
        }
    }

    float averageWaitingTime = 0;
    float averageResponseTime = 0;
    float averageTAT = 0;

    cout << "\nGantt Chart\n";
    rtime = 0;
    for (i = 0; i < k; i++)
    {
        if (i != k)
            cout << "|  " << 'P' << c[i].pId << "   ";
        rtime += c[i].bt;
        for (j = 0; j < n; j++)
        {
            if (a[j].pId == c[i].pId)
                a[j].ct = rtime;
        }
    }
    cout << "\n";
    rtime = 0;
    for (i = 0; i < k + 1; i++)
    {
        cout << rtime << "\t";
        tArray[i] = rtime;
        rtime += c[i].bt;
    }

    cout << "\n";
    cout << "\n";
    cout << "P.Name Priority AT\tBT\tCT\tTAT\tWT\tRT\n";
    for (i = 0; i < nop && a[i].pId != 'i'; i++)
    {
        if (a[i].pId == '\0')
            break;
        cout << 'P' << a[i].pId << "\t";
        cout << a[i].priority << "\t";
        cout << a[i].at << "\t";
        cout << a[i].bt << "\t";
        cout << a[i].ct << "\t";
        cout << a[i].wt + a[i].ct - rtime + a[i].bt << "\t";
        averageTAT += a[i].wt + a[i].ct - rtime + a[i].bt;
        cout << a[i].wt + a[i].ct - rtime << "\t";
        averageWaitingTime += a[i].wt + a[i].ct - rtime;
        cout << a[i].rt - a[i].at << "\t";
        averageResponseTime += a[i].rt - a[i].at;
        cout << "\n";
    }

    cout << "Average Response time: " << (float)averageResponseTime / (float)n << endl;
    cout << "Average Waiting time: " << (float)averageWaitingTime / (float)n << endl;
    cout << "Average Turnaround time: " << (float)averageTAT / (float)n << endl;
}

int main()
{
    int nop; // number of processes
    cout << "Enter number of processes\n";
    cin >> nop;
    cout << "Enter the process, AT, BT, priority respectively\n";
    insert(nop);  // to read input
    disp(nop, 1); // the second parameter is the time quanta
    return 0;
}