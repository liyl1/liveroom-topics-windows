#pragma once


// CMediaSideinfoPlayVideoDlg 对话框

#include "AppSupport/ZGUIOperator.h"

#include "MediaSideInfo/ZGMediaSideInfoDemo.h"
#include "MediaSideInfo/ZGMediaSideInfoDemoEnvirentmentHelper.h"

class CMediaSideinfoPlayVideoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMediaSideinfoPlayVideoDlg)

public:
   static CMediaSideinfoPlayVideoDlg * CreateDlgInstance(CWnd * pParent);
    CMediaSideinfoPlayVideoDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMediaSideinfoPlayVideoDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEDIASIDEINFO_PLAY };
#endif


    virtual BOOL OnInitDialog() override;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

    afx_msg void OnBnClickedPlay();
    afx_msg void OnBnClickedStop();

private:
    afx_msg LRESULT OnUICallbackMsg(WPARAM wParam, LPARAM lParam);
    void OnStatusUpdate(MediaSideInfoStatus status);
    void OnRecvMediaSideInfo(uint8_t * data, int len, string stream_id);

    bool CheckParams();

    CListBox recv_list_;
    
    unsigned int appid_;
    CString sign_;
    CString room_name_;
    CString room_id_;
    CString stream_id_;
    CString play_params_;

    bool is_url_ = false;

    ZGMediaSideInfoDemoEnvirentmentHelper demo_helper_;
    ZGMediaSideInfoDemo demo_;
public:
    afx_msg void OnBnClickedClear();
    afx_msg void OnBnClickedRadioStreamId();
    afx_msg void OnBnClickedRadioUrl();
};
