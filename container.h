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


#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <vector>
#include <sstream>
#include <utility>
#include <sstream>

#include "backup.h"

class container : public backup
{
public:
	container();
	container (const container &c);
	container (container &&c);
	virtual ~container();

	void * operator new    (size_t s);
	void   operator delete (void *ptr);

	void ref (void);
	void unref (void);

	int add (container *c);
	int remove (int index);

	virtual bool is_a (const std::string &type);
	std::string	 name;
	std::vector<std::string> type;

	int size;

	friend std::ostream & operator<< (std::ostream &stream, const container &c);
	friend std::ostream & operator<< (std::ostream &stream, const container *c);
	friend void swap (container &first, container &second);

	container & operator= (container c);

	static void dump_leaks (void);
	std::string dump_objects (void);
	virtual std::string dump_dot (void);

protected:
	std::string dump_row (const char *name, long long value);
	std::string dump_row (const char *name, long value);
	std::string dump_row (const char *name, int value);
	std::string dump_row (const char *name, unsigned int value);
	std::string dump_row (const char *name, bool value);
	std::string dump_row (const char *name, std::string &value);
	std::string dump_row (const char *name, void *value);

	std::string get_size (long long size);

	std::vector<container*> children;

	void declare (const char *name, const char *colour = NULL);

	std::string dot_colour;
	int ref_count;
};

#endif // _CONTAINER_H_

