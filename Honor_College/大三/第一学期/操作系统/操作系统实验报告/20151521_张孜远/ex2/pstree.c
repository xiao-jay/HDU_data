#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>
#include <linux/sched/signal.h>
//#include <stdio.h>
//#include <string.h>

static pid_t pid = 1709;
module_param(pid, int ,0644);

void show_it_children(struct task_struct *p,char fout1[100],int fl,int nps)
{
    struct task_struct *pchildren[500];
    struct list_head *L;
    int i = 0,npc = 0,ml = 0;
    char out[100];
    char fout2[100];

    list_for_each(L,&p->children){
        pchildren[npc++]=list_entry(L,struct task_struct,sibling);
    }
    
    //输出当前进程信息
    sprintf(out,"─%s(pid:%d,state:%ld)",p->comm,p->pid,p->state);
    ml = strlen(out) - 1;
    if(npc)
    {
        if(npc != 1)
            sprintf(fout2,"%s%s─┬─",fout1,out);
        else 
            sprintf(fout2,"%s%s───",fout1,out);
    }
    else
    {
        printk("%s%s\n",fout1,out);
        return ;
    }    
    //输出子进程信息
    if(nps - 1 > 0)
        sprintf(fout1,"%*s│%*s",fl,"",ml,"");
    else
	sprintf(fout1,"%*s",fl + ml + 2,"");
    for(i = 0;i < npc;i++)
    {
        sprintf(out,"%s(pid:%d,state:%ld)",pchildren[i]->comm,pchildren[i]->pid,pchildren[i]->state);
        if(i)
        {
            if(i != npc - 1)
                printk("%s├─%s\n",fout1,out);
            else
                printk("%s└─%s\n",fout1,out);
        }
        else
        {
            printk("%s%s\n",fout2,out);
        }
    }
}

static int mypstree_init(void)
{
    struct task_struct *p;
    struct task_struct *psibling[100];
    struct list_head *L;
    int i = 0,nps = 0,fl = 0,tps = 0;
    char out[100];
    char fout1[100];

    p=pid_task(find_vpid(pid),PIDTYPE_PID);

    list_for_each(L,&p->parent->children){
        psibling[nps++]=list_entry(L,struct task_struct,sibling);
    }

    //输出父进程信息
    if(p->parent==NULL)
        sprintf(out,"无父进程─");
    else
        sprintf(out,"%s(pid:%d,state:%ld)─",p->parent->comm,p->parent->pid,p->parent->state);
    fl = strlen(out) - 2;
    if(nps)
        sprintf(fout1,"%s┬",out);
    else
        sprintf(fout1,"%s─",out);

    show_it_children(p,fout1,fl,nps);

    tps = nps - 1;
    //输出兄弟进程信息
    for(i = 0;i < nps;i++)
    {
        if(psibling[i] != p)
        {
            --tps;
            if(tps)
                sprintf(out,"%*s├─",fl,"");
            else
                sprintf(out,"%*s└─",fl,"");
            show_it_children(psibling[i],out,fl,tps);
        }
    }
    return 0;
}

static void mypstree_exit(void)
{
	printk(KERN_ALERT"mypetree end\n");
	return ;
}

module_init(mypstree_init);
module_exit(mypstree_exit);
MODULE_LICENSE("GPL");
