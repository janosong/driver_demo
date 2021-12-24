#include <linux/init.h>
#include <linux/module.h>
#include <linux/mm_types.h>
#include <linux/mm.h>
#include <asm/fixmap.h>
#include <asm/highmem.h>
#include <linux/hash.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>


#define PRT 1
#ifdef PRT
#define PRINT_A(x) (\
    printk(KERN_INFO #x":%d %p\n", sizeof(x), &x))
#define PRINT(x) (\
    printk(KERN_INFO #x":%x \n", (x)))
#else
#define PRINT_A(x)
#define PRINT(x)
#endif

static __attribute__((unused)) void print_task(void)
{
    __attribute__((unused)) struct mm_struct *mm = current->mm;
    __attribute__((unused)) struct mm_struct *active_mm = current->active_mm;
    __attribute__((unused)) struct vm_area_struct *mmap = mm->mmap;
    __attribute__((unused)) struct vm_area_struct *vm_end = mmap->vm_prev;

    printk(KERN_INFO"\n*******task**********\n");
    PRINT(current->pid);
    PRINT(mm);
    PRINT(active_mm);
    PRINT(mm->start_code);
    PRINT(mm->end_code);
    PRINT(mm->start_data);
    PRINT(mm->end_data);
    PRINT(mm->start_brk);
    PRINT(mm->brk);
    PRINT(mm->start_stack);
    PRINT(mm->arg_start);
    PRINT(mm->arg_end);
    PRINT(mm->env_start);
    PRINT(mm->env_end);
    PRINT(mm->total_vm);

#if 0
    for (; mmap || (mmap==vm_end); mmap = mmap->vm_next) {
        PRINT(mm->mmap);
        PRINT(mmap->vm_start);
        PRINT(mmap->vm_end);
    }
#endif
}

static __attribute__((unused))void print_page(void)
{
    struct page pg;

    printk(KERN_INFO"\n");

    //printk(KERN_INFO"%s PAGE_OFFSET:%lx, sz_16M:%lx,task_size:%lx\n", __func__, CONFIG_PAGE_OFFSET, SZ_16M, TASK_SIZE);
    //printk(KERN_INFO"size page:%d \n", sizeof(struct page));
    //printk(KERN_INFO"PHYS_OFFSET:%x \n", PHYS_OFFSET);

    PRINT(PHYS_OFFSET);
    PRINT(PAGE_OFFSET);
    PRINT(MAX_NR_ZONES);
    PRINT(high_memory);
    PRINT(VMALLOC_END);
    PRINT(VMALLOC_OFFSET);
    PRINT(FIXADDR_START);
    PRINT(FIXADDR_END);
    PRINT(FIXADDR_TOP);

    PRINT(mem_map);
    PRINT(ARCH_PFN_OFFSET);
    PRINT(kmap_prot);


    pg.counters = 1;

    PRINT_A(pg);
    PRINT_A(pg.flags);
    PRINT_A(pg.mapping);

    PRINT_A(pg.index);
    PRINT_A(pg.counters);
    PRINT_A(pg.active);
    PRINT_A(pg._refcount);

    PRINT_A(pg.lru);
    PRINT_A(pg.next);
    PRINT_A(pg.pages);
    PRINT_A(pg.pobjects);


    PRINT_A(pg.slab_cache);
    PRINT_A(pg.mem_cgroup);

    PRINT(hash_ptr(&pg, 7));

}

static ssize_t dmoe_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
    return size;
}
int demo_open(struct inode *inode, struct file *filp)
{
    PRINT(current->pid);
    PRINT(filp);
    return 0;
}
int demo_release(struct inode *inode, struct file *fp)
{
    return 0;
}
int demo_poll(struct file *filp, struct poll_table_struct *wait)
{
    PRINT(filp);
    return 0;
}
#define DEVNAME "test_demo"
static struct demo {
    struct class *class;
    struct cdev cdev;
    dev_t devno;
} g_demo;

static const struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = demo_open,
    .read = NULL,
    .release = demo_release,
};

static void init_cdev(void)
{
    int ret = 0;
    ret = alloc_chrdev_region(&g_demo.devno, 0, 1, DEVNAME);

    cdev_init(&g_demo.cdev, &fops);
    g_demo.cdev.owner = THIS_MODULE;
    g_demo.cdev.ops = &fops;

    cdev_add(&g_demo.cdev, g_demo.devno, 2);

    g_demo.class = class_create(THIS_MODULE, DEVNAME);
    device_create(g_demo.class, NULL, g_demo.devno, NULL, DEVNAME);

    printk(KERN_INFO DEVNAME" init\n");

}

static void uinit_cdev(void)
{
    device_destroy(g_demo.class, g_demo.devno);
    class_destroy(g_demo.class);

    cdev_del(&g_demo.cdev);   /*注销设备*/
    unregister_chrdev_region(g_demo.devno, 2); /*释放设备号*/
    printk(KERN_INFO DEVNAME" uninit\n");
}

static int __init demo_init(void)
{
    print_task();
    init_cdev();
    return 0;
}
module_init(demo_init);

static void __exit demo_exit(void)
{
    printk(KERN_INFO"%s\n", __func__);
    uinit_cdev();
    return;
}
module_exit(demo_exit);


MODULE_AUTHOR("Jano Song");
MODULE_LICENSE("GPL v2");
