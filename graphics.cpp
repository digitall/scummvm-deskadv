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

static const uint screenWidth = 508;
static const uint screenHeight = 332;

Gfx::Gfx(DeskadvEngine *vm) : _vm(vm) {
	initGraphics(screenWidth, screenHeight, true);

	_screen = new Graphics::Surface();
	_screen->create(screenWidth, screenHeight, 1);

	// Code to load palette from dump file
	// TODO: Need to identify offset in executable and load from there.
	/*Common::File pal;
	if (!pal.open("yopal.1")) {
		error("Failed to open yopal.1");
	}
	debug("static const uint8 palette[768] = {");
	for(uint32 i = 0; i < 256; i++) {
		debugN("\t0x%02x, ", pal.readByte());
		debugN("0x%02x, ", pal.readByte());
		debugN("0x%02x, ", pal.readByte());
		pal.readByte();
		debug(" // %02d", i);
	}
	debug("\t};");
	pal.close();*/

	_vm->_system->getPaletteManager()->setPalette(palette, 0, sizeof(palette)/3);
}

Gfx::~Gfx() {
	_screen->free();
	delete _screen;
}

void Gfx::updateScreen(void) {
	debugC(1, kDebugGraphics, "Gfx::updateScreen()");
	_vm->_system->copyRectToScreen((byte *)_screen->pixels, _screen->pitch, 0, 0, screenWidth, screenHeight);
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

static const Common::Rect tileArea(13, 31, 13+(9*32), 31+(9*32));

// Reference is Apex Of Arrow
static const Common::Point UpArrow(341, 269);
static const Common::Point DownArrow(341, 311);
static const Common::Point LeftArrow(320, 290);
static const Common::Point RightArrow(362, 290);

static const Common::Rect weaponArea(383, 275, 383+32, 275+32);
static const Common::Rect weaponPowerArea(367, 275, 367+8, 275+32);

void Gfx::drawScreenOutline(void) {
	Common::Rect rect(1, 1, screenWidth-1, screenHeight-1);
	_screen->fillRect(rect, MEDIUM_GREY);
	_screen->hLine(0, 18, screenWidth-1, BLACK);

	Common::Rect outer(4, 22, screenWidth-4, screenHeight-4);
	drawShadowFrame(&outer, false, false, 3);

	_screen->fillRect(tileArea, BLACK);
	drawShadowFrame(&tileArea, true, false, 3);

	// Inventory
	// TODO

	// Direction Arrows Outline
	// Up Arrow
	_screen->drawLine(UpArrow.x, UpArrow.y, UpArrow.x-7, UpArrow.y+7, ARROW_SHADOW);
	_screen->drawLine(UpArrow.x, UpArrow.y, UpArrow.x+7, UpArrow.y+7, ARROW_SHADOW);

	_screen->drawLine(UpArrow.x-7, UpArrow.y+7, UpArrow.x-7, UpArrow.y+7+2, ARROW_SHADOW);
	_screen->drawLine(UpArrow.x+7, UpArrow.y+7, UpArrow.x+7, UpArrow.y+7+2, ARROW_SHADOW);

	_screen->drawLine(UpArrow.x-7, UpArrow.y+7+2, UpArrow.x-3, UpArrow.y+7+2, WHITE);
	_screen->drawLine(UpArrow.x+7, UpArrow.y+7+2, UpArrow.x+3, UpArrow.y+7+2, WHITE);

	_screen->drawLine(UpArrow.x-3, UpArrow.y+7+2, UpArrow.x-3, UpArrow.y+7+2+4, ARROW_SHADOW);
	_screen->drawLine(UpArrow.x+3, UpArrow.y+7+2, UpArrow.x+3, UpArrow.y+7+2+4, WHITE);

	_screen->drawLine(UpArrow.x-3, UpArrow.y+7+2+4, UpArrow.x+3, UpArrow.y+7+2+4, WHITE);

	// Down Arrow
	_screen->drawLine(DownArrow.x, DownArrow.y, DownArrow.x-7, DownArrow.y-7, ARROW_SHADOW);
	_screen->drawLine(DownArrow.x, DownArrow.y, DownArrow.x+7, DownArrow.y-7, WHITE);

	_screen->drawLine(DownArrow.x-7, DownArrow.y-7, DownArrow.x-7, DownArrow.y-7-2, ARROW_SHADOW);
	_screen->drawLine(DownArrow.x+7, DownArrow.y-7, DownArrow.x+7, DownArrow.y-7-2, ARROW_SHADOW);

	_screen->drawLine(DownArrow.x-7, DownArrow.y-7-2, DownArrow.x-3, DownArrow.y-7-2, ARROW_SHADOW);
	_screen->drawLine(DownArrow.x+7, DownArrow.y-7-2, DownArrow.x+3, DownArrow.y-7-2, ARROW_SHADOW);

	_screen->drawLine(DownArrow.x-3, DownArrow.y-7-2, DownArrow.x-3, DownArrow.y-7-2-4, ARROW_SHADOW);
	_screen->drawLine(DownArrow.x+3, DownArrow.y-7-2, DownArrow.x+3, DownArrow.y-7-2-4, WHITE);

	_screen->drawLine(DownArrow.x-3, DownArrow.y-7-2-4, DownArrow.x+3, DownArrow.y-7-2-4, ARROW_SHADOW);

	// Left Arrow
	_screen->drawLine(LeftArrow.x, LeftArrow.y, LeftArrow.x+7, LeftArrow.y-7, ARROW_SHADOW);
	_screen->drawLine(LeftArrow.x, LeftArrow.y, LeftArrow.x+7, LeftArrow.y+7, ARROW_SHADOW);

	_screen->drawLine(LeftArrow.x+7, LeftArrow.y-7, LeftArrow.x+7+2, LeftArrow.y-7, ARROW_SHADOW);
	_screen->drawLine(LeftArrow.x+7, LeftArrow.y+7, LeftArrow.x+7+2, LeftArrow.y+7, WHITE);

	_screen->drawLine(LeftArrow.x+7+2, LeftArrow.y-7, LeftArrow.x+7+2, LeftArrow.y-7+4, WHITE);
	_screen->drawLine(LeftArrow.x+7+2, LeftArrow.y+7, LeftArrow.x+7+2, LeftArrow.y+7-4, WHITE);

	_screen->drawLine(LeftArrow.x+7+2, LeftArrow.y-7+4, LeftArrow.x+7+2+4, LeftArrow.y-7+4, ARROW_SHADOW);
	_screen->drawLine(LeftArrow.x+7+2, LeftArrow.y+7-4, LeftArrow.x+7+2+4, LeftArrow.y+7-4, WHITE);

	_screen->drawLine(LeftArrow.x+7+2+4, LeftArrow.y-7+4, LeftArrow.x+7+2+4, LeftArrow.y+7-4, WHITE);

	// Right Arrow
	_screen->drawLine(RightArrow.x, RightArrow.y, RightArrow.x-7, RightArrow.y-7, ARROW_SHADOW);
	_screen->drawLine(RightArrow.x, RightArrow.y, RightArrow.x-7, RightArrow.y+7, WHITE);

	_screen->drawLine(RightArrow.x-7, RightArrow.y-7, RightArrow.x-7-2, RightArrow.y-7, ARROW_SHADOW);
	_screen->drawLine(RightArrow.x-7, RightArrow.y+7, RightArrow.x-7-2, RightArrow.y+7, WHITE);

	_screen->drawLine(RightArrow.x-7-2, RightArrow.y-7, RightArrow.x-7-2, RightArrow.y-7+4, ARROW_SHADOW);
	_screen->drawLine(RightArrow.x-7-2, RightArrow.y+7, RightArrow.x-7-2, RightArrow.y+7-4, ARROW_SHADOW);

	_screen->drawLine(RightArrow.x-7-2, RightArrow.y-7+4, RightArrow.x-7-2-4, RightArrow.y-7+4, ARROW_SHADOW);
	_screen->drawLine(RightArrow.x-7-2, RightArrow.y+7-4, RightArrow.x-7-2-4, RightArrow.y+7-4, WHITE);

	_screen->drawLine(RightArrow.x-7-2-4, RightArrow.y-7+4, RightArrow.x-7-2-4, RightArrow.y+7-4, ARROW_SHADOW);

	// WeaponArea
	drawShadowFrame(&weaponArea, true, true, 3);
	if (_vm->getGameType() == GType_Yoda) {
		drawShadowFrame(&weaponPowerArea, true, true, 3);

		// TODO: Need to work out which color index is mapped to (0x8b, 0x8b, 0xb3)
		//_screen->fillRect(weaponArea, LIGHT_PURPLE);
		//_screen->fillRect(weaponPowerArea, LIGHT_PURPLE);
	}

	// Health Meter
	// TODO 24 levels i.e. 3 levels of 8
	// Draw Pie shaped polygon.. or wedged shaped and mask over with grey outer
	// at end. Just use arbitary line drawing from centre to perimeter...
	// GREEN, HEALTH_YELLOW, HEALTH_RED, BLACK
}

void Gfx::drawWeapon(uint32 ref) {
	drawTile(ref, weaponArea.left, weaponArea.top);
}

void Gfx::drawWeaponPower(uint8 level) {
	if (_vm->getGameType() != GType_Yoda) {
		warning("Unexpected Gfx::drawWeaponPower()!");
		return;
	}

	if (level > 31) {
		warning("Gfx::drawWeaponPower() level clamped to maximum.");
		level = 31;
	}

	uint color = BLACK;
	for (uint8 i = 0; i < 32; i++) {
		if (i > level)
			color = MEDIUM_GREY;
		else
			color = POWER_BLUE;
		_screen->hLine(weaponPowerArea.left, weaponPowerArea.bottom-i, weaponPowerArea.right, color);
	}
}

void Gfx::drawDirectionArrows(bool left, bool up, bool right, bool down) {
	// TODO: Write Code
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

void Gfx::drawShadowFrame(const Common::Rect *rect, bool recessed, bool firstInverse, uint thickness) {
	// Shadow as if lit from top left corner.

	uint TLColor, BRColor;
	if (recessed) {
		// rect sub-area recessed
		TLColor = DARK_GREY;
		BRColor = LIGHT_GREY;
	} else {
		// rect sub-area raised
		TLColor = LIGHT_GREY;
		BRColor = DARK_GREY;
	}

	for (uint i = 0; i < thickness; i++) {
		// Left Border
		_screen->vLine(rect->left-1-i, rect->top-1-i, rect->bottom-1+1+i, (firstInverse && i == 0) ? BRColor : TLColor);

		// Right Border
		_screen->vLine(rect->right-1+1+i, rect->top-1-i, rect->bottom-1+1+i, (firstInverse && i == 0) ? TLColor : BRColor);

		// Top Border
		_screen->hLine(rect->left-1-i, rect->top-1-i, rect->right-1+1+i, (firstInverse && i == 0) ? BRColor : TLColor);

		// Bottom Border
		_screen->hLine(rect->left-1-i, rect->bottom-1+1+i, rect->right-1+1+i, (firstInverse && i == 0) ? TLColor : BRColor);
	}
}

} // End of namespace Deskadv
