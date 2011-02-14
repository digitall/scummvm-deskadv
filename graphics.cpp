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
#include "deskadv/graphics.h"

#include "deskadv/palette.h"

#include "common/file.h"

namespace Deskadv {

Gfx::Gfx(DeskadvEngine *vm) : _vm(vm) {
	initGraphics(320, 200, false);

	_screen = new Graphics::Surface();
	_screen->create(320, 200, 1);

	// Code to load palette from dump file
	// TODO: Need to identify offset in executable and load from there.
	/*Common::File pal;
	if (!pal.open("yopal.1")) {
		error("Failed to open yopal.1");
	}
	debug("static const uint8 palette[1024] = {");
	for(uint32 i = 0; i < 256; i++) {
		debugN("\t0x%02x, ", pal.readByte());
		debugN("0x%02x, ", pal.readByte());
		debugN("0x%02x, ", pal.readByte());
		debug("0x%02x, // %02d", pal.readByte(), i);
	}
	debug("\t};");
	pal.close();*/

	_vm->_system->getPaletteManager()->setPalette(palette, 0, sizeof(palette)/4);
}

Gfx::~Gfx() {
	_screen->free();
	delete _screen;
}

void Gfx::updateScreen(void) {
	debugC(1, kDebugGraphics, "Gfx::updateScreen()");
	_vm->_system->copyRectToScreen((byte *)_screen->pixels, _screen->pitch, 0, 0, 320, 200);
	_vm->_system->updateScreen();
}

void Gfx::drawTile(uint32 ref, uint x, uint y) {
	debugC(1, kDebugGraphics, "Gfx::drawTile(ref: %d, x: %d, y: %d)", ref, x, y);
	byte *tile = _vm->_resource->getTileData(ref);
	for (uint i = 0; i < 32; i++) {
		memcpy(_screen->getBasePtr(x, y+i), tile+(i*32), 32);
	}
}

void Gfx::viewPalette(void) {
	Common::Rect rect(0, 0, 16, 12);
	for (int i = 0; i < 256; i++) {
		_screen->fillRect(rect, i);
		if (i % 20 == 19)
			rect.moveTo(0, rect.bottom);
		else
			rect.translate(16, 0);
	}

	updateScreen();
}

} // End of namespace Deskadv
