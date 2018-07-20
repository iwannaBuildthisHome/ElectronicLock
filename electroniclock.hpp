// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _ELECTRONICLOCK_HPP_
#define _ELECTRONICLOCK_HPP_

/*****************************************************************************/
enum lockOn
	{
		progMode = 1, 
		workMode
	};
class ElectronicLock
{
 private:
	 int code;
     int m_lock;
public:
   
	/*ElectronicLock GetOn() 
	{
		return m_lock;
	}
	void SetOn(lockOn m_lock)
	{
		this->m_lock = m_lock;
	}*/
   
	ElectronicLock(int _code);
	~ElectronicLock();
	ElectronicLock(const ElectronicLock & _lock);
	ElectronicLock & operator = ( const ElectronicLock & _lock) ;
	ElectronicLock(ElectronicLock && _lock);
	ElectronicLock & operator = (ElectronicLock && _lock);

    bool isInProgrammingMode() const;
	bool toggleProgrammingMode(int _programmingCode) const;
	int registerCode(int _newCode);
	int unregisterCode(int _delPrevCode);
	int changeProgrammingCode(int _change);
	int tryUnlocking(int _codeKey);
	const char * tryUnlocking();
	bool  operator ==( ElectronicLock _l)const ;
	bool  operator !=( ElectronicLock _l)const ;
};


/*****************************************************************************/

#endif //  _ELECTRONICLOCK_HPP_
