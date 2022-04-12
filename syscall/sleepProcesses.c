#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include "sleepProcesses.h"
  
asmlinkage long sys_listSleepProcesses(const char __user *buf, int size) {
	struct task_struct *proces;
	unsigned char kbuf[1024];
	int bufsz;
	int ret;

	snprintf(kbuf, sizeof(kbuf), "List of proc in SLEEP:\n\n");
	bufsz += strlen(kbuf)+1;

	/* Find the process */
	for_each_process(proces) {
		if(proces->state == TASK_INTERRUPTIBLE || proces->state == TASK_UNINTERRUPTIBLE) {
			kbuf[index] = (long)task_pid_nr(proces);
			index = index + 1;
		}
	}
	}
	/* User buffer is too small */
	if(bufsz > size){
		return -1;
	}

	/* success */
	ret = copy_to_user((void*)buf, (void*)kbuf, bufsz);

	return bufsz - ret;

	/* Process not found */
	return -2;	
}
