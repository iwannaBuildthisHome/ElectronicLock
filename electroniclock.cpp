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



ElectronicLock::ElectronicLock(int _code)
{
	
	code = _code;
	m_lock = lockOn::progMode;
	int y;
	/*lock = code;;
	mode = lockOn::progMode;*/
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

bool ElectronicLock::isInProgrammingMode()const
{
	if (!lockOn::progMode)
		return false;
	else
		return true;
	/*if (m_lock == lockOn::workMode)
	{
		return workMode;
	}
	else if (m_lock == lockOn::progMode)
	{
		return progMode;
	}
	else if (m_lock == lockOn::progMode)
	{
		return true;
	}
	else if(m_lock != lockOn::progMode)
	{
		return false;
	}*/
	
}

	bool ElectronicLock::toggleProgrammingMode(int _programmingCode) const
{
		int y;
		
		if (m_lock != workMode)
		{
			m_lock == workMode;
			return true;
		}
		else if (!_programmingCode)
		{
			return false;
		}
		else if(m_lock != progMode)
		{
			m_lock == progMode;
			return true;
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




