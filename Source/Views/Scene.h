
#pragma once

#include "../Logic/Logic.h"
#include "View.h"

#include <map>
#include <vector>

#include <boost/optional.hpp>

namespace dxut
{
	
	class SceneNode;

//--------------------------------------------------------------------------------------

	typedef std::map<ActorId, std::shared_ptr<SceneNode>> SceneMap;
	typedef std::vector<std::shared_ptr<SceneNode>>		  SceneList;
	
//--------------------------------------------------------------------------------------

	class SceneNode
	{
	public:
		explicit SceneNode(const boost::optional<ActorId> actorId);
		virtual ~SceneNode() { }

		virtual void Update(double time, float elapsedTime) = 0;
		virtual void Kill() = 0;

		virtual void AddNode(std::shared_ptr<SceneNode> node);

		virtual void Render() = 0;
		virtual void RenderChildren();
		virtual void PreRender();
		virtual void PostRender();

	private:
		boost::optional<ActorId> mActorId;

		SceneList mChildren;
	};
	
//--------------------------------------------------------------------------------------

	class SceneRoot : public SceneNode
	{
	public:
		explicit SceneRoot();
		
		void Update(double time, float elapsedTime) { SceneNode::Update(time, elapsedTime); }
		void Kill() { SceneNode::Kill(); }

		void Render();
	};
	
//--------------------------------------------------------------------------------------

	class Scene : public IViewElement
	{
	public:
		explicit Scene();

		void Update(double time, float elapsedTime);
		void Render(ID3D10Device* pd3dDevice);
		void Kill();

		void AddNode(boost::optional<ActorId> id, std::shared_ptr<SceneNode> node);

	private:
		std::shared_ptr<SceneNode> mRoot;
		SceneMap mNodeMap;
	};

};