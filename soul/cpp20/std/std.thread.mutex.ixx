export module std.thread.mutex;

import std.type.fundamental;

export namespace std {

class mutex
{
public:
	mutex();
	~mutex();
	mutex(const mutex&) = delete;
	mutex& operator=(const mutex&) = delete;
	void lock();
	bool try_lock();
	void unlock();
};

class recursive_mutex
{
public:
	recursive_mutex();
	~recursive_mutex();
	recursive_mutex(const recursive_mutex&) = delete;
	recursive_mutex& operator=(const recursive_mutex&) = delete;
	void lock();
	bool try_lock();
	void unlock();
};

} // namespace std
