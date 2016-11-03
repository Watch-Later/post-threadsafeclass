#include <map>
#include <string>
#include <mutex>
#include <memory>
#include <cassert>
#include "cache_data.h"

class Cache3
{
	mutable std::mutex _mtx;
	std::map<int, std::shared_ptr<CacheData> > _map;

public:
	std::shared_ptr<CacheData> get(int key) const
	{
		std::lock_guard<std::mutex> l(_mtx);
		std::map<int, std::shared_ptr<CacheData> >::const_iterator it;
		if ((it = _map.find(key)) != _map.end())
		{
			auto val = it->second;
			return val;
		}
		return std::shared_ptr<CacheData>();
	} // auto unlock (lock_guard, RAII)

	void insert(int key, std::shared_ptr<CacheData> value)
	{
		std::lock_guard<std::mutex> l(_mtx);
		_map.insert(std::make_pair(key, value));
	} // auto unlock (lock_guard, RAII)
};


int main(int argc, char** argv)
{
	// fill cache
	Cache3 cache;
	cache.insert(1, std::make_shared<CacheData>(1024));
	cache.insert(2, std::make_shared<CacheData>(2048));

	// get objects from cache and access methods of them
	std::shared_ptr<CacheData> val;

	val = cache.get(1);
	if (val)
	{
		assert(val->size() == 1024);
	}

	val = cache.get(2);
	if (val)
	{
		assert(val->size() == 2048);
	}
}
