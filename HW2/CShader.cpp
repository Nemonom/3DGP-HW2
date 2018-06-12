#include "CShader.h"
#include "CPlayer.h"

CShader::~CShader()
{
	if (m_ppd3dPipelineStates)
	{
		for (int i = 0; i < m_nPipelineStates; i++) if (m_ppd3dPipelineStates[i])
			m_ppd3dPipelineStates[i]->Release();
		delete[] m_ppd3dPipelineStates;
	}
}

D3D12_RASTERIZER_DESC CShader::CreateRasterizerState()
{
	D3D12_RASTERIZER_DESC d3dRasterizerDesc;
	::ZeroMemory(&d3dRasterizerDesc, sizeof(D3D12_RASTERIZER_DESC));

	//d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_WIREFRAME;
	
	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
	//d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
	//d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_FRONT;

	d3dRasterizerDesc.FrontCounterClockwise = FALSE;
	d3dRasterizerDesc.DepthBias = 0;
	d3dRasterizerDesc.DepthBiasClamp = 0.0f;
	d3dRasterizerDesc.SlopeScaledDepthBias = 0.0f;
	d3dRasterizerDesc.DepthClipEnable = TRUE;
	d3dRasterizerDesc.MultisampleEnable = FALSE;
	d3dRasterizerDesc.AntialiasedLineEnable = FALSE;
	d3dRasterizerDesc.ForcedSampleCount = 0;
	d3dRasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
	return(d3dRasterizerDesc);
}

D3D12_DEPTH_STENCIL_DESC CShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	::ZeroMemory(&d3dDepthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	
	d3dDepthStencilDesc.DepthEnable = TRUE;
	d3dDepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	
	d3dDepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3dDepthStencilDesc.StencilEnable = FALSE;
	d3dDepthStencilDesc.StencilReadMask = 0x00;
	d3dDepthStencilDesc.StencilWriteMask = 0x00;
	d3dDepthStencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	d3dDepthStencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	return(d3dDepthStencilDesc);
}

D3D12_BLEND_DESC CShader::CreateBlendState()
{
	D3D12_BLEND_DESC d3dBlendDesc;
	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
	d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	return(d3dBlendDesc);
}

D3D12_INPUT_LAYOUT_DESC CShader::CreateInputLayout()
{
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = NULL;
	d3dInputLayoutDesc.NumElements = 0;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;
	return(d3dShaderByteCode);
}

D3D12_SHADER_BYTECODE CShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;
	return(d3dShaderByteCode);
}

//���̴� �ҽ� �ڵ带 �������Ͽ� ����Ʈ �ڵ� ����ü�� ��ȯ�Ѵ�. 
D3D12_SHADER_BYTECODE CShader::CompileShaderFromFile(const wchar_t *pszFileName, LPCSTR
pszShaderName, LPCSTR pszShaderProfile, ID3DBlob **ppd3dShaderBlob)
{
UINT nCompileFlags = 0;
#if defined(_DEBUG)
nCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
::D3DCompileFromFile(pszFileName, NULL, NULL, pszShaderName, pszShaderProfile,
	nCompileFlags, 0, ppd3dShaderBlob, NULL);
D3D12_SHADER_BYTECODE d3dShaderByteCode;
d3dShaderByteCode.BytecodeLength = (*ppd3dShaderBlob)->GetBufferSize();
d3dShaderByteCode.pShaderBytecode = (*ppd3dShaderBlob)->GetBufferPointer();
return(d3dShaderByteCode);
}

void CShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature
	*pd3dGraphicsRootSignature)
{
	ID3DBlob *pd3dVertexShaderBlob = NULL, *pd3dPixelShaderBlob = NULL;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3dPipelineStateDesc;
	::ZeroMemory(&d3dPipelineStateDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	d3dPipelineStateDesc.pRootSignature = pd3dGraphicsRootSignature;
	d3dPipelineStateDesc.VS = CreateVertexShader(&pd3dVertexShaderBlob);
	d3dPipelineStateDesc.PS = CreatePixelShader(&pd3dPixelShaderBlob);
	d3dPipelineStateDesc.RasterizerState = CreateRasterizerState();
	d3dPipelineStateDesc.BlendState = CreateBlendState();
	d3dPipelineStateDesc.DepthStencilState = CreateDepthStencilState();
	d3dPipelineStateDesc.InputLayout = CreateInputLayout();
	d3dPipelineStateDesc.SampleMask = UINT_MAX;
	d3dPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	d3dPipelineStateDesc.NumRenderTargets = 1;
	d3dPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	d3dPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dPipelineStateDesc.SampleDesc.Count = 1;
	d3dPipelineStateDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc,
		__uuidof(ID3D12PipelineState), (void **)&m_ppd3dPipelineStates[0]);
	if (pd3dVertexShaderBlob) pd3dVertexShaderBlob->Release();
	if (pd3dPixelShaderBlob) pd3dPixelShaderBlob->Release();
	if (d3dPipelineStateDesc.InputLayout.pInputElementDescs) delete[]
		d3dPipelineStateDesc.InputLayout.pInputElementDescs;
}

void CShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
	*pd3dCommandList)
{
}

void CShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CShader::UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCommandList, XMFLOAT4X4
	*pxmf4x4World)
{
	XMFLOAT4X4 xmf4x4World;
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(pxmf4x4World)));
	pd3dCommandList->SetGraphicsRoot32BitConstants(0, 16, &xmf4x4World, 0);
}

void CShader::ReleaseShaderVariables()
{
}

void CShader::OnPrepareRender(ID3D12GraphicsCommandList *pd3dCommandList)
{
	//���������ο� �׷��Ƚ� ���� ��ü�� �����Ѵ�.
	pd3dCommandList->SetPipelineState(m_ppd3dPipelineStates[0]);
}

CPlayerShader::CPlayerShader()
{
}
CPlayerShader::~CPlayerShader()
{
}

D3D12_INPUT_LAYOUT_DESC CPlayerShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CPlayerShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"VertexShader.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CPlayerShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"VertexShader.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}
void CPlayerShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature
	*pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

CObjectsShader::CObjectsShader()
{
}
CObjectsShader::~CObjectsShader()
{
}

D3D12_INPUT_LAYOUT_DESC CObjectsShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new
		D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
		D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CObjectsShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"VertexShader.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}
D3D12_SHADER_BYTECODE CObjectsShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"VertexShader.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}

void CObjectsShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature
	*pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CObjectsShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList
	*pd3dCommandList)
{
	CCubeMeshDiffused *pWallMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		100, 100, 1000, 0);
	pWallMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(100, 100, 500), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	
	wall = new CGameObject();
	wall->m_xmOOBB = pWallMesh->m_xmOOBB;
	wall->SetMesh(pWallMesh);
	wall->SetPosition(0,0,400);

	wall->Active = true;


	CCubeMeshDiffused *pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		MY_BULLET_SIZE, MY_BULLET_SIZE, MY_BULLET_SIZE, 0);
	pCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(MY_BULLET_SIZE * 0.5f, MY_BULLET_SIZE * 0.5f, MY_BULLET_SIZE * 0.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	my_bullet = new CGameObject*[max_bullet];

	CGameObject *pRotatingObject = NULL;

	for (int z = 0; z < max_bullet; z++)
	{
		pRotatingObject = new CGameObject();
		pRotatingObject->SetMesh(pCubeMesh);
		//�� ������ü ��ü�� ��ġ�� �����Ѵ�.
		pRotatingObject->Active = false;
		my_bullet[z] = pRotatingObject;
	}
		

	CCubeMeshDiffused *pCubeMesh0 = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		MY_BULLET_SIZE * 2, MY_BULLET_SIZE * 2, MY_BULLET_SIZE * 2, 1);
	pCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(MY_BULLET_SIZE, MY_BULLET_SIZE, MY_BULLET_SIZE), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	CCubeMeshDiffused *pCubeMesh1 = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		MY_BULLET_SIZE * 2, MY_BULLET_SIZE * 2, MY_BULLET_SIZE * 2, 2);
	pCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(MY_BULLET_SIZE, MY_BULLET_SIZE, MY_BULLET_SIZE), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	CCubeMeshDiffused *pCubeMesh2 = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		MY_BULLET_SIZE * 2, MY_BULLET_SIZE * 2, MY_BULLET_SIZE * 2, 3);
	pCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(MY_BULLET_SIZE, MY_BULLET_SIZE, MY_BULLET_SIZE), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));


	enemy = new CGameObject*[max_enemy];

	CGameObject *pEnemyObject = NULL;

	for (int z = 0; z < max_enemy; z++)
	{
		pEnemyObject = new CGameObject();
		if(z % 3 == 0)
			pEnemyObject->SetMesh(pCubeMesh0);	
		else if (z % 3 == 1)
			pEnemyObject->SetMesh(pCubeMesh1);
		else if (z % 3 == 2)
			pEnemyObject->SetMesh(pCubeMesh2); 
		pEnemyObject->Active = false;
		enemy[z] = pEnemyObject;
	}


	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}


void CObjectsShader::ReleaseObjects()
{
	if (my_bullet)
	{
		for (int j = 0; j < max_bullet; j++)
		{
			if (my_bullet[j]) delete my_bullet[j];
		}
		delete[] my_bullet;
	}
	if (enemy)
	{
		for (int j = 0; j < max_enemy; j++)
		{
			if (enemy[j]) delete enemy[j];
		}
		delete[] enemy;
	}

	if (wall)
		delete wall;
}

void CObjectsShader::AnimateObjects(float fTimeElapsed)
{	
	for (int j = 0; j < max_bullet; j++)
	{
		my_bullet[j]->Animate(fTimeElapsed);
	}
	for (int j = 0; j < max_enemy; j++)
	{
		if (enemy[j]->m_chase) enemy[j]->SetMovingDirection(Vector3::Normalize(Vector3::Subtract(pPlayer->GetPosition(), enemy[j]->GetPosition())));
		enemy[j]->Animate(fTimeElapsed);
	}
	
	WallCollision();
}

void CObjectsShader::ReleaseUploadBuffers()
{
	if (my_bullet)
	{
		for (int j = 0; j < max_bullet; j++) my_bullet[j]->ReleaseUploadBuffers();
	}
	if (enemy)
	{
		for (int j = 0; j < max_enemy; j++) enemy[j]->ReleaseUploadBuffers();
	}
	if (wall) wall->ReleaseUploadBuffers();
}

void CObjectsShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	CShader::Render(pd3dCommandList, pCamera);
	for (int j = 0; j < max_bullet; j++)
	{
		if (my_bullet[j])
		{
			my_bullet[j]->Render(pd3dCommandList, pCamera);
		}
	}
	for (int j = 0; j < max_enemy; j++)
	{
		if (enemy[j])
		{
			enemy[j]->Render(pd3dCommandList, pCamera);
		}
	}

	if (wall) wall->Render(pd3dCommandList, pCamera);
}

void CObjectsShader::CreateBullet()
{	
	//�� ������ü ��ü�� ��ġ�� �����Ѵ�.
	my_bullet[bullet_cnt]->SetPosition(pPlayer->GetPosition());
	my_bullet[bullet_cnt]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	my_bullet[bullet_cnt]->SetRotationSpeed(15.f + 3.0f);
	my_bullet[bullet_cnt]->SetMovingDirection(pPlayer->GetLookVector());
	my_bullet[bullet_cnt]->SetMovingSpeed(100);
	my_bullet[bullet_cnt]->Active = true;

	bullet_cnt++;

	bullet_cnt = bullet_cnt % max_bullet;
}

void CObjectsShader::CreateEnemy()
{
	enemy[enemy_cnt]->SetPosition(rand() % 40 - 20, rand() % 40 - 20, pPlayer->GetPosition().z + Vector3::Normalize(pPlayer->GetLookVector()).z * 100 );
	enemy[enemy_cnt]->SetRotationAxis(XMFLOAT3(rand() % 2, 1.0f, rand() % 2));
	enemy[enemy_cnt]->SetRotationSpeed(rand() % 10 + 5.f);
	enemy[enemy_cnt]->SetMovingDirection(XMFLOAT3(rand() % 2 - 1, rand() % 2 - 1, rand() % 2 - 1));
	enemy[enemy_cnt]->SetMovingSpeed(rand() % 30 + 20.f);
	enemy[enemy_cnt]->Active = true;

	enemy_cnt++;

	enemy_cnt = enemy_cnt % max_enemy;

	enemy[enemy_cnt]->SetPosition(rand() % 40 - 20, rand() % 40 - 20, pPlayer->GetPosition().z + Vector3::Normalize(pPlayer->GetLookVector()).z * 100);
	enemy[enemy_cnt]->SetRotationAxis(XMFLOAT3(rand() % 2, 1.0f, rand() % 2));
	enemy[enemy_cnt]->SetRotationSpeed(rand() % 10 + 5.f);
	enemy[enemy_cnt]->SetMovingDirection(XMFLOAT3(rand() % 2 - 1, rand() % 2 - 1, rand() % 2 - 1));
	enemy[enemy_cnt]->SetMovingSpeed(rand() % 30 + 20.f);
	enemy[enemy_cnt]->Active = true;

	enemy_cnt++;

	enemy_cnt = enemy_cnt % max_enemy;

	enemy[enemy_cnt]->SetPosition(rand() % 40 - 20, rand() % 40 - 20, pPlayer->GetPosition().z + Vector3::Normalize(pPlayer->GetLookVector()).z * 100);
	enemy[enemy_cnt]->SetRotationAxis(XMFLOAT3(rand() % 2, 1.0f, rand() % 2));
	enemy[enemy_cnt]->SetRotationSpeed(rand() % 10 + 5.f);
	enemy[enemy_cnt]->SetMovingDirection(XMFLOAT3(rand() % 2 - 1, rand() % 2 - 1, rand() % 2 - 1));
	enemy[enemy_cnt]->SetMovingSpeed(rand() % 30 + 20.f);
	enemy[enemy_cnt]->Active = true;

	enemy_cnt++;

	enemy_cnt = enemy_cnt % max_enemy;

}


void CObjectsShader::WallCollision()
{
	for (int i = 0; i < max_bullet; ++i)
	{
		if (my_bullet[i]->Active == false) continue;
		
		ContainmentType containType = wall->m_xmOOBB.Contains(my_bullet[i]->m_xmOOBB);
		switch (containType)
		{
		case DISJOINT:
			my_bullet[i]->Active = false;
			break;
		}
	}

}