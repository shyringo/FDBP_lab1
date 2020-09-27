#include<iostream>
#include<math.h>
#include<mpi.h>
#include<ctime>
using namespace std;
int main(int argc,char** argv)
{
    int myid,numprocs,N;
    double SqrtSum,local=0;
    MPI_Status status;
    clock_t time_start=clock();
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    if(myid==0){
	cout<<"plz enter N:";//这一步只能对进程0执行
	cin>>N;
	for(int j=1;j<numprocs;j++){
	MPI_Send(&N,1,MPI_INT,j,1,MPI_COMM_WORLD);
	}
    }
    else{
        MPI_Recv(&N,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
    }
    for(int i=myid;i<=N-1;i+=numprocs){
        local+=sqrt(i);
    }
    MPI_Reduce(&local,&SqrtSum,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    if(myid==0){
        cout<<"the sum of the respective sqrt of 0 to "<<N-1<<" is "<<SqrtSum<<endl;
    }
    MPI_Finalize();
    clock_t time_end=clock();
    cout<<"this is process "<<myid<<". My time cost is "<<(time_end-time_start)/double(CLOCKS_PER_SEC)<<endl;
}
