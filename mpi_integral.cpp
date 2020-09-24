#include<iostream>
#include<mpi.h>
#define N 10000000
using namespace std;
int main(int argc,char** argv)
{
    int myid,numprocs;
    MPI_Status status;
    double local=0,dx=double(10)/double(N),integral=0;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    if(myid!=0){
        for(int i=myid-1;i<N;i=i+numprocs-1){
            double x=i*dx+dx/2;
            local+=x*x*dx;
        }
        MPI_Send(&local,1,MPI_DOUBLE,0,1,MPI_COMM_WORLD);
    }
    else{
        for(int i=1;i<numprocs;i++){
            double d;
            MPI_Recv(&d,1,MPI_DOUBLE,i,1,MPI_COMM_WORLD,&status);
            integral+=d;
        }
        cout<<"the integral of x*x in [0,10] is "<<integral<<endl;
    }
    MPI_Finalize();
}
