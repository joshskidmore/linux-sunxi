/*
 * mux/consumer.h - definitions for the multiplexer consumer interface
 *
 * Copyright (C) 2017 Axentia Technologies AB
 *
 * Author: Peter Rosin <peda@axentia.se>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _LINUX_MUX_CONSUMER_H
#define _LINUX_MUX_CONSUMER_H

#include <linux/compiler.h>

struct device;
struct mux_control;

/**
 * struct mux_lookup -	Mux consumer to mux-controller lookup table entry
 * @list:		List head, internal use only.
 * @provider:		dev_name() of the mux-chip's parent-dev.
 * @index:		mux-controller's index in the mux-chip's mux array
 * @dev_id:		dev_name() of the consumer to map to this controller
 * @mux_name		name the consumer passes to mux_control_get
 */
struct mux_lookup {
	struct list_head list;
	const char *provider;
	unsigned int index;
	const char *dev_id;
	const char *mux_name;
};

void mux_add_table(struct mux_lookup *table, size_t num);
void mux_remove_table(struct mux_lookup *table, size_t num);

unsigned int mux_control_states(struct mux_control *mux);
int __must_check mux_control_select(struct mux_control *mux,
				    unsigned int state);
int __must_check mux_control_try_select(struct mux_control *mux,
					unsigned int state);
int mux_control_deselect(struct mux_control *mux);

struct mux_control *mux_control_get(struct device *dev, const char *mux_name);
struct mux_control *mux_control_get_optional(struct device *dev,
					     const char *mux_name);
void mux_control_put(struct mux_control *mux);

struct mux_control *devm_mux_control_get(struct device *dev,
					 const char *mux_name);
struct mux_control *devm_mux_control_get_optional(struct device *dev,
						  const char *mux_name);

#endif /* _LINUX_MUX_CONSUMER_H */
