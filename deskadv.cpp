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
#include "common/EventRecorder.h"
#include "common/file.h"
#include "common/fs.h"
#include "common/keyboard.h"

#include "graphics/cursorman.h"
#include "graphics/surface.h"
#include "graphics/pixelformat.h"

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
	DebugMan.addDebugChannel(kDebugGraphics, "Graphics", "Graphics Debug Flag");

	const Common::FSNode gameDataDir(ConfMan.get("path"));
	SearchMan.addSubDirectoryMatching(gameDataDir, "bitmaps");
	SearchMan.addSubDirectoryMatching(gameDataDir, "sfx");

	_rnd = new Common::RandomSource();
	g_eventRec.registerRandomSource(*_rnd, "deskadv");

	_console = 0;
	_gfx = 0;
	_resource = 0;

	// TODO: Add Sound Mixer
	// TODO: Add WAV Player for SFX
	// TODO: Add Standard SMF Midi Player for Music
	// TODO: Add BMP Loader for Bitmaps
}

DeskadvEngine::~DeskadvEngine() {
	DebugMan.clearAllDebugChannels();

	delete _rnd;
	delete _console;

	delete _resource;
	delete _gfx;
}

Common::Error DeskadvEngine::run() {
	Common::Event event;

	_gfx = new Gfx(this);
	_console = new DeskadvConsole(this);
	_resource = new Resource(this);

	switch (getGameType()) {
	case GType_Indy:
		if (!_resource->load("desktop.daw", false))
			error("Loading from DAW Resource File failed!");
		break;
	case GType_Yoda:
		if (!_resource->load("yodesk.dta", true))
			error("Loading from DTA Resource File Failed!");
		break;
	default:
		error("Unknown Game Type for Resource File...");
		break;
	}

	// Load Mouse Cursors
	if (getGameType() == GType_Indy)
		_gfx->loadNECursors("deskadv.exe");
	if (getGameType() == GType_Yoda)
		warning("TODO: PE Loader needed for Yoda Stories Executable");
	CursorMan.showMouse(true);

	while (!shouldQuit()) {
		debug(1, "Main Loop Tick...");

		while (_eventMan->pollEvent(event)) {
			switch (event.type) {
			case Common::EVENT_LBUTTONDOWN:
				break;

			case Common::EVENT_RBUTTONDOWN:
				break;

			case Common::EVENT_MOUSEMOVE:
				break;

			case Common::EVENT_KEYDOWN:
				switch (event.kbd.keycode) {
				case Common::KEYCODE_d:
					if (event.kbd.hasFlags(Common::KBD_CTRL)) {
						// Start the debugger
						getDebugger()->attach();
						getDebugger()->onFrame();
					}
					break;

				case Common::KEYCODE_ESCAPE:
					quitGame();
					break;

				default:
					break;
				}
				break;

			case Common::EVENT_QUIT:
			case Common::EVENT_RTL:
				quitGame();
				break;

			default:
				break;
			}
		}

		_system->delayMillis(50);
	}

	return Common::kNoError;
}

} // End of namespace Deskadv
