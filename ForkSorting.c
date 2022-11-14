#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

void MergeSort(int a[],int low,int mid,int high)
{
  int i,j,k,l,b[20];
  i=low;
  l=low;
  j=mid+1;

  while(l<=mid && j<=high)
  {
    if(a[l]<=a[j])
    {
        b[i]=a[l++];
    }else{
        b[i]=a[j++];
    }i++;
  }
  while(l<=mid)
  {
    b[i++]=a[l++];
  }
  while(j<=high)
  {
    b[i++]=a[j++];
  }
  for(i=0;i<=high;i++)
  {
    a[i]=b[i];
  }
}

void partition(int a[],int low,int high)
{
    int mid;
    if(low<high)
    {
        mid=(low+high)/2;
        partition(a,low,mid);
        partition(a,mid+1,high);
        MergeSort(a,low,mid,high);
    }

}

void BubbleSort(int a[],int n)
{
    int i,j,t;
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(a[i]>a[j])
            {
             t=a[i];
             a[i]=a[j];
             a[j]=t;
            }
        }
    }
}

void display(int a[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("%d\t\t",a[i]);
    }
    printf("\n");
}

int main()
{
    int pid,child_pid;
    int size,i,status;

    printf("Enter the number of integers to be sorted: ");
    scanf("%d",&size);

    int a[size],pArr[size],cArr[size];
    printf("Enter the Integers to be sorted\n");
    for(i=0;i<size;i++)
    {   
        printf("Enter Number %d: ",(i+1));
        scanf("%d",&a[i]);
        pArr[i]=a[i];
        cArr[i]=a[i];
    }
    printf("Your Entered Integers for Sorting\n");
    display(a,size);
    pid=getpid();
    printf("Current Process ID is: %d",pid);
    printf("[Forking child Process...]\n");
    child_pid=fork();

    if(child_pid<0)
    {
        printf("\nChild Process creation failed...!!!\n");
        exit(-1);
    }else if(child_pid==0)
    {
        printf("\nThe Child Process\n");
        printf("\nChild Process is %d",getpid());
        printf("\nParent of child process is %d",getppid());
        printf("Child is sorting the list of Integer by Bubble Sort::\n");
        BubbleSort(cArr,size);
        printf("The sorted list by child::\n");
        display(cArr,size);
        printf("Child Process Completed...\n");
        sleep(10);
    }else
    {
        printf("Parent process %d started\n",getpid());
        printf("The Parent of Parent is %d\n",getppid());
        sleep(30);
        printf("The Parent Process\n");
        printf("Parent %d is sorting the list of Integers by Merge Sort\n",getpid());
        partition(pArr,0,size-1);
        printf("The sorted list by Parent::\n");
        display(pArr,size);
        printf("Parent Process is Completed...\n");
    }
    return 0;
}