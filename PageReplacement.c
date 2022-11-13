#include<stdio.h>
#include<stdlib.h>
int choice,pagefaults=0;
int pages[50],frames[20];

void clearf(int frame[],int n)
{
  int i;
  for(i=0;i<n;i++)
  {
    frame[i]=-1;
  }
}

void menu()
{
    printf("\n\n\n\n**************MENU****************");
    printf("\nPage Replacement Algorithms");
    printf("\n1. First In First Out");
    printf("\n2. Least Recently Used");
    printf("\n3. Optimal Replacement");
    printf("\n4. Exit");
    printf("\nEnter Your Choice:");
    scanf("%d", &choice);
}

void accept(int ref[],int n)
{
    int i;
    printf("\nEnter Elements of Reference string one by one::");
    for(i=0;i<n;i++)
    {
        scanf("%d",&ref[i]);
    }
}

void display(int ref[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("%3d",ref[i]);
    }
}

int search(int frame[],int x,int fs)
{
    int i;
    for(i=0;i<fs;i++)
    {
        if(frame[i]==x)
        {
            return 1;
        }
    }return 0;
}

void fifo(int ref[],int n)
{
    int frame[10];
    int i,k,fs,temp,cnt;
    printf("\nEnter Frame Size::");
    scanf("%d",&temp);
    cnt=k=fs=0;
    

    for(i=0;i<n;i++)
    {
        if(search(frame,ref[i],fs)==0)
        {
            frame[k]=ref[i];
            k=(k+1)%temp;
            cnt++;
            if(cnt<temp)
            {
                fs=cnt;
            }else{
                fs=temp;
            }printf("\n\nFor Page %d::\t",ref[i]);
            display(frame,fs);
        }else{
            printf("\n\nFor Page %d::\t",ref[i]);
            printf(" NO Page Fault");
        }
    }printf("\n\nTotal No. of Page Faults = %d",cnt);
}

void lru(int ref[],int n)
{
    int frame[30],pos[30];
    int i,j,k,fs,temp,cnt,min;
    printf("\nEnter Frame Size::");
    scanf("%d",&fs);
    cnt=k=0;
    clearf(frame,fs);

    for(i=0;i<fs && i<n;i++)
    {
        if(search(frame,ref[i],i)==0)
        {
            frame[k++]=ref[i];
            cnt++;
            printf("\n\nFor Page %d ::\t",ref[i]);
            display(frame,k);
        }else{
            printf("\n\nFor Page %d::\t",ref[i]);
            printf(" NO Page Fault");
        }
    }
    for(;i<n;i++)
    {
        if(search(frame,ref[i],fs)==0)
        {
            for(j=0;j<fs;j++)
            {
                for(k=i-1;k>=0;k--)
                {
                    if(frame[j]==ref[k])
                    {
                        break;
                    }
                }pos[j]=k;
            }
            k=0;
            min=pos[0];
            for(j=1;j<fs;j++)
            {
                if(min>pos[j])
                {
                    min=pos[j];
                    k=j;
                }
            }frame[k]=ref[i];
            cnt++;
            printf("\n\nFor Page %d ::\t",ref[i]);
            display(frame,fs);
        }else{
            printf("\n\nFor Page %d::\t",ref[i]);
            printf(" NO Page Fault");
        }
    }printf("\n\nTotal No. of Page Faults = %d",cnt);
}

void optimal(int ref[],int n)
{
    int frame[30],pos[30];
    int i,j,k,fs,temp,cnt,max;
    printf("\nEnter Frame Size::");
    scanf("%d",&fs);
    clearf(frame,fs);
    cnt=k=0;

    for(i=0;i<fs && i<n;i++)
    {
        if(search(frame,ref[i],i)==0)
        {
            frame[k++]=ref[i];
            cnt++;
            printf("\n\nFor Page %d ::\t",ref[i]);
            display(frame,k);
        }else{
            printf("\n\nFor Page %d::\t",ref[i]);
            printf(" NO Page Faults");
        }
    }
    for(;i<n;i++)
    {
        if(search(frame,ref[i],fs)==0)
        {
            for(j=0;j<fs;j++)
            {
                for(k=i+1;k<n;k++)
                {
                    if(frame[j]==ref[k])
                    {
                        break;
                    }
                } pos[j]=k;
            }
            k=0;
            max=pos[0];
            for(j=1;j<fs;j++)
            {
                if(max<pos[j])
                {
                    max=pos[j];
                    k=j;
                }
            }frame[k]=ref[i];
            cnt++;
            printf("\n\nFor Page %d ::\t",ref[i]);
            display(frame,fs);
        }else{
            printf("\n\nFor Page %d::\t",ref[i]);
            printf(" NO Page Faults");
        }
    }printf("\n\nTotal No. of Page Faults = %d",cnt);
}

int main()
{
    int ref[50],n;

    printf("Enter the size of reference string::");
    scanf("%d",&n);
    accept(ref,n);

    while (1)
    {
        menu();
        switch (choice)
        {
        case 1:
            display(ref,n);
            fifo(ref,n);
            break;
        case 2:
            display(ref,n);
            lru(ref,n);
            break;
        case 3:
            display(ref,n);
            optimal(ref,n);
            break;
        case 4:
            exit(0);
            break;
        }
    }
}

