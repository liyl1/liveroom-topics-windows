// BaseConfigDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ZegoLiveRoomTopics.h"
#include "BaseConfigDlg.h"
#include "afxdialogex.h"

#include "Publish/PublishUI/resource.h"


// BaseConfigDlg 对话框

IMPLEMENT_DYNAMIC(BaseConfigDlg, CDialogEx)

BaseConfigDlg::BaseConfigDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BASE_FUN_DLG, pParent)
{

}

BaseConfigDlg::~BaseConfigDlg()
{
}

void BaseConfigDlg::SetEventCallBack(BaseConfigDlgEvent * cb)
{
    event_cb_ = cb;
}

void BaseConfigDlg::InitDefaultConfig()
{
    resolution_combo_box_.ResetContent();
    resolution_combo_box_.AddString(_T("(极清)1920x1080"));
    resolution_combo_box_.AddString(_T("(超清)1280x720"));
    resolution_combo_box_.AddString(_T("(高清)960x540"));
    resolution_combo_box_.AddString(_T("(标准)640x360"));
    resolution_combo_box_.AddString(_T("(流畅)480x270"));
    resolution_combo_box_.AddString(_T("低清)320x180"));
    //resolution_combo_box_.AddString(_T("4K)3840x2160"));

    // sdk 默认
    resolution_combo_box_.SetCurSel(3);

    bitrate_combo_box_.ResetContent();
    bitrate_combo_box_.AddString(_T("(3M)3000000"));
    bitrate_combo_box_.AddString(_T("(1.5M)1500000"));
    bitrate_combo_box_.AddString(_T("(1.2M)1200000"));
    bitrate_combo_box_.AddString(_T("(600KB)600000"));
    bitrate_combo_box_.AddString(_T("(400KB)400000"));
    bitrate_combo_box_.AddString(_T("(300KB)300000"));
    //bitrate_combo_box_.AddString(_T("(12M)12000000"));
    bitrate_combo_box_.SetCurSel(3);

    framte_rate_combo_box_.ResetContent();
    framte_rate_combo_box_.AddString(_T("10"));
    framte_rate_combo_box_.AddString(_T("11"));
    framte_rate_combo_box_.AddString(_T("12"));
    framte_rate_combo_box_.AddString(_T("13"));
    framte_rate_combo_box_.AddString(_T("14"));
    framte_rate_combo_box_.AddString(_T("15"));
    framte_rate_combo_box_.AddString(_T("16"));
    framte_rate_combo_box_.AddString(_T("17"));
    framte_rate_combo_box_.AddString(_T("18"));
    framte_rate_combo_box_.AddString(_T("19"));
    framte_rate_combo_box_.AddString(_T("20"));
    framte_rate_combo_box_.AddString(_T("21"));
    framte_rate_combo_box_.AddString(_T("22"));
    framte_rate_combo_box_.AddString(_T("23"));
    framte_rate_combo_box_.AddString(_T("24"));
    framte_rate_combo_box_.AddString(_T("25"));
    framte_rate_combo_box_.AddString(_T("26"));
    framte_rate_combo_box_.AddString(_T("27"));
    framte_rate_combo_box_.AddString(_T("28"));
    framte_rate_combo_box_.AddString(_T("29"));
    framte_rate_combo_box_.AddString(_T("30"));
    framte_rate_combo_box_.SetCurSel(5);

    view_mode_combo_box_.ResetContent();
    view_mode_combo_box_.AddString(_T("等比缩放, 可能有黑边"));
    view_mode_combo_box_.AddString(_T("等比缩放填充整View"));
    view_mode_combo_box_.AddString(_T("填充整个View"));
    view_mode_combo_box_.SetCurSel(0);

    ((CButton*)GetDlgItem(IDC_CHECK__PUBLISH_TOPIC_MIRROR))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_CHECK_ActivateAudioPublishStream))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_CHECK_ActivateVideoPublishStream))->SetCheck(TRUE);


    video_device_list_ = ZGConfigHelperInstance()->GetVideoDevicesList();

    camera_combo_box_.ResetContent();
    for (int i = 0; i < video_device_list_.size(); ++i)
    {
        camera_combo_box_.AddString(CString(CStringA(video_device_list_[i].device_name.c_str())));
    }

    VideoDeviceInfo default_dev;
    cur_vieo_devie_index_ = 0;
    if (ZGConfigHelperInstance()->GetDefaultVideoDevice(default_dev))
    {
        cur_vieo_devie_index_ = default_dev.index;
        camera_combo_box_.SetCurSel(cur_vieo_devie_index_);
    }

    mic_device_list_ = ZGConfigHelperInstance()->GetMicDevicesList();
    mic_combo_box_.ResetContent();
    for (int i = 0; i < mic_device_list_.size(); ++i)
    {
        mic_combo_box_.AddString(CString(CStringA(mic_device_list_[i].device_name.c_str())));
    }

    cur_mic_devie_index_ = 0;
    AudioDeviceInfo defalut_mic;
    if (ZGConfigHelperInstance()->GetDefaultMicDevice(defalut_mic))
    {
        cur_mic_devie_index_ = defalut_mic.index;
        mic_combo_box_.SetCurSel(cur_mic_devie_index_);
    }

    speaker_device_list_ = ZGConfigHelperInstance()->GetSpeakerDevicesList();
    speaker_combo_box_.ResetContent();
    for (int i = 0; i < speaker_device_list_.size(); ++i)
    {
        speaker_combo_box_.AddString(CString(CStringA(speaker_device_list_[i].device_name.c_str())));
    }

    AudioDeviceInfo defalut_speaker;
    cur_speaker_devie_index_ = 0;
    if (ZGConfigHelperInstance()->GetDefaultSpeakerDevice(defalut_speaker))
    {
        cur_speaker_devie_index_ = defalut_speaker.index;
        speaker_combo_box_.SetCurSel(cur_speaker_devie_index_);
    }

}

BOOL BaseConfigDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    InitDefaultConfig();


    return TRUE;
}

void BaseConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_PUBLISH_TOPIC_RESOLUTION, resolution_combo_box_);
    DDX_Control(pDX, IDC_COMBO_PUBLISH_TOPIC_BITRATE, bitrate_combo_box_);
    DDX_Control(pDX, IDC_COMBO_PUBLISH_TOPIC_FRAME_RATE, framte_rate_combo_box_);
    DDX_Control(pDX, IDC_COMBO_PUBLISH_TOPIC_VIEW_MODE, view_mode_combo_box_);
    DDX_Control(pDX, IDC_COMBO_PUBLISH_TOPIC_VIDEO_LIST, camera_combo_box_);
    DDX_Control(pDX, IDC_COMBO_PUBLISH_TOPIC_MIC_LIST, mic_combo_box_);
    DDX_Control(pDX, IDC_COMBO_PUBLISH_TOPIC_SPEAKER, speaker_combo_box_);
}


void BaseConfigDlg::OnOK()
{
}

void BaseConfigDlg::OnCancel()
{
}

BEGIN_MESSAGE_MAP(BaseConfigDlg, CDialogEx)
    ON_CBN_SELCHANGE(IDC_COMBO_PUBLISH_TOPIC_RESOLUTION, &BaseConfigDlg::OnCbnSelchangeComboPublishTopicResolution)
    ON_CBN_SELCHANGE(IDC_COMBO_PUBLISH_TOPIC_BITRATE, &BaseConfigDlg::OnCbnSelchangeComboPublishTopicBitrate)
    ON_CBN_SELCHANGE(IDC_COMBO_PUBLISH_TOPIC_FRAME_RATE, &BaseConfigDlg::OnCbnSelchangeComboPublishTopicFrameRate)
    ON_CBN_SELCHANGE(IDC_COMBO_PUBLISH_TOPIC_VIEW_MODE, &BaseConfigDlg::OnCbnSelchangeComboPublishTopicViewMode)
    ON_BN_CLICKED(IDC_CHECK__PUBLISH_TOPIC_MIRROR, &BaseConfigDlg::OnBnClickedCheck)
    ON_CBN_SELCHANGE(IDC_COMBO_PUBLISH_TOPIC_VIDEO_LIST, &BaseConfigDlg::OnCbnSelchangeComboPublishTopicVideoList)
    ON_CBN_SELCHANGE(IDC_COMBO_PUBLISH_TOPIC_MIC_LIST, &BaseConfigDlg::OnCbnSelchangeComboPublishTopicMicList)
    ON_CBN_SELCHANGE(IDC_COMBO_PUBLISH_TOPIC_SPEAKER, &BaseConfigDlg::OnCbnSelchangeComboPublishTopicSpeaker)
	ON_BN_CLICKED(IDC_CHECK_ActivateAudioPublishStream, &BaseConfigDlg::OnBnClickedCheckActivateaudiopublishstream)
	ON_BN_CLICKED(IDC_CHECK_ActivateVideoPublishStream, &BaseConfigDlg::OnBnClickedCheckActivatevideopublishstream)
END_MESSAGE_MAP()


// BaseConfigDlg 消息处理程序


void BaseConfigDlg::OnCbnSelchangeComboPublishTopicResolution()
{
    if (event_cb_ != nullptr)
    {
        int sel_index = resolution_combo_box_.GetCurSel();
        int w = 0, h = 0;
        switch (sel_index)
        {
        case 0:
            w = 1920;
            h = 1080;
            break;
        case 1:
            w = 1280;
            h = 720;
            break;
        case 2:
            w = 960;
            h = 540;
            break;
        case 3:
            w = 640;
            h = 360;
            break;
        case 4:
            w = 480;
            h = 270;
            break;
        case 5:
            w = 320;
            h = 180;
            break;
        case 6:
            w = 3840;
            h = 2160;
            break;
        default:
            break;
        }
        if (w != 0 && h != 0)
        {
            event_cb_->OnResolutionSelectChanged(w, h);
        }
    }
}


void BaseConfigDlg::OnCbnSelchangeComboPublishTopicBitrate()
{
    if (event_cb_ != nullptr)
    {
        int sel_index = bitrate_combo_box_.GetCurSel();
        int bitrates[] = { 3000000 , 1500000 , 1200000 , 600000 ,400000, 300000,12000000 };
        if (sel_index < sizeof(bitrates) / sizeof(int))
        {
            event_cb_->OnBitRateSelectChaned(bitrates[sel_index]);
        }
    }
}


void BaseConfigDlg::OnCbnSelchangeComboPublishTopicFrameRate()
{
    if (event_cb_ != nullptr)
    {
        int sel_index = framte_rate_combo_box_.GetCurSel();
        int frame_rates[] = { 10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30 };
        if (sel_index < sizeof(frame_rates) / sizeof(int))
        {
            event_cb_->OnFpsSelectChanged(frame_rates[sel_index]);
        }
    }
}


void BaseConfigDlg::OnCbnSelchangeComboPublishTopicViewMode()
{
    if (event_cb_ != nullptr)
    {
        int sel_index = view_mode_combo_box_.GetCurSel();
        event_cb_->OnViewModeChaned(sel_index);
    }
}


void BaseConfigDlg::OnBnClickedCheck()
{
    if (event_cb_ != nullptr)
    {
        bool enable_mirror = ((CButton*)GetDlgItem(IDC_CHECK__PUBLISH_TOPIC_MIRROR))->GetCheck();
        event_cb_->OnCaptureCameraMirrorChanged(enable_mirror);
    }
}


void BaseConfigDlg::OnCbnSelchangeComboPublishTopicVideoList()
{
    if (event_cb_ != nullptr)
    {
        cur_vieo_devie_index_ = camera_combo_box_.GetCurSel();
        if (cur_vieo_devie_index_ >= 0 && cur_vieo_devie_index_ < video_device_list_.size())
        {
            event_cb_->OnVideoDeviceSelectChanged(video_device_list_[cur_vieo_devie_index_].device_id);
        }        
    }
}


void BaseConfigDlg::OnCbnSelchangeComboPublishTopicMicList()
{
    if (event_cb_ != nullptr)
    {
        cur_mic_devie_index_ = mic_combo_box_.GetCurSel();
        if (cur_mic_devie_index_ >= 0 && cur_mic_devie_index_ < mic_device_list_.size())
        {
            event_cb_->OnMicDeviceSelectChanged(mic_device_list_[cur_mic_devie_index_].device_id);
        }
    }
}


void BaseConfigDlg::OnCbnSelchangeComboPublishTopicSpeaker()
{
    if (event_cb_ != nullptr)
    {
        cur_speaker_devie_index_ = speaker_combo_box_.GetCurSel();
        if (cur_speaker_devie_index_ >= 0 && cur_speaker_devie_index_ < speaker_device_list_.size())
        {
            event_cb_->OnSpeakerDeviceSelectChanged(speaker_device_list_[cur_speaker_devie_index_].device_id);
        }
    }
}


void BaseConfigDlg::OnBnClickedCheckActivateaudiopublishstream()
{
	// TODO: 在此添加控件通知处理程序代码
	if (event_cb_ != nullptr)
	{
		bool enable_mirror = ((CButton*)GetDlgItem(IDC_CHECK_ActivateAudioPublishStream))->GetCheck();
		event_cb_->OnActivateAudioPublishStreamChanged(enable_mirror);
	}
}


void BaseConfigDlg::OnBnClickedCheckActivatevideopublishstream()
{
	// TODO: 在此添加控件通知处理程序代码
	if (event_cb_ != nullptr)
	{
		bool enable_mirror = ((CButton*)GetDlgItem(IDC_CHECK_ActivateVideoPublishStream))->GetCheck();
		event_cb_->OnActivateVideoPublishStreamChanged(enable_mirror);
	}
}
