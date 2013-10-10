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
#include <memory>
#include <sstream>

#include "backup.h"

/**
 * backup (default)
 */
backup::backup()
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
}

/**
 * backup (copy)
 */
backup::backup (const backup &b)
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
}

/**
 * backup (move)
 */
backup::backup (backup &&b) :
	backup()
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	swap (*this, b);
}

/**
 * ~backup
 */
backup::~backup()
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
}


/**
 * operator=
 */
backup & backup::operator= (backup b)
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	swap (*this, b);
	return *this;
}

/**
 * swap
 */
void swap (backup &first, backup &second)
{
	//printf ("%s (%p,%p)\n", __PRETTY_FUNCTION__, &first, &second);
}


