// 书本测试用
SYSCALL_DEFINE0(test) {
	printk("Test!\n");
	return 0;
}
// 显示版本信息
SYSCALL_DEFINE1(show_name, void __user*, name) {
	struct new_utsname tmp;
	down_read(&uts_sem);
	memcpy(&tmp, utsname(), sizeof(tmp));
	up_read(&uts_sem);

	printk("sysname: %s\n",tmp.sysname);
    printk("release: %s\n",tmp.release);
   	printk("version: %s\n",tmp.version);

	if (copy_to_user(name, &tmp, sizeof(tmp))) return -EFAULT;
	else printk("Copy to user ok!\n");
	return 0;
}
// 查看或修改 nice
SYSCALL_DEFINE5(nice_prio, pid_t, pid, int, flag, int, nicevalue, void __user*, prio, void __user*, nice){
    struct pid* kpid;
    struct task_struct* task;
    kpid = find_get_pid(pid);/* 返回pid */
    task = pid_task(kpid, PIDTYPE_PID);/* 返回task_struct */
    int n;
    n = task_nice(task);/* 返回进程当前nice值 */
    int p;
    p = task_prio(task);/*返回进程当前prio值*/
    if(flag == 1) {
        set_user_nice(task, nicevalue);/* 修改进程nice值 */
        n = task_nice(task);/*重新取得进程nice值*/
	p = task_prio(task);
        copy_to_user(nice,&n,sizeof(n));/*将nice值拷贝到用户空间*/
        copy_to_user(prio,&p,sizeof(p));/*将prio值拷贝到用户空间*/
	printk("修改nice成功\n");
        return 0;  
    }
    else if(flag == 0) {
	printk("用户查询nice\n");
        copy_to_user(nice,&n,sizeof(n));/*将nice值拷贝到用户空间*/
        copy_to_user(prio,&p,sizeof(p));/*将prio值拷贝到用户空间*/
        return 0;
    }
    return EFAULT;
}

// 修改主机名
SYSCALL_DEFINE2(change_name, char __user *, name, int, len)
{
	int errno;
	char tmp[__NEW_UTS_LEN];

	if (len < 0 || len > __NEW_UTS_LEN)
		return -EINVAL;
	errno = -EFAULT;
	if (!copy_from_user(tmp, name, len)) {
		struct new_utsname *u;

		down_write(&uts_sem);
		u = utsname();
		memcpy(u->nodename, tmp, len);
		memset(u->nodename + len, 0, sizeof(u->nodename) - len);
		errno = 0;
		uts_proc_notify(UTS_PROC_HOSTNAME);
		up_write(&uts_sem);
		printk("修改成功\n");
	}
	return errno;
}
