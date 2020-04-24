#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/netlink.h>
#include <net/sock.h>


static struct sock *nlsk = NULL;





static int __init genl_drv_init(void)
{


	pr_info("[%s]\n", __func__);


	pr_info("[%s] OK\n", __func__);

	return 0;
}

static void __exit genl_drv_exit(void)
{
	pr_info("[%s]\n", __func__);

}

module_init(genl_drv_init);
module_exit(genl_drv_exit);

MODULE_LICENSE("Dual MPL/GPL");
MODULE_AUTHOR("yanli.qian");
MODULE_DESCRIPTION("generic netlink test driver module");
