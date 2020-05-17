#include "usr_test.h"



int main(int argc ,char *argv[])
{
    int fd;
    int ret = 0;
    struct input_event event;



    fd = open(DEV_NAME, O_RDWR);
    if(fd < 0)
    {
        printf("%s:open failed\n", __FUNCTION__);
        return -1;
    }
    printf("%s:%d\n", __FUNCTION__, __LINE__);

    while(1)
    {
	printf("%s:%d\n", __FUNCTION__, __LINE__);
	ret = read(fd, &event, sizeof(struct input_event));
	printf("%s:%d\n", __FUNCTION__, __LINE__);
	if(ret >= 0)
	{
		printf("%s:%d\n", __FUNCTION__, __LINE__);
		printf("type=%d code=%d value=%d\n", event.type, event.code, event.value);
	}

    }

    return 0;
}


