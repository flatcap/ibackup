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
#include <iostream>
#include <memory>
#include <deque>
#include <utility>
#include <string>

#include "backup.h"
#include "container.h"
#include "disk.h"
#include "fs.h"
#include "partition.h"

/**
 * run_dot
 */
void run_dot (const std::string &input, const std::string &title)
{
	FILE *file = NULL;

	std::string command = "dot -Tpng | display -title \"" + title + "\" -resize 65% - &";

	file = popen (command.c_str(), "w");

	fprintf (file, "%s\n", input.c_str());

	pclose (file);
}


/**
 * main
 */
int main (int argc, char *argv[])
{
	typedef std::pair<std::string,container*> time_pair;
	typedef std::deque<time_pair>             time_deq;
	time_deq timeline;

	disk *d1;
	partition *p1, *p2;
	fs *f1, *f2;

	// device discovery
	d1 = new disk;
	d1->label = "fedora";
	d1->serial = "0x1234";
	d1->size = 100;

	//manager->add (NULL, d1);

	p1 = new partition();
	p1->type = 42;
	p1->size = 30;

	f1 = new fs();
	f1->fstype = "ext4";
	f1->size = 30;

	p1->add (f1);

	d1->add (p1);

	p2 = new partition();
	p2->type = 99;
	p2->size = 20;

	f2 = new fs();
	f2->fstype = "ntfs";
	f2->size = 15;

	p2->add (f2);

	d1->add (p2);

	run_dot (d1->dump_objects(), "first");

	time_pair event("delete partition", p2);
	timeline.push_back (event);
	auto time_iter = timeline.back();
	p2->remove(0);

	run_dot (d1->dump_objects(), "second");

	delete d1;
	d1->dump_leaks();
	return 0;
}

