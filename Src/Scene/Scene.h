
#ifndef __SCENE_H__
#define __SCENE_H__

// 背景情報
#define BG_PATH "Data/Background/Bg.png" //背景のパス

// タイトルシーンのID
#define SCENE_ID_INIT_TITLE (100) //初期化
#define SCENE_ID_LOOP_TITLE (101) //繰り返し
#define SCENE_ID_FIN_TITLE  (102) //後処理 

// プレイシーンのID
#define SCENE_ID_INIT_PLAY (200) //初期化
#define SCENE_ID_LOOP_PLAY (201) //繰り返し
#define SCENE_ID_FIN_PLAY  (202) //後処理

// クリアシーンのID
#define SCENE_ID_INIT_CLEAR (300) //初期化
#define SCENE_ID_LOOP_CLEAR (301) //繰り返し
#define SCENE_ID_FIN_CLEAR  (302) //後処理

// ゲームオーバーシーンのID
#define SCENE_ID_INIT_GAMEOVER (400) //初期化
#define SCENE_ID_LOOP_GAMEOVER (401) //繰り返し
#define SCENE_ID_FIN_GAMEOVER  (402) //後処理

// 現在のシーンID
extern int g_CurrentSceneID;

#endif