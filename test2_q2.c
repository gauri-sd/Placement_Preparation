#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct process_info
{
        char pname[20];
        int AT,BT,TAT,WT,TBT,CT;
};

struct process_info p[100];

struct gantt_chart
{
        char pname[20];
        int ST,ET;
};

struct gantt_chart g[100];

int gcnt=0,n,totalTAT,totalWT;
float avgTAT=0.0f,avgWT=0.0f;

int isDone()
{
        int i;
        for(i=0;i<n;i++)
        {
                if(p[i].TBT!=0)
                        return 0;
        }
        return 1;
}

int isArrived(int time)
{
        int max=000,i,pos,flag=0;
        for(i=0;i<n;i++)
        {
                if(p[i].TBT!=0 && p[i].AT<=time)
                {
                        if(p[i].TBT>max)
                        {
                                pos=i;
                                max=p[i].BT;
                                flag=1;
                        }
                }
        }
        if(flag==1)
                return pos;
        else
                return -1;
}
void accept()
{
        int i;
        printf("\nHow many process you have= ");
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
                printf("\nEnter process name:");
                scanf("%s",p[i].pname);
                printf("\nEnter Arrival time:");
                scanf("%d",&p[i].AT);
                printf("\nEnter Burst time:");
                scanf("%d",&p[i].BT);
                p[i].TBT=p[i].BT;
        }

}
void ljfnp()
{
        int time=0,i;
        gcnt=0;
        while(!isDone())
        {
                if((i=isArrived(time))!=-1)
                {
                        g[gcnt].ST=time;
                        strcpy(g[gcnt].pname,p[i].pname);
                        g[gcnt].ET=time+p[i].TBT;
                        gcnt++;
                        time=time+p[i].TBT;
                        p[i].TBT=0;
                }
                else
                {
                        g[gcnt].ST=time;
                        strcpy(g[gcnt].pname,"CPU_IDLE");
                        g[gcnt].ET=time+1;
                        gcnt++;
                        time++;
                }
        }
}
void calculate()
{
        int ct=0,i,j;
        for(i=0;i<n;i++)
        {
                for(j=0;j<gcnt;j++)
                {
                        if(strcmp(p[i].pname,g[j].pname)==0)
                        {
                                ct=g[j].ET;
                        }
                }
                p[i].CT=ct;
        }
        for(i=0;i<n;i++)
        {
                p[i].TAT=p[i].CT-p[i].AT;
                p[i].WT=p[i].TAT-p[i].BT;
                totalTAT=totalTAT+p[i].TAT;
                totalWT=totalWT+p[i].WT;
        }
        avgTAT=(float)(totalTAT/n);
        avgWT=(float)(totalWT/n);
}
void display()
{
        int i=0;
        printf("\n\nPname\tAT\tBT\tTAT\tWT");
        for(i=0;i<n;i++)
        {
                printf("\n%s\t%d\t%d\t%d\t%d",p[i].pname,p[i].AT,p[i].BT,p[i].TAT,p[i].WT);
        }
	printf("\n\nGANTT CHART\n");
        for(i=0;i<gcnt;i++)
        {
                printf("\n%d\t%s\t%d",g[i].ST,g[i].pname,g[i].ET);
        }
        printf("\nTotal TAT= %d",totalTAT);
        printf("\nTotal WT= %d",totalWT);
        printf("\nAverage TAT= %f",avgTAT);
        printf("\nAverage WT= %f",avgWT);

}
int main()
{
        int i;
        accept();
        printf("\nPname\tAT\tBT");
        for(i=0;i<n;i++)
        {
                printf("\n%s\t%d\t%d",p[i].pname,p[i].AT,p[i].BT);
        }
        ljfnp();
        calculate();
        display();
}
