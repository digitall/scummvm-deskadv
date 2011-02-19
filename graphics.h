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

#ifndef DESKADV_GRAPHICS_H
#define DESKADV_GRAPHICS_H

#include "graphics/surface.h"
#include "common/ne_exe.h"

namespace Deskadv {

class Gfx {
public:
	Gfx(DeskadvEngine *vm);
	virtual ~Gfx(void);

	void updateScreen(void);
	void drawTile(uint32 ref, uint x, uint y);
	void loadNECursors(const char *filename);
	void changeCursor(uint id);
	void loadBMP(const char *filename, uint x, uint y);

	void drawScreenOutline(void);
	void drawWeapon(uint32 ref);
	void drawWeaponPower(uint8 level);
	void drawDirectionArrows(bool left, bool up, bool right, bool down);

	// Debug Routines
	void viewPalette(void);

private:
	DeskadvEngine *_vm;

	Graphics::Surface *_screen;
	Common::NEResources _ne;
	Common::Array<Common::NECursorGroup> _NECursor;

	void drawShadowFrame(const Common::Rect *rect, bool recessed, bool firstInverse, uint thickness);
};

} // End of namespace Deskadv

#endif
