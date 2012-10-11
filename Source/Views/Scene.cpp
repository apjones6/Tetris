
#include "Scene.h"

#include <boost/foreach.hpp>

namespace dxut
{

	SceneNode::SceneNode(const boost::optional<ActorId> actorId)
		: mActorId(actorId)
	{
	}
	
//--------------------------------------------------------------------------------------

	void SceneNode::Update(double time, float elapsedTime)
	{
		BOOST_FOREACH (std::shared_ptr<SceneNode> node, mChildren)
		{
			node->Update(time, elapsedTime);
		}
	}
	
//--------------------------------------------------------------------------------------
	
	void SceneNode::Kill()
	{
		BOOST_FOREACH (std::shared_ptr<SceneNode> node, mChildren)
		{
			node->Kill();
		}
	}
	
//--------------------------------------------------------------------------------------

	void SceneNode::AddNode(std::shared_ptr<SceneNode> node)
	{
		mChildren.push_back(node);
	}
	
//--------------------------------------------------------------------------------------

	void SceneNode::PreRender()
	{
	}

//--------------------------------------------------------------------------------------

	void SceneNode::RenderChildren()
	{
		BOOST_FOREACH (std::shared_ptr<SceneNode> node, mChildren)
		{
			node->PreRender();
			node->Render();
			node->RenderChildren();
			node->PostRender();
		}
	}
	
//--------------------------------------------------------------------------------------

	void SceneNode::PostRender()
	{
	}
	
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

	SceneRoot::SceneRoot()
		: SceneNode(boost::optional<ActorId>())
	{
	}
	
//--------------------------------------------------------------------------------------

	void SceneRoot::Render()
	{
	}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------

	Scene::Scene()
		: mRoot(new SceneRoot)
	{
	}
	
//--------------------------------------------------------------------------------------

	void Scene::Update(double time, float elapsedTime)
	{
		mRoot->Update(time, elapsedTime);
	}
	
//--------------------------------------------------------------------------------------

	void Scene::Render(ID3D10Device* pd3dDevice)
	{
		mRoot->PreRender();
		mRoot->Render();
		mRoot->RenderChildren();
		mRoot->PostRender();
	}

//--------------------------------------------------------------------------------------

	void Scene::Kill()
	{
		mRoot->Kill();
	}
	
//--------------------------------------------------------------------------------------

	void Scene::AddNode(boost::optional<ActorId> id, std::shared_ptr<SceneNode> node)
	{
		if (id)
		{
			mNodeMap[*id] = node;
		}

		mRoot->AddNode(node);
	}

};