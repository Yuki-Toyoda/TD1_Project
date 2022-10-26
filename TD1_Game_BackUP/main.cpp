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
const int kWindowWidth = 1920; //x
const int kWindowHeight = 1080; //y

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

#pragma region ゲージ

	typedef struct Gage {

		vector2 translate;
		vector2 length;
		unsigned int color;

	};

#pragma endregion

#pragma region 矩形
	typedef struct Quad {

		vector2 q1;
		vector2 q2;
		vector2 q3;
		vector2 q4;

	};
#pragma endregion

#pragma region easing

	typedef struct easing {

		vector2 translate;
		vector2 startPos;
		vector2 endPos;
		vector2 radius;
		vector2 startRadius;
		vector2 endRadius;
		float time;
		float easeTime;

	};

#pragma endregion

#pragma region エフェクト
	/******** エフェクト(残像) **********/

	typedef struct trajectory {
		vector2 translate; //位置
		float radius;
		unsigned int carentAlpha;
		int isActive;
		int graph;
		int graphRadius; //画像半径
	};

	/******** エフェクト(チャージ) **********/
	typedef struct effect {
		vector2 translate; //位置
		vector2 moveDirection; //動作方向
		float vectorLength; //ベクトル長さ
		float radius;
		unsigned int carentAlpha;
		int isActive;
		int graph;
		int graphRadius; //画像半径
	};

	/******** 死亡エフェクト **********/
	typedef struct deathEffect {
		vector2 translate; //位置
		vector2 moveDirection; //動作方向
		float vectorLength; //ベクトル長さ
		float radius;
		unsigned int carentAlpha;
		int isActive;
		int graph;
		int graphRadius; //画像半径
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

#pragma region スクリーン

	int fullScreen = false; 

	unsigned int currentFadeAlpha = 0xFF;
	int fadeIn = true;

	unsigned int currentBlackOutAlpha = 0xFF;
	int blackout = false;

#pragma endregion

#pragma region ゲーム

	int gameTimer = 3600;

	int flame = 0;

	int gameMinutesTimer = 0;
	int gameSecondsTimer = 0;

	int recGameMinutesTimer = 0;
	int recGameSecondsTimer = 0;

	int numberSize = 256;
	int numberSpace = numberSize / 2;

	int eachSec[2] = { 0, 0 };

	int numberGraph[11];

	numberGraph[0] = Novice::LoadTexture("./resources/graph/numbers/0.png");
	numberGraph[1] = Novice::LoadTexture("./resources/graph/numbers/1.png");
	numberGraph[2] = Novice::LoadTexture("./resources/graph/numbers/2.png");
	numberGraph[3] = Novice::LoadTexture("./resources/graph/numbers/3.png");
	numberGraph[4] = Novice::LoadTexture("./resources/graph/numbers/4.png");
	numberGraph[5] = Novice::LoadTexture("./resources/graph/numbers/5.png");
	numberGraph[6] = Novice::LoadTexture("./resources/graph/numbers/6.png");
	numberGraph[7] = Novice::LoadTexture("./resources/graph/numbers/7.png");
	numberGraph[8] = Novice::LoadTexture("./resources/graph/numbers/8.png");
	numberGraph[9] = Novice::LoadTexture("./resources/graph/numbers/9.png");

	int DotGraph = Novice::LoadTexture("./resources/graph/numbers/Dot.png");
	int XGraph = Novice::LoadTexture("./resources/graph/numbers/x.png");

	vector2 secondsTimerPosOrigin = {

		kWindowWidth / 2,
		512

	};

	enum Tutorial {

		MOVE,
		ANGLE,
		CHARGE,
		ATTACK,
		PUTDECOY,
		DECOY,
		DECOYHP,
		DECOYGAMEOVER,
		COLLECTDECOY,
		DECOYHEAL,
		ENHANCEDATTACK,
		EATTACK,
		MACHINEHP,
		MACHINEREPAIR

	};

	int tutorial = MOVE;

	int tutorialStart = false;
	int tutorialFinish = false;

	int nextTutorial = false;

	int tutorialMove = false;
	int tutorialAngle = false;
	int tutorialCharge = false;
	int endTutorialMove = false;

	int tutorialDecoy = false;
	int tutorialPutDecoy = false;
	int tutorialCollectDecoy = false;
	int endTutorialDecoy = false;

	int tutorialMachine = false;
	int tutorialMachineHP = false;
	int endTutorialMachine = false;

	int gameStart = false;
	int gameFinish = false;

	int tutorialGraph[14];

	tutorialGraph[0] = Novice::LoadTexture("./resources/graph/tutorial/1_Guide_Move.png");
	tutorialGraph[1] = Novice::LoadTexture("./resources/graph/tutorial/2_Guide_Direction.png");
	tutorialGraph[2] = Novice::LoadTexture("./resources/graph/tutorial/3_Guide_Charge.png");
	tutorialGraph[3] = Novice::LoadTexture("./resources/graph/tutorial/4_Guide_Attack.png");
	tutorialGraph[4] = Novice::LoadTexture("./resources/graph/tutorial/5_Guide_PutDecoy.png");
	tutorialGraph[5] = Novice::LoadTexture("./resources/graph/tutorial/6_Guide_Decoy.png");
	tutorialGraph[6] = Novice::LoadTexture("./resources/graph/tutorial/7_Guide_DecoyHP.png");
	tutorialGraph[7] = Novice::LoadTexture("./resources/graph/tutorial/8_Guide_DecoyGameOver.png");
	tutorialGraph[8] = Novice::LoadTexture("./resources/graph/tutorial/9_Guide_CollectDecoy.png");
	tutorialGraph[9] = Novice::LoadTexture("./resources/graph/tutorial/10_Guide_DecoyHeal.png");
	tutorialGraph[10] = Novice::LoadTexture("./resources/graph/tutorial/11_Guide_EnhancedAttack.png");
	tutorialGraph[11] = Novice::LoadTexture("./resources/graph/tutorial/12_Guide_EAttck.png");
	tutorialGraph[12] = Novice::LoadTexture("./resources/graph/tutorial/13_guide_machinehp.png");
	tutorialGraph[13] = Novice::LoadTexture("./resources/graph/tutorial/14_guide_machinerepair.png");

	int activeTutorial = false;
	int onceActive = false;
	int endTutorialAnim = false;
	int isEndTutorialAnim = false;
	int activeTutorialGraph = 0;

	easing tutorialUI = {

		kWindowWidth / 2, -128.0f,
		kWindowWidth / 2, -128.0f,
		kWindowWidth / 2, 400.0f,
		0, 256,
		0, 256,
		1920, 256,
		0.0f,
		0.0f

	};

	int activeTutorialTime = 120.0f;
	int defActiveTutorialTime = 120.0f;

#pragma endregion

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
		INITIALIZE

	};

	int scene = TITLE;

	int goGameScene = false;
	int goInitializeScene = false;

#pragma endregion
#pragma region スコア

	int score = 0;
	int tempScore = 0;
	int eachScore[7] = {0};

	vector2 scoreUIPosOrigin = { 0, 0 };

	int scoreNumberSize = 96;
	int scoreNumberSpace = scoreNumberSize / 2;

	vector2 resultScoreUIPosOrigin = { 0, 0 };
	int resultScoreNumberSize = 256;
	int resultScoreNumberSpace = resultScoreNumberSize / 2;

	int addScore = 100;
	int defAddScore = 100;

	int combo = 0;
	int tempCombo = 0;
	int eachCombo[3] = { 0 };

	vector2 comboUIPosOrigin = { 0, 0 };
	vector2 resultComboUIPosOrigin = { 0, 0 };

	int comboNumberSize = 256;
	int comboNumberSpace = comboNumberSize / 2;

	int tenCombo = 0;
	int startCombo = 10;

	Gage comboReceptionGage = {

		0.0f, 0.0f,
		0.0f, 0.0f,
		WHITE

	};

	float comboReceptionTime = 120.0f;
	float defComboReceptionTime = 120.0f;

	vector2 MagnificationUIPosOrigin = { 0, 0 };
	float scoreMagnification = 1.0f;
	float comboMagnification = 1.0f;
	int tempMagnification = 0;
	int eachMagnification[4] = { 0 };

	int MagnificationNumberSize = 64;
	int MagnificationNumberSpace = MagnificationNumberSize / 2;

#pragma endregion

#pragma region 乱数 

	unsigned int currentTime = time(nullptr);

	currentTime = time(nullptr);
	srand(currentTime);

	unsigned int effectTime = time(nullptr);
	srand(effectTime);

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

		kWindowWidth * 1.5f, kWindowHeight - 160.0f, //translate x, y
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
		512, //graphRadius

		WHITE

	};

	int flashGraph = Novice::LoadTexture("./resources/graph/player/flush.png");

	int playFlashEffect = false;
	int flashEffectFrame = 0;

	int chargeGageGraph = Novice::LoadTexture("./resources/graph/player/ChargeGage.png");

	Gage chargeGage{

		player.translate.x - player.radius, player.translate.y + player.radius / 2,
		0.0f, 0.0f,
		0x00fa9aFF

	};

	int playerDirectionGraph = Novice::LoadTexture("./resources/graph/player/playerDirection.png");

	Quad playerPoint = {

		-player.radius / 2, -player.radius / 2,
		player.radius / 2, -player.radius / 2,
		-player.radius / 2, player.radius / 2,
		player.radius / 2, player.radius / 2

	};

	Quad playerRotate = {

		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f

	};

	Quad playerDirectionOrigin = {

		player.radius * 0.75f, -player.radius / 3.0f,
		player.radius * 1.25f, -player.radius / 3.0f,
		player.radius * 0.75f, player.radius / 3.0f,
		player.radius * 1.25f, player.radius / 3.0f

	};

	Quad playerDirection = {

		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f

	};

	float theta = 0.0f;

	float moveSpeed = 0.0f;

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
	float defChargeCoolTime = 10.0f;

	int enhanceSpeed = false;

	const int maxEnhancedAttack = 5;

	int shockWaveGraph = Novice::LoadTexture("./resources/graph/player/shockwave.png");

	vector2 shockOrigin[maxEnhancedAttack];
	float shockRadius[maxEnhancedAttack];
	float maxShockRadius = 500;

	float shockTime[maxEnhancedAttack] = {0};

	int canEnhancedAttack = false;
	int doEnhancedAttack = false;
	int isEnhancedAttack[maxEnhancedAttack];

	for (int i = 0; i < maxEnhancedAttack; i++) {

		shockOrigin[i] = {0.0f, 0.0f};
		shockRadius[i] = 0.0f;

		isEnhancedAttack[i] = false;

	}

#pragma endregion
#pragma region 味方
	/******** 味方 **********/
	chara ally{

		kWindowWidth * 1.5f, kWindowHeight, //translate x, y
		0.0f, 0.0f, //moveDirection x, y
		0.0f, //vectorLength

		128.0f, //radius
		0.0f,

		20.0f, //speed
		5.0f, //defSpeed

		true,
		500, //HP

		5, //damage

		Novice::LoadTexture("./resources/graph/decoy/decoy.png"), //graph
		512, //graphRadius

		WHITE

	};

	int putDecoy = false;
	int canCollectDecoy = false;

	int deadDecoy = false;

	int allyRadius = 128;

	Quad decoyPoint = {

		-allyRadius / 2, -allyRadius / 2,
		allyRadius / 2, -allyRadius / 2,
		-allyRadius / 2, allyRadius / 2,
		allyRadius / 2, allyRadius / 2

	};

	Quad decoyRotate = {

		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 0.0f

	};

	int decoyHPGraph = Novice::LoadTexture("./resources/graph/decoy/HP.png");

	Gage decoyHPGage = {

		0, 0,
		32, 0,
		0x00ff7fFF

	};

	Distance p2d = {

		0.0f, 0.0f,
		0.0f

	};

	Distance e2d = {

		0.0f, 0.0f,
		0.0f

	};
#pragma endregion

#pragma region 敵

	const int kMaxEnemy = 250;
	chara enemy[kMaxEnemy];
	Distance e2e[kMaxEnemy];
	Distance ef2e[kMaxEnemy];
	Distance At2e[kMaxEnemy];

	Quad EnemyRotate[kMaxEnemy];

	enum EnemyType
	{

		FOLLOW,
		RUSH,
		AWAY

	};

	int isNockBacking[kMaxEnemy];
	float nockBackSpeed[kMaxEnemy];

	int enemyType[kMaxEnemy];

	int enemyNockBack[kMaxEnemy];

	int deadEnemy[kMaxEnemy];

	float enemyAmplitude[kMaxEnemy];
	float enemyAmplitudeStrength[kMaxEnemy];

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
			256,

			WHITE

		};

		enemyType[i] = FOLLOW;

		EnemyRotate[i] = {

			-enemy[i].radius / 2, -enemy[i].radius / 2,
			enemy[i].radius / 2, -enemy[i].radius / 2,
			-enemy[i].radius / 2, enemy[i].radius / 2,
			enemy[i].radius / 2, enemy[i].radius / 2

		};

		e2e[i] = {

			0.0f, 0.0f,
			0.0f

		};

		At2e[i] = {

			0.0f, 0.0f,
			0.0f

		};

		enemyNockBack[i] = 0.0f;

		isNockBacking[i] = false;
		nockBackSpeed[i] = 0.0f;

		enemyAmplitude[i] = 0.0f;
		enemyAmplitudeStrength[i] = 0.0f;

		deadEnemy[i] = false;

		ef2e[i] = {

			0.0f,0.0f,
			0.0f

		};

	}

	int killEnemy = 0;
	int tempKill = 0;
	int eachKillEnemy[4];

	int killEnemyNumberSize = 256;
	int killEnemyNumberSpace = killEnemyNumberSize / 2;

	Distance e2p{

		0.0f, 0.0f,
		0.0f

	};

	Quad EnemyPoint = {

		-enemy[0].radius / 2, -enemy[0].radius / 2,
		enemy[0].radius / 2, -enemy[0].radius / 2,
			-enemy[0].radius / 2, enemy[0].radius / 2,
			enemy[0].radius / 2, enemy[0].radius / 2

	};

#pragma endregion

#pragma region 機械

	chara Machine{

		kWindowWidth * 1.5f, kWindowHeight, //translate x, y
		0.0f, 0.0f, //moveDirection x, y
		0.0f, //vectorLength

		512.0f, //radius
		0.0f,

		0.0f, //speed
		50.0f, //defSpeed

		true,
		1000, //HP

		1, //damage

		Novice::LoadTexture("./resources/graph/machine/Machine.png"), //graph
		512, //graphRadius

		WHITE

	};

	Distance m2p = {

		0.0f, 0.0f,
		0.0f

	};

	Distance m2d = {

		0.0f, 0.0f,
		0.0f

	};

	Gage machineGage = {

		0.0f, 0.0f,
		497, 0,
		0x90ee90FF

	};

	int tempMachineEnergy = 0;

	int isRepairing = false;
	int repairComplete = false;

	unsigned int circleColor = RED;
	int collectEnergyRange = Machine.radius;

#pragma endregion
#pragma region エネルギー

	const int kMaxEnergy = kMaxEnemy;
	chara energy[kMaxEnergy];

	Distance en2p[kMaxEnergy];

	float collectRange[kMaxEnergy];

	int followPlayer[kMaxEnergy];

	int colletCount[kMaxEnergy];


	for (int i = 0; i < kMaxEnergy; i++) {

		energy[i] = {

			0.0f, 0.0f,
			0.0f, 0.0f,
			0.0f,

			32.0f,
			0.0f,

			3.0f,
			3.0f,

			false,
			1,
			1,

			Novice::LoadTexture("./resources/graph/energy/Energy.png"),
			128,

			WHITE

		};

		collectRange[i] = energy[i].radius * 25.0f;

		followPlayer[i] = false;

		colletCount[i] = 0;

		en2p[i] = {

			0.0f, 0.0f,
			0.0f

		};

	}

	int energyAmount = 0;
	int maxEnergyAmount = 1000;

	int energyIconGraph = Novice::LoadTexture("./resources/graph/energy/EnergyIcon.png");

	Gage energyAmountGage = {

		0, 0,
		0, 0,
		0x90ee90FF

	};

#pragma endregion

#pragma region スポーン

	vector2 spawnPoint[4];

	spawnPoint[0] = { 0.0f, 0.0f };
	spawnPoint[1] = { 0.0f, 0.0f };
	spawnPoint[2] = { 0.0f, 0.0f };
	spawnPoint[3] = { 0.0f, 0.0f };

	int spawnTheta = 0;

	float spawnTimer = 60.0f;
	float defSpawnTimer = 30.0f;

	int canSpawn = false;
	int enemySpawnPoint = 0;

	int canSpawnRushEnemy = false;
	int spawnRushEnemy = false;
	int spawnRushEnemyTimer = 300;

	int spawnCounter = 0;
	int nowSpawnCounter = 0;
	int maxOnceSpawn = 10;

#pragma endregion
#pragma region エフェクト
	/******** チャージエフェクト **********/
	const int chargeEffectMax = 16;
	effect chargeEffect[chargeEffectMax];

	for (int i = 0; i < chargeEffectMax; i++)
	{
		chargeEffect[i].isActive = false;
		chargeEffect[i].vectorLength = player.radius * 2;
		chargeEffect[i].moveDirection.x = 0;
		chargeEffect[i].moveDirection.y = 0;
		chargeEffect[i].translate.x = chargeEffect[i].moveDirection.x * chargeEffect[i].vectorLength;
		chargeEffect[i].translate.y = chargeEffect[i].moveDirection.y * chargeEffect[i].vectorLength;
		chargeEffect[i].carentAlpha = 0xBA;
		chargeEffect[i].radius = 96;
		chargeEffect[i].graph = Novice::LoadTexture("./resources/graph/effect/effect.png");
		chargeEffect[i].graphRadius = 512;
	};

	/******** エフェクト(残像) **********/
	const int afterimageMax = 30;

	trajectory afterimage[afterimageMax];

	Distance ef2en[afterimageMax];

	for (int i = 0; i < afterimageMax; i++)
	{
		afterimage[i].isActive = false;
		afterimage[i].translate.x = player.translate.x;
		afterimage[i].translate.y = player.translate.y;
		afterimage[i].carentAlpha = 0xBA;
		afterimage[i].radius = 128 / 2;
		afterimage[i].graph = Novice::LoadTexture("./resources/graph/player/player.png");
		afterimage[i].graphRadius = player.graphRadius;

		ef2en[i] = {

			0.0f,0.0f,
			0.0f

		};
	};

	/******** エフェクト(敵死亡) **********/

	const int deathMaxEffect = 8;
	const int playMaxDeathEffect = kMaxEnemy;
	effect deathEffect[playMaxDeathEffect][deathMaxEffect];
	int playDeathEffect[playMaxDeathEffect];

	for (int i = 0; i < playMaxDeathEffect; i++)
	{
		playDeathEffect[i] = false;
		for (int j = 0; j < deathMaxEffect; j++)
		{
			deathEffect[i][j].isActive = false;
			deathEffect[i][j].vectorLength = 0;
			deathEffect[i][j].moveDirection.x = 0;
			deathEffect[i][j].moveDirection.y = 0;
			deathEffect[i][j].translate = enemy[i].translate;
			deathEffect[i][j].carentAlpha = 0xFF;
			deathEffect[i][j].radius = 16;
			deathEffect[i][j].graph = Novice::LoadTexture("./resources/graph/effect/deathEffect.png");
			deathEffect[i][j].graphRadius = 128;
		}

	};

	/******** エフェクト(デコイ死亡) **********/

	int playDeadDecoyEffect = false;
	int endDeadDecoyEffect = false;
	const int kMaxdeadDecoyEffect = 8;

	effect deadDecoyEffect[kMaxdeadDecoyEffect];

	for (int i = 0; i < kMaxdeadDecoyEffect; i++)
	{
		deadDecoyEffect[i].isActive = false;
		deadDecoyEffect[i].vectorLength = 0;
		deadDecoyEffect[i].moveDirection.x = 0;
		deadDecoyEffect[i].moveDirection.y = 0;
		deadDecoyEffect[i].translate = ally.translate;
		deadDecoyEffect[i].carentAlpha = 0xFF;
		deadDecoyEffect[i].radius = 64;
		deadDecoyEffect[i].graph = Novice::LoadTexture("./resources/graph/effect/decoyDeadEffect.png");
		deadDecoyEffect[i].graphRadius = 128;
	};



#pragma endregion

#pragma region リザルト画面

	int resultUIPlayAnim = false;

	easing resultUI = {
		kWindowWidth / 2, 0.0f,
		kWindowWidth / 2, 1200,
		kWindowWidth / 2, 900,
		0, 272,
		0, 272,
		1280, 272,
		0.0f,
		0.0f
	};

	int resultGraph = Novice::LoadTexture("./resources/graph/result/result.png");

	int scorePlayAnim = false;

	easing scoreUI = {

		-256 * 7, 600,
		-256 * 7, 600,
		1000, 600,
		256, 256,
		256, 256,
		256, 256,
		0.0f,
		0.0f

	};

	int killUIPlayAnim = false;

	easing killUI = {

		-256 * 4, 300,
		-256 * 4, 300,
		1000 + 256 * 1.5f, 300,
		256, 256,
		256, 256,
		256, 256,
		0.0f,
		0.0f

	};

	int endUIAnim = false;

#pragma endregion

	int White1x1 = Novice::LoadTexture("white1x1.png");

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

		/*********************************
			スクリーン関係ここから
		*********************************/

		#pragma region スクリーン

		/******** フルスクリーン **********/
		if (keys[DIK_LCONTROL] && !preKeys[DIK_LCONTROL]) {

			if (fullScreen == true) {

				Novice::SetWindowMode(kWindowed);
				fullScreen = false;

			}
			else {

				Novice::SetWindowMode(kFullscreen);
				fullScreen = true;

			}

		}

		if (fadeIn == true) {

			currentFadeAlpha -= 0x03;

			if (currentFadeAlpha > 0xFF) {

				currentFadeAlpha = 0x00;

			}

		}

		else {

			currentFadeAlpha += 0x03;

			if (currentFadeAlpha > 0xFF) {

				currentFadeAlpha = 0xFF;

			}

		}

		if (blackout == true) {

			currentBlackOutAlpha += 0x03;

			if (currentBlackOutAlpha > 0xEE) {

				currentBlackOutAlpha = 0xEE;

			}

		}
		else {

			currentBlackOutAlpha -= 0x03;

			if (currentBlackOutAlpha > 0xEE) {

				currentBlackOutAlpha = 0x00;

			}

		}

#pragma endregion

		/*********************************
			スクリーン関係ここまで
		*********************************/

		switch (scene)
		{
		case TITLE:

		#pragma region シーン遷移

			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {

				fadeIn = false;
				goGameScene = true;

			}

			if (goGameScene == true) {

				if (currentFadeAlpha == 0xFF) {

					scene++;

				}

			}

#pragma endregion

			break;
		case GAME:

		#pragma region タイマーUI

			gameMinutesTimer = gameTimer / 3600;
			recGameMinutesTimer = gameMinutesTimer;

			gameSecondsTimer = (gameTimer % 3600) / 60;
			recGameSecondsTimer = gameSecondsTimer;

			secondsTimerPosOrigin.x = player.translate.x - numberSize / 4;
			secondsTimerPosOrigin.y = player.translate.y - player.radius * 3.0f;

			for (int i = 0; i <= 1; i++) {

				if (i == 0) {

					eachSec[i] = recGameSecondsTimer / 10;
					recGameSecondsTimer = recGameSecondsTimer % 10;

				}
				if (i == 1) {

					eachSec[i] = recGameSecondsTimer;

				}

			}

		#pragma endregion
		#pragma region スコアUI

			scoreUIPosOrigin.x = player.translate.x + numberSize - numberSize * 1.55;
			scoreUIPosOrigin.y = player.translate.y + player.radius * 2.0f;

			for (int i = 0; i < 7; i++) {

				if (i == 0) {
					tempScore = score;
					eachScore[i] = tempScore / 1000000;
					tempScore = tempScore % 10000000;
				}
				if (i == 1) {
					eachScore[i] = tempScore / 100000;
					tempScore = tempScore % 100000;
				}
				if (i == 2) {
					eachScore[i] = tempScore / 10000;
					tempScore = tempScore % 10000;
				}
				if (i == 3) {
					eachScore[i] = tempScore / 1000;
					tempScore = tempScore % 1000;
				}
				if (i == 4) {
					eachScore[i] = tempScore / 100;
					tempScore = tempScore % 100;
				}
				if (i == 5) {
					eachScore[i] = tempScore / 10;
					tempScore = tempScore % 10;
				}
				if (i == 6) {
					eachScore[i] = tempScore / 10;
				}

			}

		#pragma endregion
		#pragma region コンボUI

			comboUIPosOrigin.x = player.translate.x - numberSize / 2.0f;
			comboUIPosOrigin.y = player.translate.y + player.radius * 3.25f;

			for (int i = 0; i < 3; i++) {

				if (i == 0) {
					tempCombo = combo;
					eachCombo[i] = tempCombo / 100;
					tempCombo = tempCombo % 100;
				}
				if (i == 1) {
					eachCombo[i] = tempCombo / 10;
					tempCombo = tempCombo % 10;
				}
				if (i == 2) {
					eachCombo[i] = tempCombo;
				}

			}
			
			comboReceptionGage.length.x = comboReceptionTime * 1.5f;
			comboReceptionGage.length.y = 3.5f;
			comboReceptionGage.translate.x = player.translate.x;
			comboReceptionGage.translate.y = player.translate.y + 310;

			MagnificationUIPosOrigin.x = player.translate.x + MagnificationNumberSpace * 7.5f;
			MagnificationUIPosOrigin.y = player.translate.y + player.radius * 1.9f;

			for (int i = 0; i < 4; i++) {

				if (i == 0) {

					if (9.99f > comboMagnification * scoreMagnification) {
						tempMagnification = (comboMagnification * scoreMagnification) * 100;
					}
					else {

						tempMagnification = 999;

					}
					eachMagnification[i] = tempMagnification / 100;
					tempMagnification = tempMagnification % 100;
				}
				if (i == 1) {
					
					eachMagnification[i] = DotGraph;

				}
				if (i == 2) {
					eachMagnification[i] = tempMagnification / 10;
					tempMagnification = tempMagnification % 10;
				}
				if (i == 3) {
					eachMagnification[i] = tempMagnification;
				}

			}

		#pragma endregion
		#pragma region デコイHPゲージ

			decoyHPGage.translate.x = player.translate.x - 230;
			decoyHPGage.translate.y = player.translate.y - 250;

			if (decoyHPGage.length.x > 0) {

				decoyHPGage.length.x = ally.HP;

			}
			else {

				decoyHPGage.length.x = 0;

			}

#pragma endregion
		#pragma region エネルギーゲージ

			energyAmountGage.translate.x = player.translate.x + 500;
			energyAmountGage.translate.y = player.translate.y - 300;

			if (energyAmountGage.length.y > 0) {

				energyAmountGage.length.y = -1;

			}
			else {

				energyAmountGage.length.y = -energyAmount / 1.5f;

			}

		#pragma endregion

		#pragma region 倒した敵数を表示

			for (int i = 0; i < 4; i++) {

				if (i == 0) {
					tempKill = killEnemy;
					eachKillEnemy[i] = tempKill / 1000;
					tempKill = tempKill % 1000;
				}
				if (i == 1) {
					eachKillEnemy[i] = tempKill / 100;
					tempKill = tempKill % 100;
				}
				if (i == 2) {
					eachKillEnemy[i] = tempKill / 10;
					tempKill = tempKill % 10;
				}
				if (i == 3) {
					eachKillEnemy[i] = tempKill;
				}

			}

#pragma endregion

		#pragma region チュートリアル

			if (tutorialStart == false) {

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

				playerRotate.q1.x = playerPoint.q1.x * cosf(player.theta) - playerPoint.q1.y * -sinf(player.theta) + player.translate.x;
				playerRotate.q1.y = playerPoint.q1.y * cosf(player.theta) + playerPoint.q1.x * -sinf(player.theta) + player.translate.y;

				playerRotate.q2.x = playerPoint.q2.x * cosf(player.theta) - playerPoint.q2.y * -sinf(player.theta) + player.translate.x;
				playerRotate.q2.y = playerPoint.q2.y * cosf(player.theta) + playerPoint.q2.x * -sinf(player.theta) + player.translate.y;

				playerRotate.q3.x = playerPoint.q3.x * cosf(player.theta) - playerPoint.q3.y * -sinf(player.theta) + player.translate.x;
				playerRotate.q3.y = playerPoint.q3.y * cosf(player.theta) + playerPoint.q3.x * -sinf(player.theta) + player.translate.y;

				playerRotate.q4.x = playerPoint.q4.x * cosf(player.theta) - playerPoint.q4.y * -sinf(player.theta) + player.translate.x;
				playerRotate.q4.y = playerPoint.q4.y * cosf(player.theta) + playerPoint.q4.x * -sinf(player.theta) + player.translate.y;

				playerDirection.q1.x = playerDirectionOrigin.q1.x * cosf(player.theta) - playerDirectionOrigin.q1.y * -sinf(player.theta) + player.translate.x;
				playerDirection.q1.y = playerDirectionOrigin.q1.y * cosf(player.theta) + playerDirectionOrigin.q1.x * -sinf(player.theta) + player.translate.y;

				playerDirection.q2.x = playerDirectionOrigin.q2.x * cosf(player.theta) - playerDirectionOrigin.q2.y * -sinf(player.theta) + player.translate.x;
				playerDirection.q2.y = playerDirectionOrigin.q2.y * cosf(player.theta) + playerDirectionOrigin.q2.x * -sinf(player.theta) + player.translate.y;

				playerDirection.q3.x = playerDirectionOrigin.q3.x * cosf(player.theta) - playerDirectionOrigin.q3.y * -sinf(player.theta) + player.translate.x;
				playerDirection.q3.y = playerDirectionOrigin.q3.y * cosf(player.theta) + playerDirectionOrigin.q3.x * -sinf(player.theta) + player.translate.y;

				playerDirection.q4.x = playerDirectionOrigin.q4.x * cosf(player.theta) - playerDirectionOrigin.q4.y * -sinf(player.theta) + player.translate.x;
				playerDirection.q4.y = playerDirectionOrigin.q4.y * cosf(player.theta) + playerDirectionOrigin.q4.x * -sinf(player.theta) + player.translate.y;

				machineGage.length.y = -Machine.HP / 2.03;

				fadeIn = true;

				if (currentFadeAlpha == 0x00) {

					tutorialStart = true;

				}

			}

			if (tutorialStart == true && gameFinish == false) {

				if (tutorialFinish == false) {

					if (keys[DIK_W] && !preKeys[DIK_W]) {

						tutorialFinish = true;

					}

				}

			#pragma region プレイヤー

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
				if (tutorialMove == true) {

					chargeGage.translate.x = player.translate.x - player.radius / 2;
					chargeGage.translate.y = player.translate.y + player.radius / 1.5f;

					if (chargeCoolTime > 0.0f) {

						chargeCoolTime--;
						canCharge = false;

					}
					else {

						canCharge = true;

					}

					//スペースキー長押し
					if (keys[DIK_SPACE]) {

						//チャージ状態true
						isCharging = true;

					}
					else {

						//チャージ状態false
						isCharging = false;
						chargeGage.length.x = 0;

					}

					if (isCharging == true) {

						moveSpeed -= 0.1f;
						player.translate.x += (cosf(player.theta) * moveSpeed);
						player.translate.y += -(sinf(player.theta) * moveSpeed);

						if (moveSpeed < 0) {

							moveSpeed = 0;

						}

					}
					else if (isAttacking == false) {

						moveSpeed = 5.0f;

						player.translate.x += (cosf(player.theta) * moveSpeed);
						player.translate.y += -(sinf(player.theta) * moveSpeed);

					}

					if (keys[DIK_RIGHT] || keys[DIK_D]) {

						player.theta += 0.1f;

					}

					else if (keys[DIK_LEFT] || keys[DIK_A]) {

						player.theta -= 0.1f;

					}

					if (theta >= 6.0f) {

						player.theta = 0.0f;

						if (tutorial == ANGLE && tutorialAngle == false) {

							tutorialAngle = true;

						}

					}
					else if (theta < 0.0f) {

						player.theta = 5.9f;

						if (tutorial == ANGLE && tutorialAngle == false) {

							tutorialAngle = true;

						}

					}

					playerRotate.q1.x = playerPoint.q1.x * cosf(player.theta) - playerPoint.q1.y * -sinf(player.theta) + player.translate.x;
					playerRotate.q1.y = playerPoint.q1.y * cosf(player.theta) + playerPoint.q1.x * -sinf(player.theta) + player.translate.y;

					playerRotate.q2.x = playerPoint.q2.x * cosf(player.theta) - playerPoint.q2.y * -sinf(player.theta) + player.translate.x;
					playerRotate.q2.y = playerPoint.q2.y * cosf(player.theta) + playerPoint.q2.x * -sinf(player.theta) + player.translate.y;

					playerRotate.q3.x = playerPoint.q3.x * cosf(player.theta) - playerPoint.q3.y * -sinf(player.theta) + player.translate.x;
					playerRotate.q3.y = playerPoint.q3.y * cosf(player.theta) + playerPoint.q3.x * -sinf(player.theta) + player.translate.y;

					playerRotate.q4.x = playerPoint.q4.x * cosf(player.theta) - playerPoint.q4.y * -sinf(player.theta) + player.translate.x;
					playerRotate.q4.y = playerPoint.q4.y * cosf(player.theta) + playerPoint.q4.x * -sinf(player.theta) + player.translate.y;

					playerDirection.q1.x = playerDirectionOrigin.q1.x * cosf(player.theta) - playerDirectionOrigin.q1.y * -sinf(player.theta) + player.translate.x;
					playerDirection.q1.y = playerDirectionOrigin.q1.y * cosf(player.theta) + playerDirectionOrigin.q1.x * -sinf(player.theta) + player.translate.y;

					playerDirection.q2.x = playerDirectionOrigin.q2.x * cosf(player.theta) - playerDirectionOrigin.q2.y * -sinf(player.theta) + player.translate.x;
					playerDirection.q2.y = playerDirectionOrigin.q2.y * cosf(player.theta) + playerDirectionOrigin.q2.x * -sinf(player.theta) + player.translate.y;

					playerDirection.q3.x = playerDirectionOrigin.q3.x * cosf(player.theta) - playerDirectionOrigin.q3.y * -sinf(player.theta) + player.translate.x;
					playerDirection.q3.y = playerDirectionOrigin.q3.y * cosf(player.theta) + playerDirectionOrigin.q3.x * -sinf(player.theta) + player.translate.y;

					playerDirection.q4.x = playerDirectionOrigin.q4.x * cosf(player.theta) - playerDirectionOrigin.q4.y * -sinf(player.theta) + player.translate.x;
					playerDirection.q4.y = playerDirectionOrigin.q4.y * cosf(player.theta) + playerDirectionOrigin.q4.x * -sinf(player.theta) + player.translate.y;

					//チャージ状態trueの時
					if (isCharging == true && isAttacking == false && canCharge == true) {

						if (chargePower < maxPower) {

							//チャージ
							chargePower += 5.0f;
							chargeGage.length.x = chargePower * 2.14f;

						}
						else {

							//一定の値を超えたら固定
							if (putDecoy == true) {

								canEnhancedAttack = true;
								playFlashEffect = true;

							}
							chargePower = maxPower;

						}
						/******** チャージエフェクト **********/
						for (int i = 0; i < chargeEffectMax; i++)
						{
							//エフェクトが出ていない
							if (!chargeEffect[i].isActive)
							{

								chargeEffect[i].translate.x = player.translate.x;
								chargeEffect[i].translate.y = player.translate.y;
								chargeEffect[i].isActive = true;
								chargeEffect[i].carentAlpha = 0xAA;
								chargeEffect[i].vectorLength = player.radius;

								if (rand() % 8 == 0)
								{
									chargeEffect[i].moveDirection.x = 0;
									chargeEffect[i].moveDirection.y = -1;
								}
								else if (rand() % 8 == 1) {
									chargeEffect[i].moveDirection.x = -1;
									chargeEffect[i].moveDirection.y = -1;
								}
								else if (rand() % 8 == 2) {
									chargeEffect[i].moveDirection.x = 1;
									chargeEffect[i].moveDirection.y = 0;
								}
								else if (rand() % 8 == 3) {
									chargeEffect[i].moveDirection.x = -1;
									chargeEffect[i].moveDirection.y = 1;
								}
								else if (rand() % 8 == 4) {
									chargeEffect[i].moveDirection.x = 1;
									chargeEffect[i].moveDirection.y = 1;
								}
								else if (rand() % 8 == 5) {
									chargeEffect[i].moveDirection.x = 1;
									chargeEffect[i].moveDirection.y = -1;
								}
								else if (rand() % 8 == 6) {
									chargeEffect[i].moveDirection.x = -1;
									chargeEffect[i].moveDirection.y = 0;
								}
								else if (rand() % 8 == 7) {
									chargeEffect[i].moveDirection.x = 0;
									chargeEffect[i].moveDirection.y = 1;
								}
								break;
							}
							//エフェクトが出ている
							else {
								chargeEffect[i].vectorLength -= 4;
								if (chargeEffect[i].vectorLength <= 0) {
									chargeEffect[i].isActive = false;
								}
							}
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

							if (canEnhancedAttack == true) {

								doEnhancedAttack = true;
								canEnhancedAttack = false;

							}

							isAttacking = false;

						}

						//動いた時にエフェクトを薄くしていく
						for (int i = 0; i < chargeEffectMax; i++)
						{
							if (chargeEffect[i].isActive)
							{
								chargeEffect[i].carentAlpha -= 0x11;

								if (chargeEffect[i].carentAlpha <= 0) {

									chargeEffect[i].isActive = false;

								}
							}
						}
					}

					if (!keys[DIK_SPACE] && preKeys[DIK_SPACE]) {

						if (isAttacking == false) {

							isAttacking = true;

						}

					}

					for (int i = 0; i < maxEnhancedAttack; i++) {

						if (isEnhancedAttack[i] == true) {

							if (shockRadius[i] < maxShockRadius) {

								shockRadius[i] += 25.0f;

							}
							else {

								shockRadius[i] = 0;

								shockTime[i] = 0;

								isEnhancedAttack[i] = false;
							}

						}
						else {

							if (doEnhancedAttack == true) {

								shockOrigin[i] = player.translate;

								playFlashEffect = false;
								flashEffectFrame = 0;
								isEnhancedAttack[i] = true;
								doEnhancedAttack = false;
							}

						}

					}

					if (playFlashEffect == true) {

						if (flashEffectFrame < 4) {

							if (flame > 3) {

								flashEffectFrame++;
								flame = 0;
							}
							flame++;

						}
						else {

							flashEffectFrame = 0;

						}

					}

					if (isAttacking == true) {

						chargeCoolTime = defChargeCoolTime;

						if (enhanceSpeed == true) {

							player.translate.x += (cosf(player.theta) * player.speed * 1.25f * chargePower / 3.0f);
							player.translate.y += -(sinf(player.theta) * player.speed * 1.25f * chargePower / 3.0f);

						}
						else {

							player.translate.x += (cosf(player.theta) * player.speed * chargePower / 3.0f);
							player.translate.y += -(sinf(player.theta) * player.speed * chargePower / 3.0f);

						}

						chargePower--;

						//残像
						for (int i = 0; i < afterimageMax; i++)
						{
							//残像が出ていない
							if (!afterimage[i].isActive)
							{
								afterimage[i].isActive = true;
								afterimage[i].translate.x = player.translate.x;
								afterimage[i].translate.y = player.translate.y;
								afterimage[i].carentAlpha = 0xA0;
								afterimage[i].radius = 128;
								break;
							}
							//出てる
							else
							{
								afterimage[i].carentAlpha -= 0x0A;
								if (afterimage[i].carentAlpha <= 0x00) {
									afterimage[i].isActive = false;
								}
							}
						}
					}
					//動いてないとき
					else
					{
						for (int i = 0; i < afterimageMax; i++)
						{
							if (afterimage[i].isActive)
							{
								afterimage[i].carentAlpha -= 0x0A;
								if (afterimage[i].carentAlpha <= 0x00) {
									afterimage[i].isActive = false;
								}
							}
						}
					}


				}
				
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

#pragma endregion
			#pragma region 味方

				#pragma region デコイ設置
				if (tutorialDecoy == true) {

					if (keys[DIK_S] && !preKeys[DIK_S] || keys[DIK_DOWNARROW] && !preKeys[DIK_DOWNARROW]) {

						ally.HP -= 5;

						putDecoy = true;
						enhanceSpeed = true;

					}

				}
				
#pragma endregion

				#pragma region デコイの回転処理

				decoyRotate.q1.x = decoyPoint.q1.x * cosf(player.theta) - decoyPoint.q1.y * -sinf(player.theta) + player.translate.x;
				decoyRotate.q1.y = decoyPoint.q1.y * cosf(player.theta) + decoyPoint.q1.x * -sinf(player.theta) + player.translate.y;

				decoyRotate.q2.x = decoyPoint.q2.x * cosf(player.theta) - decoyPoint.q2.y * -sinf(player.theta) + player.translate.x;
				decoyRotate.q2.y = decoyPoint.q2.y * cosf(player.theta) + decoyPoint.q2.x * -sinf(player.theta) + player.translate.y;

				decoyRotate.q3.x = decoyPoint.q3.x * cosf(player.theta) - decoyPoint.q3.y * -sinf(player.theta) + player.translate.x;
				decoyRotate.q3.y = decoyPoint.q3.y * cosf(player.theta) + decoyPoint.q3.x * -sinf(player.theta) + player.translate.y;

				decoyRotate.q4.x = decoyPoint.q4.x * cosf(player.theta) - decoyPoint.q4.y * -sinf(player.theta) + player.translate.x;
				decoyRotate.q4.y = decoyPoint.q4.y * cosf(player.theta) + decoyPoint.q4.x * -sinf(player.theta) + player.translate.y;

#pragma endregion

				#pragma region プレイヤーが強化攻撃をできるか
				if (putDecoy == false && isAttacking == false) {

					enhanceSpeed = false;

				}
#pragma endregion

				#pragma region プレイヤー追従

				if (putDecoy == false) {

					ally.theta = atan2(player.translate.y - ally.translate.y, player.translate.x - ally.translate.x);

					if (ally.theta <= 0) {

						ally.theta *= -1;

					}
					else {

						float def = M_PI - ally.theta;

						ally.theta = def + M_PI;

					}

					ally.translate.x += (cosf(ally.theta) * ally.speed);
					ally.translate.y += -(sinf(ally.theta) * ally.speed);

				}

#pragma endregion
				#pragma region プレイヤーとの衝突判定

				p2d.distance.x = player.translate.x - ally.translate.x;
				p2d.distance.y = player.translate.y - ally.translate.y;

				p2d.length = sqrt(pow(p2d.distance.x, 2) + pow(p2d.distance.y, 2));

				if (p2d.length <= player.radius / 2 + ally.radius / 2) {

					if (putDecoy == true) {

						if (canCollectDecoy == true && isRepairing == false) {

							putDecoy = false;
							repairComplete = false;

						}

					}
					else {

						canCollectDecoy = false;
						ally.translate = player.translate;

					}

				}
				else {

					canCollectDecoy = true;

				}

#pragma endregion

#pragma endregion
			#pragma region デコイ死亡エフェクト
				if (playDeadDecoyEffect && !endDeadDecoyEffect)
				{
					for (int i = 0; i < kMaxdeadDecoyEffect; i++)
					{
						//エフェクトが出ていない
						if (!deadDecoyEffect[i].isActive)
						{
							deadDecoyEffect[i].translate = ally.translate;
							deadDecoyEffect[i].isActive = true;
							deadDecoyEffect[i].carentAlpha = 0xFF;
							deadDecoyEffect[i].vectorLength = 0;
							ally.isAlive = false;


							if (i == 0)
							{
								deadDecoyEffect[i].moveDirection.x = 0;
								deadDecoyEffect[i].moveDirection.y = -1;
							}
							else if (i == 1) {
								deadDecoyEffect[i].moveDirection.x = -1;
								deadDecoyEffect[i].moveDirection.y = -1;
							}
							else if (i == 2) {
								deadDecoyEffect[i].moveDirection.x = 1;
								deadDecoyEffect[i].moveDirection.y = 0;
							}
							else if (i == 3) {
								deadDecoyEffect[i].moveDirection.x = -1;
								deadDecoyEffect[i].moveDirection.y = 1;
							}
							else if (i == 4) {
								deadDecoyEffect[i].moveDirection.x = 1;
								deadDecoyEffect[i].moveDirection.y = 1;
							}
							else if (i == 5) {
								deadDecoyEffect[i].moveDirection.x = 1;
								deadDecoyEffect[i].moveDirection.y = -1;
							}
							else if (i == 6) {
								deadDecoyEffect[i].moveDirection.x = -1;
								deadDecoyEffect[i].moveDirection.y = 0;
							}
							else if (i == 7) {
								deadDecoyEffect[i].moveDirection.x = 0;
								deadDecoyEffect[i].moveDirection.y = 1;
							}
							break;
						}
						//エフェクトが出ている
						else {
							deadDecoyEffect[i].vectorLength += 10;
							deadDecoyEffect[i].carentAlpha -= 0x08;
							if (deadDecoyEffect[i].carentAlpha <= 0x0C)
							{
								endDeadDecoyEffect = true;
							}
						}
					}
				}

				if (endDeadDecoyEffect == true) {

					gameFinish = true;

				}

#pragma endregion
			#pragma region 敵

				#pragma region スポーン地点設定

				//左上
				spawnPoint[0].x = player.translate.x - kWindowWidth / 2 - 64 / 2;
				spawnPoint[0].y = player.translate.y + kWindowHeight / 2 - 64 / 2;

				//左下
				spawnPoint[1].x = player.translate.x - kWindowWidth / 2 + 64 / 2;
				spawnPoint[1].y = player.translate.y - kWindowHeight / 2 - 64 / 2;

				//右上
				spawnPoint[2].x = player.translate.x + kWindowWidth / 2 + player.radius;
				spawnPoint[2].y = player.translate.y + kWindowHeight / 2 + player.radius;

				//右下
				spawnPoint[3].x = player.translate.x + kWindowWidth / 2 + player.radius;
				spawnPoint[3].y = player.translate.y - kWindowHeight / 2 - player.radius;

#pragma endregion

				#pragma region 敵メイン処理

				for (int i = 0; i < kMaxEnemy - 10; i++) {

					#pragma region 敵回転処理

					EnemyRotate[i].q1.x = EnemyPoint.q1.x * cosf(enemy[i].theta) - EnemyPoint.q1.y * -sinf(enemy[i].theta) + enemy[i].translate.x;
					EnemyRotate[i].q1.y = EnemyPoint.q1.y * cosf(enemy[i].theta) + EnemyPoint.q1.x * -sinf(enemy[i].theta) + enemy[i].translate.y;

					EnemyRotate[i].q2.x = EnemyPoint.q2.x * cosf(enemy[i].theta) - EnemyPoint.q2.y * -sinf(enemy[i].theta) + enemy[i].translate.x;
					EnemyRotate[i].q2.y = EnemyPoint.q2.y * cosf(enemy[i].theta) + EnemyPoint.q2.x * -sinf(enemy[i].theta) + enemy[i].translate.y;

					EnemyRotate[i].q3.x = EnemyPoint.q3.x * cosf(enemy[i].theta) - EnemyPoint.q3.y * -sinf(enemy[i].theta) + enemy[i].translate.x;
					EnemyRotate[i].q3.y = EnemyPoint.q3.y * cosf(enemy[i].theta) + EnemyPoint.q3.x * -sinf(enemy[i].theta) + enemy[i].translate.y;

					EnemyRotate[i].q4.x = EnemyPoint.q4.x * cosf(enemy[i].theta) - EnemyPoint.q4.y * -sinf(enemy[i].theta) + enemy[i].translate.x;
					EnemyRotate[i].q4.y = EnemyPoint.q4.y * cosf(enemy[i].theta) + EnemyPoint.q4.x * -sinf(enemy[i].theta) + enemy[i].translate.y;

#pragma endregion

					#pragma region 敵生存時処理
					if (enemy[i].isAlive == true) {

						#pragma region 敵タイプ
						if (isNockBacking[i] == false) {

							if (putDecoy == true) {

								enemy[i].theta = atan2(ally.translate.y - enemy[i].translate.y, ally.translate.x - enemy[i].translate.x);

							}
							else {

								enemy[i].theta = atan2(player.translate.y - enemy[i].translate.y, player.translate.x - enemy[i].translate.x);

							}

							if (enemy[i].theta <= 0) {

								enemy[i].theta *= -1;

							}
							else {

								float def = M_PI - enemy[i].theta;

								enemy[i].theta = def + M_PI;

							}

							enemy[i].translate.x += (cosf(enemy[i].theta) * enemy[i].speed);
							enemy[i].translate.y += -(sinf(enemy[i].theta) * enemy[i].speed);


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

						#pragma region プレイヤーとの衝突判定
						if (isAttacking == false) {

							if (isNockBacking[i] == false) {

								e2p.distance.x = enemy[i].translate.x - player.translate.x;
								e2p.distance.y = enemy[i].translate.y - player.translate.y;

								e2p.length = sqrt(pow(e2p.distance.x, 2) + pow(e2p.distance.y, 2));

								if (e2p.length <= enemy[i].radius / 2 + player.radius / 2) {

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

								enemy[i].HP -= player.damage;

							}

						}
#pragma endregion
						#pragma region デコイとの衝突判定

						e2d.distance.x = enemy[i].translate.x - ally.translate.x;
						e2d.distance.y = enemy[i].translate.y - ally.translate.y;

						e2d.length = sqrt(pow(e2d.distance.x, 2) + pow(e2d.distance.y, 2));

						if (putDecoy == true) {

							if (e2d.length <= enemy[i].radius / 2 + ally.radius / 2) {

								enemyNockBack[i] = rand();
								enemyNockBack[i] = enemyNockBack[i] % 360;

								enemyNockBack[i] = enemyNockBack[i] * (M_PI / 180.0f);

								isNockBacking[i] = true;
								nockBackSpeed[i] = 25.0f;

							}

						}

#pragma endregion
						#pragma region エフェクトとの衝突判定
						for (int j = 0; j < afterimageMax; j++) {

							if (afterimage[j].carentAlpha <= 0xA0 && afterimage[j].isActive == true && isAttacking == true) {

								ef2e[j].distance.x = afterimage[j].translate.x - enemy[i].translate.x;
								ef2e[j].distance.y = afterimage[j].translate.y - enemy[i].translate.y;

								ef2e[j].length = sqrt(pow(ef2e[j].distance.x, 2) + pow(ef2e[j].distance.y, 2));

								if (ef2e[j].length <= afterimage[j].radius / 2 + enemy[i].radius / 2) {
									enemy[i].HP -= player.damage;


								}

							}

						}
#pragma endregion

						#pragma region 強化攻撃の衝突判定
						for (int j = 0; j < maxEnhancedAttack; j++) {

							if (isEnhancedAttack[j] == true) {

								At2e[i].distance.x = enemy[i].translate.x - shockOrigin[j].x;
								At2e[i].distance.y = enemy[i].translate.y - shockOrigin[j].y;

								At2e[i].length = sqrt(pow(At2e[i].distance.x, 2) + pow(At2e[i].distance.y, 2));

								if (At2e[i].length <= shockRadius[j] + enemy[i].radius / 2) {

									enemy[i].HP -= 10;

								}

							}

						}
#pragma endregion


						#pragma region 死亡判定

						if (enemy[i].HP <= 0) {

							deadEnemy[i] = true;
							enemy[i].HP = 1;

						}

						if (deadEnemy[i] == true) {

							if (energy[i].isAlive == false) {

								energy[i].translate = enemy[i].translate;
								energy[i].isAlive = true;

							}

							if (playDeathEffect[i] == false) {

								deathEffect[i][0].translate = enemy[i].translate;
								deathEffect[i][1].translate = enemy[i].translate;
								deathEffect[i][2].translate = enemy[i].translate;
								deathEffect[i][3].translate = enemy[i].translate;
								deathEffect[i][4].translate = enemy[i].translate;
								deathEffect[i][5].translate = enemy[i].translate;
								deathEffect[i][6].translate = enemy[i].translate;
								deathEffect[i][7].translate = enemy[i].translate;
								playDeathEffect[i] = true;
							}

							enemy[i].translate.x = 0.0f;
							enemy[i].translate.y = 0.0f;

							comboReceptionTime = defComboReceptionTime;

							score += addScore * comboMagnification * scoreMagnification;

							if (combo < 999) {

								combo++;
								tenCombo++;

							}

							nowSpawnCounter--;

							killEnemy++;

							isNockBacking[i] = false;
							enemy[i].isAlive = false;

							deadEnemy[i] = false;

						}

#pragma endregion

					}
#pragma endregion
					#pragma region スポーン処理
					else {

						if (canSpawn == true) {

							if (spawnCounter < maxOnceSpawn) {

								spawnTheta = rand();
								spawnTheta = spawnTheta % 360;

								spawnTheta = spawnTheta * (M_PI / 180.0f);

								enemy[i].translate = player.translate;
								enemy[i].translate.x += (cosf(spawnTheta) * kWindowWidth);
								enemy[i].translate.y += -(sinf(spawnTheta) * kWindowHeight);

								enemy[i].speed = rand();
								enemy[i].speed = (int)enemy[i].speed % 3 + 1;

								nowSpawnCounter++;
								spawnCounter++;

								enemy[i].isAlive = true;

							}
							else {

								canSpawn = false;
								spawnTimer = defSpawnTimer;
								spawnCounter = 0;

							}

						}

					}
#pragma endregion

				}
#pragma endregion

#pragma endregion
			#pragma region 機械

				#pragma region エネルギー回収処理

				m2d.distance.x = Machine.translate.x - ally.translate.x;
				m2d.distance.y = Machine.translate.y - ally.translate.y;

				m2d.length = sqrt(pow(m2d.distance.x, 2) + pow(m2d.distance.y, 2));

				if (putDecoy == true) {

					if (m2d.length <= collectEnergyRange / 2.0f + ally.radius / 2) {

						if (repairComplete == true) {

							isRepairing = false;

						}
						else {

							canCollectDecoy = false;
							isRepairing = true;

						}

						if (Machine.HP < 1000) {

							if (energyAmount > 0) {

								Machine.HP += 10;
								energyAmount--;

							}
							else {

								repairComplete = true;

							}

						}
						else {

							Machine.HP = 1000;
							repairComplete = true;

						}

					}

				}


#pragma endregion

				#pragma region エネルギーゲージ

				machineGage.translate.x = Machine.translate.x - Machine.radius / 2 + 10;
				machineGage.translate.y = Machine.translate.y - Machine.radius / 2 + 10;

				machineGage.length.y = -Machine.HP / 2.03;

#pragma endregion

#pragma endregion
			#pragma region エネルギー

				for (int i = 0; i < kMaxEnergy; i++) {

					if (energy[i].isAlive == true) {

						#pragma region プレイヤーとの衝突判定

						en2p[i].distance.x = energy[i].translate.x - player.translate.x;
						en2p[i].distance.y = energy[i].translate.y - player.translate.y;

						en2p[i].length = sqrt(pow(en2p[i].distance.x, 2) + pow(en2p[i].distance.y, 2));

						if (en2p[i].length <= collectRange[i] / 2 + player.radius / 2) {

							colletCount[i]++;
							if (colletCount[i] >= 10)
							{
								followPlayer[i] = true;

							}

						}
						if (colletCount[i] >= 10)
						{
							if (en2p[i].length <= energy[i].radius / 2 + player.radius / 2) {

								if (energyAmount < maxEnergyAmount) {

									energyAmount++;

								}
								else {

									energyAmount = maxEnergyAmount;

								}
								followPlayer[i] = false;
								energy[i].speed = energy[i].defSpeed;
								energy[i].isAlive = false;
								colletCount[i] = 0;
							}
						}


#pragma endregion

						#pragma region プレイヤーへの追従判定

						if (followPlayer[i] == true) {

							energy[i].theta = atan2(player.translate.y - energy[i].translate.y, player.translate.x - energy[i].translate.x);

							if (energy[i].theta <= 0) {

								energy[i].theta *= -1;

							}
							else {

								float def = M_PI - energy[i].theta;

								energy[i].theta = def + M_PI;

							}

							energy[i].translate.x += (cosf(energy[i].theta) * energy[i].speed);
							energy[i].translate.y += -(sinf(energy[i].theta) * energy[i].speed);

							energy[i].speed += 0.5f;

						}

#pragma endregion

					}

					#pragma region 画面外に生成されたとき自動で追従するようにする

					//左右
					if (energy[i].translate.x <= 0 + energy[i].radius / 2) {

						followPlayer[i] = true;

					}
					else if (energy[i].translate.x >= kWindowWidth * 3 - energy[i].radius / 2) {

						followPlayer[i] = true;

					}

					//上下
					if (energy[i].translate.y <= 0 + energy[i].radius / 2) {

						followPlayer[i] = true;

					}
					else if (energy[i].translate.y >= kWindowHeight * 2 - energy[i].radius / 2) {

						followPlayer[i] = true;

					}
#pragma endregion

				}

#pragma endregion
			#pragma region 死亡エフェクト
				/*********** 死亡エフェクト ***********/
				for (int i = 0; i < playMaxDeathEffect; i++) {
					if (playDeathEffect[i])
					{
						for (int j = 0; j < deathMaxEffect; j++)
						{
							if (!deathEffect[i][j].isActive)
							{
								deathEffect[i][j].isActive = true;
								deathEffect[i][j].carentAlpha = 0xFF;
								deathEffect[i][j].vectorLength = 0;
								if (j == 0)
								{
									deathEffect[i][j].moveDirection.x = 0;
									deathEffect[i][j].moveDirection.y = -1;
								}
								else if (j == 1) {
									deathEffect[i][j].moveDirection.x = -1;
									deathEffect[i][j].moveDirection.y = -1;
								}
								else if (j == 2) {
									deathEffect[i][j].moveDirection.x = 1;
									deathEffect[i][j].moveDirection.y = 0;
								}
								else if (j == 3) {
									deathEffect[i][j].moveDirection.x = -1;
									deathEffect[i][j].moveDirection.y = 1;
								}
								else if (j == 4) {
									deathEffect[i][j].moveDirection.x = 1;
									deathEffect[i][j].moveDirection.y = 1;
								}
								else if (j == 5) {
									deathEffect[i][j].moveDirection.x = 1;
									deathEffect[i][j].moveDirection.y = -1;
								}
								else if (j == 6) {
									deathEffect[i][j].moveDirection.x = -1;
									deathEffect[i][j].moveDirection.y = 0;
								}
								else {
									deathEffect[i][j].moveDirection.x = 0;
									deathEffect[i][j].moveDirection.y = 1;
								}
							}
							else {
								deathEffect[i][j].vectorLength += 5;
								deathEffect[i][j].carentAlpha -= 0x08;
								if (deathEffect[i][j].carentAlpha <= 0x0C)
								{
									playDeathEffect[i] = false;
								}
							}
						}
					}
					else
					{
						deathEffect[i][0].isActive = false;
						deathEffect[i][1].isActive = false;
						deathEffect[i][2].isActive = false;
						deathEffect[i][3].isActive = false;
						deathEffect[i][4].isActive = false;
						deathEffect[i][5].isActive = false;
						deathEffect[i][6].isActive = false;
						deathEffect[i][7].isActive = false;
					}
				}

#pragma endregion

			}

			if (activeTutorial == true) {

				if (tutorialUI.translate.y != tutorialUI.endPos.y) {

					if (tutorialUI.time < 1.0f) {
						tutorialUI.time += 0.01f;
					}
					else {
						tutorialUI.time = 1.0f;
					}

					tutorialUI.easeTime = 1.0f - powf(1.0f - tutorialUI.time, 5.0f);
					tutorialUI.translate.y = (1.0f - tutorialUI.easeTime) * tutorialUI.startPos.y + tutorialUI.easeTime * tutorialUI.endPos.y;
					tutorialUI.radius.x = (1.0f - tutorialUI.easeTime) * tutorialUI.startRadius.x + tutorialUI.easeTime * tutorialUI.endRadius.x;

				}
				else {

					tutorialUI.time = 0;

					if (activeTutorialTime > 0) {
						activeTutorialTime--;
					}
					else {
						activeTutorialTime = 0;
					}
				}
				
			}

			if (endTutorialAnim == true) {

				if (tutorialUI.translate.y != tutorialUI.startPos.y) {

					if (tutorialUI.time < 1.0f) {
						tutorialUI.time += 0.01f;
					}
					else {
						tutorialUI.time = 1.0f;
					}
					
					tutorialUI.easeTime = 1.0f - powf(1.0f - tutorialUI.time, 5.0f);

					tutorialUI.translate.y = (1.0f - tutorialUI.easeTime) * tutorialUI.endPos.y + tutorialUI.easeTime * tutorialUI.startPos.y;
					tutorialUI.radius.x = (1.0f - tutorialUI.easeTime) * tutorialUI.endRadius.x + tutorialUI.easeTime * tutorialUI.startRadius.x;

				}
				else {

					isEndTutorialAnim = true;

				}

			}

			if (tutorialFinish == false) {

				switch (tutorial)
				{
				case MOVE:

					if (onceActive == false) {

						activeTutorial = true;
						onceActive = true;

					}

					tutorialMove = true;

					if (activeTutorialTime == 0) {

						endTutorialAnim = true;

					}

					if (nextTutorial == true) {

						tutorial++;
						nextTutorial = false;

					}

					break;

				case ANGLE:

					break;
				case CHARGE:

					break;

				case ATTACK:

					break;

				case PUTDECOY:

					break;

				case DECOY:

					break;

				case DECOYHP:

					break;

				case DECOYGAMEOVER:

					break;

				case COLLECTDECOY:

					break;

				case DECOYHEAL:

					break;

				case ENHANCEDATTACK:

					break;

				case EATTACK:

					break;

				case MACHINEHP:

					break;

				case MACHINEREPAIR:

					break;

				}

			}

			if (tutorialFinish == true && gameFinish == false) {

				gameStart = true;

			}

#pragma endregion

		#pragma region ゲーム中

			if (gameStart == true && gameFinish == false) {
				
			#pragma region ゲーム時間
				
				if (gameTimer > 0) {

					gameTimer--;

				}
				else {

					gameTimer = 0;
					gameFinish = true;

				}

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
			#pragma region 時間がたつごとに機械のエネルギー減少

				if (Machine.HP >= 500) {

					scoreMagnification = 1.0f;

				}
				if (Machine.HP < 500) {

					scoreMagnification = 0.5f;

				}
				else if (Machine.HP <= 0) {

					scoreMagnification = 0.1f;

				}

				if (Machine.HP <= 0) {

					Machine.HP = 0;

				}
				else {

					Machine.HP--;

				}

#pragma endregion
			#pragma region 設置されている時デコイHP減少

				if (putDecoy == true) {

					if (ally.HP < 0) {

						deadDecoy = true;
						ally.HP = 0;

					}
					else {

						ally.HP -= 2;

					}

				}
				else {

					if (ally.HP >= 500) {

						ally.HP = 500;

					}
					else {

						ally.HP += 5;

					}

				}

				if (deadDecoy == true) {

					if (!playDeadDecoyEffect)
					{
						playDeadDecoyEffect = true;
					}

				}

#pragma endregion
			#pragma region コンボ

				if (comboReceptionTime < 0) {

					combo = 0;
					tenCombo = 0;
					comboMagnification = 1.0f;
					comboReceptionTime = defComboReceptionTime;

				}

				if (combo >= 1) {

					comboReceptionTime--;

				}
				else {

					comboReceptionTime = defComboReceptionTime;

				}

				if (tenCombo >= startCombo) {

					if (comboMagnification < 9.99f) {

						comboMagnification += 0.1f;

					}
					else {

						comboMagnification = 9.99f;

					}
					tenCombo = 0;

				}

			}
#pragma endregion
			#pragma region 終了処理

			if (gameFinish == true) {

				blackout = true;

				if (currentBlackOutAlpha == 0xEE) {

					resultUIPlayAnim = true;

					if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {

						resultUI.radius.x = resultUI.endRadius.x;
						resultUI.translate.y = resultUI.endPos.y;
						scoreUI.translate.x = scoreUI.endPos.x;
						killUI.translate.x = killUI.endPos.x;

					}

				}

				if (resultUIPlayAnim == true) {

					if (resultUI.translate.y != resultUI.endPos.y) {

						resultUI.time += 0.01f;

						resultUI.easeTime = 1.0f - powf(1.0f - resultUI.time, 5.0f);

						resultUI.translate.y = (1.0f - resultUI.easeTime) * resultUI.startPos.y + resultUI.easeTime * resultUI.endPos.y;
						resultUI.radius.x = (1.0f - resultUI.easeTime) * resultUI.startRadius.x + resultUI.easeTime * resultUI.endRadius.x;

					}
					else {

						scorePlayAnim = true;

					}

				}

				if (scorePlayAnim == true) {

					if (scoreUI.translate.x != scoreUI.endPos.x) {

						scoreUI.time += 0.01f;
						scoreUI.easeTime = 1.0f - powf(1.0f - scoreUI.time, 5.0f);

						scoreUI.translate.x = (1.0f - scoreUI.easeTime) * scoreUI.startPos.x + scoreUI.easeTime * scoreUI.endPos.x;

					}
					else {

						killUIPlayAnim = true;

					}

				}

				if (killUIPlayAnim == true) {

					if (killUI.translate.x != killUI.endPos.x) {

						killUI.time += 0.01f;
						killUI.easeTime = 1.0f - powf(1.0f - killUI.time, 5.0f);

						killUI.translate.x = (1.0f - killUI.easeTime) * killUI.startPos.x + killUI.easeTime * killUI.endPos.x;

					}
					else {

						endUIAnim = true;

					}

				}

				if (endUIAnim == true) {

					if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {

						fadeIn = false;
						goInitializeScene = true;

					}

				}

			}

			if (goInitializeScene == true) {

				if (currentFadeAlpha == 0xFF) {
					
					blackout = false;
					scene++;

				}

			}

			#pragma endregion

#pragma endregion

			break;
		case INITIALIZE:

		#pragma region 初期化

			#pragma region ゲーム

			gameTimer = 3600;

			gameSecondsTimer = 0;
			recGameSecondsTimer = 0;

			tutorialStart = false;
			tutorialFinish = false;

			tutorialMove = false;

			gameStart = false;
			gameFinish = false;

#pragma endregion
			#pragma region スコア

			score = 0;
			tempScore = 0;

			scoreUIPosOrigin = { 0, 0 };

			scoreNumberSize = 96;
			scoreNumberSpace = scoreNumberSize / 2;

			resultScoreUIPosOrigin = { 0, 0 };
			resultScoreNumberSize = 256;
			resultScoreNumberSpace = resultScoreNumberSize / 2;

			addScore = 100;
			defAddScore = 100;

			combo = 0;
			tempCombo = 0;

			comboUIPosOrigin = { 0, 0 };
			resultComboUIPosOrigin = { 0, 0 };

			comboNumberSize = 256;
			comboNumberSpace = comboNumberSize / 2;

			tenCombo = 0;
			startCombo = 10;

			comboReceptionGage = {

				0.0f, 0.0f,
				0.0f, 0.0f,
				WHITE

			};

			comboReceptionTime = 120.0f;
			defComboReceptionTime = 120.0f;

			MagnificationUIPosOrigin = { 0, 0 };
			scoreMagnification = 1.0f;
			comboMagnification = 1.0f;
			tempMagnification = 0;

			MagnificationNumberSize = 64;
			MagnificationNumberSpace = MagnificationNumberSize / 2;

#pragma endregion
			#pragma region 乱数 

			unsigned int currentTime = time(nullptr);

			currentTime = time(nullptr);
			srand(currentTime);

			unsigned int effectTime = time(nullptr);
			srand(effectTime);

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
			#pragma region プレイヤー

			/******** プレイヤー **********/
			player = {

				kWindowWidth * 1.5f, kWindowHeight - 160.0f, //translate x, y
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
				512, //graphRadius

				WHITE

			};

			playFlashEffect = false;
			flashEffectFrame = 0;

			chargeGage = {

				player.translate.x - player.radius, player.translate.y + player.radius / 2,
				0.0f, 0.0f,
				0x00fa9aFF

			};

			playerPoint = {

				-player.radius / 2, -player.radius / 2,
				player.radius / 2, -player.radius / 2,
				-player.radius / 2, player.radius / 2,
				player.radius / 2, player.radius / 2

			};

			playerRotate = {

				0.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 0.0f

			};

			playerDirectionOrigin = {

				player.radius * 0.75f, -player.radius / 3.0f,
				player.radius * 1.25f, -player.radius / 3.0f,
				player.radius * 0.75f, player.radius / 3.0f,
				player.radius * 1.25f, player.radius / 3.0f

			};

			playerDirection = {

				0.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 0.0f

			};

			theta = 0.0f;

			moveSpeed = 0.0f;

			//スペースキートリガー用
			isPressSpace = false;

			//チャージできるか
			canCharge = true;
			//現在チャージしているか
			isCharging = false;
			//チャージが完了しているか
			compCharge = false;

			//攻撃中か
			isAttacking = false;

			//チャージされているパワー
			chargePower = 0.0f;
			//パワーの最大値
			maxPower = 60.0f;

			//チャージ可能までのクールタイム
			chargeCoolTime = 0.0f;
			//チャージ可能までのクールタイムのデフォルト値
			defChargeCoolTime = 10.0f;

			enhanceSpeed = false;

			int canEnhancedAttack = false;
			int doEnhancedAttack = false;

			for (int i = 0; i < maxEnhancedAttack; i++) {

				shockOrigin[i] = { 0.0f, 0.0f };
				shockRadius[i] = 0.0f;

				isEnhancedAttack[i] = false;

			}

			#pragma endregion
			#pragma region 味方
			/******** 味方 **********/
			ally = {

				kWindowWidth * 1.5f, kWindowHeight, //translate x, y
				0.0f, 0.0f, //moveDirection x, y
				0.0f, //vectorLength

				128.0f, //radius
				0.0f,

				20.0f, //speed
				5.0f, //defSpeed

				true,
				500, //HP

				5, //damage

				Novice::LoadTexture("./resources/graph/decoy/decoy.png"), //graph
				512, //graphRadius

				WHITE

			};

			putDecoy = false;
			canCollectDecoy = false;

			deadDecoy = false;

			allyRadius = 128;

			decoyRotate = {

				0.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 0.0f

			};

			decoyHPGage = {

				0, 0,
				32, 0,
				0x00ff7fFF

			};

			p2d = {

				0.0f, 0.0f,
				0.0f

			};

			e2d = {

				0.0f, 0.0f,
				0.0f

			};
#pragma endregion
			#pragma region 敵

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
					256,

					WHITE

				};

				enemyType[i] = FOLLOW;

				EnemyRotate[i] = {

					-enemy[i].radius / 2, -enemy[i].radius / 2,
					enemy[i].radius / 2, -enemy[i].radius / 2,
					-enemy[i].radius / 2, enemy[i].radius / 2,
					enemy[i].radius / 2, enemy[i].radius / 2

				};

				e2e[i] = {

					0.0f, 0.0f,
					0.0f

				};

				At2e[i] = {

					0.0f, 0.0f,
					0.0f

				};

				enemyNockBack[i] = 0.0f;

				isNockBacking[i] = false;
				nockBackSpeed[i] = 0.0f;

				enemyAmplitude[i] = 0.0f;
				enemyAmplitudeStrength[i] = 0.0f;

				deadEnemy[i] = false;

				ef2e[i] = {

					0.0f,0.0f,
					0.0f

				};

			}

			killEnemy = 0;

#pragma endregion
			#pragma region 機械

			Machine = {

				kWindowWidth * 1.5f, kWindowHeight, //translate x, y
				0.0f, 0.0f, //moveDirection x, y
				0.0f, //vectorLength

				512.0f, //radius
				0.0f,

				0.0f, //speed
				50.0f, //defSpeed

				true,
				1000, //HP

				1, //damage

				Novice::LoadTexture("./resources/graph/machine/Machine.png"), //graph
				512, //graphRadius

				WHITE

			};

			m2p = {

				0.0f, 0.0f,
				0.0f

			};

			m2d = {

				0.0f, 0.0f,
				0.0f

			};

			machineGage = {

				0.0f, 0.0f,
				497, 0,
				0x90ee90FF

			};

			tempMachineEnergy = 0;

			isRepairing = false;
			repairComplete = false;

			collectEnergyRange = Machine.radius;

#pragma endregion
			#pragma region エネルギー

			for (int i = 0; i < kMaxEnergy; i++) {

				energy[i] = {

					0.0f, 0.0f,
					0.0f, 0.0f,
					0.0f,

					32.0f,
					0.0f,

					3.0f,
					3.0f,

					false,
					1,
					1,

					Novice::LoadTexture("./resources/graph/energy/Energy.png"),
					128,

					WHITE

				};

				collectRange[i] = energy[i].radius * 25.0f;

				followPlayer[i] = false;

				colletCount[i] = 0;

				en2p[i] = {

					0.0f, 0.0f,
					0.0f

				};

			}

			energyAmount = 0;
			maxEnergyAmount = 1000;

			energyIconGraph = Novice::LoadTexture("./resources/graph/energy/EnergyIcon.png");

			energyAmountGage = {

				0, 0,
				0, 0,
				0x90ee90FF

			};

#pragma endregion

			#pragma region スポーン
			spawnTheta = 0;

			spawnTimer = 60.0f;
			defSpawnTimer = 30.0f;

			canSpawn = false;
			enemySpawnPoint = 0;

			canSpawnRushEnemy = false;
			spawnRushEnemy = false;
			spawnRushEnemyTimer = 300;

			spawnCounter = 0;
			nowSpawnCounter = 0;
			maxOnceSpawn = 10;

#pragma endregion
			#pragma region エフェクト
			/******** チャージエフェクト **********/
			for (int i = 0; i < chargeEffectMax; i++)
			{
				chargeEffect[i].isActive = false;
				chargeEffect[i].vectorLength = player.radius * 2;
				chargeEffect[i].moveDirection.x = 0;
				chargeEffect[i].moveDirection.y = 0;
				chargeEffect[i].translate.x = chargeEffect[i].moveDirection.x * chargeEffect[i].vectorLength;
				chargeEffect[i].translate.y = chargeEffect[i].moveDirection.y * chargeEffect[i].vectorLength;
				chargeEffect[i].carentAlpha = 0xBA;
				chargeEffect[i].radius = 96;
				chargeEffect[i].graph = Novice::LoadTexture("./resources/graph/effect/effect.png");
				chargeEffect[i].graphRadius = 512;
			};

			/******** エフェクト(残像) **********/
			for (int i = 0; i < afterimageMax; i++)
			{
				afterimage[i].isActive = false;
				afterimage[i].translate.x = player.translate.x;
				afterimage[i].translate.y = player.translate.y;
				afterimage[i].carentAlpha = 0xBA;
				afterimage[i].radius = 128 / 2;
				afterimage[i].graph = Novice::LoadTexture("./resources/graph/player/player.png");
				afterimage[i].graphRadius = player.graphRadius;

				ef2en[i] = {

					0.0f,0.0f,
					0.0f

				};
			};

			/******** エフェクト(敵死亡) **********/

			for (int i = 0; i < playMaxDeathEffect; i++)
			{
				playDeathEffect[i] = false;
				for (int j = 0; j < deathMaxEffect; j++)
				{
					deathEffect[i][j].isActive = false;
					deathEffect[i][j].vectorLength = 0;
					deathEffect[i][j].moveDirection.x = 0;
					deathEffect[i][j].moveDirection.y = 0;
					deathEffect[i][j].translate = enemy[i].translate;
					deathEffect[i][j].carentAlpha = 0xFF;
					deathEffect[i][j].radius = 16;
					deathEffect[i][j].graph = Novice::LoadTexture("./resources/graph/effect/deathEffect.png");
					deathEffect[i][j].graphRadius = 128;
				}

			};

			/******** エフェクト(デコイ死亡) **********/

			playDeadDecoyEffect = false;
			endDeadDecoyEffect = false;

			for (int i = 0; i < kMaxdeadDecoyEffect; i++)
			{
				deadDecoyEffect[i].isActive = false;
				deadDecoyEffect[i].vectorLength = 0;
				deadDecoyEffect[i].moveDirection.x = 0;
				deadDecoyEffect[i].moveDirection.y = 0;
				deadDecoyEffect[i].translate = ally.translate;
				deadDecoyEffect[i].carentAlpha = 0xFF;
				deadDecoyEffect[i].radius = 64;
				deadDecoyEffect[i].graph = Novice::LoadTexture("./resources/graph/effect/decoyDeadEffect.png");
				deadDecoyEffect[i].graphRadius = 128;
			};



#pragma endregion
			#pragma region リザルト画面

			resultUIPlayAnim = false;

			resultUI = {
				kWindowWidth / 2, 0.0f,
				kWindowWidth / 2, 1200,
				kWindowWidth / 2, 900,
				0, 272,
				0, 272,
				1280, 272,
				0.0f,
				0.0f
			};

			scorePlayAnim = false;

			scoreUI = {

				-256 * 7, 600,
				-256 * 7, 600,
				1000, 600,
				256, 256,
				256, 256,
				256, 256,
				0.0f,
				0.0f

			};

			killUIPlayAnim = false;

			killUI = {

				-256 * 4, 300,
				-256 * 4, 300,
				1000 + 256 * 1.5f, 350,
				256, 256,
				256, 256,
				256, 256,
				0.0f,
				0.0f

			};

			endUIAnim = false;

#pragma endregion

			scene--;

#pragma endregion

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
				0x696969FF

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
					BLACK

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
					BLACK

				);
			}

#pragma endregion

			#pragma region 機械描画

			Novice::DrawBox(

				worldPosOrigin.x + machineGage.translate.x - scrool.x,
				worldPosOrigin.y - machineGage.translate.y + scrool.y,
				machineGage.length.x,
				machineGage.length.y,
				0.0f,
				machineGage.color,
				kFillModeSolid

			);

			Novice::DrawQuad(

				worldPosOrigin.x + Machine.translate.x - Machine.radius / 2 - scrool.x,
				worldPosOrigin.y - Machine.translate.y - Machine.radius / 2 + scrool.y,

				worldPosOrigin.x + Machine.translate.x + Machine.radius / 2 - scrool.x,
				worldPosOrigin.y - Machine.translate.y - Machine.radius / 2 + scrool.y,

				worldPosOrigin.x + Machine.translate.x - Machine.radius / 2 - scrool.x,
				worldPosOrigin.y - Machine.translate.y + Machine.radius / 2 + scrool.y,

				worldPosOrigin.x + Machine.translate.x + Machine.radius / 2 - scrool.x,
				worldPosOrigin.y - Machine.translate.y + Machine.radius / 2 + scrool.y,

				0,
				0,

				Machine.graphRadius,
				Machine.graphRadius,

				Machine.graph,
				Machine.color

			);

#pragma endregion

			#pragma region タイマー処理
			for (int i = 0; i <= 1; i++) {
				Novice::DrawQuad(

					worldPosOrigin.x + secondsTimerPosOrigin.x - numberSize / 2 - scrool.x + (numberSpace * i),
					worldPosOrigin.y - secondsTimerPosOrigin.y - numberSize / 2 + scrool.y,

					worldPosOrigin.x + secondsTimerPosOrigin.x + numberSize / 2 - scrool.x + (numberSpace * i),
					worldPosOrigin.y - secondsTimerPosOrigin.y - numberSize / 2 + scrool.y,

					worldPosOrigin.x + secondsTimerPosOrigin.x - numberSize / 2 - scrool.x + (numberSpace * i),
					worldPosOrigin.y - secondsTimerPosOrigin.y + numberSize / 2 + scrool.y,

					worldPosOrigin.x + secondsTimerPosOrigin.x + numberSize / 2 - scrool.x + (numberSpace * i),
					worldPosOrigin.y - secondsTimerPosOrigin.y + numberSize / 2 + scrool.y,

					0,
					0,

					512,
					512,

					numberGraph[eachSec[i]],
					WHITE

				);
			}
#pragma endregion

			#pragma region スコア
			for (int i = 0; i < 7; i++) {
				Novice::DrawQuad(

					worldPosOrigin.x + scoreUIPosOrigin.x - scoreNumberSize / 2 - scrool.x + (scoreNumberSpace * i),
					worldPosOrigin.y - scoreUIPosOrigin.y - scoreNumberSize / 2 + scrool.y,

					worldPosOrigin.x + scoreUIPosOrigin.x + scoreNumberSize / 2 - scrool.x + (scoreNumberSpace * i),
					worldPosOrigin.y - scoreUIPosOrigin.y - scoreNumberSize / 2 + scrool.y,

					worldPosOrigin.x + scoreUIPosOrigin.x - scoreNumberSize / 2 - scrool.x + (scoreNumberSpace * i),
					worldPosOrigin.y - scoreUIPosOrigin.y + scoreNumberSize / 2 + scrool.y,

					worldPosOrigin.x + scoreUIPosOrigin.x + scoreNumberSize / 2 - scrool.x + (scoreNumberSpace * i),
					worldPosOrigin.y - scoreUIPosOrigin.y + scoreNumberSize / 2 + scrool.y,

					0,
					0,

					512,
					512,

					numberGraph[eachScore[i]],
					WHITE

				);
			}

#pragma endregion

			#pragma region コンボ

			for (int i = 0; i < 3; i++) {

				Novice::DrawQuad(

					worldPosOrigin.x + comboUIPosOrigin.x - comboNumberSize / 2 - scrool.x + (comboNumberSpace * i),
					worldPosOrigin.y - comboUIPosOrigin.y - comboNumberSize / 2 + scrool.y,

					worldPosOrigin.x + comboUIPosOrigin.x + comboNumberSize / 2 - scrool.x + (comboNumberSpace * i),
					worldPosOrigin.y - comboUIPosOrigin.y - comboNumberSize / 2 + scrool.y,

					worldPosOrigin.x + comboUIPosOrigin.x - comboNumberSize / 2 - scrool.x + (comboNumberSpace * i),
					worldPosOrigin.y - comboUIPosOrigin.y + comboNumberSize / 2 + scrool.y,

					worldPosOrigin.x + comboUIPosOrigin.x + comboNumberSize / 2 - scrool.x + (comboNumberSpace * i),
					worldPosOrigin.y - comboUIPosOrigin.y + comboNumberSize / 2 + scrool.y,

					0,
					0,

					512,
					512,

					numberGraph[eachCombo[i]],
					WHITE

				);
			}

#pragma endregion

			#pragma region コンボ受付時間

			Novice::DrawQuad(

				worldPosOrigin.x + comboReceptionGage.translate.x - comboReceptionGage.length.x - scrool.x,
				worldPosOrigin.y - comboReceptionGage.translate.y - comboReceptionGage.length.y + scrool.y,

				worldPosOrigin.x + comboReceptionGage.translate.x + comboReceptionGage.length.x - scrool.x,
				worldPosOrigin.y - comboReceptionGage.translate.y - comboReceptionGage.length.y + scrool.y,

				worldPosOrigin.x + comboReceptionGage.translate.x - comboReceptionGage.length.x - scrool.x,
				worldPosOrigin.y - comboReceptionGage.translate.y + comboReceptionGage.length.y + scrool.y,

				worldPosOrigin.x + comboReceptionGage.translate.x + comboReceptionGage.length.x - scrool.x,
				worldPosOrigin.y - comboReceptionGage.translate.y + comboReceptionGage.length.y + scrool.y,

				0, 0,
				1, 1,

				White1x1,
				comboReceptionGage.color

			);


			#pragma endregion

			#pragma region 倍率

			Novice::DrawQuad(

				worldPosOrigin.x + MagnificationUIPosOrigin.x - MagnificationNumberSize / 2 - scrool.x - MagnificationNumberSize / 1.75f,
				worldPosOrigin.y - MagnificationUIPosOrigin.y - MagnificationNumberSize / 2 + scrool.y - 5,

				worldPosOrigin.x + MagnificationUIPosOrigin.x + MagnificationNumberSize / 2 - scrool.x - MagnificationNumberSize / 1.75f,
				worldPosOrigin.y - MagnificationUIPosOrigin.y - MagnificationNumberSize / 2 + scrool.y - 5,

				worldPosOrigin.x + MagnificationUIPosOrigin.x - MagnificationNumberSize / 2 - scrool.x - MagnificationNumberSize / 1.75f,
				worldPosOrigin.y - MagnificationUIPosOrigin.y + MagnificationNumberSize / 2 + scrool.y - 5,

				worldPosOrigin.x + MagnificationUIPosOrigin.x + MagnificationNumberSize / 2 - scrool.x - MagnificationNumberSize / 1.75f,
				worldPosOrigin.y - MagnificationUIPosOrigin.y + MagnificationNumberSize / 2 + scrool.y - 5,

				0,
				0,

				512,
				512,

				XGraph,
				WHITE

			);

			for (int i = 0; i < 4; i++) {

				if (eachMagnification[i] == DotGraph) {

					Novice::DrawQuad(

						worldPosOrigin.x + MagnificationUIPosOrigin.x - MagnificationNumberSize / 2 - scrool.x + (MagnificationNumberSpace * i),
						worldPosOrigin.y - MagnificationUIPosOrigin.y - MagnificationNumberSize / 2 + scrool.y,

						worldPosOrigin.x + MagnificationUIPosOrigin.x + MagnificationNumberSize / 2 - scrool.x + (MagnificationNumberSpace * i),
						worldPosOrigin.y - MagnificationUIPosOrigin.y - MagnificationNumberSize / 2 + scrool.y,

						worldPosOrigin.x + MagnificationUIPosOrigin.x - MagnificationNumberSize / 2 - scrool.x + (MagnificationNumberSpace * i),
						worldPosOrigin.y - MagnificationUIPosOrigin.y + MagnificationNumberSize / 2 + scrool.y,

						worldPosOrigin.x + MagnificationUIPosOrigin.x + MagnificationNumberSize / 2 - scrool.x + (MagnificationNumberSpace * i),
						worldPosOrigin.y - MagnificationUIPosOrigin.y + MagnificationNumberSize / 2 + scrool.y,

						0,
						0,

						512,
						512,

						DotGraph,
						WHITE

					);

				}
				else {

					Novice::DrawQuad(

						worldPosOrigin.x + MagnificationUIPosOrigin.x - MagnificationNumberSize / 2 - scrool.x + (MagnificationNumberSpace * i),
						worldPosOrigin.y - MagnificationUIPosOrigin.y - MagnificationNumberSize / 2 + scrool.y,

						worldPosOrigin.x + MagnificationUIPosOrigin.x + MagnificationNumberSize / 2 - scrool.x + (MagnificationNumberSpace * i),
						worldPosOrigin.y - MagnificationUIPosOrigin.y - MagnificationNumberSize / 2 + scrool.y,

						worldPosOrigin.x + MagnificationUIPosOrigin.x - MagnificationNumberSize / 2 - scrool.x + (MagnificationNumberSpace * i),
						worldPosOrigin.y - MagnificationUIPosOrigin.y + MagnificationNumberSize / 2 + scrool.y,

						worldPosOrigin.x + MagnificationUIPosOrigin.x + MagnificationNumberSize / 2 - scrool.x + (MagnificationNumberSpace * i),
						worldPosOrigin.y - MagnificationUIPosOrigin.y + MagnificationNumberSize / 2 + scrool.y,

						0,
						0,

						512,
						512,

						numberGraph[eachMagnification[i]],
						WHITE

					);

				}
				
			}

			#pragma endregion

			#pragma region 敵描画

			for (int i = 0; i < kMaxEnemy; i++) {

				if (enemy[i].isAlive == true) {

					Novice::DrawQuad(

						(worldPosOrigin.x + EnemyRotate[i].q1.x - scrool.x),
						(worldPosOrigin.y - EnemyRotate[i].q1.y + scrool.y),

						(worldPosOrigin.x + EnemyRotate[i].q2.x - scrool.x),
						(worldPosOrigin.y - EnemyRotate[i].q2.y + scrool.y),

						(worldPosOrigin.x + EnemyRotate[i].q3.x - scrool.x),
						(worldPosOrigin.y - EnemyRotate[i].q3.y + scrool.y),

						(worldPosOrigin.x + EnemyRotate[i].q4.x - scrool.x),
						(worldPosOrigin.y - EnemyRotate[i].q4.y + scrool.y),

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
			#pragma region エフェクト
			/******** 残像 **********/
			for (int i = 0; i < afterimageMax; i++)
			{
				if (afterimage[i].isActive)
				{
					Novice::DrawQuad(

						worldPosOrigin.x + afterimage[i].translate.x - afterimage[i].radius / 2 - scrool.x,
						worldPosOrigin.y - afterimage[i].translate.y - afterimage[i].radius / 2 + scrool.y,

						worldPosOrigin.x + afterimage[i].translate.x + afterimage[i].radius / 2 - scrool.x,
						worldPosOrigin.y - afterimage[i].translate.y - afterimage[i].radius / 2 + scrool.y,

						worldPosOrigin.x + afterimage[i].translate.x - afterimage[i].radius / 2 - scrool.x,
						worldPosOrigin.y - afterimage[i].translate.y + afterimage[i].radius / 2 + scrool.y,

						worldPosOrigin.x + afterimage[i].translate.x + afterimage[i].radius / 2 - scrool.x,
						worldPosOrigin.y - afterimage[i].translate.y + afterimage[i].radius / 2 + scrool.y,

						0,
						0,

						afterimage[i].graphRadius,
						afterimage[i].graphRadius,

						afterimage[i].graph,
						0xFFFFFF00 + afterimage[i].carentAlpha

					);
				}
			}

			if (ally.isAlive == true && putDecoy == false) {

				/******** 味方描画 **********/
				Novice::DrawQuad(

					worldPosOrigin.x + decoyRotate.q1.x - scrool.x,
					worldPosOrigin.y - decoyRotate.q1.y + scrool.y,

					worldPosOrigin.x + decoyRotate.q2.x - scrool.x,
					worldPosOrigin.y - decoyRotate.q2.y + scrool.y,

					worldPosOrigin.x + decoyRotate.q3.x - scrool.x,
					worldPosOrigin.y - decoyRotate.q3.y + scrool.y,

					worldPosOrigin.x + decoyRotate.q4.x - scrool.x,
					worldPosOrigin.y - decoyRotate.q4.y + scrool.y,

					0,
					0,

					ally.graphRadius,
					ally.graphRadius,

					ally.graph,
					ally.color
				);

			}

			/******** チャージエフェクト **********/
			for (int i = 0; i < chargeEffectMax; i++)
			{
				if (chargeEffect[i].isActive)
				{
					Novice::DrawQuad(

						worldPosOrigin.x + chargeEffect[i].translate.x - chargeEffect[i].radius * 0.4f + chargeEffect[i].vectorLength * chargeEffect[i].moveDirection.x - scrool.x,
						worldPosOrigin.y - chargeEffect[i].translate.y - chargeEffect[i].radius * 0.4f + chargeEffect[i].vectorLength * chargeEffect[i].moveDirection.y + scrool.y,

						worldPosOrigin.x + chargeEffect[i].translate.x + chargeEffect[i].radius * 0.4f + chargeEffect[i].vectorLength * chargeEffect[i].moveDirection.x - scrool.x,
						worldPosOrigin.y - chargeEffect[i].translate.y - chargeEffect[i].radius * 0.4f + chargeEffect[i].vectorLength * chargeEffect[i].moveDirection.y + scrool.y,

						worldPosOrigin.x + chargeEffect[i].translate.x - chargeEffect[i].radius * 0.4f + chargeEffect[i].vectorLength * chargeEffect[i].moveDirection.x - scrool.x,
						worldPosOrigin.y - chargeEffect[i].translate.y + chargeEffect[i].radius * 0.4f + chargeEffect[i].vectorLength * chargeEffect[i].moveDirection.y + scrool.y,

						worldPosOrigin.x + chargeEffect[i].translate.x + chargeEffect[i].radius * 0.4f + chargeEffect[i].vectorLength * chargeEffect[i].moveDirection.x - scrool.x,
						worldPosOrigin.y - chargeEffect[i].translate.y + chargeEffect[i].radius * 0.4f + chargeEffect[i].vectorLength * chargeEffect[i].moveDirection.y + scrool.y,

						0,
						0,

						chargeEffect[i].graphRadius,
						chargeEffect[i].graphRadius,

						chargeEffect[i].graph,
						0xFFFFFF00 + chargeEffect[i].carentAlpha

					);
				}
			}

			/******** 死亡 **********/
			for (int i = 0; i < playMaxDeathEffect; i++)
			{
				for (int j = 0; j < deathMaxEffect; j++)
				{
					if (deathEffect[i][j].isActive)
					{
						Novice::DrawQuad(

							worldPosOrigin.x + deathEffect[i][j].translate.x - deathEffect[i][j].radius + deathEffect[i][j].vectorLength * deathEffect[i][j].moveDirection.x - scrool.x,
							worldPosOrigin.y - deathEffect[i][j].translate.y - deathEffect[i][j].radius + deathEffect[i][j].vectorLength * deathEffect[i][j].moveDirection.y + scrool.y,

							worldPosOrigin.x + deathEffect[i][j].translate.x + deathEffect[i][j].radius + deathEffect[i][j].vectorLength * deathEffect[i][j].moveDirection.x - scrool.x,
							worldPosOrigin.y - deathEffect[i][j].translate.y - deathEffect[i][j].radius + deathEffect[i][j].vectorLength * deathEffect[i][j].moveDirection.y + scrool.y,

							worldPosOrigin.x + deathEffect[i][j].translate.x - deathEffect[i][j].radius + deathEffect[i][j].vectorLength * deathEffect[i][j].moveDirection.x - scrool.x,
							worldPosOrigin.y - deathEffect[i][j].translate.y + deathEffect[i][j].radius + deathEffect[i][j].vectorLength * deathEffect[i][j].moveDirection.y + scrool.y,

							worldPosOrigin.x + deathEffect[i][j].translate.x + deathEffect[i][j].radius + deathEffect[i][j].vectorLength * deathEffect[i][j].moveDirection.x - scrool.x,
							worldPosOrigin.y - deathEffect[i][j].translate.y + deathEffect[i][j].radius + deathEffect[i][j].vectorLength * deathEffect[i][j].moveDirection.y + scrool.y,

							0,
							0,

							deathEffect[i][j].graphRadius,
							deathEffect[i][j].graphRadius,

							deathEffect[i][j].graph,
							0xFFFFFF00 + deathEffect[i][j].carentAlpha

						);
					}
				}
			}

			/**********  デコイ死亡エフェクト  **********/
			if (playDeadDecoyEffect && !endDeadDecoyEffect)
			{
				for (int i = 0; i < deathMaxEffect; i++)
				{
					if (deadDecoyEffect[i].isActive)
					{
						Novice::DrawQuad(

							worldPosOrigin.x + deadDecoyEffect[i].translate.x - deadDecoyEffect[i].radius + deadDecoyEffect[i].vectorLength * deadDecoyEffect[i].moveDirection.x - scrool.x,
							worldPosOrigin.y - deadDecoyEffect[i].translate.y - deadDecoyEffect[i].radius + deadDecoyEffect[i].vectorLength * deadDecoyEffect[i].moveDirection.y + scrool.y,

							worldPosOrigin.x + deadDecoyEffect[i].translate.x + deadDecoyEffect[i].radius + deadDecoyEffect[i].vectorLength * deadDecoyEffect[i].moveDirection.x - scrool.x,
							worldPosOrigin.y - deadDecoyEffect[i].translate.y - deadDecoyEffect[i].radius + deadDecoyEffect[i].vectorLength * deadDecoyEffect[i].moveDirection.y + scrool.y,

							worldPosOrigin.x + deadDecoyEffect[i].translate.x - deadDecoyEffect[i].radius + deadDecoyEffect[i].vectorLength * deadDecoyEffect[i].moveDirection.x - scrool.x,
							worldPosOrigin.y - deadDecoyEffect[i].translate.y + deadDecoyEffect[i].radius + deadDecoyEffect[i].vectorLength * deadDecoyEffect[i].moveDirection.y + scrool.y,

							worldPosOrigin.x + deadDecoyEffect[i].translate.x + deadDecoyEffect[i].radius + deadDecoyEffect[i].vectorLength * deadDecoyEffect[i].moveDirection.x - scrool.x,
							worldPosOrigin.y - deadDecoyEffect[i].translate.y + deadDecoyEffect[i].radius + deadDecoyEffect[i].vectorLength * deadDecoyEffect[i].moveDirection.y + scrool.y,

							0,
							0,

							deadDecoyEffect[i].graphRadius,
							deadDecoyEffect[i].graphRadius,

							deadDecoyEffect[i].graph,
							0xFFFFFF00 + deadDecoyEffect[i].carentAlpha

						);
					}
				}
			}
#pragma endregion

			#pragma region エネルギー描画

			for (int i = 0; i < kMaxEnergy; i++) {

				if (energy[i].isAlive == true) {

					Novice::DrawQuad(

						worldPosOrigin.x + energy[i].translate.x - energy[i].radius / 2 - scrool.x,
						worldPosOrigin.y - energy[i].translate.y - energy[i].radius / 2 + scrool.y,

						worldPosOrigin.x + energy[i].translate.x + energy[i].radius / 2 - scrool.x,
						worldPosOrigin.y - energy[i].translate.y - energy[i].radius / 2 + scrool.y,

						worldPosOrigin.x + energy[i].translate.x - energy[i].radius / 2 - scrool.x,
						worldPosOrigin.y - energy[i].translate.y + energy[i].radius / 2 + scrool.y,

						worldPosOrigin.x + energy[i].translate.x + energy[i].radius / 2 - scrool.x,
						worldPosOrigin.y - energy[i].translate.y + energy[i].radius / 2 + scrool.y,

						0,
						0,

						energy[i].graphRadius,
						energy[i].graphRadius,

						energy[i].graph,
						energy[i].color

					);

				}

			}

#pragma endregion

			#pragma region 味方描画

			if (ally.isAlive == true && putDecoy == true)
			{

				/******** 味方描画 **********/
				Novice::DrawQuad(

					worldPosOrigin.x + ally.translate.x - ally.radius / 2 - scrool.x,
					worldPosOrigin.y - ally.translate.y - ally.radius / 2 + scrool.y,

					worldPosOrigin.x + ally.translate.x + ally.radius / 2 - scrool.x,
					worldPosOrigin.y - ally.translate.y - ally.radius / 2 + scrool.y,

					worldPosOrigin.x + ally.translate.x - ally.radius / 2 - scrool.x,
					worldPosOrigin.y - ally.translate.y + ally.radius / 2 + scrool.y,

					worldPosOrigin.x + ally.translate.x + ally.radius / 2 - scrool.x,
					worldPosOrigin.y - ally.translate.y + ally.radius / 2 + scrool.y,

					0,
					0,

					ally.graphRadius,
					ally.graphRadius,

					ally.graph,
					ally.color

				);
			}
#pragma endregion
			#pragma region プレイヤー描画

			for (int i = 0; i < maxEnhancedAttack; i++) {

				Novice::DrawQuad(

					worldPosOrigin.x + shockOrigin[i].x - shockRadius[i] - scrool.x,
					worldPosOrigin.y - shockOrigin[i].y - shockRadius[i] + scrool.y,

					worldPosOrigin.x + shockOrigin[i].x + shockRadius[i] - scrool.x,
					worldPosOrigin.y - shockOrigin[i].y - shockRadius[i] + scrool.y,

					worldPosOrigin.x + shockOrigin[i].x - shockRadius[i] - scrool.x,
					worldPosOrigin.y - shockOrigin[i].y + shockRadius[i] + scrool.y,

					worldPosOrigin.x + shockOrigin[i].x + shockRadius[i] - scrool.x,
					worldPosOrigin.y - shockOrigin[i].y + shockRadius[i] + scrool.y,

					0, 0,
					512, 512,

					shockWaveGraph,
					WHITE
				);

			}

			/******** プレイヤー描画 **********/
			Novice::DrawQuad(

				(worldPosOrigin.x + playerRotate.q1.x - scrool.x),
				(worldPosOrigin.y - playerRotate.q1.y + scrool.y),

				(worldPosOrigin.x + playerRotate.q2.x - scrool.x),
				(worldPosOrigin.y - playerRotate.q2.y + scrool.y),

				(worldPosOrigin.x + playerRotate.q3.x - scrool.x),
				(worldPosOrigin.y - playerRotate.q3.y + scrool.y),

				(worldPosOrigin.x + playerRotate.q4.x - scrool.x),
				(worldPosOrigin.y - playerRotate.q4.y + scrool.y),

				0,
				0,

				player.graphRadius,
				player.graphRadius,

				player.graph,
				player.color

			);

			Novice::DrawQuad(

				(worldPosOrigin.x + playerDirection.q1.x - scrool.x),
				(worldPosOrigin.y - playerDirection.q1.y + scrool.y),

				(worldPosOrigin.x + playerDirection.q2.x - scrool.x),
				(worldPosOrigin.y - playerDirection.q2.y + scrool.y),

				(worldPosOrigin.x + playerDirection.q3.x - scrool.x),
				(worldPosOrigin.y - playerDirection.q3.y + scrool.y),

				(worldPosOrigin.x + playerDirection.q4.x - scrool.x),
				(worldPosOrigin.y - playerDirection.q4.y + scrool.y),

				0,
				0,

				player.graphRadius,
				player.graphRadius,

				playerDirectionGraph,
				player.color

			);

			if (playFlashEffect == true) {

				Novice::DrawQuad(

					worldPosOrigin.x + player.translate.x - 64 - scrool.x,
					worldPosOrigin.y - player.translate.y - 64 + scrool.y,

					worldPosOrigin.x + player.translate.x + 64 - scrool.x,
					worldPosOrigin.y - player.translate.y - 64 + scrool.y,

					worldPosOrigin.x + player.translate.x - 64 - scrool.x,
					worldPosOrigin.y - player.translate.y + 64 + scrool.y,

					worldPosOrigin.x + player.translate.x + 64 - scrool.x,
					worldPosOrigin.y - player.translate.y + 64 + scrool.y,

					128 * flashEffectFrame,
					0,

					128,
					128,

					flashGraph,
					WHITE

				);

			}

#pragma endregion

			#pragma region UI関連

			if (isCharging == true) {

				Novice::DrawSprite(

					worldPosOrigin.x + chargeGage.translate.x - 5 - scrool.x,
					worldPosOrigin.y - chargeGage.translate.y - 5 + scrool.y,
					chargeGageGraph,
					1,
					1,
					0.0f,
					WHITE

				);

				Novice::DrawBox(

					worldPosOrigin.x + chargeGage.translate.x - scrool.x,
					worldPosOrigin.y - chargeGage.translate.y + scrool.y,
					chargeGage.length.x,
					10,
					0.0f,
					chargeGage.color,
					kFillModeSolid

				);

			}

			Novice::DrawBox(

				worldPosOrigin.x + decoyHPGage.translate.x - scrool.x,
				worldPosOrigin.y - decoyHPGage.translate.y + scrool.y,
				decoyHPGage.length.x,
				10,
				0.0f,
				decoyHPGage.color,
				kFillModeSolid

			);

			Novice::DrawQuad(

				worldPosOrigin.x + decoyHPGage.translate.x - 16 - scrool.x - 30,
				worldPosOrigin.y - decoyHPGage.translate.y - 16 + scrool.y + 5,

				worldPosOrigin.x + decoyHPGage.translate.x + 16 - scrool.x - 30,
				worldPosOrigin.y - decoyHPGage.translate.y - 16 + scrool.y + 5,

				worldPosOrigin.x + decoyHPGage.translate.x - 16 - scrool.x - 30,
				worldPosOrigin.y - decoyHPGage.translate.y + 16 + scrool.y + 5,

				worldPosOrigin.x + decoyHPGage.translate.x + 16 - scrool.x - 30,
				worldPosOrigin.y - decoyHPGage.translate.y + 16 + scrool.y + 5,

				0, 0,
				64, 64,
				decoyHPGraph,
				WHITE

			);

			Novice::DrawBox(

				worldPosOrigin.x + energyAmountGage.translate.x - scrool.x,
				worldPosOrigin.y - energyAmountGage.translate.y + scrool.y,
				20,
				energyAmountGage.length.y,
				0.0f,
				energyAmountGage.color,
				kFillModeSolid

			);

			Novice::DrawQuad(

				worldPosOrigin.x + energyAmountGage.translate.x - 16 - scrool.x + 10,
				worldPosOrigin.y - energyAmountGage.translate.y - 16 + scrool.y + 20,

				worldPosOrigin.x + energyAmountGage.translate.x + 16 - scrool.x + 10,
				worldPosOrigin.y - energyAmountGage.translate.y - 16 + scrool.y + 20,

				worldPosOrigin.x + energyAmountGage.translate.x - 16 - scrool.x + 10,
				worldPosOrigin.y - energyAmountGage.translate.y + 16 + scrool.y + 20,

				worldPosOrigin.x + energyAmountGage.translate.x + 16 - scrool.x + 10,
				worldPosOrigin.y - energyAmountGage.translate.y + 16 + scrool.y + 20,

				0, 0,
				64, 64,
				energyIconGraph,
				WHITE

			);

			#pragma endregion

			#pragma region 画面暗転
			Novice::DrawBox(
				0,
				0,
				kWindowWidth,
				kWindowHeight,
				0.0f,
				0x00000000 + currentBlackOutAlpha,
				kFillModeSolid
			);
			#pragma endregion

			#pragma region リザルト画面

			if (gameFinish == true) {

				Novice::DrawQuad(

					worldPosOrigin.x + resultUI.translate.x - resultUI.radius.x / 2,
					worldPosOrigin.y - resultUI.translate.y - resultUI.radius.y / 2,

					worldPosOrigin.x + resultUI.translate.x + resultUI.radius.x / 2,
					worldPosOrigin.y - resultUI.translate.y - resultUI.radius.y / 2,

					worldPosOrigin.x + resultUI.translate.x - resultUI.radius.x / 2,
					worldPosOrigin.y - resultUI.translate.y + resultUI.radius.y / 2,

					worldPosOrigin.x + resultUI.translate.x + resultUI.radius.x / 2,
					worldPosOrigin.y - resultUI.translate.y + resultUI.radius.y / 2,

					0,
					0,

					resultUI.radius.x,
					resultUI.radius.y,

					resultGraph,
					WHITE

				);

				for (int i = 0; i < 7; i++) {
					Novice::DrawQuad(

						worldPosOrigin.x + scoreUI.translate.x - scoreUI.radius.x / 2 + (scoreUI.radius.x / 2 * i),
						worldPosOrigin.y - scoreUI.translate.y - scoreUI.radius.y / 2,

						worldPosOrigin.x + scoreUI.translate.x + scoreUI.radius.x / 2 + (scoreUI.radius.x / 2 * i),
						worldPosOrigin.y - scoreUI.translate.y - scoreUI.radius.y / 2,

						worldPosOrigin.x + scoreUI.translate.x - scoreUI.radius.x / 2 + (scoreUI.radius.x / 2 * i),
						worldPosOrigin.y - scoreUI.translate.y + scoreUI.radius.y / 2,

						worldPosOrigin.x + scoreUI.translate.x + scoreUI.radius.x / 2 + (scoreUI.radius.x / 2 * i),
						worldPosOrigin.y - scoreUI.translate.y + scoreUI.radius.y / 2,

						0,
						0,

						512,
						512,

						numberGraph[eachScore[i]],
						WHITE

					);
				}

				for (int i = 0; i < 4; i++) {
					Novice::DrawQuad(

						worldPosOrigin.x + killUI.translate.x - killUI.radius.x / 2 + (killUI.radius.x / 2 * i),
						worldPosOrigin.y - killUI.translate.y - killUI.radius.y / 2,

						worldPosOrigin.x + killUI.translate.x + killUI.radius.x / 2 + (killUI.radius.x / 2 * i),
						worldPosOrigin.y - killUI.translate.y - killUI.radius.y / 2,

						worldPosOrigin.x + killUI.translate.x - killUI.radius.x / 2 + (killUI.radius.x / 2 * i),
						worldPosOrigin.y - killUI.translate.y + killUI.radius.y / 2,

						worldPosOrigin.x + killUI.translate.x + killUI.radius.x / 2 + (killUI.radius.x / 2 * i),
						worldPosOrigin.y - killUI.translate.y + killUI.radius.y / 2,

						0,
						0,

						512,
						512,

						numberGraph[eachKillEnemy[i]],
						WHITE

					);
				}

			}

			#pragma endregion

			#pragma region チュートリアル

			if (activeTutorial == true) {

				Novice::DrawQuad(

					worldPosOrigin.x + tutorialUI.translate.x - tutorialUI.radius.x / 2,
					worldPosOrigin.y - tutorialUI.translate.y - tutorialUI.radius.y / 2,

					worldPosOrigin.x + tutorialUI.translate.x + tutorialUI.radius.x / 2,
					worldPosOrigin.y - tutorialUI.translate.y - tutorialUI.radius.y / 2,

					worldPosOrigin.x + tutorialUI.translate.x - tutorialUI.radius.x / 2,
					worldPosOrigin.y - tutorialUI.translate.y + tutorialUI.radius.y / 2,

					worldPosOrigin.x + tutorialUI.translate.x + tutorialUI.radius.x / 2,
					worldPosOrigin.y - tutorialUI.translate.y + tutorialUI.radius.y / 2,

					0,
					0,

					tutorialUI.radius.x,
					tutorialUI.radius.y,

					tutorialGraph[tutorial],
					WHITE

				);

			}

			#pragma endregion


			break;
		case INITIALIZE:



			break;
		}

		#pragma region フェードイン

		Novice::DrawBox(

			0,
			0,
			kWindowWidth,
			kWindowHeight,
			0.0f,
			0x00000000 + currentFadeAlpha,
			kFillModeSolid

		);

		#pragma endregion

#pragma region Debug描画

		/******** プレイヤーデバック描画 **********/
		Novice::ScreenPrintf(0, 10, "killCount : %d", tutorial);
		Novice::ScreenPrintf(0, 30, "killCount : %d", nextTutorial);
		Novice::ScreenPrintf(0, 50, "killCount : %d", isEndTutorialAnim);
		Novice::ScreenPrintf(0, 70, "killCount : %d", activeTutorial);
		Novice::ScreenPrintf(0, 90, "killCount : %d", onceActive);
		Novice::ScreenPrintf(0, 110, "killCount : %4.2f", tutorialUI.time);
		Novice::ScreenPrintf(0, 130, "killCount : %d", activeTutorialTime);

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