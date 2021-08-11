#include <linux/init.h>
#include <linux/module.h>
#include <linux/scatterlist.h>
#include <linux/slab.h>
#include "xdma-sgm.h"

#define MAP_SIZE (1024*1024*8)

struct pci_map_drv {
    struct scatterlist *sgl;
    struct sg_mapping_t *sgm;
};

struct pci_map_drv demo;




static int __init pci_init(void)
{
    printk(KERN_INFO"%s PAGE_OFFSET:%x, sz_16M:%x,task_size:%lx\n", __func__, CONFIG_PAGE_OFFSET, SZ_16M, TASK_SIZE);
    demo->sgm = sg_create_mapper(MAP_SIZE);
    pci_map_sg()
    return 0;
}
module_init(pci_init);

static void __exit pci_exit(void)
{
    sg_destroy_mapper(demo->sgm);
    printk(KERN_INFO"%s\n", __func__);
    return;
}
module_exit(pci_exit);


MODULE_LICENSE("GPL v2");
