#include<stdio.h>
#include<pthread.h>
struct task {
    int name;
    int arT, brT, crT, wrT, trT;
    int processed;

} p[20];

void *scheduling(void *args);

int n;
void sortTheArrival()
{
    struct task temp;
    int i, j;

    // use Selection Sort 
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {

            // Check for lesser arrival time
            if (p[i].arT > p[j].arT) {

                // Swap earlier process to front
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}
int main(){
	pthread_t thread1;
	pthread_create(&thread1, NULL, scheduling, NULL);
	pthread_join(thread1, NULL);
    return 0;
}

void *scheduling(void *args){
	int burst_time[20],arrival[20];
     int i, j, t, sum_bt = 0;
     char c;
     float avgwt = 0, avgtt = 0;
      printf("Enter Total Number of Processes:\t");
      scanf("%d", &n);
      printf("\nEnter Burst Time  and arrival time For %d Processes\n", n);
      for(i = 0; i < n; i++)
      {
            printf("\nProcess[%d]\n", i + 1);
            printf("Process Burst Time:\t");
            scanf("%d", &burst_time[i]);

            printf("Process Arrival-Time:\t");
            scanf("%d", &arrival[i]);
      }
	    for (i = 0; i < n; i++) {
	    	 p[i].name = i+1;

        p[i].arT = arrival[i];
        p[i].brT =burst_time[i];

        // Variable for Completion status
        // Pending = 0
        // processed = 1
        p[i].processed = 0;

        // Variable for sum of all Burst Times
        sum_bt += p[i].brT;
    }

    // Sorting the structure by arrival times
    sortTheArrival();
    printf("\nName\tArrival Time\tBurst Time\tWaiting Time");
    printf("\tTurnAround Time\t");
    for (t = p[0].arT; t < sum_bt;) {

        // Set lower bound to Priority
        float priority = -1;

        // Priority Variable
        float temp;

        // Variable to store next processs selected
        int location;
        for (i = 0; i < n; i++) {

            // Checking if process has arrived and is Incomplete
            if (p[i].arT <= t && p[i].processed != 1) {

                // Calculating Priority
                temp = 1+ (t - p[i].arT) / p[i].brT;

                // Checking for Highest Priority
                if (priority < temp) {

                    // Storing Priority
                    priority = temp;

                    // Storing Location
                    location = i;
                }
            }
        }

        // Update time value
        t += p[location].brT;

        // Calculation of waiting time
        p[location].wrT = t - p[location].arT - p[location].brT;

        // Calculation of Turn Around Time
        p[location].trT = t - p[location].arT;

        // Sum Turn Around Time for average
        avgtt += p[location].trT;

        // Updating Completion Status
        p[location].processed = 1;

        // Sum Waiting Time for average
        avgwt += p[location].wrT;
        printf("\n%d\t\t%d\t\t", p[location].name,p[location].arT);
        printf("%d\t\t%d\t\t", p[location].brT, p[location].wrT);
        printf("%d\t", p[location].trT);
    }
    printf("\nAverage waiting time:%f\n", avgwt / n);
    printf("Average Turn Around time:%f\n", avgtt / n);
    printf("Average total time:%f\n", (avgtt+avgwt) / n);		
}
