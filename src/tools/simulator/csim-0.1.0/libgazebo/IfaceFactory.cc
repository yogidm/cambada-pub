/*
 *  Gazebo - Outdoor Multi-Robot Simulator
 *  Copyright (C) 2003
 *     Nate Koenig & Andrew Howard
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
/*
 * Desc: Factory for creating iface
 * Author: Nate Koenig
 * Date: 06 May 2007
 * SVN info: $Id: IfaceFactory.cc 7044 2008-09-24 18:12:51Z natepak $
 */

#include <sstream>
#include <iostream>

#include "gazebo.h"
#include "IfaceFactory.hh"

using namespace gazebo;

std::map<std::string, IfaceFactoryFn> *IfaceFactory::ifaces;

// Register a iface class.  Use by dynamically loaded modules
void IfaceFactory::RegisterIface(std::string classname, IfaceFactoryFn factoryfn)
{
  if (ifaces == 0)
    ifaces = new std::map<std::string, IfaceFactoryFn>();

  (*ifaces)[classname] = factoryfn;
}

// Create a new instance of a iface.  Used by the world when reading
// the world file.
Iface *IfaceFactory::NewIface(const std::string &classname)
{
  if (ifaces->find(classname) != ifaces->end())
  {
    return ((*ifaces)[classname]) ();
  }
  else
  {
    std::ostringstream stream;
    stream << "Unable to make interface of type " << classname;
    throw(stream.str());
  }


  return NULL;
}
