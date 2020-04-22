#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/netlink.h>
#include <net/sock.h>

#define NETLINK_TEST 30

static struct sock *nlsk = NULL;

static void nl_recv_callback(struct sk_buff *skb)
{
}

static int __init nl_drv_init(void)
{
	struct netlink_kernel_cfg cfg = {
		.input = nl_recv_callback,
	};


	pr_info("[%s]\n", __func__);

	nlsk = netlink_kernel_create(&init_net, NETLINK_TEST, &cfg);
	if (nlsk == NULL) {
		pr_err("[%s] can't create netlink socket\n", __func__);
		return -ENOMEM;
	}

	pr_info("[%s] OK\n", __func__);

	return 0;
}

static void __exit nl_drv_exit(void)
{
	pr_info("[%s]\n", __func__);

	netlink_kernel_release(nlsk);
}

module_init(nl_drv_init);
module_exit(nl_drv_exit);

MODULE_LICENSE("Dual MPL/GPL");
MODULE_AUTHOR("yanli.qian");
MODULE_DESCRIPTION("netlink test driver module");
