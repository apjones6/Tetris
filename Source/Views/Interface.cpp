
#include "../DXUT/DXUT.h"
#include "Interface.h"

namespace dxut
{

	Panel::Panel(float x, float y, float width, float height, const D3DXCOLOR& color)
		: mX(x), mY(y), mW(width), mH(height),
		  mVisible(false),
		  mColor(color)
	{
	}
	
//--------------------------------------------------------------------------------------

	void Panel::Initialize()
	{
		HRESULT hr;
		ID3D10Device* pd3dDevice = DXUTGetD3D10Device();

		const float lt = mX - mW / 2.0f;
		const float rt = mX + mW / 2.0f;
		const float tp = mY + mH / 2.0f;
		const float bm = mY - mH / 2.0f;

		// Static vertex data
		dxut::Vertex v[] = 
			{
				{ D3DXVECTOR3(lt, bm, 1.0f), mColor },
				{ D3DXVECTOR3(lt, tp, 1.0f), mColor },
				{ D3DXVECTOR3(rt, bm, 1.0f), mColor },
				{ D3DXVECTOR3(rt, tp, 1.0f), mColor }
			};

		D3D10_BUFFER_DESC bufferDesc;
		D3D10_SUBRESOURCE_DATA initData;

		// Create vertex buffer
		bufferDesc.Usage = D3D10_USAGE_IMMUTABLE;
		bufferDesc.ByteWidth = sizeof(dxut::Vertex) * 4;
		bufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		initData.pSysMem = v;
		V(pd3dDevice->CreateBuffer(&bufferDesc, &initData, &mVB));

		// Create index data
		DWORD indices[] =
			{
				0, 1, 2,
				1, 3, 2
			};

		// Create index buffer
		bufferDesc.Usage = D3D10_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(DWORD) * 6;
		bufferDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		initData.pSysMem = indices;
		V(pd3dDevice->CreateBuffer(&bufferDesc, &initData, &mIB));
	}

//--------------------------------------------------------------------------------------

	void Panel::Update(double time, float elapsedTime)
	{
	}

//--------------------------------------------------------------------------------------

	void Panel::Render(ID3D10Device* pd3dDevice)
	{
		// Set vertex buffer
		UINT stride = sizeof(dxut::Vertex);
		UINT offset = 0;
		pd3dDevice->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);

		// Set index buffer
		pd3dDevice->IASetIndexBuffer(mIB, DXGI_FORMAT_R32_UINT, 0);
		
		// Set topology
		pd3dDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// Draw
		pd3dDevice->DrawIndexed(6, 0, 0);
	}

//--------------------------------------------------------------------------------------
	
	void Panel::Kill()
	{
		SAFE_RELEASE(mVB);
		SAFE_RELEASE(mIB);
	}

//--------------------------------------------------------------------------------------

	LRESULT Panel::OnMsgProc(const Message& message)
	{
		return false;
	}

};