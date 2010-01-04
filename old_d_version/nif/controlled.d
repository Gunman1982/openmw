/*
  OpenMW - The completely unofficial reimplementation of Morrowind
  Copyright (C) 2008  Nicolay Korslund
  Email: < korslund@gmail.com >
  WWW: http://openmw.snaptoad.com/

  This file (controlled.d) is part of the OpenMW package.

  OpenMW is distributed as free software: you can redistribute it
  and/or modify it under the terms of the GNU General Public License
  version 3, as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  version 3 along with this program. If not, see
  http://www.gnu.org/licenses/ .

 */

module nif.controlled;

import nif.record;
import nif.extra;

// 'Controlled' is something that has a controller
abstract class Controlled : Extra
{
  Controller controller;  

 override:
  void read()
    {
      super.read();
      debug(verbose) writef("Controller ");
      getIndex();
    }

  void sortOut(Record[] list)
    {
      super.sortOut(list);
      controller = lookup!(Controller)(list);
    }
}

// Record with name and controller/extra data link
abstract class Named : Controlled
{
  // Name of this object. This is used to refer to the object from .kf
  // files.
  char[] name;

 override:
  char[] toString()
    {
      if(name.length)
	return super.toString() ~ " '" ~ name ~ "'";
      else
	return super.toString();
    }

  void read()
    {
      //super.read(f);
      name = nifFile.getString();
      debug(verbose) writefln("Name: %s", name);
      super.read();
    }
}

class NiSequenceStreamHelper : Named {}