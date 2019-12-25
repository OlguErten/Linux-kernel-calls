#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main()
{
    long int elapsed_time = syscall(548);
    printf("Elapsed time: %ld\n", elapsed_time);
    
    return 0;
}
