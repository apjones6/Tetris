
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

	/**
	 * A single node of a scene graph, such as a character, or the gun he's holding.
	 */
	class SceneNode
	{
	public:
		explicit SceneNode(const boost::optional<dxut::ActorId> actorId);
		virtual ~SceneNode() { }

		boost::optional<dxut::ActorId> ActorId() const { return mActorId; }

		virtual void Update(double time, float elapsedTime) = 0;
		virtual void Kill() = 0;

		virtual void AddNode(std::shared_ptr<SceneNode> node);

		virtual void Render() = 0;
		virtual void RenderChildren();
		virtual void PreRender();
		virtual void PostRender();

	private:
		const boost::optional<dxut::ActorId> mActorId;

		SceneList mChildren;
	};
	
//--------------------------------------------------------------------------------------

	/**
	 * The root of a scene graph, which all nodes are attached directly or indirectly off.
	 */
	class SceneRoot : public SceneNode
	{
	public:
		explicit SceneRoot();
		
		void Update(double time, float elapsedTime) { SceneNode::Update(time, elapsedTime); }
		void Kill() { SceneNode::Kill(); }

		void Render();
	};
	
//--------------------------------------------------------------------------------------

	/**
	 * The view element which contains the scene graph root, which in turn holds all objects
	 * within the 2D or 3D scene.
	 */
	class Scene : public IViewElement
	{
	public:
		explicit Scene();

		void Update(double time, float elapsedTime);
		void Render(ID3D10Device* pd3dDevice);
		void Kill();
		
		void	AddNode(std::shared_ptr<SceneNode> node);
		LRESULT OnMsgProc(const Message& message);
		
		bool Visible() const { return mVisible; }
		void Visible(bool visible) { mVisible = visible; }

	private:
		std::shared_ptr<SceneNode> mRoot;
		bool mVisible;
		SceneMap mNodeMap;
	};

};