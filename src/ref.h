#ifndef REF_H
#define REF_H

class Ref
{
public:
	Ref() : _ref(1) {}
	virtual ~Ref(){}

	inline int ref(){
		return ++_ref;
	}

	inline int def(){
		--_ref;
		if(_ref <= 0)
			delete this;

		return _ref;
	}

private:
	int _ref;
};

#endif