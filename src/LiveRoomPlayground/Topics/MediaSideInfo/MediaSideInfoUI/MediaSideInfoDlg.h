
// MediaSideInfoDlg.h: 头文件
//

#pragma once

#include "AppSupport/ZGUIOperator.h"

#include "MediaSideInfo/ZGMediaSideInfoDemo.h"
#include "MediaSideInfo/ZGMediaSideInfoDemoEnvirentmentHelper.h"

// CMediaSideInfoDlg 对话框
class CMediaSideInfoDlg : public CDialogEx
{

// 构造
public:

    static CMediaSideInfoDlg * CreateDlgInstance(CWnd * pParent);

    void LoginRoom();

protected:
    
    CMediaSideInfoDlg(CWnd* pParent = nullptr);	// 标准构造函数
    
    void OnStatusUpdate(MediaSideInfoStatus status);

    void OnRecvMediaSideInfo(uint8_t * data, int len, string stream_id);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEDIASIDEINFO_DIALOG };
#endif


    virtual void OnOK() override;

    virtual void OnCancel() override;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
    CString login_status_str_;
    CString check_result_str_;
    BOOL is_only_audio_;
    BOOL is_custom_packet_;
    afx_msg void OnBnClickedStartPublishBtn();
protected:
    CListBox send_list_;
    CListBox recv_list_;
    CString send_side_info_str_;
    bool have_checked_ = false;

    afx_msg void OnBnClickedCheckSideInfoBtn();
    afx_msg LRESULT OnUICallbackMsg(WPARAM wParam, LPARAM lParam);


private:

    ZGMediaSideInfoDemoEnvirentmentHelper demo_helper_;

    ZGMediaSideInfoDemo demo_;


public:
    afx_msg void OnBnClickedSendSideInfoBtn();
};
