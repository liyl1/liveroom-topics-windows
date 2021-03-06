#pragma once

#include <string>

#include "Topics/MediaPlayer/ZGMediaPlayerDemo.h"
#include "AppSupport/ZGUIOperator.h"

#include "ZGSlider.h"

using std::string;

// MediaPlayerDialog 对话框

class MediaPlayerDialog : public CDialogEx, public ZGMediaPlayerDemoCallBack
{
    DECLARE_DYNAMIC(MediaPlayerDialog)

public:
    virtual ~MediaPlayerDialog();

    static MediaPlayerDialog * CreateDlgInstance(CWnd * pParent);

    void StartMediaPlayer();

protected:

    MediaPlayerDialog(CWnd* pParent = nullptr);   // 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_MEDIAPLAYER_DIALOG };
#endif

    virtual BOOL OnInitDialog() override;

    virtual void OnPlayerState(string play_state) override;
    virtual void OnPlayerProgress(long current, long max, string desc) override;
    virtual void OnPlayerStop() override;
    virtual void OnPublishState(string pub_state) override;
    virtual void OnPlayerError(int ec) override;

protected:
    void OnSelPlayAudioTypeChange();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual void PostNcDestroy() override;
    virtual void OnCancel() override;

    void UpdatePlayStatus(string str_status);
    void UpdatePlayerProgress(string str_progress);
    void UpdatePlayProgressSliderStatus(float percent);

private:

    void InitControls();
    void ProcessPlaySliderPosChange(int nPos);
    void ProcessVolumeSliderPosChange(int nPos);
    DECLARE_MESSAGE_MAP()
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg LRESULT OnUICallbackMsg(WPARAM wParam, LPARAM lParam);

    afx_msg void OnBnClickedButtonPlay();
    afx_msg void OnBnClickedButtonStop();
    afx_msg void OnBnClickedButtonPause();
    afx_msg void OnBnClickedButtonResume();

    CListBox * media_file_list_control_;
    CStatic * play_status_control_;
    CStatic * play_progress_status_control_;
    CButton * repeat_checkbox_button_;
    CButton * mic_checkbox_button_;
    ZGSlider play_progress_slider_control_;
    ZGSlider volume_slider_control_;
    CComboBox* play_audio_type_combobox_contronl_;
    CEdit*     viewer_url_edit_contronl_;

    ZGMediaPlayerDemo media_player_;
    string cur_media_file_url_;

    long cur_media_max_duration_;

public:

    afx_msg void OnBnClickedCheckMic();
};
