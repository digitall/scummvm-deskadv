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

	bool Cmd_ViewPalette(int argc, const char **argv);
	bool Cmd_DrawTile(int argc, const char **argv);
	bool Cmd_drawWeapon(int argc, const char **argv);
	bool Cmd_drawWeaponPower(int argc, const char **argv);
	bool Cmd_eraseInventoryItem(int argc, const char **argv);
	bool Cmd_drawInventoryItem(int argc, const char **argv);
	bool Cmd_drawDirectionArrows(int argc, const char **argv);
	bool Cmd_drawHealthMeter(int argc, const char **argv);
	bool Cmd_ChangeCursor(int argc, const char **argv);
	bool Cmd_ListSounds(int argc, const char **argv);
	bool Cmd_PlaySound(int argc, const char **argv);
	bool Cmd_StopSound(int argc, const char **argv);
	bool Cmd_DrawZone(int argc, const char **argv);
};

} // End of namespace Deskadv

#endif
