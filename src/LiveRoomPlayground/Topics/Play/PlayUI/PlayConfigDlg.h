#pragma once

#include "Play/PlayDemo.h"


class PlayConfigDlgEvent
{
public:
    virtual void OnPlayButtonEvent() = 0;
    virtual void OnBaseFunctionButtonEvent(bool show) = 0;
};


class PlayConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PlayConfigDlg)

public:
	PlayConfigDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PlayConfigDlg();

    void SetEventCallBack(PlayConfigDlgEvent * cb);

    PlayConfig GetConfig();

    void InitDlgData();

    // 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLAY_CONFIG_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonPlayTopicStartPlay();

    CString stream_id_;

    PlayConfigDlgEvent * event_cb_ = nullptr;

    bool show_base_fun_ = false;

    PlayConfig play_config_;
    afx_msg void OnBnClickedButtonPlayTopicBaseFun();
};
