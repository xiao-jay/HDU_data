#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>
#include <linux/sched/signal.h>

static pid_t pid = 1;
module_param(pid, int, 0644);
const int depth = 3;
const int N = 1 << 8;
int num_children(struct task_struct *p) {
	int tot = 0;
	struct list_head *L;
	list_for_each(L, &p->children) ++tot;
	return tot;
}

void dfs(struct task_struct *p, char *out, char *ind, int dep) {
	char n_out[N];
	snprintf(n_out, N, "%s(pid: %d, state: %ld)", p->comm, p->pid, p->state);
	int l = strlen(n_out), tot = num_children(p);
	char new_out[N];
	snprintf(new_out, N, "%s%s", out, n_out);
	// printk("%d\n", tot);
	if (!tot || !dep) {
		printk("%s\n", new_out);
		return;
	}
	char new_ind[N], end_ind[N];
	snprintf(new_ind, N, "%s%*s │ ", ind, l, "");
	snprintf(end_ind, N, "%s%*s   ", ind, l, "");
	int i = 0;
	struct list_head *L;
	list_for_each(L, &p->children) {
		struct task_struct *q = list_entry(L, struct task_struct, sibling);
		i == 0 ? snprintf(n_out, N, "%s%s", new_out, tot > 1 ? "─┬─" : "───") :
			snprintf(n_out, N, "%s%*s%s", ind, l, "", i == tot - 1 ? " └─" : " ├─");
		dfs(q, n_out, i == tot - 1 ? end_ind : new_ind, dep - 1);
		++i;
	}
}
// 初始化函数
static int pstree_init(void) {
	struct task_struct *p = pid_task(find_vpid(pid), PIDTYPE_PID);
	if (p == NULL) {
		printk("Nullptr\n");
		return 0;
	}
	char ind[N], out[N], n_out[N];
	if (p->real_parent == NULL) {
		snprintf(out, N, "无父进程───");
		snprintf(ind, N, "%*s   ", (int)strlen(out), "");
		dfs(p, out, ind, depth);
		return 0;
	}
	struct task_struct *fa = p->real_parent;
	snprintf(n_out, N, "%s(pid: %d, state: %ld)", fa->comm, fa->pid, fa->state);
	int l = strlen(n_out), tot = num_children(fa);
	snprintf(ind, N, "%*s │ ", l, "");
	snprintf(out, N, "%s%s", n_out, tot > 1 ? "─┬─" : "───");
	// printk("%d\n", p->pid);
	// printk("%s\n", out);
	dfs(p, out, ind, depth);
	int num = tot - 1;
	struct list_head *L;
	list_for_each(L, &fa->children) {
		struct task_struct *q = list_entry(L, struct task_struct, sibling);
		if (p == q) continue;
		snprintf(out, N, "%*s%s", l, "", --num == 0 ? " └─": " ├─");
		dfs(q, out, ind, depth);
		//printk("%s\n", out);
	}
	return 0;
}
// 清理函数
static void pstree_exit(void) {
	printk(KERN_ALERT"pstree.ko has been uninstalled!\n");
}

// 函数注册
module_init(pstree_init);  
module_exit(pstree_exit);  

// 模块许可申明
MODULE_LICENSE("GPL");
