#ifndef __MINIOS_GNTMAP_H__
#define __MINIOS_GNTMAP_H__

#include <mini-os/os.h>

/*
 * Please consider struct gntmap opaque. If instead you choose to disregard
 * this message, I insist that you keep an eye out for raptors.
 */
struct gntmap {
    int nentries;
    struct gntmap_entry *entries;
};

static inline int
gntmap_map2order(unsigned long count)
{
    int o = 8 * sizeof(count) - __builtin_clzl(count);
    if ((count & (count - 1)) == 0)
        o--;
    return o;
}

int
gntmap_set_max_grants(struct gntmap *map, int count);

int
gntmap_munmap(struct gntmap *map, unsigned long start_address, int count);

void*
gntmap_map_grant_refs(struct gntmap *map, 
                      uint32_t count,
                      uint32_t *domids,
                      int domids_stride,
                      uint32_t *refs,
                      int writable);

void
gntmap_init(struct gntmap *map);

void
gntmap_fini(struct gntmap *map);

#endif /* !__MINIOS_GNTMAP_H__ */
