#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
*/

#define IFNAMSIZ 16

int bypass_portid_pair[4] = {1,0,3,2};

int is_elem_in_arr(int elem, int tmp[IFNAMSIZ]){
	int i;
	for(i = 0; i < IFNAMSIZ; i++){
		if(elem == tmp[i]){
			return 1;
		}
	}
	return 0;
}

void disp_bypass_pair_show(void){

	int i = 0;
	int nports_total = 4;

	int j = 0;
	int tmp[IFNAMSIZ];

	
	memset(tmp, -1, sizeof(tmp));
	
	for(i = 0; i < nports_total; i++){
		if(is_elem_in_arr(i, tmp) || is_elem_in_arr(bypass_portid_pair[i], tmp)){
			continue;
		}
        printf("hello");
		tmp[j++] = i;
		tmp[j++] = bypass_portid_pair[i];
	}
    printf("j is %d\n", j);
}

int main(int argc, char* argv[])
{
    disp_bypass_pair_show();
	return 0;
}
