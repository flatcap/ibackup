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


#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <unordered_set>

#include "container.h"

class manager
{
public:
	manager();
	virtual ~manager();

	container * add    (container *parent, container *child);
	container * remove (container *item);

protected:
	std::unordered_set<container*>	pool_current;
	std::unordered_set<container*>	pool_old;

	// timeline
	//	changes
	//	iterator
	//
	// disks -- discovery
	// partition -- read partition table
	// fs -- probe

	void freeze();
	void thaw();

	container head;
};

#endif // _MANAGER_H_

