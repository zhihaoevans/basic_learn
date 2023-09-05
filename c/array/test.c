#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int dpdk_get_coremask_from_string(const char *str, unsigned char *core_mask)
{
	const char *p, *q;
	int idx = 0;
	char tmp[17]={0}; 

	p = strstr(str, "0x");
	if(p){
		p = p + 2;
	}else{
		p = str;
	}

	q = p + strlen(p);
	while((q>p) && (idx < 2)){
		memset(tmp, 0, sizeof(tmp));
		if((q - 16) <= p){
			strncpy(tmp, p, q-p);
		}else{
			strncpy(tmp, q-16, 16);
		}
		core_mask[idx] = strtoull(tmp, NULL, 16);
		idx++;
		q-=16;
	}

	return 0;
}

int main() {
    
    unsigned char arr[2];

    dpdk_get_coremask_from_string("1234", arr);
    printf("arr[0] %2x\n", arr[0]);
    printf("arr[1] %2x\n", arr[1]);

    return 0;
}
