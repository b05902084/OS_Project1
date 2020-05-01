#include<linux/linkage.h>
#include<linux/kernel.h>
#include<linux/ktime.h>
#include<linux/timekeeping.h>

asmlinkage int sys_get_time(time_t *tv_sec, long *tv_nsec){
	struct timespec t;
	getnstimeofday(&t);
	*tv_sec = t.tv_sec;
	*tv_nsec = t.tv_nsec;
	return 0;
}
