#pragma once

#include "AppSupport/ZGConfigHelper.h"

class PlayBaseConfigDlgEvent
{
public:
    virtual void OnViewModeChaned(int view_mode_index) = 0;
    virtual void OnPlayMuted(bool enable_mute) = 0;
    virtual void OnSetPlayVolume(int vol) = 0;
	virtual void OnActivateVideoPlayStreamChanged(std::string streamID, bool activated) = 0;
	virtual void OnActivateAudioPlayStreamChanged(std::string streamID, bool activated) = 0;
};

class PlayBaseConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PlayBaseConfigDlg)

public:
	PlayBaseConfigDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PlayBaseConfigDlg();

    void InitDefaultConfig();

    void SetEventCallBack(PlayBaseConfigDlgEvent * cb);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLAY_BASE_FUN_DLG };
#endif


    virtual BOOL OnInitDialog() override;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

    virtual void OnOK() override;

    virtual void OnCancel() override;

    CComboBox view_mode_combo_box_;

    CSliderCtrl play_volume_slider_;

    PlayBaseConfigDlgEvent  * event_cb_ = nullptr;

public:
    afx_msg void OnBnClickedCheckPlayTopicMute();
    afx_msg void OnCbnSelchangeComboPlayTopicViewMode();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedCheckMutePlayVideoStream();
	afx_msg void OnBnClickedCheckMutePlayAudioStream();
};
