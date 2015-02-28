#!/bin/bash
# shell script specifications
echo "**************************************************************************"
echo "            Dolby Digital Plus Decoder build environment shell            "
echo "                         AMLOGIC INC. (shanghai)                          "
echo "                               2015.02.08                                 "
echo "**************************************************************************"

# step 1: Install DS-5 for armcc neon compile
echo "====================================step 1================================"
echo "please ensure that installed DS-5 software into your home dir"
echo "DS-5 license for AMLOGIC: 27000@10.18.11.26"
echo "load DS-5 configuration environment"
if ! test -d ~/DS-5
then 
    echo -e "DS-5 dir does not exist"
    echo -p "if you"
else
    echo -e "DS-5 dir exist === check OK"
fi


echo $PATH
source ~/DS-5/sw/ARM_DS-5/env.sh ~/DS-5
echo $PATH
#armcc

# step 2: Install 
echo "====================================step 2================================="

ARMLINUCPATH=$(which arm-linux-gcc)
if ! $?
then 
    echo "arm-linux-gcc ===  check  OK"
else
    echo "arm-linux-gcc ===  check failed"
fi

echo $ARMLINUCPATH


# step 3: configure DS-5 and arm-linux-gcc cross-compilation
echo "====================================step 3================================="
#armcc --arm_linux_configure --arm_linux_config_file=/home/xiaoxiong161/Myworks/MS12/arm_linux_config.xml \
#       --configure_sysroot=/usr/local/arm/4.3.2/arm-none-linux-gnueabi/libc \
#       --configure_cpp_headers=/usr/local/arm/4.3.2/arm-none-linux-gnueabi/include/c++/4.3.2 \
#       --configure_extra_libraries=/usr/local/arm/4.3.2/lib/gcc/arm-none-linux-gnueabi/4.3.2,/usr/local/arm/4.3.2/arm-none-linux-gnueabi/lib
#
# step 4:
echo "====================================step 4================================="
export ARM_LINUX_CONFIG_FILE=$(pwd)/arm_linux_config.xml
echo $ARM_LINUX_CONFIG_FILE

if ! test $ARM_LINUX_CONFIG_FILE
then
    echo "sccusse: arm linux configuration file is created OK"
else
    echo "error: arm linux configuration file does not exist, please check step 4"
fi

# step 5: make"
echo "==========================step 5============================="
#make -C

exit
