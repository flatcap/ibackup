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

#include "disk.h"

/**
 * disk (default)
 */
disk::disk()
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	declare ("disk", "#aaffaa");
}

/**
 * disk (copy)
 */
disk::disk (const disk &d) :
	label (d.label),
	serial (d.serial)
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	declare ("disk", "#aaffaa");
}

/**
 * disk (move)
 */
disk::disk (disk &&d) :
	disk()
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	swap (*this, d);
}

/**
 * ~disk
 */
disk::~disk()
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
}


/**
 * operator=
 */
disk & disk::operator= (disk d)
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	swap (*this, d);
	return *this;
}

/**
 * swap
 */
void swap (disk &first, disk &second)
{
	//printf ("%s (%p,%p)\n", __PRETTY_FUNCTION__, &first, &second);
	std::swap (first.children, second.children);
}


/**
 * dump_dot
 */
std::string disk::dump_dot (void)
{
	std::ostringstream output;

	output << container::dump_dot();

	output << dump_row ("label",  label);
	output << dump_row ("serial", serial);

	return output.str();
}

