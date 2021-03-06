// PlayLoginRoomConfigDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "PlayLoginRoomConfigDlg.h"
#include "afxdialogex.h"

#include "Play/PlayUI/resource.h"

// PlayLoginRoomConfigDlg 对话框

IMPLEMENT_DYNAMIC(PlayLoginRoomConfigDlg, CDialogEx)

PlayLoginRoomConfigDlg::PlayLoginRoomConfigDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PLAY_LOGINROOM_CONFIG_DLG, pParent)
{
    room_id_ = "";
}

PlayLoginRoomConfigDlg::~PlayLoginRoomConfigDlg()
{
}

void PlayLoginRoomConfigDlg::SetEventCallBack(PlayLoginRoomConfigDlgEvent * cb)
{
    event_cb_ = cb;
}

PlayLoginRomConfig PlayLoginRoomConfigDlg::GetConfig()
{
    return login_room_config_;
}


void PlayLoginRoomConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_PLAY_TOPIC_ROOMID, room_id_);
}


BEGIN_MESSAGE_MAP(PlayLoginRoomConfigDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_PLAY_TOPIC_LOGINROOM, &PlayLoginRoomConfigDlg::OnBnClickedButtonPlayTopicLoginroom)
END_MESSAGE_MAP()


// PlayLoginRoomConfigDlg 消息处理程序


void PlayLoginRoomConfigDlg::OnBnClickedButtonPlayTopicLoginroom()
{
    UpdateData(TRUE);

    if (room_id_ == _T(""))
    {
        MessageBox(_T("请输入roomID"));
        return;
    }

    login_room_config_.room_id = CStringA(room_id_).GetBuffer();
    login_room_config_.room_role = ZEGO::COMMON::Audience;

    if (event_cb_ != nullptr)
    {
        event_cb_->OnLoginRoomButtonEvent();
    }
}
