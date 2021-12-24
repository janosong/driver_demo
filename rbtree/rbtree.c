#include <stdio.h>


struct rb_node {
    unsigned long  __rb_parent_color;
    struct rb_node *rb_right;
    struct rb_node *rb_left;

} __attribute__((aligned(sizeof(long))));
/* The alignment might seem pointless, but allegedly CRIS needs it */

struct rb_root {
    struct rb_node *rb_node;

};


struct eventpoll {
    struct rb_root rbr;
};

struct epitem {
    struct rb_node rbn;
};

static inline void rb_link_node(struct rb_node *node, struct rb_node *parent,
                        struct rb_node **rb_link)
{
    node->__rb_parent_color = (unsigned long)parent;
    node->rb_left = node->rb_right = NULL;

    *rb_link = node;

}

static void ep_rbtree_insert(struct eventpoll *ep, struct epitem *epi)
{
    int kcmp;
    struct rb_node **p = &ep->rbr.rb_node, *parent = NULL;
    struct epitem *epic;

    while (*p) {
        parent = *p;
        p = &parent->rb_right;

    }
    rb_link_node(&epi->rbn, parent, p);

}

int main()
{
    struct rb_node node = {0};
    //struct rb_root root = {.rb_node = &node};
    struct eventpoll ep = {.rbr.rb_node = &node};
    struct epitem epi = {0};
    ep_rbtree_insert(&ep, &epi);
    return 0;
}
