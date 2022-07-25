#include <stdio.h>
#include <stdlib.h>

/* Declare dynamic arrays and global variables*/
int *resource = NULL;
int *available = NULL;
int *max_claim = NULL;
int *allocated = NULL;
int *need = NULL;

int num_process;
int num_resource;

/***********************************************************/
void printvector() {
	/* declare local variables */
    int i;
	/* for loop: print each resource index */
	   /* print number of total units and available units of each resource index ""resource[i] and available[i]"""*/
    
    printf("units\tavailable\n");
    for (i=0; i< num_resource ;i++) {
       printf("%d", resource[i]);
       printf("\t");
       printf("%d", available[i]);
       printf("\n");
    }
    return;
}

/***************************************************************/
void printmatrix() { 
	/* declare local variables */
   int i, j;
	
   /* for each process: */
	  /* for each resource: */
			/* print maximum number of units each process may request, is allocated, and needs from each resource */
	
	printf("\nMaximum\t\t\tCurrent\t\t\tPotential\n");
	for(i=0; i< num_process; i++) {
      for(j=0; j< num_resource; j++) {
          printf("%d\t", max_claim[i*num_resource+j]);
          }
      for(j=0; j< num_resource; j++) {
          printf("%d\t", allocated[i*num_resource+j]);
          }
      for(j=0; j< num_resource; j++) {
          printf("%d\t", need[i*num_resource+j]);
          }
       printf("\n");
      }
   
   return;
}


/****************************************************************/
void option1() {
	/* declare local variables */
   int i, j;
   // int num_process;
   // int num_resource;
	/* prompt for number of processes and number of resources */
   printf("enter total number of processes: ");
   scanf("%d", &num_process);
   printf("enter the total number of resources: ");
   scanf("%d", &num_resource);
	/* allocate memory for vectors and arrays: resource, available, max_claim, allocated, need */
   resource = (int *)malloc(num_resource * sizeof(int));
   available = (int *)malloc(num_resource * sizeof(int));
   
   max_claim = (int *)malloc(num_process * num_resource * sizeof(int));
   allocated = (int *)malloc(num_process * num_resource * sizeof(int));
   need = (int *)malloc(num_process * num_resource * sizeof(int));
   
   /* for each resource, prompt for number of units, set resource and available vectors indices*/
    printf("enter number of units: \n");
    for(int j=0; j< num_resource; j++) {
       
       scanf("%d", &resource[j]);
       available[j] = resource[j];
       }
	/* for each process, for each resource, prompt for maximum number of units requested by process, update max_claim and need arrays */ 
	    /* for each process, for each resource, prompt for number of resource units allocated to process */
    printf("enter the max claim: \n");
    for(int i=0; i< num_process; i++) {
      for(int j=0; j< num_resource; j++) {
          
          scanf("%d", &max_claim[i * num_resource + j]); 
          need[i * num_resource + j] = max_claim[i * num_resource + j];
    }
    }
    printf("enter the allocated: \n");
    for(int i=0; i< num_process; i++) {
      for(int j=0; j< num_resource; j++) {
          
          scanf("%d", &allocated[i * num_resource + j]); 
          
          need[i * num_resource + j] -= allocated[i * num_resource + j]; 
          available[j] -= allocated[i * num_resource + j]; 
    }
    }
	/* print vector, matrices*/
    
    printvector();
    printmatrix();
	return;
}


/********************************************************************/
void option2() {

	/* declare local variables, including vector to indicate if process is safely sequenced and "num_sequenced" count*/
int i,j;
int finished=0;
int *sequenced = (int *)calloc(num_process, sizeof(int));
int at_least_one =1;
int less_than_or_equal =1;
		
	/* while not all processed are sequenced */
   while ((finished < num_process) && (at_least_one==1)) {
      at_least_one = 0;
		/* for each process */ 
			/* if process has not been safely sequenced yet 8? */
      for (i=0; i<num_process ; i++) {
          less_than_or_equal = 1;
          if (sequenced[i]==0) {
				/* for each resource */
            for (j=0; j<num_resource; j++) {
                printf("%d", need[i*num_resource+j]);
                printf("\t");
                }
					/* check for safe sequencing by comparing process' need vector to available vector */
	      		               
                                 /* if each resource is available */
					/* print message that process had been safely sequenced */
             for (j=0; j<num_resource; j++) {
                 printf("%d", available[j]);
                 printf("\t");
                }
             for (j=0; j<num_resource; j++) {
                less_than_or_equal &= (need[i*num_resource+j] <= available[j]);

              }
             
             if (less_than_or_equal == 1) {
               at_least_one = 1;
               printf("p[%d] sequence successed \n", i);
               printf("\n");
          
					/* update number of available units of resource */
               
					/* for each resource */
                for (j=0; j<num_resource; j++) {
						/*free all resources allocated to process */
                    available[j] += allocated[i*num_resource+j];
                    allocated[i*num_resource+j] = 0;
               } 
						/* increment number of sequenced processes */
                  finished ++;
                  sequenced[i] = 1;
                  }
               else {
                  printf("p[%d] sequence failed \n", i);
                  printf("\n");
                  }
                  }
                  }
                  printf("finished: %d", finished);
                  printf("\n");
                  }
                  if(at_least_one == 0) {
                     printf("have reached a deadlock");
                     }
return;
}


/********************************************************************/
void option3() {
	/* check if vectors/array are not NULL--if so, free each vector/array */
    if (resource != NULL) {
       free(resource);
       free(available);
       free(max_claim);
       free(allocated);
       free(need);
       printf("quiting program");
       exit(0);
    } 
    
	return;
}


/***************************************************************/
int main() {
  int choice = 0;
  
  while (choice != 5) {
     printf("\nBanker's algorithm\n");
     printf("--------------------------------\n");
     printf("1) Enter parameters\n");
     printf("2) Determine safe sequence\n");
     printf("3) quit program\n");

     printf("\nEnter selection: ");
     scanf("%d", &choice);
    
     switch(choice) {
        case 1: option1();
        break;
        case 2: option2();
        break;
        case 3: option3(); 
        break;
        default: 
        printf("Invalid option!\n"); 
        break;
     }    
   }    
  return 1;
}