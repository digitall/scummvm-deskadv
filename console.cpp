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

#include "deskadv/deskadv.h"
#include "deskadv/console.h"

namespace Deskadv {

DeskadvConsole::DeskadvConsole(DeskadvEngine *vm) : GUI::Debugger(), _vm(vm) {
	DCmd_Register("viewPalette", WRAP_METHOD(DeskadvConsole, Cmd_ViewPalette));
	DCmd_Register("drawTile", WRAP_METHOD(DeskadvConsole, Cmd_DrawTile));
	DCmd_Register("changeCursor", WRAP_METHOD(DeskadvConsole, Cmd_ChangeCursor));
	DCmd_Register("listSounds", WRAP_METHOD(DeskadvConsole, Cmd_ListSounds));
	DCmd_Register("playSound", WRAP_METHOD(DeskadvConsole, Cmd_PlaySound));
}

DeskadvConsole::~DeskadvConsole() {
}

bool DeskadvConsole::Cmd_ViewPalette(int argc, const char **argv) {
	_vm->_gfx->viewPalette();
	return false;
}

bool DeskadvConsole::Cmd_DrawTile(int argc, const char **argv) {
	if (argc != 4) {
		DebugPrintf("Usage: drawTile <ref> <x> <y>\n");
		return true;
	}

	uint32 ref = atoi(argv[1]);
	uint x = atoi(argv[2]);
	uint y = atoi(argv[3]);
	_vm->_gfx->drawTile(ref, x, y);
	_vm->_gfx->updateScreen();
	return false;
}

bool DeskadvConsole::Cmd_ChangeCursor(int argc, const char **argv) {
	if (argc != 2) {
		DebugPrintf("changeCursor <id>\n");
		return true;
	}

	uint id = atoi(argv[1]);

	_vm->_gfx->changeCursor(id);
	_vm->_gfx->updateScreen();
	return true;
}

bool DeskadvConsole::Cmd_ListSounds(int argc, const char **argv) {
	if (argc != 1) {
		DebugPrintf("listSounds\n");
		return true;
	}

	for (int i = 0; i < _vm->_resource->getSoundCount(); i++)
		DebugPrintf("Sound %d: \"%s\"\n", i, _vm->_resource->getSoundFilename(i));
	return true;
}

bool DeskadvConsole::Cmd_PlaySound(int argc, const char **argv) {
	if (argc != 2) {
		DebugPrintf("playSound <ref>\n");
		return true;
	}

	uint32 ref = atoi(argv[1]);

	DebugPrintf("Playing Sound %d...\n", ref);
	//_vm->_snd->playSFX(ref);
	_vm->_snd->playMID(ref);

	return true;
}

} // End of namespace Deskadv
