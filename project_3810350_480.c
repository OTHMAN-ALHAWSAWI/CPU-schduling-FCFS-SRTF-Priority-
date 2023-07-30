#include <stdio.h>

void findWaitingTimeFCFS(int processes[], int n, int bt[], int wt[])
{
    wt[0] = 0;

    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];
}

void findAverageTimeFCFS(int processes[], int n, int bt[])
{
    int wt[n], total_wt = 0;

    findWaitingTimeFCFS(processes, n, bt, wt);

    printf("FCFS Scheduling:\n");
    printf("Processes  Burst time  Waiting time\n");

    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        printf("%d\t%d\t\t%d\n", i + 1, bt[i], wt[i]);
    }

    printf("\nAverage waiting time: %.2f\n\n", (float)total_wt / n);
}

void findWaitingTimeSRTF(int processes[], int n, int bt[], int wt[])
{
    int rt[n];

    for (int i = 0; i < n; i++)
        rt[i] = bt[i];

    int complete = 0, t = 0, minm = 999999;
    int shortest = 0, finish_time;
    int check = 0;

    while (complete != n)
    {

        for (int j = 0; j < n; j++)
        {
            if ((rt[j] > 0) && (rt[j] < minm))
            {
                minm = rt[j];
                shortest = j;
                check = 1;
            }
        }

        if (check == 0)
        {
            t++;
            continue;
        }

        rt[shortest]--;

        minm = rt[shortest];
        if (minm == 0)
            minm = 999999;

        if (rt[shortest] == 0)
        {
            complete++;
            check = 0;

            finish_time = t + 1;

            wt[shortest] = finish_time - bt[shortest];

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }
}

void findAverageTimeSRTF(int processes[], int n, int bt[])
{
    int wt[n], total_wt = 0;

    findWaitingTimeSRTF(processes, n, bt, wt);

    printf("SRTF Scheduling:\n");
    printf("Processes  Burst time  Waiting time\n");

    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        printf("%d\t%d\t\t%d\n", i + 1, bt[i], wt[i]);
    }

    printf("\nAverage waiting time: %.2f\n\n", (float)total_wt / n);
}

void findWaitingTimePriority(int processes[], int n, int bt[], int priority[], int wt[])
{
    int pos, temp;

    for (int i = 0; i < n; i++)
    {
        pos = i;
        for (int j = i + 1; j < n; j++)
        {
            if (priority[j] < priority[pos])
                pos = j;
        }

        temp = priority[i];
        priority[i] = priority[pos];
        priority[pos] = temp;

        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        temp = processes[i];
        processes[i] = processes[pos];
        processes[pos] = temp;
    }

    wt[0] = 0;

    for (int i = 1; i < n; i++)
        wt[i] = bt[i - 1] + wt[i - 1];
}

void findAverageTimePriority(int processes[], int n, int bt[], int priority[])
{
    int wt[n], total_wt = 0;

    findWaitingTimePriority(processes, n, bt, priority, wt);

    printf("Priority Scheduling:\n");
    printf("Processes  Burst time  Priority  Waiting time\n");

    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + wt[i];
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], priority[i], wt[i]);
    }

    printf("\nAverage waiting time: %.2f\n\n", (float)total_wt / n);
}

int main()
{
    int n;
    printf("Enter the number of operations: ");
    scanf("%d", &n);

    int processes[n], burst_time[n], priority[n];

    printf("Enter the CPU time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    printf("Enter the priority for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        scanf("%d", &priority[i]);
    }

    findAverageTimeFCFS(processes, n, burst_time);
    findAverageTimeSRTF(processes, n, burst_time);
    findAverageTimePriority(processes, n, burst_time, priority);

    return 0;
}