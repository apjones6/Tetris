
#pragma once

#include "Scene.h"

namespace dxut
{
	
	class Triangle : public SceneNode
	{
	public:
		explicit Triangle(dxut::ActorId id, float x, float y, float width, float height);

		void Update(double time, float elapsedTime);
		void Render();
		void Kill();

	private:
		void Initialize();

	private:
		const float mX, mY, mW, mH;
		float mElapsed;
		bool mState;

		ID3D10Buffer* mVB1;
		ID3D10Buffer* mVB2;
		ID3D10Buffer* mIB;
	};

};