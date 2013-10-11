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

#include "fs.h"

/**
 * fs (default)
 */
fs::fs()
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	declare ("fs", "#bbffff");
}

/**
 * fs (copy)
 */
fs::fs (const fs &f) :
	fstype (f.fstype)
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	declare ("fs", "#bbffff");
}

/**
 * fs (move)
 */
fs::fs (fs &&f) :
	fs()
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	swap (*this, f);
}

/**
 * ~fs
 */
fs::~fs()
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
}


/**
 * operator=
 */
fs & fs::operator= (fs f)
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	swap (*this, f);
	return *this;
}

/**
 * swap
 */
void swap (fs &first, fs &second)
{
	//printf ("%s (%p,%p)\n", __PRETTY_FUNCTION__, &first, &second);
	std::swap (first.children, second.children);
}


/**
 * dump_dot
 */
std::string fs::dump_dot (void)
{
	std::ostringstream output;

	output << container::dump_dot();

	output << dump_row ("filesystem", fstype);

	return output.str();
}

