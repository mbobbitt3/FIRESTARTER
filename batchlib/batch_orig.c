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
#define max_ops (10000)
/* This is what is included from msr_safe.h.
 * Included here for reference.
 
struct msr_batch_op
{
    __u16 cpu;     // In: CPU to execute {rd/wr}msr instruction
    __u16 isrdmsr; // In: 0=wrmsr, non-zero=rdmsr
    __s32 err;     // Out: set if error occurred with this operation
    __u32 msr;     // In: MSR Address to perform operation
    __u64 msrdata; // In/Out: Input/Result to/from operation
    __u64 wmask;   // Out: Write mask applied to wrmsr
};

struct msr_batch_array
{
    __u32 numops;             // In: # of operations in operations array
    struct msr_batch_op *ops; // In: Array[numops] of operations
};

#define X86_IOC_MSR_BATCH   _IOWR('c', 0xA2, struct msr_batch_array)

*/

// How to staticly allocate memory.
//struct msr_batch_op mybatch[5][10000];

// Determine size of an array:
// sizeof( struct msr_batch_op )

//
// Function declarations (fill these in for each funciton below)
//
int print_op( struct msr_batch_op *op );
//
// Function defintions
//

// Adds a read operation to the batch.  Returns the index of the new
// op or -1 on error.  Duplicate this for write ops.
/*
int add_readop_to_batch(struct msr_batch_array *batch, __u16 cpu, __u32 msr){
    batch->numops = batch->numops+1;  // Adding one more op.
    batch->ops = realloc( batch->ops, sizeof(struct msr_batch_op) * batch->numops );
    batch->ops[numops-1].cpu = cpu;
    batch->ops[numops-1].isrdmsr = 1;
    batch->ops[numops-1].err = 0;
    batch->ops[numops-1].msr = msr;
    batch->ops[numops-1].msrdata = 0;
    batch->ops[numops-1].wmask = 0;

    printf("MSR value: %" PRIx64 "\n" "CPU core: %" PRIu16, 
            batch->ops[numops-1].msrdata,
            batch->ops[numops-1].cpu);

return 0;


}

*/

/*
    first call to add_readop_to_batch using malloc
    malloc returns 0xFFFFFFFFF3847100, the first byte of the 32 bytes that were allocated.
    That value is saved in batch->ops

    second call 
    malloc returns 0xFAAAAFFFF3847100, the first byte of the 32 bytes that were allocated.
    That value is saved in batch->ops
 
    Alternatively
    first call to add_readop_to_batch using realloc
    batch-ops was initialized to NULL by the caller.
    realloc returns 0xFFFFFFFFF3847100, the first byte of the 32 bytes that were allocated.
    That value is saved in batch->ops

    second call 
    realloc called with 64 bytes and pointer 0xFFFFFFFFF3847100
    realloc returns 0xFAAAFFFFF3847100.  It has copied 64 bytes from 0xFFFFFFFFF3847100
      and then freed that memory.  In short, it has appened 32 bytes to the previous 32
      bytes, and if needed, found a new home for that in memory where it will fit.
    That value is saved in batch->ops

*/


// Adds multiple read operations to the batch, each to be run on
// a different cpu.  Returns the index of the first op or -1 on error.
// Duplicate this for write ops.


int fd, rc;

struct msr{
	uint32_t address;
    	uint64_t writemask;
};
static struct msr *msr_list = NULL;
static uint32_t msr_count;
#define MSR_BUF_SIZE (1023)
int main(){
	return 0;
}
int add_readops_to_batch(struct msr_batch_array *batch, __u16 firstcpu, __u16 lastcpu, __u32 msr){
    int i;
    //make an if statement that nakes sure tha firstcpu < lastcpu
    if(firstcpu > lastcpu){	 
	 printf(" first cpu should be < last cpu.");
	 exit(-1);
    }
    

	
    batch->numops = batch->numops+(lastcpu-firstcpu)+1;
    batch->ops = realloc( batch->ops, sizeof(struct msr_batch_op) * batch->numops );
    for(i = firstcpu; i <= lastcpu; i++){
        batch->ops[i].cpu = i;
        batch->ops[i].isrdmsr = 1;
        batch->ops[i].err = 0;
        batch->ops[i].msr = msr;
        batch->ops[i].msrdata = 0;
        batch->ops[i].wmask = 0;
	
printf("MSR Add: %" PRIx32 " MSR value: %llu"  " CPU core: %" PRIu16 "\n",
	batch->ops[i].msr,
        batch->ops[i].msrdata,
        batch->ops[i].cpu);
    	
    }
#if DEBUG
	if(batch->ops[i].err == -13){
		perror("MSR permission error check msr_approved_list to make sure MSR exists and is readable");
		exit(-1);
	}
#endif
    return 0;

}



/*
int add_writeop_to_batch(struct msr_batch_array *batch, __u16 cpu, __u32 msr, __u64 writemask){

        batch->numops = batch->numops+1;  // Adding one more op.
        batch->ops = realloc( batch->ops, sizeof(struct msr_batch_op) * batch->numops );
        batch->ops[numops-1].cpu = cpu;
        batch->ops[numops-1].isrdmsr = 0;
        batch->ops[numops-1].err = 0;
        batch->ops[numops-1].msr = msr;
        batch->ops[numops-1].msrdata = 0;
        batch->ops[numops-1].wmask = writemask;

        printf("MSR value: %" PRIx64 "\n" "CPU core: %" PRIu16, 
            batch->ops[numops-1].msrdata,
            batch->ops[numops-1].cpu);
        return 0;
}*/


void check_msr(){
	FILE *fp;
	int rc;
	char buf[MSR_BUF_SIZE];
	fp = fopen("/dev/cpu/msr_approved_list", "r");

	if(fp == NULL){
		printf("File could not be opened check that you have read permissions and that the file exists");
		exit(-1);
	}

	while(fgets(buf, MSR_BUF_SIZE, fp) != NULL){
		if(buf[0] == '#'){
			continue;
		}
		msr_list = realloc( msr_list, sizeof( struct msr ) * ++msr_count );
        	rc = sscanf( buf, "0x%" PRIx32 " 0x%" PRIx64 "\n", &(msr_list[msr_count-1].address), &(msr_list[msr_count-1].writemask) );
        	if(rc < 2){
            		fprintf( stderr, "Ooops, don't know how to parse '%s'.\n", buf );
            		exit(-1);
     		}
	}

	if(msr_count == 0){
		fprintf(stderr, "msr_approved is readable but empty %s \n", buf);
		exit(-1);
	}

	assert(EOF != fclose(fp));	

}

void print_approved_list(){
	int i;
	assert( msr_list );

	for( i=0; i<msr_count; i++ ){
        	fprintf( stdout, "0x%08" PRIx32 " 0x%016" PRIx64 "\n", msr_list[i].address, msr_list[i].writemask );
	}
}

bool msr_read_check(uint32_t address){
	for( int i=0; i<msr_count; i++ ){
        	if( address == msr_list[i].address ){
         		return true;
        	}
    	}

	return false;
}

bool msr_write_check(uint32_t address, uint64_t value){
	for( int i=0; i<msr_count; i++ ){
        	if( address == msr_list[i].address ){
        		if( (msr_list[i].writemask | value ) == msr_list[i].writemask ){
               			 return true;
           		}
			
			else{
                		return false;
           		}
      		}
	}
    return false;
}

int add_writeops_to_batch(struct msr_batch_array *batch, __u16 first_cpu, __u16 last_cpu, __u32 msr, __u64 writemask){
	int i;
	
	if(first_cpu >= last_cpu){
		printf("in (firstcpu, lastcpu) first cpu should be < last cpu");
		exit(-1);
	}

	batch->numops = batch->numops+(last_cpu-first_cpu)+1;
	batch->ops = realloc( batch->ops, sizeof(struct msr_batch_op) * batch->numops );

	for(i = first_cpu; i <= last_cpu; i++){
	
		batch->ops[i].cpu = i;
        	batch->ops[i].isrdmsr = 1; 
        	batch->ops[i].err = 0;
        	batch->ops[i].msr = msr;
        	batch->ops[i].msrdata = 0;
        	batch->ops[i].wmask = writemask;

    		printf("MSR Add: %" PRIx32 " MSR value: %llu"  " CPU core: %" PRIu16 "\n",
    			batch->ops[i].msr,
        		batch->ops[i].msrdata,
        		batch->ops[i].cpu);
    	}
	
	if(batch->ops[i].err == -13){
		perror("MSR permission error check msr_approved_list to make sure MSR is writable");
		exit(-1);
	}

	return 0;  

}

// Print an indivdiual op via the msr_batch_op pointer.
int print_op( struct msr_batch_op *op ){
	
	printf("cpu: %" PRIu16 "  isrdmsr: %" PRIu16  " err: %" PRId32 "  msraddr: %" PRIx32 "  msrdata: %" PRIu64  "   wmask: %" PRIx64 " \n", 
		(uint16_t)op->cpu,
		(uint16_t)op->isrdmsr,
		(int32_t)op->err,
		(uint32_t)op->msr,
		(uint64_t)op->msrdata,
		(uint64_t)op->wmask);

	return 0;
}

// Print a full batch by the msr_batch_array pointer
//This function prints the number of operations in msr_batch_array.numops
//and then prints each of the ops contains in msr_batch_array.ops.
int print_batch( struct msr_batch_array *batch ){
	int i;
	printf("numops: %" PRIu32 "\n", (uint32_t)batch->numops);
	printf("operations in batch " PRIu32 "\n");
   
	for(i=0; i < batch->numops; i++){
        	print_op(&(batch->ops[i]));

    	}
	
	return 0;

}

// Print any ops that have errors by pointer.
/*
int print_error_ops( struct msr_batch_array *batch ){
}

// Actually run the batch.
*/
int run_batch( struct msr_batch_array *batch ){
	fd = open("/dev/cpu/msr_batch", O_RDWR);
   
	if(fd == -1){
		perror("err cannot access directory make sure permissions are set!");
    		exit(-1);
	}
	
	if(fd == -13){
		perror("error file or directory may not exist or be accessible");
		exit(-1);
		
	}
#if DEBUG
	for(i=0; i < batch->numops; i++){
        	print_op(&(batch->ops[i]));

    	}
#endif
	rc = ioctl(fd, X86_IOC_MSR_BATCH, batch);

#if DEBUG
	for(i=0; i < batch->numops; i++){
        	print_op(&(batch->ops[i]));

    	}
#endif
	if(rc == -13){
		perror("ioctl failed");
		fprintf(stderr,"%s::%d rc=%d \n Check that msr_safe kernel module is loaded and that the MSR exists", __FILE__, __LINE__, rc);
	}	
       	
	if(rc < 0){
		rc = rc * -1;
		perror("ioctl failed");
		fprintf(stderr, "%s::%d rc=%d\n", __FILE__, __LINE__, rc);

	exit(-1);
   } 
	return 0;	

}

