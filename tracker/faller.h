#include "multisprite.h"

class Faller: public MultiSprite {
public:
	Faller(const std::string& name);
	Faller(const MultiSprite& rhs): MultiSprite(rhs) {}
	virtual void update(Uint32 ticks);
	void draw() const ;
};
