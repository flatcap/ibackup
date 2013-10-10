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


#ifndef _DISK_H_
#define _DISK_H_

#include <string>

#include "container.h"

class disk : public container
{
public:
	disk();
	disk (const disk &d);
	disk (disk &&d);
	virtual ~disk();

	friend void swap (disk &first, disk &second);

	disk & operator= (disk d);

protected:
	std::string label;
	std::string serial;
};

#endif // _DISK_H_

