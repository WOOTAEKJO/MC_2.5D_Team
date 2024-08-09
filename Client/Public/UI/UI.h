#pragma once
#include "GameObject.h"
#include "Transform.h"

class CUIState;

BEGIN(Engine)

class CRcTex;
class CTexture;
class CTransform;
class CInputDev;
class CRcTexLeft;

END

class CUI : public CGameObject
{
protected:
	explicit CUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CUI(const CUI& rhs);
	virtual ~CUI();

public:
	virtual HRESULT Ready_GameObject() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject() override;
	virtual void Render_GameObject();
protected:
	virtual HRESULT		Add_Component();
	HRESULT		Setting_UI(const _tchar* tTextureTag);
public:
	void	Set_TextureNum(_int Num) { m_iTextureNum = Num; }
	_int	Get_TextureNum() { return m_iTextureNum; }
public:
	_bool	Get_HideCheck() { return m_bHide; }
	void	Set_HideCheck(_bool bCheck) { m_bHide = bCheck; }
protected:
	CRcTex* m_pBufferCom = nullptr;
	//CTransform* m_pTransformCom = nullptr;
	CTexture* m_pTextureCom = nullptr;
protected: // 직교 투영을 위함
	_matrix	m_matUIProj;
	_matrix m_matUIView;
protected: // 렌더하는 텍스쳐 넘버
	_int	m_iTextureNum = 0;
protected:
	CUIState* m_pUIState = nullptr;

protected: // 크기 맞추기
	_float	m_fSizeX = 0.f;
	_float	m_fSizeY = 0.f;

	_float	m_fX = 0.f;
	_float	m_fY = 0.f;
protected:
	_bool	m_bHide = false;
protected:
	UIORDER	m_eUI_RenderType = UIORDER::UIORDER_END;
protected:
	virtual void Free();
};

