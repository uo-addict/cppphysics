#ifndef PROCESSOR
#define PROCESSOR

#include <vector>

class entity;
class processor
{
	friend class world;
	virtual void process(const std::vector<entity*>&) = 0;
};

#endif

