// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _ELECTRONICLOCK_HPP_
#define _ELECTRONICLOCK_HPP_

/*****************************************************************************/

class ElectronicLock
{
private :
	int code,m_lock, workMode, progMode;
	
public:
	ElectronicLock(int _code);
	~ElectronicLock();
	ElectronicLock(const ElectronicLock & _lock);
	ElectronicLock & operator = ( const ElectronicLock & _lock) ;
	ElectronicLock(ElectronicLock && _lock);
	ElectronicLock & operator = (ElectronicLock && _lock);

    bool isInProgrammingMode();
	bool toggleProgrammingMode(int _programmingCode);
	int registerCode(int _newCode);
	int unregisterCode(int _delPrevCode);
	int changeProgrammingCode(int _change);
	int tryUnlocking(int _codeKey);
	const char * tryUnlocking();
	bool  operator ==( ElectronicLock _l)const ;
	bool  operator !=( ElectronicLock _l)const ;
/*-----------------------------------------------------------------*/

    // TODO ...

/*------------------------------------------------------------------*/

};


/*****************************************************************************/

#endif //  _ELECTRONICLOCK_HPP_
