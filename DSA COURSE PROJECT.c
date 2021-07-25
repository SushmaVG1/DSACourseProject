#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#define max 100
#define V 11
struct air_p
{
    char src[max];
    char code[max];
};
struct air
{
    int i;
    char src[max];
    char dest[max];
    char time[max];
    char day[max];
    int seats;
    int price;
};
int match[11]={8556,9025,9236,9152,7226,8726,7634,9005,9129,8023,8358};
char name[15][11]={"MUMBAI","BENGALURU","KOLKATA","RANCHI","CHENNAI","LUCKHNOW","AHMEDABAD","AMRITSAR","PATNA","JAIPUR","DELHI"};
char CODE[max],SRC[max],DEST[max],src[max],dest[max];
int g=0,r=100,c=7,flag=0,check;
int graph[V][V] = { { 0,7400,9600,7445,1500,4500,12000,5210,14000,5293,1450 },
                        { 7000,0,5212,5213,5214,5216,5217,5218,5219,5299,5215 },
                        { 5220,5221,0,5222,5223,5225,5226,5227,5228,5297,5224 },
                        { 5229,5230,5231,0,5232,5234,5235,5236,5237,5295,5233},
                        { 5238,5239,5240,5241,0,5243,5244,5245,5246,INT_MAX,5242},
                        { 5256,5257,5258,5259,5260,0,5262,5263,5264,INT_MAX,5261},
                        { 5265,5266,5267,5268,5269,5271,0,5272,5273,INT_MAX,5270},
                        { 5274,5275,5276,5277,5278,5280,5281,0,5282,INT_MAX,5279},
                        { 5283,5284,5285,5286,5287,5289,5290,5291,0,INT_MAX,5288},
                        { 5292,5298,5296,5294,INT_MAX,INT_MAX,INT_MAX,INT_MAX,5300,0,INT_MAX},
                        { 5247,5248,5249,5250,5251,5252,5253,5254,5255,INT_MAX,0}};
int dist[V],par[V],sptSet[V],par[V],avlbl[V][V];
struct air a[max];
void load(struct air a[max])
{
    int l,k;
    const char s[2]={','};
    char *tok;
    FILE *fp;
    char buff[max];
    fp=fopen("airplane_details.csv","r");
    if(fp==NULL)
    {
        printf("File not present\n");
    }
    for(int j=0;j<r;j++)
    {
        l=0;
        fscanf(fp,"%d",&k);
        fgets(buff,max,fp);
        a[j].i=k;
        tok=strtok(buff,s);
        strcpy(a[j].src,tok);
        while(l<c-2)
        {
            tok=strtok(NULL,s);
            if(l==0)
                strcpy(a[j].dest,tok);
            if(l==1)
                strcpy(a[j].time,tok);
            if(l==2)
                strcpy(a[j].day,tok);
            if(l==3)
                a[j].seats=atoi(tok);
            if(l==4)
                a[j].price=atoi(tok);
            l++;
        }
    }
    fclose(fp);
}
void computeLPSArray(char* pat, int M, int* lps)
{
	int len = 0;
	lps[0] = 0;
	int i = 1;
	while (i < M)
    {
		if (pat[i] == pat[len])
        {
			len++;
			lps[i] = len;
			i++;
		}
		else
		{
			if (len != 0)
            {
				len = lps[len - 1];
			}
			else
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}
int KMPSearch(char* pat, char* txt)
{
	int M = strlen(pat);
	int N = strlen(txt);
	int lps[M];
	computeLPSArray(pat,M,lps);
	int i = 0;
	int j = 0;
	while (i < N)
    {
		if (pat[j] == txt[i])
        {
			j++;
			i++;
		}

		if (j == M)
        {
			g++;
			j = lps[j - 1];
		}
		else if (i < N && pat[j] != txt[i])
        {
			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}
}
int driver_kmp(char *a, char *b)
{
    g=0;
	KMPSearch(a,b);//searching for A in B
	if(g==1)
        return 1;
	else
        return 0;
}
int find_code(char find_src[max],int r)
{
    FILE *fp;
    fp=fopen("airplane_code.txt","r");
    char buff[max],q[2]={'_'};
    char *tok;
    int k=0,x;
    struct air_p ap;
    for(int i=1;i<=r;i++)
    {
        fgets(buff,max,fp);
        tok=strtok(buff,q);
        strcpy(ap.src,tok);
        tok=strtok(NULL,q);
        strcpy(ap.code,tok);
        x=driver_kmp(strlwr(ap.src),strlwr(find_src));
        if(x==0)
            k=0;
        else
        {
            k=1;
            if(!strcmp(src,find_src))
                strcpy(SRC,ap.code);
            if(!strcmp(dest,find_src))
                strcpy(DEST,ap.code);
            fclose(fp);
            return 1;
        }
    }
    if(k==0)
    {
        printf("Airport not found.\nPlease re-enter valid airport name\n");
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return k;
}
int hash(char code[max])
{
       int s=0;
       for(int i=0;i<strlen(code);i++)
      {
          s+=code[i]*pow(10,i);
      }
      return s;
}
struct air write(int h,char des[max])
{
    struct air a;
    int r=100,l,k,c=7;
    const char s[2]={','};
    char *tok;
    FILE *fp;
    char buff[max];
    fp=fopen("airplane_details.csv","r");
    for(int j=0;j<r;j++)
    {
        l=0;
        fscanf(fp,"%d",&k);
        fgets(buff,max,fp);
        if(k==h)
        {
            a.i=k;
            tok=strtok(buff,s);
            strcpy(a.src,tok);
            while(l<c-2)
            {
                tok=strtok(NULL,s);
                if(l==0)
                    strcpy(a.dest,tok);
                if(l==1)
                    strcpy(a.time,tok);
                if(l==2)
                    strcpy(a.day,tok);
                if(l==3)
                    a.seats=atoi(tok);
                if(l==4)
                    a.price=atoi(tok);
                l++;
            }
            int temp;
            temp=driver_kmp(strlwr(a.dest),strlwr(des));
            if(temp)
            {
                flag=1;
                printf("\n\n*****FLIGHT DETAILS*****\nSOURCE: %s\nDESTINATION: %s\nDAY OF JOURNEY: %s\nDEPARTURE TIME: %s\nNO OF SEATS AVAILABLE: %d\nTICKET PRICE: %d\n************************\n\n",a.src,strupr(a.dest),a.time,a.day,a.seats,a.price);
                fclose(fp);
                return a;
            }
            else
                continue;
        }
    }
    if(flag==0)
        printf("Direct flights unavailable\n***************\n\n");
    fclose(fp);
    return a;
}
int book_ticket(struct air ap)
{
    int tckt,b;
    char c;
    printf("Enter the number of tickets to be booked:  ");
    scanf("%d",&tckt);
    if(ap.seats<tckt)
    {
        b=0;
        printf("%d seats are unavailable\n",tckt);
        return b;
    }
    else
    {
        printf("Total cost would be Rs. %d/-\n",ap.price*tckt);
        printf("Do you want to confirm tickets?(Y/N) ");
        fflush(stdin);
        scanf("%c",&c);
        if(c=='Y'||c=='y')
        {
            b=1;
            printf("%d seats successfully booked:)\n**********************\n\n",tckt);
            ap.seats-=tckt;
        }
        else
        {
            printf("\n*******************\n");
            b=0;
        }
    }
    return b;
}
int search(int match[11],int key)
{
    for(int i=0;i<11;i++)
    {
        if(key==match[i])
            return i;
    }
}
int minDistance(int dist[],int sptSet[])
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}
int find(char s[max],char d[max])
{
    for(int i=0;i<r;i++)
    {
        if(driver_kmp(s,a[i].src)&&driver_kmp(d,a[i].dest))
        {
            printf("\n\n*****FLIGHT DETAILS*****\nSOURCE: %s\nDESTINATION: %s\nDAY OF JOURNEY: %s\nDEPARTURE TIME: %s\nNO OF SEATS AVAILABLE: %d\nTICKET PRICE: %d\n************************\n\n",a[i].src,strupr(a[i].dest),a[i].time,a[i].day,a[i].seats,a[i].price);
            return a[i].seats;
        }
    }
}
int printSolution(int graph[V][V],int par[V],int src,int dest)
{
    int sum=0,seats[5],k=0,price[5],tckt;
    char ch,c;
    printf("\n*******************\n");
    for(int i=dest;par[i]!=-1;i=par[i])
    {
        sum+=graph[par[i]][i];
        printf("%s -> %s with price Rs.%d\n",name[par[i]],name[i],graph[par[i]][i]);
        seats[k]=find(name[par[i]],name[i]);
        price[k]=graph[par[i]][i];
        k++;
    }
    printf("\n\nDo you want to book ticket?(Y/N) ");
    fflush(stdin);
    scanf("%c",&ch);
    if(ch=='Y'||ch=='y')
    {
        printf("Enter no of tickets to be booked: ");
        fflush(stdin);
        scanf("%d",&tckt);
        if(seats[0]>=tckt&&seats[1]>=tckt)
        {
            printf("Total expense would be Rs. %d/-\n",(price[0]+price[1])*tckt);
            printf("Do you want to confirm ticket?(Y/N) ");
            fflush(stdin);
            scanf("%c",&c);
            if(c=='Y'||c=='y')
            {
                printf("%d tickets successfully booked:)\n**********************\n\n\n",tckt);
                return 0;
            }
            else
                printf("\n\n*******************\n\n");
        }
        else
            printf("%d seats unavailable\n\n***********************\n\n",tckt);
    }
    else
        printf("\n\n*****************\n\n");
    return 0;
}
void dijkstra(int src,int dest)
{
        for (int i = 0; i < V; i++)
            dist[i] = INT_MAX, sptSet[i] = 0;
        dist[src] = 0;
        par[src]=-1;
        avlbl[src][dest]=1;
        for (int count = 0; count < V - 1; count++)
        {
            int u = minDistance(dist, sptSet);
            sptSet[u] =1;
            for (int v = 0; v < V; v++)
                if (!sptSet[v] && graph[u][v]!=INT_MAX && dist[u] != INT_MAX&& dist[u] + graph[u][v] < dist[v]&&avlbl[u][v]!=1)
                 {
                     dist[v] = dist[u] + graph[u][v];
                     par[v]=u;
                 }
        }
        printSolution(graph,par,src,dest);
    return;
}
int main()
{
    int ch,h,b,src_hash,dest_hash,si,di;
    char c;
    struct air ap;
    printf("WELCOME!!!\n");
    load(a);
    while(1)
    {
        fflush(stdin);
        printf("AIRPORTS AVAILABLE: \tBENGALURU\tCHENNAI\t\tPATNA\n\t\t\tLUCKHNOW\tAMRITSAR\tMUMBAI\n\t\t\tKOLKATA\t\tRANCHI\t\tDELHI\n\t\t\tJAIPUR\t\tAHMEDABAD\n");
        printf("\n\nEnter source : ");
        scanf("%s",src);
        if(find_code(src,11))
        {
            printf("Enter destination : ");
            scanf("%s",dest);
            if(find_code(dest,11))
            {
                printf("\nEnter 1 for direct flight\nEnter 2 for connecting flights\n");
                scanf("%d",&ch);
                switch(ch)
                {
                    case 1: h=hash(SRC);
                            ap=write(h,dest);
                            if(flag)
                            {
                                printf("\nDo you want to book tickets of this flight?(Y/N) ");
                                fflush(stdin);
                                scanf("%c",&c);
                                if(c=='Y'||c=='y')
                                {
                                    book_ticket(ap);
                                    printf("\n\n*****FLIGHT DETAILS*****\nSOURCE: %s\nDESTINATION: %s\nDAY OF JOURNEY: %s\nDEPARTURE TIME: %s\nNO OF SEATS AVAILABLE: %d\nTICKET PRICE: %d\n************************\n\n",ap.src,strupr(ap.dest),ap.time,ap.day,ap.seats,ap.price);

                                }
                                else
                                    printf("*******************\n");
                            }
                            break;
                    case 2: src_hash=hash(SRC);
                            dest_hash=hash(DEST);
                            si=search(match,src_hash);
                            di=search(match,dest_hash);
                            dijkstra(si,di);
                            break;
                    default: printf("Please enter valid inputs\n");
                }
            }
        }
    }
    printf("Thank you for visiting!!!");
    return 0;
}
