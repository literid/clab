#include "nvector.h"

Vector* vscan(type tp) {

	Vector* vptr;

	printf("\nenter the size of vector\n");

	int size;
	scanf("%d",&size);
  
    if (tp == INT) {
    	vptr = vcreate(INT,size);
    	printf("\nenter %d integer elements\n", size);
    	
    	int temp;
    	for (int i = 0; i < size; ++i) {
    		scanf("%d",&temp);
    		vset_elem(vptr,i,&temp);
    	}
    }

    if (tp == COMPLEX){
    	vptr = vcreate(COMPLEX,size);
    	printf("\nenter %d complex elements", size);

    	double img,real;

    	for (int i = 0; i < size; ++i) {
    		printf("\nreal part ");
    		scanf("%le",&real);
    		printf("image part ");
    		scanf("%le",&img);
    		complex z = CMPLX(real,img);
    		vset_elem(vptr,i,&z);
    	}
    }
 	
 	return vptr;
}

void ui () {
	int choice;

	Vector* varr[6] = {NULL} ;

	void clean() {

		for (int i = 0; i < 6; ++i) {
			if (varr[i] != NULL) {
			vfree(varr[i]);
			}
		}
	}

	while(1){
		printf("%s\n",
			"1. set int vector1\n"
			"2. set int vector2\n"
			"3. set compl vector3\n"
			"4. set compl vector4\n"
			"5. get vector1 + vector2\n"
			"6. get vector3 + vector4\n"
			"7. get scalar multiply of int vectors\n"
			"8. get scalar multiply of compl vectors\n"
			"9. get elem\n"
			"10. delete choosen vector\n"
			"11. exit\n"
		);

		int* iscr;
		complex* cscr;
		scanf("%d", &choice); 
		
		switch(choice) {
			case 1:
				if (varr[0] != NULL) {
					free(varr[0]);
				}
				varr[0] = vscan(INT);
				printf("vector1 = ");
				vprint(varr[0]);
				break;
			case 2:
				if (varr[1] != NULL) {
					free(varr[1]);
				}
				varr[1] = vscan(INT);
				printf("vector2 = ");
				vprint(varr[1]);
				break;
			case 3:
				if (varr[2] != NULL) {
					free(varr[2]);
				}			
				varr[2] = vscan(COMPLEX);
				printf("vector3 = ");
				vprint(varr[2]);
				break;
			case 4:
				if (varr[3] != NULL) {
					free(varr[3]);
				}			
				varr[3] = vscan(COMPLEX);
				printf("vector4 = ");
				vprint(varr[3]);
				break;				
			case 5:
				if ((varr[0] == NULL) || (varr[1] == NULL)) {
					clean();
					printf("error: null vector\n");
					exit(1);
				}

				if (varr[4] != NULL) {
					free(varr[4]);
				}

				varr[4] = vadd(varr[0], varr[1]);
				printf("vector5 = ");
				vprint(varr[4]);
				break;
			case 6:
				if ((varr[2] == NULL) || (varr[3] == NULL)) {
					clean();
					printf("error: null vector\n");
					exit(1);
				}

				if (varr[5] != NULL) {
					free(varr[5]);
				}

				varr[5] = vadd(varr[2], varr[3]);
				printf("vector6 = ");
				vprint(varr[5]);
				break;
			case 7:
				if ((varr[0] == NULL) || (varr[1] == NULL)) {
					clean();
					printf("error: null vector\n");
					exit(1);
				}

				iscr = (int*)vscal_mult(varr[0], varr[1]);
				printf("%d\n",*iscr);
				free(iscr);
				break;
			case 8:
				if ((varr[2] == NULL) || (varr[3] == NULL)) {
					clean();
					printf("error: null vector\n");
					exit(1);
				}
				
				cscr = (complex*)vscal_mult(varr[2], varr[3]);
				printf("%g %+gi\n",creal(*cscr),cimag(*cscr));
				free(cscr);
				break;
			case 9:
				printf("enter the number of vector\n");
				int num1;
				scanf("%d",&num1);

				if ((num1 < 1) && (num1 > 6)) {
					clean();					
					exit(1);
				}

				if (varr[num1-1] == NULL) {
					clean();
					printf("error: null vector\n");
					exit(1);
				}

				int ind;
				printf("enter index\n");
				scanf("%d",&ind);

				if (varr[num1-1]->str_type == INT) {
					printf("%d\n",*(int*)vget_elem(varr[num1-1],ind));
				} else {
					complex tmp = *(complex*)vget_elem(varr[num1-1],ind);
					printf("%g %+gi\n",creal(tmp),cimag(tmp));
				}
				break;	
			case 10:
				printf("enter the number of vector to delete ");
				int num;
				scanf("%d",&num);

				if ((num >= 1) && (num <= 6) && (varr[num-1] != NULL)) {
					vfree(varr[num-1]);
					varr[num-1] = NULL;
				} else {
					clean();
					printf("error: null vector\n");
					exit(1);
				}
				break;	
			case 11:
				clean();
				return;
			default:
				clean();
				exit(1);
				break;		
		}
	}
}

int main() {
	ui();
}