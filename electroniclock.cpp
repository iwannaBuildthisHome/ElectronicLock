// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine
#include <stdio.h> 
#include "electroniclock.hpp"
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string.h>
#include <string>
#include "Header.h"
#include <cassert>
#include <sstream>
#include <set>
#include <cctype>
/*****************************************************************************/

    // TODO ...

/*****************************************************************************/

struct IntegerSet
{
	IntegerList m_data;
};
IntegerSet * IntegerSetCreate()
{
	IntegerSet* pSet = new IntegerSet;
	IntegerListInit(pSet->m_data);
	return pSet;
}

void IntegerSetDestroy(IntegerSet * _pSet)
{
	IntegerListDestroy(_pSet->m_data);
	delete _pSet;
}
void IntegerSetClear(IntegerSet & _set)
{
	IntegerListClear(_set.m_data);
}
bool IntegerSetIsEmpty(const IntegerSet & _set)
{
	return IntegerListIsEmpty(_set.m_data);
}

bool IntegerSetHasKey(const IntegerSet & _set, int _key)
{
	IntegerList::Node * pNode = _set.m_data.m_pFirst;
	while (pNode)
	{
		if (pNode->m_value == _key)
			return true;
		pNode = pNode->m_pNext;
	}
		return false;
}
void IntegerSetInsertKey(IntegerSet & _set, int _key)
{
	if (!IntegerSetHasKey(_set, _key))
		IntegerListPushBack(_set.m_data, _key);
}
void IntegerSetRemoveKey(IntegerSet & _set, int _key)
{
	IntegerList::Node * pNode = _set.m_data.m_pFirst;
	while (pNode)
	{
		if (pNode->m_value == _key)
		{
			IntegerListDeleteNode(_set.m_data, pNode);
			return;
		}
		pNode = pNode->m_pNext;
		
	}
}

IntegerSet * IntegerSetCopy(const IntegerSet * const _pSet) {
	IntegerSet * result = IntegerSetCreate();
	IntegerList::Node * pElement = _pSet->m_data.m_pFirst;
	while (pElement) {
		IntegerListPushBack(result->m_data, pElement->m_value);
		pElement = pElement->m_pNext;
	}
	return result;
}
int IntegerSetSize(const IntegerSet & _set)
{
	int nElements = 0;
	const IntegerList::Node * pNode = _set.m_data.m_pFirst;
	while (pNode)
	{
		++nElements;
		pNode = pNode->m_pNext;
	}

	return nElements;
}
bool IntegerSetEqual(const IntegerSet  & set1, const IntegerSet  & set2)
{
	int size1 = IntegerSetSize(set1);
	int size2 = IntegerSetSize(set2);
	if (size1 != size2)
		return false;

	IntegerList::Node * cNode = set1.m_data.m_pFirst;
	while (cNode)
	{
		if (!IntegerSetHasKey(set2, cNode->m_value))
			return false;
		cNode = cNode->m_pNext;
	}
	return true;
}


ElectronicLock::ElectronicLock(int _code)
{
	mode = lockOn::progMode;
	nCode = IntegerSetCreate();
	IntegerSetInsertKey(*nCode, _code);
}
ElectronicLock::~ElectronicLock()
{
	IntegerSetDestroy(nCode);
}
ElectronicLock::ElectronicLock(ElectronicLock & _lock)
	:mode(_lock.mode)
{
	nCode = IntegerSetCopy(_lock.nCode);
}
ElectronicLock& ElectronicLock::operator = (const ElectronicLock & _lock)
{
	if (this == &_lock)
		return * this;
	else
	{
		delete nCode;
		nCode = new IntegerSet(*_lock.nCode);
		mode = lockOn::workMode;
		return *this;
	}
}
ElectronicLock::ElectronicLock(ElectronicLock && _lock)
	:nCode(std::move(_lock.nCode)), mode(std::move(_lock.mode))
{
	//IntegerSetCopy(_lock.nCode);
	_lock.nCode = nullptr;
}
ElectronicLock&ElectronicLock::operator = (ElectronicLock && _lock) 
{
	if (& _lock == this)
		return *this;
	else
	{
		std::swap(nCode, _lock.nCode);
		std::swap(mode, _lock.mode);
		return *this;
	}
}

bool ElectronicLock::isInProgrammingMode()const
{
	return mode == lockOn::progMode;
}
	bool ElectronicLock::toggleProgrammingMode(int _programmingCode)
	{
		if (!IntegerSetHasKey(*nCode, _programmingCode))
			return false;
		mode = (mode == lockOn::progMode) ? lockOn::workMode : lockOn::progMode;
		return true;
		
		/*if (_programmingCode != code)
			return false;

		if (mode == lockOn::progMode)
		{
			mode = lockOn::workMode;
			return true;
		}
		else 
		{
			mode = lockOn::progMode;
			return true;
		}*/

}
void ElectronicLock::registerCode(int _newCode)
{
	if (mode != lockOn::progMode) {
		throw std::logic_error("Not in programming mode");
	}
	IntegerSetInsertKey(*nCode, _newCode);
	assert(IntegerSetHasKey(*nCode, _newCode));
}
void ElectronicLock::unregisterCode(int _delPrevCode)
{
	if (mode != lockOn::progMode) {
		throw std::logic_error("Not in programming mode");
	}
	IntegerSetRemoveKey(*nCode, _delPrevCode);
	assert(!IntegerSetHasKey(*nCode, _delPrevCode));
}
bool ElectronicLock::changeProgrammingCode(int _change)
{
	if (mode != lockOn::progMode)
		throw std::logic_error("Not in programming mode");
	IntegerSetClear(*nCode);
	IntegerSetInsertKey(*nCode, _change);
	return 0;
}

bool ElectronicLock::tryUnlocking(int _codeKey)
{
	if (mode == lockOn::progMode)
	{
		throw std::logic_error("Not in operational mode");
	}
	if (nCode == nullptr)
	{
		return false;
	}
	if (IntegerSetHasKey(*nCode, _codeKey)) 
	{
		return true;
	}
	return false;
}

bool ElectronicLock::tryUnlocking(const char * _str)
{
	std::stringstream ss;
	ss << _str;
	unsigned int code;
	ss >> code;

	int pCode = 0;
	std::string item(_str);
	sscanf(item.c_str(),"%d", &pCode);
  
	if (!isdigit(_str[0]))
		throw std::logic_error("Bad format");

	if (!IntegerSetHasKey(*nCode, code))
	{  
		return false;
	}
	if(IntegerSetHasKey(*nCode, code))
	{
		return true;
	}
	//std::ostringstream ss;
	//ss << nCode;
 //   char * cstr = new char[ss.str().length() + 1];
	//	strcpy(cstr, ss.str().c_str());
	//	return cstr;
}
  
bool ElectronicLock::operator == ( ElectronicLock _l) const
{
	if (IntegerSetEqual(*_l.nCode, *this->nCode)){
			return true;
	}
}
bool ElectronicLock::operator != ( ElectronicLock _l)const
{
	return !(*this == _l);
}
