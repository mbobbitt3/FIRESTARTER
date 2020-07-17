#ifndef batchlib_h__
#include "msr_safe.h"
#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>
#include<stdint.h>
#include<string.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include<errno.h>
#include<assert.h>
#include<stdlib.h>
#include<stdbool.h>
#define batchlib_h__
extern int add_readops_to_batch(struct msr_batch_array *batch, __u16 firstcpu, __u16 lastcpu, __u32 msr);
extern int add_writeop_to_batch(struct msr_batch_array *batch, __u16 cpu, __u32 msr, __u64 writemask);
extern void check_msr();
extern void print_approved_list();
extern bool msr_read_check(uint32_t address);
extern bool msr_write_check (uint32_t address, uint64_t value);
extern int add_writeops_to_batch(struct msr_batch_array *batch, __u16 first_cpu,__u16 last_cpu, __u32 msr, __u64 writemask);
extern int print_op(struct msr_batch_op *op);
extern int print_batch( struct msr_batch_array *batch);
extern int run_batch(struct msr_batch_array *batch);

#endif

