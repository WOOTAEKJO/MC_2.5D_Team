#pragma once
//#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)

class CGameObject;

class CImGuiMgr

{
    DECLARE_SINGLETON(CImGuiMgr)

public:
    enum OBJECTKEY { KEY_HUMAN, KEY_QUADRUPEDAL,KEY_MONSTER, KEY_ITEM };

private:
    explicit CImGuiMgr();
    virtual  ~CImGuiMgr();

public:
    HRESULT Ready_ImGuiMgr();

    void    Tool();                 // ��� �� ���

    void    Set_GraphicDev(LPDIRECT3DDEVICE9 pGraphicDev) { m_pGraphicDev = pGraphicDev; }  // �׷��� ��ġ�� �������� ����

    void    Parts_Setting();        // �����

public:  // �ִϸ��̼�
    void    AnimationTool();        // �ִϸ��̼� ��
    void    Frame();                // �⺻���� ������ ����
    void    Distribute();           // ����, �� �������� ���ؼ� ��ü������ �������� �й��Ѵ�.
    void    FixFrame();             // ������ ����, ����, ��ġ/���� �� ����
    void    Movement();             // ���� ���� 
    void    AddFrame();             // �������� �߰��� �� �ɼ�

    void    SaveAnimationData();    // �ִϸ��̼� ������ ����
    void    LoadAnimationData();    // �ִϸ��̼� ������ �ε�
public: // ���� �ִϸ��̼�

    void    MonAnimationTool();        // �ִϸ��̼� ��
    void    MonFrame();                // �⺻���� ������ ����
    void    MonDistribute();           // ����, �� �������� ���ؼ� ��ü������ �������� �й��Ѵ�.
    void    MonFixFrame();             // ������ ����, ����, ��ġ/���� �� ����
    void    MonMovement();             // ���� ���� 
    void    MonAddFrame();             // �������� �߰��� �� �ɼ�
    void    MonETC_Select_Par();       // etc �θ� ����

    void    SaveMonAnimationData(); // ���� �ִϸ��̼� ������ ����
    void    LoadMonAnimationData(); // ���� �ִϸ��̼� ������ �ε�

public: // ������Ʈ
    void    ObjectTool();            // ������Ʈ ��
    void    ObjectCreate();          // ������Ʈ ����
    void    ObjectSetting();         // ������ ������Ʈ ����

    void    SaveObjectData();       // ������Ʈ ������ ������ ����
    void    LoadObjectData();       // ������Ʈ ������ ������ �ε�

    void    SaveObjectInformationData();    // ������Ʈ ��ü ���� ������ ����
    void    LoadObjectInforamtionData();    // ������Ʈ ��ġ ���� ������ �ε�

public: // �ִϸ��̼�
    _float* Get_Speed() { return &m_fSpeed; }
    _int* Get_FrameIndex() { return &m_iFrameIndex; }
    _int* Get_MovementFrameIndex() { return &m_iMovementFrameIndex; }
    _bool* Get_AnimationCheck() { return &m_bAnimationCheck; }
    _bool* Get_MovementFrameCheck() { return &m_bMovementFrameCheck; }
    vector<FRAME*>* Get_Parts() { return &m_vecParts; }
    vector<FRAME*>* Get_Movement() { return &m_vecMovement[m_iMovementIndex]; }

    void            Set_Total(const _float& fX, const _float& fY, const _float& fZ) {
        for (_ulong i = 0; i < m_vecParts.size(); i++) {
            m_vecParts[i][TOTAL].vPosition = { fX,fY,fZ };
        }
    }
public:  // ���� �ִϸ��̼�
    _float* Get_MonSpeed() { return &m_fMonSpeed; }
    _int* Get_MonFrameIndex() { return &m_iMonFrameIndex; }
    _int* Get_MonMovementFrameIndex() { return &m_iMonMovementFrameIndex; }
    _bool* Get_MonAnimationCheck() { return &m_bMonAnimationCheck; }
    _bool* Get_MonMovementFrameCheck() { return &m_bMonMovementFrameCheck; }
    vector<MONSTERFRAME*>* Get_MonParts() { return &m_vecMonParts; }
    vector<MONSTERFRAME*>* Get_MonMovement() { return &m_vecMonMovement[m_iMonMovementIndex]; }
    //vector<MONSTERPARTS*>* Get_MonETCPar() { return &m_vecETCPar; }

    void            Set_MonTotal(const _float& fX, const _float& fY, const _float& fZ) {
        for (_ulong i = 0; i < m_vecMonParts.size(); i++) {
            m_vecMonParts[i][(_uint)MONSTERPARTS::TOTAL].vPosition = { fX,fY,fZ };
        }
    }

public:  // ������Ʈ
    _bool* Get_ObjectTextureMode() { return &m_bSelectTexture; }
    _int* Get_ObjectColorNum() { return &m_iColorTextureIndex; }
    TOTALITEMINFO* Get_ItemDemo() { return m_ItemTotal; }

    void    Set_ItemPartInfo(vector<PARTSITEMINFO*>* vecItemPartsInfo) { 
        
        for_each(m_vecItemPartsSave.begin(), m_vecItemPartsSave.end(), CDeleteObj2());
        m_vecItemPartsSave.clear();

            for (_int i = 0; i < vecItemPartsInfo->size(); i++) {
                PARTSITEMINFO* pTemp = new PARTSITEMINFO;
                pTemp->iTextureNum = (*vecItemPartsInfo)[i]->iTextureNum;
                pTemp->vPosition = (*vecItemPartsInfo)[i]->vPosition;

                m_vecItemPartsSave.push_back(pTemp);
            }
        }
    vector<PARTSITEMINFO*>* Get_ItemPartInfo() { return &m_vecItemPartsLoad; }

private: // ����
    LPDIRECT3DDEVICE9			        m_pGraphicDev=nullptr;  // �׷��� ī�� ��ġ  
    map<OBJECTKEY, CGameObject*>        m_mapObject;    // ���� ������Ʈ�� �����ؼ� ����
private: // �ִϸ��̼�
    _float				m_fSpeed;                       // �ִϸ��̼� �ӵ� ��

    _int                m_iFrameIndex;                  // �ΰ��� ������ ������ �����ϴ� �ε���
    _int                m_iMovementIndex;               // �ΰ��� ������ ������ �����ϴ� �ε���
    _int                m_iMovementFrameIndex;          // �� ������ ������ �ε���
    _bool               m_bAnimationCheck;              // �ΰ��� ������ �ִϸ��̼��� ���� ���� ����

    vector<FRAME*>      m_vecParts;                     // �ΰ��� ���� ������ ������ ��� ����/ �����͸� �� ���͸� �̿��ؼ� ����
    vector<vector<FRAME*>> m_vecMovement;               // ������ ��� ����
    string              m_strText;                      // �ִϸ��̼� ������ ������ �� Ű ��
    const _tchar* m_AniTag;                             // �ִϸ��̼� ������ �ҷ��� �� �޾� �� Ű ��

    _int                m_iFrameRange[2];               // �ִϸ��̼� ������ �������� ������ ���� ����(���� ������/ �� ������)
    _float              m_iRotRange[2];                 // �ִϸ��̼� ������ �������� ���� ����/ �� ����

    _int                m_iMovementRagne[2];            // ���� �ε���/ �� �ε����� �����ؼ� �� ������ �����.

    _int                m_iMovementAddRange[2];         // ���� ����/ �� ���۸� �����ؼ� �ϳ��� ��ģ��.

    _int                m_iFrameNum;                    // ���� ������ ��
    _int                m_iFrameIndexSelect[2];         // ���� ���� ������ �ε����� �� ������ �ε����� ����

    _bool               m_bLastFrameCheck;              // �ִϸ��̼� �������� ���� ������ �� �������� ���� �����ϴ����� üũ
    _bool               m_bMovementFrameCheck;          // ���� �������� ȭ�鿡 ����ϱ� ���� �뵵

private: // ���� �ִϸ��̼�
    _float				m_fMonSpeed;                       // �ִϸ��̼� �ӵ� ��

    _int                m_iMonFrameIndex;                  // �ΰ��� ������ ������ �����ϴ� �ε���
    _int                m_iMonMovementIndex;               // �ΰ��� ������ ������ �����ϴ� �ε���
    _int                m_iMonMovementFrameIndex;          // �� ������ ������ �ε���
    _bool               m_bMonAnimationCheck;              // �ΰ��� ������ �ִϸ��̼��� ���� ���� ����

    vector<MONSTERFRAME*>      m_vecMonParts;                     // �ΰ��� ���� ������ ������ ��� ����/ �����͸� �� ���͸� �̿��ؼ� ����
    vector<vector<MONSTERFRAME*>> m_vecMonMovement;               // ������ ��� ����
    string              m_strMonText;                      // �ִϸ��̼� ������ ������ �� Ű ��
    const _tchar* m_MonAniTag;                             // �ִϸ��̼� ������ �ҷ��� �� �޾� �� Ű ��

    _int                m_iMonFrameRange[2];               // �ִϸ��̼� ������ �������� ������ ���� ����(���� ������/ �� ������)
    _float              m_iMonRotRange[2];                 // �ִϸ��̼� ������ �������� ���� ����/ �� ����

    _int                m_iMonMovementRagne[2];            // ���� �ε���/ �� �ε����� �����ؼ� �� ������ �����.

    _int                m_iMonMovementAddRange[2];         // ���� ����/ �� ���۸� �����ؼ� �ϳ��� ��ģ��.

    _int                m_iMonFrameNum;                    // ���� ������ ��
    _int                m_iMonFrameIndexSelect[2];         // ���� ���� ������ �ε����� �� ������ �ε����� ����

    _bool               m_bMonLastFrameCheck;              // �ִϸ��̼� �������� ���� ������ �� �������� ���� �����ϴ����� üũ
    _bool               m_bMonMovementFrameCheck;          // ���� �������� ȭ�鿡 ����ϱ� ���� �뵵
    //vector<MONSTERPARTS*> m_vecETCPar;                      // ETC �θ� ��� ����

private: // ������Ʈ
    TOTALITEMINFO* m_ItemTotal = nullptr;           // ������ ��ü�� �ش��ϴ� ������ ����
    vector<PARTSITEMINFO*>       m_vecItemPartsSave;    // ������ ������ ������ �����ϴ� ����
    vector<PARTSITEMINFO*>       m_vecItemPartsLoad;    // ������ ������ ������ �ҷ����� ����  -> ��� �ҷ����� �����ϰ� �ϱ� ���� 2���� ����

    string                       m_strItemPartsText;    // ������ ������ ������ ������ �� ������ Ű ��
    _int                        m_iObjectCreatIndex;    // ���� ������ �� �޺��ڽ����� �����ϴ� �ε���

    _bool                       m_bSelectTexture;       // ������Ʈ �ؽ��� ���

    _int                        m_iColorTextureIndex;   // ������Ʈ ���� �ؽ���
private:
    virtual void    Free();
};

END

