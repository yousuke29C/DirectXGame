#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete sprite_;
	delete model_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	// ファイル名を指定てテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");
	// スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	// 3Dモデルの生成
	model_ = Model::Create();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ピュープロジェクトの初期化
	viewProjection_.Initialize();
	// サウンドデータの読み込み
	soundDateHandle_ = audio_->LoadWave("se_sad03.wav");
	// 音声再生
	audio_->PlayWave(soundDateHandle_);
	// 音声再生
	/*voiceHandle_ = audio_->PlayWave(soundDateHandle_, true);*/
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");
	// 3Dモデル
	model_ = Model::Create();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	// X, Y, Z, 方向のスケーリング設定
	worldTransform_.scale_ = {5.0f, 1.0f, 1.0f};
	// ワールドトランスフォームを設定
	worldTransform_.Initialize();
	// X, Y, Z, 輪周りの回転角を設定
	worldTransform_.rotation_ = {0.0f, XM_PI / 4.0f, 0.0f};
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// X, Y, Z, 輪周りの回転角の設定
	worldTransform_.rotation_ = {0.0f, XMConvertToRadians(45.0f), 0.0f};
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// X, Y, Z, 輪周りの平行移動を設定
	worldTransform_.translation_ = {0.0f, 10.0f, 0.0f};
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// X, Y, Z, 方向のスケーリングを設定
	worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};
	// X, Y, Z, 輪周りの回転角の設定
	worldTransform_.rotation_ = {XM_PI / 4.0f, XM_PI / 4.0f, 0.0f};
	// X, Y, Z, 輪周りの平行移動を設定
	worldTransform_.translation_ = {10.0f, 10.0f, 10.0f};

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
}
void GameScene::Update() {
	// スプライトの今の座標を取得
	XMFLOAT2 position = sprite_->GetPosition();
	// 座標を{2,0}移動
	position.x += 2.0f;
	position.y += 1.0f;
	// 移動した座標をスプライトに反映
	sprite_->SetPosition(position);
	// スペースキーを押した瞬間
	if (input_->TriggerKey(DIK_SPACE)) {
		// 音声停止
		audio_->StopWave(voiceHandle_);
	}
	// デバックテキストの表示
	// debugText_->Print("Kaizokuou ni oreha naru.", 50, 50, 1.0f);
	debugText_->Print("translation:(10.000000, 10.000000, 10.000000)", 50, 50, 1.0f);
	debugText_->Print("rotation:(0.785398, 0.785398, 0.000000)", 50, 70, 1.0f);
	debugText_->Print("scale:(5.000000, 5.000000, 5.000000)", 50, 90, 1.0f);
	// 書式指定付き表示
	debugText_->SetPos(50, 70);
	// debugText_->Printf("year:%d", 2001);
	//  変数の値をインクリメント
	value_++;
	// 値を含んだ文字列
	// std::string strDebug = std::string("Value:") + std::to_string(value_);
	// デバッグテキストの表示
	// debugText_->Print(strDebug, 50, 30, 1.0f);
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

	/*sprite_->Draw();*/

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
	// 3Dモデル
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

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}