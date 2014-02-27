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


#include "manager.h"
#include "container.h"

/**
 * manager
 */
manager::manager() :
	head()
{
	head.name = "dummy";
}

/**
 * ~manager
 */
manager::~manager()
{
}

/**
 * add
 */
container *
manager::add (container *parent, container *child)
{
	if (!parent) {
		//top = child;
	}

	child->ref();
	pool_current.insert(child);

	if (parent) {
		//container *parent_copy = parent->copy();
		parent->ref();
		pool_old.insert(parent);
	}

	return NULL;
}

/**
 * remove
 */
container *
manager::remove (container *item)
{
	std::tuple<long, container *, container *, std::string> t;
	return NULL;
}

