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
#include "graphics/wincursor.h"
#include "graphics/fontman.h"
#include "graphics/imagedec.h"

namespace Deskadv {

static const uint screenWidth = 532;
static const uint screenHeight = 332;

// Inventory Scroll Bar
static const Common::Rect InvScrollOuter(504, 30, 504+16, 268);
static const Common::Rect InvScroll(InvScrollOuter.left, InvScrollOuter.top+13, InvScrollOuter.right, InvScrollOuter.bottom-13);
static const Common::Rect InvScrUp(InvScrollOuter.left+2, InvScrollOuter.top+2, InvScrollOuter.right-2, InvScrollOuter.top+2+9);
static const Common::Rect InvScrDown(InvScrollOuter.left+2, InvScrollOuter.bottom-2-9, InvScrollOuter.right-2, InvScrollOuter.bottom-2);

Gfx::Gfx(DeskadvEngine *vm) : _vm(vm) {
	initGraphics(screenWidth, screenHeight, true);

	_screen = new Graphics::Surface();
	_screen->create(screenWidth, screenHeight, 1);

	// Code to load palette from dump file
	// TODO: Need to identify offset in executable and load from there.
	/*Common::File palFile;
	if (!palFile.open("deskadv.exe")) {
		error("Failed to open deskadv.exe");
	}
	palFile.seek(0x33e9e, SEEK_SET); // Indy Demo
	debug("static const uint8 palette[768] = {");
	for(uint32 i = 0; i < 241; i++) {
		debugN("\t0x%02x, ", palFile.readByte());
		debugN("0x%02x, ", palFile.readByte());
		debugN("0x%02x, ", palFile.readByte());
		if (palFile.readByte() != 0)
			warning("Palette Entry %d Alpha is non-zero", i);
		debug(" // %02d", i+10);
	}
	debug("\t};");
	palFile.close();*/

	const uint8 *palData;
	uint8 pal[256 * 3];
	switch (_vm->getGameType()) {
	case GType_Indy:
		palData = indyPalette;
		break;
	case GType_Yoda:
		palData = yodaPalette;
		break;
	default:
		error("Unknown Game Type for Palette Setting...");
		break;
	}
	// Convert Palette from stored BGR to RGB
	for (uint i = 0; i < 256; i++) {
		uint8 blue = palData[(i*3)+0];
		uint8 green = palData[(i*3)+1];
		uint8 red = palData[(i*3)+2];
		pal[(i*3)+0] = red;
		pal[(i*3)+1] = green;
		pal[(i*3)+2] = blue;
	}
	_vm->_system->getPaletteManager()->setPalette(pal, 0, 256);

	_font = FontMan.getFontByUsage(Graphics::FontManager::kGUIFont);
	if (!_font)
		error("Font Not Found!");

	InvScrThumb = new Common::Rect();
}

Gfx::~Gfx() {
	_screen->free();
	delete _screen;

	delete InvScrThumb;
}

void Gfx::updateScreen(void) {
	debugC(1, kDebugGraphics, "Gfx::updateScreen()");
	_vm->_system->copyRectToScreen((byte *)_screen->pixels, _screen->pitch, 0, 0, screenWidth, screenHeight);
	_vm->_system->updateScreen();
}

void Gfx::drawTileInt(uint32 ref, uint x, uint y, byte transparentColor) {
	debugC(1, kDebugGraphics, "Gfx::drawTileInt(ref: %d, x: %d, y: %d)", ref, x, y);
	byte *tile = _vm->_resource->getTileData(ref);
	for (uint dy = 0; dy < 32; dy++) {
		for (uint dx = 0; dx < 32; dx++) {
			byte pixel = *(tile+(dy*32)+dx);
			if ((pixel != 0 && pixel < 10) || (pixel != 255 && pixel > 245))
				warning("Gfx::drawTileInt(ref: %d) uses System Palette Index: %d", ref, pixel);
			debugC(1, kDebugGraphics, "Gfx::drawTileInt x:%d y:%d pixel:%d", x, y, pixel);
			if (pixel != transparentColor)
				*((byte *)_screen->getBasePtr(x+dx, y+dy)) = pixel;
		}
	}
	delete[] tile;
}

void Gfx::loadNECursors(const char *filename) {
	_ne.loadFromEXE(filename);
	_cursor = _ne.getIDList(Common::kNECursor);
	debugC(1, kDebugGraphics, "Loading NE Cursors: Found %d", _cursor.size());
	for (uint i = 0; i < _cursor.size(); i++)
		debugC(1, kDebugGraphics, "\tCursor %d Resource id: %s", i, _cursor[i].toString().c_str());
}

void Gfx::loadPECursors(const char *filename) {
	Common::WinResourceID c(Common::kPECursor);
	_pe.loadFromEXE(filename);
	_cursor = _pe.getNameList(c);
	debugC(1, kDebugGraphics, "Loading PE Cursors: Found %d", _cursor.size());
	for (uint i = 0; i < _cursor.size(); i++)
		debugC(1, kDebugGraphics, "\tCursor %d Resource id: %s", i, _cursor[i].toString().c_str());
}

void Gfx::setDefaultCursor() {
	static const byte s_bwPalette[] = {
		0x00, 0x00, 0x00,	// Black
		0xFF, 0xFF, 0xFF	// White
	};

	static const byte defaultCursor[] = {
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 2, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0,
		1, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0, 0,
		1, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0,
		1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 0,
		1, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0,
		1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0, 0,
		1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0,
		1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1,
		1, 2, 2, 2, 1, 2, 2, 1, 0, 0, 0, 0,
		1, 2, 2, 1, 1, 2, 2, 1, 0, 0, 0, 0,
		1, 2, 1, 0, 1, 1, 2, 2, 1, 0, 0, 0,
		1, 1, 0, 0, 0, 1, 2, 2, 1, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 2, 2, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0
	};

	CursorMan.replaceCursor(defaultCursor, 12, 20, 0, 0, 0);
	CursorMan.replaceCursorPalette(s_bwPalette, 1, 2);
}

void Gfx::changeCursor(uint id) {
	if (id >= _cursor.size()) {
		warning("Attempted to set invalid cursor id:%d", id);
		return;
	}

	// TODO: Add Code to select PE cursors if present..
	Graphics::WinCursor cur;
	Common::SeekableReadStream* curData = _ne.getResource(Common::kNECursor, _cursor[id]);
	cur.readFromStream(*curData);
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
	CursorMan.replaceCursor(cur.getSurface(), cur.getWidth(), cur.getHeight(), cur.getHotspotX(), cur.getHotspotY(), cur.getKeyColor());
	CursorMan.replaceCursorPalette(cur.getPalette(), 0, 256);
	delete curData;
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

const Common::Rect tileArea(13, 31, 13+(9*32), 31+(9*32));

const Common::Rect InvIcon0(314, 31, 314+32, 31+32);
const Common::Rect InvDesc0(314+35, 31, 314+35+147, 31+32);

// Reference is Apex Of Arrow
const Common::Point UpArrow(347, 274);
const Common::Point DownArrow(347, 316);
const Common::Point LeftArrow(326, 295);
const Common::Point RightArrow(368, 295);

const Common::Rect weaponArea(405, 280, 405+32, 280+32);
const Common::Rect weaponPowerArea(405-16, 280, 405-16+8, 280+32);

const Common::Point health(480, 280+16);

const Common::String strFile("File");
const Common::String strOptions("Options");
const Common::String strWindow("Window");
const Common::String strHelp("Help");

const Common::Rect lFile(5, 5, 5+(6*strFile.size()), 17);
const Common::Rect lOptions(lFile.right+15, lFile.top, lFile.right+15+(6*strOptions.size()), lFile.bottom);
const Common::Rect lWindow(lOptions.right+15, lOptions.top, lOptions.right+15+(6*strWindow.size()), lOptions.bottom);
const Common::Rect lHelp(lWindow.right+15, lWindow.top, lWindow.right+15+(6*strHelp.size()), lWindow.bottom);

void Gfx::drawScreenOutline(void) {
	Common::Rect rect(1, 1, screenWidth-1, screenHeight-1);
	_screen->fillRect(rect, MEDIUM_GREY);
	_screen->hLine(0, 18, screenWidth-1, BLACK);

	// Menu Bar
	_font->drawString(_screen, strFile, lFile.left, lFile.top, lFile.width(), BLACK, Graphics::kTextAlignLeft, 0, false);
	_font->drawString(_screen, strOptions, lOptions.left, lOptions.top, lOptions.width(), BLACK, Graphics::kTextAlignLeft, 0, false);
	_font->drawString(_screen, strWindow, lWindow.left, lWindow.top, lWindow.width(), BLACK, Graphics::kTextAlignLeft, 0, false);
	_font->drawString(_screen, strHelp, lHelp.left, lHelp.top, lHelp.width(), BLACK, Graphics::kTextAlignLeft, 0, false);

	Common::Rect outer(4, 22, screenWidth-4, screenHeight-4);
	drawShadowFrame(&outer, false, false, 3);

	_screen->fillRect(tileArea, BLACK);
	drawShadowFrame(&tileArea, true, false, 3);

	// Inventory
	static const Common::Rect InvOuter(313, 30, 497, 268);
	drawShadowFrame(&InvOuter, true, false, 2);

	Common::Rect InvIcon = InvIcon0;
	for (uint i = 0; i < 7; i++) {
		drawShadowFrame(&InvIcon, false, false, 1);
		InvIcon.translate(0, 34);
	}

	Common::Rect InvDesc = InvDesc0;
	for (uint i = 0; i < 7; i++) {
		drawShadowFrame(&InvDesc, false, false, 1);
		InvDesc.translate(0, 34);
	}

	// Inventory Scroll Bar
	drawShadowFrame(&InvScrollOuter, true, false, 2);

	_screen->fillRect(InvScroll, LIGHT_GREY);

	_screen->fillRect(InvScrUp, MEDIUM_GREY);
	drawShadowFrame(&InvScrUp, false, false, 1);
	_screen->hLine(InvScrUp.left-2, InvScrUp.bottom+1, InvScrUp.right+1, BLACK);
	_screen->vLine(InvScrUp.right+1, InvScrUp.top-2, InvScrUp.bottom, BLACK);
	for (uint i = 0; i < 3; i++)
		_screen->hLine(InvScrUp.left+5-i, InvScrUp.top+3+i, InvScrUp.left+5+i, BLACK);

	_screen->fillRect(InvScrDown, MEDIUM_GREY);
	drawShadowFrame(&InvScrDown, false, false, 1);
	_screen->hLine(InvScrDown.left-2, InvScrDown.bottom+1, InvScrDown.right+1, BLACK);
	_screen->vLine(InvScrDown.right+1, InvScrDown.top-2, InvScrDown.bottom, BLACK);
	for (uint i = 0; i < 3; i++)
		_screen->hLine(InvScrDown.left+5-i, InvScrDown.bottom-4-i, InvScrDown.left+5+i, BLACK);

	InvScrThumb->left = InvScrollOuter.left;
	InvScrThumb->top = InvScrollOuter.top-2+40;
	InvScrThumb->right = InvScrollOuter.right;
	InvScrThumb->bottom = InvScrollOuter.top+1+40+9;
	_screen->fillRect(*InvScrThumb, MEDIUM_GREY);
	InvScrThumb->top += 2;
	InvScrThumb->bottom -= 1;
	InvScrThumb->left += 2;
	InvScrThumb->right -= 2;
	drawShadowFrame(InvScrThumb, false, false, 1);
	_screen->hLine(InvScrThumb->left-2, InvScrThumb->bottom+1, InvScrThumb->right+1, BLACK);
	_screen->vLine(InvScrThumb->right+1, InvScrThumb->top-2, InvScrThumb->bottom, BLACK);

	// Direction Arrows Outline
	// Up Arrow
	_screen->drawLine(UpArrow.x, UpArrow.y, UpArrow.x-7, UpArrow.y+7, ARROW_SHADOW);
	_screen->drawLine(UpArrow.x, UpArrow.y, UpArrow.x+7, UpArrow.y+7, ARROW_SHADOW);

	_screen->drawLine(UpArrow.x-7, UpArrow.y+7, UpArrow.x-7, UpArrow.y+7+2, ARROW_SHADOW);
	_screen->drawLine(UpArrow.x+7, UpArrow.y+7, UpArrow.x+7, UpArrow.y+7+2, ARROW_SHADOW);

	_screen->drawLine(UpArrow.x-7, UpArrow.y+7+2, UpArrow.x-7+4, UpArrow.y+7+2, WHITE);
	_screen->drawLine(UpArrow.x+7, UpArrow.y+7+2, UpArrow.x+7-4, UpArrow.y+7+2, WHITE);

	_screen->drawLine(UpArrow.x-7+4, UpArrow.y+7+2, UpArrow.x-7+4, UpArrow.y+7+2+4, ARROW_SHADOW);
	_screen->drawLine(UpArrow.x+7-4, UpArrow.y+7+2, UpArrow.x+7-4, UpArrow.y+7+2+4, WHITE);

	_screen->drawLine(UpArrow.x-7+4, UpArrow.y+7+2+4, UpArrow.x+7-4, UpArrow.y+7+2+4, WHITE);

	// Down Arrow
	_screen->drawLine(DownArrow.x, DownArrow.y, DownArrow.x-7, DownArrow.y-7, ARROW_SHADOW);
	_screen->drawLine(DownArrow.x, DownArrow.y, DownArrow.x+7, DownArrow.y-7, WHITE);

	_screen->drawLine(DownArrow.x-7, DownArrow.y-7, DownArrow.x-7, DownArrow.y-7-2, ARROW_SHADOW);
	_screen->drawLine(DownArrow.x+7, DownArrow.y-7, DownArrow.x+7, DownArrow.y-7-2, ARROW_SHADOW);

	_screen->drawLine(DownArrow.x-7, DownArrow.y-7-2, DownArrow.x-7+4, DownArrow.y-7-2, ARROW_SHADOW);
	_screen->drawLine(DownArrow.x+7, DownArrow.y-7-2, DownArrow.x+7-4, DownArrow.y-7-2, ARROW_SHADOW);

	_screen->drawLine(DownArrow.x-7+4, DownArrow.y-7-2, DownArrow.x-7+4, DownArrow.y-7-2-4, ARROW_SHADOW);
	_screen->drawLine(DownArrow.x+7-4, DownArrow.y-7-2, DownArrow.x+7-4, DownArrow.y-7-2-4, WHITE);

	_screen->drawLine(DownArrow.x-7+4, DownArrow.y-7-2-4, DownArrow.x+7-4, DownArrow.y-7-2-4, ARROW_SHADOW);

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

	_screen->hLine(health.x-5, health.y, health.x+5, BLACK);
	_screen->vLine(health.x, health.y-5, health.y+5, BLACK);

	drawFilledCircle(_screen, health, 15+2, DARK_GREY);
	drawFilledCircle(_screen, health, 15, GREEN);
}

void Gfx::drawStartup(void) {
	byte *stup = _vm->_resource->getStupData();
	for (uint y = 0; y < 9 * 32; y++) {
		for (uint x = 0; x < 9 * 32; x++) {
			*((byte *)_screen->getBasePtr(tileArea.left+x, tileArea.top+y)) = stup[(y*32*9)+x];
		}
	}
	delete[] stup;
}

void Gfx::drawTile(uint32 ref, uint8 x, uint8 y) {
	if (x > 8) {
		warning("drawTile(ref:%d) x:%d out of range 0 to 8 - clamping", ref, x);
		x = 8;
	}

	if (y > 8) {
		warning("drawTile(ref:%d) y:%d out of range 0 to 8 - clamping", ref, y);
		y = 8;
	}

	drawTileInt(ref, tileArea.left+(x*32), tileArea.top+(y*32), TRANSPARENT);
}

void Gfx::drawWeapon(uint32 ref) {
	drawTileInt(ref, weaponArea.left, weaponArea.top, TRANSPARENT);
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

void Gfx::eraseInventoryItem(uint slot) {
	Common::Rect InvIcon = InvIcon0;
	for (uint i = 0; i < slot; i++)
		InvIcon.translate(0, 34);
	_screen->fillRect(InvIcon, MEDIUM_GREY);

	Common::Rect InvDesc = InvDesc0;
	for (uint i = 0; i < slot; i++)
		InvDesc.translate(0, 34);
	_screen->fillRect(InvDesc, MEDIUM_GREY);
}

void Gfx::drawInventoryItem(uint slot, uint32 iconRef, const char *name) {
	if (slot > 6) {
		warning("Gfx::drawInventoryItem() slot %d out of max range 0 to 6", slot);
		return;
	}

	eraseInventoryItem(slot);
	drawTileInt(iconRef, InvIcon0.left, InvIcon0.top+(slot*34), TRANSPARENT);
	const Common::String n(name);
	_font->drawString(_screen, n, InvDesc0.left+5, InvDesc0.top+(slot*34)+12, InvDesc0.width()-10, BLACK, Graphics::kTextAlignLeft, 0, false);
}

const Common::Rect *Gfx::getInvScrUp(void) {
	return &InvScrUp;
}

const Common::Rect *Gfx::getInvScrDown(void) {
	return &InvScrDown;
}

void Gfx::drawDirectionArrows(bool left, bool up, bool right, bool down) {
	uint colorLeft = MEDIUM_GREY;
	uint colorUp = MEDIUM_GREY;
	uint colorRight = MEDIUM_GREY;
	uint colorDown = MEDIUM_GREY;

	if (left)
		colorLeft = GREEN;
	if (up)
		colorUp = GREEN;
	if (right)
		colorRight = GREEN;
	if (down)
		colorDown = GREEN;

	// Up Arrow
	for (uint i = 0; i < 7; i++)
		_screen->drawLine(UpArrow.x-i, UpArrow.y+1+i, UpArrow.x+i, UpArrow.y+1+i, colorUp);
	_screen->drawLine(UpArrow.x-6, UpArrow.y+1+7, UpArrow.x+6, UpArrow.y+1+7, colorUp);
	for (uint i = 0; i < 4; i++)
		_screen->drawLine(UpArrow.x-7+5, UpArrow.y+1+8+i, UpArrow.x+7-5, UpArrow.y+1+8+i, colorUp);

	// Down Arrow
	for (uint i = 0; i < 7; i++)
		_screen->drawLine(DownArrow.x-i, DownArrow.y-1-i, DownArrow.x+i, DownArrow.y-1-i, colorDown);
	_screen->drawLine(DownArrow.x-6, DownArrow.y-1-7, DownArrow.x+6, DownArrow.y-1-7, colorDown);
	for (uint i = 0; i < 4; i++)
		_screen->drawLine(DownArrow.x-7+5, DownArrow.y-1-8-i, DownArrow.x+7-5, DownArrow.y-1-8-i, colorDown);

	// Left Arrow
	for (uint i = 0; i < 7; i++)
		_screen->drawLine(LeftArrow.x+1+i, LeftArrow.y-i, LeftArrow.x+1+i, LeftArrow.y+i, colorLeft);
	_screen->drawLine(LeftArrow.x+1+7, LeftArrow.y-6, LeftArrow.x+1+7, LeftArrow.y+6, colorLeft);
	for (uint i = 0; i < 4; i++)
		_screen->drawLine(LeftArrow.x+1+8+i, LeftArrow.y-7+5, LeftArrow.x+1+8+i, LeftArrow.y+7-5, colorLeft);

	// Right Arrow
	for (uint i = 0; i < 7; i++)
		_screen->drawLine(RightArrow.x-1-i, RightArrow.y-i, RightArrow.x-1-i, RightArrow.y+i, colorRight);
	_screen->drawLine(RightArrow.x-1-7, RightArrow.y-6, RightArrow.x-1-7, RightArrow.y+6, colorRight);
	for (uint i = 0; i < 4; i++)
		_screen->drawLine(RightArrow.x-1-8-i, RightArrow.y-7+5, RightArrow.x-1-8-i, RightArrow.y+7-5, colorRight);
}

void Gfx::drawHealthMeter(uint level) {
	// TODO
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

void Gfx::drawFrameCircle(Graphics::Surface *target, const Common::Point center, uint radius, uint color) {
	#define setPixel(x, y, color) *((byte *)target->getBasePtr(x, y)) = color;

	// Implementation of "midpoint circle algorithm" also known as "Bresenham's circle algorithm".
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;

	setPixel(center.x, center.y + radius, color);
	setPixel(center.x, center.y - radius, color);
	setPixel(center.x + radius, center.y, color);
	setPixel(center.x - radius, center.y, color);

	while (x < y) {
		// ddF_x == 2 * x + 1;
		// ddF_y == -2 * y;
		// f == x*x + y*y - radius*radius + 2*x - y + 1;
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		setPixel(center.x + x, center.y + y, color);
		setPixel(center.x - x, center.y + y, color);
		setPixel(center.x + x, center.y - y, color);
		setPixel(center.x - x, center.y - y, color);
		setPixel(center.x + y, center.y + x, color);
		setPixel(center.x - y, center.y + x, color);
		setPixel(center.x + y, center.y - x, color);
		setPixel(center.x - y, center.y - x, color);
	}
}

void Gfx::drawFilledCircle(Graphics::Surface *target, const Common::Point center, uint radius, uint color) {
	// Filled Implementation of "midpoint circle algorithm" also known as "Bresenham's circle algorithm".
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;

	target->vLine(center.x, center.y + radius, center.y - radius, color);
	target->hLine(center.x + radius, center.y, center.x - radius, color);

	while (x < y) {
		// ddF_x == 2 * x + 1;
		// ddF_y == -2 * y;
		// f == x*x + y*y - radius*radius + 2*x - y + 1;
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		target->hLine(center.x + x, center.y + y, center.x - x, color);
		target->hLine(center.x + x, center.y - y, center.x - x, color);
		target->hLine(center.x + y, center.y + x, center.x - y, color);
		target->hLine(center.x + y, center.y - x, center.x - y, color);
	}
}

} // End of namespace Deskadv
