// PlayRealDataDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "PlayRealDataDlg.h"
#include "afxdialogex.h"

#include "Play/PlayUI/resource.h"

// PlayRealDataDlg 对话框

IMPLEMENT_DYNAMIC(PlayRealDataDlg, CDialogEx)

PlayRealDataDlg::PlayRealDataDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PLAY_REAL_DATA_DLG, pParent)
{

}

PlayRealDataDlg::~PlayRealDataDlg()
{
}

void PlayRealDataDlg::InitShowRealData()
{
    CString str = L"";
    ((CStatic*)GetDlgItem(IDC_STATIC_PLAY_ROOMID_TEXT))->SetWindowText(str);

    ((CStatic*)GetDlgItem(IDC_STATIC_PLAY_STREAMID_TEXT))->SetWindowText(str);

    ((CStatic*)GetDlgItem(IDC_STATIC_PLAY_RESOLUTION_TEXT))->SetWindowText(str);

    ((CStatic*)GetDlgItem(IDC_STATIC_PLAY_BITRATE_TEXT))->SetWindowText(str);

    ((CStatic*)GetDlgItem(IDC_STATIC_PLAY_FRAMERATE_TEXT))->SetWindowText(str);

    ((CButton*)GetDlgItem(IDC_BUTTON_PLAY_TOPIC_BASE_FUN2))->SetWindowText(_T("常用功能>>"));

    show_base_fun_ = false;
}

void PlayRealDataDlg::UpdateRealData(const PlayRealDataInfo & info)
{
    PostUIData * pdata = CreateUIData();
    pdata->cb_in_ui_fun = [info, pdata, this]()->void
    {
        CString str;
        str = CString(CStringA(info.room_id.c_str()));
        ((CStatic*)GetDlgItem(IDC_STATIC_PLAY_ROOMID_TEXT))->SetWindowText(str);

        str = CString(CStringA(info.stream_id.c_str()));
        ((CStatic*)GetDlgItem(IDC_STATIC_PLAY_STREAMID_TEXT))->SetWindowText(str);

        str.Format(_T("%dx%d"), info.resolution_w, info.resolution_h);
        ((CStatic*)GetDlgItem(IDC_STATIC_PLAY_RESOLUTION_TEXT))->SetWindowText(str);

        str.Format(_T("%.4f"), info.bit_rate_bps_per_second);
        ((CStatic*)GetDlgItem(IDC_STATIC_PLAY_BITRATE_TEXT))->SetWindowText(str);

        str.Format(_T("%.4f"), info.frame_rate);
        ((CStatic*)GetDlgItem(IDC_STATIC_PLAY_FRAMERATE_TEXT))->SetWindowText(str);


        DestroyUIData(pdata);
    };

    PostMsgDataToUI(pdata);
}


void PlayRealDataDlg::SetEventCallBack(PlayRealDataDlgEvent * cb)
{
    event_cb_ = cb;
}

void PlayRealDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


void PlayRealDataDlg::OnOK()
{
}

void PlayRealDataDlg::OnCancel()
{
}

BEGIN_MESSAGE_MAP(PlayRealDataDlg, CDialogEx)
    ON_MESSAGE(UI_CALLBACK_MSG, &PlayRealDataDlg::OnUICallbackMsg)
    ON_BN_CLICKED(IDC_BUTTON_PLAY_TOPIC_BASE_FUN2, &PlayRealDataDlg::OnBnClickedButtonPlayTopicBaseFun2)
END_MESSAGE_MAP()


// PlayRealDataDlg 消息处理程序


void PlayRealDataDlg::OnBnClickedButtonPlayTopicBaseFun2()
{
    if (!show_base_fun_)
    {
        ((CButton*)GetDlgItem(IDC_BUTTON_PLAY_TOPIC_BASE_FUN2))->SetWindowText(_T("常用功能<<"));
        show_base_fun_ = true;
    }
    else {
        ((CButton*)GetDlgItem(IDC_BUTTON_PLAY_TOPIC_BASE_FUN2))->SetWindowText(_T("常用功能>>"));
        show_base_fun_ = false;
    }

    if (event_cb_ != nullptr)
    {
        event_cb_->OnRealDataBaseFunctionButtonEvent(show_base_fun_);
    }
}

afx_msg LRESULT PlayRealDataDlg::OnUICallbackMsg(WPARAM wParam, LPARAM lParam)
{
    PostUIData * pdata = (PostUIData *)wParam;
    if (pdata != nullptr && pdata->cb_in_ui_fun)
    {
        pdata->cb_in_ui_fun();
    }
    return 0;
}