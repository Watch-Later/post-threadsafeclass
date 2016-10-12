cmake_minimum_required(VERSION 3.0)
project(article_thread_safe_cache)

add_executable(
	article_thread_safe_cache
	cache_data.h
	cache1.cpp
	cache2.cpp
	cache3.cpp
)