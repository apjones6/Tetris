
#include "../Core/Message.h"
#include "../DXUT/DXUT.h"
#include "../Input/Input.h"
#include "HumanView.h"
#include "Interface.h"
#include "Scene.h"

#include <boost/foreach.hpp>

namespace dxut
{
	
	HRESULT BuildFX(ID3D10Device* pd3dDevice, ID3D10Effect** pEffect, ID3D10EffectTechnique** pTech)
	{
		DWORD shaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
	#if defined( DEBUG ) || defined( _DEBUG )
		shaderFlags |= D3D10_SHADER_DEBUG;
	#endif
 
		assert(pd3dDevice != NULL);
		assert(*pEffect == NULL);
		assert(*pTech == NULL);

		// Create effect
		ID3D10Blob* errors = 0;
		HRESULT hr = D3DX10CreateEffectFromFile(L"../Effects/Simple.fx", 0, 0, "fx_4_0", shaderFlags, 0, pd3dDevice, 0, 0, pEffect, &errors, 0);
		if (FAILED(hr))
		{
			if (errors)
			{
				// Show compile errors
				MessageBoxA(0, (char*)errors->GetBufferPointer(), 0, 0);
				SAFE_RELEASE(errors);
			}

			return DXTRACE_ERR_MSGBOX(L"D3DX10CreateEffectFromFile", hr);
		} 

		// Create technique
		(*pTech) = (*pEffect)->GetTechniqueByName("Simple");
		return S_OK;
	}

//--------------------------------------------------------------------------------------

	HRESULT BuildVertexLayouts(ID3D10Device* pd3dDevice, ID3D10EffectTechnique* pTech, ID3D10InputLayout** pLayout)
	{
		D3D10_PASS_DESC PassDesc;
		HRESULT hr;

		assert(pd3dDevice != NULL);
		assert(pTech != NULL);
		assert(*pLayout == NULL);

		// Describe input layout
		D3D10_INPUT_ELEMENT_DESC vertexDesc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 }
			};

		// Create input layout
		pTech->GetPassByIndex(0)->GetDesc(&PassDesc);
		V_RETURN(pd3dDevice->CreateInputLayout(vertexDesc, 2, PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, pLayout));
		return S_OK;
	}
	
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
	
	HumanView::HumanView(std::shared_ptr<IKeyboardHandler> keyboardHandler, std::shared_ptr<IMouseHandler> mouseHandler)
		: mKeyboardHandler(keyboardHandler),
	      mMouseHandler(mouseHandler),
		  mLayout(0),
		  mTech(0),
		  mFX(0)
	{
	}
	
//--------------------------------------------------------------------------------------

	HumanView::HumanView()
		: mKeyboardHandler(new KeyboardHandler),
	      mMouseHandler(new MouseHandler),
		  mLayout(0),
		  mTech(0),
		  mFX(0)
	{
	}
	
//--------------------------------------------------------------------------------------

	void HumanView::Initialize()
	{
		HRESULT hr;
		ID3D10Device* pd3dDevice = DXUTGetD3D10Device();

		// Build effects and layouts
		V(BuildFX(pd3dDevice, &mFX, &mTech));
		V(BuildVertexLayouts(pd3dDevice, mTech, &mLayout));

		// Create root scene
		mScene = std::shared_ptr<Scene>(new Scene);
		AddView(mScene);

		// Create interface
		std::shared_ptr<Panel> ui(new Panel(0, 0, 1.0f, 1.0f, dxut::PURPLE));
		ui->Initialize();
		AddView(ui);
	}
	
//--------------------------------------------------------------------------------------

	void HumanView::Update(double time, float elapsedTime)
	{
		// Update input handlers
		mKeyboardHandler->Update(time, elapsedTime);
		mMouseHandler->Update(time, elapsedTime);

		// Update view elements
		BOOST_FOREACH (std::shared_ptr<IViewElement> element, mElementList)
		{
			element->Update(time, elapsedTime);
		}
	}

//--------------------------------------------------------------------------------------

	void HumanView::Render(ID3D10Device* pd3dDevice)
	{
		// Clear render target
		pd3dDevice->ClearRenderTargetView(DXUTGetD3D10RenderTargetView(), BLACK);

		// Get view list end once
		const ViewElementList::const_iterator iEnd = mElementList.end();

		// Get technique description
		D3D10_TECHNIQUE_DESC techDesc;
		mTech->GetDesc(&techDesc);
		
		// Set input layout
		pd3dDevice->IASetInputLayout(mLayout);

		// Set World View Projection matrix
		// TODO: This should be exposed to all scene nodes (and interface classes?) and managed by them
		D3DXMATRIX wvp;
		ID3D10EffectMatrixVariable* fxWVP = mFX->GetVariableByName("gWVP")->AsMatrix();
		D3DXMatrixIdentity(&wvp);
		fxWVP->SetMatrix((float*)&wvp);

		// Loop passes
		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			mTech->GetPassByIndex(p)->Apply(0);

			// Draw views
			for (ViewElementList::iterator i = mElementList.begin(); i != iEnd; ++i)
			{
				(*i)->Render(pd3dDevice);
			}
		}
	}
	
//--------------------------------------------------------------------------------------

	void HumanView::Kill()
	{
		// Shutdown views
		BOOST_FOREACH (std::shared_ptr<IViewElement> element, mElementList)
		{
			element->Kill();
		}

		mElementList.clear();

		SAFE_RELEASE(mLayout);
		SAFE_RELEASE(mFX);
	}

//--------------------------------------------------------------------------------------

	LRESULT HumanView::OnMsgProc(const Message& message)
	{
		// Allow views to handle message
		BOOST_REVERSE_FOREACH (std::shared_ptr<IViewElement> element, mElementList)
		{
			if (element->OnMsgProc(message))
			{
				return true;
			}
		}

		// Handle keyboard messages
		switch (message.msg)
		{
		case WM_KEYDOWN:
			mKeyboardHandler->OnKeyDown(message.wParam);
			return 0;

        case WM_KEYUP:
			mKeyboardHandler->OnKeyUp(message.wParam);
			return 0;
		}

		// Mouse messages require the X and Y coordinates
		const WORD x = LOWORD(message.lParam);
		const WORD y = HIWORD(message.lParam);

		// Handle mouse messages
		switch (message.msg)
		{
		case WM_LBUTTONDOWN:
			mMouseHandler->OnLeftDown(x, y);
			break;

		case WM_LBUTTONUP:
			mMouseHandler->OnLeftUp(x, y);
			break;

		case WM_RBUTTONDOWN:
			mMouseHandler->OnRightDown(x, y);
			break;

		case WM_RBUTTONUP:
			mMouseHandler->OnRightUp(x, y);
			break;

		case WM_MOUSEMOVE:
			mMouseHandler->OnMove(x, y);
			break;
		}

		return 0;
	}

//--------------------------------------------------------------------------------------

	void HumanView::AddView(std::shared_ptr<IViewElement> view)
	{
		mElementList.push_back(view);
	}
	
//--------------------------------------------------------------------------------------

	void HumanView::RemoveView(std::shared_ptr<IViewElement> view)
	{
		mElementList.remove(view);
	}

};