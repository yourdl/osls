#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
		
void sort(int arr[30],int n)
{
	int i,j,temp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-1;j++)
		{
			if(arr[j]>arr[j+1])
			{
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
	printf("\n Ascending Order \n");
	for(i=0;i<n;i++)
		printf("\t%d",arr[i]);
	printf("\n\n\n");
}

void forkeg()
{
 	int arr[25],arr1[25],n,i,status;
 	printf("\nEnter the no of values in array");
 	scanf("%d",&n);
 	printf("\nEnter the array elements");
 	for(i=0;i<n;i++)
    		scanf("%d",&arr[i]);
 	int pid=fork();
  	if(pid==0)
   	{
      		sleep(10);
      		printf("\nchild process\n");
      		printf("child process id=%d\n",getpid());
      		sort(arr,n);
       		printf("\nElements Sorted Using bubble Sort");
     		printf("\n");
       		for(i=0;i<n;i++)
    			printf("%d,",arr[i]);
    		printf("\b");
     		printf("\nparent process id=%d\n",getppid());
     		//system("ps -x");
       }    
      else
       {
     		printf("\nparent process\n");
     		printf("\nparent process id=%d\n",getppid());
	 	sort(arr,n);	      
		printf("Elements Sorted Using Bubble Sort");
     		printf("\n");
      		for(i=0;i<n;i++)
    			printf("%d,",arr[i]);
    		printf("\n\n\n"); 
      } 
 }     
 int main()
 {
   	forkeg();
   	return 0;
 }
