#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>

/*================================
	コピペ用↓
=================================*/

/*********************************
	大見出しコピペ
*********************************/

/******** 小見出しコピペ用 **********/

/*================================
	コピペ用↑
=================================*/

/******** ウィンドウ名の指定 **********/
const char kWindowTitle[] = "LC1A_16_トヨダユウキ_TD1_課題";

/******** ウィンドウサイズの指定 **********/
const int kWindowWidth = 1280; //x
const int kWindowHeight = 720; //y

/*********************************
	定数の宣言ここまで
*********************************/

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	/*********************************
		構造体宣言ここから
	*********************************/
#pragma region 構造体

#pragma region 二次元ベクトル

	/******** 二次元ベクトル **********/

	typedef struct vector2 {

		float x; //x
		float y; //y

	};

#pragma endregion
#pragma region 距離

	/******** 距離 **********/

	typedef struct Distance {

		vector2 distance; //距離xy
		float length; //実際距離

	};

#pragma endregion
#pragma region 画像

	/******** 画像 **********/

	typedef struct graph {

		vector2 translate;
		vector2 radius;
		vector2 imgRadius;
		vector2 drawStartArea;
		vector2 drawEndArea;
		int name;

	};

#pragma endregion
#pragma region キャラクター

	/******** キャラクター **********/
	 //位置
	 //動作方向
	 //ベクトル長さ
	 //当たり判定半径
	 //進行方向
	 //スピード
	 //スピードデフォルト値
	 //生存しているか
	 //キャラクタHP
	 //与えるダメージ
	 //画像半径
	 //色
	typedef struct chara {

		vector2 translate; //位置
		vector2 moveDirection; //動作方向
		float vectorLength; //ベクトル長さ

		float radius; //当たり判定半径
		float theta; //進行方向

		float speed; //スピード
		float defSpeed; //スピードデフォルト/

		int isAlive;
		int HP; //キャラクタHP

		int damage; //与えるダメージ

		int graph; //キャラ画像
		int graphRadius; //画像半径

		unsigned int color; //色

	};

#pragma endregion

#pragma endregion
	/*********************************
		構造体宣言ここまで
	*********************************/

	/*********************************
		変数宣言ここから
	*********************************/
#pragma region 変数

#pragma region ワールド座標関係

	/******** ワールド座標原点 **********/
	vector2 worldPosOrigin{

		0, //x
		kWindowHeight //y

	};

#pragma endregion
#pragma region シーン

	enum Scenes
	{

		TITLE,
		GAME,
		RESULT

	};

	int scene = TITLE;

#pragma endregion
#pragma region スコア

	int score = 0;

	int combo = 0;
	int nowCombo = 0;
	int startCombo = 10;
	float comboMagnification = 1.0f;
	float comboReceptionTime = 120.0f;
	float defComboReceptionTime = 120.0f;


#pragma endregion


#pragma region 乱数 

	unsigned int currentTime = time(nullptr);

	currentTime = time(nullptr);
	srand(currentTime);

#pragma endregion

#pragma region スクロール関係

	/******** スクロール **********/

	//開始座標
	vector2 scroolStartPos{

		kWindowWidth - kWindowWidth / 2, //x
		worldPosOrigin.y - kWindowHeight + kWindowHeight / 2 //y

	};

	//スクロール値
	vector2 scrool{

		0.0f, //x
		0.0f //y

	};

#pragma endregion
#pragma region 背景

	/******** 背景 **********/

	int white1x1Png = Novice::LoadTexture("white1x1.png");

	int bgGraph[6];

	bgGraph[0] = Novice::LoadTexture("./resources/graph/map/BG_1.png");
	bgGraph[1] = Novice::LoadTexture("./resources/graph/map/BG_2.png");
	bgGraph[2] = Novice::LoadTexture("./resources/graph/map/BG_3.png");
	bgGraph[3] = Novice::LoadTexture("./resources/graph/map/BG_4.png");
	bgGraph[4] = Novice::LoadTexture("./resources/graph/map/BG_5.png");
	bgGraph[5] = Novice::LoadTexture("./resources/graph/map/BG_6.png");

	graph bg[6];

	for (int i = 0; i < 6; i++) {

		bg[i] = {

			kWindowWidth / 2, kWindowHeight / 2,
			kWindowWidth, kWindowHeight,
			kWindowWidth, kWindowHeight,
			0.0f, 0.0f,
			1920.0f, 1080.0f,
			bgGraph[i]

		};

	}

#pragma endregion
#pragma region プレイヤー

	/******** プレイヤー **********/
	chara player{

		kWindowWidth * 1.5f, kWindowHeight, //translate x, y
		0.0f, 0.0f, //moveDirection x, y
		0.0f, //vectorLength

		128.0f, //radius
		0.0f,

		5.0f, //speed
		5.0f, //defSpeed

		true,
		1, //HP

		10, //damage

		Novice::LoadTexture("./resources/graph/player/player.png"), //graph
		128, //graphRadius

		WHITE

	};

	vector2 playerPreTranslate = {

		0.0f,0.0f

	};

	vector2 playerAttackRange = {

		0.0f, 0.0f

	};

	float theta = 0.0f;

	//スペースキートリガー用
	int isPressSpace = false;

	//チャージできるか
	int canCharge = true;
	//現在チャージしているか
	int isCharging = false;
	//チャージが完了しているか
	int compCharge = false;

	//攻撃中か
	int isAttacking = false;

	//チャージされているパワー
	float chargePower = 0.0f;
	//パワーの最大値
	float maxPower = 60.0f;

	//チャージ可能までのクールタイム
	float chargeCoolTime = 0.0f;
	//チャージ可能までのクールタイムのデフォルト値
	float defChargeCoolTime = 120.0f;

	int enemyHit = false;

#pragma endregion
#pragma region 敵

	const int kMaxEnemy = 100;

	chara enemy[kMaxEnemy];
	Distance e2e[kMaxEnemy];

	enum EnemyType
	{

		FOLLOW

	};

	int isNockBacking[kMaxEnemy];
	float nockBackSpeed[kMaxEnemy];

	int enemyType[kMaxEnemy];

	int enemyNockBack[kMaxEnemy];

	for (int i = 0; i < kMaxEnemy; i++) {

		enemy[i] = {

			0.0f, 0.0f,
			0.0f, 0.0f,
			0.0f,

			64.0f,
			0.0f,

			3.0f,
			3.0f,

			false,
			1,
			1,

			Novice::LoadTexture("./resources/graph/enemy/enemy.png"),
			128,

			WHITE

		};

		enemyType[i] = FOLLOW;

		e2e[i] = {

			0.0f, 0.0f,
			0.0f

		};

		enemyNockBack[i] = 0.0f;

		isNockBacking[i] = false;
		nockBackSpeed[i] = 0.0f;

	}

	Distance e2p{

		0.0f, 0.0f,
		0.0f

	};

#pragma endregion
#pragma region スポーン

	vector2 spawnPoint[4];

	spawnPoint[0] = { 0.0f, 0.0f };
	spawnPoint[1] = { 0.0f, 0.0f };
	spawnPoint[2] = { 0.0f, 0.0f };
	spawnPoint[3] = { 0.0f, 0.0f };

	float spawnTimer = 60.0f;
	float defSpawnTimer = 90.0f;

	int canSpawn = false;
	int enemySpawnPoint = 0;

	int spawnCounter = 0;
	int nowSpawnCounter = 0;
	int maxOnceSpawn = 10;

#pragma endregion

#pragma endregion
	/*********************************
		変数宣言ここまで
	*********************************/

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		/*********************************
			更新処理ここから
		*********************************/

		/*================================
			コピペ用↓
		=================================*/

		/*********************************
			大見出しコピペ
		*********************************/

		/******** 小見出しコピペ用 **********/

		/*================================
			コピペ用↑
		=================================*/

		/*********************************
			スクリーン関係ここから
		*********************************/

		/******** フルスクリーン **********/
		//Novice::SetWindowMode(kFullscreen);

		/*********************************
			スクリーン関係ここまで
		*********************************/

		switch (scene)
		{
		case TITLE:

		#pragma region シーン遷移

			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {

				scene++;

			}

		#pragma endregion
			break;
		case GAME:

		#pragma region プレイヤー

		#pragma region 移動


			///******** プレイヤー移動 **********/

			//		//ベクトル初期化
			//player.moveDirection.x = 0.0f;
			//player.moveDirection.y = 0.0f;

			////移動方向指定
			//if (keys[DIK_UP] || keys[DIK_W]) {

			//	player.moveDirection.y++; //上

			//}

			//if (keys[DIK_LEFT] || keys[DIK_A]) {

			//	player.moveDirection.x--; //左

			//}

			//if (keys[DIK_DOWN] || keys[DIK_S]) {

			//	player.moveDirection.y--; //下

			//}

			//if (keys[DIK_RIGHT] || keys[DIK_D]) {

			//	player.moveDirection.x++; //右

			//}

			//if (isCharging == false && isAttacking == false) {

			//	//ベクトルの長さを求める
			//	player.vectorLength = sqrt(pow(player.moveDirection.x, 2) + pow(player.moveDirection.y, 2));

			//	//ベクトルの長さが0以外の時
			//	if (player.vectorLength != 0.0f) {

			//		//x方向の移動
			//		player.translate.x += player.moveDirection.x / player.vectorLength * player.speed;

			//		//y方向の移動
			//		player.translate.y += player.moveDirection.y / player.vectorLength * player.speed;

			//	}
			//	else {

			//		//x方向の移動
			//		player.translate.x += player.moveDirection.x * player.speed;

			//		//y方向の移動
			//		player.translate.y += player.moveDirection.y * player.speed;

			//	}

			//}


#pragma endregion
		#pragma region 壁貫通防止
					//左右
					if (player.translate.x <= 0 + player.radius / 2) {

						player.translate.x = player.radius / 2;

					}
					else if (player.translate.x >= kWindowWidth * 3 - player.radius / 2) {

						player.translate.x = kWindowWidth * 3 - player.radius / 2;

					}

					//上下
					if (player.translate.y <= 0 + player.radius / 2) {

						player.translate.y = player.radius / 2;

					}
					else if (player.translate.y >= kWindowHeight * 2 - player.radius / 2) {

						player.translate.y = kWindowHeight * 2 - player.radius / 2;

					}
		#pragma endregion
		#pragma region チャージ
					/******** チャージ関係の処理 **********/
					//スペースキー長押し
					if (keys[DIK_SPACE]) {

						//チャージ状態true
						isCharging = true;

					}
					else {

						//チャージ状態false
						isCharging = false;

					}

					if (keys[DIK_RIGHT] || keys[DIK_D]) {

						player.theta += 0.1f;

					}

					else if (keys[DIK_LEFT] || keys[DIK_A]) {

						player.theta -= 0.1f;

					}

					//チャージ状態trueの時
					if (isCharging == true && isAttacking == false) {

						if (chargePower < maxPower) {

							//チャージ
							chargePower += 5.0f;

						}
						else {

							//一定の値を超えたら固定
							chargePower = maxPower;

						}
					}
					else {

						if (chargePower > 0) {

							//スペースキーを離したらパワーが減る
							chargePower -= 4.0f;

						}
						else {

							//0以下になったら値を0にリセット
							chargePower = 0;

							isAttacking = false;

						}

					}

					if (theta >= 6.0f) {

						player.theta = 0.0f;

					}
					else if (theta < 0.0f) {

						player.theta = 5.9f;

					}

					if (!keys[DIK_SPACE] && preKeys[DIK_SPACE]) {

						if (isAttacking == false) {

							isAttacking = true;

						}

					}

					if (isAttacking == true) {

						playerPreTranslate.x = player.translate.x;
						playerPreTranslate.y = player.translate.y;

						player.translate.x += (cosf(player.theta) * player.speed * chargePower / 3.0f);
						player.translate.y += -(sinf(player.theta) * player.speed * chargePower / 3.0f);

						playerAttackRange.x = player.translate.x - playerPreTranslate.x;
						playerAttackRange.y = player.translate.y - playerPreTranslate.y;

						chargePower--;

					}
		#pragma endregion
		#pragma region コンボ

					if (comboReceptionTime < 0) {

						combo = 0;
						nowCombo = 0;
						comboMagnification = 1.0f;
						comboReceptionTime = defComboReceptionTime;

					}

					if (combo >= 1) {

						comboReceptionTime--;

					}
					else {

						comboReceptionTime = defComboReceptionTime;

					}

					if (nowCombo >= startCombo) {

						comboMagnification += 0.1f;
						nowCombo = 0;

					}

		#pragma endregion

		#pragma endregion
		#pragma region スクロール

					/******** スクロール処理 **********/

					if (player.translate.x >= scroolStartPos.x || player.translate.x <= scroolStartPos.x) {

						scrool.x = player.translate.x - scroolStartPos.x;

					}
					else {

						scrool.x = 0.0f;

					}

					if (player.translate.y >= scroolStartPos.y || player.translate.y <= scroolStartPos.y) {

						scrool.y = player.translate.y - scroolStartPos.y;

					}
					else {

						scrool.y = 0.0f;

					}

		#pragma endregion
		#pragma region 敵

					#pragma region スポーン地点設定

					//上
					spawnPoint[0].x = player.translate.x;
					spawnPoint[0].y = player.translate.y + kWindowHeight / 2 + player.radius;

					//下
					spawnPoint[1].x = player.translate.x;
					spawnPoint[1].y = player.translate.y - kWindowHeight / 2 - player.radius;

					//右
					spawnPoint[2].x = player.translate.x + kWindowWidth / 2 + player.radius;
					spawnPoint[2].y = player.translate.y;

					//左
					spawnPoint[3].x = player.translate.x - kWindowWidth / 2 - player.radius;
					spawnPoint[3].y = player.translate.y;

					#pragma endregion

					#pragma region スポーンタイマー

					if (nowSpawnCounter <= kMaxEnemy) {

						if (spawnTimer <= 0.0f) {

							canSpawn = true;

						}
						else {

							canSpawn = false;
							spawnTimer--;

						}

					}

					#pragma endregion


					for (int i = 0; i < kMaxEnemy; i++) {

						if (keys[DIK_E]) {

							spawnCounter = 0;
							nowSpawnCounter = 0;
							nowSpawnCounter--;
							isNockBacking[i] = false;
							enemy[i].translate.x = 0.0f;
							enemy[i].translate.y = 0.0f;
							enemy[i].isAlive = false;

						}

						if (enemy[i].isAlive == true) {

						#pragma region 追尾敵
							if (isNockBacking[i] == false) {

								switch (enemyType[i])
								{
								case FOLLOW:

									enemy[i].theta = atan2(player.translate.y - enemy[i].translate.y, player.translate.x - enemy[i].translate.x);

									if (enemy[i].theta <= 0) {

										enemy[i].theta *= -1;

									}
									else {

										float def = M_PI - enemy[i].theta;

										enemy[i].theta = def + M_PI;

									}

									enemy[i].translate.x += (cosf(enemy[i].theta) * enemy[i].speed);
									enemy[i].translate.y += -(sinf(enemy[i].theta) * enemy[i].speed);
									break;

								}

							}	
							else {

								enemy[i].translate.x += (cosf(enemyNockBack[i]) * nockBackSpeed[i]);
								enemy[i].translate.y += -(sinf(enemyNockBack[i]) * nockBackSpeed[i]);
								nockBackSpeed[i]--;

							}

							if (nockBackSpeed[i] <= 0) {

								isNockBacking[i] = false;

							}

						#pragma endregion

						#pragma region 衝突判定

							if (isAttacking == false) {

								if (isNockBacking[i] == false) {

									e2p.distance.x = enemy[i].translate.x - player.translate.x;
									e2p.distance.y = enemy[i].translate.y - player.translate.y;

									e2p.length = sqrt(pow(e2p.distance.x, 2) + pow(e2p.distance.y, 2));

									if (e2p.length <= enemy[i].radius / 2 + player.radius / 2) {

										enemyHit = true;
										enemyNockBack[i] = rand();
										enemyNockBack[i] = enemyNockBack[i] % 360;

										enemyNockBack[i] = enemyNockBack[i] * (M_PI / 180.0f);

										isNockBacking[i] = true;
										nockBackSpeed[i] = 20.0f;

									}

								}

							}
							else {

								e2p.distance.x = enemy[i].translate.x - player.translate.x;
								e2p.distance.y = enemy[i].translate.y - player.translate.y;

								e2p.length = sqrt(pow(e2p.distance.x, 2) + pow(e2p.distance.y, 2));

								if (e2p.length <= enemy[i].radius / 2 + player.radius / 2) {

									enemy[i].translate.x = 0.0f;
									enemy[i].translate.y = 0.0f;

									combo++;
									nowCombo++;
									comboReceptionTime = defComboReceptionTime;

									score += 100 * comboMagnification;

									nowSpawnCounter--;

									isNockBacking[i] = false;
									enemy[i].isAlive = false;

								}

							}

						#pragma endregion

						}

						else {

							if (canSpawn == true) {

								if (spawnCounter <= maxOnceSpawn) {

									enemySpawnPoint = rand();
									enemySpawnPoint = enemySpawnPoint % 4;

									enemy[i].translate = spawnPoint[enemySpawnPoint];

									enemy[i].speed = rand();
									enemy[i].speed = (int)enemy[i].speed % 5 + 2;

									/*if (enemySpawnPoint >= 2) {

										enemy[i].translate.x = rand();
										enemy[i].translate.x = (int)enemy[i].translate.x % ((int)enemy[i].translate.x + kWindowWidth / 2) - ((int)enemy[i].translate.x - kWindowWidth / 2);

									}
									else if (enemySpawnPoint >= 0) {

										enemy[i].translate.y = rand();
										enemy[i].translate.y = (int)enemy[i].translate.y % ((int)enemy[i].translate.y + kWindowHeight / 2) - ((int)enemy[i].translate.y - kWindowHeight / 2);

									}*/

									enemy[i].isAlive = true;

									nowSpawnCounter++;
									spawnCounter++;

								}
								else {
									
									canSpawn = false;
									spawnTimer = defSpawnTimer;
									spawnCounter = 0;

								}

							}

						}

					}
		#pragma endregion

			break;
		case RESULT:



			break;
		}

		/*********************************
			更新処理ここまで
		*********************************/

		/*********************************
			描画処理ここから
		*********************************/

		switch (scene)
		{
		case TITLE:



			break;
		case GAME:

		#pragma region 背景描画

			Novice::DrawQuad(

				worldPosOrigin.x + player.translate.x - kWindowWidth / 2 - scrool.x,
				worldPosOrigin.y - player.translate.y - kWindowHeight / 2 + scrool.y,

				worldPosOrigin.x + player.translate.x + kWindowWidth / 2 - scrool.x,
				worldPosOrigin.y - player.translate.y - kWindowHeight / 2 + scrool.y,

				worldPosOrigin.x + player.translate.x - kWindowWidth / 2 - scrool.x,
				worldPosOrigin.y - player.translate.y + kWindowHeight / 2 + scrool.y,

				worldPosOrigin.x + player.translate.x + kWindowWidth / 2 - scrool.x,
				worldPosOrigin.y - player.translate.y + kWindowHeight / 2 + scrool.y,

				0,
				0,

				1,
				1,

				white1x1Png,
				BLACK

			);

			/******** 背景描画 **********/

			for (int i = 0; i < 3; i++) {


				Novice::DrawQuad(

					worldPosOrigin.x + bg[i].translate.x * (i + 1) + (kWindowWidth / 2 * i) - bg[i].radius.x / 2 - scrool.x,
					worldPosOrigin.y - bg[i].translate.y - bg[i].radius.y / 2 - (kWindowHeight)+scrool.y,

					worldPosOrigin.x + bg[i].translate.x * (i + 1) + (kWindowWidth / 2 * i) + bg[i].radius.x / 2 - scrool.x,
					worldPosOrigin.y - bg[i].translate.y - bg[i].radius.y / 2 - (kWindowHeight)+scrool.y,

					worldPosOrigin.x + bg[i].translate.x * (i + 1) + (kWindowWidth / 2 * i) - bg[i].radius.x / 2 - scrool.x,
					worldPosOrigin.y - bg[i].translate.y + bg[i].radius.y / 2 - (kWindowHeight)+scrool.y,

					worldPosOrigin.x + bg[i].translate.x * (i + 1) + (kWindowWidth / 2 * i) + bg[i].radius.x / 2 - scrool.x,
					worldPosOrigin.y - bg[i].translate.y + bg[i].radius.y / 2 - (kWindowHeight)+scrool.y,

					bg[i].drawStartArea.x,
					bg[i].drawStartArea.y,

					bg[i].drawEndArea.x,
					bg[i].drawEndArea.y,

					bg[i].name,
					WHITE

				);


			}

			for (int i = 0; i < 3; i++) {


				Novice::DrawQuad(

					worldPosOrigin.x + bg[i + 3].translate.x * (i + 1) + (kWindowWidth / 2 * i) - bg[i + 3].radius.x / 2 - scrool.x,
					worldPosOrigin.y - bg[i + 3].translate.y - bg[i + 3].radius.y / 2 + scrool.y,

					worldPosOrigin.x + bg[i + 3].translate.x * (i + 1) + (kWindowWidth / 2 * i) + bg[i + 3].radius.x / 2 - scrool.x,
					worldPosOrigin.y - bg[i + 3].translate.y - bg[i].radius.y / 2 + scrool.y,

					worldPosOrigin.x + bg[i + 3].translate.x * (i + 1) + (kWindowWidth / 2 * i) - bg[i + 3].radius.x / 2 - scrool.x,
					worldPosOrigin.y - bg[i + 3].translate.y + bg[i + 3].radius.y / 2 + scrool.y,

					worldPosOrigin.x + bg[i + 3].translate.x * (i + 1) + (kWindowWidth / 2 * i) + bg[i + 3].radius.x / 2 - scrool.x,
					worldPosOrigin.y - bg[i + 3].translate.y + bg[i + 3].radius.y / 2 + scrool.y,

					bg[i + 3].drawStartArea.x,
					bg[i + 3].drawStartArea.y,

					bg[i + 3].drawEndArea.x,
					bg[i + 3].drawEndArea.y,

					bg[i + 3].name,
					WHITE

				);


			}

#pragma endregion

		#pragma region プレイヤー描画

			/******** プレイヤー描画 **********/
			Novice::DrawQuad(

				worldPosOrigin.x + player.translate.x - player.radius / 2 - scrool.x,
				worldPosOrigin.y - player.translate.y - player.radius / 2 + scrool.y,

				worldPosOrigin.x + player.translate.x + player.radius / 2 - scrool.x,
				worldPosOrigin.y - player.translate.y - player.radius / 2 + scrool.y,

				worldPosOrigin.x + player.translate.x - player.radius / 2 - scrool.x,
				worldPosOrigin.y - player.translate.y + player.radius / 2 + scrool.y,

				worldPosOrigin.x + player.translate.x + player.radius / 2 - scrool.x,
				worldPosOrigin.y - player.translate.y + player.radius / 2 + scrool.y,

				0,
				0,

				player.graphRadius,
				player.graphRadius,

				player.graph,
				player.color

			);

#pragma endregion

		#pragma region 敵描画

			for (int i = 0; i < kMaxEnemy; i++) {

				if (enemy[i].isAlive == true) {

					Novice::DrawQuad(

						worldPosOrigin.x + enemy[i].translate.x - enemy[i].radius / 2 - scrool.x,
						worldPosOrigin.y - enemy[i].translate.y - enemy[i].radius / 2 + scrool.y,

						worldPosOrigin.x + enemy[i].translate.x + enemy[i].radius / 2 - scrool.x,
						worldPosOrigin.y - enemy[i].translate.y - enemy[i].radius / 2 + scrool.y,

						worldPosOrigin.x + enemy[i].translate.x - enemy[i].radius / 2 - scrool.x,
						worldPosOrigin.y - enemy[i].translate.y + enemy[i].radius / 2 + scrool.y,

						worldPosOrigin.x + enemy[i].translate.x + enemy[i].radius / 2 - scrool.x,
						worldPosOrigin.y - enemy[i].translate.y + enemy[i].radius / 2 + scrool.y,

						0,
						0,

						enemy[i].graphRadius,
						enemy[i].graphRadius,

						enemy[i].graph,
						enemy[i].color

					);

				}

			}

#pragma endregion

			break;
		case RESULT:



			break;
		}

#pragma region Debug描画

		/******** プレイヤーデバック描画 **********/

		//座標
		Novice::ScreenPrintf(0, 10, "Px : %4.2f Py : %4.2f", player.translate.x, player.translate.y);
		Novice::ScreenPrintf(0, 30, "Enemy : %d", nowSpawnCounter);
		Novice::ScreenPrintf(0, 50, "SCORE : %d", score);
		Novice::ScreenPrintf(0, 70, "Combo : %d", combo);
		Novice::ScreenPrintf(0, 90, "Combo : %d", nowCombo);
		Novice::ScreenPrintf(0, 110, "ScoreMag : %4.2f", comboMagnification);

		//発射方向
		Novice::DrawLine(
			worldPosOrigin.x + player.translate.x - scrool.x,
			worldPosOrigin.y - player.translate.y + scrool.y,
			worldPosOrigin.x + player.translate.x + (cosf(player.theta) * player.speed * 2 * (chargePower + 10) / 3) - scrool.x,
			worldPosOrigin.y - player.translate.y + (sinf(player.theta) * player.speed * 2 * (chargePower + 10) / 3) + scrool.y,
			WHITE
		);

#pragma endregion

		/*********************************
			描画処理ここまで
		*********************************/

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {

			break;

		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
