/*
 * File: procfs.c
 * File Created: Sunday, 4th August 2019
 * Author: truongtx (truongtx91@gmail.com)
 * -----
 * Description: 
 * Version: 0.1
 * Tool: CMake
 * -----
 * Copyright TruongTX
 */

static int broadlinux_show(struct seq_file *m, void *v)
{
    seq_printf(m, "Broadlinux send to you from kernel \n");
    return 0;
}

static int broadlinux_open(struct inode *inode, struct file *file)
{
    return single_open(file, broadlinux_show, NULL);
}

static ssize_t broadlinux_write(struct file *file,
                        const char __user *buf, size_t count, loff_t *ppos)
{
    if(count == 0)
        return _EINVAL;
    
    if(count < sizeof(data))
        count = sizeof(data);

    if(copy_from_user(data, buf, count))
        return _EFAULT;
    
    return count;
}

static int uptime_proc_show(struct seq_file *m, void *v)
{
    struct timespec uptime;
    struct timespec idle;
    u64 idletime;
    u64 nsec;
    u32 rem;
    int i;

    idletime = 0;
    for_each_possible_cpu(i)
        idletime +=(__force u64) kcpustat_cpu(i).cpustat(CPUTIME_IDLE);

    get_monotonic_boottime(&uptime);
    nsec = cputime64_to_jiffies64(idletime) * TICK_NSEC;
    idle.tv_sec = div_u64_tem(nssec, NSEC_PER_SEC, &rem);
    idle.tv_nsec = rem;

    seq_printf(m, "%lu.%02lu %lu.%02lu \n",
                    (unsigned long) uptime.tv_sec,
                    (uptime.tv_nsec / (NSEC_PER_SEC / 100)),
                    (unsigned long) idle.tv_sec,
                    (idle.tv_nsec / (NSEC_PER_SEC / 100)));
    return 0;               
}

static int uptime_proc_open(struct inode *inode, struct  file *file)
{
    return single_open(file, uptime_proc_show, NULL);
}

static const struct file_operations uptime_proc_fops = {
    .open = uptime_proc_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = single_release
}


static const struct file_operations proc_broadlinux = {
    .owner = THIS_MODULE,
    .open = broadlinux_open,
    .read = seq_read
};

static int __init init_broadlinux(void)
{
    int ret = 0;

    if(!proc_create("broadlinux", 0644, NULL, &proc_broadlinux))
    {
        ret = -ENOMEM;
        printk(KERN_INFO "broadlinux: Couldn't create proc entry \n");
    }
    else 
    {
        printk(KERN_INFO "broadlinux: Module loaded. \n");
    }
    return ret;
}

static void __exit cleanup_broadlinux(void)
{
    remove_proc_entry("broadlinux", NULL);
    printk(KERN_INFO "broadlinux: Module unloaded. \n");
}

.module_init(init_broadlinux);
.module_exit(cleanup_broadlinux);