/* Copyright (c) 2013 Richard Russon (FlatCap)
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#include <cstdio>

#include "partition.h"

/**
 * partition (default)
 */
partition::partition()
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	declare ("partition", "#ffffdd");
}

/**
 * partition (copy)
 */
partition::partition (const partition &p) :
	type (p.type)
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	declare ("partition", "#ffffdd");
}

/**
 * partition (move)
 */
partition::partition (partition &&p) :
	partition()
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	swap (*this, p);
}

/**
 * ~partition
 */
partition::~partition()
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
}


/**
 * operator=
 */
partition & partition::operator= (partition p)
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	swap (*this, p);
	return *this;
}

/**
 * swap
 */
void swap (partition &first, partition &second)
{
	//printf ("%s (%p,%p)\n", __PRETTY_FUNCTION__, &first, &second);
	std::swap (first.children, second.children);
}


/**
 * dump_dot
 */
std::string partition::dump_dot (void)
{
	std::ostringstream output;

	output << container::dump_dot();

	output << dump_row ("type", type);

	return output.str();
}

