#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/device.h>

struct gpio_drv {
    struct gpio_chip chip;
    struct mutex lock;
};

static const struct gpio_chip demo_chip = {
    .label = "demo_gpio",
    .owner = THIS_MODULE,
    .get_direction = 0,
};

struct device dev;

static int __init gpio_init(void)
{
    int ret;
    //dev_set_name(&dev, "haha");
    //ret = device_register(&dev);
    ret = register_chrdev_region(MKDEV(255, 10), 10, "haha");
    printk(KERN_INFO"%s %d ret:%x\n", __func__, __LINE__,ret);
    ret = register_chrdev_region(MKDEV(255, 12), 10, "haha");
    printk(KERN_INFO"%s %d ret:%x\n", __func__, __LINE__,ret);
    ret = register_chrdev_region(MKDEV(255, 8), 10, "haha");
    printk(KERN_INFO"%s %d ret:%x\n", __func__, __LINE__,ret);
    ret = register_chrdev_region(MKDEV(255, 8), 22, "haha");
    printk(KERN_INFO"%s %d ret:%x\n", __func__, __LINE__,ret);
    ret = register_chrdev_region(MKDEV(255, 9), 15, "haha");
    printk(KERN_INFO"%s %d ret:%x\n", __func__, __LINE__,ret);
    return 0;
}
module_init(gpio_init);

static void __exit gpio_exit(void)
{
    //device_unregister(&dev);
    unregister_chrdev_region(MKDEV(255, 8), 22);
    unregister_chrdev_region(MKDEV(255, 10), 10);
    printk(KERN_INFO"%s\n", __func__);
    return;
}
module_exit(gpio_exit);


MODULE_LICENSE("GPL v2");
