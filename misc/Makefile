# make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
rdir := $(dir $(mkfile_path))
$(eval wdir := $(abspath $(rdir)/../../))

ifneq  ($(KERNELRELEASE),)
obj-m:=mdev.o mdrv.o
$(info "2nd")
else
#KDIR := /lib/modules/$(shell uname -r)/build
KDIR :=$(wdir)/linux-4.14.99
DST :=$(wdir)/busybox-1.33.1/_install/app
PWD:=$(shell pwd)
all:
	$(info "1st")
	$(shell if [ ! -e $(DST) ];then mkdir -p $(DST); fi)
	arm-linux-gnueabihf-gcc -static -o test test.c
	make -C $(KDIR) M=$(PWD) modules
	cp *.ko test $(DST)
clean:
	rm -f *.ko *.o *.symvers *.mod.c *.mod.o *.order test $(DST)/*
endif