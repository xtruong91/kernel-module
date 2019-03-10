/*
 * File: stop.c
 * File Created: Sunday, 10th March 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */

#include "stop.h"

void cleanup_module()
{
	printk(KERN_INFO "Short is the life of a kernel module\n");
}