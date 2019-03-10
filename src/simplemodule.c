/*
 * File: simplemodule.c
 * File Created: Sunday, 10th March 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: common structure of Kernel module file
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */

#include <linux/module.h> // need by all modules
#include <linux/kernel.h>  // need for kern_info
#include <linux/init.h>
#include <linux/stat.h>

static short int myshort = 1;
static int myint = 420;
static long int mylong = 9999;
static char *mystring = "blah";
static int myintArray[2] = { -1, -1 };
static int arr_argc = 0;

static int count __initdata = 0; 
/*
 * module_param_array(name, type, num, perm);
 * The first param is the parameter's (in this case the array's) name
 * The second param is the data type of the elements of the array
 * The third argument is a pointer to the variable that will store the number 
 * of elements of the array initialized by the user at module loading time
 * The fourth argument is the permission bits
 */
module_param_array(myintArray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myintArray, "An array of integers");

static int __init init_simplemodule(void)
{
  printk (KERN_EMERG "Starting with  kernel linux : %d", count);
  printk(KERN_INFO "Hello, world 5\n=============\n");
	printk(KERN_INFO "myshort is a short integer: %hd\n", myshort);
	printk(KERN_INFO "myint is an integer: %d\n", myint);
	printk(KERN_INFO "mylong is a long integer: %ld\n", mylong);
	printk(KERN_INFO "mystring is a string: %s\n", mystring);
	for (i = 0; i < (sizeof myintArray / sizeof (int)); i++)
	{
		printk(KERN_INFO "myintArray[%d] = %d\n", i, myintArray[i]);
	}
	printk(KERN_INFO "got %d arguments for myintArray.\n", arr_argc);
  return 0;
}

static void __exit cleanup_simplemodule(void)
{
  printk( KERN_EMERG "Cleaing ! \n");
  return;
}

module_init (init_simplemodule);
module_exit (cleanup_hello);

MODULE_LICENSE ("GPL");

/*
 * Or with defines, like this:
 */
MODULE_AUTHOR("truongtx");	/* Who wrote this module? */
MODULE_DESCRIPTION(DRIVER_DESC);	/* What does this module do */

/*  
 *  This module uses /dev/testdevice.  The MODULE_SUPPORTED_DEVICE macro might
 *  be used in the future to help automatic configuration of modules, but is 
 *  currently unused other than for documentation purposes.
 */
MODULE_SUPPORTED_DEVICE("testdevice");
