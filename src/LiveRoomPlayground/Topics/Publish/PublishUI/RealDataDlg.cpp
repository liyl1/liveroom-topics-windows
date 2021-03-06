// RealDataDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ZegoLiveRoomTopics.h"
#include "RealDataDlg.h"
#include "afxdialogex.h"

#include "Publish/PublishUI/resource.h"


// RealDataDlg 对话框

IMPLEMENT_DYNAMIC(RealDataDlg, CDialogEx)

RealDataDlg::RealDataDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REAL_DATA_DLG, pParent)
{

}

RealDataDlg::~RealDataDlg()
{
}

void RealDataDlg::SetEventCallBack(RealDataDlgEvent * cb)
{
    event_cb_ = cb;
}

void RealDataDlg::UpdateRealData(const RealDataInfo & info)
{
    PostUIData * pdata = CreateUIData();
    pdata->cb_in_ui_fun = [info, pdata, this]()->void
    {
        CString str;
        str = CString(CStringA(info.room_id.c_str()));
        ((CStatic*)GetDlgItem(IDC_STATIC_PUBLISH_ROOMID_TEXT))->SetWindowText(str);

        str = CString(CStringA(info.stream_id.c_str()));
        ((CStatic*)GetDlgItem(IDC_STATIC_PUBLISH_STREAMID_TEXT))->SetWindowText(str);

        str.Format(_T("%dx%d"), info.resolution_w, info.resolution_h);
        ((CStatic*)GetDlgItem(IDC_STATIC_RESOLUTION_TEXT))->SetWindowText(str);

        str.Format(_T("%.4f"), info.bit_rate_bps_per_second);
        ((CStatic*)GetDlgItem(IDC_STATIC_PUBLISH_BITRATE_TEXT))->SetWindowText(str);

        str.Format(_T("%.4f"), info.frame_rate);
        ((CStatic*)GetDlgItem(IDC_STATIC_PUBLISH_FRAMERATE_TEXT))->SetWindowText(str);


        DestroyUIData(pdata);
    };

    PostMsgDataToUI(pdata);
}

void RealDataDlg::InitShowRealData()
{
    CString str = L"";
    ((CStatic*)GetDlgItem(IDC_STATIC_PUBLISH_ROOMID_TEXT))->SetWindowText(str);

    ((CStatic*)GetDlgItem(IDC_STATIC_PUBLISH_STREAMID_TEXT))->SetWindowText(str);

    ((CStatic*)GetDlgItem(IDC_STATIC_RESOLUTION_TEXT))->SetWindowText(str);

    ((CStatic*)GetDlgItem(IDC_STATIC_PUBLISH_BITRATE_TEXT))->SetWindowText(str);

    ((CStatic*)GetDlgItem(IDC_STATIC_PUBLISH_FRAMERATE_TEXT))->SetWindowText(str);

    ((CButton*)GetDlgItem(IDC_BUTTON_PUBLISH_TOPIC_BASE_FUN2))->SetWindowText(_T("常用功能>>"));

    show_base_fun_ = false;
}

void RealDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RealDataDlg, CDialogEx)
    ON_MESSAGE(UI_CALLBACK_MSG, &RealDataDlg::OnUICallbackMsg)
    ON_BN_CLICKED(IDC_BUTTON_PUBLISH_TOPIC_BASE_FUN2, &RealDataDlg::OnBnClickedButtonPublishTopicBaseFun2)
END_MESSAGE_MAP()


// RealDataDlg 消息处理程序


void RealDataDlg::OnBnClickedButtonPublishTopicBaseFun2()
{
    if (!show_base_fun_)
    {
        ((CButton*)GetDlgItem(IDC_BUTTON_PUBLISH_TOPIC_BASE_FUN2))->SetWindowText(_T("常用功能<<"));
        show_base_fun_ = true;
    }
    else {
        ((CButton*)GetDlgItem(IDC_BUTTON_PUBLISH_TOPIC_BASE_FUN2))->SetWindowText(_T("常用功能>>"));
        show_base_fun_ = false;
    }

    if (event_cb_ != nullptr)
    {
        event_cb_->OnRealDataBaseFunctionButtonEvent(show_base_fun_);
    }
}

afx_msg LRESULT RealDataDlg::OnUICallbackMsg(WPARAM wParam, LPARAM lParam)
{
    PostUIData * pdata = (PostUIData *)wParam;
    if (pdata != nullptr && pdata->cb_in_ui_fun)
    {
        pdata->cb_in_ui_fun();
    }
    return 0;
}

void RealDataDlg::OnOK()
{
}

void RealDataDlg::OnCancel()
{
}
