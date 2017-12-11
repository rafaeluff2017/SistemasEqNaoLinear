#include<stdio.h>
#include<math.h>

#define e 2.71828182846
#define N 3
#define pi 3.14159265359
#define h 1e-06



double f1(double x[N])
{
	return(pow(x[0],2) - 81*pow((x[1]+0.1), 2) + sin(x[2]) + 1.06);
}


double f2(double x[N])
{
	return(exp(x[0]*x[1]) + 20*x[2] + ((10*M_PI) - 3)/3.0);
}


double f3(double x[N])
{
	return((3*x[0]) - cos(x[1] *x[2]) - 1.0/2);
}

double df(double f(), double x[N], int k)
{
	int i;
	double aux[N], v;
	
	
	for(i = 0; i < N; i++)
		aux[i] = x[i];
	
	aux[k] = x[k] + h/2.0;
	
	v = f(aux);
	
	aux[k] = x[k] - h/2.0;	
	
	v = (v - f(aux))/h;
	
	return(v);
}





int main(int argc, char **argv)
{
	double x[N] = {0}, xa[N],Y[N],aux;	//xa é o vetor chute
	double eps = 0.0001, tol=1e-07,norm, norma,norm1, norma1, M[N][N], mt[N][N+1],normay=0,normy;
	double (*equacao[N])() = {f1, f2, f3};
	int i, j,k,itt=0;
	double A[20][20],c;
	
	FILE *fp;
	fp=fopen("sistema2.dat","w");
	
	for(i=0;i<N;i++)
	{
		printf("\nDigite o %dº valor para chute para x\n",i);
		scanf("%lf", &xa[i]);
	}


do{

			norm = 0.0;
			
			for(i = 0; i < N; i++)
			{	
				
				
				x[i] = equacao[i](xa);
 						
				
										
				norm += pow(fabs(x[i]),2);
			}
	
			
			norma = sqrt(norm);
			
		 		




		// calculando o jocobiano
		for(i = 0; i < N; i++)
		{
			x[i] = -equacao[i](xa);
			
			for(j = 0; j < N; j++)
			{
				M[i][j] = df(equacao[i], xa, j);
			}		
		}
	
	
	
		for(i = 0; i < N; i++)
		{
			for(j = 0; j < N; j++)
			
			mt[i][j] = M[i][j];
		}
	
		for(i = 0; i < N; i++)
		
			mt[i][N] = x[i];
			
		
		/*printf("\nMatriz total:\n");
		for(i = 0; i < N; i++)
		{
			for(j = 0; j < N+1; j++)
				
				printf("%.2lf\t", mt[i][j]);
			
		printf("\n");
		}*/
		
		

					
	//Lendo Matriz aumentada
	for(i=0; i<N; i++)
   	{
		for(j=0; j<(N+1); j++)
		{
			A[i][j]=mt[i][j]   ;        		
			
      		}
		//printf("\n");   	
	}

	//diagonalizando
	for(j=0; j<N; j++)
    {
        for(i=0; i<N; i++)
        {
            if(i!=j) // Pegando elementos Diferentes
            {
                c=A[i][j]/A[j][j];// operador para diagonalizar
                for(k=0; k<N+1; k++)
                {
                    A[i][k]=A[i][k]-c*A[j][k]; // fazendo para todas as linhase colunas
                }
            }
        }
    }
			
     	
	
	

	// Imprimindo a solução
	//printf("\n O vetor solução\n"); 
	for(i=0; i<N; i++)
   	 {
       	 	
       	 	Y[i]=A[i][N]/A[i][i];
        	//printf("\ny[%d]= %.2lf\n",i,Y[i]);
   	 }

	
	//Somando x=xa+Y	
	
	//printf("\nVetor atualizado X.\n");
	for(i=0;i<N;i++)
	{

		xa[i]=xa[i]+Y[i];
		//printf("\nx%d= %.2lf",i,xa[i]);
		
	}	
	
	
	
			// calculando a nova norma
			norm1=0.0;
			for(i = 0; i < N; i++)
			{	
				
				
				x[i] = equacao[i](xa);
 						
				
										
				norm1 += pow(fabs(x[i]),2);
			}
	
			
			norma1 = sqrt(norm1);
		
	
		 
			
			
			
			//calculando a norma de y
			normy=0;
			for(i = 0; i < N; i++)
			{	
		
 						

										
				normy += pow(fabs(Y[i]),2);
			}
	
			
			normay = sqrt(normy);
			fprintf(fp,"\n%d\t%.2lf",itt,normay);	

		
		itt++;
		
		if (itt==15)
			break;
   
       }while(fabs(norma1-norma)>tol );
	
	
	//imprimindo o vetor x final
	printf("\nVetor atualizado X.\n");
	for(i=0;i<N;i++)
	{

		xa[i]=xa[i]+Y[i];
		printf("\nx%d= %.2lf",i,xa[i]);
		
	}	
	
	// Imprimindo a solução
	printf("\n O vetor solução\n"); 
	for(i=0; i<N; i++)
   	 {
       	 	
       	 	Y[i]=A[i][N]/A[i][i];
        	printf("\ny[%d]= %.2lf\n",i,Y[i]);
   	 }
	// Calculando a norma do vetor y
	
	for(i=0;i<N;i++){
			normay=pow(Y[i],2);
		}
	printf("Norma do vetor solução é %.2lf",sqrt(normay));
	
	printf("\n\ninterações: %d\n",itt);


}
	
	
	




