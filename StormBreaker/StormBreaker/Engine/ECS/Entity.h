#ifndef ENTITY_H
#define ENTITY_H

#include "framework.h"
#include <string>
struct Entity
{

private:
	std::string  m_entityName;
	uint32_t m_entityId;

public:
	uint32_t     GetEntityId()   const { return m_entityId; }
	std::string  GetEntityName() const  { return m_entityName; }

};
#endif // !ENTITY_H
