#include "CGameObject.h"
#include "CShader.h"

CGameObject::CGameObject()
{
	XMStoreFloat4x4(&m_xmf4x4World, XMMatrixIdentity());
}

CGameObject::~CGameObject()
{
	if (m_pMesh) m_pMesh->Release();
	if (m_pShader)
	{
		m_pShader->ReleaseShaderVariables();
		m_pShader->Release();
	}
}

void CGameObject::SetShader(CShader *pShader)
{
	if (m_pShader) m_pShader->Release();
	m_pShader = pShader;
	if (m_pShader) m_pShader->AddRef();
}

void CGameObject::ReleaseUploadBuffers()
{
	if (m_pMesh) m_pMesh->ReleaseUploadBuffers();

}

void CGameObject::SetMesh(CMesh *pMesh)
{
	if (m_pMesh) m_pMesh->Release();
	m_pMesh = pMesh;
	if (m_pMesh) m_pMesh->AddRef();
}


void CGameObject::Animate(float fElapsedTime)
{
	if (Active)
	{
		if (m_chase == false)
		{
			if (m_time < fElapsedTime * 6000)
			{
				m_time += fElapsedTime;
			}
			else
			{
				m_chase = true;
			}
		}

		XMFLOAT3 xmf3Shift = XMFLOAT3(0, 0, 0);


		if (m_fRotationSpeed != 0.0f) Rotate(&m_xmf3RotationAxis, m_fRotationSpeed * fElapsedTime);

		if (m_fMovingSpeed != 0.0f) Move(m_xmf3MovingDirection, m_fMovingSpeed * fElapsedTime);

		if (m_pMesh)
		{
			m_pMesh->m_xmOOBB.Transform(m_xmOOBB, XMLoadFloat4x4(&m_xmf4x4World));
			XMStoreFloat4(&m_xmOOBB.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_xmOOBB.Orientation)));
		}
	}
	
}

void CGameObject::OnPrepareRender()
{
}

void CGameObject::Rotate(XMFLOAT3 *pxmf3Axis, float fAngle)
{
	XMMATRIX mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(pxmf3Axis),
		XMConvertToRadians(fAngle));
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

void CGameObject::Move(XMFLOAT3& vDirection, float fSpeed)
{
	XMFLOAT3 xmf3Position = GetPosition();
	xmf3Position = Vector3::Add(xmf3Position, vDirection, fSpeed);
	CGameObject::SetPosition(xmf3Position);
}

void CGameObject::CreateShaderVariables(ID3D12Device *pd3dDevice,
	ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CGameObject::ReleaseShaderVariables()
{
}

void CGameObject::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	XMFLOAT4X4 xmf4x4World;
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_xmf4x4World)));
	//��ü�� ���� ��ȯ ����� ��Ʈ ���(32-��Ʈ ��)�� ���Ͽ� ���̴� ����(��� ����)�� �����Ѵ�.
	pd3dCommandList->SetGraphicsRoot32BitConstants(0, 16, &xmf4x4World, 0);
}

void CGameObject::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	if (Active)
	{
		OnPrepareRender();
		//��ü�� ������ ���̴� ����(��� ����)�� �����Ѵ�.
		UpdateShaderVariables(pd3dCommandList);
		if (m_pShader) m_pShader->Render(pd3dCommandList, pCamera);
		if (m_pMesh) m_pMesh->Render(pd3dCommandList);
	}
}

void CGameObject::SetPosition(float x, float y, float z)
{
	m_xmf4x4World._41 = x;
	m_xmf4x4World._42 = y;
	m_xmf4x4World._43 = z;
}

void CGameObject::SetPosition(XMFLOAT3 xmf3Position)
{
	SetPosition(xmf3Position.x, xmf3Position.y, xmf3Position.z);
}

XMFLOAT3 CGameObject::GetPosition()
{
	return(XMFLOAT3(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43));
}

//���� ��ü�� ���� z-�� ���͸� ��ȯ�Ѵ�.
XMFLOAT3 CGameObject::GetLook()
{
	float x = m_xmf4x4World._31;
	float y = m_xmf4x4World._32;
	float z = m_xmf4x4World._33;

	XMFLOAT3 put{ x,y,z };

	return(Vector3::Normalize(put));
}

//���� ��ü�� ���� y-�� ���͸� ��ȯ�Ѵ�. 
XMFLOAT3 CGameObject::GetUp()
{
	float x = m_xmf4x4World._21;
	float y = m_xmf4x4World._22;
	float z = m_xmf4x4World._23;

	XMFLOAT3 put{ x,y,z };

	return(Vector3::Normalize(put));
}

//���� ��ü�� ���� x-�� ���͸� ��ȯ�Ѵ�. 
XMFLOAT3 CGameObject::GetRight()
{
	float x = m_xmf4x4World._11;
	float y = m_xmf4x4World._12;
	float z = m_xmf4x4World._13;

	XMFLOAT3 put{ x,y,z };

	return(Vector3::Normalize(put));
}

//���� ��ü�� ���� x-�� �������� �̵��Ѵ�. 
void CGameObject::MoveStrafe(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Right = GetRight();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Right, fDistance);
	CGameObject::SetPosition(xmf3Position);
}

//���� ��ü�� ���� y-�� �������� �̵��Ѵ�.
void CGameObject::MoveUp(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Up = GetUp();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Up, fDistance);
	CGameObject::SetPosition(xmf3Position);
}

//���� ��ü�� ���� z-�� �������� �̵��Ѵ�. 
void CGameObject::MoveForward(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Look = GetLook();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Look, fDistance);
	CGameObject::SetPosition(xmf3Position);
}

