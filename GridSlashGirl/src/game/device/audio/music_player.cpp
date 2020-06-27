#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "music_player.h"
#include "utils/string_util.h"
#include "DxLib.h"

namespace game::audio
{
	void MusicPlayer::setPlayMusicVolume(int playMusicHandle, float playMusicVolume, float playMusicDistance) const
	{
		float volume
			= (volumeAttenuationCoefficient_ > 0.f && playMusicDistance > 0.f)
			? playMusicVolume / std::powf(playMusicDistance * volumeAttenuationCoefficient_ + 1.f, 2.f)
			: playMusicVolume;
		int volumePal = static_cast<int>(std::roundf(masterVolume_ * volume));
		ChangeVolumeSoundMem(std::clamp<int>(volumePal, 0, 255), playMusicHandle);
	}

	void MusicPlayer::updateAllPlayMusicVolume() const
	{
		for (const auto& itrPlay : playMusicHandleToVolumeAndDistance_)
		{
			setPlayMusicVolume(itrPlay.first, itrPlay.second.volume, itrPlay.second.distance);
		}
	}

	MusicPlayer::MusicPlayer()
		: masterVolume_(1.f),
		  volumeAttenuationCoefficient_(-1.f)
	{}

	MusicPlayer::~MusicPlayer()
	{
		InitSoundMem();
	}

	void MusicPlayer::loadMusicNameToPathDatabase(const std::string& databaseFilePath, bool passFirstLine)
	{
		loadMusicNameToPath_.clear();

		std::ifstream ifs(databaseFilePath);
		std::string line;
		if (passFirstLine) std::getline(ifs, line); // àÍçsñ⁄ÇÕîÚÇŒÇ∑
		while (std::getline(ifs, line))
		{
			std::vector<std::string> strVec = util::split(line, ',');
			if (strVec.size() >= 2) loadMusicNameToPath_[strVec[0]] = strVec[1];
		}
	}

	void MusicPlayer::loadMusic(const std::string& loadMusicName)
	{
		auto itrLoad = loadMusicNameToPath_.find(loadMusicName);
		if (itrLoad != loadMusicNameToPath_.end())
		{
			loadMusic(loadMusicName, itrLoad->second);
		}
	}

	void MusicPlayer::loadMusic(const std::string& loadMusicName, const std::string& loadMusicFilePath)
	{
		auto itrLoad = loadMusicNameToHandle_.find(loadMusicName);
		if (itrLoad == loadMusicNameToHandle_.end())
		{
			int loadMusicHandle = LoadSoundMem(loadMusicFilePath.c_str());
			if (loadMusicHandle != -1)
			{
				loadMusicNameToHandle_[loadMusicName] = loadMusicHandle;
			}
		}
	}

	void MusicPlayer::deleteMusic(const std::string& loadMusicName)
	{
		auto itrLoad = loadMusicNameToHandle_.find(loadMusicName);
		if (itrLoad != loadMusicNameToHandle_.end())
		{
			DeleteSoundMem(itrLoad->second);
			loadMusicNameToHandle_.erase(itrLoad);
		}
	}

	void MusicPlayer::playSE(const std::string& loadMusicName, float playMusicVolume, float playMusicDistance) const
	{
		auto itrLoad = loadMusicNameToHandle_.find(loadMusicName);
		if (itrLoad != loadMusicNameToHandle_.end())
		{
			int playMusicHandle = DuplicateSoundMem(itrLoad->second);
			if (playMusicHandle != -1)
			{
				SetPlayFinishDeleteSoundMem(TRUE, playMusicHandle);
				setPlayMusicVolume(playMusicHandle, playMusicVolume, playMusicDistance);
				PlaySoundMem(playMusicHandle, DX_PLAYTYPE_BACK, FALSE);
			}
		}
	}

	int MusicPlayer::playMusic(const std::string& loadMusicName, float playMusicVolume, float playMusicDistance, bool isLoop, bool topPositionFlag)
	{
		auto itrLoad = loadMusicNameToHandle_.find(loadMusicName);
		if (itrLoad != loadMusicNameToHandle_.end())
		{
			int playMusicHandle = DuplicateSoundMem(itrLoad->second);
			if (playMusicHandle != -1)
			{
				playMusicHandleToVolumeAndDistance_[playMusicHandle] = MusicVolumeAndDistance{ playMusicVolume, playMusicDistance };
				setPlayMusicVolume(playMusicHandle, playMusicVolume, playMusicDistance);
				PlaySoundMem(
					playMusicHandle,
					isLoop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK,
					topPositionFlag
				);
			}
			return playMusicHandle;
		}
		else return -1;
	}

	void MusicPlayer::stopMusic(int* const playMusicHandle)
	{
		if (playMusicHandle)
		{
			auto itrPlay = playMusicHandleToVolumeAndDistance_.find(*playMusicHandle);
			if (itrPlay != playMusicHandleToVolumeAndDistance_.end())
			{
				StopSoundMem(itrPlay->first);
				DeleteSoundMem(itrPlay->first);
				playMusicHandleToVolumeAndDistance_.erase(itrPlay);
			}
			*playMusicHandle = -1;
		}
	}

	void MusicPlayer::deleteAllMusic()
	{
		for (const auto& itrLoad : loadMusicNameToHandle_)
		{
			DeleteSoundMem(itrLoad.second);
		}
		loadMusicNameToHandle_.clear();
	}

	void MusicPlayer::setPlayMusicVolume(int playMusicHandle, float playMusicVolume)
	{
		auto itrPlay = playMusicHandleToVolumeAndDistance_.find(playMusicHandle);
		if (itrPlay != playMusicHandleToVolumeAndDistance_.end())
		{
			itrPlay->second.volume = playMusicVolume;
			setPlayMusicVolume(itrPlay->first, playMusicVolume, itrPlay->second.distance);
		}
	}

	void MusicPlayer::setPlayMusicDistance(int playMusicHandle, float playMusicDistance)
	{
		auto itrPlay = playMusicHandleToVolumeAndDistance_.find(playMusicHandle);
		if (itrPlay != playMusicHandleToVolumeAndDistance_.end())
		{
			itrPlay->second.distance = playMusicDistance;
			setPlayMusicVolume(itrPlay->first, itrPlay->second.volume, playMusicDistance);
		}
	}

	void MusicPlayer::setMasterVolume(float masterVolume)
	{
		masterVolume_ = std::clamp<float>(masterVolume, 0.f, 1.f);
		updateAllPlayMusicVolume();
	}

	float MusicPlayer::getMasterVolume() const
	{
		return masterVolume_;
	}

	void MusicPlayer::setVolumeAttenuationCoefficient(float volumeAttenuationCoefficient)
	{
		volumeAttenuationCoefficient_ = volumeAttenuationCoefficient;
		updateAllPlayMusicVolume();
	}

	float MusicPlayer::getVolumeAttenuationCoefficient() const
	{
		return volumeAttenuationCoefficient_;
	}
	
	void MusicPlayer::stopFinishedMusic(int* const playMusicHandle)
	{
		if (playMusicHandle)
		{
			auto itrPlay = playMusicHandleToVolumeAndDistance_.find(*playMusicHandle);
			if (itrPlay != playMusicHandleToVolumeAndDistance_.end())
			{
				if (CheckSoundMem(itrPlay->first) == 0)
				{
					DeleteSoundMem(itrPlay->first);
					playMusicHandleToVolumeAndDistance_.erase(itrPlay);
					*playMusicHandle = -1;
				}
			}
		}
	}

	void MusicPlayer::startFadeMusicVolume(int playMusicHandle, float targetVolume, int fadeFrame, bool stopWhenFadeFinish)
	{
		auto itrPlay = playMusicHandleToVolumeAndDistance_.find(playMusicHandle);
		if (itrPlay != playMusicHandleToVolumeAndDistance_.end())
		{
			playMusicHandleToVolumeFadeData_[playMusicHandle] =
			{
				fadeFrame,
				(targetVolume - itrPlay->second.volume) / fadeFrame,
				stopWhenFadeFinish
			};
		}
	}

	void MusicPlayer::update()
	{
		for (auto itrFade = playMusicHandleToVolumeFadeData_.begin(); itrFade != playMusicHandleToVolumeFadeData_.end();)
		{
			auto itrPlay = playMusicHandleToVolumeAndDistance_.find(itrFade->first);
			if (itrPlay != playMusicHandleToVolumeAndDistance_.end())
			{
				itrPlay->second.volume += itrFade->second.deltaVolumeFade;
				setPlayMusicVolume(itrPlay->first, itrPlay->second.volume, itrPlay->second.distance);

				if (--itrFade->second.fadeFrame == 0)
				{
					if (itrFade->second.stopWhenFadeFinish)
					{
						StopSoundMem(itrPlay->first);
						DeleteSoundMem(itrPlay->first);
						playMusicHandleToVolumeAndDistance_.erase(itrPlay);
					}
					itrFade = playMusicHandleToVolumeFadeData_.erase(itrFade);
				}
				else ++itrFade;
			}
			else
			{
				itrFade = playMusicHandleToVolumeFadeData_.erase(itrFade);
			}
		}
	}
}