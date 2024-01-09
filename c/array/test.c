#include <stdio.h>
#include <stdlib.h>

#define IFNAMSIZ 16
#define DRIVER_NAME_LEN 32

struct pci_device {
	int vendor;
	int device;
	char pci_addr[IFNAMSIZ];
	char ifname[IFNAMSIZ];
	char driver[DRIVER_NAME_LEN];

	struct pci_device *next;
};

struct pci_device *pd;



int sizeof_arr(char *arr){
    return sizeof(arr);
}

int main(int argc, char* argv[])

  {
    pd = (struct pci_device *)malloc(sizeof(struct pci_device));
	char arr[]="123456789abcde";
    printf("sizeof arr is %d\n", sizeof(arr));
    printf("sizeof arr is %d\n", sizeof_arr(arr));
    printf("sizeof arr is %d\n", sizeof((pd->driver)));
    return 0;
  }