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

    void    Tool();                 // 모든 툴 출력

    void    Set_GraphicDev(LPDIRECT3DDEVICE9 pGraphicDev) { m_pGraphicDev = pGraphicDev; }  // 그래픽 장치를 가져오기 위함

    void    Parts_Setting();        // 참고용

public:  // 애니메이션
    void    AnimationTool();        // 애니메이션 툴
    void    Frame();                // 기본적인 프레임 관련
    void    Distribute();           // 시작, 끝 프레임을 정해서 전체적으로 프레임을 분배한다.
    void    FixFrame();             // 지정된 범위, 파츠, 위치/각도 를 수정
    void    Movement();             // 동작 관련 
    void    AddFrame();             // 프레임을 추가할 때 옵션

    void    SaveAnimationData();    // 애니메이션 데이터 저장
    void    LoadAnimationData();    // 애니메이션 데이터 로드
public: // 몬스터 애니메이션

    void    MonAnimationTool();        // 애니메이션 툴
    void    MonFrame();                // 기본적인 프레임 관련
    void    MonDistribute();           // 시작, 끝 프레임을 정해서 전체적으로 프레임을 분배한다.
    void    MonFixFrame();             // 지정된 범위, 파츠, 위치/각도 를 수정
    void    MonMovement();             // 동작 관련 
    void    MonAddFrame();             // 프레임을 추가할 때 옵션
    void    MonETC_Select_Par();       // etc 부모를 결정

    void    SaveMonAnimationData(); // 몬스터 애니메이션 데이터 저장
    void    LoadMonAnimationData(); // 몬스터 애니메이션 데이터 로드

public: // 오브젝트
    void    ObjectTool();            // 오브젝트 툴
    void    ObjectCreate();          // 오브젝트 생성
    void    ObjectSetting();         // 생성한 오브젝트 세팅

    void    SaveObjectData();       // 오브젝트 파츠별 데이터 저장
    void    LoadObjectData();       // 오브젝트 파츠별 데이터 로드

    void    SaveObjectInformationData();    // 오브젝트 전체 기준 데이터 저장
    void    LoadObjectInforamtionData();    // 오브젝트 전치 기준 데이터 로드

public: // 애니메이션
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
public:  // 몬스터 애니메이션
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

public:  // 오브젝트
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

private: // 공용
    LPDIRECT3DDEVICE9			        m_pGraphicDev=nullptr;  // 그래픽 카드 장치  
    map<OBJECTKEY, CGameObject*>        m_mapObject;    // 데모 오브젝트를 생성해서 보관
private: // 애니메이션
    _float				m_fSpeed;                       // 애니메이션 속도 값

    _int                m_iFrameIndex;                  // 인간형 데모의 파츠를 선택하는 인덱스
    _int                m_iMovementIndex;               // 인간형 데모의 동작을 선택하는 인덱스
    _int                m_iMovementFrameIndex;          // 한 동작의 프레임 인덱스
    _bool               m_bAnimationCheck;              // 인간형 데모의 애니메이션을 돌릴 지를 선택

    vector<FRAME*>      m_vecParts;                     // 인간형 데모 파츠별 정보를 담는 벡터/ 데이터를 이 벡터를 이용해서 저장
    vector<vector<FRAME*>> m_vecMovement;               // 동작을 담는 벡터
    string              m_strText;                      // 애니메이션 정보를 저장할 때 키 값
    const _tchar* m_AniTag;                             // 애니메이션 정보를 불러올 때 받아 올 키 값

    _int                m_iFrameRange[2];               // 애니메이션 프레임 수정에서 프레임 벡터 범위(시작 프레임/ 끝 프레임)
    _float              m_iRotRange[2];                 // 애니메이션 프레임 수정에서 시작 각도/ 끝 각도

    _int                m_iMovementRagne[2];            // 시작 인덱스/ 끝 인덱스를 설정해서 한 동작을 만든다.

    _int                m_iMovementAddRange[2];         // 시작 동작/ 끝 동작를 설정해서 하나로 합친다.

    _int                m_iFrameNum;                    // 나눌 프레임 수
    _int                m_iFrameIndexSelect[2];         // 나눌 시작 프레임 인덱스와 끝 프레임 인덱스를 선택

    _bool               m_bLastFrameCheck;              // 애니메이션 프레임을 새로 생성할 때 마지막과 같이 생성하는지를 체크
    _bool               m_bMovementFrameCheck;          // 동작 프레임을 화면에 출력하기 위한 용도

private: // 몬스터 애니메이션
    _float				m_fMonSpeed;                       // 애니메이션 속도 값

    _int                m_iMonFrameIndex;                  // 인간형 데모의 파츠를 선택하는 인덱스
    _int                m_iMonMovementIndex;               // 인간형 데모의 동작을 선택하는 인덱스
    _int                m_iMonMovementFrameIndex;          // 한 동작의 프레임 인덱스
    _bool               m_bMonAnimationCheck;              // 인간형 데모의 애니메이션을 돌릴 지를 선택

    vector<MONSTERFRAME*>      m_vecMonParts;                     // 인간형 데모 파츠별 정보를 담는 벡터/ 데이터를 이 벡터를 이용해서 저장
    vector<vector<MONSTERFRAME*>> m_vecMonMovement;               // 동작을 담는 벡터
    string              m_strMonText;                      // 애니메이션 정보를 저장할 때 키 값
    const _tchar* m_MonAniTag;                             // 애니메이션 정보를 불러올 때 받아 올 키 값

    _int                m_iMonFrameRange[2];               // 애니메이션 프레임 수정에서 프레임 벡터 범위(시작 프레임/ 끝 프레임)
    _float              m_iMonRotRange[2];                 // 애니메이션 프레임 수정에서 시작 각도/ 끝 각도

    _int                m_iMonMovementRagne[2];            // 시작 인덱스/ 끝 인덱스를 설정해서 한 동작을 만든다.

    _int                m_iMonMovementAddRange[2];         // 시작 동작/ 끝 동작를 설정해서 하나로 합친다.

    _int                m_iMonFrameNum;                    // 나눌 프레임 수
    _int                m_iMonFrameIndexSelect[2];         // 나눌 시작 프레임 인덱스와 끝 프레임 인덱스를 선택

    _bool               m_bMonLastFrameCheck;              // 애니메이션 프레임을 새로 생성할 때 마지막과 같이 생성하는지를 체크
    _bool               m_bMonMovementFrameCheck;          // 동작 프레임을 화면에 출력하기 위한 용도
    //vector<MONSTERPARTS*> m_vecETCPar;                      // ETC 부모를 담고 있음

private: // 오브젝트
    TOTALITEMINFO* m_ItemTotal = nullptr;           // 아이템 전체에 해당하는 정보를 보관
    vector<PARTSITEMINFO*>       m_vecItemPartsSave;    // 아이템 파츠별 정보를 저장하는 벡터
    vector<PARTSITEMINFO*>       m_vecItemPartsLoad;    // 아이템 파츠별 정보를 불러오는 벡터  -> 계속 불러오고 보관하고 하기 위해 2개로 만듬

    string                       m_strItemPartsText;    // 아이템 파츠별 정보를 저장할 때 저장할 키 값
    _int                        m_iObjectCreatIndex;    // 데모를 생성할 때 콤보박스에서 선택하는 인덱스

    _bool                       m_bSelectTexture;       // 오브젝트 텍스쳐 모드

    _int                        m_iColorTextureIndex;   // 오브젝트 색깔 텍스쳐
private:
    virtual void    Free();
};

END

