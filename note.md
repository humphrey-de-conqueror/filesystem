struct super_operation		-> operation on whole filesystem (mkdir)
	register_filesystem(&my_fs_type)
	unregister_filesystem(&my_fs_type)
		struct file_system_type my_fs_type = {
			.name = "myfs", 
			.mount = myfs_mount, //function pointer when `mount` execute
			.kill_sb = kill_litter_super, // when umount called
		};
				mount: myfs_mount {
					mount_nodev -> call myfs_fill_super
					1, set superblock properties 
					2. create the root inode 
					3. create a root dentry pointing to that inode
				}
					myfs_fill_super {
						1. sb->s_magic     -- a unique number identifying our filesystem
						2. sb->s_op        -- pointer to our super_operations
						3. sb->s_maxbytes  -- max file size we support
						4. root inode      -- create it, set its inode_operations
						5. root dentry     -- wrap the root inode, hand it back to VFS
					}

struct inode_operation		-> operation on metadata of file/directory (ls, chmod)

struct file_operation		-> operation on a opened file (cat)

target: 
+ a filesystem that can we mount 
+ has a single root directory 
+ has one hardcoded file 
+ that can be cat from userspace 