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

#include "common/file.h"

#include "deskadv/deskadv.h"
#include "deskadv/resource.h"

namespace Deskadv {

Resource::Resource(DeskadvEngine *vm) : _vm(vm) {
	_file = 0;
	_tileCount = 0;
	_tileDataOffset = 0;
}

Resource::~Resource() {
	while(!_zones.empty()) {
		ZONE *temp = &_zones.back();
		delete[] temp->tiles[0];
		delete[] temp->tiles[1];
		delete[] temp->tiles[2];
		_zones.pop_back();
	}

	if (_file)
		_file->close();
	delete _file;
}

bool Resource::load(const char *filename, bool isYoda) {
	// isYoda boolean switches between Indy DAW format and Yoda DTA format

	// Multiple calls of load not supported.
	assert(_file == 0);

	_file = new Common::File();
	if (!_file->open(filename))
		return false;

	uint32 tag;

	while(!_vm->shouldQuit()) {
		tag = _file->readUint32BE();

		// TODO: Missing Blocks in Indy DAW resource file
		// unknown tag ZAUX, size 15040
		// unknown tag ZAX2, size 9506
		// unknown tag ZAX3, size 4086
		// unknown tag ZAX4, size 3660
		// unknown tag HTSP, size 12138
		// unknown tag ACTN, size 370217
		//
		// unknown tag CHAR, size 2108
		// unknown tag CHWP, size 164
		// unknown tag CAUX, size 110

		// TODO: Missing Blocks in Yoda DTA resource file
		// Skipping unknown tag CHAR, size 6470
		// Skipping unknown tag CHWP, size 464
		// Skipping unknown tag CAUX, size 310

		if (tag == MKTAG('V','E','R','S')) { // Version
			uint32 version = _file->readUint32LE();
			debugC(1, kDebugResource, "Found VERS Tag - Version: %d", version);
			if (version != 0x200)
				warning("Unsupported Version");
		} else if (tag == MKTAG('E','N','D','F')) { // End of File
			break;
		} else if (tag == MKTAG('S','T','U','P')) {
			uint32 size = _file->readUint32LE();
			debugC(1, kDebugResource, "Found %s tag, size %d", tag2str(tag), size);
			assert (size == 32*32*9*9);
			_stupOffset = _file->pos();
			_file->seek(size, SEEK_CUR);
		} else if (tag == MKTAG('S','N','D','S')) { // Sound List
			uint32 size = _file->readUint32LE();
			int16 count = -(_file->readSint16LE());
			debugC(1, kDebugResource, "Found %s tag, size %d, %d sounds", tag2str(tag), size, count);
			size -= 2;
			for (int16 i = 0; i < count; i++) {
				uint16 strsize = _file->readUint16LE();
				size -= (2 + strsize);
				Common::String strname;
				char c;
				while ((c = _file->readByte()) != 0)
					strname += c;
				if (strsize != strname.size() + 1)
					warning("String Length Mismatch");
				debugC(1, kDebugResource, "sound \"%s\"", strname.c_str());
				_soundFiles.push_back(strname);
			}
			assert (size == 0);
		} else if (tag == MKTAG('A','N','A','M')) { // Action Names
			uint32 size = _file->readUint32LE();
			debugC(1, kDebugResource, "Found %s tag, size %d", tag2str(tag), size);
			while (!_vm->shouldQuit()) {
				uint16 zoneid = _file->readUint16LE();
				if (zoneid == 0xffff)
					break;
				debugC(1, kDebugResource, "entry for zone %04x (%d)", zoneid, zoneid);
				while (!_vm->shouldQuit()) {
					uint16 id = _file->readUint16LE();
					if (id == 0xffff)
						break;
					Common::String name;
					uint16 len;
					if (isYoda)
						len = 24;
					else
						len = 16;
					for (uint16 i = 0; i < len; i++)
						name += _file->readByte();
					name = name.c_str(); // Drop extra trailing nulls
					debugC(1, kDebugResource, "entry id %04x (%d) is \"%s\"", id, id, name.c_str());
				}
			}
		} else if (tag == MKTAG('P','N','A','M')) { // Procedure Names
			uint32 size = _file->readUint32LE();
			debugC(1, kDebugResource, "Found %s tag, size %d", tag2str(tag), size);
			uint16 count = _file->readUint16LE();
			for (uint i = 0; i < count; i++) {
				Common::String name;
				for (uint16 j = 0; j < 16; j++)
					name += _file->readByte();
				name = name.c_str(); // Drop extra trailing nulls
				debugC(1, kDebugResource, "entry %04x (%d) is \"%s\"", i, i, name.c_str());
			}
		} else if (tag == MKTAG('T','N','A','M')) { // Tile Names
			uint32 size = _file->readUint32LE();
			debugC(1, kDebugResource, "Found %s tag, size %d", tag2str(tag), size);
			while (!_vm->shouldQuit()) {
				TNAME t;
				t.id = _file->readUint16LE();
				if (t.id == 0xffff)
					break;
				uint16 len;
				if (isYoda)
					len = 24;
				else
					len = 16;
				for (uint16 i = 0; i < len; i++)
					t.name += _file->readByte();
				t.name = t.name.c_str(); // Drop extra trailing nulls
				debugC(1, kDebugResource, "entry id %04x (%d) is \"%s\"", t.id, t.id, t.name.c_str());
				_tileNames.push_back(t);
			}
		} else if (tag == MKTAG('Z','N','A','M')) { // Zone Names
			uint32 size = _file->readUint32LE();
			debugC(1, kDebugResource, "Found %s tag, size %d", tag2str(tag), size);
			while (!_vm->shouldQuit()) {
				uint16 id = _file->readUint16LE();
				if (id == 0xffff)
					break;
				Common::String name;
				uint16 len;
				if (isYoda)
					len = 24;
				else
					len = 16;
				for (uint16 i = 0; i < len; i++)
					name += _file->readByte();
				name = name.c_str(); // Drop extra trailing nulls
				debugC(1, kDebugResource, "entry id %04x (%d) is \"%s\"", id, id, name.c_str());
			}
		} else if (tag == MKTAG('P','U','Z','2')) {
			uint32 size = _file->readUint32LE();
			debugC(1, kDebugResource, "Found %s tag, size %d", tag2str(tag), size);
			while (!_vm->shouldQuit()) {
				uint16 puzid = _file->readUint16LE();
				if (puzid == 0xffff)
					break;
				tag = _file->readUint32BE();
				assert (tag == MKTAG('I','P','U','Z'));
				uint32 ipuzSize = _file->readUint32LE();
				uint32 u1 = _file->readUint32LE();
				uint32 u2 = _file->readUint32LE();
				uint32 u3 = 0;
				if (isYoda)
					u3 = _file->readUint32LE();
				uint16 u4 = _file->readUint16LE();
				debugC(1, kDebugResource, "puz id %d (0x%04x) size %d, unknowns %08x, %08x, %08x, %04x", puzid, puzid, ipuzSize, u1, u2, u3, u4);
				for (uint i = 0; i < 5; i++) {
					uint16 strlen = _file->readUint16LE();
					Common::String str;
					for (uint16 j = 0; j < strlen; j++)
						str += _file->readByte();
					debugC(1, kDebugResource, " IPUZ string%d: \"%s\"", i, str.c_str());
				}
				uint16 u5 = _file->readUint16LE();
				uint16 u6 = 0;
				if (isYoda)
					u6 = _file->readUint16LE();
				debugC(1, kDebugResource, " IPUZ unknowns %04x, %04x", u5, u6);
			}
		} else if (tag == MKTAG('T','I','L','E')) { // Tile Data
			uint32 size = _file->readUint32LE();
			_tileCount = size / 1028;
			assert (_tileCount*1028 == size);
			debugC(1, kDebugResource, "Found %s tag, size %d, %d tiles", tag2str(tag), size, _tileCount);
			_tileDataOffset = _file->pos();
			for (uint32 i = 0; i < _tileCount; i++) {
				uint16 unknown1 = _file->readUint16LE();
				uint16 unknown2 = _file->readUint16LE();
				debugC(1, kDebugResource, "Tile #%d (%d, %d)", i, unknown1, unknown2);
				_file->seek(32 * 32, SEEK_CUR);
			}
		} else if (tag == MKTAG('Z','O','N','E')) { // Zone Data
			if (!isYoda) {
				uint32 size = _file->readUint32LE();
				debugC(1, kDebugResource, "size: %d", size);
			}
			_zoneCount = _file->readUint16LE();
			debugC(1, kDebugResource, "ZONE tag: %d zones", _zoneCount);
			for (uint16 i = 0; i < _zoneCount; i++) {
				debugCN(1, kDebugResource, "\n");

				// Zone Header
				if (isYoda) {
					uint16 unknown1 = _file->readUint16LE();
					uint32 size = _file->readUint32LE();
					uint16 zone_id = _file->readUint16LE();
					assert (zone_id == i);
					debugC(1, kDebugResource, "zone entry #%04x (%d): unknowns %04x, size %d", zone_id, zone_id, unknown1, size);
				}

				// IZON
				tag = _file->readUint32BE();
				uint32 size = _file->readUint32LE();
				assert (tag == MKTAG('I','Z','O','N'));
				debugC(1, kDebugResource, "%s: size: %d", tag2str(tag), size);
				uint16 width = _file->readUint16LE();
				uint16 height = _file->readUint16LE();
				uint32 izon_unknown1 = _file->readUint32LE();
				uint16 izon_unknown2 = 0;
				uint16 izon_unknown3 = 0;
				if (isYoda) {
					izon_unknown2 = _file->readUint16LE();
					izon_unknown3 = _file->readUint16LE();
				}
				debugC(1, kDebugResource, " %dx%d entries, unknowns %08x, %04x, %04x", width, height, izon_unknown1, izon_unknown2, izon_unknown3);

				ZONE z;
				z.width = width;
				z.height = height;
				z.tiles[0] = new uint16[width*height];
				z.tiles[1] = new uint16[width*height];
				z.tiles[2] = new uint16[width*height];

				// tiles
				for (uint16 j = 0; j < height; j++) {
					for (uint16 k = 0; k < width; k++) {
						uint16 u1 = _file->readUint16LE();
						uint16 u2 = _file->readUint16LE();
						uint16 u3 = _file->readUint16LE();
						debugC(1, kDebugResource, "(tile: %04x, %04x, %04x)", u1, u2, u3);
						z.tiles[0][(j*width)+k] = u1;
						z.tiles[1][(j*width)+k] = u2;
						z.tiles[2][(j*width)+k] = u3;
					}
					debugCN(1, kDebugResource, "\n");
				}
				_zones.push_back(z);

				if (!isYoda)
					continue;

				uint16 count2 = _file->readUint16LE();
				debugC(1, kDebugResource, "zone count2 %d", count2);
				for (uint16 j = 0; j < count2; j++) {
					// TODO
					uint32 type = _file->readUint32LE();
					assert (type < 16);
					const uint8 typetypes[16] = {0, 0, 0, 1, 1, 2, 3, 3, 3, 4, 7, 7, 5, 7, 6, 6};
					uint16 u1 = _file->readUint16LE();
					uint16 u2 = _file->readUint16LE();
					uint16 u3 = _file->readUint16LE();
					uint16 unknown = _file->readUint16LE();
					debugC(1, kDebugResource, " zone count2 data: type %08x (%d), unknowns %04x, %04x, %04x, unknown data %04x", type, typetypes[type], u1, u2, u3, unknown);
				}

				// IZAX
				tag = _file->readUint32BE();
				assert (tag == MKTAG('I','Z','A','X'));
				uint32 ignored1 = _file->readUint32LE();
				uint16 ignored2 = _file->readUint16LE();
				debugC(1, kDebugResource, "IZAX: useless unknowns %08x, %04x", ignored1, ignored2);

				uint16 izaxCount1 = _file->readUint16LE();
				debugC(1, kDebugResource, " IZAX count1 %d", izaxCount1);
				for (uint16 j = 0; j < izaxCount1; j++) {
					// TODO
					uint16 u1 = _file->readUint16LE();
					uint16 u2 = _file->readUint16LE();
					uint16 u3 = _file->readUint16LE();
					uint16 u4 = _file->readUint16LE();
					uint32 u5 = _file->readUint32LE();
					uint8 u6[32];
					_file->read(u6, 32);
					debugC(1, kDebugResource, "  IZAX count1 data: %04x, %04x, %04x, %04x, %08x", u1, u2, u3, u4, u5);
					debugCN(1, kDebugResource, "  IZAX count1 data:");
					for(uint8 k = 0; k < 32; k++)
						debugCN(1, kDebugResource, "%02x", u6[k]);
					debugCN(1, kDebugResource, "\n");
				}

				uint16 izaxCount2 = _file->readUint16LE();
				debugC(1, kDebugResource, " IZAX count2 %d", izaxCount2);
				for (uint16 j = 0; j < izaxCount2; j++) {
					// TODO
					uint16 u1 = _file->readUint16LE();
					debugC(1, kDebugResource, "  IZAX count2 data: %04x", u1);
				}

				uint16 izaxCount3 = _file->readUint16LE();
				debugC(1, kDebugResource, " IZAX count3 %d", izaxCount3);
				for (uint16 j = 0; j < izaxCount3; j++) {
					// TODO
					uint16 u1 = _file->readUint16LE();
					debugC(1, kDebugResource, "  IAZX count3 data: %04x", u1);
				}

				// IZX2
				tag = _file->readUint32BE();
				assert (tag == MKTAG('I','Z','X','2'));
				uint32 ignored3 = _file->readUint32LE();
				uint16 izx2Count = _file->readUint16LE();
				debugC(1, kDebugResource, " IZX2: unknown %08x, count %d", ignored3, izx2Count);
				for (uint16 j = 0; j < izx2Count; j++) {
					// TODO
					int16 u1 = _file->readUint16LE();
					debugC(1, kDebugResource, "  IZX2 data: %04x", u1);
				}

				// IZX3
				tag = _file->readUint32BE();
				assert (tag == MKTAG('I','Z','X','3'));
				uint32 ignored4 = _file->readUint32LE();
				uint16 izx3Count = _file->readUint16LE();
				debugC(1, kDebugResource, " IZX3: unknown %08x, count %d", ignored4, izx3Count);
				for (uint16 j = 0; j < izx3Count; j++) {
					// TODO
					uint16 u1 = _file->readUint16LE();
					debugC(1, kDebugResource, "  IZX3 data: %04x", u1);
				}

				// IZX4
				tag = _file->readUint32BE();
				assert (tag == MKTAG('I','Z','X','4'));
				uint32 ignored5 = _file->readUint32LE();
				uint16 izx4Count = _file->readUint16LE();
				debugC(1, kDebugResource, " IZX4: unknown %08x, unknown %d", ignored5, izx4Count);

				// IACT entries
				uint16 iactCount = _file->readUint16LE();
				debugC(1, kDebugResource, " IACT count: %d", iactCount);
				for (uint16 j = 0; j < iactCount; j++) {
					tag = _file->readUint32BE();
					assert (tag == MKTAG('I','A','C','T'));
					uint32 ignored6 = _file->readUint32LE();
					uint16 iactItemCount1 = _file->readUint16LE();
					debugC(1, kDebugResource, "  IACT: unknown %08x, count1 %d", ignored6, iactItemCount1);
					for (uint16 k = 0; k < iactItemCount1; k++) {
						uint16 u1 = _file->readUint16LE();
						uint16 u2 = _file->readUint16LE();
						uint16 u3 = _file->readUint16LE();
						uint16 u4 = _file->readUint16LE();
						uint16 u5 = _file->readUint16LE();
						uint16 u6 = _file->readUint16LE();
						uint16 u7 = _file->readUint16LE();
						debugC(1, kDebugResource, "   IACT count1 data: %04x, %04x, %04x, %04x, %04x, %04x, %04x", u1, u2, u3, u4, u5, u6, u7);
					}
					uint16 iactItemCount2 = _file->readUint16LE();
					debugC(1, kDebugResource, "  IACT: count2 %d", iactItemCount2);
					for(uint16 k = 0; k < iactItemCount2; k++) {
						uint16 u1 = _file->readUint16LE();
						uint16 u2 = _file->readUint16LE();
						uint16 u3 = _file->readUint16LE();
						uint16 u4 = _file->readUint16LE();
						uint16 u5 = _file->readUint16LE();
						uint16 u6 = _file->readUint16LE();
						debugC(1, kDebugResource, "   IACT count2 data: %04x, %04x, %04x, %04x, %04x, %04x", u1, u2, u3, u4, u5, u6);
						uint16 strlen = _file->readUint16LE();
						if (strlen) {
							Common::String str;
							for (uint16 l = 0; l < strlen; l++)
								str += _file->readByte();
							debugC(1, kDebugResource, "    IACT count2 string: \"%s\"", str.c_str());
						} else
							debugC(1, kDebugResource, "    IACT count2 string: none");
					}
				}
			}
		} else {
			uint32 size = _file->readUint32LE();
			debugC(1, kDebugResource, "Skipping unknown tag %s, size %d", tag2str(tag), size);
			for (uint32 i = 0; i < size; i++)
				_file->readByte();
		}
	}

	return true;
}

ZONE *Resource::getZone(uint num) {
	if (num >= _zones.size()) {
		warning("Resource::getZone(%d) ref is out of range", num);
		return 0;
	}

	return &_zones[num];
}

byte *Resource::getStupData(void) {
	byte *data = new byte[32 * 32 * 9 * 9];
	_file->seek(_stupOffset, SEEK_SET);
	_file->read(data, 32 * 32 * 9 * 9);
	return data;
}

byte *Resource::getTileData(uint32 ref) {
	if (ref >= _tileCount) {
		warning("Resource::getTileData(%d) ref is out of range", ref);
		return 0;
	}

	byte *data = new byte[32 * 32];
	_file->seek(_tileDataOffset + (ref * ((32 * 32) + 4)) + 4, SEEK_SET);
	_file->read(data, 32 * 32);
	return data;
}

uint16 Resource::getTileFlags(uint32 ref, bool upperField) {
	if (ref >= _tileCount) {
		warning("Resource::getTileFlags(%d) ref is out of range", ref);
		return 0;
	}

	_file->seek(_tileDataOffset + (ref * ((32 * 32) + 4)) + (upperField ? 2 : 0), SEEK_SET);
	return _file->readUint16LE();
}

const char *Resource::getTileName(uint32 ref) {
	if (ref >= _tileCount) {
		warning("Resource::getTileName(%d) ref is out of range", ref);
		return 0;
	}

	for (uint32 i = 0; i < _tileNames.size(); i++) {
		if (ref == _tileNames[i].id)
			return _tileNames[i].name.c_str();
	}
	// Tile Name not found.
	return 0;
}

const char *Resource::getSoundFilename(uint16 ref) {
	if (ref >= _soundFiles.size()) {
		warning("Resource::getSoundFilename(%d) ref is out of range", ref);
		return 0;
	}

	return _soundFiles[ref].c_str();
}

} // End of namespace Deskadv
