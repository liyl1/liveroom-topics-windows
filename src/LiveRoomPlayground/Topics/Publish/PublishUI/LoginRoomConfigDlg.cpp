// LoginRoomConfigDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ZegoLiveRoomTopics.h"
#include "LoginRoomConfigDlg.h"
#include "afxdialogex.h"

#include "Publish/PublishUI/resource.h"

// LoginRoomConfigDlg 对话框

IMPLEMENT_DYNAMIC(LoginRoomConfigDlg, CDialogEx)

LoginRoomConfigDlg::LoginRoomConfigDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGINROOM_CONFIG_DLG, pParent)
{

}

LoginRoomConfigDlg::~LoginRoomConfigDlg()
{
}

void LoginRoomConfigDlg::SetEventCallBack(LoginRoomConfigDlgEvent * cb)
{
    event_cb_ = cb;
}


LoginRomConfig LoginRoomConfigDlg::GetConfig()
{
    return login_room_config_;
}

void LoginRoomConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_PUBLISH_TOPIC_ROOMID, room_id_);
}


void LoginRoomConfigDlg::OnOK()
{
}

void LoginRoomConfigDlg::OnCancel()
{
}

BEGIN_MESSAGE_MAP(LoginRoomConfigDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_PUBLISH_TOPIC_LOGINROOM, &LoginRoomConfigDlg::OnBnClickedButtonPublishTopicLoginroom)
END_MESSAGE_MAP()


// LoginRoomConfigDlg 消息处理程序


void LoginRoomConfigDlg::OnBnClickedButtonPublishTopicLoginroom()
{
    UpdateData(TRUE);

    if (room_id_ == _T(""))
    {
        MessageBox(_T("请输入roomID"));
        return;
    }

    login_room_config_.room_id = CStringA(room_id_).GetBuffer();
    login_room_config_.room_role = ZEGO::COMMON::Anchor;

    if (event_cb_ != nullptr)
    {
        event_cb_->OnLoginRoomButtonEvent();
    }
}
