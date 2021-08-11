obj-m += memdev.o
KERNELDIR ?=/home/ti_linux/ti-processor-sdk-linux-am57xx-evm-04.02.00.09/board-support/linux-4.9.59+gitAUTOINC+a75d8e9305-ga75d8e9305/
#KERNELDIR ?= /usr/src/linux-headers-4.15.0-50/kernel/
#NKER_FLAGS=$(LINKER_FLAGS) 

PWD       := $(shell pwd)

##ROOT := $(dir $(M))
#XILINXINCLUDE := -I$(ROOT)../include -I$(ROOT)/include

GCCVERSION = $(shell gcc -dumpversion | sed -e 's/\.\([0-9][0-9]\)/\1/g' -e 's/\.\([0-9]\)/0\1/g' -e 's/^[0-9]\{3,4\}$$/&00/')

GCC49 := $(shell expr $(GCCVERSION) \>= 40900)
ifeq ($(GCC49),1)
   CFLAGS_memdev.o += -Wno-error=date-time
endif

all: writeapp readapp
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

writeapp:
	$(CROSS_COMPILE)gcc app-write.c -o write
readapp:
	$(CROSS_COMPILE)gcc app-read.c -o read

clean:
	rm -rf write read *.o *.o.d *~ core .depend .*.cmd *.ko *.ko.unsigned *.mod.c .tmp_versions *.symvers .#* *.save *.bak Modules.* modules.order Module.markers *.bin
#clean: 
#	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules clean


