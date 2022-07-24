#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 	25
#define PER	20
#define C 	20
#define run 	500
#define ge 	10
#define TS 	19
#define pro 	2
#define skill 	10

int no_cross=0,no_mutation=0;
//===================================================Sociometric matrix gen===================================
void socio_initial(float weight[pro],int chrom[TS],int soci[N][N],int require[pro][skill+1],float fit[2*C])
{
	int p,q,r,s;
	int sum,sum2=0;
	float eff[pro];
	float geff=0.0;
	
	int i,j,k,l,m;
	int a;
	int n;
	float e1,e2,e3;
	p=0;geff=0.0;
	for( i=0;i<pro;i++)
	{	eff[i]=0;e1=0;e2=0;
		q=p;
		r=q;
		s=q;
		sum=0;
		a=require[i][skill];
		a=a*a;	
		for( j=0;j<require[i][skill];j++)
		{	
			l=chrom[r];
			
			//l=l%1000;
			//printf("%d-",l);
			q=s;
			for(k=0;k<require[i][skill];k++)
			{
				m=chrom[q];
				//m=m%1000;
				//printf(" %d ",m);
				//sum=sum+(float)soci[l-1][m-1];
				soci[l-1][m-1]=1;
				sum=sum+(float)soci[l-1][m-1];
				q++;
				sum2++;
			}
			p++;r++;
		//printf("vivek");
		}
		e1=a;
		//printf("%f",e1);
		e2=sum;
		e2=e2/e1;
		eff[i]=((0.5*(1.0+e2)));
		
		geff=geff+(eff[i]*weight[i]);
	
		
	}
		
	
	printf("optimal fitness %f\n",geff);
	printf("sum2 is %d\n",sum2);
	
}
void sociometric(int socio[N][N])
{
	int b,a,no1=0;
	int total;
	float n=N,p=PER;
	int i,j,k,l,x;
	int count=0;
	int c=0;
	int P;
	P=(int)((n*n*(p/100)));
	total=P;
	P=(int)(P/n);
	a=(int)(N/P);
	printf("%d\n",P);
	for(i=0;i<N;i++){
		socio[i][i]=1;
		}
	for(i=0;i<N;i++)
	{	
		for(j=0;j<N;j++)
		{
			if(socio[i][j]==1)
			no1++;
		}
	}
	
	//b=N/p;
	//p=p-1;
	//a=b;
	
	printf("total: %d ",total);
	for(l=0;l<2;l++)
	{	
		for(i=l;i<N;i=i+2)
		{		
		if(i%2==0)
		{j=1;}
		else{j=0;}
		k=0;
		while(k<P)
		{	if(socio[i][j]!=1){
			socio[i][j]=1;no1++;}
			
			j=j+a;
			k++;
			if(no1>=total)
			break;		
		}if(no1>=total)
			break;
		}if(no1>=total)
			break;
	}printf("\nno1: %d ",no1); 
	/*j=0;x=1;
	for(i=0;i<N;i++)
	{
		if(i%2==0)
		j=1;
		else j=0;
		while(j<=N)
		{
			socio[i][j]=1;
			j=j+4;
		}
	}*/
	/*for (i=0;i<N;i++)
	{	k=0;
		if(x==a)
		{x=1;}
		j=x;
		
		while(k<=p)
		{
			socio[i][j]=1;
			j=j+b-1;
			k++;
		}
		if(b==0)
		{
			b=a;
			}
		else b--;
		x++;
		}*/
	
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			x=rand()%2;
			if(socio[i][j]!=1)
			{
				if(x==1)
				socio[i][j]=-1;
				else
				socio[i][j]=0;
			}
		}
	}
	for(i=0;i<N;i++)
	{for(j=0;j<N;j++)
		{c++;
		if(socio[i][j]==1)
		count++;
		//printf("%d ",socio[i][j]);
		}
		//printf("\n");
	}
	printf("\n%d\n%d\n",count,c);	
}

//======================================================CROSSOVER==========================================
void swapc(int chr[C][TS],int c1,int c2,int supp1[C][N],int i)
{
			int z=0,j,k,temp;
			int a,b;
			j=c1;
			while(j<=c2)
			{	a=chr[i][j];
				k=c1;z=0;
				while(k<=c2)
				{
					b=chr[i+1][k];
					if(a==b){z=1;}
					k++;
				}
				if(z==0)
				{
					a=a%1000;
					supp1[i][a-1]=0;
					supp1[i+1][a-1]=1;
				}j++;
			}
			j=c1;			
			while(j<=c2)
			{	a=chr[i+1][j];
				k=c1;z=0;
				while(k<=c2)
				{
					b=chr[i][k];
					if(a==b){z=1;}
					k++;
				}
				if(z==0)
				{
					a=a%1000;
					supp1[i+1][a-1]=0;
					supp1[i][a-1]=1;
				}j++;
			}		
				
			
			j=c1;
			while(j<=c2)
			{	

				temp=chr[i][j];
				chr[i][j]=chr[i+1][j];
				chr[i+1][j]=temp;
				j++;
			}no_cross++;	//printf("%d-done \n",no_cross);
			

}

void crossover(int chr[C][TS],int supp1[C][N],int supp2[skill][N],int value[skill])
{
	int i,j,k,count=1,x;
	int c1,c2,temp,temp1;
	int flag1,flag2,z=0;
	int a,b;
	for(i=0;i<C;i=i+2)
	{
		c1=1;c2=0;
		flag1=0;flag2=0;		
		while(c1>c2)
		{
			c1=rand()%TS;
			c2=rand()%TS;
		}
		j=c1;
		while(j<=c2)
		{	x=chr[i][j]%1000;
			if(supp1[i+1][x-1]==1)
			{	k=c1;
				count=0;
				temp=chr[i][j];
				while(k<=c2)
				{	temp1=chr[i+1][k];
					if(temp==temp1)
					{count++;z++;}
					k++;
				}
				if(count==0)
				{break;}
			}
			j++;
		}
		
		if(j==(c2+1)&&z!=(c2-c1+1)){
		flag1=1;}
		j=c1;
		z=0;
		while(j<=c2)
		{	x=chr[i+1][j]%1000;
			if(supp1[i][x-1]==1)
			{	k=c1;
				count=0;
				temp=chr[i+1][j];
				while(k<=c2)
				{	temp1=chr[i][k];
					if(temp==temp1)
					{count++;z++;}
					k++;
				}
				if(count==0){
				break;}
				
			}
			j++;
		}	
		if(j==(c2+1)&&z!=(c2-c1+1)){
		flag2=1;}
		if(flag1==1&&flag2==1)
		{
			swapc(chr,c1,c2,supp1,i);}
			
	}
	//printf("\nCROSS-complete\n");
}		

	
//=============================Mutation====================================================
void mutation(int chr[C][TS],int supp1[C][N],int supp2[skill][N],int value[skill],int req[pro][skill+1],int position[pro],int mut)
{	
	int i,j,r,l,m;
	int k,x,y,s,e,f,count=0;
	int temp;
	no_mutation++;
	if(mut==0)
	{
	for(i=0;i<C;i++)
	{
			count=1;
			k=rand()%TS;
			x=chr[i][k];
			s=x/1000;//skill no.
			x=x%1000;//individual
			while(count<=20)
			{
			
			e=rand()%value[s-1];//position in support array
			f=supp2[s-1][e]%1000;//position value in support array
			
			if(supp1[i][f-1]==0)//e sd be f
			{
				supp1[i][x-1]=0;
				supp1[i][f-1]=1;
				chr[i][k]=supp2[s-1][e];
				count=21;
			}
			count++;
			}
			if(count!=22)
			{
				count=0;
				while(count<value[s-1])
				{
					f=supp2[s-1][count]%1000;
					
					if(supp1[i][f-1]==0)//e sd be f
					{
						supp1[i][x-1]=0;
						supp1[i][f-1]=1;
						chr[i][k]=supp2[s-1][count];
						break;
					}
					count++;
			}	}
	}
	}
	else
	{	//srand(time(0));
		/*for(i=0;i<pro;i++)
		{
			printf("%d ",position[i]);
		}printf("\n");*/
	
		l=0;
		for(i=0;i<C;i++)
		{	
			if(l==pro)
			{ l=0;}
			k=rand()%TS;
			x=chr[i][k];
			s=x/1000;	//Skill no.
			x=x%1000;	//Individual
			
			
			
			if(position[l]<=k && k<=(position[l]+req[l][skill+1]))
			{l++;if(l==pro)
				{l=0;}}
			if(req[l][s-1]==0){break;}
			else{m=rand()%req[l][s-1];}
			j=0;
			e=position[l];			
			while(j<s-1)
			{	
				e=e+req[l][j];
				j++;
			}
			temp=chr[i][e+m];
			chr[i][e+m]=chr[i][k];
			chr[i][k]=temp;
			l++;
			
		}	
	}
	//printf("\nMUTA-complete\n");
}
//======================================Selection===========================================
void swap(int i,int j,int cro[C][TS],int croclo[C][TS],int supp[C][N],int supp1[C][N])
{
	int k,temp;
	if(j<C)
	{
	for(k=0;k<N;k++)
	{	if(k<TS){
		temp=cro[i][k];
		cro[i][k]=cro[j][k];
		cro[j][k]=temp;
		}
		temp=supp[i][k];
		supp[i][k]=supp[j][k];
		supp[j][k]=temp;
	}}
	else
	{
		j=j-C;
		for(k=0;k<N;k++)
		{	if(k<TS){
			temp=cro[i][k];
			cro[i][k]=croclo[j][k];
			croclo[j][k]=temp;
				}
				temp=supp[i][k];
				supp[i][k]=supp1[j][k];
				supp1[j][k]=temp;
		}
	}	
}
void selection(int cro[C][TS],int croclo[C][TS],float fit[2*C],int supp[C][N],int supp1[C][N])//Selection function
{	
	int i,j,k;
	float max;
	for( i=0;i<C;i++)
	{	max=fit[i];
		k=i;
		for(j=i;j<2*C;j++)
		{
			if(max<fit[j])
			{
				max=fit[j];
				k=j;
			}
		}
		if(k!=i){
		fit[k]=fit[i];
		fit[i]=max;
		swap(i,k,cro,croclo,supp,supp1);
		}
		
		
	}
	//printf("\nSELEC-complete\n");
}
//====================================for making clone of chromosome=======================================
void clone(int arr[C][TS],int arr1[C][TS],int supp[C][N],int suppc[C][N])
{	int i,j;
	for(i=0;i<C;i++)
		{
		for(j=0;j<N;j++)
		{	if(j<TS)
			arr1[i][j]=arr[i][j];
			suppc[i][j]=supp[i][j];
		}
		}
}
			
int max(int arr[C])
{
	int i,j;
	float m=0.0;
	for(i=0;i<C;i++)
	{
		if(m<arr[i])
		{
			m=arr[i];
			j=i;
		}
	}
	return j;
}

//=============================================Calculating fitness function======================================



void fitness(int pos,float weight[pro],int chrom[C][TS],int soci[N][N],int require[pro][skill+1],float fit[2*C])
{
	int p,q,r,s;
	int sum;
	
	float eff[pro];
	float geff=0.0;
	int i,j,k,l,m;
	int a;
	int n;
	float e1,e2,e3;
	for( n=0;n<C;n++)
	{p=0;geff=0.0;
	for( i=0;i<pro;i++)
	{	eff[i]=0;e1=0;e2=0;
		q=p;
		r=q;
		s=q;
		sum=0;
		a=require[i][skill];
		a=a*a;	
		for( j=0;j<require[i][skill];j++)
		{	
			l=chrom[n][r];
			
			l=l%1000;
			//printf("%d-",l);
			q=s;
			for(k=0;k<require[i][skill];k++)
			{
				m=chrom[n][q];
				m=m%1000;
				//printf(" %d ",m);
				sum=sum+(float)soci[l-1][m-1];
				q++;
				
			}
			p++;r++;
		//printf("vivek");
		}
		
	
		e1=a;
		//printf("%f",e1);
		e2=sum;
		e2=e2/e1;
		eff[i]=((0.5*(1.0+e2)));
		
		geff=geff+(eff[i]*weight[i]);
		//printf(" %f ",geff);
	}
		if(pos==1)
		fit[n]=geff;
		else
		fit[n+C]=geff;
		
	}
	//printf("\n");
	
}

//=============================main()===========================================================================	
				
int main(int argc, char *argv[])
{
	clock_t start,end;
	double cpu_time_used;
	start=clock();
	int socio[N][N];
	int supp[skill][N];
	int req[pro][skill+1];
	int i,j,k,l;
	int chromo[C][TS];
	int chromclone[C][TS];
	int suppo[C][N];
	int suppclone[C][N];
	int x[skill];
	int a,b,c,pos=1;
	float pc=0.6,pm=0.4,fp;
	float prob;
	FILE *fi=fopen(argv[1],"r");
	FILE *fo=fopen(argv[3],"a");
	FILE *fs=fopen(argv[2],"r");
	float w[pro],fitval[2*C];
	float fitplot[1500];
	int support[N];
	int chromoshome[TS];
	int arr[N];
	int flg1=0,flg2=0;
	int position[pro];
	position[0]=0;b=0;
	
	if(argc<4||argc>4){exit(0);}	
	for(i=0;i<pro;i++)
	{	a=0;
		fscanf(fi,"%f",&w[i]);
		for(j=0;j<skill;j++)
		{	
			fscanf(fi,"%d",&req[i][j]);
			a=a+req[i][j];
			b=b+req[i][j];	
		}
		req[i][j]=a;
		position[i+1]=b;
		printf("%d %d\n",b,position[i]);
	}
	

	for(i=0;i<skill;i++)
	{
		fscanf(fi,"%d",&x[i]);
		for(j=0;j<x[i];j++)	
		{
			fscanf(fi,"%d",&supp[i][j]);
		}
	}
		for(j=0;j<C;j++){
			for(k=0;k<N;k++)
			{
				suppo[j][k]=0;
				suppclone[j][k]=0;
				
			}}
	//for(i=0;i<N;i++)
	//{fscanf(fi,"%d",&chromoshome[i]);}	
	
	
	//socio_initial(w,chromoshome,socio,req,fitval);
	//sociometric(socio);
	for(i=0;i<pro;i++)
	{printf("%f ",w[i]);}printf("\n");

	for(i=0;i<pro;i++)
	{
		for(j=0;j<skill;j++)
		{
			printf("%d ",req[i][j]);
		}printf("\n");
	}
	printf("\n");
	
	for(i=0;i<skill;i++)
	{
		printf("%d\n",x[i]);
		for(j=0;j<x[i];j++)
		{
			printf("%d ",supp[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			fscanf(fs,"%d",&socio[i][j]);
			//printf("%d ",socio[i][j]);
		}//printf("\n");
	}		
	fscanf(fs,"%d",&i);
	fscanf(fs,"%d",&j);
	printf("\n: %d\n: %d\n",i,j);
	//printf("\n");
	/*for(i=0;i<N;i++)		//sociomatrix generation
	{
		for(j=0;j<N;j++)
		{
			
			printf("%d ",socio[i][j]);
		}
		printf("\n");
	}	
	exit(0);*/

	srand(time(0));
	printf("input has accepted\n");
	int v=0;
	for(l=0;l<C;l++)
	{
		v=0;
		for(i=0;i<pro;i++)
		{
			for(j=0;j<skill;j++)
			{
				for(k=0;k<req[i][j];k++)
				{	
					c=1;
					while(c<20)
					{
					b=x[j];
					a=rand()%b;
					b=supp[j][a];
					b=b%1000;
					if(suppo[l][b-1]==0)
					{
						suppo[l][b-1]=1;
						chromo[l][v]=supp[j][a];
						c=22;
						v++;
					}c++;
					}
					if(c!=23)
					{	
							
						a=0;c=1;
						while(c!=0&&a<x[j])
						{
							b=supp[j][a];
							b=b%1000;
							if(suppo[l][b-1]==0)
							{
								suppo[l][b-1]=1;
								chromo[l][v]=supp[j][a];
								c=0;
								v++;
							}a++;
						}
						
						}
				}
			}
		}
	}						
	
	printf("\n=========================================Initial Population===================================================\n\n");														
	for(i=0;i<C;i++)
	{
		for(j=0;j<TS;j++)
		{
			printf("%d ",chromo[i][j]);
		}
		printf("\n\n");
	}
	
	//printf("required set\n");
/*===============================================================================
	for(i=0;i<p;i++)
	{
		for(j=0;j<4;j++)
		{
			printf("%d ",req[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<35;i++)
	{
		for(j=0;j<35;j++)
		{
			printf("%d ",socio[i][j]);
		}
		printf("\n");
	}
*/
	printf("vivek");



	fitness(pos,w,chromo,socio,req,fitval);
	
	clone(chromo,chromclone,suppo,suppclone);
	//printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@22");
	fitplot[0]=fitval[0];//for ploting 
	for( i=0;i<C;i++)
	{
		printf(" %f ",fitval[i]);
	}
	printf(" %f ",fitval[0]);
	
	int gino=0,plot=0,mut=0;
	pos++;
	fitness(pos,w,chromclone,socio,req,fitval);
	
	printf("\n\nWAIT FOR A WHILE.................\n");
	mut=0;
	for(i=0;i<run;i++)//run
	{	//printf("\n================%d Run",i+1);
		
		for(j=0;j<ge;j++)//generation
		{	
			flg1=0;flg2=0;			
			clone(chromo,chromclone,suppo,suppclone);
			prob=(float)(rand()%10)/10.0;
			//printf("\n$$$$$$$$PROB:  %f$$$$$$$$$$$\n",prob);
			
			if(prob<=pc)
			{flg1=1;
			crossover(chromclone,suppclone,supp,x);
			//printf("C-");
			}
			if(prob<=pm)
			{flg2=1;
				//if(j%2==0){
				//mut=1;}
				if(mut==0)
				{mut=1;}
				 else{mut=0;}
			mutation(chromclone,suppclone,supp,x,req,position,mut);
			//printf("M\n");
			}

			if(flg1==1||flg2==1)
			{
			fitness(pos,w,chromclone,socio,req,fitval);
			selection(chromo,chromclone,fitval,suppo,suppclone);
			}
			gino++;
			//printf("%d generation  efficiency is: %f",j+1,fitval[0]);
			//printf("%f ",fitval[0]);
			if(((j+1)%5)==0)
			{
				plot++;
				fitplot[plot]=fitval[0];}
	
		}
		
	}
	printf("\n====================================================Final population=========================================\n\n");
	for(i=0;i<C;i++)
	{
		for(j=0;j<TS;j++)
		{
			printf("%d ",chromo[i][j]);
		}
		printf("\n\n");
	}
	printf("\n\n");
/*
for(i=0;i<20;i++)
	{
		for(j=0;j<28;j++)
		{
			printf("%d ",chromclone[i][j]);
		}
		printf("\n\n");
	}*/
	printf("\n\n");
	
	printf("Total No. of Iteration:%d\n",gino);


	printf("\n");
	for( i=0;i<2*C;i++)
	{
		printf(" %f ",fitval[i]);
	}

	int z=0;
	printf("\nFittest team will be in given data set:\n\n");
	fprintf(fo,"Team is: ");

	for(i=0;i<N;i++)
	{arr[i]=0;}
	
	for(i=0;i<TS;i++)
	{	k=chromo[0][i]%1000;
		if(arr[k-1]==0){
			arr[k-1]=1;}
		else{	j=chromo[0][i];
			z=1;}
		
		printf("%d ",chromo[0][i]);
		fprintf(fo,"%d ",chromo[0][i]);
	}
	printf("\n");
	fprintf(fo,"\n");
	for(i=0;i<1000;i++)
	{
		fprintf(fo,"%f ",fitplot[i]);
	}
	printf("\nFinal Global Efficiency: %f\n\n ",fitplot[999]);
	fprintf(fo,"\n");
			
	/*=================================================for(i=0;i<10;i++)
	{
		for(j=0;j<20;j++)
		{
			
	prob=(rand()%10)/10;
	if(prob<pm)
	{
		mutation();
	}
	else if(
	*/
	//for(i=0;i<20;i++)
	//{
	//	for(j=0;j<29;j++)
	//	{
	//		printf("%d ",chromo[i][j]);
	//	}
	//	printf("\n\n");
	//}

	/*printf("support set\n");
	for(i=0;i<3;i++)
	{
		for(j=0;j<20;j++)
		{
			printf("%d ",supp[i][j]);
		}
		printf("\n");
	}

	for(i=0;i<3;i++)
	{
		
		for(j=0;j<20;j++)	
		{
			
			
			for(k=0;k<20;k++)
			{
				printf("%d ",suppo[i][j][k]);
			}printf("\n");
		}printf("\n\n");
	}
		=====================================================================================*/
	end=clock();
	if(z==1)
	printf("solution is Infeasible, due to %d\n",j);
	else
	printf("solution is Feasible\n");
	printf("No. of crossover %d\nNo. of Mutation %d\n\n",no_cross,no_mutation);
	cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
	printf("\n\nTotal CPU time is: %f\n\n",cpu_time_used);
	fprintf(fo,"CPU TIME: %f\n",cpu_time_used);
	return 0;
	
}				
	
