#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/printk.h>

static struct timer_list timer = {0};

void timer_handler(struct timer_list *t)
{
    pr_debug("pr_dbg: This is pr_init func.\n");
    mod_timer(&timer, jiffies+msecs_to_jiffies(5000));
}

static int pr_test_init(void)
{
    timer_setup(&timer, timer_handler, 0);
    timer.expires = jiffies + 5 * HZ;
    add_timer(&timer);

    return 0;
}

static int pr_init(void)
{
    pr_test_init();
    printk("pr_init.\n");

    return 0;
}

static void pr_exit(void)
{
    printk("pr_exit.\n");
    del_timer(&timer);
}

module_init(pr_init);
module_exit(pr_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xzh");