#pragma once

#include "stdafx.h"
#include "Timer.h"
#include "CShader.h"
#include "CCamera.h"

class CPlayer;

class CScene
{
public:   
	CScene();   
	~CScene();

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
		*pd3dCommandList);
	void ReleaseObjects();

	bool ProcessInput();   
	void AnimateObjects(float fTimeElapsed);  
	void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera);

	void ReleaseUploadBuffers();
	//�׷��� ��Ʈ �ñ׳��ĸ� �����Ѵ�. 
	ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	ID3D12RootSignature *GetGraphicsRootSignature();

protected:
	//��ġ(Batch) ó���� �ϱ� ���Ͽ� ���� ���̴����� ����Ʈ�� ǥ���Ѵ�.
	CObjectsShader *m_pShaders = NULL;
	int m_nShaders = 0;

	ID3D12RootSignature *m_pd3dGraphicsRootSignature; 
	//��Ʈ �ñ׳��ĸ� ��Ÿ���� �������̽� �������̴�. 

public:
	void Put_Player(CPlayer *p)
	{
		m_pShaders[0].pPlayer = p;
	}
	void CreateBullet();
	void CreateEnemy();
	void Skill();

	CGameObject *PickObjectPointedByCursor(int xClient, int yClient, CCamera *pCamera);
};

