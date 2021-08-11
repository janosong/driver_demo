#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>

struct clk_drv {
    struct gpio_chip chip;
    struct mutex lock;
};

static const struct gpio_chip demo_chip = {
    .label = "demo_clk",
    .owner = THIS_MODULE,
    .get_direction = 0,
};

static int __init clk_init(void)
{
    printk(KERN_INFO"%s PAGE_OFFSET:%lx, sz_16M:%lx,task_size:%lx\n", __func__, CONFIG_PAGE_OFFSET, SZ_16M, TASK_SIZE);
    return 0;
}
module_init(clk_init);

static void __exit clk_exit(void)
{
    printk(KERN_INFO"%s\n", __func__);
    return;
}
module_exit(clk_exit);


MODULE_LICENSE("MIT");
//MODULE_LICENSE("GPL v2");
