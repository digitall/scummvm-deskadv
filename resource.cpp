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

	char tag[5];
	tag[4] = 0;

	while(!_vm->shouldQuit()) {
		_file->read(tag, 4);

		// TODO: Missing Blocks in all resource file types
		// unknown tag STUP, size 82944

		// TODO: Missing Blocks in Indy DAW resource file
		// unknown tag ZAUX, size 15040
		// unknown tag ZAX2, size 9506
		// unknown tag ZAX3, size 4086
		// unknown tag ZAX4, size 3660
		// unknown tag HTSP, size 12138
		// unknown tag ACTN, size 370217
		//
		// unknown tag PUZ2, size 36744
		// unknown tag CHAR, size 2108
		// unknown tag CHWP, size 164
		// unknown tag CAUX, size 110

		// TODO: Missing Blocks in Yoda DTA resource file
		// Skipping unknown tag PUZ2, size 38834
		// Skipping unknown tag CHAR, size 6470
		// Skipping unknown tag CHWP, size 464
		// Skipping unknown tag CAUX, size 310

		if (tag == Common::String("VERS")) {
			uint32 version = _file->readUint32LE();
			debugC(1, kDebugResource, "Found VERS Tag - Version: %d", version);
			if (version != 0x200)
				warning("Unsupported Version");
		} else if (tag == Common::String("ENDF")) {
			break;
		} else if (tag == Common::String("SNDS")) {
			uint32 size = _file->readUint32LE();
			int16 count = -(_file->readSint16LE());
			debugC(1, kDebugResource, "Found %s tag, size %d, %d sounds", tag, size, count);
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
		} else if (tag == Common::String("TNAM")) {
			uint32 size = _file->readUint32LE();
			debugC(1, kDebugResource, "Found %s tag, size %d", tag, size);
			while (!_vm->shouldQuit()) {
				Common::String name;
				uint16 len;
				uint16 id = _file->readUint16LE();
				if (isYoda)
					len = 24;
				else
					len = 16;
				if (id == 0xffff)
					break;
				for (uint16 i = 0; i < len; i++)
					name += _file->readByte();
				debugC(1, kDebugResource, "item id %04x (%d) is \"%s\"", id, id, name.c_str());
			}
		} else if (tag == Common::String("TILE")) {
			uint32 size = _file->readUint32LE();
			_tileCount = size / 1028;
			assert (_tileCount*1028 == size);
			debugC(1, kDebugResource, "Found %s tag, size %d, %d tiles", tag, size, _tileCount);
			_tileDataOffset = _file->pos();
			for (uint32 i = 0; i < _tileCount; i++) {
				uint16 unknown1 = _file->readUint16LE();
				uint16 unknown2 = _file->readUint16LE();
				debugC(1, kDebugResource, "Tile #%d (%d, %d)", i, unknown1, unknown2);
				_file->seek(32 * 32, SEEK_CUR);
			}
		} else if (tag == Common::String("ZONE")) {
			if (!isYoda) {
				uint32 size = _file->readUint32LE();
				debugC(1, kDebugResource, "size: %d", size);
			}
			uint16 zoneCount = _file->readUint16LE();
			debugC(1, kDebugResource, "ZONE tag: %d zones", zoneCount);
			for (uint16 i = 0; i < zoneCount; i++) {
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
				_file->read(tag, 4);
				uint32 size = _file->readUint32LE();
				assert (tag == Common::String("IZON"));
				debugC(1, kDebugResource, "%s: size: %d", tag, size);
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

				// tiles
				for (uint16 j = 0; j < width; j++) {
					for (uint16 k = 0; k < height; k++) {
						uint16 u1 = _file->readUint16LE();
						uint16 u2 = _file->readUint16LE();
						uint16 u3 = _file->readUint16LE();
						debugC(1, kDebugResource, "(tile: %04x, %04x, %04x)", u1, u2, u3);
					}
					debugCN(1, kDebugResource, "\n");
				}

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
				_file->read(tag, 4);
				assert (tag == Common::String("IZAX"));
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
				_file->read(tag, 4);
				assert (tag == Common::String("IZX2"));
				uint32 ignored3 = _file->readUint32LE();
				uint16 izx2Count = _file->readUint16LE();
				debugC(1, kDebugResource, " IZX2: unknown %08x, count %d", ignored3, izx2Count);
				for (uint16 j = 0; j < izx2Count; j++) {
					// TODO
					int16 u1 = _file->readUint16LE();
					debugC(1, kDebugResource, "  IZX2 data: %04x", u1);
				}

				// IZX3
				_file->read(tag, 4);
				assert (tag == Common::String("IZX3"));
				uint32 ignored4 = _file->readUint32LE();
				uint16 izx3Count = _file->readUint16LE();
				debugC(1, kDebugResource, " IZX3: unknown %08x, count %d", ignored4, izx3Count);
				for (uint16 j = 0; j < izx3Count; j++) {
					// TODO
					uint16 u1 = _file->readUint16LE();
					debugC(1, kDebugResource, "  IZX3 data: %04x", u1);
				}

				// IZX4
				_file->read(tag, 4);
				assert (tag == Common::String("IZX4"));
				uint32 ignored5 = _file->readUint32LE();
				uint16 izx4Count = _file->readUint16LE();
				debugC(1, kDebugResource, " IZX4: unknown %08x, unknown %d", ignored5, izx4Count);

				// IACT entries
				uint16 iactCount = _file->readUint16LE();
				debugC(1, kDebugResource, " IACT count: %d", iactCount);
				for (uint16 j = 0; j < iactCount; j++) {
					_file->read(tag, 4);
					assert (tag == Common::String("IACT"));
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
			debugC(1, kDebugResource, "Skipping unknown tag %s, size %d", tag, size);
			for (uint32 i = 0; i < size; i++)
				_file->readByte();
		}
	}

	return true;
}

byte *Resource::getTileData(uint32 ref) {
	byte *data = new byte[32 * 32];
	_file->seek(_tileDataOffset + (ref * ((32 * 32) + 4)) + 4, SEEK_SET);
	_file->read(data, 32 * 32);
	return data;
}

const char *Resource::getSoundFilename(uint16 ref) {
	if (ref >= _soundFiles.size()) {
		warning("Sound::getSoundFilename(%d) ref is out of range", ref);
		return 0;
	}

	return _soundFiles[ref].c_str();
}

} // End of namespace Deskadv
