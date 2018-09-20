#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

	int rank, a;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		a = 100;
		MPI_Send(&a, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		MPI_Recv(&a, 1, MPI_INT, 1, 2, MPI_COMM_WORLD, NULL);
		printf("%d\n", a);

	} else if (rank == 1) {
		MPI_Recv(&a, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, NULL);
		printf("%d\n", a);
		a = 200;
		MPI_Send(&a, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0;
}
