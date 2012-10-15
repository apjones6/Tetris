
#include "../DXUT/DXUT.h"
#include "../Logic/Logic.h"
#include "TriangleView.h"

namespace dxut
{
	
	Triangle::Triangle(dxut::ActorId id, float x, float y, float width, float height)
		: SceneNode(id),
		  mX(x),
		  mY(y),
		  mW(width),
		  mH(height),
		  mElapsed(0.0f),
		  mState(false)
	{
		Initialize();
	}
	
//--------------------------------------------------------------------------------------

	void Triangle::Initialize()
	{
		HRESULT hr;
		ID3D10Device* pd3dDevice = DXUTGetD3D10Device();

		const float lt = mX - mW / 2.0f;
		const float rt = mX + mW / 2.0f;
		const float tp = mY + mH / 2.0f;
		const float bm = mY - mH / 2.0f;

		// Static vertex data
		Vertex v[] = 
			{
				{ D3DXVECTOR3(lt, bm, 1.0f), GREEN },
				{ D3DXVECTOR3(mX, tp, 1.0f), GREEN },
				{ D3DXVECTOR3(rt, bm, 1.0f), GREEN }
			};

		D3D10_BUFFER_DESC bufferDesc;
		D3D10_SUBRESOURCE_DATA initData;

		// Create vertex buffer
		bufferDesc.Usage = D3D10_USAGE_IMMUTABLE;
		bufferDesc.ByteWidth = sizeof(Vertex) * 3;
		bufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		initData.pSysMem = v;
		V(pd3dDevice->CreateBuffer(&bufferDesc, &initData, &mVB1));

		// Static vertex data
		v[0].col = PURPLE;
		v[1].col = PURPLE;
		v[2].col = PURPLE;

		// Create vertex buffer
		V(pd3dDevice->CreateBuffer(&bufferDesc, &initData, &mVB2));

		// Create index data
		DWORD indices[] =
			{
				0, 1, 2
			};

		// Create index buffer
		bufferDesc.Usage = D3D10_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(DWORD) * 3;
		bufferDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		initData.pSysMem = indices;
		V(pd3dDevice->CreateBuffer(&bufferDesc, &initData, &mIB));
	}
	
//--------------------------------------------------------------------------------------

	void Triangle::Update(double time, float elapsedTime)
	{
		// Toggle state every second
		if ((mElapsed += elapsedTime) >= 1.0f)
		{
			mState = !mState;
			mElapsed -= 1.0f;
		}
	}
	
//--------------------------------------------------------------------------------------

	void Triangle::Render()
	{
		ID3D10Device* pd3dDevice = DXUTGetD3D10Device();

		// Set vertex buffer
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		pd3dDevice->IASetVertexBuffers(0, 1, mState ? &mVB1 : &mVB2, &stride, &offset);

		// Set index buffer
		pd3dDevice->IASetIndexBuffer(mIB, DXGI_FORMAT_R32_UINT, 0);
		
		// Set topology
		pd3dDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// Draw
		pd3dDevice->DrawIndexed(3, 0, 0);
	}
	
//--------------------------------------------------------------------------------------

	void Triangle::Kill()
	{
		SAFE_RELEASE(mVB1);
		SAFE_RELEASE(mVB2);
		SAFE_RELEASE(mIB);
	}
	
};