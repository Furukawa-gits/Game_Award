#include "Title.h"
#include "Raki_imguiMgr.h"
#include "TexManager.h"

#include "NY_random.h"

using namespace myImgui;

Title::Title(ISceneChanger *changer) : BaseScene(changer) {

    
    camera->SetViewStatusEyeTargetUp(eye, target, up);

    stage->LoadStage("./Resources/stage1.csv", playerTile);
    player->Init();
    player->bodysetup(playerTile);

    UINT Back = TexManager::LoadTexture("Resources/back.png");

}

//������
void Title::Initialize() {
    /// <summary>
    /// �t�B�[���h�Ǘ���������
    /// </summary>

    //StageMoveParticle::Get()->Init(&cam);
}

void Title::Finalize()
{

}

//�X�V
void Title::Update() {
    camera->SetViewStatusEyeTargetUp(eye, target, up);

    player->Update(*stage);
}

//�`��
void Title::Draw() {

    //�w�i�ɏ�ɂ���
    Raki_DX12B::Get()->StartDrawRenderTarget();

    Raki_DX12B::Get()->StartDrawBackbuffer();

    // �`�揈��
    //DrawGraph(0, 0, Back, true);
    //DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), true);
    SpriteManager::Get()->SetCommonBeginDraw();
    stage->Draw(drawOffsetX, drawOffsetY);
    player->Draw(drawOffsetX, drawOffsetY);

    //�`��I��
    Raki_DX12B::Get()->CloseDraw();

}
