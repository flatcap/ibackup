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
#include <typeinfo>
#include <set>

#include <math.h>

#include "container.h"

std::set<container*> obj_set;

/**
 * container (default)
 */
container::container() :
	size(0)
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	declare ("container");
}

/**
 * container (copy)
 */
container::container (const container &c) :
	size (c.size),
	children (c.children)
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	declare ("container");
}

/**
 * container (move)
 */
container::container (container &&c) :
	container()
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	swap (*this, c);
}

/**
 * ~container
 */
container::~container()
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	for (auto c : children) {
		delete c;
	}
}


/**
 * operator new
 */
void * container::operator new (size_t s)
{
	container *b = (container*) malloc (s);

	//log_info ("new object %p\n", (void*) b);
	obj_set.insert (b);

	return b;
}

/**
 * operator delete
 */
void container::operator delete (void *ptr)
{
	if (!ptr)
		return;

	container *c = (container *) (ptr);
	if (c->ref_count != 0)
		printf ("REF COUNT = %d\n", c->ref_count);

	//log_info ("deleted object %p\n", ptr);
	obj_set.erase (c);
	free (ptr);
}

/**
 * operator=
 */
container & container::operator= (container c)
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	swap (*this, c);
	return *this;
}

/**
 * swap
 */
void swap (container &first, container &second)
{
	//printf ("%s (%p,%p)\n", __PRETTY_FUNCTION__, &first, &second);
	std::swap (first.children, second.children);
}

/**
 * operator<<
 */
std::ostream& operator<< (std::ostream &stream, const container &c)
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
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
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	if (c)
		return operator<< (stream, *c);
	else
		return stream;
}


/**
 * add
 */
int container::add (container *c)
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	children.push_back(c);
	return children.size();
}

/**
 * remove
 */
int container::remove (int index)
{
	//printf ("%s (%p)\n", __PRETTY_FUNCTION__, this);
	auto iter = children.begin() + index;
	delete *iter;
	children.erase(iter);
	return children.size();
}


/**
 * dump_dot
 */
std::string container::dump_dot (void)
{
	std::ostringstream output;

	output << dump_row ("size", size);

	return output.str();
}


/**
 * is_a
 */
bool container::is_a (const std::string &t)
{
	//std::cout << "my type = " << type.back() << ", compare to " << t << "\n";

	// Start with the most derived type
	for (auto it = type.rbegin(); it != type.rend(); it++) {
		if ((*it) == t) {
			return true;
		}
	}

	return false;
}

/**
 * declare
 */
void container::declare (const char *n, const char *colour)
{
	type.push_back (n);
	name = n;
	if (colour) {
		dot_colour = colour;
	}
}


/**
 * ref
 */
void container::ref (void)
{
	ref_count++;
}

/**
 * unref
 */
void container::unref (void)
{
	ref_count--;
	if (ref_count == 0)
		delete this;
}


/**
 * get_size
 */
std::string container::get_size (long long size)
{
	char buffer[64];
	double power = log2 ((double) llabs (size)) + 0.5;
	const char *suffix = "";
	double divide = 1;

	if (power < 10) {
		suffix = "   B";
		divide = 1;
	} else if (power < 20) {
		suffix = " KiB";
		divide = 1024;
	} else if (power < 30) {
		suffix = " MiB";
		divide = 1048576;
	} else if (power < 40) {
		suffix = " GiB";
		divide = 1073741824;
	} else if (power < 50) {
		suffix = " TiB";
		divide = 1099511627776;
	} else if (power < 60) {
		suffix = " PiB";
		divide = 1125899906842624;
	}
	sprintf (buffer, "%0.3g%s", (double)size/divide, suffix);
	return buffer;
}


/**
 * dump_row
 */
std::string container::dump_row (const char *name, long long value)
{
	std::ostringstream s;
	std::string str = get_size (value);

	s << "<tr>";
	s << "<td align=\"left\">" << name << "</td>";
	s << "<td>=</td>";
#if 1
	s << "<td align=\"left\">" << str << "</td>";
#else
	s << "<td align=\"left\">" << value << " (" << str << ")</td>";
#endif
	s << "</tr>\n";

	return s.str();
}

/**
 * dump_row
 */
std::string container::dump_row (const char *name, long value)
{
	std::ostringstream s;

	s << "<tr>";
	s << "<td align=\"left\">" << name << "</td>";
	s << "<td>=</td>";
	s << "<td align=\"left\">" << value << "</td>";
	s << "</tr>\n";

	return s.str();
}

/**
 * dump_row
 */
std::string container::dump_row (const char *name, int value)
{
	std::ostringstream s;

	s << "<tr>";
	s << "<td align=\"left\">" << name << "</td>";
	s << "<td>=</td>";
	s << "<td align=\"left\">" << value << "</td>";
	s << "</tr>\n";

	return s.str();
}

/**
 * dump_row
 */
std::string container::dump_row (const char *name, unsigned int value)
{
	std::ostringstream s;

	s << "<tr>";
	s << "<td align=\"left\">" << name << "</td>";
	s << "<td>=</td>";
	s << "<td align=\"left\">" << value << "</td>";
	s << "</tr>\n";

	return s.str();
}

/**
 * dump_row
 */
std::string container::dump_row (const char *name, bool value)
{
	std::ostringstream s;

	s << "<tr>";
	s << "<td align=\"left\">" << name << "</td>";
	s << "<td>=</td>";
	s << "<td align=\"left\">" << (value ? "true" : "false") << "</td>";
	s << "</tr>\n";

	return s.str();
}

/**
 * dump_row
 */
std::string container::dump_row (const char *name, std::string &value)
{
	std::ostringstream s;

	s << "<tr>";
	s << "<td align=\"left\">" << name << "</td>";
	s << "<td>=</td>";
	s << "<td align=\"left\">" << value << "</td>";
	s << "</tr>\n";

	return s.str();
}

/**
 * dump_row
 */
std::string container::dump_row (const char *name, void *value)
{
	std::ostringstream s;

	s << "<tr>";
	s << "<td align=\"left\">" << name << "</td>";
	s << "<td>=</td>";
	s << "<td align=\"left\">" << value << "</td>";
	s << "</tr>\n";

	return s.str();
}


/**
 * dump_objects
 */
std::string container::dump_objects (void)
{
	std::ostringstream dot;

	dot << "digraph disks {\n";
	dot << "graph [ rankdir=\"TB\", color=\"white\",bgcolor=\"#000000\" ];\n";
	dot << "node [ shape=\"record\", color=\"black\", fillcolor=\"lightcyan\", style=\"filled\" ];\n";
	dot << "edge [ penwidth=3.0,color=\"#cccccc\" ];\n";
	dot << "\n";

#if 1
	for (auto c : obj_set) {
		//printf ("%s\n", c->name.c_str());
		dot << "\n";
		//dot << "// " << c << "\n";

		if (c->name.empty()) {
			c->name = "UNKNOWN";
		}
		if (c->dot_colour.empty()) {
			printf ("empty colour on %s\n", c->name.c_str());
			c->dot_colour = "white";
		}

		dot << "obj_" << (void*) c <<" [fillcolor=\"" << c->dot_colour << "\",label=<<table cellspacing=\"0\" border=\"0\">\n";
		//dot << "<tr><td align=\"left\" bgcolor=\"white\" colspan=\"3\"><font color=\"#000000\" point-size=\"20\"><b>" << c->name << "</b></font> (" << (void*) c << ")<font color=\"#ff0000\" point-size=\"20\"><b> : " << c->ref_count << "</b></font></td></tr>\n";
		dot << "<tr><td align=\"left\" bgcolor=\"white\" colspan=\"3\"><font color=\"#000000\" point-size=\"20\"><b>" << c->name << "</b></font> (" << (void*) c << ")</td></tr>\n";

		dot << c->dump_dot();

		dot << "</table>>];\n";

		for (auto ic : c->children) {
			dot << "obj_" << (void*) c << " -> obj_" << (void*) ic << ";\n";
		}
	}
#endif

	dot << "\n}";
	dot << "\n";

	return dot.str();
}

/**
 * dump_leaks
 */
void container::dump_leaks (void)
{
	if (obj_set.size() == 0)
		return;

	printf ("Leaks (%lu):\n", obj_set.size());
	for (auto c : obj_set) {
		//printf ("\t0x%p - %s, %s, %d\n", c, c->name.c_str(), c->device.c_str(), c->ref_count);
		printf ("\t0x%p\n", c);
	}
}


