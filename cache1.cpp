#include <map>
#include <string>
#include <memory>
#include <cassert>
#include "cache_data.h"

/*
	not thread-safe implementation
*/
class Cache1
{
	std::map<int, std::shared_ptr<CacheData> > _map;

public:
	bool contains(int key) const
	{
		return _map.find(key) != _map.end();
	}

	std::shared_ptr<CacheData> get(int key) const
	{
		return _map.at(key);
	}

	void insert(int key, std::shared_ptr<CacheData> value)
	{
		_map.insert(std::make_pair(key, value));
	}
};

int main(int argc, char** argv)
{
	// fill cache
	Cache1 cache;
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