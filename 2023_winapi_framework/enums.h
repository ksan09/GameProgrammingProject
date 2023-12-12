#pragma once

enum class KEY_STATE
{
	// NONE: �ȴ���
	// DOWN: �� ����
	// UP: ��
	// PRESS: ��������
	NONE, DOWN, UP, PRESS
};

enum class KEY_TYPE
{
	LEFT, RIGHT, UP, DOWN,
	Q,W,E,R,T,Y,U,I,O,P,
	A,S,D,F,G,H,J,K,L,
	Z,X,C,V,B,N,M,
	CTRL, LALT, LSHIFT, SPACE,
	ENTER, TAB, ESC, LBUTTON, RBUTTON, LAST
	// LAST�ǹ�: ���̶�� ���̾�
};

enum class OBJECT_GROUP
{
	DEFAULT,
	PLAYER_DIR_COL,
	OBJ,
	BOTTOM_COL,
	PLAYER,
	BOSS,
	EFFECT,
	END = 30
};

enum class PEN_TYPE
{
	HOLLOW, RED, GREEN, 
	BLUE, YELLOW, END
};

enum class BRUSH_TYPE
{
	HOLLOW, RED, GREEN,
	BLUE, YELLOW, END
};

enum class EVENT_TYPE
{
	DELETE_OBJECT,
	CREATE_OBJECT,
	SCENE_CHANGE,
	END
};

enum class PLAYER_STATE
{
	Idle,
	MoveLeft,
	MoveRight,
	JumpLeft,
	JumpRight,
	FallLeft,
	FallRight,
};

enum class DIR
{
	LEFT, TOP, RIGHT, BOTTOM
};

enum class NODE_STATE
{
	SUCCESS, FAILURE, RUNNING
};

enum class STAGE_CLEAR
{
	S1, S2, S3,
	S12, S23, S13,
	ALL
};