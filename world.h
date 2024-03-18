#ifndef WORLD
#define WORLD

#include <vector>

#include "processor.h"
#include "entity.h"

class processor;
class entity;
class world
{
	std::vector<processor*> processors;
	std::vector<entity*> entities;

public: 
	world() {
	}

	~world() {
	}

	// Add processors
	bool add_processor(processor* processor) {
		if (std::find(processors.begin(), processors.end(), processor) != processors.end()) {
			// Add processor if it doesn't exist
			processors.push_back(processor);
			return true;
		}
		return false;
	}

	// Process world
	void process() {
		for (std::vector<processor*>::iterator itr = processors.begin(); itr != processors.end(); ++itr) {
			(*itr)->process(entities);
		}
	}
};

#endif

