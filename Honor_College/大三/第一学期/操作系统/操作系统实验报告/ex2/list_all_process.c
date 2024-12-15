#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init_task.h>
// 初始化函数
static int LAP_init(void) {
	struct task_struct *p;
	p = NULL;
	p = &init_task;
	printk(KERN_ALERT"名称\t\t进程号\t状态\t优先级\t父进程号\t");
	for_each_process(p) if(p->mm == NULL) { //内核线程的mm成员为空
		printk(KERN_ALERT"%s\t\t%d\t%ld\t%d\n", p->comm, p->pid, p->state, p->normal_prio, p->parent->pid);
	}
	return 0;
}
// 清理函数
static void LAP_exit(void) {
	printk(KERN_ALERT"End of LAP!\n");
}

// 函数注册
module_init(LAP_init);  
module_exit(LAP_exit);  

// 模块许可申明
MODULE_LICENSE("GPL");
