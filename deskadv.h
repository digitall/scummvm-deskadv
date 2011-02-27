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
#include "common/debug.h"
#include "common/debug-channels.h"
#include "common/ne_exe.h"

#include "engines/engine.h"
#include "engines/util.h"

#include "deskadv/console.h"
#include "deskadv/graphics.h"
#include "deskadv/sound.h"
#include "deskadv/resource.h"

namespace Deskadv {

struct DeskadvGameDescription;

class DeskadvEngine;
class DeskadvConsole;

enum GameType {
	GType_Indy = 1,
	GType_Yoda = 2
};

// Engine Debug Flags
enum {
	kDebugResource  = (1 << 0),
	kDebugSaveLoad  = (1 << 1),
	kDebugScript    = (1 << 2),
	kDebugText      = (1 << 3),
	kDebugCollision = (1 << 4),
	kDebugGraphics  = (1 << 5),
	kDebugSound     = (1 << 6)
};

class DeskadvEngine : public Engine {
protected:
	Common::Error run();

public:
	DeskadvEngine(OSystem *syst, const DeskadvGameDescription *gameDesc);
	virtual ~DeskadvEngine();

	virtual bool hasFeature(EngineFeature f) const;

	int getGameType() const;
	const char *getGameId() const;
	uint32 getFeatures() const;
	Common::Language getLanguage() const;

	const DeskadvGameDescription *_gameDescription;

	GUI::Debugger *getDebugger() { return _console; }

	Gfx *_gfx;
	Sound *_snd;
	Resource *_resource;

private:
	DeskadvConsole *_console;

	Common::RandomSource *_rnd;

	// TODO: Add Variables For Game State:
	// World Size
	// Combat Difficulty
	// Sound Effects On/Off
	// Music On/Off

	// Current World Data

	// Current Zone
	// Ego Position in Zone
	// Health Level
	// Weapon
	// Inventory Contents
};

} // End of namespace Deskadv

#endif
