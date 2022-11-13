#include<stdio.h>
#include<stdlib.h>
int max[10][10],allocation[10][10],need[10][10],avail[10];
int np,nr;

void readmatrix(int matrix[10][10])
{
    int i,j;
    for(i=0;i<np;i++)
    {
        for(j=0;j<nr;j++)
        {
            scanf("%d",&matrix[i][j]);
        }
    }
}

void calculate_need()
{
    int i,j;
    for(i=0;i<np;i++)
    {
        
        for(j=0;j<nr;j++)
        {
            need[i][j]=max[i][j]-allocation[i][j];
        }
    }
}

void bankers()
{
    int i,j,k=0,flag;
    int finish[10],safe_seq[10];
    for(i=0;i<np;i++)
    {
        finish[i]=0;
    }
   
    for(i=0;i<np;i++)
    {
        flag=0;
        if(finish[i]==0)
        {
            for(j=0;j<nr;j++)
            {
                if(need[i][j]>avail[j])
                {
                    flag=1;
                    break;
                }
            }
            if(flag==0)
            {
                finish[i]=1;
                safe_seq[k]=i;
                k++;

                for(j=0;j<nr;j++)
                {
                    avail[j]+=allocation[i][j];
                    i--;
                }
            }
        }
    }
    flag=0;
    for(i=0;i<np;i++)
    {
        if(finish[i]==0)
        {
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        printf("\n The system is in safe state!  \n The safe sequence is ==>");
        for(i=0;i<np;i++)
        {
            printf(" P%d",safe_seq[i]);
        }
    }else{
        printf("\n The system is in Deadlock state...!!!");
    }
}

void display_matrix(int matrix[10][10])
{
    int i,j;
    for(i=0;i<np;i++)
    {
        printf("\n P%d",i);
        for(j=0;j<nr;j++)
        {
            printf(" %d",matrix[i][j]);
        }
    }
}

int main()
{
    int j;
    printf("\nEnter the no. of processes ");
    scanf("%d",&np);
    printf("\nEnter the no. of resources ");
    scanf("%d",&nr);
    printf("\nEnter the intial allocation matrix ");
    readmatrix(allocation);
    printf("\nEnter the maximum requirement matrix ");
    readmatrix(max);
    printf("\nEnter the available resources ");
    for(j=0;j<nr;j++)
    {
        scanf("%d",&avail[j]);
    }
    
    printf("\n  ***********Entered Data is ************\n\n");
    printf("\n Initial allocation: \n");
    display_matrix(allocation);
    printf("\n\n\n Maximum Requirement\n");
    display_matrix(max);
    printf("\n Available Resources\n");
    for(j=0;j<nr;j++)
    {
        printf("%d",avail[j]);
    }
    
    calculate_need();
    printf("\n\n\n Need is \n");
    display_matrix(need);

    bankers();
    printf("\n\n\n\n\n");
}