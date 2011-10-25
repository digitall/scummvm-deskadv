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

#include "base/plugins.h"
#include "engines/advancedDetector.h"

#include "deskadv/deskadv.h"

namespace Deskadv {

struct DeskadvGameDescription {
	ADGameDescription desc;

	int gameType;
};

int DeskadvEngine::getGameType() const {
	return _gameDescription->gameType;
}

const char *DeskadvEngine::getGameId() const {
	return _gameDescription->desc.gameid;
}

uint32 DeskadvEngine::getFeatures() const {
	return _gameDescription->desc.flags;
}

Common::Language DeskadvEngine::getLanguage() const {
	return _gameDescription->desc.language;
}

}

static const PlainGameDescriptor deskadvGames[] = {
	{"indydesk", "Indiana Jones Desktop Adventures"},
	{"yodadesk", "Yoda Stories"},
	{0, 0}
};

namespace Deskadv {

static const DeskadvGameDescription gameDescriptions[] = {

	// Indiana Jones Desktop Adventures - English
	{
		{
			"indydesk",
			0,
			{{"desktop.daw", 0, "173efd0c8aa63f20752445c07d9afd15", -1},
			 {"deskadv.exe", 0, "df36d397f90f19f5daed425403cf9538", -1},
			 AD_LISTEND},
			Common::EN_ANY,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO1(GUIO_NONE)
		},
		GType_Indy
	},

	// Indiana Jones Desktop Adventures (Demo) - English
	{
		{
			"indydesk",
			"Demo",
			{{"desktop.daw", 0, "c30d601f7fabc01cfa9bda154a99edb9", -1},
			 {"deskadv.exe", 0, "2d561e0cfd8b3d9035af2e612e28eba8", -1},
			 AD_LISTEND},
			Common::EN_ANY,
			Common::kPlatformWindows,
			ADGF_DEMO,
			GUIO1(GUIO_NONE)
		},
		GType_Indy
	},

	// Yoda Stories - English
	{
		{
			"yodadesk",
			0,
			{{"yodesk.dta", 0, "1d2afd3a6af3ff71c31582757060427d", -1},
			 {"yodesk.exe", 0, "8c2a17262a9b93e3f8f198dc922e8e67", -1},
			 AD_LISTEND},
			Common::EN_ANY,
			Common::kPlatformWindows,
			ADGF_NO_FLAGS,
			GUIO1(GUIO_NONE)
		},
		GType_Yoda
	},

	// Yoda Stories (Demo) - English
	{
		{
			"yodadesk",
			"Demo",
			{{"yodademo.dta", 0, "1d2afd3a6af3ff71c31582757060427d", -1},
			 {"yodademo.exe", 0, "6298347428cb02cf6a6d923ffc46f8ac", -1},
			 AD_LISTEND},
			Common::EN_ANY,
			Common::kPlatformWindows,
			ADGF_DEMO,
			GUIO1(GUIO_NONE)
		},
		GType_Yoda
	},

	{ AD_TABLE_END_MARKER, 0 }
};

} // End of namespace Deskadv

using namespace Deskadv;

class DeskadvMetaEngine : public AdvancedMetaEngine {
public:
	DeskadvMetaEngine() : AdvancedMetaEngine(Deskadv::gameDescriptions, sizeof(Deskadv::DeskadvGameDescription), deskadvGames) {}

	virtual const char *getName() const {
		return "Desktop Adventures Engine";
	}

	virtual const char *getOriginalCopyright() const {
		return "Lucasarts Desktop Adventures";
	}

	virtual bool createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const;
	virtual bool hasFeature(MetaEngineFeature f) const;
};

bool DeskadvMetaEngine::createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const {
	const Deskadv::DeskadvGameDescription *gd = (const Deskadv::DeskadvGameDescription *)desc;
	if (gd) {
		*engine = new Deskadv::DeskadvEngine(syst, gd);
	}
	return gd != 0;
}

bool DeskadvMetaEngine::hasFeature(MetaEngineFeature f) const {
	return false;
}

bool Deskadv::DeskadvEngine::hasFeature(EngineFeature f) const {
	return (f == kSupportsRTL);
}

#if PLUGIN_ENABLED_DYNAMIC(DESKADV)
REGISTER_PLUGIN_DYNAMIC(DESKADV, PLUGIN_TYPE_ENGINE, DeskadvMetaEngine);
#else
REGISTER_PLUGIN_STATIC(DESKADV, PLUGIN_TYPE_ENGINE, DeskadvMetaEngine);
#endif
