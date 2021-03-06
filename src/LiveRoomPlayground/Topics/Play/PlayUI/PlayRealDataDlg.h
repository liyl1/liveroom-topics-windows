#pragma once

#include "AppSupport/ZGUIOperator.h"
#include "Play/PlayDemo.h"

class PlayRealDataDlgEvent
{
public:
    virtual void OnRealDataBaseFunctionButtonEvent(bool show) = 0;

};

class PlayRealDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PlayRealDataDlg)

public:
	PlayRealDataDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PlayRealDataDlg();

    void InitShowRealData();
    void UpdateRealData(const PlayRealDataInfo & info);
    void SetEventCallBack(PlayRealDataDlgEvent * cb);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLAY_REAL_DATA_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

    virtual void OnOK() override;

    virtual void OnCancel() override;

    afx_msg void OnBnClickedButtonPlayTopicBaseFun2();

    afx_msg LRESULT OnUICallbackMsg(WPARAM wParam, LPARAM lParam);

    PlayRealDataDlgEvent * event_cb_ = nullptr;

    bool show_base_fun_ = false;


};
