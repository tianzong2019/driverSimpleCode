# make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
 
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
rdir := $(dir $(mkfile_path))
 
ifneq  ($(KERNELRELEASE),)
 
obj-m:=device.o driver.o
$(info "2nd")
 
else
 
#KDIR := /lib/modules/$(shell uname -r)/build
KDIR :=$(rdir)/../../linux-4.14.99
DST :=$(rdir)/../../busybox-1.33.1/_install/app
PWD:=$(shell pwd)
 
all:
	$(shell if [ ! -e $(DST) ];then mkdir -p $(DST); fi)
	$(info "1st")
	make -C $(KDIR) M=$(PWD) modules
	cp -rf *.ko $(DST)
clean:
	rm -f *.ko *.o *.symvers *.mod.c *.mod.o *.order mread mwrite $(DST)/*
endif
