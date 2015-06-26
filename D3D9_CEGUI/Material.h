#pragma once
#include <string>
#include <list>
#include <windows.h>

/*-----------------------------------------------------------------------
* ����: CMaterial
* ˵��: ������, ��Ϸ������Ͽɲɼ�����Ʒ
-----------------------------------------------------------------------*/

typedef struct MATERIAL {
    std::string strName;
    float fPointX;
    float fPointY;
    float fPointZ;
    int nID;
    int nKey;
    std::string strType; // ��� 1:���ڿ󹤾ߣ�,2:ҩ��,3:���棨���湤�ߣ�,5:Ģ��,6:����,7:����Сʯͷ,8:���,0xA:����ʬ��,0xC:��ͷ,0x11:��
    //int nIndex; //�����
} material, *pMaterial;

class CMaterial {
public:
    void initMaterial(); // ������ǰ����ĵ�����Ʒ, ��ʼ�� m_material_list �б�
    void initMaterial_2(); // ������ǰ����ĵ�����Ʒ, ��ʼ�� m_material_list �б�. �ڶ��ַ���
    static std::list<material> m_material_list;
};
