obj-m += xdma.o
xdma-objs := xdma-core.o xdma-sgm.o xdma-ioctl.o xdma-bit.o xdma_vs.o

#KERNELDIR ?= /lib/modules/$(shell uname -r)/build
#KERNELDIR ?= ~/ti-processor-sdk-linux-rt-am57xx-evm-05.03.00.07/board-support/linux-rt-4.14.79+gitAUTOINC+a72bf1418c-ga72bf1418c
#KERNELDIR ?= ~/ti-processor-sdk-linux-am57xx-evm-04.01.00.06/board-support/linux-4.9.41+gitAUTOINC+e3a80a1c5c-ge3a80a1c5c/
KERNELDIR ?=/home/ti_linux/ti-processor-sdk-linux-am57xx-evm-04.02.00.09/board-support/linux-4.9.59+gitAUTOINC+a75d8e9305-ga75d8e9305/
#KERNELDIR ?=/data_disk/songzhenhao/Work/tisdk/build/arago-tmp-external-arm-toolchain/work/am57xx_evm-linux-gnueabi/linux-ti-staging/4.19.38+gitAUTOINC+4dae378bbe-r7a.arago5.tisdk0.3/git



NKER_FLAGS=$(LINKER_FLAGS) /MAP

PWD       := $(shell pwd)

ROOT := $(dir $(M))
XILINXINCLUDE := -I$(ROOT)../include -I$(ROOT)/include -g -Wno-date-time

GCCVERSION = $(shell gcc -dumpversion | sed -e 's/\.\([0-9][0-9]\)/\1/g' -e 's/\.\([0-9]\)/0\1/g' -e 's/^[0-9]\{3,4\}$$/&00/')

GCC49 := $(shell expr $(GCCVERSION) \>= 40900)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

install: all
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
	depmod -a
	install -m 644 10-xcldma.rules /etc/udev/rules.d

clean:
	rm -rf *.o *.o.d *~ core .depend .*.cmd *.ko *.ko.unsigned *.mod.c .tmp_versions *.symvers .#* *.save *.bak Modules.* modules.order Module.markers *.bin

CFLAGS_xdma-core.o := -Wall -DDEBUG  $(XILINXINCLUDE)

ifeq ($(GCC49),1)
	CFLAGS_xdma-core.o += -Wno-error=date-time
endif

CFLAGS_xdma-sgm.o := $(XILINXINCLUDE)
CFLAGS_xdma-bit.o := $(XILINXINCLUDE)
CFLAGS_xdma-ioctl.o := $(XILINXINCLUDE)
CFLAGS_xdma_vs.o := $(XILINXINCLUDE)
