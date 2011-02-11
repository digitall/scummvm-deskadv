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

#ifndef DESKADV_H
#define DESKADV_H

#include "common/random.h"
#include "common/system.h"

#include "engines/engine.h"
#include "engines/util.h"

#include "deskadv/console.h"
#include "deskadv/graphics.h"

namespace Deskadv {

struct DeskadvGameDescription;

class DeskadvEngine;
class DeskadvConsole;

// Engine Debug Flags
enum {
	kDebugResource  = (1 << 0),
	kDebugSaveLoad  = (1 << 1),
	kDebugScript    = (1 << 2),
	kDebugText      = (1 << 3),
	kDebugCollision = (1 << 4)
};

class DeskadvEngine : public Engine {
protected:
	Common::Error run();

public:
	DeskadvEngine(OSystem *syst, const DeskadvGameDescription *gameDesc);
	virtual ~DeskadvEngine();

	virtual bool hasFeature(EngineFeature f) const;

	int getGameType() const;
	uint32 getGameID() const;
	uint32 getFeatures() const;
	Common::Language getLanguage() const;
	Common::Platform getPlatform() const;
	const Common::String& getTargetName() const { return _targetName; }

	const DeskadvGameDescription *_gameDescription;

	GUI::Debugger *getDebugger() { return _console; }

	Gfx *_gfx;

private:
	DeskadvConsole *_console;

	Common::RandomSource *_rnd;
};

} // End of namespace Deskadv

#endif
