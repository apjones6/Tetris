
#pragma once

#include "Scene.h"

namespace dxut
{
	
	class Quad : public SceneNode
	{
	public:
		explicit Quad(ActorId id, float x, float y, float width, float height, const D3DXCOLOR& color);

		void Update(double time, float elapsedTime) { }
		void Render();
		void Kill();

	private:
		void Initialize();

	private:
		const float mX, mY, mW, mH;
		const D3DXCOLOR mColor;

		ID3D10Buffer* mVB;
		ID3D10Buffer* mIB;
	};

};