#ifndef scene_manager_h
#define scene_manager_h

#include <memory>
#include <unordered_map>
#include "utils/singleton.h"
#include "scene_factory.h"

namespace game::scene
{
	class SceneManager : public Singleton<SceneManager>
	{
		friend class Singleton<SceneManager>; // Singleton �ł̃C���X�^���X�쐬�͋���

	private:
		bool isMovingScene_; // �V�[�����ړ������ǂ���
		SCENE_ID nextSceneID_; // �ړ���̃V�[��ID
		bool isFadeOut_; // �t�F�[�h�A�E�g���t�F�[�h�C���C�����̔���
		int moveSceneFrame_; // �V�[���ړ��ɗv����t���[����
		int fadeLevel_; // �t�F�[�h�̂����� (�ő��moveSceneFrame)
		bool drawMoveSceneFadeOut_; // �t�F�[�h�A�E�g��`�悷�邩�ǂ���
		bool drawMoveSceneFadeIn_; // �t�F�[�h�C����`�悷�邩�ǂ���
		unsigned int moveSceneFadeColor_; // �V�[���ړ����̃t�F�[�h�F
		std::vector<SCENE_ID> createSceneIDVector_; // �V�[���ړ����ɍ쐬����V�[��ID�̃��X�g
		std::vector<SCENE_ID> deleteSceneIDVector_; // �V�[���ړ����ɔj������V�[��ID�̃��X�g

		// �V�[��ID�ƍ쐬�����V�[���̃}�b�v
		std::unordered_map<SCENE_ID, std::unique_ptr<BaseScene>> idToScene_;
		// ���݂̃V�[��ID
		SCENE_ID currentSceneID_;

		// �V�[���t�@�N�g��
		std::unique_ptr<SceneFactory> sceneFactory_;

		// �V�[��������������
		void initScene(SCENE_ID sceneID);
		// �V�[�����I������
		void finalScene(SCENE_ID sceneID);

		// ���݂̃V�[������������
		void swapScene();
		// �V�[���ړ����X�V����
		void updateMoveScene();

		// �V�[���ړ��̃t�F�[�h�C��/�A�E�g��`�悷��
		void drawMoveSceneFade() const;

		SceneManager(); // �O���ł̃C���X�^���X�쐬�͋֎~
		~SceneManager();

	public:
		// �X�e�b�v���Ƃ̏��� (�I����false��Ԃ�)
		// ��ӏ��݂̂���̌Ăяo����������
		bool step();

		// ���݃V�[���ړ������ǂ������擾
		bool isMovingScene() const;
		/*
			�V�[���ړ��󋵂��擾���� (-1.0~1.0�̊Ԃ̒l)
			-1.0~0.0: �t�F�[�h�C����
			0.0: �V�[���ړ����ł͂Ȃ� (�������͑����V�[���ړ��̏u��)
			0.0~1.0: �t�F�[�h�A�E�g��
		*/
		float getFadeRatio() const;

		// �V�[���ړ��ɗv����t���[������ݒ肷��
		void setMoveSceneFrame(int moveSceneFrame);
		// �t�F�[�h�A�E�g/�C����`�悷�邩�ǂ�����ݒ肷��
		void setDrawMoveSceneFade(bool drawMoveSceneFadeOut, bool drawMoveSceneFadeIn);
		// �V�[���ړ����̃t�F�[�h�F��ݒ肷��
		void setMoveSceneFadeColor(unsigned int moveSceneFadeColor);

		// �V�[���ړ����J�n����
		void moveScene(SCENE_ID sceneID, const std::vector<SCENE_ID>& createSceneIDVector = {}, const std::vector<SCENE_ID>& deleteSceneIDVector = {});

		// �ŏ��̃V�[�����쐬����
		void createFirstScene(SCENE_ID sceneID);
		// �V�[�����쐬����
		void createScene(SCENE_ID sceneID);

		// �V�[����j������
		void deleteScene(SCENE_ID sceneID);
	};
}

#endif // !scene_manager_h