#include "../Header/Config.h"

void cSystemConfig::SetDefault() {
	mConfig.fWindowMode = true;
	mConfig.mDisplayWidth = 640;
	mConfig.mDisplayHeight = 480;
	mConfig.mRotation = eRotation_Horizontal;
}

const sSystemConfig cSystemConfig::GetConfig() {
	return mConfig;
}

int cSystemConfig::Load() {
	std::tstring tFileName;
	tFileName = _T("./config.json");

	std::ifstream tFile;
	tFile.open(tFileName, std::ios::out);

	if (!tFile) {
		return -1;
	}

	picojson::value tInputData;
	tFile >> tInputData;

	mConfig.fWindowMode = tInputData.get<picojson::object>()["Display"].get<picojson::object>()["Window"].get<bool>();
	mConfig.mDisplayWidth = static_cast<unsigned short>(tInputData.get<picojson::object>()["Display"].get<picojson::object>()["ResolutionX"].get<double>());
	mConfig.mDisplayHeight = static_cast<unsigned short>(tInputData.get<picojson::object>()["Display"].get<picojson::object>()["ResolutionY"].get<double>());
	mConfig.mRotation = static_cast<eScreenRotation>(
		static_cast<int>(tInputData.get<picojson::object>()["Display"].get<picojson::object>()["Rotation"].get<double>()) % eRotation_None
		);

	if (mConfig.mDisplayWidth < 480) {
		mConfig.mDisplayWidth = 480;
	}
	if (mConfig.mDisplayHeight < 480) {
		mConfig.mDisplayHeight = 480;
	}

	tFile.close();

	return 0;
}

int cSystemConfig::Write() {
	std::tstring tFileName;
	tFileName = _T("./config.json");

	std::ofstream tFile;
	tFile.open(tFileName, std::ios::trunc);

	if (!tFile) {
		return -1;
	}

	picojson::object tAllObject, tDisplay;

	tDisplay.emplace(std::make_pair("Window", mConfig.fWindowMode));
	tDisplay.emplace(std::make_pair("ResolutionX", static_cast<double>(mConfig.mDisplayWidth)));
	tDisplay.emplace(std::make_pair("ResolutionY", static_cast<double>(mConfig.mDisplayHeight)));
	tDisplay.emplace(std::make_pair("Rotation", static_cast<double>(mConfig.mRotation)));

	tAllObject.emplace(std::make_pair("Display", tDisplay));

	picojson::value tOutputData(tAllObject);

	tFile << tOutputData.serialize(true);

	tFile.close();

	return 0;
}

void cGameConfig::SetDefault() {
	mConfig.mZoomX = 95;
	mConfig.mZoomY = 95;
	mConfig.mPositionX = 0;
	mConfig.mPositionY = 0;
}
const sGameConfig cGameConfig::GetConfig() {
	return mConfig;
}

int cGameConfig::Load() {
	std::tstring tFileName;
	tFileName = _T("./setting.dat");

	std::ifstream tFile;
	tFile.open(tFileName, std::ios::binary);

	if (!tFile) {

		return -1;
	}

	tFile.close();

	return 0;
}

int cGameConfig::Write() {
	std::tstring tFileName;
	tFileName = _T("./setting.dat");

	std::ofstream tFile;
	tFile.open(tFileName, std::ios::binary);

	if (!tFile) {
		return -1;
	}

	tFile.close();

	return 0;
}