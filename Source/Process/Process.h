
#pragma once

#include <list>
#include <memory>

namespace dxut
{

	class Process
	{
	public:
		explicit Process();
		virtual ~Process() { }

		virtual void Initialize();
		virtual void Update(float elapsedTime) = 0;
		virtual void Kill();

		std::shared_ptr<Process> Next() const { return mNext; }
		std::shared_ptr<Process> SetNext(std::shared_ptr<Process> process);

		bool IsInitialized() const { return mInitialized; }
		bool IsAttached() const { return mAttached; }
		bool IsPaused() const { return mPaused; }
		bool IsKilled() const { return mKilled; }

		void SetAttached(bool attached) { mAttached = attached; }
		void SetPaused(bool paused) { mPaused = paused; }

	private:
		bool mInitialized;
		bool mAttached;
		bool mPaused;
		bool mKilled;

		std::shared_ptr<Process> mNext;
	};
	
//--------------------------------------------------------------------------------------
	
	typedef std::list<std::shared_ptr<Process>> ProcessList;

//--------------------------------------------------------------------------------------
	
	class ProcessManager
	{
	public:
		~ProcessManager();
		
		void Update(float elapsedTime);

		void Attach(std::shared_ptr<Process> process);
		void Detach(std::shared_ptr<Process> process);

	private:
		ProcessList mProcesses;
	};

};