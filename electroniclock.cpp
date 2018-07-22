// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "electroniclock.hpp"
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string.h>
#include <string>
#include "Header.h"
#include <cassert>
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
int IntegerSetSize(const IntegerSet & _set)
{
	return IntegerListSize(_set.m_data);
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
	assert(!"Hey is unavailible!");
}

//void IntegerSetInsertAllKeys(const IntegerSet & _sourceSet, IntegerSet & _targetSet)
//{
//	IntegerList::Node * pNode = _sourceSet.m_data.m_pFirst;
//	while (pNode)
//	{
//		IntegerSetInsertKey(_targetSet, pNode->m_value);
//		pNode = pNode->m_pNext;
//	}
//}

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
ElectronicLock::ElectronicLock(const ElectronicLock & _lock)
{
}
ElectronicLock&ElectronicLock::operator = (const ElectronicLock & _lock)
{
	if (&_lock == this)
		return *this;

}
ElectronicLock::ElectronicLock(ElectronicLock && _lock)
{

}
ElectronicLock&ElectronicLock::operator = (ElectronicLock && _lock) 
{
	if (& _lock == this)
		return *this;
	return *this;

}

bool ElectronicLock::isInProgrammingMode()const
{
	return mode == lockOn::progMode;
	/*switch(mode)
	{
	case lockOn::progMode:
		return true;
			break;
	case lockOn::workMode:
		return false;
			break;
	}*/
	
	//if (!mode)
	//{
	//	/*return mode == lockOn::progMode;*/
	//	return false;
	//}
	//else if (mode == lockOn::progMode)/*if (mode != lockOn::progMode)*/
	//{
	//	return true;
	//}
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

}
int ElectronicLock::changeProgrammingCode(int _change)
{
	return 0;
}

bool ElectronicLock::tryUnlocking(int _codeKey)
{

	if (mode == lockOn::progMode)
	{
		throw std::logic_error("Not in operational mode");
	}
	if (IntegerSetHasKey(*nCode, _codeKey)) {
		return true;
	}
	return false;
	/*if (_codeKey == code)
		mode = lockOn::workMode;            
    if (_codeKey != code)
	{	
		return false;
	}

	if (mode == lockOn::progMode)
	{
		throw std::logic_error("Not in operational mode");
	}
	if (mode == lockOn::workMode)
		return true;
	
	
	
	
	return 0;*/

}


const char * ElectronicLock::tryUnlocking()
{
	return 0;
}

bool ElectronicLock::operator == ( ElectronicLock _l)const
{
	return false;
}
bool ElectronicLock::operator != ( ElectronicLock _l)const
{
	return false;
}
