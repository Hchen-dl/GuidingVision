#include "ControlCAN.h"
#include "AngleResult.h"
class ControlCAN_CH
{
	int m_connect;
	int m_devtype;
	int m_devind;
	int m_cannum;
public:
	ControlCAN_CH()
	{
		m_connect = 0;
		m_devtype= 4;//#define VCI_USBCAN1		3    //#define VCI_USBCAN2		4
		m_devind = 0;
		m_cannum = 0;
	}
	int Initial()
	{
		if (m_connect == 1)
		{
			m_connect = 0;
			//Sleep(500);
			//GetDlgItem(IDC_BTN_CONECTCAN)->SetWindowText(_T("连接"));
			VCI_CloseDevice(m_devtype, m_devind);

			//KillTimer(ID_TIMER_SHOWCNT);
			return -1;
		}
		if (VCI_OpenDevice(m_devtype, m_devind, 0) != STATUS_OK)
		{
			//MessageBox(_T("打开设备失败!"), _T("警告"), MB_OK | MB_ICONQUESTION);
			return -2;
		}
		m_connect = 1;
		VCI_INIT_CONFIG init_config;
		int index = 0, filtertype = 0, mode = 0, cannum = 0;
		int devtype = 4;//#define VCI_USBCAN1		3    //#define VCI_USBCAN2		4		
		//CString strcode, strmask, strtiming0, strtiming1, strtmp;
		char szcode[20], szmask[20], sztiming0[20], sztiming1[20];
		unsigned char sztmp[4];
		DWORD code = 0, mask = 0xffffffff, timing0 = 0x01, timing1 = 0x1C;//波特率为250kb时
		init_config.AccCode = code;
		init_config.AccMask = mask;
		init_config.Filter = filtertype;
		init_config.Mode = mode;
		init_config.Timing0 = (UCHAR)timing0;
		init_config.Timing1 = (UCHAR)timing1;
		if (VCI_InitCAN(devtype, index, cannum, &init_config) != STATUS_OK)
		{
			//MessageBox(_T("初始化CAN失败!"), _T("警告"), MB_OK | MB_ICONQUESTION);
			VCI_CloseDevice(devtype, index);
			return -3;
		}
		//m_connect = 1;
		//m_devind = index;
		//m_cannum = cannum;
		//GetDlgItem(IDC_BTN_CONECTCAN)->SetWindowText(_T("断开"));
		//m_recvcount = 0;
		//m_sendcnt = 0;

		//SetTimer(ID_TIMER_SHOWCNT, ID_TIMER_SHOWCNT_TM, NULL);
		//AfxBeginThread(ReceiveThread, this);
	};
	int Connect()
	{
		VCI_StartCAN(m_devtype, m_devind, m_cannum);
		return 1;
	};
	int Close()
	{
		if (m_connect == 1)
		{
			m_connect = 0;
			//Sleep(500);
			//GetDlgItem(IDC_BTN_CONECTCAN)->SetWindowText(_T("连接"));
			VCI_CloseDevice(m_devtype, m_devind);

			//KillTimer(ID_TIMER_SHOWCNT);
			return 1;
		}
	};
	int Send(AngleResult re)
	{
		if (m_connect == 0)
			return 0;
		VCI_CAN_OBJ frameinfo;
		unsigned char FrameID[4];
		//frameinfo.ID=(UINT) 0x0CFFFFC5;//零X零C
		memcpy(&FrameID, re.can_frame_ID, 4);
		BYTE datalen = 8;
		frameinfo.DataLen = datalen;
		memcpy(&frameinfo.Data, re.can_data_, datalen);

		frameinfo.RemoteFlag = 0;
		frameinfo.ExternFlag = 1;
		if (frameinfo.ExternFlag == 1)
		{
			frameinfo.ID = ((DWORD)FrameID[0] << 24) + ((DWORD)FrameID[1] << 16) + ((DWORD)FrameID[2] << 8) +
				((DWORD)FrameID[3]);
		}
		else
		{
			frameinfo.ID = ((DWORD)FrameID[2] << 8) + ((DWORD)FrameID[3]);
		}
		frameinfo.SendType = 0;//
		if (VCI_Transmit(m_devtype, m_devind, m_cannum, &frameinfo, 1) == 1)
		{
			//m_sendcnt += 1;
			//ShowInfo("写入成功", 0);
			//SetDlgItemText(IDC_SHOWSTATUS, _T(""));
			return 1;
		}
		else
		{
			//ShowInfo("写入失败", 2);
			return -1;
		}
	};

};