
#pragma once

#include "../Logic/Listener.h"
#include "../Views/Scene.h"

namespace tetris
{
	
	class ViewListener : public dxut::IListener
	{
	public:
		bool Handle(dxut::EventPtr e);
	};
	
//--------------------------------------------------------------------------------------
	
	class Quad : public dxut::SceneNode
	{
	public:
		explicit Quad(dxut::ActorId id, float x, float y, float width, float height, const D3DXCOLOR& color);

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
	
//--------------------------------------------------------------------------------------
	
	class Triangle : public dxut::SceneNode
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