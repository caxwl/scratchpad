#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"

void check(int const value)
{
    if (value != MPI_SUCCESS)
    {
       fprintf(stderr, "Failed in MPI\n");
       exit(1);
    }
}

int main(int argc, char** argv)
{
    MPI_Request mr;
    int input = 1;
    int result;
    int rank, size;
    
    check(MPI_Init(&argc, &argv));    
    check(MPI_Comm_rank(MPI_COMM_WORLD, &rank));
    check(MPI_Comm_size(MPI_COMM_WORLD, &size));
    if (rank==0) {
       check(MPI_Issend(&input, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, &mr));
       check(MPI_Test(&mr, &result, MPI_STATUS_IGNORE));
       fprintf(stdout, "MPI result: %d\n", result);
       check(MPI_Cancel(&mr));
       check(MPI_Wait(&mr, MPI_STATUS_IGNORE));  
    }

    check(MPI_Finalize());
    return 0;
}
