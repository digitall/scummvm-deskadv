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

#ifndef DESKADV_RESOURCE_H
#define DESKADV_RESOURCE_H

#include "common/file.h"

namespace Deskadv {

class DeskadvEngine;

typedef struct tname {
	uint16 id;
	Common::String name;
} TNAME;

typedef struct zone {
	uint16 width;
	uint16 height;
	uint16 *tiles[3];
} ZONE;

// Tile Flag Masks
#define TILE_LOWER_USE_TRANSPARENCY 0x0001

class Resource {
public:
	Resource(DeskadvEngine *vm);
	virtual ~Resource(void);

	bool load(const char *filename, bool isYoda);

	byte *getStupData(void);

	uint32 getTileCount(void) { return _tileCount; }
	byte *getTileData(uint32 ref);
	uint16 getTileFlags(uint32 ref, bool upperField);
	const char *getTileName(uint32 ref);

	uint16 getZoneCount(void) { return _zoneCount; }
	ZONE *getZone(uint num);

	uint16 getSoundCount(void) { return _soundFiles.size(); }
	const char *getSoundFilename(uint16 ref);

private:
	DeskadvEngine *_vm;

	Common::File *_file;

	uint32 _stupOffset;

	uint32 _tileCount;
	uint32 _tileDataOffset;
	Common::Array<TNAME> _tileNames;

	uint16 _zoneCount;
	Common::Array<ZONE> _zones;

	Common::Array<Common::String> _soundFiles;
};

} // End of namespace Deskadv

#endif
