
// MediaSideInfoDlg.cpp: 实现文件
//

#include "stdafx.h"

#include "MediaSideInfoDlg.h"
#include "afxdialogex.h"

#include "MediaSideInfo/MediaSideInfoUI/resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMediaSideInfoDlg 对话框


CMediaSideInfoDlg * CMediaSideInfoDlg::CreateDlgInstance(CWnd * pParent)
{
    CMediaSideInfoDlg * p = new CMediaSideInfoDlg(pParent);
    p->Create(IDD_MEDIASIDEINFO_DIALOG, pParent);
    return p;
}

CMediaSideInfoDlg::CMediaSideInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MEDIASIDEINFO_DIALOG, pParent)
    , login_status_str_(_T(""))
    , is_only_audio_(FALSE)
    , is_custom_packet_(FALSE)
    , send_side_info_str_(_T(""))
    , check_result_str_(_T(""))
{

}


void CMediaSideInfoDlg::LoginRoom()
{
    std::vector<unsigned int> control_id_list;
    control_id_list.push_back(IDC_ONLY_AUDIO_CHECK);
    control_id_list.push_back(IDC_CUSTOM_PACKET_CHECK);
    control_id_list.push_back(IDC_START_PUBLISH_BTN);
    control_id_list.push_back(IDC_SEND_SIDE_INFO_BTN);
    control_id_list.push_back(IDC_CHECK_SIDE_INFO_BTN);

    for (auto control_id : control_id_list)
    {
        GetDlgItem(control_id)->EnableWindow(FALSE);
    }


    demo_helper_.status_cb_ = std::bind(&CMediaSideInfoDlg::OnStatusUpdate, this, std::placeholders::_1);
    demo_helper_.LoginRoom();
    demo_.SetMediaSideInfoCallBack(std::bind(&CMediaSideInfoDlg::OnRecvMediaSideInfo, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}


void CMediaSideInfoDlg::OnStatusUpdate(MediaSideInfoStatus status)
{
    typedef struct UIDataStruct
    {
        MediaSideInfoStatus s;
    } UIDataStruct;

    UIDataStruct ui_data;
    ui_data.s = status;

    PostUIData * pdata = CreateUIData();
    pdata->cb_in_ui_fun = [ui_data, pdata,this]()->void
    {

        string status_str = demo_helper_.DescOfStatus(ui_data.s);
        login_status_str_ = CStringA(status_str.c_str());

        UpdateData(FALSE);
        if (login_status_str_ == "LoginOk")
        {
            std::vector<unsigned int> control_id_list;
            control_id_list.push_back(IDC_ONLY_AUDIO_CHECK);
            control_id_list.push_back(IDC_CUSTOM_PACKET_CHECK);
            control_id_list.push_back(IDC_START_PUBLISH_BTN);
            //control_id_list.push_back(IDC_SEND_SIDE_INFO_BTN);
            //control_id_list.push_back(IDC_CHECK_SIDE_INFO_BTN);

            for (auto control_id : control_id_list)
            {
                GetDlgItem(control_id)->EnableWindow(TRUE);
            }
        }else if (login_status_str_ == "Ready")
        {
            std::vector<unsigned int> control_id_list;
            control_id_list.push_back(IDC_ONLY_AUDIO_CHECK);
            control_id_list.push_back(IDC_CUSTOM_PACKET_CHECK);
            control_id_list.push_back(IDC_START_PUBLISH_BTN);
            //control_id_list.push_back(IDC_SEND_SIDE_INFO_BTN);
            //control_id_list.push_back(IDC_CHECK_SIDE_INFO_BTN);

            for (auto control_id : control_id_list)
            {
                GetDlgItem(control_id)->EnableWindow(FALSE);
            }

            control_id_list.clear();
            control_id_list.push_back(IDC_SEND_SIDE_INFO_BTN);
            control_id_list.push_back(IDC_CHECK_SIDE_INFO_BTN);

            for (auto control_id : control_id_list)
            {
                GetDlgItem(control_id)->EnableWindow(TRUE);
            }
        }
        else {
            std::vector<unsigned int> control_id_list;
            control_id_list.push_back(IDC_ONLY_AUDIO_CHECK);
            control_id_list.push_back(IDC_CUSTOM_PACKET_CHECK);
            control_id_list.push_back(IDC_START_PUBLISH_BTN);
            control_id_list.push_back(IDC_SEND_SIDE_INFO_BTN);
            control_id_list.push_back(IDC_CHECK_SIDE_INFO_BTN);

            for (auto control_id : control_id_list)
            {
                GetDlgItem(control_id)->EnableWindow(FALSE);
            }
        }


        DestroyUIData(pdata);
    };


    PostMsgDataToUI(pdata);
}

void CMediaSideInfoDlg::OnRecvMediaSideInfo(uint8_t * data, int len, string stream_id)
{
    typedef struct UIDataStruct
    {
        string str;
        string stream_id;

    } UIDataStruct;

    UIDataStruct ui_data;
    ui_data.str = string((char *)data, len);
    ui_data.stream_id = stream_id;

    PostUIData * pdata = CreateUIData();
    pdata->cb_in_ui_fun = [ui_data, pdata,this]()->void
    {
        string recv_data = ui_data.str;
        demo_helper_.AddRecvMsg(recv_data);

        recv_list_.AddString(CString(CStringA(recv_data.c_str())));

        DestroyUIData(pdata);
    };

    PostMsgDataToUI(pdata);
}

void CMediaSideInfoDlg::OnOK()
{
    OnBnClickedSendSideInfoBtn();
}

void CMediaSideInfoDlg::OnCancel()
{
}

void CMediaSideInfoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_CHECK_RESULT, check_result_str_);
    DDX_Text(pDX, IDC_STATUS, login_status_str_);
    DDX_Check(pDX, IDC_ONLY_AUDIO_CHECK, is_only_audio_);
    DDX_Check(pDX, IDC_CUSTOM_PACKET_CHECK, is_custom_packet_);
    DDX_Control(pDX, IDC_SEND_SIDE_INFO_LIST, send_list_);
    DDX_Control(pDX, IDC_RECV_SIDE_INFO_LIST, recv_list_);
    DDX_Text(pDX, IDC_SIDE_INFO_EDIT, send_side_info_str_);
}

BEGIN_MESSAGE_MAP(CMediaSideInfoDlg, CDialogEx)
    ON_MESSAGE(UI_CALLBACK_MSG, &CMediaSideInfoDlg::OnUICallbackMsg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_START_PUBLISH_BTN, &CMediaSideInfoDlg::OnBnClickedStartPublishBtn)
    ON_BN_CLICKED(IDC_CHECK_SIDE_INFO_BTN, &CMediaSideInfoDlg::OnBnClickedCheckSideInfoBtn)
    ON_BN_CLICKED(IDC_SEND_SIDE_INFO_BTN, &CMediaSideInfoDlg::OnBnClickedSendSideInfoBtn)
END_MESSAGE_MAP()


// CMediaSideInfoDlg 消息处理程序

BOOL CMediaSideInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

    std::vector<unsigned int> disable_control_id_list;
    disable_control_id_list.push_back(IDC_ONLY_AUDIO_CHECK);
    disable_control_id_list.push_back(IDC_CUSTOM_PACKET_CHECK);
    disable_control_id_list.push_back(IDC_START_PUBLISH_BTN);
    disable_control_id_list.push_back(IDC_SEND_SIDE_INFO_BTN);
    disable_control_id_list.push_back(IDC_CHECK_SIDE_INFO_BTN);

    for (auto control_id : disable_control_id_list)
    {
        GetDlgItem(control_id)->EnableWindow(FALSE);
    }

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMediaSideInfoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void CMediaSideInfoDlg::OnBnClickedStartPublishBtn()
{
    UpdateData(TRUE);
    ZGMediaSideInfoDemoConfig config;
    config.only_audio_publish = is_only_audio_;
    config.custom_packet = is_custom_packet_;

    demo_.InitSideInfoConfig(config);
    demo_.ActivateMediaSideInfoForPublishChannel();

    demo_helper_.InitVideoView(GetDlgItem(IDC_LOCAL_VIDEO)->GetSafeHwnd(), GetDlgItem(IDC_REMOTE_VIDEO)->GetSafeHwnd());
    demo_helper_.PublishAndPlayWithConfig(config);
}


void CMediaSideInfoDlg::OnBnClickedSendSideInfoBtn()
{
    if (have_checked_)
    {
        send_list_.ResetContent();
        recv_list_.ResetContent();
        have_checked_ = false;

        check_result_str_ = "";
        UpdateData(FALSE);
    }

    UpdateData(TRUE);
    send_list_.AddString(send_side_info_str_);
    string str_to_send = CStringA(send_side_info_str_.GetBuffer()).GetBuffer();
    demo_helper_.AddSentMsg(str_to_send);
    demo_.SendMediaSideInfo((unsigned char *)str_to_send.c_str(), str_to_send.length());
}


void CMediaSideInfoDlg::OnBnClickedCheckSideInfoBtn()
{
    have_checked_ = true;
    string check_ret = demo_helper_.CheckSentRecvMsgs();
    check_result_str_ = CStringA(check_ret.c_str());
    UpdateData(FALSE);
}

afx_msg LRESULT CMediaSideInfoDlg::OnUICallbackMsg(WPARAM wParam, LPARAM lParam)
{
    PostUIData * pdata = (PostUIData *)wParam;
    if (pdata != nullptr && pdata->cb_in_ui_fun)
    {
        pdata->cb_in_ui_fun();
    }
    return 0;
}


