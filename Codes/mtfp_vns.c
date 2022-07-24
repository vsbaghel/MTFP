#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 25
#define PER 20
#define C 5000
#define P 2
#define S 10
#define D 5

void socio_initial(int solution[P][S][100],int soci[N][N],float weight[P],int require[P][S+1])
{
	int p,q,r,s,sum,sum2=0;
	
	float eff[P],geff=0.0;
	int i,j,k,l,m,a;
	int n;
	float e1,e2,e3;
	
	for( i=0;i<P;i++)
	{	
		sum=0;
		a=require[i][S];		
		for(j=0;j<S;j++)
		{
			for(k=0;k<require[i][j];k++)
			{
				p=(solution[i][j][k])%1000;
				for(l=0;l<S;l++)
				{
					for(m=0;m<require[i][l];m++)
					{
						q=(solution[i][l][m])%1000;
						soci[p-1][q-1]=1;
						sum=sum+soci[p-1][q-1];
						sum2++;
					}
				}
			}
		}
				
		

		a=a*a;
		e1=(float)(a);
		e2=(float)sum/e1;
		eff[i]=((0.5*(1+e2)));
		geff=geff+(eff[i]*weight[i]);
	}			
		
	//printf("\n");
	printf("%f \n",geff); 
	printf("sum2 is: %d \n",sum2);
	
}

void sociometric(int socio[N][N])
{
	int b,a,no1=0;
	int total;
	float n=N,p=PER;
	int i,j,k,l,x;
	int count=0;
	int c=0;
	int Pi;
	Pi=(int)((n*n*(p/100)));
	total=Pi;
	Pi=(int)(Pi/n);
	a=(int)(N/Pi);
	printf("%d\n",Pi);
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
		while(k<Pi)
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

//=============================================Neighbourhood search============================================================
void neigh_d(int solution[P][S][100], int skil, int supp[S][N], int suppo[N], int require[P][S+1],int socio[N][N], int nop[S])
{
	
	int i,j,k,l,m,x;
	int c=0,d;
	int sk[S];
	for(i=0;i<S;i++)
	{	sk[i]=0;
		}
	
	for(i=0;i<skil;i++)
	{	c=1;
		while(c!=0&&c<=10)
		{
			
			k= rand()%S;
			c++;
			if(sk[k]==0)
			{
				sk[k]=1;
				c=0;
			}
			
		}
		if(c!=0)
		{	c=0;
			while(c<S)
			{
				if(sk[c]==0)
				{
					k=c;
					sk[c]=1;
					break;
				}
				c++;
			}
		}
		for(j=0;j<P;j++)
		{
			for(l=0;l<require[j][k];l++)
			{
				x=solution[j][k][l]%1000;
				suppo[x-1]=0;
			}
		}
		for(j=0;j<P;j++)
		{
			for(l=0;l<require[j][k];l++)
			{
				c=1;d=1;
				while(c<=10)		//Normal random process
				{
		
					x=rand()%nop[k];
					m=supp[k][x]%1000;
					c++;
					if(suppo[m-1]==0)
					{
						solution[j][k][l]=supp[k][x];
						suppo[m-1]=1;d=0;
						break;
					}
					
				}
				if(d!=0)			//Brute Force
				{	c=0;
					while(c<nop[k])
					{
						m=supp[k][c]%1000;
						
						if(suppo[m-1]==0)
						{
							solution[j][k][l]=supp[k][c];
							suppo[m-1]=1;
							//c=nop[k]+1;
							break;
						}
						c++;
					}					
				}

					
			}
		}
	}

}


//===============================================Efficiency calculation===================================================
float fitness(int solution[P][S][100],int soci[N][N],float weight[P],int require[P][S+1])
{
	int p,q,r,s,sum;
	
	float eff[P],geff=0.0;
	int i,j,k,l,m,a;
	int n;
	float e1,e2,e3;
	
	for( i=0;i<P;i++)
	{	
		sum=0;
		a=require[i][S];		
		for(j=0;j<S;j++)
		{
			for(k=0;k<require[i][j];k++)
			{
				p=(solution[i][j][k])%1000;
				for(l=0;l<S;l++)
				{
					for(m=0;m<require[i][l];m++)
					{
						q=(solution[i][l][m])%1000;
						sum=sum+soci[p-1][q-1];
					}
				}
			}
		}
				
		

		a=a*a;
		e1=(float)(a);
		e2=(float)sum/e1;
		eff[i]=((0.5*(1+e2)));
		geff=geff+(eff[i]*weight[i]);
	}			
		
	//printf("\n");
	 
	return geff;
}

//========================================Copy================================
void copy(int solution[P][S][100],int solfin[P][S][100],int req[P][S+1])
{
	int i,j,k;
	for(i=0;i<P;i++)
	{
		for(j=0;j<S;j++)
		{
			for(k=0;k<req[i][j];k++)
			{
				solfin[i][j][k]=solution[i][j][k];
			}
		}
	}
}

void copy2(int suppo1[N],int suppo2[N])
{
	int i;
	for(i=0;i<N;i++)
	{
		suppo2[i]=suppo1[i];
	}
}
void makezero(int suppo[N])
{	int i;
	for( i=0;i<N;i++)
	{
		suppo[i]=0;
	}
}

//=================================================main()======================================
int main(int argc, char *argv[])
{

	clock_t start,end;
	double cpu_time_used;
	start=clock();
	FILE *fi=fopen(argv[1],"r");
	FILE *fs=fopen(argv[2],"r");
	FILE *fo=fopen(argv[3],"a");
	int solution[P][S][100];
	int solfin[P][S][100];
	int supp[S][N];
	float fit=0.0;
	int sol[P][S][100];	
	int req[P][S+1];
	int socio[N][N];
	int i,j,k,l;
	
	int suppo[N];
	int suppo2[N];
	int suppo_fin[N];
	int nop[S];
	int a,b,c,pos=1,v;
	int count=0;
	float fitx[2000];
	int arr[N];
	
	float w[P];
	float fitval=0.0,fit1;

	if(argc<4||argc>4){exit(0);}	
	for(i=0;i<N;i++)
		arr[i]=0;
	
	for(i=0;i<P;i++)		//requirement of every skill's individuals in project
	{	a=0;
		fscanf(fi,"%f",&w[i]);
		for(j=0;j<S;j++)
		{	
			fscanf(fi,"%d",&req[i][j]);
			a=a+req[i][j];	
		}
		req[i][j]=a;
	}

	for(i=0;i<S;i++)		//support set of each and every skills
	{
		fscanf(fi,"%d",&nop[i]);
		a=nop[i];
		for(j=0;j<a;j++)	
		{
			fscanf(fi,"%d",&supp[i][j]);
		}
	}
	
	/*for(i=0;i<P;i++)
	{
		for(j=0;j<S;j++)
		{
			for(k=0;k<req[i][j];k++)
			{	
				fscanf(fi,"%d",&solution[i][j][k]);
			}
		}
	}*/
	makezero(suppo);
	makezero(suppo2);
	makezero(suppo_fin);
	for(i=0;i<P;i++)
	{	printf("project %d:",i+1);
		for(j=0;j<S;j++)
		{	
			for(k=0;k<req[i][j];k++)
			{
				printf("%d- ",solution[i][j][k]);
			}
			
		}
	}printf("\n");

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
	//socio_initial(solution,socio,w,req);
	//sociometric(socio);

	/*for(i=0;i<N;i++)		//sociomatrix generation
	{
		for(j=0;j<N;j++)
		{
			
			printf("%d ",socio[i][j]);
		}
		printf("\n");
	}*/	
	//exit(0);

/*	for(i=0;i<N;i++)		//sociomatrix generation
	{
		for(j=0;j<N;j++)
		{
			b=rand()%2;
			if(i==j)
			socio[i][j]=1;
			else
			socio[i][j]=b;
		}
		j=0;
		while(j<10)
		{
			b=rand()%N;
			if(i!=b)
			socio[i][b]=-socio[i][b];
		j++;}
	}
*/	//printf("vivek");
	

	srand(time(0));
	v=0;
	for(i=0;i<P;i++)
	{
		for(j=0;j<S;j++)
		{
			for(k=0;k<req[i][j];k++)
			{	
				c=1;
				while(c<20)
				{
					b=nop[j];
					a=rand()%b;
					b=supp[j][a];
					b=b%1000;
					if(suppo[b-1]==0)
					{
						suppo[b-1]=1;
						suppo2[b-1]=1;
						suppo_fin[b-1]=1;
						solution[i][j][k]=supp[j][a];
						solfin[i][j][k]=supp[j][a];
						sol[i][j][k]=supp[j][a];						
						c=22;
						v++;
					}c++;
				}
					if(c!=23)
					{	
							
						a=0;c=1;
						while(c!=0&&a<nop[j])
						{
							b=supp[j][a];
							b=b%1000;
							if(suppo[b-1]==0)
							{
								suppo[b-1]=1;
								suppo2[b-1]=1;
								suppo_fin[b-1]=1;
								solution[i][j][k]=supp[j][a];
								solfin[i][j][k]=supp[j][a];
								sol[i][j][k]=supp[j][a];
								c=0;
								v++;
							}a++;
						}
						
						}
				
				
			}
		}
	}
		
	for(i=0;i<P;i++)
	{	printf("project %d\n",i+1);
		for(j=0;j<S;j++)
		{	printf("skill %d\n",j+1);
			for(k=0;k<req[i][j];k++)
			{
				printf("%d-%d-%d ",solution[i][j][k],solfin[i][j][k],sol[i][j][k]);
			}
			printf("\n");
		}
	}
	
	
	printf("\n");
	
	fitval=fitness(solution,socio,w,req);
	fit1=fitval;
	fitx[0]=fit1;
	printf("%f ",fitval);

	//variable neighbourhood search 
	int vi=1;
	int gino=1;
	printf("\nWAIT FOR A WHILE..............\n");
	for(i=0;i<C;i++)
	{
		
		k=1;
		for(j=1;j<=S;j++)
		{
			//fitval=local_search(solution,k,req,supp,suppo,socio,nop,fit1);
			//=======================================================
			copy(solution,sol,req);
			copy2(suppo,suppo2);			
			for(l=0;l<D;l++)
			{	count++;
				neigh_d(solution,k,supp,suppo,req,socio,nop);
				fit=fitness(solution,socio,w,req);
				if(fit>fit1)
				{
					fit1=fit;
					copy(solution,sol,req);
					copy2(suppo,suppo2);
				}
				else{
					copy(sol,solution,req);
					copy2(suppo2,suppo);
					}
				//printf("%f ",fit1);
				//if(gino%5==0)
				//{
				//	fitx[vi]=fit1;
				//	vi++;
				//}	
				gino++;
			}
			//fitval=fit1;
			//=======================================================	
			if(fit1>fitval)
			{	fitval=fit1;
				copy(solution,solfin,req);
				copy2(suppo,suppo_fin);
			}		//if(fitval>fit1)
				//{
				//	fit1=fitval;
				//	copy(solution,solfin,req);
				
				//}
			else{
			k=k+1;
			copy(solfin,solution,req);
			copy2(suppo_fin,suppo);
			}
			//printf("%f %d\n",fit1,gino);
			gino++;
		}
		//printf("vivek");
		//fitx[i+1]=fit1;
		if(i%5==0)
		{
			fitx[vi]=fitval;
			vi++;
		}
		
	}
	printf("\n++++++++%f+++++++++++\n",fitval);
	int z=0;
	int infeas;
	printf("\n");
	for(i=0;i<1000;i++)
	{
	 fprintf(fo,"%f ",fitx[i]);
	}fprintf(fo,"\n");
	printf("\nTotal Iteration: %d\n",count);		
	printf("%f ",fit1);	
	end=clock();
	cpu_time_used=((double)(end-start))/CLOCKS_PER_SEC;
	for(i=0;i<P;i++)
	{	printf("project %d\n",i+1);
		for(j=0;j<S;j++)
		{	printf("skill %d\n",j+1);
			for(k=0;k<req[i][j];k++)
			{	if(arr[(solfin[i][j][k]%1000)-1]==1)
					{z=1;infeas=solfin[i][j][k];}
				arr[(solfin[i][j][k]%1000)-1]=1;
				printf("%d ",solfin[i][j][k]);
				fprintf(fo,"%d ",solfin[i][j][k]);
			}
			
		}
	}printf("\n++++++++%f+++++++++++\n",fitval);
	if(z==1)
	{printf("\n\n***************Solution is Infeasible due to: %d\n\n",infeas);}
	else{printf("\n\n***************Solution is Feasible\n\n");}
	printf("\n\nTotal CPU time is: %f\n\n",cpu_time_used);
	fprintf(fo,"\nCPU Time:%f\n",cpu_time_used);
return 0;
}
