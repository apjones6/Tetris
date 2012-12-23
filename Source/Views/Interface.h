
#pragma once

#include "View.h"

namespace dxut
{

	/**
	 * A user interface control which displays a colored panel in the window.
	 *
	 * This control does not accept user input, but instead wraps other usable controls, such as
	 * buttons and input fields.
	 */
	class Panel : public IViewElement
	{
	public:
		explicit Panel(float x, float y, float width, float height, const D3DXCOLOR& color);
		
		void Initialize();
		void Update(double time, float elapsedTime);
		void Render(ID3D10Device* pd3dDevice);
		void Kill();

		LRESULT OnMsgProc(const Message& message);
		
		bool Visible() const { return mVisible; }
		void Visible(bool visible) { mVisible = visible; }

	private:
		const float mX, mY, mW, mH;
		const D3DXCOLOR mColor;

		bool mVisible;

		ID3D10Buffer* mVB;
		ID3D10Buffer* mIB;
	};

};