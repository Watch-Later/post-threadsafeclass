#pragma once

#include <inttypes.h>
#include <cstring>

class CacheData
{
	size_t _size;
	uint8_t* _bytes;

public:
	CacheData(size_t size) :
		_size(size),
		_bytes(0)
	{
		if (size > 0)
		{
			_bytes = new uint8_t[_size];
			memset(_bytes, 0, _size);
		}
	}

	~CacheData()
	{
		if (_bytes != 0)
		{
			delete[] _bytes;
			_bytes = 0;
			_size = 0;
		}
	}

	size_t size() const
	{
		return _size;
	}
};