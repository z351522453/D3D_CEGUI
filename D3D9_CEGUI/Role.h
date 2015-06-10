#pragma once
#include <string>
#include <windows.h>
#include "GameHOOK.h"
#include <map>

class CRole {
public:
    virtual ~CRole();
    static CRole* GetInstance();
    static int GetRoleAddr();
    static int WhereIsRole(); // 当前人物位置, 0: 城镇  2: FB
    static void SendPackage(DWORD PDATA);
    static std::string GetRoleMap(); // 获取当前地图
    static std::string GetRoleZone(); // 获取当前副本
    static void CityFly(std::string strKey); // 城镇传送
    static int GetRoleRoom(); // 获取当前房间
    static void TeleportToPoint(float fx, float fy, float fz);
    static void RoleTeleport(int nKey, float fx, float fy, float fz);
    static void GetPoint(float& fx, float& fy, float& fz);
    static void ByMap(const char* szKey); // 副本过图
    static void Turn(); // 转向
    static BOOL TurntoBoss(int nKey);
    static void Attack_Pack(int nPart); // 攻击封包
    static void GoForward();
    static void GoLeft();
    static void GoRight();
    static void GoBack();
    static void Stop(std::string pos);
    static void Attack();
    static void Roll();
    static int HaveWeapon();
    static int HaveMode();
    static void Weapon();
    static void ChangeMode();
    static float GetHpPer(); // 获取血量百分比
    static void Invincible(); // 开无敌
    static void UnInvincible(); // 关无敌
    static void CatInvincible(); // 猫无敌

    static std::map<int, std::string> s_allItems; // 游戏内所有物品
    static void initAllItems();

protected:
    int         m_nRoleAddr; // 人物指针
    static BOOL Attack_Pack_Boss(int nBossKey, int nPart);
    static void Send_Attack_Pack(int nRoleKey, int nBoosKey, float fx, float fy, float fz, int nPart);
    static int Decode(int nData); // 数据解密

private:
    CRole();
    static CRole*  m_cInstance;
    static CGameHOOK m_hook; // 用来实现人物无敌
    static CGameHOOK m_CatHook; // 用来实现猫无敌
};