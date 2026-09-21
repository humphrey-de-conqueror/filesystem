struct super_operation		-> operation on whole filesystem (mkdir)

struct inode_operation		-> operation on metadata of file/directory (ls, chmod)

struct file_operation		-> operation on a opened file (cat)

target: 
+ a filesystem that can we mount 
+ has a single root directory 
+ has one hardcoded file 
+ that can be cat from userspace 