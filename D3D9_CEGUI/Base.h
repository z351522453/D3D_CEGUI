#pragma once
#include <windows.h>

//基址
const DWORD BASE_GAME = 0x025F3D00;   // 游戏基址   地址: 55D960
const DWORD BASE_TASK = 0x025F4090;   // 任务基址   地址: 535A44
const DWORD BASE_KEYBOARD_HANDLER = 0x0201C0CC;   // 按键处理类基址   地址: 6B9E2B
const DWORD BASE_CAMERA = 0x022B2EC8;   // 摄像机相关基址   地址: 150BB1C
const DWORD BASE_LOADING_FLAG = 0x02092E54;   // 正在过图标志（0：不在过图，1:正在过图。）   地址: 75D26E
const DWORD BASE_CURRENT_MAP_OBJECTS = 0x0201C108;   // 当前地图中的所有对象遍历基址   地址: 6B51F2
const DWORD BASE_CURRENT_MAP_OBJECTS2 = 0x0255AE7C;   // 当前地图中的所有对象遍历2基址   地址: 1B8F894
const DWORD BASE_AUCTION = 0x025F3FF4;   // 拍卖行数据基址   地址: 46E100
const DWORD BASE_SUPPLY_BOX = 0x0201C180;   // 补给箱基址   地址: 6B53C0
const DWORD BASE_REWARD_TASK = 0x025F40D4;   // 悬赏任务信息基址   地址: 559B4F
const DWORD BASE_SETTINGS = 0x022B2ECC;   // 游戏设置相关基址   地址: 15082A8
//调用
const DWORD CALL_VALUE_DECRYPT = 0x01B91DE0;   // 加密值解密函数   地址: 55D9A0
const DWORD CALL_VALUE_DECRYPT2 = 0x0469740;   // 加密值解密函数2   地址: 53932E
const DWORD CALL_KEYBOARD_EVENT_HANDLE = 0x016ADF50;   // 按键消息处理   地址: 16AE300
const DWORD CALL_TELESPORT = 0x09367E0;   // 瞬移CALL   地址: 94DA95
const DWORD CALL_SEND_PACKET = 0x69C460;   // 发包CALL（取左边的值）   地址: 69C460
const DWORD CALL_INJURE = 0x01339890;   // 攻击伤害CALL   地址: 1515068
const DWORD CALL_COMMON_FUNCTION = 0x012E9500;   // 通用调用函数   地址: 12EC6FB
const DWORD CALL_SWITCH_REGION = 0x0137F880;   // 顺图   地址: 139B6FF
const DWORD CALL_COLLECTING = 0x05E54D0;   // 采集物品   地址: 61481A
const DWORD CALL_COLLECTING2 = 0x01B62440;   // 采集物品2   地址: 5E6140
const DWORD CALL_MOVE_INVENTORY_ITEM = 0x05F5C80;   // 将背包物品存入仓库   地址: 5480AC
const DWORD CALL_GET_OBJECT_IDLE_STATE = 0x01581090;   // 获取对象空闲标识（1：空闲，0：繁忙）   地址: 153B763
const DWORD CALL_ATTACK = 0x14A4920;   // 左键攻击CALL（取左边的值）   地址: 14A4920
const DWORD CALL_GET_GLOBAL_VARIABLE = 0x076FA20;   // 根据名称获取游戏中的全局变量   地址: 4415E8
const DWORD CALL_GET_ROLE_LIST_INFO = 0x0139C540;   // 获取角色列表相关的指针   地址: 51C822
const DWORD CALL_GET_REWARD_TASK_STATUS = 0x055A3D0;   // 获取悬赏任务状态   地址: 559F1E
const DWORD CALL_GET_FARM_INFO = 0x01325BD0;   // 获取庄园信息指针   地址: 132622E
const DWORD CALL_GET_COLLECTED_TIME = 0x0469740;   // 获取猎友庄园已采集次数   地址: 620A8E
const DWORD CALL_DO_ACTION = 0x02B653A2;   // 执行攻击，闪避等动作   地址: 14F1DB8
const DWORD CALL_GET_UI_MODE = 0x01529F90;   // 获取菜单开启状态（鼠标指针显示）   地址: 13AE68A
const DWORD CALL_BAKE_1 = 0x060D3F0;   // 烤肉1   地址: 5F5A97
const DWORD CALL_PLAY_ACTION = 0x01496D30;   // 开始烤肉等动画   地址: 138C53F
const DWORD CALL_GET_COPY_UNLOCK_STATE = 0x057CB70;   // 获取副本解锁状态   地址: 57B2E6
//偏移
const DWORD OFFSET_ROLE_INFO_1 = 0x0C8;   // 当前人物指针偏移1   地址: 55D966
const DWORD OFFSET_ROLE_INFO_2 = 0x028;   // 当前人物指针偏移2(取byte)   地址: 55D96C
const DWORD OFFSET_ROLE_INFO_3 = 0x0A8;   // 当前人物指针偏移3   地址: 45E8F8
const DWORD OFFSET_ROLE_INFO_4 = 0x0214;   // 当前人物指针偏移4   地址: 621C02
const DWORD OFFSET_ROLE_LEVEL = 0x0434;   // 人物等级加密数值偏移   地址: 55DA28
const DWORD OFFSET_GET_ROLE_NAME = 0x0B0;   // 获取人物名称的CALL相对于HandlerTable的偏移   地址: 55DD1E
const DWORD OFFSET_ROLE_HP = 0x04DC;   // 人物血量偏移   地址: 55E3EC
const DWORD OFFSET_NEARBY_OBJECT = 0x50;   // 周围对象叉树偏移(取byte)   地址: 9513DE
const DWORD OFFSET_NEARBY_OBJECT_ROOT = 0x09C;   // 周围对象叉树的根偏移   地址: 92A6D4
const DWORD OFFSET_COOR = 0x60;   // 坐标相对于对象指针的偏移（取byte）   地址: 1BF70AA
const DWORD OFFSET_ROLE_ENDURE = 0x0576;   // 人物最大耐力   地址: 55D9D9
const DWORD OFFSET_ROLE_CURHP = 0x04D4;   // 人物当前血量   地址: 55D9BA
const DWORD OFFSET_ROLE_CURENDURE = 0x056E;   // 人物当前耐力   地址: 55D9F8
const DWORD OFFSET_KEYBOARD_HANDLER = 0x48;   // 按键处理类偏移（取byte）   地址: 16A7817
const DWORD OFFSET_CAREMA_1 = 0x0D0;   // 摄像机类偏移1   地址: 150BB22
const DWORD OFFSET_CAREMA_2 = 0x05C;   // 摄像机类偏移2（取byte）   地址: 150BB28
const DWORD OFFSET_CAREMA_ANGLE = 0x0160;   // 摄像机类视角偏移   地址: 13A4C30
const DWORD OFFSET_SEND_PACKET_ECX_1 = 0x0435C;   // 发包ECX偏移1   地址: 54739F
const DWORD OFFSET_SEND_PACKET_ECX_2 = 0x0F8;   // 发包ECX偏移2   地址: 5F4D8A
const DWORD OFFSET_SEND_PACKET_ECX_3 = 0x1C;   // 发包ECX偏移3（取byte）   地址: 6269FF
const DWORD OFFSET_CITY_FLAG_1 = 0x0435C;   // 城镇标识偏移1   地址: 547A76
const DWORD OFFSET_CITY_FLAG_2 = 0x0F8;   // 城镇标识偏移2   地址: 5F6C4C
const DWORD OFFSET_CITY_FLAG_3 = 0x1C;   // 城镇标识偏移3(取byte)   地址: 626907
const DWORD OFFSET_CITY_FLAG_4 = 0x24;   // 城镇标识偏移4(取byte)   地址: 69C468
const DWORD OFFSET_CITY_FLAG_5 = 0x088;   // 城镇标识偏移5   地址: 69C56B
const DWORD OFFSET_SELECT_COPY = 0x0174;   // 选择副本偏移   地址: 133A79A
const DWORD OFFSET_ATTACK = 0x01A2A;   // 角色攻击力偏移   地址: 55D98E
const DWORD OFFSET_GET_TELESPORT_PTR = 0x080;   // 获取瞬移写入数据的指针   地址: 1558336
const DWORD OFFSET_GET_SWITCH_REGION_ECX = 0x0178;   // 获取顺图的ECX   地址: 14A532A
const DWORD OFFSET_CURRENT_MAP_OBJECTS2 = 0x074;   // 当前地图中的所有对象遍历2偏移（取BYTE）   地址: 4651FC
const DWORD OFFSET_COLLECTING_PARAM_1 = 0x09C;   // 采集CALL的参数偏移1   地址: 46535C
const DWORD OFFSET_COLLECTING_PARAM_2 = 0x064;   // 采集CALL的参数偏移2(取byte)   地址: 465362
const DWORD OFFSET_COLLECTING_ACTION = 0x020B4;   // 当前正在进行采集的动作信息   地址: 1BB71FB
const DWORD OFFSET_GET_OBJECT_DETAIL = 0x025C;   // 根据对象指针获取对象详情指针   地址: 150DBB7
const DWORD OFFSET_CURRENT_MAP_ENTITY_COUNT = 0x0600C0;   // 当前地图中的对象数量偏移   地址: 92A067
const DWORD OFFSET_CURRENT_MAP_ENTITY_ARRAY = 0x5C;   // 当前地图中的对象数组首地址偏移（取BYTE）   地址: 92A076
const DWORD OFFSET_OBJECT_ENG_NAME = 0x0EC;   // 对象英文名偏移   地址: 92C9FC
const DWORD OFFSET_WEAPON = 0x01440;   // 人物当前手持武器的Key偏移   地址: 1362AD9
const DWORD OFFSET_ROLE_IDLE_STATE_1 = 0x01B80;   // 人物是否空闲偏移1   地址: 1382AE3
const DWORD OFFSET_ROLE_IDLE_STATE_2 = 0x024;   // 人物是否空闲偏移2（取byte）   地址: 1505EBA
const DWORD OFFSET_ROLE_IDLE_STATE_3 = 0x0135C;   // 人物是否空闲偏移3   地址: 1506A24
const DWORD OFFSET_ATTACK_PARAM1 = 0x01D90;   // 左键攻击参数1偏移   地址: 1382B12
const DWORD OFFSET_ATTACK_PARAM2_1 = 0x0D8;   // 左键攻击参数2偏移1   地址: 14C5749
const DWORD OFFSET_ATTACK_PARAM2_2 = 0x031C;   // 左键攻击参数2偏移2   地址: 14F1B0B
const DWORD OFFSET_IS_DEAD = 0x0F4;   // 对象死亡判断CALL在虚表中的偏移   地址: 1362949
const DWORD OFFSET_ATTACK_PART = 0x048;   // 攻击部位偏移(取byte)   地址: 13318BE
const DWORD OFFSET_NO_DELAY_USE_ITEM_PACKET3_PARAM1 = 0x011C;   // 无延迟使用物品第3个封包的参数1偏移   地址: 1BBDD38
const DWORD OFFSET_GET_TIMESTAMP = 0x0228;   // 获取时间戳函数在虚表中的偏移   地址: 164C7D3
const DWORD OFFSET_GET_COLLECT_ITEM_TYPE = 0x01AC;   // 获取采集物类别   地址: 46524B
const DWORD OFFSET_GET_SUPPLY_BOX = 0x0164;   // 获取补给箱的函数在虚表中的偏移   地址: 6332CA
const DWORD OFFSET_GET_ROLE_LIST = 0x028;   // 获取角色列表的函数在虚表中的偏移（取byte）   地址: 51C82D
const DWORD OFFSET_GET_ALL_REWARD_TASK = 0x0D8;   // 获取所有悬赏任务信息的函数在虚表中的偏移   地址: 1C28C59
const DWORD OFFSET_ROLE_FARM = 0x03F88;   // 庄园信息偏移   地址: 5E4A6A
const DWORD OFFSET_GET_COLLECTED_TIME_ECX = 0x01A5A;   // 获取猎友庄园已采集次数   地址: 620A6C
const DWORD OFFSET_DODGE_ACTION = 0x0334;   // 闪避动作   地址: 14F1DB2
const DWORD OFFSET_EXP_LIMIT = 0x019B0;   // 当天经验限制剩余   地址: 539329
const DWORD OFFSET_REWARD_TASK_STARLEVEL = 0x0D8;   // 悬赏任务星级   地址: 55A082
const DWORD OFFSET_SETTINGS_ATTACK_AUTO_DIR = 0x0918;   // 第一击方向调整设置（F11）   地址: 15082AE
const DWORD OFFSET_SWAP_INVENTORY_ITEM = 0x04C;   // 穿装备函数在虚表中的偏移(取byte)   地址: 5474CA
const DWORD OFFSET_CURRENT_FORM = 0x01A8;   // 当前所在界面   地址: 1594AB7
const DWORD OFFSET_GET_ENTRUST_TASK_COUNT_ECX = 0x020A0;   // 获取今天已完成的公会委托任务次数的ECX   地址: 5696A1
const DWORD OFFSET_GET_ENTRUST_TASK_COUNT = 0x0D2FF5050;   // 获取今天已完成的公会委托任务次数的函数在虚表中的偏移（取BYTE）   地址: 5696B0
//常量
const DWORD SIZE_SALE_ITEM = 0x68;   // 商店物品信息结构体大小（取byte）   地址: 517011
//挂钩处
const DWORD HOOK_TELESPORT = 0x9EA2FB;   // 瞬移Hook处(取左边的值)   地址: 9EA2FB
const DWORD HOOK_INJURE = 0x1515060;   // 伤害包发送HOOK(取左边的值)   地址: 1515060
const DWORD HOOK_INVINCIBLE = 0x1385605;   // 当前人物受伤HOOK(取左边的值)（Nop掉6个字节可实现无敌）   地址: 1385605
const DWORD HOOK_SWITCH_REGION = 0x139B6F5;   // 顺图脚本录制HOOK处(取左边的值)   地址: 139B6F5
const DWORD HOOK_ABNORMAL_STATE = 0x1526049;   // 屏蔽迷糊、颤抖、麻痹、睡眠等不正常状态   地址: 1526049