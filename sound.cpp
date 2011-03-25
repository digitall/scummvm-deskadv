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
#include "deskadv/sound.h"

#include "common/file.h"
#include "common/str.h"

#include "audio/audiostream.h"
#include "audio/decoders/wave.h"

namespace Deskadv {

Sound::Sound(DeskadvEngine *vm) : _vm(vm) {
	MidiDriver::DeviceHandle dev = MidiDriver::detectDevice(MDT_MIDI | MDT_ADLIB | MDT_PREFER_GM);
	_midiDriver = MidiDriver::createMidi(dev);
	_midiDriver->open();
	_midiPlayer = MidiParser::createParser_SMF();
	_midiPlayer->setMidiDriver(_midiDriver);
	_midiPlayer->setTimerRate(_midiDriver->getBaseTempo());
	_midiDriver->setTimerCallback(_midiPlayer, MidiParser::timerCallback);

	_sfxFile = 0;
	_midiData = 0;
}

Sound::~Sound() {
	stopSFX();
	stopMID();

	_midiDriver->setTimerCallback(0, 0);
	_midiDriver->close();
	_midiPlayer->setMidiDriver(0);
	delete _midiDriver;
	delete _midiPlayer;
}

void Sound::playSound(uint32 ref) {
	Common::String filename = lastPathComponent(Common::String(_vm->_resource->getSoundFilename(ref)), '\\');
	filename.toLowercase();

	if (filename.hasSuffix("wav"))
		playSFX(ref);
	else if (filename.hasSuffix("mid"))
		playMID(ref);
	else
		warning("playSound(%d) unrecognised file type \"%s\"", ref, filename.c_str());
}

void Sound::playSFX(uint32 ref) {
	Common::String filename = lastPathComponent(Common::String(_vm->_resource->getSoundFilename(ref)), '\\');

	stopSFX();

	debugC(1, kDebugSound, "playSFX(%d) -> \"%s\"", ref, filename.c_str());

	_sfxFile = new Common::File();
	_sfxFile->open(filename);

	Audio::AudioStream *stream = Audio::makeWAVStream(_sfxFile, DisposeAfterUse::NO);
	_vm->_mixer->playStream(Audio::Mixer::kSFXSoundType, &_SFXSoundHandle, stream);
}

void Sound::playMID(uint32 ref) {
	Common::String filename = lastPathComponent(Common::String(_vm->_resource->getSoundFilename(ref)), '\\');

	stopMID();

	debugC(1, kDebugSound, "playMID(%d) -> \"%s\"", ref, filename.c_str());

	Common::File midiFile;
	midiFile.open(filename);
	uint32 mdSize = midiFile.size();
	debugC(1, kDebugSound, "\tLoading MIDI File Data of size: %d", mdSize);
	_midiData = new byte[mdSize];
	midiFile.read(_midiData, mdSize);
	_midiPlayer->loadMusic(_midiData, mdSize);
	_midiPlayer->setTrack(0);
	midiFile.close();
}

void Sound::stopSFX(void) {
	debugC(1, kDebugSound, "stopSFX()");

	_vm->_mixer->stopHandle(_SFXSoundHandle);

	if (_sfxFile)
		_sfxFile->close();
	delete _sfxFile;
	_sfxFile = 0;
}

void Sound::stopMID(void) {
	debugC(1, kDebugSound, "stopMID()");

	_midiPlayer->stopPlaying();
	_midiPlayer->unloadMusic();

	delete[] _midiData;
	_midiData = 0;
}

} // End of namespace Deskadv
