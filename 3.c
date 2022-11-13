#include<stdio.h>
#include<stdlib.h>
int burst_time[10],arrival_time[10],remaining_burst_time[10],finish[10],process_name[10],waiting_time[10],turnaround_time[10];
int n,pending,time,count,choice,z=0;

void menu(){
    printf("\n\n\n\n*******MENU*****");
    printf("\n1. Round Robin");
    printf("\n2. SJF");
    printf("\n3. Exit");
    printf("\nEnter Your Choice:");
    scanf("%d",&choice);
}

void input(){
    int i;
    printf("\nEnter the no. of process ");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        process_name[i]=i;
        printf("\nEnter the Arrival Time of Process %d:",process_name[i]);
        scanf("%d",&arrival_time[i]);
        printf("\nEnter the Burst Time of Process %d:",process_name[i]);
        scanf("%d",&burst_time[i]);
        remaining_burst_time[i]=burst_time[i];
    }
}

void sort(){
    int i,j,t;
    for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++){
            if(remaining_burst_time[i]<remaining_burst_time[j]){
                t=burst_time[i];
                burst_time[i]=burst_time[j];
                burst_time[j]=t;

                t=remaining_burst_time[i];
                remaining_burst_time[i]=remaining_burst_time[j];
                remaining_burst_time[j]=t;

                t=arrival_time[i];
                arrival_time[i]=arrival_time[j];
                arrival_time[j]=t;

                t=waiting_time[i];
                waiting_time[i]=waiting_time[j];
                waiting_time[j]=t;

                t=process_name[i];
                process_name[i]=process_name[j];
                process_name[j]=t;

                t=finish[i];
                finish[i]=finish[j];
                finish[j]=t;
            }
        }
    }
}

void output(){
    int i;
    printf("\n\n\nProcess A.T. B.T. W.T. T.A.T.");
    for(i=0;i<n;i++){
        printf("\n P%d \t %d \t %d \t %d \t %d",process_name[i],arrival_time[i],burst_time[i],waiting_time[i],turnaround_time[i]);
    }
    return;
}

void round_robin(){
    int time_quantum,i;
    input();
    pending=n;

    printf("\n Enter time quantum ");
    scanf("%d",&time_quantum);
    printf("\nTime quantum taken successfully");
    printf("\nGantt Chart==> ");
    for(i=0;i<n;i++){
        finish[i]=0;
        waiting_time[i]=0;
    }
    
    for(time=0,count=0;pending>0;){

        if(finish[count]!=1 && arrival_time[count]<=time && remaining_burst_time[count]<=time_quantum){
            time+=remaining_burst_time[count];
            pending--;
            finish[count]=1;
            waiting_time[count]-=arrival_time[count];
            turnaround_time[count]=waiting_time[count]+burst_time[count];

            for(i=0;i<remaining_burst_time[count];i++){
                printf("P%d ",process_name[count]);
            }
            for(i=0;i<n;i++){
                if(i==count || finish[i]==1){
                    continue;
                }else{
                    waiting_time[i]+=remaining_burst_time[count];
                }
            }
            remaining_burst_time[count]=0;
        }else if(finish[count]!=1 && arrival_time[count]<=time && remaining_burst_time[count]>time_quantum){

            time+=time_quantum;
            remaining_burst_time[count]-=time_quantum;
            for(i=0;i<time_quantum;i++){
                printf("P%d ",process_name[count]);
            }

        }
        count=(count+1)%n;
    }
    return;
}

void sjf(){
    int i;
    input();
    pending=n;
    for(i=0;i<n;i++){
        finish[i]=0;
        waiting_time[i]=0;
    }
    printf("Gantt Chart==> ");
    for(time=0,count=0;pending>0;){
        sort();
        for(count=0;count<n;count++){

           if(finish[count]!=1 && arrival_time[count]<=time){
              printf("P%d ",process_name[count]);
              time++;
              remaining_burst_time[count]--;

              for(i=0;i<n;i++){
                if(i==count || finish[i]==1){
                    continue;
                }else{
                    waiting_time[i]++;
                }
            }
            if(remaining_burst_time[count]==0){
                pending--;
                finish[count]=1;
                waiting_time[count]-=arrival_time[count];
                turnaround_time[count]=waiting_time[count]+burst_time[count];
            }
            break;
           }  
        
        }
    }
}


int main(){
    while(1){
        menu();
        switch(choice){
            case 1: round_robin();
                break;
            case 2: sjf();
                break;
            case 3: exit(0);
                break;
        }
    }output();
    return 0;
}