// MediaSideInfoPannelDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ZegoLiveRoomTopics.h"
#include "MediaSideInfoPannelDlg.h"
#include "afxdialogex.h"

#include "MediaSideInfo/MediaSideInfoUI/resource.h"

MediaSideInfoPannelDlg * MediaSideInfoPannelDlg::CreateDlgInstance(CWnd * pParent)
{
    MediaSideInfoPannelDlg * p = new MediaSideInfoPannelDlg(pParent);
    p->Create(IDD_MEDIASIDEINFO_PANNEL, pParent);
    return p;
}

// MediaSideInfoPannelDlg 对话框

IMPLEMENT_DYNAMIC(MediaSideInfoPannelDlg, CDialogEx)

MediaSideInfoPannelDlg::MediaSideInfoPannelDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MEDIASIDEINFO_PANNEL, pParent)
{

}

MediaSideInfoPannelDlg::~MediaSideInfoPannelDlg()
{
}

BOOL MediaSideInfoPannelDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    ((CButton*)GetDlgItem(IDC_SENDRECV))->SetCheck(TRUE);

    OnBnClickedSendrecv();

    return TRUE;
}

void MediaSideInfoPannelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MediaSideInfoPannelDlg, CDialogEx)
    ON_BN_CLICKED(IDC_SENDRECV, &MediaSideInfoPannelDlg::OnBnClickedSendrecv)
    ON_BN_CLICKED(IDC_RECV, &MediaSideInfoPannelDlg::OnBnClickedRecv)
END_MESSAGE_MAP()


// MediaSideInfoPannelDlg 消息处理程序


void MediaSideInfoPannelDlg::OnBnClickedSendrecv()
{
    if (media_side_info_dlg_ptr_ == nullptr)
    {
        media_side_info_dlg_ptr_ = CMediaSideInfoDlg::CreateDlgInstance(this);
    }

    CRect rect;
    GetDlgItem(IDC_SIDEINFO_PANNEL)->GetWindowRect(rect);
    ScreenToClient(&rect);
    media_side_info_dlg_ptr_->MoveWindow(rect.left, rect.top, rect.Width(), rect.Height());

    media_side_info_dlg_ptr_->LoginRoom();

    if (media_side_info_play_only_ != nullptr)
    {
        media_side_info_play_only_->ShowWindow(FALSE);
    }
    
    media_side_info_dlg_ptr_->ShowWindow(TRUE);
}


void MediaSideInfoPannelDlg::OnBnClickedRecv()
{

    if (media_side_info_play_only_ == nullptr)
    {
        media_side_info_play_only_ = CMediaSideinfoPlayVideoDlg::CreateDlgInstance(this);
    }

    CRect rect;
    GetDlgItem(IDC_SIDEINFO_PANNEL)->GetWindowRect(rect);
    ScreenToClient(&rect);
    media_side_info_play_only_->MoveWindow(rect.left, rect.top, rect.Width(), rect.Height());

    if (media_side_info_dlg_ptr_ != nullptr)
    {
        media_side_info_dlg_ptr_->ShowWindow(FALSE);
    }
    media_side_info_play_only_->ShowWindow(TRUE);
}
