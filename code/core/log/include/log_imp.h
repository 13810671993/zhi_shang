#ifndef __LOG_IMP_H__
#define __LOG_IMP_H__

class CLogImp : public CLog
{
public:
	static CLogImp*	GetInstance();
	static VOID		DestroyInstance();

protected:
	CLogImp();
	~CLogImp();

private:
	static CLogImp*	m_pLogImp;
};

#endif // !__LOG_IMP_H__

