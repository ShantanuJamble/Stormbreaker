#ifndef  COMPONENT_H
#define  COMPONENT_H

struct Component
{
public:
	virtual Component* GetComponent() = 0;
};

#endif // ! COMPONENT_H
