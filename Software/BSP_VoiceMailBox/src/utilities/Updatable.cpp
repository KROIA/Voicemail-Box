#include "utilities/Updatable.hpp"
#include <algorithm>

namespace VoiceMailBox
{


	Updatable::Updatable()
	{
		getInstances().push_back(this);
	}
	Updatable::~Updatable()
	{
		std::vector<Updatable*> &updatable = getInstances();
		auto it = std::find(updatable.begin(), updatable.end(), this);
		if (it != updatable.end())
			updatable.erase(it);
	}

	void Updatable::updateInstances()
	{
		for (auto& instance : getInstances())
			instance->update();
	}

	std::vector<Updatable*> &Updatable::getInstances()
	{
		static std::vector<Updatable*> updatables;
		return updatables;
	}

}
