#ifndef __LOGIC_INNER_TOOLS_H__
#define __LOGIC_INNER_TOOLS_H__

//�߳����ߣ����뼶  
#define  BOOST_SLEEP(n)  boost::thread::sleep(boost::get_system_time()+boost::posix_time::millisec(n))

#define MAX_BUFFER_SIZE			(sizeof(void*))	//���ù�����ϢBufferƽ������
#define MAX_BUFFER_NUM			2000			//���ù�����ϢBuf������

#endif
