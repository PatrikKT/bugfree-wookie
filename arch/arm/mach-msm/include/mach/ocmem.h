/* Copyright (c) 2012, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _ARCH_ARM_MACH_MSM_OCMEM_H
#define _ARCH_ARM_MACH_MSM_OCMEM_H

#include <asm/page.h>
#include <linux/module.h>
#include <linux/notifier.h>

#define OCMEM_MIN_ALLOC SZ_64K
#define OCMEM_MIN_ALIGN SZ_64K

#define OCMEM_MAX_CHUNKS 32
#define MIN_CHUNK_SIZE (SZ_1K/8)

struct ocmem_buf {
	unsigned long addr;
	unsigned long len;
};

struct ocmem_buf_attr {
	unsigned long paddr;
	unsigned long len;
};

struct ocmem_chunk {
	bool ro;
	unsigned long ddr_paddr;
	unsigned long size;
};

struct ocmem_map_list {
	unsigned num_chunks;
	struct ocmem_chunk chunks[OCMEM_MAX_CHUNKS];
};

enum ocmem_client {
	
	OCMEM_GRAPHICS = 0x0,
	
	OCMEM_VIDEO,
	OCMEM_CAMERA,
	
	OCMEM_HP_AUDIO,
	OCMEM_VOICE,
	
	OCMEM_LP_AUDIO,
	OCMEM_SENSORS,
	OCMEM_BLAST,
	OCMEM_CLIENT_MAX,
};

enum ocmem_notif_type {
	OCMEM_MAP_DONE = 1,
	OCMEM_MAP_FAIL,
	OCMEM_UNMAP_DONE,
	OCMEM_UNMAP_FAIL,
	OCMEM_ALLOC_GROW,
	OCMEM_ALLOC_SHRINK,
	OCMEM_NOTIF_TYPE_COUNT,
};

void *ocmem_notifier_register(int client_id, struct notifier_block *nb);

int ocmem_notifier_unregister(void *notif_hndl, struct notifier_block *nb);

unsigned long get_max_quota(int client_id);

struct ocmem_buf *ocmem_allocate(int client_id, unsigned long size);

struct ocmem_buf *ocmem_allocate_nowait(int client_id, unsigned long size);

struct ocmem_buf *ocmem_allocate_nb(int client_id, unsigned long size);

struct ocmem_buf *ocmem_allocate_range(int client_id, unsigned long min,
			unsigned long goal, unsigned long step);

int ocmem_free(int client_id, struct ocmem_buf *buf);

int ocmem_shrink(int client_id, struct ocmem_buf *buf,
			unsigned long new_size);

int ocmem_expand(int client_id, struct ocmem_buf *buf,
			unsigned long new_size);

int ocmem_evict(int client_id);

int ocmem_restore(int client_id);
#endif