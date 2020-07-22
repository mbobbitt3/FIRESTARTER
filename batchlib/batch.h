#ifndef batchlib_h__
#define batchlib_h__

#include "msr_safe.h"
#include <inttypes.h>
#include <stdbool.h>

extern int add_readops_to_batch(struct msr_batch_array *batch, __u16 firstcpu, __u16 lastcpu, __u32 msr);
extern int add_writeops_to_batch(struct msr_batch_array *batch, __u16 first_cpu,__u16 last_cpu, __u32 msr, __u64 writemask);

extern void init_msr_list();
extern void print_approved_list();
extern bool msr_read_check(uint32_t address);
extern bool msr_write_check (uint32_t address, uint64_t value);
extern int print_op(struct msr_batch_op *op);
extern int print_batch( struct msr_batch_array *batch);
extern int run_batch(struct msr_batch_array *batch);

#endif

