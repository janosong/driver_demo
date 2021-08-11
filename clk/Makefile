obj-m := clk-demo.o

KERNELDIR :=/home/ti_linux/ti-processor-sdk-linux-am57xx-evm-04.02.00.09/board-support/linux-4.9.59+gitAUTOINC+a75d8e9305-ga75d8e9305/
#KERNELDIR :=/lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)

modules:
		#$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
		make -C $(KERNELDIR) M=$(PWD) modules
modules_install:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
		rm -rf *.o *~ core .depend .*.cmd *.ko.* *.mod.c .tmp_versions *.order *.symvers *.ko
