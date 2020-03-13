#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <complex.h>

typedef enum {INT = 1, COMPLEX} type;	

typedef struct {
	void* buffer;
	int count;
	type str_type;
} Vector;

Vector* vcreate(type str_type,int count) {
    
    if (count <= 0 ) {
    	printf("error: wrong size\n");
    	exit(1);
    }

    if ((str_type < 1) || (str_type > 2)) {
    	printf("error: wrong type\n");
    	exit(1);
    }

    Vector* vptr = (Vector*)malloc(sizeof(Vector));
    
    int elem_size;
    switch(str_type) {
    	case INT:
    		elem_size = sizeof(int);
    		break;
    	case COMPLEX:
    		elem_size = sizeof(complex);
    		break;
    	default : 
    		break;
    }

    vptr->str_type = str_type;
    vptr->count = count;
    vptr->buffer = malloc(count*elem_size);

    return vptr;
}

void* vget_elem(Vector* vec,int index) {
	
	if ((index < 0) || (index >= vec->count)) {
		printf("error: index out of range\n");
		exit(1);
	}

	if (vec == NULL) {
		printf("error: null vector\n");
		exit(1);
	}

    switch(vec->str_type) {
    	case INT:
    		return ((int*)(vec->buffer)+index);
    		break;
    	case COMPLEX:
    		return ((complex*)(vec->buffer)+index);
    		break;
    	default : 
    		break;
    }
} 

void vset_elem(Vector* vec, int index, void* value) {
    
    if (vec == NULL) {
		printf("error: null vector\n");
		exit(1);
	}

    int elem_size;
    
    switch(vec->str_type) {
    	case INT:
    		elem_size = sizeof(int);
    		break;
    	case COMPLEX:
    		elem_size = sizeof(complex);
    		break;
    	default : 
    		break;
    }

    void *p = (char*)vec->buffer + index*elem_size;
    memcpy(p, value, elem_size);
}

Vector* vadd(Vector* vec1, Vector* vec2) {
	
	if ((vec1 == NULL) || (vec2 ==NULL)) {
		printf("error: null vector\n");
		exit(1);
	}	

	if ((vec1->str_type != vec2->str_type) || (vec1->count != vec2->count)) {
		printf("error: wrong types format\n");
		exit(1);
	}

	Vector* vptr = vcreate(vec1->str_type, vec1->count);
	
	for (int i = 0; i < vec1->count; ++i) {
		if (vec1->str_type == INT) {
			((int*)vptr->buffer)[i] = ((int*)vec1->buffer)[i] + ((int*)vec2->buffer)[i];
		} else if (vec1->str_type == COMPLEX) {
			((complex*)vptr->buffer)[i] = ((complex*)vec1->buffer)[i] + ((complex*)vec2->buffer)[i];						
		}
	}

	return vptr;
}

void* vscal_mult(Vector* vec1, Vector* vec2) {
	
    if ((vec1 == NULL) || (vec2 ==NULL)) {
		printf("error: null vector\n");
		exit(1);
	}	

    switch(vec1->str_type) {
    	case INT:
			
			if ((vec1->count != vec2->count) || (vec1->str_type != INT) || (vec2->str_type != INT)) {
				printf("error: wrong types format\n");
				exit(1);
			} 

			int* ires = (int*)malloc(sizeof(int));
			*ires = 0;
				
			for (int i = 0; i < vec1->count; ++i) {
				*ires += ((int*)vec1->buffer)[i] * ((int*)vec2->buffer)[i];
			} 

			return(ires);
    		break;
    	case COMPLEX:
			
			if ((vec1->count != vec2->count) || (vec1->str_type != COMPLEX) || (vec2->str_type != COMPLEX)) {
				printf("error: wrong types format\n");
				exit(1);
			} 

			complex* cres = (complex*)malloc(sizeof(complex));;
					
			for (int i = 0; i < vec1->count; ++i) {
				*cres += ((complex*)vec1->buffer)[i] * conj(((complex*)vec2->buffer)[i]);						
			}
				
			return cres;	    		
  	 		break;
    	default : 
    		break;
    }
} 

void vfree(Vector* vec) {
	
	if (vec == NULL) {
		printf("error: null vector\n");
		exit(1);
	}

	free(vec->buffer);
	free(vec);
}

void vprint(Vector* vec) {
	
	if (vec == NULL) {
		printf("error: null vector\n");
		exit(1);
	}

	for (int i = 0; i < vec->count ; ++i) {
		if (vec->str_type == COMPLEX) { 
			printf("%g %+gi ",creal(((complex*)vec->buffer)[i]),cimag(((complex*)vec->buffer)[i]));
		} else {	 
			printf("%d ",((int*)vec->buffer)[i]);
		}	
	};

	printf("\n");
}
