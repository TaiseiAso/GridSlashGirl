#ifndef music_player_h
#define music_player_h

#include <unordered_map>
#include "utils/singleton.h"

namespace game::audio
{
	class MusicPlayer : public Singleton<MusicPlayer>
	{
		friend class Singleton<MusicPlayer>; // Singleton でのインスタンス作成は許可

	private:
		struct MusicVolumeAndDistance {
			float volume; // 音楽の再生音量
			float distance; // 音源とリスナーの距離 (0以下なら距離を無視して音量減衰しない)
		};

		struct MusicVolumeFadeData {
			int fadeFrame; // フェードにかかるフレーム数
			float deltaVolumeFade; // 1フレームで変化する音量
			bool stopWhenFadeFinish; // フェード終了後に音楽を停止するか
		};

		// メモリに読み込む音楽の名前とファイルパスのマップ
		std::unordered_map<std::string, std::string> loadMusicNameToPath_;

		// メモリに読み込んだ音楽の名前とハンドルのマップ
		std::unordered_map<std::string, int> loadMusicNameToHandle_;

		// 再生している音楽のハンドルと<再生音量, リスナーとの距離>の構造体のマップ
		std::unordered_map<int, MusicVolumeAndDistance> playMusicHandleToVolumeAndDistance_;

		// 再生している音楽の音量を変化させるための情報セット
		std::unordered_map<int, MusicVolumeFadeData> playMusicHandleToVolumeFadeData_;

		// 全体の音量比率 (-1から1の間の値)
		float masterVolume_;

		// 音源とリスナーの距離による音量減衰の係数 (大きいほど減衰しやすい) (0以下なら減衰しない)
		float volumeAttenuationCoefficient_;

		// 再生中の音楽の音量を更新する
		void setPlayMusicVolume(int playMusicHandle, float playMusicVolume, float playMusicDistance) const;
		// 再生中の全ての音楽の音量を更新する
		void updateAllPlayMusicVolume() const;

		MusicPlayer(); // 外部でのインスタンス作成は禁止
		~MusicPlayer();

	public:
		// 音楽の名前とファイルパスが対応付けられたデータベースを読み込む
		void loadMusicNameToPathDatabase(const std::string& databaseFilePath, bool passFirstLine = true);
		
		// 音楽をメモリに読み込む (データベースの読み込みが前提)
		void loadMusic(const std::string& loadMusicName);
		// 音楽をメモリに読み込む
		void loadMusic(const std::string& loadMusicName, const std::string& loadMusicFilePath);
		
		// 音楽をメモリから破棄する
		void deleteMusic(const std::string& loadMusicName);

		// メモリに読み込んだ音楽を再生する (あとから制御しない効果音用)
		void playSE(const std::string& loadMusicName, float playMusicVolume, float playMusicDistance = 0.f) const;
		// メモリに読み込んだ音楽を再生する (ハンドルを返す) (失敗すると-1を返す)
		int playMusic(const std::string& loadMusicName, float playMusicVolume, float playMusicDistance = 0.f, bool isLoop = true, bool topPositionFlag = true);

		// 再生中の音楽を停止する
		void stopMusic(int* const playMusicHandle);

		// すべての音楽をメモリから破棄する
		void deleteAllMusic();

		// 再生中の音楽の音量を変更する
		void setPlayMusicVolume(int playMusicHandle, float playMusicVolume);
		// 再生中の音楽のリスナーとの距離を変更する
		void setPlayMusicDistance(int playMusicHandle, float playMusicDistance);

		// マスター音量を変更する (-1から1の間の値)
		void setMasterVolume(float masterVolume);
		// マスター音量を取得する
		float getMasterVolume() const;

		// 音源とリスナーの距離による音量減衰の係数を変更する
		void setVolumeAttenuationCoefficient(float volumeAttenuationCoefficient);
		// 音源とリスナーの距離による音量減衰の係数を取得する
		float getVolumeAttenuationCoefficient() const;

		// 終了しているのに停止していない音楽を停止する
		void stopFinishedMusic(int* const playMusicHandle);

		// 再生中の音楽の音量のフェードを開始する
		void startFadeMusicVolume(int playMusicHandle, float targetVolume, int fadeFrame, bool stopWhenFadeFinish = false);

		// 再生中でかつフェード中の音楽の音量を更新する
		void update();
	};
}

#endif // !music_player_h