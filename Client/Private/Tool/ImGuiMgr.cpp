#include "stdafx.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx9.h"

#include "..\Header\ImGuiMgr.h"

#include "Export_System.h"
#include "Export_Utility.h"

#include "commdlg.h"
#include "shlwapi.h"

#include "HumanDemo.h"
#include "MonsterDemo.h"
#include "ItemDemo.h"


IMPLEMENT_SINGLETON(CImGuiMgr)

CImGuiMgr::CImGuiMgr()
    :m_fSpeed(1.f), m_iFrameIndex(0), m_iMovementIndex(0), m_bAnimationCheck(false), m_AniTag(nullptr), m_bLastFrameCheck(false),
    m_iMovementFrameIndex(0), m_bMovementFrameCheck(false), m_iFrameNum(0), m_bSelectTexture(false), m_iColorTextureIndex(0),
    m_fMonSpeed(1.f), m_iMonFrameIndex(0), m_iMonMovementIndex(0), m_bMonAnimationCheck(false), m_MonAniTag(nullptr), m_bMonLastFrameCheck(false),
    m_iMonMovementFrameIndex(0), m_bMonMovementFrameCheck(false), m_iMonFrameNum(0)
{
    //ZeroMemory(m_iSetAddFrame, sizeof(_int[4]));
    //m_iSetAddFrame[0] = 1;
    ZeroMemory(m_iFrameRange, sizeof(_int[2]));
    ZeroMemory(m_iMovementRagne, sizeof(_int[2]));
    ZeroMemory(m_iMovementAddRange, sizeof(_int[2]));
    ZeroMemory(m_iFrameIndexSelect, sizeof(_int[2]));
    ZeroMemory(m_iRotRange, sizeof(_float[2]));

    ZeroMemory(m_iMonFrameRange, sizeof(_int[2]));
    ZeroMemory(m_iMonMovementRagne, sizeof(_int[2]));
    ZeroMemory(m_iMonMovementAddRange, sizeof(_int[2]));
    ZeroMemory(m_iMonFrameIndexSelect, sizeof(_int[2]));
    ZeroMemory(m_iMonRotRange, sizeof(_float[2]));
}
CImGuiMgr::~CImGuiMgr()
{
    CImGuiMgr::Free();
}

HRESULT CImGuiMgr::Ready_ImGuiMgr()
{

    for (int i = 0; i < 1; i++) {
        FRAME* pFrame = new FRAME[(_uint)PARTS::PARTS_END];
        //ZeroMemory(pFrame, sizeof((FRAME[(_uint)PARTS::PARTS_END]));
        ZeroMemory(pFrame, sizeof(FRAME[(_uint)PARTS::PARTS_END]));
        pFrame[(_uint)PARTS::HEAD].vPosition = { 0.f,1.6f,0.f };
        pFrame[(_uint)PARTS::BODY].vPosition = { 0.f,0.f,0.f };
        pFrame[(_uint)PARTS::LEFT_ARM].vPosition = { -1.2f,0.f,0.f };
        pFrame[(_uint)PARTS::RIGHT_ARM].vPosition = { 1.2f,0.f,0.f };
        pFrame[(_uint)PARTS::LEFT_LEG].vPosition = { -0.4f,-2.4f,0.f };
        pFrame[(_uint)PARTS::RIGHT_LEG].vPosition = { 0.4f,-2.4f,0.f };

        /*for (_uint i = 1; i < (_uint)PARTS::PARTS_END; i++) {
            pFrame[i].vPosition.y += 4.1f;
        }*/

        m_vecParts.push_back(pFrame);
    }

    for (int i = 0; i < 1; i++) {
        MONSTERFRAME* pFrame = new MONSTERFRAME[(_uint)MONSTERPARTS::MONSTERPARTS_END];
        //ZeroMemory(pFrame, sizeof((FRAME[(_uint)PARTS::PARTS_END]));
        ZeroMemory(pFrame, sizeof(MONSTERFRAME[(_uint)MONSTERPARTS::MONSTERPARTS_END]));
        pFrame[(_uint)MONSTERPARTS::HEAD].vPosition = { 0.f,1.6f,0.f };
        pFrame[(_uint)MONSTERPARTS::BODY].vPosition = { 0.f,0.f,0.f };
        pFrame[(_uint)MONSTERPARTS::LEFT_ARM].vPosition = { -1.2f,0.f,0.f };
        pFrame[(_uint)MONSTERPARTS::RIGHT_ARM].vPosition = { 1.2f,0.f,0.f };
        pFrame[(_uint)MONSTERPARTS::LEFT_LEG].vPosition = { -0.4f,-2.4f,0.f };
        pFrame[(_uint)MONSTERPARTS::RIGHT_LEG].vPosition = { 0.4f,-2.4f,0.f };
        pFrame[(_uint)MONSTERPARTS::ETC1].vPosition = { 0.f, 2.f,0.f };
        pFrame[(_uint)MONSTERPARTS::ETC2].vPosition = { 0.f, 2.f,0.f };
        pFrame[(_uint)MONSTERPARTS::ETC3].vPosition = { 0.f, 2.f,0.f };
        pFrame[(_uint)MONSTERPARTS::ETC4].vPosition = { 0.f, 2.f,0.f };
        pFrame[(_uint)MONSTERPARTS::ETC5].vPosition = { 0.f, 2.f,0.f };
        pFrame[(_uint)MONSTERPARTS::ETC6].vPosition = { 0.f, 2.f,0.f };

        for (_uint i = 1; i < (_uint)MONSTERPARTS::MONSTERPARTS_END; i++) {
            pFrame[i].vPosition.y += 2.1f;
        }

        pFrame[(_uint)MONSTERPARTS::TOTAL].vScale = { 0.5f,0.5f,0.5f };
        pFrame[(_uint)MONSTERPARTS::HEAD].vScale = { 0.8f,0.8f,0.8f };
        pFrame[(_uint)MONSTERPARTS::BODY].vScale = { 0.8f,1.2f,0.4f };
        pFrame[(_uint)MONSTERPARTS::LEFT_ARM].vScale = { 0.4f,1.2f,0.4f };
        pFrame[(_uint)MONSTERPARTS::RIGHT_ARM].vScale = { 0.4f,1.2f,0.4f };
        pFrame[(_uint)MONSTERPARTS::LEFT_LEG].vScale = { 0.4f,1.2f,0.4f };
        pFrame[(_uint)MONSTERPARTS::RIGHT_LEG].vScale = { 0.4f,1.2f,0.4f };
        pFrame[(_uint)MONSTERPARTS::ETC1].vScale = { 0.5f, 0.5f,0.5f };
        pFrame[(_uint)MONSTERPARTS::ETC2].vScale = { 0.5f, 0.5f,0.5f };
        pFrame[(_uint)MONSTERPARTS::ETC3].vScale = { 0.5f, 0.5f,0.5f };
        pFrame[(_uint)MONSTERPARTS::ETC4].vScale = { 0.5f, 0.5f,0.5f };
        pFrame[(_uint)MONSTERPARTS::ETC5].vScale = { 0.5f, 0.5f,0.5f };
        pFrame[(_uint)MONSTERPARTS::ETC6].vScale = { 0.5f, 0.5f,0.5f };

        m_vecMonParts.push_back(pFrame);
    }

    /*for (_uint i = 0; i < 6; i++) {
        MONSTERPARTS* pETC = new MONSTERPARTS;
        *pETC = MONSTERPARTS::TOTAL;
        m_vecETCPar.push_back(pETC);
    }*/

    for (_uint i = 0; i < 1; i++) {
        PARTSITEMINFO* pItemParts = new PARTSITEMINFO;
        ZeroMemory(pItemParts, sizeof(PARTSITEMINFO));
        m_vecItemPartsLoad.push_back(pItemParts);
    }

    m_ItemTotal = new TOTALITEMINFO;
    ZeroMemory(m_ItemTotal, sizeof(TOTALITEMINFO));
    m_ItemTotal->vScale = { 1.f, 1.f, 1.f };

    return S_OK;
}

void CImGuiMgr::Tool()
{
    ImGui::Begin("Tool", nullptr);

    ObjectTool();

    for (auto iter : m_mapObject) {
        if (iter.first == KEY_HUMAN) {
            AnimationTool();
        }
    }
    for (auto iter : m_mapObject) {
        if (iter.first == KEY_MONSTER) {
            MonAnimationTool();
        }
    }

    

    ImGui::End();
}

void CImGuiMgr::Parts_Setting()
{

    //ImGui::Begin(u8"예시", NULL, ImGuiWindowFlags_MenuBar);

    //ImGuiStyle& style = ImGui::GetStyle();
    ////↓맨아래 popItemWidth와 같이작동하며 ↓
    //ImGui::PushItemWidth(ImGui::GetFontSize() * -5);
    //if (ImGui::BeginMenuBar())
    //{
    //    if (ImGui::BeginMenu(u8"메뉴"))
    //    {
    //        ImGui::MenuItem(u8"예시");
    //        ImGui::EndMenu();
    //    }
    //    ImGui::EndMenuBar();
    //}
    //ImGui::Text(u8"O키ImGui켜기 P키 ImGui끄기");
    //ImGui::Spacing();// 간격 자동맞춤(아마?)

    //if (ImGui::CollapsingHeader(u8"토글예시"))
    //{
    //    ImGui::SeparatorText(u8"경계선 예시:");

    //    ImGui::BulletText(u8"글머리표 예시");

    //    if (ImGui::TreeNode(u8"미니 토글 예시"))
    //    {
    //        ImGui::SeparatorText(u8"경계선 예시:");

    //        //↓마지막 매개변수는 이벤트 넣으면 됩니다↓
    //        //ImGui::CheckboxFlags(u8"체크박스 예시", &io->ConfigFlags, ImGuiConfigFlags_NavEnableGamepad);
    //        //↓같은라인에 글 이나 옵션 추가할때 SameLine넣어주시면 됩니다
    //        ImGui::SameLine(); ImGui::Text(u8" / 같은줄에 글쓰기 예시");

    //        //↓체크박스같은거 선택 못하게 막기 Begin과end둘다필요하며 사이에 넣으면됨↓
    //        ImGui::BeginDisabled();

    //        //ImGui::CheckboxFlags(u8"변경 못하는 체크박스 예시", &io->ConfigFlags, ImGuiConfigFlags_DockingEnable);

    //        ImGui::EndDisabled();//체크박스같은거 선택 못하게 막기

    //        ImGui::Button(u8"클릭버튼 예시");

    //        char str0[255] = "Hi";
    //        ImGui::InputText(u8"입력받기 예시", str0, sizeof(str0));

    //        static int i0 = 123;
    //        ImGui::InputInt(u8"int 값", &i0);

    //        static float f0 = 0.001f;
    //        ImGui::InputFloat(u8"float 값", &f0, 0.01f, 1.0f, "%.3f");

    //        static float vec4a[4] = { 0.10f, 0.20f, 0.30f };
    //        ImGui::InputFloat3(u8"칸3개 예시", vec4a);

    //        static int i1 = 0;
    //        //1번째 옆에 이름(설명?)2번째 기본값 3번째 최소값 4번째 최대값
    //        ImGui::SliderInt(u8"슬라이드 예시", &i1, -1, 3);

    //        //콤보박스 추가
    //        const char* items[] = { u8"가가가", u8"나나나", u8"다다다", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIIIIII", "JJJJ", "KKKKKKK" };
    //        static int item_current = 0;
    //        ImGui::Combo(u8"콤보박스 예시", &item_current, items, IM_ARRAYSIZE(items));

    //        //리스트 박스 추가
    //        const char* items2[] = { "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon" };
    //        static int item_current2 = 1;
    //        ImGui::ListBox("listbox", &item_current2, items2, IM_ARRAYSIZE(items2), 4);
    //        if (ImGui::BeginTabBar(u8"탭 예시", ImGuiTabBarFlags_None))//end를 넣어줘야한다
    //        {
    //            if (ImGui::BeginTabItem(u8"탭? 예시"))//마지막에 end가 필요하다
    //            {
    //                ImGui::SeparatorText(u8"경계선 예시");
    //                ImGui::SliderFloat2("WindowPadding", (float*)&style.WindowPadding, 0.0f, 20.0f, "%.0f");
    //                ImGui::EndTabItem();

    //                //선택?예시
    //                static int e = 0;
    //                ImGui::RadioButton("radio a", &e, 0); ImGui::SameLine();
    //                ImGui::RadioButton("radio b", &e, 1); ImGui::SameLine();
    //                ImGui::RadioButton("radio c", &e, 2);

    //                ImGui::Text(u8"숫자 클릭예시");
    //                static int counter = 0;
    //                float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
    //                ImGui::PushButtonRepeat(true);
    //                if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { counter--; }
    //                ImGui::SameLine(0.0f, spacing);
    //                if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { counter++; }
    //                ImGui::PopButtonRepeat();
    //                ImGui::SameLine();
    //                ImGui::Text("%d", counter);
    //            }
    //            ImGui::EndTabBar();
    //        }
    //        ImGui::PopItemWidth();
    //        ImGui::TreePop();//미니토글 마지막에 필수로 추가
    //    }
    //}


    ImGui::End();

}

void CImGuiMgr::AnimationTool()
{
    if (ImGui::TreeNode(u8"AnimationTool"))
    {

        if (ImGui::BeginTabBar(u8"Frame", ImGuiTabBarFlags_None)) {

            if (ImGui::BeginTabItem(u8"Frame")) {
                
                Frame();

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem(u8"Distribute")) {

                Distribute();

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem(u8"FixFrame")) {

                FixFrame();

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem(u8"Movement")) {

                Movement();

                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::TreePop();//미니토글 마지막에 필수로 추가
    }
}

void CImGuiMgr::Frame()
{
    ImGui::BeginListBox(u8"Frame");
    for (_ulong i = 0; i < m_vecParts.size(); i++) {
        string str1 = to_string(i);
        if (ImGui::Selectable(str1.c_str(), i == m_iFrameIndex)) {
            m_iFrameIndex = i;
        }
    }

    ImGui::EndListBox();


    const char* Parts[] = { u8"Total" ,u8"Head",u8"Body",u8"LeftArm",u8"RightArm",u8"LeftLeg",u8"RightLeg" };
    static int PartsIndex = 0;
    ImGui::Combo(u8"Parts", &PartsIndex, Parts, IM_ARRAYSIZE(Parts));

    ImGui::InputFloat(u8"PosX", &m_vecParts[m_iFrameIndex][PartsIndex].vPosition.x, 0.1f, 100.f, "%.1f");
    ImGui::InputFloat(u8"PosY", &m_vecParts[m_iFrameIndex][PartsIndex].vPosition.y, 0.1f, 100.f, "%.1f");
    ImGui::InputFloat(u8"PosZ", &m_vecParts[m_iFrameIndex][PartsIndex].vPosition.z, 0.1f, 100.f, "%.1f");
    //ImGui::InputFloat3("Pos", m_vecParts[m_iFrameIndex][PartsIndex].vPosition);

    ImGui::InputFloat(u8"RotX", &m_vecParts[m_iFrameIndex][PartsIndex].vRotation.x, 5.f, 100.f, "%.1f");
    ImGui::InputFloat(u8"RotY", &m_vecParts[m_iFrameIndex][PartsIndex].vRotation.y, 5.f, 100.f, "%.1f");
    ImGui::InputFloat(u8"RotZ", &m_vecParts[m_iFrameIndex][PartsIndex].vRotation.z, 5.f, 100.f, "%.1f");
    //ImGui::InputFloat3("Rot", m_vecParts[m_iFrameIndex][PartsIndex].vRotation);

    char buf[255]{};
    strncpy_s(buf, m_strText.c_str(), sizeof(buf) - 1);
    ImGui::InputText("Text", buf, sizeof(buf));
    m_strText = buf;

    ImGui::InputFloat(u8"Speed", &m_fSpeed, 1.f, 10.f, "%.1f");

    if (ImGui::Button(u8"Reset")) {
        if (PartsIndex == 0) {
            m_vecParts[m_iFrameIndex][PartsIndex].vPosition = { 0.f,0.f,0.f };
        }
        else if (PartsIndex == 1) {
            m_vecParts[m_iFrameIndex][PartsIndex].vPosition = { 0.f,1.6f,0.f };
        }
        else if (PartsIndex == 2) {
            m_vecParts[m_iFrameIndex][PartsIndex].vPosition = { 0.f,0.f,0.f };
        }
        else if (PartsIndex == 3) {
            m_vecParts[m_iFrameIndex][PartsIndex].vPosition = { -1.2f,0.f,0.f };
        }
        else if (PartsIndex == 4) {
            m_vecParts[m_iFrameIndex][PartsIndex].vPosition = { 1.2f,0.f,0.f };
        }
        else if (PartsIndex == 5) {
            m_vecParts[m_iFrameIndex][PartsIndex].vPosition = { -0.4f,-2.4f,0.f };
        }
        else if (PartsIndex == 6) {
            m_vecParts[m_iFrameIndex][PartsIndex].vPosition = { 0.4f, -2.4f,0.f };
        }
        m_vecParts[m_iFrameIndex][PartsIndex].vRotation = { 0.f,0.f,0.f };
    }

    ImGui::Checkbox("LastFrame", &m_bLastFrameCheck);

    if (ImGui::Button(u8"AddFrame"))
    {
        AddFrame();

    }

    if (ImGui::Button(u8"DeleteFrame"))
    {
        if (m_iFrameIndex != 0) {
            if (m_iFrameIndex == m_vecParts.size() - 1) {
                m_iFrameIndex -= 1;
            }
            Safe_Delete(m_vecParts.back());
            m_vecParts.pop_back();
        }
    }

    if (ImGui::Button(u8"AllDelete"))
    {
        for_each(m_vecParts.begin(), m_vecParts.end(), CDeleteObj2());
        m_vecParts.clear();

        m_iFrameIndex = 0;

        AddFrame();
    }

    if (ImGui::Button(u8"Start")) {
        m_bAnimationCheck = true;
    }
    if (ImGui::Button(u8"Stop")) {
        m_bAnimationCheck = false;
    }
    if (ImGui::Button(u8"Save")) {
        SaveAnimationData();
    }
    if (ImGui::Button(u8"Load")) {
        LoadAnimationData();
    }
}

void CImGuiMgr::Distribute()
{
    
    ImGui::InputInt("FrameNum", &m_iFrameNum);
    ImGui::InputInt2("Start/End FrameIndex", m_iFrameIndexSelect);

    if (ImGui::Button(u8"Create")) {

        if (0 <= m_iFrameIndexSelect[0] && m_iFrameIndexSelect[1] < m_vecParts.size()) {

            vector<FRAME*> vecTemp;
            FRAME* pTemp = nullptr;
            for (_int i = 0; i < 2; i++) {
                pTemp = new FRAME[(_uint)PARTS::PARTS_END];
                for (_uint j = 0; j < (_uint)PARTS::PARTS_END; ++j) {
                    pTemp[j] = m_vecParts[m_iFrameIndexSelect[i]][j];
                }
                vecTemp.push_back(pTemp);
            }

            for_each(m_vecParts.begin(), m_vecParts.end(), CDeleteObj2());
            m_vecParts.clear();


            _vec3 vRot[7], vPos[7], vStartRot[7], vStartPos[7], fDistRot[7], fDistPos[7];
            for (_uint j = 0; j < (_uint)PARTS::PARTS_END; ++j) {
                vRot[j] = (-1.f * (vecTemp[0][j].vRotation) + (vecTemp[1][j].vRotation)); // 각도
                vPos[j] = (-1.f * (vecTemp[0][j].vPosition) + (vecTemp[1][j].vPosition)); // 위치
                vStartRot[j] = vecTemp[0][j].vRotation;
                vStartPos[j] = vecTemp[0][j].vPosition;
                fDistRot[j] = vRot[j] / (m_iFrameNum - 1);
                fDistPos[j] = vPos[j] / (m_iFrameNum - 1);
            }

            for (_int i = 0; i < m_iFrameNum; i++) {

                pTemp = new FRAME[(_uint)PARTS::PARTS_END];
                for (_uint j = 0; j < (_uint)PARTS::PARTS_END; ++j) {
                    pTemp[j].vRotation = vStartRot[j];
                    pTemp[j].vPosition = vStartPos[j];
                }
                for (_uint j = 0; j < (_uint)PARTS::PARTS_END; ++j) {
                    vStartRot[j] += fDistRot[j];
                    vStartPos[j] += fDistPos[j];
                }

                m_vecParts.push_back(pTemp);

            }

            for_each(vecTemp.begin(), vecTemp.end(), CDeleteObj2());
            vecTemp.clear();
        }

    }
    
}

void CImGuiMgr::FixFrame()
{
    ImGui::InputInt2("FrameRange", m_iFrameRange);

    const char* Parts2[] = { u8"Total" ,u8"Head",u8"Body",u8"LeftArm",u8"RightArm",u8"LeftLeg",u8"RightLeg" };
    static int PartsIndex2 = 0;
    ImGui::Combo(u8"Fix_Parts", &PartsIndex2, Parts2, IM_ARRAYSIZE(Parts2));

    const char* cMat[] = { "Pos" , "Rot" };
    static int cMatIndex = 0;
    ImGui::Combo(u8"Select_Mat", &cMatIndex, cMat, IM_ARRAYSIZE(cMat));

    const char* cCoord[] = { "X" , "Y" , "Z" };
    static int cCoordIndex = 0;
    ImGui::Combo(u8"Select_Coord", &cCoordIndex, cCoord, IM_ARRAYSIZE(cCoord));


    ImGui::InputFloat2("Start/Last", m_iRotRange);

    if (ImGui::Button(u8"FixFrame"))
    {
        _float fRot = (-1.f * (m_iRotRange[0]) + (m_iRotRange[1]));
        _float fRot2 = (_float)m_iRotRange[0];
        _float fRot3 = fRot / (m_iFrameRange[1] + 1);
        if (0 <= m_iFrameRange[0] && m_iFrameRange[1] <= m_vecParts.size()) {
            if (cMatIndex == 0) {
                for (_uint i = m_iFrameRange[0]; i <= m_iFrameRange[1]; i++) {
                    if (cCoordIndex == 0) {
                        m_vecParts[i][PartsIndex2].vPosition.x = fRot2;
                    }
                    else if (cCoordIndex == 1) {
                        m_vecParts[i][PartsIndex2].vPosition.y = fRot2;
                    }
                    else if (cCoordIndex == 2) {
                        m_vecParts[i][PartsIndex2].vPosition.z = fRot2;
                    }
                    fRot2 += fRot3;
                }
            }
            else if (cMatIndex == 1) {
                for (_uint i = m_iFrameRange[0]; i <= m_iFrameRange[1]; i++) {
                    if (cCoordIndex == 0) {
                        m_vecParts[i][PartsIndex2].vRotation.x = fRot2;
                    }
                    else if (cCoordIndex == 1) {
                        m_vecParts[i][PartsIndex2].vRotation.y = fRot2;
                    }
                    else if (cCoordIndex == 2) {
                        m_vecParts[i][PartsIndex2].vRotation.z = fRot2;
                    }
                    fRot2 += fRot3;
                }
            }
        }
        else {
            MSG_BOX("범위를 잘못 설정하였습니다.");
        }

    }

    if (ImGui::Button(u8"Reverse")) {
        vector<FRAME*> vecTemp;
        FRAME* pTemp = nullptr;
        for (_int i = (m_vecParts.size() - 1); i >= 0; --i) {
            pTemp = new FRAME[(_uint)PARTS::PARTS_END];
            for (_uint j = 0; j < (_uint)PARTS::PARTS_END; ++j) {
                pTemp[j] = m_vecParts[i][j];
            }
            vecTemp.push_back(pTemp);
        }
        for (_uint i = 0; i < vecTemp.size(); i++) {
            m_vecParts.push_back(vecTemp[i]);
        }
    }
}

void CImGuiMgr::Movement()
{
    ImGui::BeginListBox(u8"Movement");
    for (_ulong i = 0; i < m_vecMovement.size(); i++) {
        string str1 = to_string(i);
        if (ImGui::Selectable(str1.c_str(), i == m_iMovementIndex)) {
            m_iMovementIndex = i;
        }
    }
    ImGui::EndListBox();

    if (m_vecMovement.size() != 0) {
        if (m_vecMovement[m_iMovementIndex].size() <= m_iMovementFrameIndex) {
            m_iMovementFrameIndex = 0;
        }
    }

    if (m_vecMovement.size() != 0) {
        ImGui::BeginListBox(u8"MovementFrame");
        for (_ulong j = 0; j < m_vecMovement[m_iMovementIndex].size(); j++) {
            string str2 = to_string(j);
            if (ImGui::Selectable(str2.c_str(), j == m_iMovementFrameIndex)) {
                
                m_iMovementFrameIndex = j;
            }
        }
        ImGui::EndListBox();
    }

    ImGui::InputInt2("MovementRange", m_iMovementRagne);

    if (ImGui::Button(u8"Create")) {
        if (0 <= m_iMovementRagne[0] && m_iMovementRagne[1] < m_vecParts.size()) {
           
            if (m_iMovementRagne[1] == (m_vecParts.size() - 1)) {
                AddFrame();
                
            }
            vector<FRAME*> vecTemp;
            FRAME* pFram = nullptr;
            for (_uint i = m_iMovementRagne[0]; i <= m_iMovementRagne[1]; i++) {
                pFram = new FRAME[(_uint)PARTS::PARTS_END];
                for (_uint j = 0; j < (_uint)PARTS::PARTS_END; ++j) {
                    pFram[j] = m_vecParts[i][j];
                }
                vecTemp.push_back(pFram);
            }
            m_vecMovement.push_back(vecTemp);


            for (_int i = m_iMovementRagne[0]; i <= m_iMovementRagne[1]; i++) {

                Safe_Delete(m_vecParts[0]);
                m_vecParts.erase(m_vecParts.begin());
                m_iFrameIndex = 0;
            }
        }
        else {
            //MSG_BOX("범위를 벗어남");
        }
    }

    if (ImGui::Button(u8"DeleteMovement"))
    {
        if (m_iMovementIndex >= 0 && m_vecMovement.size() != 0) {

            m_bMovementFrameCheck = false;

            if (m_iMovementIndex == m_vecMovement.size() - 1 && m_iMovementIndex != 0) {
                m_iMovementIndex -= 1;
            }
            for_each(m_vecMovement[m_iMovementIndex].begin(), m_vecMovement[m_iMovementIndex].end(), CDeleteObj2());
            m_vecMovement[m_iMovementIndex].clear();
            m_vecMovement.erase(m_vecMovement.begin() + m_iMovementIndex);
        }
    }

    if (ImGui::Button(u8"DeleteMovementFrame"))
    {
        if (m_iMovementFrameIndex != 0) {
            if (m_iMovementFrameIndex == m_vecMovement[m_iMovementIndex].size() - 1) {
                m_iMovementFrameIndex -= 1;
            }
            Safe_Delete(m_vecMovement[m_iMovementIndex].back());
            m_vecMovement[m_iMovementIndex].pop_back();
        }
    }

    if (m_vecMovement.size() != 0) {
        ImGui::Checkbox("MovementFrame", &m_bMovementFrameCheck);
    }

    ImGui::InputInt2("MovementAddRange", m_iMovementAddRange);

    if (ImGui::Button(u8"AddMovement"))
    {
        if (0 <= m_iMovementAddRange[0] && m_iMovementAddRange[1] < m_vecMovement.size()) {

            for_each(m_vecParts.begin(), m_vecParts.end(), CDeleteObj2());
            m_vecParts.clear();

            FRAME* pFram = nullptr;
            for (_int i = m_iMovementAddRange[0]; i <= m_iMovementAddRange[1]; i++) {
                for (_int j = 0; j < m_vecMovement[i].size(); j++) {
                    pFram = new FRAME[(_uint)PARTS::PARTS_END];
                    for (_uint k = 0; k < (_uint)PARTS::PARTS_END; ++k) {
                        pFram[k] = m_vecMovement[i][j][k];
                    }
                    m_vecParts.push_back(pFram);
                }
            }
        }
    }

    if (ImGui::Button(u8"Start")) {
        m_bAnimationCheck = true;
    }
    if (ImGui::Button(u8"Stop")) {
        m_bAnimationCheck = false;
    }
}

void CImGuiMgr::AddFrame()
{
    if (m_bLastFrameCheck == false) {
        FRAME* pFrame = new FRAME[(_uint)PARTS::PARTS_END];
        ZeroMemory(pFrame, sizeof(FRAME[(_uint)PARTS::PARTS_END]));
        pFrame[(_uint)PARTS::HEAD].vPosition = { 0.f,1.6f,0.f };
        pFrame[(_uint)PARTS::BODY].vPosition = { 0.f,0.f,0.f };
        pFrame[(_uint)PARTS::LEFT_ARM].vPosition = { -1.2f,0.f,0.f };
        pFrame[(_uint)PARTS::RIGHT_ARM].vPosition = { 1.2f,0.f,0.f };
        pFrame[(_uint)PARTS::LEFT_LEG].vPosition = { -0.4f,-2.4f,0.f };
        pFrame[(_uint)PARTS::RIGHT_LEG].vPosition = { 0.4f, -2.4f,0.f };

        m_vecParts.push_back(pFrame);
    }
    else {
        FRAME* pFrame = new FRAME[(_uint)PARTS::PARTS_END];
        ZeroMemory(pFrame, sizeof(FRAME[(_uint)PARTS::PARTS_END]));
        pFrame[(_uint)PARTS::TOTAL].vPosition = m_vecParts.back()[TOTAL].vPosition;
        pFrame[(_uint)PARTS::HEAD].vPosition = m_vecParts.back()[HEAD].vPosition;
        pFrame[(_uint)PARTS::BODY].vPosition = m_vecParts.back()[BODY].vPosition;
        pFrame[(_uint)PARTS::LEFT_ARM].vPosition = m_vecParts.back()[LEFT_ARM].vPosition;
        pFrame[(_uint)PARTS::RIGHT_ARM].vPosition = m_vecParts.back()[RIGHT_ARM].vPosition;
        pFrame[(_uint)PARTS::LEFT_LEG].vPosition = m_vecParts.back()[LEFT_LEG].vPosition;
        pFrame[(_uint)PARTS::RIGHT_LEG].vPosition = m_vecParts.back()[RIGHT_LEG].vPosition;

        pFrame[(_uint)PARTS::TOTAL].vRotation = m_vecParts.back()[TOTAL].vRotation;
        pFrame[(_uint)PARTS::HEAD].vRotation = m_vecParts.back()[HEAD].vRotation;
        pFrame[(_uint)PARTS::BODY].vRotation = m_vecParts.back()[BODY].vRotation;
        pFrame[(_uint)PARTS::LEFT_ARM].vRotation = m_vecParts.back()[LEFT_ARM].vRotation;
        pFrame[(_uint)PARTS::RIGHT_ARM].vRotation = m_vecParts.back()[RIGHT_ARM].vRotation;
        pFrame[(_uint)PARTS::LEFT_LEG].vRotation = m_vecParts.back()[LEFT_LEG].vRotation;
        pFrame[(_uint)PARTS::RIGHT_LEG].vRotation = m_vecParts.back()[RIGHT_LEG].vRotation;

        m_vecParts.push_back(pFrame);
    }
}

void CImGuiMgr::SaveAnimationData()
{
    //GetOpenFileName()
    OPENFILENAME    open;
    TCHAR   lpstrFile[MAX_PATH] = L"";
    static TCHAR filter[] = L"*.dat";

    ZeroMemory(&open, sizeof(OPENFILENAME));
    open.lStructSize = sizeof(OPENFILENAME);
    open.lpstrFilter = filter;
    open.lpstrFile = lpstrFile;
    open.nMaxFile = 100;
    open.lpstrInitialDir = L"";

    GetModuleFileName(NULL, lpstrFile, MAX_PATH);
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin\Client.exe
    PathRemoveFileSpec(lpstrFile);
    PathRemoveFileSpec(lpstrFile);
    PathRemoveFileSpec(lpstrFile);
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin
    lstrcat(lpstrFile, L"\\Data\\Animation");
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin\Data\Animation
    basic_string<TCHAR> converted(m_strText.begin(), m_strText.end());
    const _tchar* aa = converted.c_str();

    wcscat_s(lpstrFile, L"\\");
    wcscat_s(lpstrFile, L"ANIMATION_");
    wcscat_s(lpstrFile, aa);
    wcscat_s(lpstrFile, L".dat");

    if (GetSaveFileName(&open) != 0) {

        HANDLE hFile = CreateFile(lpstrFile, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

        if (INVALID_HANDLE_VALUE == hFile)
            return;

        DWORD	dwByte = 0;
        DWORD	dwStrByte = 0;

        dwStrByte = sizeof(CHAR) * (m_strText.length() + 1);

        WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
        WriteFile(hFile, m_strText.c_str(), dwStrByte, &dwByte, nullptr);
        WriteFile(hFile, &m_fSpeed, sizeof(_float), &dwByte, nullptr);

        for (auto& iter : m_vecParts) {
            WriteFile(hFile, iter, sizeof(FRAME[(_uint)PARTS::PARTS_END]), &dwByte, nullptr);
        }

        CloseHandle(hFile);
    }

}

void CImGuiMgr::LoadAnimationData()
{
    OPENFILENAME    open;
    TCHAR   lpstrFile[MAX_PATH] = L"";
    static TCHAR filter[] = L"*.*";

    ZeroMemory(&open, sizeof(OPENFILENAME));
    open.lStructSize = sizeof(OPENFILENAME);
    open.lpstrFilter = filter;
    open.lpstrFile = lpstrFile;
    open.nMaxFile = 100;
    open.lpstrInitialDir = L"";

    GetModuleFileName(NULL, lpstrFile, MAX_PATH);
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin\Client.exe
    PathRemoveFileSpec(lpstrFile);
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin
    PathRemoveFileSpec(lpstrFile);
    PathRemoveFileSpec(lpstrFile);
    lstrcat(lpstrFile, L"\\Data\\Animation\\data");
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin\Data\Animation

    if (GetOpenFileName(&open) != 0) {

        for_each(m_vecParts.begin(), m_vecParts.end(), CDeleteObj2());
        m_vecParts.clear();

        HANDLE hFile = CreateFile(lpstrFile, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
        //C:\Users\조우택\Desktop\SR_TeamMinever2\Data\Animation\HUMAN_TEST.dat
        if (INVALID_HANDLE_VALUE == hFile)
            return;

        DWORD	dwByte = 0;
        DWORD	dwStrByte = 0;
        FRAME* pFrame = nullptr;

        ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

        CHAR* pTag = new CHAR[dwStrByte];

        ReadFile(hFile, pTag, dwStrByte, &dwByte, nullptr);

        m_strText = pTag;

        Safe_Delete_Array(pTag);

        basic_string<TCHAR> converted(m_strText.begin(), m_strText.end());
        m_AniTag = converted.c_str();

        ReadFile(hFile, &m_fSpeed, sizeof(_float), &dwByte, nullptr);

        while (true)
        {
            pFrame = new FRAME[(_uint)PARTS::PARTS_END];

            ReadFile(hFile, pFrame, sizeof(FRAME[(_uint)PARTS::PARTS_END]), &dwByte, nullptr);

            if (0 == dwByte)
            {
                Safe_Delete(pFrame);
                break;
            }

            m_vecParts.push_back(pFrame);
        }

        CloseHandle(hFile);
    }


}

void CImGuiMgr::MonAnimationTool()
{
    if (ImGui::TreeNode(u8"MonAnimationTool"))
    {

        if (ImGui::BeginTabBar(u8"MonFrame", ImGuiTabBarFlags_None)) {

            if (ImGui::BeginTabItem(u8"MonFrame")) {

                MonFrame();

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem(u8"MonDistribute")) {

                MonDistribute();

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem(u8"MonFixFrame")) {

                MonFixFrame();

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem(u8"MonMovement")) {

                MonMovement();

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem(u8"MonETC")) {

                MonETC_Select_Par();

                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::TreePop();//미니토글 마지막에 필수로 추가
    }
}

void CImGuiMgr::MonFrame()
{
    ImGui::BeginListBox(u8"MonFrame");
    for (_ulong i = 0; i < m_vecMonParts.size(); i++) {
        string str1 = to_string(i);
        if (ImGui::Selectable(str1.c_str(), i == m_iMonFrameIndex)) {
            m_iMonFrameIndex = i;
        }
    }

    ImGui::EndListBox();


    const char* Parts[] = { u8"Total" ,u8"Head",u8"Body",u8"LeftArm",u8"RightArm",u8"LeftLeg",u8"RightLeg",
    u8"ETC1" ,u8"ETC2" ,u8"ETC3" ,u8"ETC4" ,u8"ETC5" ,u8"ETC6" };
    static int PartsIndex = 0;
    ImGui::Combo(u8"MonParts", &PartsIndex, Parts, IM_ARRAYSIZE(Parts));

    ImGui::InputFloat(u8"MonScaleX", &m_vecMonParts[m_iMonFrameIndex][PartsIndex].vScale.x, 0.1f, 100.f, "%.1f");
    ImGui::InputFloat(u8"MonScaleY", &m_vecMonParts[m_iMonFrameIndex][PartsIndex].vScale.y, 0.1f, 100.f, "%.1f");
    ImGui::InputFloat(u8"MonScaleZ", &m_vecMonParts[m_iMonFrameIndex][PartsIndex].vScale.z, 0.1f, 100.f, "%.1f");
    //ImGui::InputFloat3("Pos", m_vecParts[m_iFrameIndex][PartsIndex].vPosition);

    ImGui::InputFloat(u8"MonPosX", &m_vecMonParts[m_iMonFrameIndex][PartsIndex].vPosition.x, 0.1f, 100.f, "%.1f");
    ImGui::InputFloat(u8"MonPosY", &m_vecMonParts[m_iMonFrameIndex][PartsIndex].vPosition.y, 0.1f, 100.f, "%.1f");
    ImGui::InputFloat(u8"MonPosZ", &m_vecMonParts[m_iMonFrameIndex][PartsIndex].vPosition.z, 0.1f, 100.f, "%.1f");
    //ImGui::InputFloat3("Pos", m_vecParts[m_iFrameIndex][PartsIndex].vPosition);

    ImGui::InputFloat(u8"MonRotX", &m_vecMonParts[m_iMonFrameIndex][PartsIndex].vRotation.x, 5.f, 100.f, "%.1f");
    ImGui::InputFloat(u8"MonRotY", &m_vecMonParts[m_iMonFrameIndex][PartsIndex].vRotation.y, 5.f, 100.f, "%.1f");
    ImGui::InputFloat(u8"MonRotZ", &m_vecMonParts[m_iMonFrameIndex][PartsIndex].vRotation.z, 5.f, 100.f, "%.1f");
    //ImGui::InputFloat3("Rot", m_vecParts[m_iFrameIndex][PartsIndex].vRotation);

    char buf[255]{};
    strncpy_s(buf, m_strMonText.c_str(), sizeof(buf) - 1);
    ImGui::InputText("MonText", buf, sizeof(buf));
    m_strMonText = buf;

    ImGui::InputFloat(u8"MonSpeed", &m_fMonSpeed, 1.f, 10.f, "%.1f");

    if (ImGui::Button(u8"MonReset")) {
        if (PartsIndex == 0) { //total
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vPosition = { 0.f,0.f,0.f };
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vScale = { 0.5f,0.5f,0.5f };
        }
        else if (PartsIndex == 1) { //head
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vPosition = { 0.f,1.6f,0.f };
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vScale = { 0.8f,0.8f,0.8f };
        }
        else if (PartsIndex == 2) { //body
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vPosition = { 0.f,0.f,0.f };
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vScale = { 0.8f,1.2f,0.4f };
        }
        else if (PartsIndex == 3) { //leftarm
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vPosition = { -1.2f,0.f,0.f };
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vScale = { 0.4f,1.2f,0.4f };
        }
        else if (PartsIndex == 4) { //rightarm
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vPosition = { 1.2f,0.f,0.f };
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vScale = { 0.4f,1.2f,0.4f };
        }
        else if (PartsIndex == 5) { //leftleg
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vPosition = { -0.4f,-2.4f,0.f };
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vScale = { 0.4f,1.2f,0.4f };
        }
        else if (PartsIndex == 6) { //rightleg
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vPosition = { 0.4f, -2.4f,0.f };
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vScale = { 0.4f,1.2f,0.4f };
        }
        else if (PartsIndex == 7) { //etc1
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vPosition = { 0.f, 2.f,0.f };
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vScale = { 0.5f,0.5f,0.5f };
        }
        else if (PartsIndex == 8) { //etc2
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vPosition = { 0.f, 2.f,0.f };
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vScale = { 0.5f,0.5f,0.5f };
        }
        else if (PartsIndex == 9) { //etc3
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vPosition = { 0.f, 2.f,0.f };
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vScale = { 0.5f,0.5f,0.5f };
        }
        else if (PartsIndex == 10) { //etc4
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vPosition = { 0.f, 2.f,0.f };
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vScale = { 0.5f,0.5f,0.5f };
        }
        else if (PartsIndex == 11) { //etc5
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vPosition = { 0.f, 2.f,0.f };
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vScale = { 0.5f,0.5f,0.5f };
        }
        else if (PartsIndex == 12) { //etc6
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vPosition = { 0.f, 2.f,0.f };
            m_vecMonParts[m_iMonFrameIndex][PartsIndex].vScale = { 0.5f,0.5f,0.5f };
        }
        m_vecMonParts[m_iMonFrameIndex][PartsIndex].vRotation = { 0.f,0.f,0.f };
    }

    ImGui::Checkbox("MonLastFrame", &m_bMonLastFrameCheck);

    if (ImGui::Button(u8"MonAddFrame"))
    {
        MonAddFrame();

    }

    if (ImGui::Button(u8"MonDeleteFrame"))
    {
        if (m_iMonFrameIndex != 0) {
            if (m_iMonFrameIndex == m_vecMonParts.size() - 1) {
                m_iMonFrameIndex -= 1;
            }
            Safe_Delete(m_vecMonParts.back());
            m_vecMonParts.pop_back();
        }
    }

    if (ImGui::Button(u8"MonAllDelete"))
    {
        for_each(m_vecMonParts.begin(), m_vecMonParts.end(), CDeleteObj2());
        m_vecMonParts.clear();

        m_iMonFrameIndex = 0;

        MonAddFrame();
    }

    if (ImGui::Button(u8"MonStart")) {
        m_bMonAnimationCheck = true;
    }
    if (ImGui::Button(u8"MonStop")) {
        m_bMonAnimationCheck = false;
    }
    if (ImGui::Button(u8"MonSave")) {
        SaveMonAnimationData();
    }
    if (ImGui::Button(u8"MonLoad")) {
        LoadMonAnimationData();
    }
}

void CImGuiMgr::MonDistribute()
{
    ImGui::InputInt("MonFrameNum", &m_iMonFrameNum);
    ImGui::InputInt2("Start/End MonFrameIndex", m_iMonFrameIndexSelect);

    if (ImGui::Button(u8"MonCreate")) {

        if (0 <= m_iMonFrameIndexSelect[0] && m_iMonFrameIndexSelect[1] < m_vecMonParts.size()) {

            vector<MONSTERFRAME*> vecTemp;
            MONSTERFRAME* pTemp = nullptr;
            for (_int i = 0; i < 2; i++) {
                pTemp = new MONSTERFRAME[(_uint)MONSTERPARTS::MONSTERPARTS_END];
                for (_uint j = 0; j < (_uint)MONSTERPARTS::MONSTERPARTS_END; ++j) {
                    pTemp[j] = m_vecMonParts[m_iMonFrameIndexSelect[i]][j];
                }
                vecTemp.push_back(pTemp);
            }

            for_each(m_vecMonParts.begin(), m_vecMonParts.end(), CDeleteObj2());
            m_vecMonParts.clear();

            _vec3 vRot[13], vPos[13],vScale[13], vStartRot[13], vStartPos[13], vStartScale[13], fDistRot[13], fDistPos[13],fDistScale[13];
            for (_uint j = 0; j < (_uint)MONSTERPARTS::MONSTERPARTS_END; ++j) {
                vRot[j] = (-1.f * (vecTemp[0][j].vRotation) + (vecTemp[1][j].vRotation)); // 각도
                vPos[j] = (-1.f * (vecTemp[0][j].vPosition) + (vecTemp[1][j].vPosition)); // 위치
                vScale[j] = (-1.f * (vecTemp[0][j].vScale) + (vecTemp[1][j].vScale)); // 스케일
                vStartRot[j] = vecTemp[0][j].vRotation;
                vStartPos[j] = vecTemp[0][j].vPosition;
                vStartScale[j] = vecTemp[0][j].vScale;
                fDistRot[j] = vRot[j] / (m_iMonFrameNum - 1);
                fDistPos[j] = vPos[j] / (m_iMonFrameNum - 1);
                fDistScale[j]= vScale[j]/ (m_iMonFrameNum - 1);
            }

            for (_int i = 0; i < m_iMonFrameNum; i++) {

                pTemp = new MONSTERFRAME[(_uint)MONSTERPARTS::MONSTERPARTS_END];
                for (_uint j = 0; j < (_uint)MONSTERPARTS::MONSTERPARTS_END; ++j) {
                    pTemp[j].vRotation = vStartRot[j];
                    pTemp[j].vPosition = vStartPos[j];
                    pTemp[j].vScale = vStartScale[j];
                    pTemp[j].eETC_Par = vecTemp[0][j].eETC_Par;
                }
                for (_uint j = 0; j < (_uint)MONSTERPARTS::MONSTERPARTS_END; ++j) {
                    vStartRot[j] += fDistRot[j];
                    vStartPos[j] += fDistPos[j];
                    vStartScale[j] += fDistScale[j];
                }

                m_vecMonParts.push_back(pTemp);
              
            }
            
            for_each(vecTemp.begin(), vecTemp.end(), CDeleteObj2());
            vecTemp.clear();
           
        }
       
    }

    
}

void CImGuiMgr::MonFixFrame()
{
    ImGui::InputInt2("MonFrameRange", m_iMonFrameRange);

    const char* Parts2[] = { u8"Total" ,u8"Head",u8"Body",u8"LeftArm",u8"RightArm",u8"LeftLeg",u8"RightLeg",
     u8"ETC1" ,u8"ETC2" ,u8"ETC3" ,u8"ETC4" ,u8"ETC5" ,u8"ETC6" };
    static int PartsIndex2 = 0;
    ImGui::Combo(u8"MonFix_Parts", &PartsIndex2, Parts2, IM_ARRAYSIZE(Parts2));

    const char* cMat[] = { "Pos" , "Rot", "Scale"};
    static int cMatIndex = 0;
    ImGui::Combo(u8"MonSelect_Mat", &cMatIndex, cMat, IM_ARRAYSIZE(cMat));

    const char* cCoord[] = { "X" , "Y" , "Z" };
    static int cCoordIndex = 0;
    ImGui::Combo(u8"MonSelect_Coord", &cCoordIndex, cCoord, IM_ARRAYSIZE(cCoord));


    ImGui::InputFloat2("MonStart/Last", m_iMonRotRange);

    if (ImGui::Button(u8"MonFixFrame"))
    {
        _float fRot = (-1.f * (m_iMonRotRange[0]) + (m_iMonRotRange[1]));
        _float fRot2 = (_float)m_iMonRotRange[0];
        _float fRot3 = fRot / (m_iMonFrameRange[1] + 1);
        if (0 <= m_iMonFrameRange[0] && m_iMonFrameRange[1] <= m_vecMonParts.size()) {
            if (cMatIndex == 0) {
                for (_uint i = m_iMonFrameRange[0]; i <= m_iMonFrameRange[1]; i++) {
                    if (cCoordIndex == 0) {
                        m_vecMonParts[i][PartsIndex2].vPosition.x = fRot2;
                    }
                    else if (cCoordIndex == 1) {
                        m_vecMonParts[i][PartsIndex2].vPosition.y = fRot2;
                    }
                    else if (cCoordIndex == 2) {
                        m_vecMonParts[i][PartsIndex2].vPosition.z = fRot2;
                    }
                    fRot2 += fRot3;
                }
            }
            else if (cMatIndex == 1) {
                for (_uint i = m_iMonFrameRange[0]; i <= m_iMonFrameRange[1]; i++) {
                    if (cCoordIndex == 0) {
                        m_vecMonParts[i][PartsIndex2].vRotation.x = fRot2;
                    }
                    else if (cCoordIndex == 1) {
                        m_vecMonParts[i][PartsIndex2].vRotation.y = fRot2;
                    }
                    else if (cCoordIndex == 2) {
                        m_vecMonParts[i][PartsIndex2].vRotation.z = fRot2;
                    }
                    fRot2 += fRot3;
                }
            }
            else if (cMatIndex == 2) {
                for (_uint i = m_iMonFrameRange[0]; i <= m_iMonFrameRange[1]; i++) {
                    if (cCoordIndex == 0) {
                        m_vecMonParts[i][PartsIndex2].vScale.x = fRot2;
                    }
                    else if (cCoordIndex == 1) {
                        m_vecMonParts[i][PartsIndex2].vScale.y = fRot2;
                    }
                    else if (cCoordIndex == 2) {
                        m_vecMonParts[i][PartsIndex2].vScale.z = fRot2;
                    }
                    fRot2 += fRot3;
                }
            }
        }
        else {
            MSG_BOX("범위를 잘못 설정하였습니다.");
        }

    }

    if (ImGui::Button(u8"MonReverse")) {
        vector<MONSTERFRAME*> vecTemp;
        MONSTERFRAME* pTemp = nullptr;
        for (_int i = (m_vecMonParts.size() - 1); i >= 0; --i) {
            pTemp = new MONSTERFRAME[(_uint)MONSTERPARTS::MONSTERPARTS_END];
            for (_uint j = 0; j < (_uint)MONSTERPARTS::MONSTERPARTS_END; ++j) {
                pTemp[j] = m_vecMonParts[i][j];
            }
            vecTemp.push_back(pTemp);
        }
        for (_uint i = 0; i < vecTemp.size(); i++) {
            m_vecMonParts.push_back(vecTemp[i]);
        }
    }
}

void CImGuiMgr::MonMovement()
{
    ImGui::BeginListBox(u8"MonMovement");
    for (_ulong i = 0; i < m_vecMonMovement.size(); i++) {
        string str1 = to_string(i);
        if (ImGui::Selectable(str1.c_str(), i == m_iMonMovementIndex)) {
            m_iMonMovementIndex = i;
        }
    }
    ImGui::EndListBox();

    if (m_vecMonMovement.size() != 0) {
        if (m_vecMonMovement[m_iMonMovementIndex].size() <= m_iMonMovementFrameIndex) {
            m_iMonMovementFrameIndex = 0;
        }
    }

    if (m_vecMonMovement.size() != 0) {
        ImGui::BeginListBox(u8"MonMovementFrame");
        for (_ulong j = 0; j < m_vecMonMovement[m_iMonMovementIndex].size(); j++) {
            string str2 = to_string(j);
            if (ImGui::Selectable(str2.c_str(), j == m_iMonMovementFrameIndex)) {

                m_iMonMovementFrameIndex = j;
            }
        }
        ImGui::EndListBox();
    }

    ImGui::InputInt2("MonMovementRange", m_iMonMovementRagne);

    if (ImGui::Button(u8"MonCreate")) {
        if (0 <= m_iMonMovementRagne[0] && m_iMonMovementRagne[1] < m_vecMonParts.size()) {

            if (m_iMonMovementRagne[1] == (m_vecMonParts.size() - 1)) {
                MonAddFrame();

            }
            vector<MONSTERFRAME*> vecTemp;
            MONSTERFRAME* pFram = nullptr;
            for (_uint i = m_iMonMovementRagne[0]; i <= m_iMonMovementRagne[1]; i++) {
                pFram = new MONSTERFRAME[(_uint)MONSTERPARTS::MONSTERPARTS_END];
                for (_uint j = 0; j < (_uint)MONSTERPARTS::MONSTERPARTS_END; ++j) {
                    pFram[j] = m_vecMonParts[i][j];
                }
                vecTemp.push_back(pFram);
            }
            m_vecMonMovement.push_back(vecTemp);


            for (_int i = m_iMonMovementRagne[0]; i <= m_iMonMovementRagne[1]; i++) {

                Safe_Delete(m_vecMonParts[0]);
                m_vecMonParts.erase(m_vecMonParts.begin());
                m_iMonFrameIndex = 0;
            }
        }
        else {
            //MSG_BOX("범위를 벗어남");
        }
    }

    if (ImGui::Button(u8"MonDeleteMovement"))
    {
        if (m_iMonMovementIndex >= 0 && m_vecMonMovement.size() != 0) {

            m_bMonMovementFrameCheck = false;

            if (m_iMonMovementIndex == m_vecMonMovement.size() - 1 && m_iMonMovementIndex != 0) {
                m_iMonMovementIndex -= 1;
            }
            for_each(m_vecMonMovement[m_iMonMovementIndex].begin(), m_vecMonMovement[m_iMonMovementIndex].end(), CDeleteObj2());
            m_vecMonMovement[m_iMonMovementIndex].clear();
            m_vecMonMovement.erase(m_vecMonMovement.begin() + m_iMonMovementIndex);
        }
    }

    if (ImGui::Button(u8"MonDeleteMovementFrame"))
    {
        if (m_iMonMovementFrameIndex != 0) {
            if (m_iMonMovementFrameIndex == m_vecMonMovement[m_iMonMovementIndex].size() - 1) {
                m_iMonMovementFrameIndex -= 1;
            }
            Safe_Delete(m_vecMonMovement[m_iMonMovementIndex].back());
            m_vecMonMovement[m_iMonMovementIndex].pop_back();
        }
    }

    if (m_vecMonMovement.size() != 0) {
        ImGui::Checkbox("MonMovementFrame", &m_bMonMovementFrameCheck);
    }

    ImGui::InputInt2("MonMovementAddRange", m_iMonMovementAddRange);

    if (ImGui::Button(u8"MonAddMovement"))
    {
        if (0 <= m_iMonMovementAddRange[0] && m_iMonMovementAddRange[1] < m_vecMonMovement.size()) {

            for_each(m_vecMonParts.begin(), m_vecMonParts.end(), CDeleteObj2());
            m_vecMonParts.clear();

            MONSTERFRAME* pFram = nullptr;
            for (_int i = m_iMonMovementAddRange[0]; i <= m_iMonMovementAddRange[1]; i++) {
                for (_int j = 0; j < m_vecMonMovement[i].size(); j++) {
                    pFram = new MONSTERFRAME[(_uint)MONSTERPARTS::MONSTERPARTS_END];
                    for (_uint k = 0; k < (_uint)MONSTERPARTS::MONSTERPARTS_END; ++k) {
                        pFram[k] = m_vecMonMovement[i][j][k];
                    }
                    m_vecMonParts.push_back(pFram);
                }
            }
        }
    }

    if (ImGui::Button(u8"MonStart")) {
        m_bMonAnimationCheck = true;
    }
    if (ImGui::Button(u8"MonStop")) {
        m_bMonAnimationCheck = false;
    }
}

void CImGuiMgr::MonAddFrame()
{
    if (m_bMonLastFrameCheck == false) {
        MONSTERFRAME* pFrame = new MONSTERFRAME[(_uint)MONSTERPARTS::MONSTERPARTS_END];
        ZeroMemory(pFrame, sizeof(MONSTERFRAME[(_uint)MONSTERPARTS::MONSTERPARTS_END]));
        pFrame[(_uint)MONSTERPARTS::HEAD].vPosition = { 0.f,1.6f,0.f };
        pFrame[(_uint)MONSTERPARTS::BODY].vPosition = { 0.f,0.f,0.f };
        pFrame[(_uint)MONSTERPARTS::LEFT_ARM].vPosition = { -1.2f,0.f,0.f };
        pFrame[(_uint)MONSTERPARTS::RIGHT_ARM].vPosition = { 1.2f,0.f,0.f };
        pFrame[(_uint)MONSTERPARTS::LEFT_LEG].vPosition = { -0.4f,-2.4f,0.f };
        pFrame[(_uint)MONSTERPARTS::RIGHT_LEG].vPosition = { 0.4f, -2.4f,0.f };
        pFrame[(_uint)MONSTERPARTS::ETC1].vPosition = { 0.f, 2.f,0.f };
        pFrame[(_uint)MONSTERPARTS::ETC2].vPosition = { 0.f, 2.f,0.f };
        pFrame[(_uint)MONSTERPARTS::ETC3].vPosition = { 0.f, 2.f,0.f };
        pFrame[(_uint)MONSTERPARTS::ETC4].vPosition = { 0.f, 2.f,0.f };
        pFrame[(_uint)MONSTERPARTS::ETC5].vPosition = { 0.f, 2.f,0.f };
        pFrame[(_uint)MONSTERPARTS::ETC6].vPosition = { 0.f, 2.f,0.f };

        pFrame[(_uint)MONSTERPARTS::TOTAL].vScale = { 0.5f,0.5f,0.5f };
        pFrame[(_uint)MONSTERPARTS::HEAD].vScale = { 0.8f,0.8f,0.8f };
        pFrame[(_uint)MONSTERPARTS::BODY].vScale = { 0.8f,1.2f,0.4f };
        pFrame[(_uint)MONSTERPARTS::LEFT_ARM].vScale = { 0.4f,1.2f,0.4f };
        pFrame[(_uint)MONSTERPARTS::RIGHT_ARM].vScale = { 0.4f,1.2f,0.4f };
        pFrame[(_uint)MONSTERPARTS::LEFT_LEG].vScale = { 0.4f,1.2f,0.4f };
        pFrame[(_uint)MONSTERPARTS::RIGHT_LEG].vScale = { 0.4f,1.2f,0.4f };
        pFrame[(_uint)MONSTERPARTS::ETC1].vScale = { 0.5f, 0.5f,0.5f };
        pFrame[(_uint)MONSTERPARTS::ETC2].vScale = { 0.5f, 0.5f,0.5f };
        pFrame[(_uint)MONSTERPARTS::ETC3].vScale = { 0.5f, 0.5f,0.5f };
        pFrame[(_uint)MONSTERPARTS::ETC4].vScale = { 0.5f, 0.5f,0.5f };
        pFrame[(_uint)MONSTERPARTS::ETC5].vScale = { 0.5f, 0.5f,0.5f };
        pFrame[(_uint)MONSTERPARTS::ETC6].vScale = { 0.5f, 0.5f,0.5f };

        m_vecMonParts.push_back(pFrame);
    }
    else {
        MONSTERFRAME* pFrame = new MONSTERFRAME[(_uint)MONSTERPARTS::MONSTERPARTS_END];
        ZeroMemory(pFrame, sizeof(MONSTERFRAME[(_uint)MONSTERPARTS::MONSTERPARTS_END]));
        pFrame[(_uint)MONSTERPARTS::TOTAL].vPosition = m_vecMonParts.back()[(_uint)MONSTERPARTS::TOTAL].vPosition;
        pFrame[(_uint)MONSTERPARTS::HEAD].vPosition = m_vecMonParts.back()[(_uint)MONSTERPARTS::HEAD].vPosition;
        pFrame[(_uint)MONSTERPARTS::BODY].vPosition = m_vecMonParts.back()[(_uint)MONSTERPARTS::BODY].vPosition;
        pFrame[(_uint)MONSTERPARTS::LEFT_ARM].vPosition = m_vecMonParts.back()[(_uint)MONSTERPARTS::LEFT_ARM].vPosition;
        pFrame[(_uint)MONSTERPARTS::RIGHT_ARM].vPosition = m_vecMonParts.back()[(_uint)MONSTERPARTS::RIGHT_ARM].vPosition;
        pFrame[(_uint)MONSTERPARTS::LEFT_LEG].vPosition = m_vecMonParts.back()[(_uint)MONSTERPARTS::LEFT_LEG].vPosition;
        pFrame[(_uint)MONSTERPARTS::RIGHT_LEG].vPosition = m_vecMonParts.back()[(_uint)MONSTERPARTS::RIGHT_LEG].vPosition;
        pFrame[(_uint)MONSTERPARTS::ETC1].vPosition = m_vecMonParts.back()[(_uint)MONSTERPARTS::ETC1].vPosition;
        pFrame[(_uint)MONSTERPARTS::ETC2].vPosition = m_vecMonParts.back()[(_uint)MONSTERPARTS::ETC2].vPosition;
        pFrame[(_uint)MONSTERPARTS::ETC3].vPosition = m_vecMonParts.back()[(_uint)MONSTERPARTS::ETC3].vPosition;
        pFrame[(_uint)MONSTERPARTS::ETC4].vPosition = m_vecMonParts.back()[(_uint)MONSTERPARTS::ETC4].vPosition;
        pFrame[(_uint)MONSTERPARTS::ETC5].vPosition = m_vecMonParts.back()[(_uint)MONSTERPARTS::ETC5].vPosition;
        pFrame[(_uint)MONSTERPARTS::ETC6].vPosition = m_vecMonParts.back()[(_uint)MONSTERPARTS::ETC6].vPosition;

        pFrame[(_uint)MONSTERPARTS::TOTAL].vRotation = m_vecMonParts.back()[(_uint)MONSTERPARTS::TOTAL].vRotation;
        pFrame[(_uint)MONSTERPARTS::HEAD].vRotation = m_vecMonParts.back()[(_uint)MONSTERPARTS::HEAD].vRotation;
        pFrame[(_uint)MONSTERPARTS::BODY].vRotation = m_vecMonParts.back()[(_uint)MONSTERPARTS::BODY].vRotation;
        pFrame[(_uint)MONSTERPARTS::LEFT_ARM].vRotation = m_vecMonParts.back()[(_uint)MONSTERPARTS::LEFT_ARM].vRotation;
        pFrame[(_uint)MONSTERPARTS::RIGHT_ARM].vRotation = m_vecMonParts.back()[(_uint)MONSTERPARTS::RIGHT_ARM].vRotation;
        pFrame[(_uint)MONSTERPARTS::LEFT_LEG].vRotation = m_vecMonParts.back()[(_uint)MONSTERPARTS::LEFT_LEG].vRotation;
        pFrame[(_uint)MONSTERPARTS::RIGHT_LEG].vRotation = m_vecMonParts.back()[(_uint)MONSTERPARTS::RIGHT_LEG].vRotation;
        pFrame[(_uint)MONSTERPARTS::ETC1].vRotation = m_vecMonParts.back()[(_uint)MONSTERPARTS::ETC1].vRotation;
        pFrame[(_uint)MONSTERPARTS::ETC2].vRotation = m_vecMonParts.back()[(_uint)MONSTERPARTS::ETC2].vRotation;
        pFrame[(_uint)MONSTERPARTS::ETC3].vRotation = m_vecMonParts.back()[(_uint)MONSTERPARTS::ETC3].vRotation;
        pFrame[(_uint)MONSTERPARTS::ETC4].vRotation = m_vecMonParts.back()[(_uint)MONSTERPARTS::ETC4].vRotation;
        pFrame[(_uint)MONSTERPARTS::ETC5].vRotation = m_vecMonParts.back()[(_uint)MONSTERPARTS::ETC5].vRotation;
        pFrame[(_uint)MONSTERPARTS::ETC6].vRotation = m_vecMonParts.back()[(_uint)MONSTERPARTS::ETC6].vRotation;

        pFrame[(_uint)MONSTERPARTS::TOTAL].vScale = m_vecMonParts.back()[(_uint)MONSTERPARTS::TOTAL].vScale;
        pFrame[(_uint)MONSTERPARTS::HEAD].vScale = m_vecMonParts.back()[(_uint)MONSTERPARTS::HEAD].vScale;
        pFrame[(_uint)MONSTERPARTS::BODY].vScale = m_vecMonParts.back()[(_uint)MONSTERPARTS::BODY].vScale;
        pFrame[(_uint)MONSTERPARTS::LEFT_ARM].vScale = m_vecMonParts.back()[(_uint)MONSTERPARTS::LEFT_ARM].vScale;
        pFrame[(_uint)MONSTERPARTS::RIGHT_ARM].vScale = m_vecMonParts.back()[(_uint)MONSTERPARTS::RIGHT_ARM].vScale;
        pFrame[(_uint)MONSTERPARTS::LEFT_LEG].vScale = m_vecMonParts.back()[(_uint)MONSTERPARTS::LEFT_LEG].vScale;
        pFrame[(_uint)MONSTERPARTS::RIGHT_LEG].vScale = m_vecMonParts.back()[(_uint)MONSTERPARTS::RIGHT_LEG].vScale;
        pFrame[(_uint)MONSTERPARTS::ETC1].vScale = m_vecMonParts.back()[(_uint)MONSTERPARTS::ETC1].vScale;
        pFrame[(_uint)MONSTERPARTS::ETC2].vScale = m_vecMonParts.back()[(_uint)MONSTERPARTS::ETC2].vScale;
        pFrame[(_uint)MONSTERPARTS::ETC3].vScale = m_vecMonParts.back()[(_uint)MONSTERPARTS::ETC3].vScale;
        pFrame[(_uint)MONSTERPARTS::ETC4].vScale = m_vecMonParts.back()[(_uint)MONSTERPARTS::ETC4].vScale;
        pFrame[(_uint)MONSTERPARTS::ETC5].vScale = m_vecMonParts.back()[(_uint)MONSTERPARTS::ETC5].vScale;
        pFrame[(_uint)MONSTERPARTS::ETC6].vScale = m_vecMonParts.back()[(_uint)MONSTERPARTS::ETC6].vScale;

        m_vecMonParts.push_back(pFrame);
    }
}

void CImGuiMgr::MonETC_Select_Par()
{
    const char* Parts[] = { u8"Total" ,u8"Head",u8"Body",u8"LeftArm",u8"RightArm",u8"LeftLeg",u8"RightLeg" };
    static int PartsIndex1 = (int)m_vecMonParts[0][(_uint)MONSTERPARTS::ETC1].eETC_Par;
    ImGui::Combo(u8"ETC1", &PartsIndex1, Parts, IM_ARRAYSIZE(Parts));
    m_vecMonParts[0][(_uint)MONSTERPARTS::ETC1].eETC_Par = (MONSTERPARTS)PartsIndex1;

    static int PartsIndex2 = (int)m_vecMonParts[0][(_uint)MONSTERPARTS::ETC2].eETC_Par;
    ImGui::Combo(u8"ETC2", &PartsIndex2, Parts, IM_ARRAYSIZE(Parts));
    m_vecMonParts[0][(_uint)MONSTERPARTS::ETC2].eETC_Par = (MONSTERPARTS)PartsIndex2;

    static int PartsIndex3 = (int)m_vecMonParts[0][(_uint)MONSTERPARTS::ETC3].eETC_Par;
    ImGui::Combo(u8"ETC3", &PartsIndex3, Parts, IM_ARRAYSIZE(Parts));
    m_vecMonParts[0][(_uint)MONSTERPARTS::ETC3].eETC_Par = (MONSTERPARTS)PartsIndex3;

    static int PartsIndex4 = (int)m_vecMonParts[0][(_uint)MONSTERPARTS::ETC4].eETC_Par;
    ImGui::Combo(u8"ETC4", &PartsIndex4, Parts, IM_ARRAYSIZE(Parts));
    m_vecMonParts[0][(_uint)MONSTERPARTS::ETC4].eETC_Par = (MONSTERPARTS)PartsIndex4;

    static int PartsIndex5 = (int)m_vecMonParts[0][(_uint)MONSTERPARTS::ETC5].eETC_Par;
    ImGui::Combo(u8"ETC5", &PartsIndex5, Parts, IM_ARRAYSIZE(Parts));
    m_vecMonParts[0][(_uint)MONSTERPARTS::ETC5].eETC_Par = (MONSTERPARTS)PartsIndex5;

    static int PartsIndex6 = (int)m_vecMonParts[0][(_uint)MONSTERPARTS::ETC6].eETC_Par;
    ImGui::Combo(u8"ETC6", &PartsIndex6, Parts, IM_ARRAYSIZE(Parts));
    m_vecMonParts[0][(_uint)MONSTERPARTS::ETC6].eETC_Par = (MONSTERPARTS)PartsIndex6;
    
}

void CImGuiMgr::SaveMonAnimationData()
{
    //GetOpenFileName()
    OPENFILENAME    open;
    TCHAR   lpstrFile[MAX_PATH] = L"";
    static TCHAR filter[] = L"*.dat";

    ZeroMemory(&open, sizeof(OPENFILENAME));
    open.lStructSize = sizeof(OPENFILENAME);
    open.lpstrFilter = filter;
    open.lpstrFile = lpstrFile;
    open.nMaxFile = 100;
    open.lpstrInitialDir = L"";

    GetModuleFileName(NULL, lpstrFile, MAX_PATH);
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin\Client.exe
    PathRemoveFileSpec(lpstrFile);
    PathRemoveFileSpec(lpstrFile);
    PathRemoveFileSpec(lpstrFile);
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin
    lstrcat(lpstrFile, L"\\Data\\MonAnimation");
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin\Data\Animation
    basic_string<TCHAR> converted(m_strMonText.begin(), m_strMonText.end());
    const _tchar* aa = converted.c_str();

    wcscat_s(lpstrFile, L"\\");
    wcscat_s(lpstrFile, L"MONANIMATION_");
    wcscat_s(lpstrFile, aa);
    wcscat_s(lpstrFile, L".dat");

    if (GetSaveFileName(&open) != 0) {

        HANDLE hFile = CreateFile(lpstrFile, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

        if (INVALID_HANDLE_VALUE == hFile)
            return;

        DWORD	dwByte = 0;
        DWORD	dwStrByte = 0;

        dwStrByte = sizeof(CHAR) * (m_strMonText.length() + 1);

        WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
        WriteFile(hFile, m_strMonText.c_str(), dwStrByte, &dwByte, nullptr);
        WriteFile(hFile, &m_fMonSpeed, sizeof(_float), &dwByte, nullptr);

        for (auto& iter : m_vecMonParts) {
            WriteFile(hFile, iter, sizeof(MONSTERFRAME[(_uint)MONSTERPARTS::MONSTERPARTS_END]), &dwByte, nullptr);
        }

        CloseHandle(hFile);
    }
}

void CImGuiMgr::LoadMonAnimationData()
{
    OPENFILENAME    open;
    TCHAR   lpstrFile[MAX_PATH] = L"";
    static TCHAR filter[] = L"*.*";

    ZeroMemory(&open, sizeof(OPENFILENAME));
    open.lStructSize = sizeof(OPENFILENAME);
    open.lpstrFilter = filter;
    open.lpstrFile = lpstrFile;
    open.nMaxFile = 100;
    open.lpstrInitialDir = L"";

    GetModuleFileName(NULL, lpstrFile, MAX_PATH);
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin\Client.exe
    PathRemoveFileSpec(lpstrFile);
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin
    PathRemoveFileSpec(lpstrFile);
    PathRemoveFileSpec(lpstrFile);
    lstrcat(lpstrFile, L"\\Data\\MonAnimation\\data");
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin\Data\Animation

    if (GetOpenFileName(&open) != 0) {

        for_each(m_vecMonParts.begin(), m_vecMonParts.end(), CDeleteObj2());
        m_vecMonParts.clear();

        HANDLE hFile = CreateFile(lpstrFile, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
        //C:\Users\조우택\Desktop\SR_TeamMinever2\Data\Animation\HUMAN_TEST.dat
        if (INVALID_HANDLE_VALUE == hFile)
            return;

        DWORD	dwByte = 0;
        DWORD	dwStrByte = 0;
        MONSTERFRAME* pFrame = nullptr;
        MONSTERPARTS* pETC = nullptr;

        ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

        CHAR* pTag = new CHAR[dwStrByte];

        ReadFile(hFile, pTag, dwStrByte, &dwByte, nullptr);

        m_strMonText = pTag;

        Safe_Delete_Array(pTag);

        basic_string<TCHAR> converted(m_strMonText.begin(), m_strMonText.end());
        m_MonAniTag = converted.c_str();

        ReadFile(hFile, &m_fMonSpeed, sizeof(_float), &dwByte, nullptr);

        while (true)
        {
            pFrame = new MONSTERFRAME[(_uint)MONSTERPARTS::MONSTERPARTS_END];
            pETC = new MONSTERPARTS;

            ReadFile(hFile, pFrame, sizeof(MONSTERFRAME[(_uint)MONSTERPARTS::MONSTERPARTS_END]), &dwByte, nullptr);

            if (0 == dwByte)
            {
                Safe_Delete(pFrame);
                break;
            }

            m_vecMonParts.push_back(pFrame);
        }
        MONSTERPARTS a = m_vecMonParts[0][(_uint)MONSTERPARTS::ETC6].eETC_Par;
        CloseHandle(hFile);
    }
}

void CImGuiMgr::SaveObjectData()
{
    OPENFILENAME    open;
    TCHAR   lpstrFile[MAX_PATH] = L"";
    static TCHAR filter[] = L"*.dat";

    ZeroMemory(&open, sizeof(OPENFILENAME));
    open.lStructSize = sizeof(OPENFILENAME);
    open.lpstrFilter = filter;
    open.lpstrFile = lpstrFile;
    open.nMaxFile = 100;
    open.lpstrInitialDir = L"";

    GetModuleFileName(NULL, lpstrFile, MAX_PATH);
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin\Client.exe
    PathRemoveFileSpec(lpstrFile);
    PathRemoveFileSpec(lpstrFile);
    PathRemoveFileSpec(lpstrFile);
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin
    lstrcat(lpstrFile, L"\\Data\\ObjectPartsInfo");
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin\Data\Animation
    basic_string<TCHAR> converted(m_strItemPartsText.begin(), m_strItemPartsText.end());
    const _tchar* aa = converted.c_str();

    wcscat_s(lpstrFile, L"\\");
    wcscat_s(lpstrFile, L"PARTSINFO_");
    wcscat_s(lpstrFile, aa);
    wcscat_s(lpstrFile, L".dat");

    if (GetSaveFileName(&open) != 0) {

        HANDLE hFile = CreateFile(lpstrFile, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

        if (INVALID_HANDLE_VALUE == hFile)
            return;

        DWORD	dwByte = 0;


        for (auto& iter : m_vecItemPartsSave) {
            WriteFile(hFile, iter, sizeof(PARTSITEMINFO), &dwByte, nullptr);
        }

        CloseHandle(hFile);
    }
}

void CImGuiMgr::LoadObjectData()
{
    OPENFILENAME    open;
    TCHAR   lpstrFile[MAX_PATH] = L"";
    static TCHAR filter[] = L"*.*";

    ZeroMemory(&open, sizeof(OPENFILENAME));
    open.lStructSize = sizeof(OPENFILENAME);
    open.lpstrFilter = filter;
    open.lpstrFile = lpstrFile;
    open.nMaxFile = 100;
    open.lpstrInitialDir = L"";

    GetModuleFileName(NULL, lpstrFile, MAX_PATH);
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin\Client.exe
    PathRemoveFileSpec(lpstrFile);
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin
    PathRemoveFileSpec(lpstrFile);
    PathRemoveFileSpec(lpstrFile);
    lstrcat(lpstrFile, L"\\Data\\ObjectPartsInfo\\data");
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin\Data\Animation

    if (GetOpenFileName(&open) != 0) {

        for_each(m_vecItemPartsLoad.begin(), m_vecItemPartsLoad.end(), CDeleteObj2());
        m_vecItemPartsLoad.clear();

        HANDLE hFile = CreateFile(lpstrFile, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

        if (INVALID_HANDLE_VALUE == hFile)
            return;

        DWORD	dwByte = 0;

        PARTSITEMINFO* pItemPartsInfo = nullptr;

        while (true)
        {
            pItemPartsInfo = new PARTSITEMINFO;

            ReadFile(hFile, pItemPartsInfo, sizeof(PARTSITEMINFO), &dwByte, nullptr);

            if (0 == dwByte)
            {
                Safe_Delete(pItemPartsInfo);
                break;
            }

            m_vecItemPartsLoad.push_back(pItemPartsInfo);
        }

        CloseHandle(hFile);
    }
}

void CImGuiMgr::SaveObjectInformationData()
{
    OPENFILENAME    open;
    TCHAR   lpstrFile[MAX_PATH] = L"";
    static TCHAR filter[] = L"*.dat";

    ZeroMemory(&open, sizeof(OPENFILENAME));
    open.lStructSize = sizeof(OPENFILENAME);
    open.lpstrFilter = filter;
    open.lpstrFile = lpstrFile;
    open.nMaxFile = 100;
    open.lpstrInitialDir = L"";

    GetModuleFileName(NULL, lpstrFile, MAX_PATH);
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin\Client.exe
    PathRemoveFileSpec(lpstrFile);
    PathRemoveFileSpec(lpstrFile);
    PathRemoveFileSpec(lpstrFile);
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin
    lstrcat(lpstrFile, L"\\Data\\ObjectTotalInfo");
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin\Data\Animation
    /*basic_string<TCHAR> converted(m_strItemTotalText.begin(), m_strItemTotalText.end());
    const _tchar* aa = converted.c_str();*/

    wcscat_s(lpstrFile, L"\\");
    wcscat_s(lpstrFile, L"TOTALINFO_");
    //wcscat_s(lpstrFile, aa);
    wcscat_s(lpstrFile, L".dat");

    if (GetSaveFileName(&open) != 0) {

        HANDLE hFile = CreateFile(lpstrFile, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

        if (INVALID_HANDLE_VALUE == hFile)
            return;

        DWORD	dwByte = 0;


        /*for (auto& iter : m_vecItemPartsSave) {
            WriteFile(hFile, iter, sizeof(PARTSITEMINFO), &dwByte, nullptr);
        }*/

        WriteFile(hFile, m_ItemTotal, sizeof(TOTALITEMINFO), &dwByte, nullptr);

        CloseHandle(hFile);
    }
}

void CImGuiMgr::LoadObjectInforamtionData()
{
    OPENFILENAME    open;
    TCHAR   lpstrFile[MAX_PATH] = L"";
    static TCHAR filter[] = L"*.*\*.dat";

    ZeroMemory(&open, sizeof(OPENFILENAME));
    open.lStructSize = sizeof(OPENFILENAME);
    open.lpstrFilter = filter;
    open.lpstrFile = lpstrFile;
    open.nMaxFile = 100;
    open.lpstrInitialDir = L"";

    GetModuleFileName(NULL, lpstrFile, MAX_PATH);
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin\Client.exe
    PathRemoveFileSpec(lpstrFile);
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin
    PathRemoveFileSpec(lpstrFile);
    PathRemoveFileSpec(lpstrFile);
    lstrcat(lpstrFile, L"\\Data\\ObjectTotalInfo\\data");
    //C:\Users\조우택\Desktop\SR_TeamMine\Client\Bin\Data\Animation

    if (GetOpenFileName(&open) != 0) {

        HANDLE hFile = CreateFile(lpstrFile, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

        if (INVALID_HANDLE_VALUE == hFile)
            return;

        DWORD	dwByte = 0;
        DWORD	dwStrByte = 0;

        //TOTALITEMINFO* pItemPartsInfo = new TOTALITEMINFO;

        ReadFile(hFile, m_ItemTotal, sizeof(TOTALITEMINFO), &dwByte, nullptr);

        CloseHandle(hFile);
    }
}

void CImGuiMgr::ObjectTool()
{
    if (ImGui::TreeNode(u8"ObjectTool"))
    {
        if (ImGui::BeginTabBar(u8"Object", ImGuiTabBarFlags_None)) {

            if (ImGui::BeginTabItem(u8"ObjectCreate")) {

                ObjectCreate();

                ImGui::EndTabItem();
            }
            

            if (ImGui::BeginTabItem(u8"ObjectSetting")) {

                ObjectSetting();

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        ImGui::TreePop();
    }
}

void CImGuiMgr::ObjectCreate()
{
    if (ImGui::Button("Create")) {
        if (Engine::CManagement::GetInstance()->Get_GameLogic_Objects(WEAPON).empty()) {

            _matrix test;
            D3DXMatrixIdentity(&test);

            Engine::CGameObject* pGameObject = nullptr;
            pGameObject = CItemDemo::Create(m_pGraphicDev, ITEM_CREATE);
            Engine::CManagement::GetInstance()->Add_GameLogic_Object(OBJECTTYPE::WEAPON, pGameObject);
            m_mapObject.insert({ OBJECTKEY::KEY_ITEM ,pGameObject });



        }
        else {
            //MSG_BOX("이미 존재합니다");
        }
    }

    ImGui::Checkbox(u8"Texture", &m_bSelectTexture);

    const char* Texture[] = { u8"Black" ,u8"Blue",u8"Brown",u8"Cyan",u8"Gray",u8"Green",u8"Light_Blue", u8"Ligth_Gray" ,u8"Lime" ,u8"Megenta",
                              u8"Orange",u8"Pink",u8"Purple",u8"Red",u8"White",u8"Yellow", u8"cobblestone", "dirt","grassblock", "oak_leaves",
                              "oak_log","stone", "andesite","deepslate", "diamond_block","emerald_block", "farmland", "farmland_moist","gold_block","granite","gravel","hay_block", "oak_planks", 
                               "polished_andesite","polished_deepslate", "polished_diorite", "polished_granite", "red_wool","smooth_stone", "stone_bricks", "tnt", "white_wool", 
        "rose_quartz", "rose_quartz.tiles"
      //  "glass", "stripped_oak_log", "crying_obsidian", "nether_bricks", "nether_gold_ore"
    };

    ImGui::Combo(u8"Parts", &m_iColorTextureIndex, Texture, IM_ARRAYSIZE(Texture));

    char buf[255]{};
    strncpy_s(buf, m_strItemPartsText.c_str(), sizeof(buf) - 1);
    ImGui::InputText("Text", buf, sizeof(buf));
    m_strItemPartsText = buf;

    if (ImGui::Button(u8"Save")) {
        SaveObjectData();
    }

    if (ImGui::Button(u8"Load")) {


        if (Engine::CManagement::GetInstance()->Get_GameLogic_Objects(WEAPON).empty()) {

            LoadObjectData();

            _matrix test;
            D3DXMatrixIdentity(&test);

            Engine::CGameObject* pGameObject = nullptr;
            pGameObject = CItemDemo::Create(m_pGraphicDev, ITEM_CREATE);
            Engine::CManagement::GetInstance()->Add_GameLogic_Object(OBJECTTYPE::WEAPON, pGameObject);
            m_mapObject.insert({ OBJECTKEY::KEY_ITEM ,pGameObject });

        }
        else {
            //MSG_BOX("이미 존재합니다");
        }
    }
}

void CImGuiMgr::ObjectSetting()
{
    const char* Object[] = { u8"Human" ,u8"Quadrupedal",u8"Monster",u8"Item" };
    ImGui::Combo(u8"Object", &m_iObjectCreatIndex, Object, IM_ARRAYSIZE(Object));

    if (ImGui::Button(u8"Load")) {

        if (m_iObjectCreatIndex == OBJECTKEY::KEY_HUMAN) {

            if (Engine::CManagement::GetInstance()->Get_GameLogic_Objects(HUMAN_DEMO).empty()) {

                Engine::CGameObject* pGameObject = nullptr;
                pGameObject = CHumanDemo::Create(m_pGraphicDev);
                Engine::CManagement::GetInstance()->Add_GameLogic_Object(OBJECTTYPE::HUMAN_DEMO, pGameObject);
                m_mapObject.insert({ OBJECTKEY::KEY_HUMAN ,pGameObject });
            }
            else {
                //MSG_BOX("이미 존재합니다");
            }

        }
        else if (m_iObjectCreatIndex == OBJECTKEY::KEY_QUADRUPEDAL) {

        }
        else if (m_iObjectCreatIndex == OBJECTKEY::KEY_MONSTER) {
            if (Engine::CManagement::GetInstance()->Get_GameLogic_Objects(MONSTER_DEMO).empty()) {

                Engine::CGameObject* pGameObject = nullptr;
                pGameObject = CMonsterDemo::Create(m_pGraphicDev);
                Engine::CManagement::GetInstance()->Add_GameLogic_Object(OBJECTTYPE::MONSTER_DEMO, pGameObject);
                m_mapObject.insert({ OBJECTKEY::KEY_MONSTER ,pGameObject });
            }
            else {
                //MSG_BOX("이미 존재합니다");
            }
        }
        else if (m_iObjectCreatIndex == OBJECTKEY::KEY_ITEM) {
            if (Engine::CManagement::GetInstance()->Get_GameLogic_Objects(WEAPON).empty()) {

                LoadObjectData();

                _matrix test;
                D3DXMatrixIdentity(&test);

                Engine::CGameObject* pGameObject = nullptr;
                pGameObject = CItemDemo::Create(m_pGraphicDev, ITEM_USE);
                Engine::CManagement::GetInstance()->Add_GameLogic_Object(OBJECTTYPE::WEAPON, pGameObject);
                m_mapObject.insert({ OBJECTKEY::KEY_ITEM ,pGameObject });

            }
            else {
                //MSG_BOX("이미 존재합니다");
            }
        }
    }

    if (ImGui::Button(u8"Delete")) {

        OBJECTTYPE selectedObjType;

        switch (m_iObjectCreatIndex)
        {
        case 0:
            selectedObjType = OBJECTTYPE::HUMAN_DEMO;
            break;
        case 1:
            selectedObjType = OBJECTTYPE::QUADRUPEDAL;
            break;
        case 2:
            selectedObjType = OBJECTTYPE::MONSTER_DEMO;
            break;
        case 3:
            selectedObjType = OBJECTTYPE::WEAPON;

            break;
        default:
            break;
        }

        if (Engine::CManagement::GetInstance()->Get_GameLogic_Objects(selectedObjType).size() != 0)
        {
            Engine::CManagement::GetInstance()->Get_GameLogic_Objects(selectedObjType).front()->Set_Dead();
            m_mapObject.erase((OBJECTKEY)m_iObjectCreatIndex);
        }
        else {
            //MSG_BOX("이 아이가 아니야");
        }


    }

    if (Engine::CManagement::GetInstance()->Get_GameLogic_Objects(WEAPON).size() != 0) {
        ImGui::InputFloat(u8"ScaleX", &m_ItemTotal->vScale.x, 0.1f, 100.f, "%.3f");
        ImGui::InputFloat(u8"ScaleY", &m_ItemTotal->vScale.y, 0.1f, 100.f, "%.3f");
        ImGui::InputFloat(u8"ScaleZ", &m_ItemTotal->vScale.z, 0.1f, 100.f, "%.3f");
        //ImGui::InputFloat3("Scale", m_ItemTotal->vScale);

        ImGui::InputFloat(u8"PosX", &m_ItemTotal->vStartPosition.x, 1.0f, 100.f, "%.1f");
        ImGui::InputFloat(u8"PosY", &m_ItemTotal->vStartPosition.y, 1.0f, 100.f, "%.1f");
        ImGui::InputFloat(u8"PosZ", &m_ItemTotal->vStartPosition.z, 1.0f, 100.f, "%.1f");
        //ImGui::InputFloat3("Pos", m_ItemTotal->vStartPosition);

        ImGui::InputFloat(u8"RotX", &m_ItemTotal->vStartRotation.x, 5.0f, 100.f, "%.1f");
        ImGui::InputFloat(u8"RotY", &m_ItemTotal->vStartRotation.y, 5.0f, 100.f, "%.1f");
        ImGui::InputFloat(u8"RotZ", &m_ItemTotal->vStartRotation.z, 5.0f, 100.f, "%.1f");
       // ImGui::InputFloat3("Rot", m_ItemTotal->vStartRotation);

        const char* Parts3[] = { u8"Total" ,u8"Head",u8"Body",u8"LeftArm",u8"RightArm",u8"LeftLeg",u8"RightLeg" };
        static int PartsIndex3 = 0;
        ImGui::Combo(u8"Parts", &PartsIndex3, Parts3, IM_ARRAYSIZE(Parts3));
        m_ItemTotal->iPartsType = (PARTS)PartsIndex3;

        if (ImGui::Button(u8"InfoSave")) {
            SaveObjectInformationData();
        }

        if (ImGui::Button(u8"InfoLoad")) {

            LoadObjectInforamtionData();
        }
    }
}

void CImGuiMgr::Free()
{
    for_each(m_vecParts.begin(), m_vecParts.end(), CDeleteObj2());
    m_vecParts.clear();

    for (auto& iter : m_vecMovement) {
        for_each(iter.begin(), iter.end(), CDeleteObj2());
        iter.clear();
    }
    m_vecMovement.clear();

    for_each(m_vecMonParts.begin(), m_vecMonParts.end(), CDeleteObj2());
    m_vecMonParts.clear();

    for (auto& iter : m_vecMonMovement) {
        for_each(iter.begin(), iter.end(), CDeleteObj2());
        iter.clear();
    }
    m_vecMonMovement.clear();

    /*for_each(m_mapObject.begin(), m_mapObject.end(), CDeleteMap());
    m_mapObject.clear();*/

    Safe_Delete(m_ItemTotal);

    for_each(m_vecItemPartsSave.begin(), m_vecItemPartsSave.end(), CDeleteObj2());
    m_vecItemPartsSave.clear();

    for_each(m_vecItemPartsLoad.begin(), m_vecItemPartsLoad.end(), CDeleteObj2());
    m_vecItemPartsLoad.clear();

}
