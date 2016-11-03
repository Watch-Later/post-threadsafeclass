#include <map>
#include <string>
#include <memory>
#include <mutex>
#include <cassert>
#include "cache_data.h"

/*
	thread-safe but not atomic
*/
class Cache2
{
	mutable std::mutex _mtx;
	std::map<int, std::shared_ptr<CacheData> > _map;

public:
	bool contains(int key) const
	{
		std::lock_guard<std::mutex> l(_mtx);
		bool b = _map.find(key) != _map.end();
		return b;
	}

	std::shared_ptr<CacheData> get(int key) const
	{
		std::lock_guard<std::mutex> l(_mtx);
		std::shared_ptr<CacheData> val = _map.at(key); // can throw an std::exception
		return val;
	}

	void insert(int key, std::shared_ptr<CacheData> value)
	{
		std::lock_guard<std::mutex> l(_mtx);
		_map.insert(std::make_pair(key, value));
	}
};

int main(int argc, char** argv)
{
	// fill cache
	Cache2 cache;
	cache.insert(1, std::make_shared<CacheData>(1024));
	cache.insert(2, std::make_shared<CacheData>(2048));

	// get objects from cache and access methods of them
	if (cache.contains(1))
	{
		assert(cache.get(1)->size() == 1024);
	}
	if (cache.contains(2))
	{
		assert(cache.get(2)->size() == 2048);
	}
}