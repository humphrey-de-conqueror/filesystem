#include <linux/module.h> 
#include <linux/fs.h> 
#include <linux/pagemap.h> 

#define MYFS_MAGIC	0x6d796673

static int myfs_fill_super(struct super_block *sb, void *data, int silent)
{
	return 0; 
}

static struct dentry *myfs_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data)
{
	return mount_nodev(fs_type, flags, data, myfs_fill_super);
}

static struct file_system_type myfs_type = {
	.name		= "myfs",
	.owner		= THIS_MODULE,
	.mount		= myfs_mount, 
	.kill_sb	= kill_litter_super, /* kernel build-in */
};

static int __init myfs_init(void)
{	
	int ret; 
	
	ret	= register_filesystem(&myfs_type);
	if (ret != 0) {
		printk(KERN_ERR "myfs: failed to register filesystem\n");
		return ret; 
	}

	printk(KERN_INFO "myfs: registered\n");

	return 0;
}

static void __exit myfs_exit(void)
{
	unregister_filesystem(&myfs_type);
	printk(KERN_INFO "myfs: unregistered\n");
}

module_init(myfs_init);
module_exit(myfs_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("humphrey-de-conqueror");
MODULE_DESCRIPTION("simple in-memory filesystem");