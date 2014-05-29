/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#ifndef DESKADV_CONSOLE_H
#define DESKADV_CONSOLE_H

#include "gui/debugger.h"

namespace Deskadv {

class DeskadvEngine;

class DeskadvConsole : public GUI::Debugger {
public:
	DeskadvConsole(DeskadvEngine *vm);
	virtual ~DeskadvConsole(void);

private:
	DeskadvEngine *_vm;

	bool cmdViewPalette(int argc, const char **argv);
	bool cmdDrawStartup(int argc, const char **argv);
	bool cmdDrawTile(int argc, const char **argv);
	bool cmdDrawWeapon(int argc, const char **argv);
	bool cmdDrawWeaponPower(int argc, const char **argv);
	bool cmdEraseInventoryItem(int argc, const char **argv);
	bool cmdDrawInventoryItem(int argc, const char **argv);
	bool cmdDrawDirectionArrows(int argc, const char **argv);
	bool cmdDrawHealthMeter(int argc, const char **argv);
	bool cmdChangeCursor(int argc, const char **argv);
	bool cmdListSounds(int argc, const char **argv);
	bool cmdPlaySound(int argc, const char **argv);
	bool cmdStopSound(int argc, const char **argv);
	bool cmdDrawZone(int argc, const char **argv);
};

} // End of namespace Deskadv

#endif
