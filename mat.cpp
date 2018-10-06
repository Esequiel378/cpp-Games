#include <iostream>
using namespace std;

void MatrizId(float A[10][10],int n)
{
    int i,j;
    for (i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            if(i==j)
                A[i][j]=1;
            else A[i][j]=0;
        }
}

void MostrarMatriz(float A[10][10],int n)
{
    int i,j;
    cout<<"La matriz es:"<<endl;
    for (i=0;i<n;i++)
        {
        for (j=0;j<n;j++)
            cout<<A[i][j]<<"\t";
            cout<<endl;
        }
}


int main()
{
    int n;float A[10][10];
    cout<<"Ingrese el rango de la matriz: ";cin>>n;
    //MatrizId(A,n);
    MostrarMatriz(A,n);
}
