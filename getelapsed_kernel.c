#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/fcntl.h>
#include <asm/uaccess.h>

asmlinkage long sys_get_elapsed_time(void) 
{

    char buffer_uptime[1], buffer_stat[100];                            /* Declaring buffers to hold datas of file descriptors */
    char dummy[100];                                                    /* Declaring dummy array for parsing /proc/<pid>/stat until 22nd element */
    int Proc_Uptime, Input;                                             /* Declaring file descriptors */
    long int ticks, sec, e_sec;                                         /* Declaring variables for time related operations */
    unsigned long long int p_start_time;                                /* Declaring variables for time related operations */
    ticks = 100;

    mm_segment_t old_fs = get_fs();                                     /* This get_fs function is used for extending addr_limit in order to read data into kernel buffer */

    set_fs(KERNEL_DS);                                                  /* Set addr_limit for read data into kernel buffer */
    Input = ksys_open("/proc/1/stat", O_RDONLY, 0);                     /* Open stat file to read start time of the process */

    ksys_read(Input, buffer_stat, 400);                                 /* Read file descriptor into the buffer */
    sscanf(buffer_stat, "%lld %c %s %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %llu", dummy,dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, &p_start_time);                     /* Read file descriptor into the buffer start time gives in clockticks */

    ksys_close(Input);                                                  /* Close file */
    set_fs(old_fs);                                                     /* Get back old addr_limit */
  
    set_fs(KERNEL_DS);                                                  /* Set addr_limit for read data into kernel buffer */

    Proc_Uptime = ksys_open("/proc/uptime", O_RDONLY, 0);               /* Open uptime file to read uptime of the system */

    ksys_read(Proc_Uptime, buffer_uptime, 8);                           /* Read file descriptor into the buffer */
    sscanf(buffer_uptime, "%lds", &sec);                                /* Read file descriptor into the buffer start time gives in seconds */

    ksys_close(Proc_Uptime);                                            /* Close file */
    set_fs(old_fs);                                                     /* Get back old addr_limit */

    e_sec = sec - p_start_time/ticks;                                   /* Calculate elapsed time by substracting start time from uptime */             
    
    printk("Total elapsed time since process started: %ld\n", e_sec);   /* Print elapsed time since the process started */

    return e_sec;                                                       /* Return elapsed time */
}
