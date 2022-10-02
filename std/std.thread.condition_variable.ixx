export module std.thread.condition.variable;

import std.type.fundamental;
import std.thread.mutex;

export namespace std {

class condition_variable
{
public:
	condition_variable();
	~condition_variable();
	condition_variable(const condition_variable&) = delete;
	condition_variable& operator=(const condition_variable&) = delete;
	void notify_one();
	void notify_all();
	void wait(unique_lock<mutex>& lock);
};

} // namespace std
