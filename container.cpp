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


#include <typeinfo>

#include "container.h"

/**
 * container
 */
container::container() :
	size(0)
{
}

/**
 * ~container
 */
container::~container()
{
	for (auto c : children) {
		delete c;
	}
}


/**
 * add
 */
int container::add (container *c)
{
	children.push_back(c);
	return children.size();
}

/**
 * remove
 */
int container::remove (int index)
{
	children.erase(children.begin() + index);
	return children.size();
}


/**
 * operator<<
 */
std::ostream& operator<< (std::ostream &stream, const container &c)
{
	stream << typeid(c).name() << " = " << c.size;

	for (auto i : c.children) {
		stream << "\n\t" << i;
	}

	return stream;
}

/**
 * operator<<
 */
std::ostream& operator<< (std::ostream &stream, const container *c)
{
	if (c)
		return operator<< (stream, *c);
	else
		return stream;
}


