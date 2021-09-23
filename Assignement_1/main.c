#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include<linux/random.h>

#include"chardev.h"


static dev_t first;
static struct cdev c_dev;
static struct class *cls;
uint16_t baro_value;


static int my_open(struct inode *i, struct file *f)
{
printk(KERN_INFO "Mychar: open()\n");
return 0;
}

static int my_close(struct inode *i, struct file *f)
{
printk(KERN_INFO "Mychar: close()\n");
return 0;
}

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
uint16_t read_value;
  /*
      using lib function get_random_bytes() to get 2 byte random data 
  */
   get_random_bytes(&read_value,2);
   printk(KERN_ALERT "message inside kernel:%d\n",read_value);
   copy_to_user(buf,&read_value,2);
  
return 0;
}



long first_ioctl(struct file *file,unsigned int request ,unsigned long message)
{
  char rec_mess;
switch(request)
{
case READ_GYRO_X:
     my_read(file,(char *)message,2,0);

break;

case READ_GYRO_Y:
    my_read(file,(char *)message,2,0);
   
   break;
   case READ_GYRO_Z:
    my_read(file,(char *)message,2,0);
   
   break;
   
   case READ_ACCELERO_X:
    my_read(file,(char *)message,2,0);
   
   break;
   
   case READ_ACCELERO_Y:
    my_read(file, (char *)message,2,0);
   
   break;
   
   case READ_ACCELERO_Z:
    my_read(file,(char *)message,2,0);
   
   break;
   
   case READ_MAGNETO_X:
    my_read(file,(char *)message,2,0);
   
   break;
   
   case READ_MAGNETO_Y:
    my_read(file,(char *)message,2,0);
   
   break;
   
   case READ_MAGNETO_Z:
    my_read(file,(char *)message,2,0);
   
   break;

   case READ_BARO:
    /*
      using lib function get_random_bytes() to get 2 byte random data 
  */
   get_random_bytes(&baro_value,2);
   /*
      masking value to emulate 10-bit sensor value
   */
   baro_value= baro_value & (0x000003FF); 
   /*
      using copy_to_user to copy value from kernel space to user space
   */
   copy_to_user((char *)message,&baro_value,sizeof(baro_value));
   break;
   
   
   case WRITE_FILE:
    /*
       using copy_from_user function to copy the message from user space to kernel space
    */
      copy_from_user(&rec_mess,message,1);
      printk(KERN_ALERT "%c",message);     
    
   break;
   
   }
   
   return 0;
 
}

static struct file_operations fops =
{
  .owner = THIS_MODULE,
  .open = my_open,
  .release = my_close,
  .read = my_read,
  .unlocked_ioctl=first_ioctl
};

static int __init mychar_init(void)
{
printk(KERN_INFO "Char driver registered");
if (alloc_chrdev_region(&first,0,1,"BITS_PILANI") < 0)
{
return -1;
}

printk (KERN_INFO "<major, minor> : <%d, %d>\n", MAJOR(first) , MINOR(first) );

if ((cls = class_create(THIS_MODULE, "char_drv")) == NULL)
{
unregister_chrdev_region(first,1);
return -1;
}

if (device_create(cls, NULL, first, NULL, "imu_char") == NULL)
{
class_destroy(cls);
unregister_chrdev_region(first,1);
return -1;
}

cdev_init(&c_dev, &fops);
if (cdev_add(&c_dev, first, 1) == -1)
{
device_destroy(cls,first);
class_destroy(cls);
unregister_chrdev_region(first,1);
return -1;
}  
return 0;
}

static void __exit mychar_exit(void)
{
cdev_del(&c_dev);
device_destroy(cls,first);
class_destroy(cls);
unregister_chrdev_region(first,1);
printk(KERN_INFO "char driver unregistered\n\n");

}

module_init(mychar_init);
module_exit(mychar_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SAHIL BHADWAL");
MODULE_DESCRIPTION("This is a module for reading data through sensor");
