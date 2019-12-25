#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/fcntl.h>
#include <asm/uaccess.h>

asmlinkage long sys_get_elapsed_time(void) 
{
    char  buffer_uptime[100], buffer_stat[100];
    char dummy[30];
    int Proc_Uptime, Input, Booting_Time, Elapsed_Time;
    long int ticks, sec, e_sec;
    long long int p_start_time;

    ticks = 100;

    mm_segment_t old_fs = get_fs();

    set_fs(KERNEL_DS);    
    Input = ksys_open("/proc/1/stat", O_RDONLY, 0);

    ksys_read(Input, buffer_stat, 1); 
    sscanf(buffer_stat, "%d %d %d %d %d %d %d %d %d %d %d, %d %d %d %d %d %d %d %d %d %d %lld", dummy,dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, dummy, &p_start_time);

    ksys_close(Input);
    set_fs(old_fs);

    set_fs(KERNEL_DS);

    Proc_Uptime = ksys_open("/proc/uptime", O_RDONLY, 0);

    ksys_read(Proc_Uptime, buffer_uptime, 1);
    sscanf(buffer_uptime, "%lds", &sec);

    ksys_close(Proc_Uptime);
    set_fs(old_fs);

    Booting_Time = (sec*ticks);
    Elapsed_Time = Booting_Time - p_start_time;
    
    e_sec = Elapsed_Time / ticks;

    printk("%ld\n", e_sec);

    return e_sec;
}
