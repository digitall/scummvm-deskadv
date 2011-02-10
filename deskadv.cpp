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
#include "common/scummsys.h"
 
#include "common/config-manager.h"
#include "common/debug.h"
#include "common/debug-channels.h"
#include "common/EventRecorder.h"
#include "common/file.h"
#include "common/fs.h"
 
#include "engines/util.h"

#include "deskadv/console.h"
#include "deskadv/deskadv.h"

namespace Deskadv {

DeskadvEngine::DeskadvEngine(OSystem *syst, const DeskadvGameDescription *gameDesc) : Engine(syst), _gameDescription(gameDesc) {
	DebugMan.addDebugChannel(kDebugResource, "Resource", "Resource Debug Flag");
	DebugMan.addDebugChannel(kDebugSaveLoad, "Saveload", "Saveload Debug Flag");
	DebugMan.addDebugChannel(kDebugScript, "Script", "Script Debug Flag");
	DebugMan.addDebugChannel(kDebugText, "Text", "Text Debug Flag");
	DebugMan.addDebugChannel(kDebugCollision, "Collision", "Collision Debug Flag");

	const Common::FSNode gameDataDir(ConfMan.get("path"));
	SearchMan.addSubDirectoryMatching(gameDataDir, "bitmaps");
	SearchMan.addSubDirectoryMatching(gameDataDir, "sfx");

	_rnd = new Common::RandomSource();
	g_eventRec.registerRandomSource(*_rnd, "deskadv");

	_console = 0;

	// TODO: Add Sound Mixer
	// TODO: Add WAV Player for SFX
	// TODO: Add Standard SMF Midi Player for Music
	// TODO: Add BMP Loader for Bitmaps
}

DeskadvEngine::~DeskadvEngine() {
	DebugMan.clearAllDebugChannels();

	delete _rnd;
	delete _console;
}

Common::Error DeskadvEngine::run() {
	//Common::Event event;

	initGraphics(320, 200, false);

	_console = new DeskadvConsole(this);

	while (!shouldQuit()) {
		debug(1, "Main Loop Tick...");
		_system->delayMillis(50);
	}

	return Common::kNoError;
}

} // End of namespace Deskadv
