// PlayBaseConfigDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "PlayBaseConfigDlg.h"
#include "afxdialogex.h"

#include "Play/PlayUI/resource.h"

// PlayBaseConfigDlg 对话框

IMPLEMENT_DYNAMIC(PlayBaseConfigDlg, CDialogEx)

PlayBaseConfigDlg::PlayBaseConfigDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PLAY_BASE_FUN_DLG, pParent)
{

}

PlayBaseConfigDlg::~PlayBaseConfigDlg()
{
}

void PlayBaseConfigDlg::InitDefaultConfig()
{
    view_mode_combo_box_.ResetContent();
    view_mode_combo_box_.AddString(_T("等比缩放, 可能有黑边"));
    view_mode_combo_box_.AddString(_T("等比缩放填充整View"));
    view_mode_combo_box_.AddString(_T("填充整个View"));
    view_mode_combo_box_.SetCurSel(0);

    ((CButton*)GetDlgItem(IDC_CHECK_PLAY_TOPIC_MUTE))->SetCheck(FALSE);

    play_volume_slider_.SetRangeMin(0);
    play_volume_slider_.SetRangeMax(100);
    play_volume_slider_.SetPos(100);

    CString str_cur_play_volume;

    str_cur_play_volume.Format(_T("%d"), play_volume_slider_.GetPos());

    GetDlgItem(IDC_STATIC_PLAY_VOLUME)->SetWindowText(str_cur_play_volume);

}

void PlayBaseConfigDlg::SetEventCallBack(PlayBaseConfigDlgEvent * cb)
{
    event_cb_ = cb;
}

BOOL PlayBaseConfigDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    InitDefaultConfig();

    return TRUE;
}

void PlayBaseConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_PLAY_TOPIC_VIEW_MODE, view_mode_combo_box_);
    DDX_Control(pDX, IDC_PLAY_VOLUME_SLIDER, play_volume_slider_);
}


void PlayBaseConfigDlg::OnOK()
{
}

void PlayBaseConfigDlg::OnCancel()
{
}

BEGIN_MESSAGE_MAP(PlayBaseConfigDlg, CDialogEx)
    ON_BN_CLICKED(IDC_CHECK_PLAY_TOPIC_MUTE, &PlayBaseConfigDlg::OnBnClickedCheckPlayTopicMute)
    ON_CBN_SELCHANGE(IDC_COMBO_PLAY_TOPIC_VIEW_MODE, &PlayBaseConfigDlg::OnCbnSelchangeComboPlayTopicViewMode)
	ON_BN_CLICKED(IDC_CHECK_MUTE_PLAY_VIDEO_STREAM, &PlayBaseConfigDlg::OnBnClickedCheckMutePlayVideoStream)
	ON_BN_CLICKED(IDC_CHECK_MUTE_PLAY_AUDIO_STREAM, &PlayBaseConfigDlg::OnBnClickedCheckMutePlayAudioStream)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


void PlayBaseConfigDlg::OnBnClickedCheckPlayTopicMute()
{
    if (event_cb_ != nullptr)
    {
        bool enable_mute = ((CButton*)GetDlgItem(IDC_CHECK_PLAY_TOPIC_MUTE))->GetCheck();
        event_cb_->OnPlayMuted(enable_mute);
    }
}


void PlayBaseConfigDlg::OnCbnSelchangeComboPlayTopicViewMode()
{
    if (event_cb_ != nullptr)
    {
        int sel_index = view_mode_combo_box_.GetCurSel();
        event_cb_->OnViewModeChaned(sel_index);
    }
}

void PlayBaseConfigDlg::OnBnClickedCheckMutePlayAudioStream()
{
	// TODO: 在此添加控件通知处理程序代码
	if (event_cb_ != nullptr)
	{
		bool mute = ((CButton*)GetDlgItem(IDC_CHECK_MUTE_PLAY_AUDIO_STREAM))->GetCheck();
		event_cb_->OnActivateAudioPlayStreamChanged("s512", !mute);
	}
}

void PlayBaseConfigDlg::OnBnClickedCheckMutePlayVideoStream()
{
	// TODO: 在此添加控件通知处理程序代码
	if (event_cb_ != nullptr)
	{
		bool mute = ((CButton*)GetDlgItem(IDC_CHECK_MUTE_PLAY_VIDEO_STREAM))->GetCheck();
		event_cb_->OnActivateVideoPlayStreamChanged("s512", !mute);
	}
}

void PlayBaseConfigDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CString str_cur_play_volume;

	int set_play_vol = 0;

	set_play_vol = play_volume_slider_.GetPos();

	str_cur_play_volume.Format(_T("%d"), set_play_vol);

	GetDlgItem(IDC_STATIC_PLAY_VOLUME)->SetWindowText(str_cur_play_volume);

	if (event_cb_ != nullptr)
	{
		event_cb_->OnSetPlayVolume(set_play_vol);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
