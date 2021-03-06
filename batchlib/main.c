#include "msr_safe.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "batch.h"

int main(){
	int rc;
	struct msr_batch_array my_batch;
	my_batch.numops = 0;
	my_batch.ops = NULL;

    	add_readop( &my_batch, 0x611);
	parse_msr_approved_list();
   	msr_write_check(0xe7, 0); 
	rc = run_batch(&my_batch);
	
	printf("%d", rc);
	return 0;
}
