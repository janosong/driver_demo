file=`ls *.ko`
pass=root
#make ARCH=arm CROSS_COMPILE=~/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- -j48
make ARCH=arm CROSS_COMPILE=/home/ti_linux/ti-processor-sdk-linux-am57xx-evm-04.02.00.09/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- -j48
#make ARCH=arm CROSS_COMPILE=/home/songzhenhao/ti-processor-sdk-linux-am57xx-evm-04.01.00.06/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf- -j48
if [ $# -lt 1  ]
then
    expect -c "
    spawn scp $file root@172.16.81.95:
    expect \"password:\"
    send \"${pass}\r\"
    expect eof
    "
else
    echo "do not update $file!"
    for var in $*
    do
        echo "$var"
    done
fi
