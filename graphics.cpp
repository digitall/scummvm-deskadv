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

#include "graphics/cursorman.h"
#include "graphics/imagedec.h"

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

void Gfx::loadNECursors(const char *filename) {
		_ne.loadFromEXE(filename);
		_NECursor = _ne.getCursors();
		debugC(1, kDebugGraphics, "Loading NE Cursors: Found %d", _NECursor.size());
		for (uint i = 0; i < _NECursor.size(); i++)
			debugC(1, kDebugGraphics, "\tFound %d Cursors of Resource id: %s", _NECursor[i].cursors.size(), _NECursor[i].id.toString().c_str());
}

void Gfx::changeCursor(uint id) {
		if (id >= _NECursor.size()) {
			warning("Attempted to set invalid cursor id:%d", id);
			return;
		}

		const Common::NECursor *cur = _NECursor[id].cursors[0];
		//  0 -       Left Arrow White Filled (0x006a)
		//  1 -      Right Arrow White Filled (0x006b)
		//  2 -         Up Arrow White Filled (0x006c)
		//  3 -       Down Arrow White Filled (0x006d)
		//  4 -    Up-Left Arrow White Filled (0x0071)
		//  5 -   Up-Right Arrow White Filled (0x0072)
		//  6 -  Down-Left Arrow White Filled (0x0073)
		//  7 - Down-Right Arrow White Filled (0x0074)
		//  8 -            Cross White Filled (0x0076)
		//  9 -             Hand White Filled (0x00c2)
		//
		// 10 -    Win3.1        Context Help (0x7901)
		// 11 -    Win3.1         Move Window (0x7903)
		// 12 -    Win3.1   Horizontal Resize (0x7904)
		// 13 -    Win3.1     Vertical Resize (0x7905)
		// 14 -    Win3.1            No Entry (0x7906)
		// 15 -    Win3.1 Bottom Right Resize (0x7907)
		// 16 -    Win3.1 Bottom  Left Resize (0x7908)
		// 17 -    Win3.1 Vertical     Resize (0x7909)
		// 18 -    Win3.1 Horizontal   Resize (0x790a)
		// 19 -    Win3.1 Move         Window (0x790b)
		// 20 -    Win3.1   Pointer with Move (0x790c)
		CursorMan.replaceCursorPalette(cur->getPalette(), 0, 256);
		CursorMan.replaceCursor(cur->getSurface(), cur->getWidth(), cur->getHeight(), cur->getHotspotX(), cur->getHotspotY(), 0);
}

void Gfx::loadBMP(const char *filename, uint x, uint y) {
	Common::File imageFile;

	if (!imageFile.open(filename))
		error("LoadBMP : Failed to open \"%s\"", filename);

	Graphics::Surface *image = Graphics::ImageDecoder::loadFile(imageFile, _vm->_system->getOverlayFormat());

	if (image) {
		// TODO: Format conversion needed?
		for (uint i = 0; i < image->h; i++)
			memcpy(_screen->getBasePtr(x, y+i), image->getBasePtr(0, i), image->w);

		image->free();
		delete image;
	} else
		warning("loadBMP failure!");
	imageFile.close();
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
