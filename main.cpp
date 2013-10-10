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

#include "backup.h"
#include "container.h"
#include "disk.h"
#include "fs.h"
#include "partition.h"

/**
 * make_tree
 */
static disk * make_tree (void)
{
	disk *d = new disk;
	d->size = 100;

	partition *p;
	fs *f;

	p = new partition();
	p->type = 42;
	p->size = 30;

	f = new fs();
	f->fstype = "ext4";
	f->size = 30;

	p->add (f);

	d->add (p);

	p = new partition();
	p->type = 99;
	p->size = 20;

	f = new fs();
	f->fstype = "ntfs";
	f->size = 15;

	p->add (f);

	d->add (p);

	return d;
}

/**
 * run_dot
 */
void run_dot (const std::string &input)
{
	FILE *file = NULL;

	file = popen ("dot -Tpng | display -resize 75% - &", "w");

	fprintf (file, "%s\n", input.c_str());

	pclose (file);
}


/**
 * main
 */
int main (int argc, char *argv[])
{
	disk *d = make_tree();
	d->label = "fedora";
	d->serial = "0x1234";

	run_dot (d->dump_objects());

	delete d;
	d->dump_leaks();
	return 0;
}

