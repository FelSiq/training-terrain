#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int rank;
	char buffer[] = "world!";

	MPI_Init(&argc, &argv);

	MPI_Status status;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		printf("Hello");

		MPI_Send(buffer, sizeof(buffer), 
			MPI_CHAR, 1, 1, MPI_COMM_WORLD);

		MPI_Recv(NULL, 0, MPI_CHAR, 1, 2, 
			MPI_COMM_WORLD, &status);
	} else
	if (rank == 1) {
		MPI_Recv(buffer, sizeof(buffer), 
			MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);

		MPI_Send(NULL, 0, MPI_CHAR, 0, 2, MPI_COMM_WORLD);

		printf(" %s", buffer);

	} 

	MPI_Finalize();
	return 0;
}
