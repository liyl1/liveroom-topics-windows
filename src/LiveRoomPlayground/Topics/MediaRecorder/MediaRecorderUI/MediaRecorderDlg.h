
// MediaRecorderDlg.h: 头文件
//

#pragma once

#include <string>

#include "Topics/MediaRecorder/ZGMediaRecorderDemo.h"
#include "Topics/MediaRecorder/ZGMediaRecorderDemoHelper.h"

#include "AppSupport/ZGUIOperator.h"

using std::string;

// CMediaRecorderDlg 对话框
class CMediaRecorderDlg : public CDialogEx, public ZGMediaRecorderDemoCallBack
{
// 构造
public:

    static CMediaRecorderDlg * CreateDlgInstance(CWnd * pParent);
    
// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_MEDIARECORDER_DIALOG };
#endif

    void LoginAndPreview();

protected:

    CMediaRecorderDlg(CWnd* pParent = nullptr);	// 标准构造函数

    void OnPublishStateUpdate(string state);
    virtual void OnMediaRecorderFileStatus(const unsigned int duration, const unsigned int file_size) override;
    virtual void OnMediaRecordStateUpdate(string record_state) override;

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

private:
    BOOL is_audio_only_check_ = FALSE;
    BOOL is_video_only_check_ = FALSE;
    BOOL is_both_check_ = TRUE;

    BOOL is_flv_check_ = FALSE;
    BOOL is_mp4_check_ = TRUE;

    CString save_file_path_;
    CString record_file_info_;
    CString record_status_;

    string cur_publish_status_;
    string cur_record_status_;

    ZGMediaRecorderDemoConfig config_;
    ZGMediaRecorderDemoHelper demo_helper_;
    ZGMediaRecorderDemo demo_;

    afx_msg LRESULT OnUICallbackMsg(WPARAM wParam, LPARAM lParam);
    afx_msg void OnBnClickedSetPathButton();
    afx_msg void OnBnClickedStartRecord();
    afx_msg void OnBnClickedStopRecord();
    afx_msg void OnBnClickedPlay();
    afx_msg void OnBnClickedAudioOnlyCheck();
    afx_msg void OnBnClickedVideoOnlyCheck();
    afx_msg void OnBnClickedPublishingCheck();
    afx_msg void OnBnClickedRadioFlv();
    afx_msg void OnBnClickedRadioMp4();
public:
    afx_msg void OnBnClickedBothCheck();
};
