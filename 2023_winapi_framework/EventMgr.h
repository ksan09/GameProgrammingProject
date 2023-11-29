#pragma once
class Object;
struct tEvent
{
	EVENT_TYPE eEve; // �̺�Ʈ Ÿ��
	Object* Obj;
	wstring SceneName;
	OBJECT_GROUP ObjType;
};
class EventMgr
{
	SINGLE(EventMgr);
public:
	void Update();
	void DeleteObject(Object* _pObj);
	void SceneChange(wstring _wSceneName);
private:
	void Excute(const tEvent& _eve);
private:
	vector<tEvent> m_vecEvent;
	vector<Object*> m_vecDead;
};

