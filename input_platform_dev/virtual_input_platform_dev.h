#ifndef VIRTUAL_INPUT_DEV_H_
#define VIRTUAL_INPUT_DEV_H_ 
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/cdev.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/mdio.h>
#include <linux/phy.h>
#include <linux/platform_device.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/kdev_t.h>
#include <linux/syscalls.h>
#include <linux/mount.h>
#include <linux/device.h>

struct virtual_input_platform_config
{
    int ev_type;
    int ev_bit;
};

#endif
