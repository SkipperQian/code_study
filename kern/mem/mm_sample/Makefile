export ARCH=arm64
export CROSS_COMPILE=aarch64-linux-gnu-

#KERNEL_VER = $(shell uname -r)
#KERNEL_DIR = /lib/modules/$(KERNEL_VER)/build
KERNEL_DIR = ~/code/linux-4.0.1/

PWD = $(shell pwd)

MODULE = mm_sample
obj-m := $(MODULE).o

all:
	make -C $(KERNEL_DIR) M=$(PWD)  modules  

.PHONY:clean
clean:
	make -C $(KERNEL_DIR) M=$(PWD) clean 
