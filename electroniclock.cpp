// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "electroniclock.hpp"
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string.h>
#include <string>
/*****************************************************************************/

    // TODO ...

/*****************************************************************************/



ElectronicLock::ElectronicLock(int _code):code(_code)
{
	m_lock = code;
	progMode = code;
}
ElectronicLock::~ElectronicLock()
{
}
ElectronicLock::ElectronicLock(const ElectronicLock & _lock)
{
	m_lock = _lock.m_lock;

}
ElectronicLock&ElectronicLock::operator = (const ElectronicLock & _lock)
{
	if (&_lock == this)
		return *this;
	m_lock = _lock.m_lock;

}
ElectronicLock::ElectronicLock(ElectronicLock && _lock)
{
	m_lock = _lock.m_lock;

}
ElectronicLock&ElectronicLock::operator = (ElectronicLock && _lock) 
{
	if (& _lock == this)
		return *this;
	std::swap(m_lock, _lock.m_lock);
	return *this;

}

bool ElectronicLock::isInProgrammingMode()
{     /*m_lock*/;

if (code!=m_lock)
{
	return false;
}
else
{
	workMode = m_lock;
	return true;
}


}

bool ElectronicLock::toggleProgrammingMode(int _programmingCode) {
	std::cin >> code;
	_programmingCode = code;
	if (_programmingCode == m_lock)
	{
		return true;
	}
	else if (_programmingCode != m_lock)
	{
		//progMode = m_lock;
		return true;
	}
	else if (_programmingCode != workMode)
	{
		return false;
	}

	else if (_programmingCode != progMode)
	{
		return false;
	}

}
int ElectronicLock::registerCode(int _newCode)
{
	return 0;

}
int ElectronicLock::unregisterCode(int _delPrevCode)
{
	return 0;

}
int ElectronicLock::changeProgrammingCode(int _change)
{
	return 0;
}
int ElectronicLock::tryUnlocking(int _codeKey)
{
	
	return 0;

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




