#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

struct proc_dir_entry *my_proc_entry;

static int proc_clk_show(struct seq_file *m, void *v)
{
    //cat显示的内容
    seq_printf(m,
          "pll0: %u Mhz\n"
          "pll1: %u Mhz\n"
          "pll2: %u Mhz\n",
          100, 200, 300);
   return 0;
}

static int clk_info_open(struct inode *inode, struct file *filp)
{
     return single_open(filp, proc_clk_show, NULL);
}

static struct file_operations myops = 
{
      .owner = THIS_MODULE,
      .open = clk_info_open,
      .read = seq_read,
      .llseek = seq_lseek,
      .release = seq_release,
};

static int __init my_module_init(void)
{
    //注册proc接口
   my_proc_entry = proc_create("clk", 0644, NULL, &myops);

    return 0;
}

static void __exit my_module_exit(void)
{
    //注销proc接口
   proc_remove(my_proc_entry);
}

module_init(my_module_init);
module_exit(my_module_exit);
MODULE_LICENSE("GPL");