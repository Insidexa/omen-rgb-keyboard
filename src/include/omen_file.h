// SPDX-License-Identifier: GPL-3
/*
 * HP OMEN RGB Keyboard Driver - file access helper
 *
 * State files are read and written from workqueue context. Since Linux 7.x
 * kernel threads no longer resolve paths against the userspace root, so a
 * plain filp_open() from a kworker fails with -ENOENT for every path under
 * /var. scoped_with_init_fs() switches path resolution to userspace's root
 * for the duration of the open; on older kernels the macro does not exist
 * and kernel threads already see that root.
 */

#ifndef OMEN_FILE_H
#define OMEN_FILE_H

#include <linux/fs.h>
#include <linux/fs_struct.h>

static inline struct file *omen_filp_open(const char *path, int flags, umode_t mode)
{
#ifdef scoped_with_init_fs
	scoped_with_init_fs()
		return filp_open(path, flags, mode);
#endif
	return filp_open(path, flags, mode);
}

#endif /* OMEN_FILE_H */
