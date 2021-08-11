#!/bin/bash
pass=root
#make ARCH=arm CROSS_COMPILE=~/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- -j48
make ARCH=arm CROSS_COMPILE=/home/ti_linux/ti-processor-sdk-linux-am57xx-evm-04.02.00.09/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- -j48
#make ARCH=arm CROSS_COMPILE=/home/songzhenhao/ti-processor-sdk-linux-am57xx-evm-04.01.00.06/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- -j48
expect -c "
spawn scp memdev.ko read write  root@172.16.15.30:
expect \"password:\"
send \"${pass}\r\"
expect eof
"


