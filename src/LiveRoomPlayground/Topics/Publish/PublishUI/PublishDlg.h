
// PublishDlg.h: 头文件
//

#pragma once

#include "AppSupport/ZGUIOperator.h"
#include "AppSupport/ZGLog.h"

#include "Publish/PublishDemo.h"

#include "InitSDKConfigDlg.h"
#include "LoginRoomConfigDlg.h"
#include "PublishConfigDlg.h"
#include "BaseConfigDlg.h"
#include "RealDataDlg.h"


// CPublishDlg 对话框
class CPublishDlg : public CDialogEx,
    public InitSDKConfigDlgEvent, 
    public LoginRoomConfigDlgEvent, 
    public PublishConfigDlgEvent,
    public BaseConfigDlgEvent,
    public RealDataDlgEvent,
    public ILogToView
{
// 构造
public:
    static CPublishDlg * CreateDlgInstance(CWnd * pParent);
    void InitDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PUBLISH_DIALOG };
#endif

    virtual void OnInitSDKButtonEvent() override;

    virtual void OnLoginRoomButtonEvent() override;

    virtual void OnPublishButtonEvent() override;

    virtual void OnBaseFunctionButtonEvent(bool show) override;

    virtual void OnRealDataBaseFunctionButtonEvent(bool show) override;


    virtual void OnResolutionSelectChanged(int w, int h) override;


    virtual void OnBitRateSelectChaned(int bit_rate) override;


    virtual void OnFpsSelectChanged(int fps) override;


    virtual void OnViewModeChaned(int view_mode_index) override;


    virtual void OnCaptureCameraMirrorChanged(bool enable_mirror) override;

	virtual void OnActivateVideoPublishStreamChanged(bool activated) override;
	virtual void OnActivateAudioPublishStreamChanged(bool activated) override;


    virtual void OnVideoDeviceSelectChanged(std::string device_id) override;


    virtual void OnMicDeviceSelectChanged(std::string device_id) override;


    virtual void PrintToView(const char * log_str) override;


    virtual void OnSpeakerDeviceSelectChanged(std::string device_id) override;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
    CPublishDlg(CWnd* pParent = nullptr);	// 标准构造函数

    virtual void OnOK() override;

    virtual void OnCancel() override;

    void OnPublishDemoStatus(ZGPublishStatus status);

    void OnPublishRealDataRefresh(const RealDataInfo & real_data);

    void ShowLoginRoomConfig();

    void ShowPublishConfig();

    void ShowBaseConfig();

    void SetHScroll();
    void ShowRealDataDlg();

    // 实现
protected:

    void AddLogToList(std::string str_log);

    void HideAllConfigDlg();

    InitSDKConfigDlg init_sdk_config_dlg_;
    LoginRoomConfigDlg login_room_config_dlg_;
    PublishConfigDlg publish_config_dlg_;
    BaseConfigDlg base_config_dlg_;
    RealDataDlg real_data_dlg_;

    PublishDemo publish_demo_;

    CListBox log_list_;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg LRESULT OnUICallbackMsg(WPARAM wParam, LPARAM lParam);
};
