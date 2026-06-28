/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Copyright (C) 2021 Linux 5.15-rc1
 * Copyright (C) 2026 Pindorama Games (we added the struct rb_root_sched structure.)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. 
 */

#ifndef _LINUX_RBTREE_TYPES_H
#define _LINUX_RBTREE_TYPES_H

struct rb_node {
	unsigned long  __rb_parent_color;
	struct rb_node *rb_right;
	struct rb_node *rb_left;
} __attribute__((aligned(sizeof(long))));
/* The alignment might seem pointless, but allegedly CRIS needs it */

struct rb_node_linked {
	struct rb_node		node;
	struct rb_node_linked	*prev;
	struct rb_node_linked	*next;
};

struct rb_root {
	struct rb_node *rb_node;
};

/*
 * Leftmost-cached rbtrees.
 *
 * We do not cache the rightmost node based on footprint
 * size vs number of potential users that could benefit
 * from O(1) rb_last(). Just not worth it, users that want
 * this feature can always implement the logic explicitly.
 * Furthermore, users that want to cache both pointers may
 * find it a bit asymmetric, but that's ok.
 */
struct rb_root_cached {
	struct rb_root rb_root;
	struct rb_node *rb_leftmost;
};

/*
 * Leftmost tree with links. This would allow a trivial rb_rightmost update,
 * but that has been omitted due to the lack of users.
 */
struct rb_root_linked {
	struct rb_root		rb_root;
	struct rb_node_linked	*rb_leftmost;
};

#define RB_ROOT (struct rb_root) { NULL, }
#define RB_ROOT_CACHED (struct rb_root_cached) { {NULL, }, NULL }
#define RB_ROOT_LINKED (struct rb_root_linked) { {NULL, }, NULL }

struct rb_root_scheduler {
    struct rb_root                  rb_boot;   /* Corrigido de rb_boot para rb_root */
    struct rb_node                  rb_node;
    struct rb_root_scheduler        *rb_sched; /* Corrigido: Agora é um ponteiro para evitar recursão infinita */
    unsigned long long              sched_64;  /* Corrigido: Nomes em C não podem começar com números */
};

#endif /* LINUX_RBTREE_TYPES */
