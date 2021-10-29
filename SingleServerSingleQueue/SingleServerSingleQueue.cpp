#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

int main()
{
    int n=7; //number of customers
    int table[n][7]; //Table to store values
    /**
    Columns are:
    Customer(0), Arrival time(1), service begin(2), service time(3), service end(4), wait(5), server idle time(6)
    */
    int totals[7]; //Table to store sum of all columns
    //Set total array values to zero
    memset(totals, 0, sizeof(totals));

    cout<<"Enter arrival time, service time as Input:\n";
    //Input variables- arrival time, service time
    for(int i=0; i<n; i++)
    {
        cin>>table[i][1]>>table[i][3];
        table[i][0] = i+1;
        //summing their values
        totals[1]+=table[i][1];
        totals[3]+=table[i][3];
    }

    //Find other variables of table

    //Find service begin column
    table[0][2] = table[0][1];
    totals[2]+=table[0][2];

    //next service begin is later of next's arrival time and current's service end time
    for(int i=1; i<n; i++)
    {
        table[i][2] = max(table[i][1], table[i-1][2]+table[i-1][3]);
        totals[2]+=table[i][2];
    }

    //service end, wait columns
    int nonWaitCust=0;
    for(int i=0; i<n; i++)
    {
        //Service end
        table[i][4]= table[i][2] + table[i][3];
        totals[4]+=table[i][4];
        //wait = service begin - arrival
        table[i][5]= table[i][2] - table[i][1];
        totals[5]+=table[i][5];
        if(table[i][5]>0) nonWaitCust++;
    }

    //Idle server = next arrival time - current service end time
    for(int i=0; i<n-1; i++)
    {
        table[i][6] = max(table[i+1][1] - table[i][4], 0);
        totals[6]+=table[i][6];
    }
    table[n-1][6]=0;
    totals[6]+=table[n-1][6];

    cout<<"\nTable:\nCustomer(0), Arrival time(1), service begin(2), service time(3), service end(4), wait(5), server idle time(6)\n";
    //Print table
    for(int i=0; i<7; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<table[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\nTotal values of the columns:\n";
    //Print totals
    for(int i=0; i<7; i++)
        cout<<totals[i]<<" ";

    //Finding the values in question:
    float ans1 = float(totals[5])/float(n);
    float ans2 = float(nonWaitCust)/float(n);
    float ans3 = float(totals[6])/float(totals[3]);
    float ans4 = float(totals[3])/float(n);
    float ans5 = float(totals[1])/float(n);
    float ans6 = float(table[n-1][4])/float(n);

    cout<<"\n\nAverage Waiting time per customer: "<<ans1;
    cout<<"\nProbability of a customer to wait in the queue: "<<ans2;
    cout<<"\nIdle time for servers: "<<ans3;
    cout<<"\nAverage service time: "<<ans4;
    cout<<"\nAverage arrival time: "<<ans5;
    cout<<"\nAverage time customer spent in system: "<<ans6;
    cout<<"\n";
    return 0;
}

/*
Enter arrival time, service time as Input:
0 2
6 3
7 1
11 1
14 1
20 1
25 2

Table:
Customer(0), Arrival time(1), service begin(2), service time(3), service end(4), wait(5), server idle time(6)
1 0  0  2 2  0 4
2 6  6  3 9  0 0
3 7  9  1 10 2 1
4 11 11 1 12 0 2
5 14 14 1 15 0 5
6 20 20 1 21 0 4
7 25 25 2 27 0 0

Total values of the columns:
0 83 85 11 96 2 16

Average Waiting time per customer: 0.285714
Probability of a customer to wait in the queue: 0.142857
Idle time for servers: 1.45455
Average service time: 1.57143
Average arrival time: 11.8571
Average time customer spent in system: 3.85714
*/
