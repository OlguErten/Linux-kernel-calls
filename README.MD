use: "sudo su" to become super user

1) check your current kernel version

uname -r

2) download one of the latest kernel code version

wget v<KERNEL_MAJOR_VERSION>/<KERNEL_VERSION>

3) Change your directory to new kernel code

cd /usr/src/<KERNEL_VERSION>/

4) Make directory for system call function and change you directory

mkdir getelapsed
cd getelapsed

5) Copy provided getelapsed_kernel.c to the getelapsed directory (name the source code as getelapsed.c as well)
6) Create a “Makefile” in the hello directory

gedit Makefile

#then write the code below inside Makefile

obj-y := getelapsed.o


7) Go to parent directory

cd ../

8) Open "Makefile"

gedit Makefile

9) search for "core-y" in the document and find the line as the second instance of your search:

core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/

10) Add ‘hello/’ to the end of this line:

core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/ getelapsed/

11) Add the new system call to the system call table:
If you are on a 32-bit system you’ll need to change ‘syscall_32.tbl’. For 64-bit, change ‘syscall_64.tbl’.

cd arch/x86/entry/syscalls/
gedit syscall_64.tbl

12) Add the line below. Beware, the first number should be +1 based on the EOF.

548       64        getelapsed          sys_get_elapsed_time

Example:

523	...	...	...
524	...	...	...
525	64	getelapsed	sys_get_elapsed_time

13) Go to the <KERNEL_VERSION>/ directory and type the following commands

cd include/linux/
gedit syscalls.h

14) Add the following line to the end of the document before the #endif statement

asmlinkage long sys_hello(void);

15) Before starting to compile you need to install a few packages. Type the following commands in your terminal:

sudo apt-get install gcc
sudo apt-get install libncurses5-dev
sudo apt-get install bison
sudo apt-get install flex
sudo apt-get install libssl-dev
sudo apt-get install libelf-dev
sudo apt-get update
sudo apt-get upgrade
sudo apt-get make

16) Configure your kernel by using the following command in your <KERNEL_VERSION>/ directory

sudo make menuconfig

IMPORTANT NORE: while entering this command, you might want to maximize your terminal screen. 
Otherwise, you might get and error and a pop-up screen will not appear.

Once the above command is used to configure the Linux kernel, you will get a pop up window with the list of 
menus and you can select the items for the new configuration. If your unfamiliar with the configuration just 
check for the file systems menu and check whether “ext4” is chosen or not, if not select it and save the configuration.

17) Now to compile the kernel you can use the make command:

sudo make

The compilation took 3-4 hours for me on VM. As an alternative you can take advantage of the multiple cores on your computer, by simply typing

sudo make -jn

the  'n' letter in "-jn" option stands for the number of cores you want to dedicate for compilation. However, we don't quite recommend it on VM
users. Or dedicate less amount of cores than you have given to your VM.

Example:

sudo make -j2

18) To install/update kernel,type the given command below.

sudo make modules_install install

19) The command will create some files under "/boot/" directory and it will automatically make a entry in your grub.cfg. 
	To check whether it made correct entry, check the files under /boot/ directory . If you have followed the steps without 
	any error you will find the following files in it in addition to others.

- System.map-<KERNEL_VERSION>
- vmlinuz-<KERNEL_VERSION>
- initrd.img-<KERNEL_VERSION>
- config-<KERNEL_VERSION>

20) Finally run the following command to reboot your computer:


shutdown -r now

21) After you computer has restarted, run the following command to check if your kernel has been updated/installed

uname -r

22) Write the C code given below to check if our system call function is working

#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
int main()
{
         long int Elapsed_time = syscall(548);
         printf("System call sys_hello returned %ld\n", Elapsed_time);
         return 0;
}

23) To check the message of your kernel run the following command given below.

dmesg


USEFUL LINKS
1) https://medium.com/@ssreehari/implementing-a-system-call-in-linux-kernel-4-7-1-6f98250a8c38

2) https://medium.com/anubhav-shrimal/adding-a-hello-world-system-call-to-linux-kernel-dad32875872

