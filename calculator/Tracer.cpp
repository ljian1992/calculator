#include <iostream>
#include "Tracer.h"

bool Tracer::Ready_ = false;

Tracer::Tracer() : lockCount_(0)
{
	Ready_ = true;
}

Tracer::~Tracer()
{
	Ready_ = false;
	Dump();
}

void Tracer::Add(void * p, const char * file, unsigned line)
{
	if (lockCount_ > 0)
	{
		return;
	}

	Tracer::Lock lock(*this);

	mapEntry_[p] = Entry(file, line);

}

void Tracer::Remove(void * p)
{
	if (lockCount_ > 0)
	{
		return;
	}

	Tracer::Lock lock(*this);

	std::map<void*, Entry>::const_iterator it = mapEntry_.find(p);

	if (mapEntry_.end() != it)
	{
		mapEntry_.erase(it);
	}


}

void Tracer::Dump()
{
	if (0 < mapEntry_.size())
	{
		std::cout << "-----------------------Memory leak(s)-----------------------" << std::endl;
		std::map<void*, Entry>::const_iterator it = mapEntry_.begin();

		for (; it != mapEntry_.end(); ++it)
		{
			const char* file = it->second.GetFileName();
			unsigned int line = it->second.GetLine();
			unsigned int addr = reinterpret_cast<unsigned int>(it->first);

			std::cout << "0x" << std::hex << addr << ":"
				<< file << "  line: " << std::dec << line << std::endl;
		}
		std::cout << std::endl;
	}
}

Tracer NewTrace;

void* operator new(size_t size, const char * file, unsigned int line)
{

	if (0 == size)  //C++ Standard 规定当要求的内存为 0 byte 时也应该返回有效的内存地址
	{
		size = 1;
	}	

	void *p = malloc(size);
	if (Tracer::Ready_)
	{
		NewTrace.Add(p, file, line);
	}

	return p;
}


void* operator new(size_t size)
{
	void *p = malloc(size);
	if (Tracer::Ready_)
	{
		NewTrace.Add(p, "?", 0);
	}

	return p;
}

void* operator new[](size_t size, const char * file, unsigned int line)
{
	void *p = malloc(size);
	if (Tracer::Ready_)
	{
		NewTrace.Add(p, file, line);
	}

	return p;
}

void* operator new[](size_t size)
{
	void *p = malloc(size);
	if (Tracer::Ready_)
	{
		NewTrace.Add(p, "?", 0);
	}

	return p;
}

void operator delete(void *p, const char* file, unsigned int line)
{
	if (Tracer::Ready_)
	{
		NewTrace.Remove(p);
	}

	free(p);
}

void operator delete(void *p)
{
	if (Tracer::Ready_)
	{
		NewTrace.Remove(p);
	}

	free(p);
}

void operator delete[](void *p, const char *, unsigned int )
{
	if (Tracer::Ready_)
	{
		NewTrace.Remove(p);
	}

	free(p);
}

void operator delete[](void *p)
{
	if (Tracer::Ready_)
	{
		NewTrace.Remove(p);
	}

	free(p);
}