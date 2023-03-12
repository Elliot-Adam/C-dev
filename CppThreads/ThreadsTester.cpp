#include <thread>         // std::thread
#include <mutex>
#include <chrono>
#include <sstream>
#include <list>

#include "ThreadsTester.h"


static bool TerminateAll = false;

static std::mutex Mtx;


class MutexLocker
{
	std::mutex& mtx;

public:
	MutexLocker(std::mutex & mtx)
		: mtx(mtx)
	{
		mtx.lock();
	}

	~MutexLocker()
	{
		mtx.unlock();
	}
};

void ThreadBody(int msWait)
{
	std::stringstream ss;
	ss << std::this_thread::get_id();
	const size_t id = std::stoull(ss.str());

	const char* payload = "0123456789abcdefghijklmnopqrstuvwxyz0123456789";


	printf("%s, id=%08zu, started\n", __FUNCTION__, id);

	while (!TerminateAll)
	{
		{
			MutexLocker l(Mtx);

			//Mtx.lock();

			printf("%s, id=%08zu, executing, msWait=%d. ", __FUNCTION__, id, msWait);
			for (const char* pc = payload; *pc != '\0'; ++pc)
			{
				printf("%c", *pc);
			}
			printf("\n");

			//Mtx.unlock();
		}


		// do stuff...
		std::this_thread::sleep_for(std::chrono::milliseconds(msWait));

	}

	printf("%s, id=%08zu, finished\n", __FUNCTION__, id);
}


#pragma region ThreadsTester
void ThreadsTester::Test()
{
	const size_t numberOfThreads = 20;

	TerminateAll = false;

	std::list<std::thread> threads;

	while(threads.size() < numberOfThreads)
	{
		threads.emplace_back(std::thread(ThreadBody, static_cast<int>((threads.size() % 4) + 1)));
	}

	std::this_thread::sleep_for(std::chrono::seconds(5));

	TerminateAll = true;

	for (std::thread& thread : threads)
	{
		thread.join();	// pauses until thread finishes
	}
}


#pragma endregion ThreadsTester

