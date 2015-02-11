#ifndef _TRACER_H_
#define _TRACER_H_

#include <map>


void* operator new(size_t size, const char * file, unsigned int line);
void operator delete(void *p, const char*, unsigned int line);

void* operator new(size_t size);
void operator delete(void *p);

void* operator new[](size_t size);
void operator delete[](void *p);

void* operator new[](size_t size, const char * file, unsigned int line);
void operator delete[](void *p, const char *, unsigned int);


class Tracer
{
private:
	class Entry
	{
	protected:
		const char* file_;
		unsigned int line_;            
	public:
		Entry(const char * file = 0, unsigned int line = 0)
			: file_(file), line_(line) {}

		const char * GetFileName() const { return file_; }
		unsigned int GetLine() const { return line_; }
	};

	class Lock
	{
	protected:
		Tracer& tracer_;
	public:
		Lock (Tracer& tracer): tracer_(tracer){ tracer_.lock(); }
		~Lock() { tracer_.unlock(); }
	};

	friend class Lock;  //保证Lock类能够访问Tracer类的私有成员

private:
	std::map<void*, Entry> mapEntry_;   //也是要分配内存的-->需要重载多个new delete
	                                    //计数防止operator new的递归调用
	void lock() { ++lockCount_; }
	void unlock() { --lockCount_; }
	unsigned int lockCount_;
public:
	Tracer();
   ~Tracer();
   static bool Ready_;  //由于重载new 和 delete要用到Ready_故权限为 public,设置为static
   void Add(void *p, const char *file, unsigned line);
   void Remove(void *p);
   void Dump();
};

extern Tracer NewTrace;

#endif //_TRACER_H_

