#include <linux/init.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/poll.h>
#include <linux/wait.h>
#include <linux/cdev.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <asm/ioctl.h>

#define POLL_DEV_NAME "poll"

#define POLL_MAGIC 'P'
#define POLL_SET_COUNT      (_IOW(POLL_MAGIC, 0, unsigned int))

struct poll_dev {
    struct cdev cdev;
    struct class *class;
    struct device *device;

    wait_queue_head_t wq_head;

    struct mutex poll_mutex;
    unsigned int count;

    dev_t devno;

};

struct poll_dev *g_poll_dev = NULL;

static int poll_open(struct inode *inode, struct file *filp)
{
    filp->private_data = g_poll_dev;

    return 0;

}

static int poll_close(struct inode *inode, struct file *filp)
{
    return 0;

}

static unsigned int poll_poll(struct file *filp, struct poll_table_struct *wait)
{
    unsigned int mask = 0;
    struct poll_dev *dev = filp->private_data;

    mutex_lock(&dev->poll_mutex);

    poll_wait(filp, &dev->wq_head, wait);

    if (dev->count > 0) {
        mask |= POLLIN | POLLRDNORM;

        /* decrease each time */
        dev->count--;

    }
    mutex_unlock(&dev->poll_mutex);

    return mask;

}

static long poll_ioctl(struct file *filp, unsigned int cmd,
        unsigned long arg)
{
    struct poll_dev *dev = filp->private_data;
    unsigned int cnt;

    switch (cmd) {
        case POLL_SET_COUNT:
            mutex_lock(&dev->poll_mutex);
            if (copy_from_user(&cnt, (void __user *)arg, _IOC_SIZE(cmd))) {
                pr_err("copy_from_user fail:%d\n", __LINE__);
                return -EFAULT;

            }

            if (dev->count == 0) {
                wake_up_interruptible(&dev->wq_head);

            }

            /* update count */
            dev->count += cnt;

            mutex_unlock(&dev->poll_mutex);
            break;
        default:
            return -EINVAL;

    }

    return 0;

}

static struct file_operations poll_fops = {
    .owner = THIS_MODULE,
    .open = poll_open,
    .release = poll_close,
    .poll = poll_poll,
    .unlocked_ioctl = poll_ioctl,
    .compat_ioctl = poll_ioctl,

};

static int __init poll_init(void)
{
    int ret;

    if (g_poll_dev == NULL) {
        g_poll_dev = (struct poll_dev *)kzalloc(sizeof(struct poll_dev), GFP_KERNEL);
        if (g_poll_dev == NULL) {
            pr_err("struct poll_dev allocate fail\n");
            return -1;

        }

    }

    /* allocate device number */
    ret = alloc_chrdev_region(&g_poll_dev->devno, 0, 1, POLL_DEV_NAME);
    if (ret < 0) {
        pr_err("alloc_chrdev_region fail:%d\n", ret);
        goto alloc_chrdev_err;

    }

    /* set char-device */
    cdev_init(&g_poll_dev->cdev, &poll_fops);
    g_poll_dev->cdev.owner = THIS_MODULE;
    ret = cdev_add(&g_poll_dev->cdev, g_poll_dev->devno, 1);
    if (ret < 0) {
        pr_err("cdev_add fail:%d\n", ret);
        goto cdev_add_err;

    }

    /* create device */
    g_poll_dev->class = class_create(THIS_MODULE, POLL_DEV_NAME);
    if (IS_ERR(g_poll_dev->class)) {
        pr_err("class_create fail\n");
        goto class_create_err;

    }
    g_poll_dev->device = device_create(g_poll_dev->class, NULL,
            g_poll_dev->devno, NULL, POLL_DEV_NAME);
    if (IS_ERR(g_poll_dev->device)) {
        pr_err("device_create fail\n");
        goto device_create_err;

    }

    mutex_init(&g_poll_dev->poll_mutex);
    init_waitqueue_head(&g_poll_dev->wq_head);

    return 0;

device_create_err:
    class_destroy(g_poll_dev->class);
class_create_err:
    cdev_del(&g_poll_dev->cdev);
cdev_add_err:
    unregister_chrdev_region(g_poll_dev->devno, 1);
alloc_chrdev_err:
    kfree(g_poll_dev);
    g_poll_dev = NULL;
    return -1;

}

static void __exit poll_exit(void)
{
    cdev_del(&g_poll_dev->cdev);
    device_destroy(g_poll_dev->class, g_poll_dev->devno);
    unregister_chrdev_region(g_poll_dev->devno, 1);
    class_destroy(g_poll_dev->class);

    kfree(g_poll_dev);
    g_poll_dev = NULL;

}

module_init(poll_init);
module_exit(poll_exit);

MODULE_DESCRIPTION("select demo");
MODULE_AUTHOR("songzhenhao");
MODULE_LICENSE("GPL v2");
