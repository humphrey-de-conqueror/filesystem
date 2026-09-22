#include <linux/module.h> 
#include <linux/fs.h> 
#include <linux/pagemap.h> 
#include <linux/fs_context.h>

#define MYFS_MAGIC	0x6d796673

static const struct super_operations myfs_super_ops = {
	.statfs		= simple_statfs, /*kernel build in*/
};

static int myfs_fill_super(struct super_block *sb, struct fs_context *fc)
{
	struct inode *root_inode; 

	sb->s_magic	= MYFS_MAGIC; 
	sb->s_op	= &myfs_super_ops; 
	sb->s_maxbytes	= MAX_LFS_FILESIZE; 

	root_inode	= new_inode(sb);
	if (!root_inode)
		return -ENOMEM; 

	root_inode->i_ino	= 1; 
	root_inode->i_mode	= S_IFDIR | 0755;
	inode_init_owner(&nop_mnt_idmap, root_inode, NULL, S_IFDIR | 0755);

	sb->s_root	= d_make_root(root_inode);
	if (!sb->s_root)
		return -ENOMEM; 

	return 0; 
}

static int myfs_get_tree(struct fs_context *fc)
{
	return get_tree_nodev(fc, myfs_fill_super);
}

static const struct fs_context_operations myfs_fc_ops = {
	.get_tree = myfs_get_tree,
};

static int myfs_init_fs_context(struct fs_context *fc)
{
	fc->ops	= &myfs_fc_ops;
	return 0;
}

static struct file_system_type myfs_type = {
	.name			= "myfs",
	.owner			= THIS_MODULE,
	.init_fs_context	= myfs_init_fs_context,
	.kill_sb		= kill_anon_super, /* kernel build-in */
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