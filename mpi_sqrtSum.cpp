#include<iostream>
#include<math.h>
#include<mpi.h>
using namespace std;
int main(int argc,char** argv)
{
    int myid,numprocs,N;
    cin>>N;//计算0到N-1的开方求和
    double SqrtSum=0,local=0;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    for(int i=myid;i<=N-1;i=i+numprocs){
        local+=sqrt(i);
    }
    MPI_Reduce(&local,&SqrtSum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    if(myid==0){
        cout<<"the sum of the respective sqrt of 0 to "<<N-1<<" is SqrtSum";
    }
    MPI_Finalize();
}