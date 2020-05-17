#include "virtual_input_platform_dev.h"


static void virtual_input_dev_release(struct device *dev)
{

}
static struct virtual_input_platform_config virtual_input_config =
{
    .ev_type = 1,
};
static struct platform_device virtual_input_platform_device = {
    .name = "virtual_input_dev",
    .id = 0,
    .dev =
    {
        .platform_data = &virtual_input_config,
        .release = virtual_input_dev_release,
    }
};

static int __init virtual_input_platform_dev_init(void)
{
    platform_device_register(&virtual_input_platform_device);

    return 0;
}

static void __exit virtual_input_platform_dev_exit(void)
{
    platform_device_unregister(&virtual_input_platform_device);
}


module_init(virtual_input_platform_dev_init);
module_exit(virtual_input_platform_dev_exit);

MODULE_DESCRIPTION("Virtual Input Platform Devs");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("jerry_chg");
