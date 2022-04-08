﻿#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() { delete sprite_; 
delete model_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");
	//スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	model_ = Model::Create();
	dxCommon_->GetDevice();
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	//サウンドデータの読み込み
	soundDateHandle_ = audio_->LoadWave("se_sad03.wav");
	audio_->PlayWave(soundDateHandle_);
	voiceHandle_ = audio_->PlayWave(soundDateHandle_, true);//音声再生

}

void GameScene::Update() { XMFLOAT2 position = sprite_->GetPosition();
//座標を{2,0}移動
	position.x += 2.0f;
position.y += 1.0f;
//移動した座標をスプライトに反映
sprite_->SetPosition(position);

//スペースキーを押した瞬間
if (input_->TriggerKey(DIK_SPACE)) {
	//音声消失
	audio_->StopWave(voiceHandle_);
}

//デバックテキストの表示
debugText_->Print("Kaizokuou ni oreha naru.", 50, 50, 1.0f);
//書式指定付き表示
debugText_->SetPos(50, 10);
debugText_->Printf("year:%d", 2001);
//変数の値をインクリメント
value_++;
//値を含んだ文字列
std::string strDebug = std::string("Value:") +
std::to_string(value_);
//デバックテキストの表示
debugText_->Print(strDebug, 50, 100, 1.0f);

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	sprite_->Draw();
	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
