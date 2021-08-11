#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define DEV "/dev/mem_dev"
int main()
{
    FILE *fp = NULL;
    char Buf[128];


    /*打开设备文件*/
    fp = fopen(DEV,"r+");
    if (fp == NULL)
    {
        printf("Open Dev %s memdev Error!\n", DEV);
        return -1;
    }
    printf("open Dev:%s\n", DEV);

    /*写入设备*/
    strcpy(Buf,"memdev is char dev!");
    printf("Write BUF: %s\n",Buf);
    fwrite(Buf, sizeof(Buf), 1, fp);

    sleep(5);
    fclose(fp);

    return 0;

}
