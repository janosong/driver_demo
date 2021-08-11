#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <poll.h>


#define DEV "/dev/mem_dev"
int main()
{
    int fd;
    fd_set rds;
    int ret;
    char Buf[128] = {0};

    /*初始化Buf*/
   // strcpy(Buf,"memdev is char dev!\n");
   // printf("BUF: %s\n",Buf);

    /*打开设备文件*/
    fd = open(DEV,O_RDWR|O_NONBLOCK);
   // fd = open(DEV,O_RDWR);
    if (0 == fd)
    {
        printf("read open failed %s!\n", DEV);
        return 1;
    }
    printf("read open %s \r\n", DEV);


    /*清除Buf*/
//    strcpy(Buf,"Buf is NULL!");
#if 0 //select mode
    struct timeval timeout={3.0};
    FD_ZERO(&rds);
    FD_SET(fd, &rds);
    ret = select(fd + 1, &rds, NULL, NULL, &timeout);
    if (ret <= 0)
    {
        printf("select error!\n");
        exit(1);

    }
    printf("select:%d\n", ret);

    if (FD_ISSET(fd, &rds))
    {
        ret = read(fd, Buf, sizeof(Buf));
        if (ret <0 )
        {
            printf("read failed:%d %s\n", errno, strerror(errno));
        }
    }
    else
    {
        printf("FD no set\n");
        close(fd);
        return 0;
    }
#endif

#if 1 //poll mode
    struct pollfd pfds;
    pfds.fd = fd;
    pfds.events = POLLIN;
    ret = poll(&pfds, 1, 5000);
    if (ret <= 0)
    {
        printf("poll error:%d\n", ret);
    }
    printf("poll event:0x%.8x\n", pfds.revents);
    ret = read(fd, Buf, sizeof(Buf));
    if (ret <0 )
    {
        printf("read failed:%d %s\n", errno, strerror(errno));
    }
#endif
#if 0 // block read
    ret = read(fd, Buf, sizeof(Buf));
    printf("read failed:%d %s\n", errno, strerror(errno));
#endif


    /*检测结果*/
    printf("Read BUF2: %s\n",Buf);

    close(fd);

    return 0;

}
