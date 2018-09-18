#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("IC411");
MODULE_DESCRIPTION("Module to add /dev/upper");

//function declarations
static int upper_init(void);
static void upper_cleanup(void);
static ssize_t upper_read(struct file * file, char * buf, size_t len, loff_t *ppos);
static ssize_t upper_write(struct file *filep, const char *buf, size_t len, loff_t *offset);
static int upper_open(struct inode *inodep, struct file *filep);

//setting up device structure
static struct file_operations upper_fops = {
  .open = upper_open,
  .read = upper_read,
  .write = upper_write,
};
static struct miscdevice upper_dev = { MISC_DYNAMIC_MINOR,"upper",&upper_fops};

//globals
static char upper_buffer[4096] = {0};
static short upper_buffer_size = 0;

//specify  our init and cleanup functions
module_init(upper_init);
module_exit(upper_cleanup);


//Initialize the module
static int __init upper_init(void)
{
  int ret;

  printk(KERN_INFO "upper: Initializing /dev/upper\n");
  if( (ret = misc_register(&upper_dev) ))
    printk(KERN_ERR "upper: Unable to register \"/dev/upper\" device\n");

  return ret;

}

//De-initialize the module
static void __exit upper_cleanup(void)
{
  printk(KERN_INFO "upper: De-initializing /dev/upper\n");
  misc_deregister(&upper_dev);
}

//Open the /dev/upper device
static int upper_open(struct inode *inodep, struct file *filep){
  printk(KERN_INFO "upper: /dev/upper opened\n");
  return 0;
}

//called whenever /dev/upper is read from
static ssize_t upper_read(struct file * filep, char * buf, size_t len, loff_t *ppos){

  //filep : structure of the file
  //buf   : userspace address to write what was read to
  //len   : requested number of bytes to read
  //ppos  : offset into the file

  printk(KERN_INFO "upper: read: upper_buffer=\"%s\" upper_buffer_size=%d\n",upper_buffer, upper_buffer_size);
  
  // TODO: If the number of bytes that is being read (in 'len') is less than 
  //  the number of bytes currently in the buffer, return an error.

  if(len < upper_buffer_size)
    return EINVAL;

  
  
  // If the file object ppos does not indicate the beginning, return zero
  if( *ppos != 0)
    return 0; 
	
  // TODO: If the upper_buffer is already empty, return an error

  if(upper_buffer_size == 0)
    return EINVAL;
  
  
  // TODO: Attempt to transfer all bytes in upper_buffer from kernel space 
  //  to the user-space buffer whose pointer was passed in. 
  //  If unsuccessful, return an error. 
  
  
  if((copy_to_user(buf, upper_buffer, upper_buffer_size)) > 0)
      return EINVAL;

     
  
  *ppos = upper_buffer_size; //indicate how far into file we are
  upper_buffer_size = 0; //indicate the buffer is now empty
  return *ppos;
     
}

//called whenever /dev/upper is written to
static ssize_t upper_write(struct file *filep, const char *buf, size_t len, loff_t *ppos){

  //filep : structure of the file
  //buf   : userspace data to be written
  //len   : request number of bytes to write
  //ppos  : offset into the file

  int i;	// Loop counter.

  // TODO: If the buffer 'buf' is not empty, return an error.

  if(upper_buffer_size > 0){
    printk(KERN_ERR ": Invalid argument");
    return EINVAL;
  }
  
  
  // If the file object ppos does not indicate the beginning, return zero
  if ( *ppos != 0 ) 
    return 0; 

  // TODO: If the length (len) of bytes to write would be too big
  //  for the 4096-byte max buffer size, return an error.

  if(len > 4096)
    return EINVAL;
  

  // TODO: Copy bytes from userspace by way of input arguments.
  //  While copying, convert any lowercase letters to uppercase.

  for(i =0; i < len; ++i){
    if(buf[i] > 0x60)
      upper_buffer[i] = buf[i] - 0x20;
    else
      upper_buffer[i] = buf[i];
  }


  

  upper_buffer_size = len;
  printk(KERN_INFO "upper: write: wrote %d bytes to upper_buffer\n", upper_buffer_size);
  *ppos = len;
  return len;

}
