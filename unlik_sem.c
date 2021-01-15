
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <semaphore.h>

int main()
{	sem_unlink("fork");
	sem_unlink("wt");
	sem_unlink("dead");
	sem_unlink("start");
	sem_unlink("grap");
	sem_unlink("mutex");
	return 0;
}
