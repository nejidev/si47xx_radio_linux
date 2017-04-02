KERN_DIR = /home/linux-4.1.36

all:
	arm-linux-gcc -o radio_fm radio_fm.c
	arm-linux-gcc -o radio_amsw radio_amsw.c
	make -C $(KERN_DIR) M=`pwd` modules 

clean:
	rm radio_fm
	rm radio_amsw
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order
	

obj-m	+= si47xx_dev.o
obj-m	+= si47xx.o
