#include<linux/linkage.h>
#include<linux/kernel.h>
#include<linux/uaccess.h>

asmlinkage int sys_print_kernel(char *buf_user, int buf_size){
	char buf_k[256];
	if (buf_size > 256) return -1;
	if (copy_from_user(buf_k, buf_user, buf_size) > 0) return -2;
	printk("%s\n", buf_k);
	return 0;

	// char buf_k[256];
	// printk("buffer size: %d\n",buf_size);
	// printk("copy_from_user return %lu\n",copy_from_user(buf_k, buf_user, buf_size));
	// printk("copy '%s' to '%s'\n", buf_user, buf_k);
	// printk("%s\n", buf_k);
	// return 0;
}
