#include "virtual_input_dev.h"






static ssize_t vinput_key_value_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    virtual_input_info_t *input_infop = dev_get_drvdata(dev);


    
    return  sprintf(buf, "%d\n", input_infop->key_value);
}


static ssize_t vinput_key_value_store(struct device *dev,
                    struct device_attribute *attr,
                    const char *buf, size_t count)
{
    virtual_input_info_t *input_infop = dev_get_drvdata(dev);
    u32 key_value = simple_strtoul(buf, NULL, 10);


    input_infop->key_value = key_value > 0?1:0;
    printk("%s:%d\n", __FUNCTION__, __LINE__);
    input_report_key(input_infop->input_dev, KEY_UP, input_infop->key_value);
    
    printk("%s:%d\n", __FUNCTION__, __LINE__);
    input_sync(input_infop->input_dev);
    printk("%s:%d\n", __FUNCTION__, __LINE__);

    return count;
}

static DEVICE_ATTR(vinput_key, S_IWUSR|S_IRUSR, vinput_key_value_show, vinput_key_value_store);


static struct attribute *virtual_input_attrs[] =
{
    &dev_attr_vinput_key.attr,
    NULL
};
static const struct attribute_group virtual_input_attr_group = 
{
    .attrs = virtual_input_attrs,
};

static int virtual_input_open(struct input_dev *dev)
{
    printk("%s:%d\n", __FUNCTION__, __LINE__);

    return 0;
}

static int virtual_input_platform_probe(struct platform_device *platform_dev)
{
    virtual_input_info_t *input_infop = kzalloc(sizeof(virtual_input_info_t), GFP_KERNEL);
    int ret = 0;

    if(input_infop == NULL)
        return -ENOMEM;

    input_infop->key = 20;
    input_infop->input_dev = input_allocate_device();

    printk("%s:%d\n", __FUNCTION__, __LINE__);
    if(input_infop->input_dev == NULL)
    {
        ret = -ENOMEM;
        goto free_info;
    }
    input_infop->input_dev->evbit[0] = BIT_MASK(EV_KEY);
    
    __set_bit(KEY_UP, input_infop->input_dev->keybit);
    input_infop->input_dev->open = virtual_input_open;
    input_infop->input_dev->name = "virtual_key_input";
    input_infop->input_dev->id.version = 0x0010;
    input_infop->input_dev->id.vendor = 0x0508;
    input_infop->input_dev->id.product = 0x0003;
    printk("%s:%d  %s\n", __FUNCTION__, __LINE__, dev_name(&platform_dev->dev));
    printk("hint_events_per_packet=%d max_vals=%d\n", input_infop->input_dev->hint_events_per_packet,
        input_infop->input_dev->max_vals);

    ret = input_register_device(input_infop->input_dev);
    if(ret != 0)
    {
        goto free_input_device;
    }
    printk("%s:%d\n", __FUNCTION__, __LINE__);

    printk("hint_events_per_packet=%d max_vals=%d\n", input_infop->input_dev->hint_events_per_packet,
        input_infop->input_dev->max_vals);
    sysfs_create_group(&(platform_dev->dev.kobj), &virtual_input_attr_group);

    platform_set_drvdata(platform_dev, input_infop);
    
    printk("%s:%d\n", __FUNCTION__, __LINE__);
    return 0;

free_input_device:
    input_free_device(input_infop->input_dev);
free_info:
    kfree(input_infop);

    return ret;
} 

static int virtual_input_platform_remove(struct platform_device *platform_dev)
{

    virtual_input_info_t *input_infop = platform_get_drvdata(platform_dev);

    sysfs_remove_group(&(platform_dev->dev.kobj), &virtual_input_attr_group);
    platform_set_drvdata(platform_dev, NULL);

    printk("%s:%d\n", __FUNCTION__, __LINE__);

    input_unregister_device(input_infop->input_dev);
    kfree(input_infop);
    printk("%s:%d\n", __FUNCTION__, __LINE__);

   return 0;
}


static struct platform_driver virtual_input_platform_driver = {
    .driver = {
        .name = "virtual_input_dev",
        .owner = THIS_MODULE,
    },
    .probe = virtual_input_platform_probe,
    .remove = virtual_input_platform_remove,
};





static int __init virtual_input_device_init(void)
{
    int ret = 0;
    printk("%s:%d\n", __FUNCTION__, __LINE__);

    ret = platform_driver_register(&virtual_input_platform_driver);

    return ret;
}

static void __exit virtual_input_device_exit(void)
{
    platform_driver_unregister(&virtual_input_platform_driver);
}



module_init(virtual_input_device_init);
module_exit(virtual_input_device_exit);
MODULE_DESCRIPTION("Virtual Input Device");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("jerry_chg");
