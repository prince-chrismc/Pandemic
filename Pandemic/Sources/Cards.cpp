#include <ios> //std::hex
#include <sstream> //std::stringstream
#include "Cards.h"

Card::Card(const CardsList& id, const char * name) : m_name(name)
{
	std::stringstream ss;
	ss << std::hex << id;
	m_id = ss.str();
}

Card::Card(const CardsList & id, const char * name, const char * desc) : m_description(desc)
{
	Card(id, name);
}
