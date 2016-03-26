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
	registerCmd("viewPalette", WRAP_METHOD(DeskadvConsole, cmdViewPalette));
	registerCmd("drawStartup", WRAP_METHOD(DeskadvConsole, cmdDrawStartup));
	registerCmd("drawTile", WRAP_METHOD(DeskadvConsole, cmdDrawTile));
	registerCmd("drawWeapon", WRAP_METHOD(DeskadvConsole, cmdDrawWeapon));
	registerCmd("drawWeaponPower", WRAP_METHOD(DeskadvConsole, cmdDrawWeaponPower));
	registerCmd("eraseInventoryItem", WRAP_METHOD(DeskadvConsole, cmdEraseInventoryItem));
	registerCmd("drawInventoryItem", WRAP_METHOD(DeskadvConsole, cmdDrawInventoryItem));
	registerCmd("drawDirectionArrows", WRAP_METHOD(DeskadvConsole, cmdDrawDirectionArrows));
	registerCmd("drawHealthMeter", WRAP_METHOD(DeskadvConsole, cmdDrawHealthMeter));
	registerCmd("changeCursor", WRAP_METHOD(DeskadvConsole, cmdChangeCursor));
	registerCmd("listSounds", WRAP_METHOD(DeskadvConsole, cmdListSounds));
	registerCmd("playSound", WRAP_METHOD(DeskadvConsole, cmdPlaySound));
	registerCmd("stopSound", WRAP_METHOD(DeskadvConsole, cmdStopSound));
	registerCmd("drawZone", WRAP_METHOD(DeskadvConsole, cmdDrawZone));
}

DeskadvConsole::~DeskadvConsole() {
}

bool DeskadvConsole::cmdViewPalette(int argc, const char **argv) {
	_vm->_gfx->viewPalette();
	return false;
}

bool DeskadvConsole::cmdDrawStartup(int argc, const char **argv) {
	_vm->_gfx->drawStartup();
	return false;
}

bool DeskadvConsole::cmdDrawTile(int argc, const char **argv) {
	if (argc != 4) {
		debugPrintf("Usage: drawTile <ref> <x> <y>\n");
		return true;
	}

	uint32 ref = atoi(argv[1]);
	uint8 x = atoi(argv[2]);
	uint8 y = atoi(argv[3]);
	_vm->_gfx->drawTile(ref, x, y);
	return false;
}

bool DeskadvConsole::cmdDrawWeapon(int argc, const char **argv) {
	if (argc != 2) {
		debugPrintf("Usage: drawWeapon <ref>\n");
		return true;
	}

	uint32 ref = atoi(argv[1]);
	_vm->_gfx->drawWeapon(ref);
	return false;
}

bool DeskadvConsole::cmdDrawWeaponPower(int argc, const char **argv) {
	if (argc != 2) {
		debugPrintf("Usage: drawWeaponPower <level>\n");
		return true;
	}

	uint8 level = atoi(argv[1]);
	_vm->_gfx->drawWeaponPower(level);
	return false;
}

bool DeskadvConsole::cmdEraseInventoryItem(int argc, const char **argv) {
	if (argc != 2) {
		debugPrintf("Usage: eraseInventoryItem <slot num>\n");
		return true;
	}

	uint slot = atoi(argv[1]);

	_vm->_gfx->eraseInventoryItem(slot);
	return false;
}

bool DeskadvConsole::cmdDrawInventoryItem(int argc, const char **argv) {
	if (argc != 3) {
		debugPrintf("Usage: drawInventoryItem <slot num> <icon ref>\n");
		return true;
	}

	uint slot = atoi(argv[1]);
	uint32 iconRef = atoi(argv[2]);

	_vm->_gfx->drawInventoryItem(slot, iconRef, _vm->_resource->getTileName(iconRef));
	return false;
}

bool DeskadvConsole::cmdDrawDirectionArrows(int argc, const char **argv) {
	if (argc != 5) {
		debugPrintf("Usage: drawDirectionArrows <left> <up> <right> <down>\n");
		return true;
	}

	uint8 left = atoi(argv[1]);
	uint8 up = atoi(argv[2]);
	uint8 right = atoi(argv[3]);
	uint8 down = atoi(argv[4]);

	_vm->_gfx->drawDirectionArrows(left, up, right, down);
	return false;
}

bool DeskadvConsole::cmdDrawHealthMeter(int argc, const char **argv) {
	if (argc != 2) {
		debugPrintf("Usage: drawHealthMeter <level>\n");
		return true;
	}

	uint level = atoi(argv[1]);

	_vm->_gfx->drawHealthMeter(level);
	return false;
}

bool DeskadvConsole::cmdChangeCursor(int argc, const char **argv) {
	if (argc != 2) {
		debugPrintf("changeCursor <id>\n");
		return true;
	}

	uint id = atoi(argv[1]);

	_vm->_gfx->changeCursor(id);
	_vm->_gfx->updateScreen();
	return true;
}

bool DeskadvConsole::cmdListSounds(int argc, const char **argv) {
	if (argc != 1) {
		debugPrintf("listSounds\n");
		return true;
	}

	for (int i = 0; i < _vm->_resource->getSoundCount(); i++)
		debugPrintf("Sound %d: \"%s\"\n", i, _vm->_resource->getSoundFilename(i));
	return true;
}

bool DeskadvConsole::cmdPlaySound(int argc, const char **argv) {
	if (argc != 2) {
		debugPrintf("playSound <ref>\n");
		return true;
	}

	uint32 ref = atoi(argv[1]);

	debugPrintf("Playing Sound %d...\n", ref);
	_vm->_snd->playSound(ref);

	return false;
}

bool DeskadvConsole::cmdStopSound(int argc, const char **argv) {
	if (argc != 1) {
		debugPrintf("stopSound\n");
		return true;
	}

	debugPrintf("Stopping Sound\n");
	_vm->_snd->stopSFX();
	_vm->_snd->stopMID();

	return true;
}

bool DeskadvConsole::cmdDrawZone(int argc, const char **argv) {
	if (argc != 2) {
		debugPrintf("drawZone <num = 0 to %d>\n", _vm->_resource->getZoneCount());
		return true;
	}

	uint16 num = atoi(argv[1]);

	if (num >= _vm->_resource->getZoneCount()) {
		debugPrintf("zone num must be in range 0 to %d\n", _vm->_resource->getZoneCount());
		return true;
	}

	// TODO: Add Support to scroll Zone.
	if (num < _vm->_resource->getZoneCount()) {
		ZONE *z = _vm->_resource->getZone(num);
		for (uint y = 0; y < 9; y++) {
			for (uint x = 0; x < 9; x++) {
				for (uint layer = 0; layer < 3; layer++) {
					uint16 tileRef = z->tiles[layer][(y*z->width)+x];
					if (tileRef != 0xFFFF)
						_vm->_gfx->drawTile(tileRef, x, y);
				}
			}
		}
	}

	return false;
}

} // End of namespace Deskadv
