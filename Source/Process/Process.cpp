
#include "../DXUT/DXUT.h"
#include "Process.h"

#include <algorithm>

#include <boost/foreach.hpp>

namespace dxut
{

	Process::Process()
		: mInitialized(false),
		  mAttached(false),
		  mPaused(false),
		  mKilled(false)
	{
	}
	
//--------------------------------------------------------------------------------------
	
	void Process::Initialize()
	{
		assert(!mInitialized);
		mInitialized = true;
	}
	
//--------------------------------------------------------------------------------------
	
	void Process::Update(float elapsedTime)
	{
		if (!mInitialized)
		{
			Initialize();
		}
	}

//--------------------------------------------------------------------------------------
	
	void Process::Kill()
	{
		assert(!mKilled);
		mKilled = true;
	}
	
//--------------------------------------------------------------------------------------
	
	std::shared_ptr<Process> Process::SetNext(std::shared_ptr<Process> next)
	{
		mNext = next;
		return next;
	}

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
	
	ProcessManager::~ProcessManager()
	{
		// Set all processes detached
		BOOST_FOREACH (std::shared_ptr<Process> process, mProcesses)
		{
			assert(process->IsAttached());
			process->SetAttached(false);
		}

		// Detach all processes
		mProcesses.clear();
	}

//--------------------------------------------------------------------------------------
	
	void ProcessManager::Update(float elapsedTime)
	{
		ProcessList detachList;
		ProcessList attachList;

		// Update processes
		BOOST_FOREACH (std::shared_ptr<Process> process, mProcesses)
		{
			// Mark to detach if killed
			if (process->IsKilled())
			{
				// Get next process to attach
				std::shared_ptr<Process> next = process->Next();
				if (next)
				{
					//process->SetNext(std::shared_ptr<Process>(NULL));
					attachList.push_back(next);
				}

				detachList.push_back(process);
				continue;
			}

			// Update if not paused
			if (!process->IsPaused())
			{
				process->Update(elapsedTime);
			}
		}

		// Detach killed processes
		BOOST_FOREACH (std::shared_ptr<Process> process, detachList)
		{
			Detach(process);
		}

		// Attach next processes
		BOOST_FOREACH (std::shared_ptr<Process> process, attachList)
		{
			Attach(process);
		}
	}

//--------------------------------------------------------------------------------------
	
	void ProcessManager::Attach(std::shared_ptr<Process> process)
	{
		assert(!process->IsAttached());

		mProcesses.push_back(process);
		process->SetAttached(true);
	}
	
//--------------------------------------------------------------------------------------
	
	void ProcessManager::Detach(std::shared_ptr<Process> process)
	{
		assert(process->IsAttached());
		assert(std::find(mProcesses.begin(), mProcesses.end(), process) != mProcesses.end());

		mProcesses.remove(process);
		process->SetAttached(false);
	}

};