
// PublishDlg.cpp: 实现文件
//

#include "stdafx.h"

#include "PublishDlg.h"
#include "afxdialogex.h"

#include "AppSupport/ZGConfigHelper.h"
#include "Publish/PublishUI/Resource.h"
#include "LiveRoom-Publisher.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPublishDlg 对话框

CPublishDlg * CPublishDlg::CreateDlgInstance(CWnd * pParent)
{
    CPublishDlg * p = new CPublishDlg(pParent);
    p->Create(IDD_PUBLISH_DIALOG, pParent);
    return p;
}

CPublishDlg::CPublishDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PUBLISH_DIALOG, pParent),
    init_sdk_config_dlg_(this),
    login_room_config_dlg_(this),
    publish_config_dlg_(this)
{
}

void CPublishDlg::InitDlg()
{
    log_list_.ResetContent();
    SendDlgItemMessage(IDC_LIST_PUBLISH_TOPIC_LOG, LB_SETHORIZONTALEXTENT, (WPARAM)0, 0);
    HideAllConfigDlg();

    CRect rect;
    GetDlgItem(IDC_STATIC_PUBLISH_TOPIC_CONFIG_PANNEL)->GetWindowRect(rect);
    ScreenToClient(&rect);
    init_sdk_config_dlg_.MoveWindow(rect.left, rect.top, rect.Width(), rect.Height());
    init_sdk_config_dlg_.ShowWindow(SW_SHOW);

    publish_demo_.SetViewLogCallBack(this);
    ZGConfigHelperInstance()->SetViewLogCallBack(this);

}

void CPublishDlg::HideAllConfigDlg()
{
    init_sdk_config_dlg_.ShowWindow(SW_HIDE);
    login_room_config_dlg_.ShowWindow(SW_HIDE);
    publish_config_dlg_.ShowWindow(SW_HIDE);
    base_config_dlg_.ShowWindow(SW_HIDE);
    real_data_dlg_.ShowWindow(SW_HIDE);
}

void CPublishDlg::OnOK()
{
}

void CPublishDlg::OnCancel()
{
}

void CPublishDlg::OnPublishDemoStatus(ZGPublishStatus status)
{

    PostUIData * pdata = CreateUIData();
    pdata->cb_in_ui_fun = [status, pdata, this]()->void
    {
        switch (status)
        {
        case kZGStatus_Init_SDK_OK:
            AddLogToList("初始化sdk成功");
            AddLogToList("开始本地预览");
            publish_demo_.StartPreview(GetDlgItem(IDC_STATIC_PUBLISH_TOPIC_VIDEO)->GetSafeHwnd());
            ShowLoginRoomConfig();
            break;
        case kZGStatus_Login_OK:
            AddLogToList("登录房间成功");
            ShowPublishConfig();

            break;
        case kZGStatus_Publishing:
            AddLogToList("推流成功");
            ShowRealDataDlg();
            break;
        default:
            break;
        }


        DestroyUIData(pdata);
    };

    PostMsgDataToUI(pdata);
}

void CPublishDlg::OnPublishRealDataRefresh(const RealDataInfo & real_data)
{
    real_data_dlg_.UpdateRealData(real_data);
}

void CPublishDlg::ShowLoginRoomConfig()
{
    init_sdk_config_dlg_.ShowWindow(SW_HIDE);

    CRect rect;
    GetDlgItem(IDC_STATIC_PUBLISH_TOPIC_CONFIG_PANNEL)->GetWindowRect(rect);
    ScreenToClient(&rect);
    login_room_config_dlg_.MoveWindow(rect.left, rect.top, rect.Width(), rect.Height());
    login_room_config_dlg_.ShowWindow(SW_SHOW);
}

void CPublishDlg::ShowPublishConfig()
{
    login_room_config_dlg_.ShowWindow(SW_HIDE);

    CRect rect;
    GetDlgItem(IDC_STATIC_PUBLISH_TOPIC_CONFIG_PANNEL)->GetWindowRect(rect);
    ScreenToClient(&rect);
    publish_config_dlg_.MoveWindow(rect.left, rect.top, rect.Width()/2, rect.Height());
    publish_config_dlg_.ShowWindow(SW_SHOW);
}

void CPublishDlg::ShowRealDataDlg()
{
    publish_config_dlg_.ShowWindow(SW_HIDE);
    base_config_dlg_.ShowWindow(SW_HIDE);

    CRect rect;
    GetDlgItem(IDC_STATIC_PUBLISH_TOPIC_CONFIG_PANNEL)->GetWindowRect(rect);
    ScreenToClient(&rect);
    real_data_dlg_.MoveWindow(rect.left, rect.top, rect.Width() / 2, rect.Height());
    real_data_dlg_.ShowWindow(SW_SHOW);
}

void CPublishDlg::ShowBaseConfig()
{
    publish_config_dlg_.ShowWindow(SW_HIDE);

    CRect rect;
    GetDlgItem(IDC_STATIC_PUBLISH_TOPIC_CONFIG_PANNEL)->GetWindowRect(rect);
    ScreenToClient(&rect);
    base_config_dlg_.MoveWindow(rect.left, rect.top, rect.Width(), rect.Height());
    base_config_dlg_.ShowWindow(SW_SHOW);
}

void CPublishDlg::SetHScroll()
{
    CDC* dc = GetDC();
    SIZE s;
    int index;
    CString str;
    long temp;
    for (index = 0; index < log_list_.GetCount(); index++)
    {
        log_list_.GetText(index, str);
        s = dc->GetTextExtent(str, str.GetLength() + 1);   
        // 获取字符串的像素大小
        // 如果新的字符串宽度大于先前的水平滚动条宽度，则重新设置滚动条宽度
        // 得到滚动条的宽度
        temp = (long)SendDlgItemMessage(IDC_LIST_PUBLISH_TOPIC_LOG, LB_GETHORIZONTALEXTENT, 0, 0); 
        if (s.cx > temp)
        {
            SendDlgItemMessage(IDC_LIST_PUBLISH_TOPIC_LOG, LB_SETHORIZONTALEXTENT, (WPARAM)s.cx, 0);
        }
    }
    ReleaseDC(dc);
}

void CPublishDlg::AddLogToList(std::string str_log)
{
    PostUIData * pdata = CreateUIData();
    pdata->cb_in_ui_fun = [str_log, pdata, this]()->void
    {
        CStringA str;
        str.Format("%s", str_log.c_str());
        log_list_.AddString(CString(str));
        SetHScroll();

        DestroyUIData(pdata);
    };

    PostMsgDataToUI(pdata);

}

void CPublishDlg::OnInitSDKButtonEvent()
{
    publish_config_dlg_.InitDlgData();
    real_data_dlg_.InitShowRealData();
    base_config_dlg_.InitDefaultConfig();

    publish_demo_.SetStateUpdateObserver(std::bind(&CPublishDlg::OnPublishDemoStatus,this, std::placeholders::_1));
    publish_demo_.SetRealDataRefreshObserver(std::bind(&CPublishDlg::OnPublishRealDataRefresh, this, std::placeholders::_1));
    
    AddLogToList("开始初始化sdk");
    publish_demo_.InitSDK(init_sdk_config_dlg_.GetConfig());
}

void CPublishDlg::OnLoginRoomButtonEvent()
{
    AddLogToList("开始登录房间");
    publish_demo_.LoginRoom(login_room_config_dlg_.GetConfig());
}

void CPublishDlg::OnPublishButtonEvent()
{   
    AddLogToList("开始推流");
    LIVEROOM::EnableAGC(false);
    publish_demo_.StartPublish(publish_config_dlg_.GetConfig());
}

void CPublishDlg::OnBaseFunctionButtonEvent(bool show)
{
    if (show)
    {
        CRect rect;
        GetDlgItem(IDC_STATIC_PUBLISH_TOPIC_CONFIG_PANNEL)->GetWindowRect(rect);
        ScreenToClient(&rect);
        base_config_dlg_.MoveWindow(rect.left + rect.Width() / 2, rect.top, rect.Width() / 2, rect.Height());
        base_config_dlg_.ShowWindow(SW_SHOW);
    }
    else {
        base_config_dlg_.ShowWindow(SW_HIDE);
    }
}


void CPublishDlg::OnRealDataBaseFunctionButtonEvent(bool show)
{
    if (show)
    {
        CRect rect;
        GetDlgItem(IDC_STATIC_PUBLISH_TOPIC_CONFIG_PANNEL)->GetWindowRect(rect);
        ScreenToClient(&rect);
        base_config_dlg_.MoveWindow(rect.left + rect.Width() / 2, rect.top, rect.Width() / 2, rect.Height());
        base_config_dlg_.ShowWindow(SW_SHOW);
    }
    else {
        base_config_dlg_.ShowWindow(SW_HIDE);
    }
}


void CPublishDlg::OnResolutionSelectChanged(int w, int h)
{
    ZGConfigHelperInstance()->SetPublishResolution(w, h);
}

void CPublishDlg::OnBitRateSelectChaned(int bit_rate)
{
    ZGConfigHelperInstance()->SetVideoBitrate(bit_rate);
}

void CPublishDlg::OnFpsSelectChanged(int fps)
{
    ZGConfigHelperInstance()->SetPublishVideoFps(fps);
}

void CPublishDlg::OnViewModeChaned(int view_mode_index)
{
    ZGConfigHelperInstance()->SetPreviewViewMode((ZEGO::LIVEROOM::ZegoVideoViewMode)view_mode_index);
}

std::string kDevID = "";
void CPublishDlg::OnCaptureCameraMirrorChanged(bool enable_mirror)
{
    ZGConfigHelperInstance()->EnableCaptureMirror(enable_mirror);
}

void CPublishDlg::OnActivateVideoPublishStreamChanged(bool activated)
{
	ZGConfigHelperInstance()->ActivateVideoPublishStream(activated);
}

void CPublishDlg::OnActivateAudioPublishStreamChanged(bool activated)
{
	ZGConfigHelperInstance()->ActivateAudioPublishStream(activated);
}

void CPublishDlg::OnVideoDeviceSelectChanged(std::string device_id)
{
    ZGConfigHelperInstance()->SetVideoDevice(device_id);
}

void CPublishDlg::OnMicDeviceSelectChanged(std::string device_id)
{
    ZGConfigHelperInstance()->SetMicDevice(device_id);
}

void CPublishDlg::PrintToView(const char * log_str)
{
    AddLogToList(log_str);
}

void CPublishDlg::OnSpeakerDeviceSelectChanged(std::string device_id)
{
    ZGConfigHelperInstance()->SetSpeakerDevice(device_id.c_str());
}

void CPublishDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_PUBLISH_TOPIC_LOG, log_list_);
}

BEGIN_MESSAGE_MAP(CPublishDlg, CDialogEx)
    ON_MESSAGE(UI_CALLBACK_MSG, &CPublishDlg::OnUICallbackMsg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_CREATE()
END_MESSAGE_MAP()


// CPublishDlg 消息处理程序

BOOL CPublishDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPublishDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


int CPublishDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDialogEx::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  在此添加您专用的创建代码

    init_sdk_config_dlg_.Create(IDD_INITSDK_CONFIG_DLG, this);
    init_sdk_config_dlg_.SetEventCallBack(this);

    login_room_config_dlg_.Create(IDD_LOGINROOM_CONFIG_DLG, this);
    login_room_config_dlg_.SetEventCallBack(this);

    publish_config_dlg_.Create(IDD_PUBLISH_CONFIG_DLG, this);
    publish_config_dlg_.SetEventCallBack(this);

    base_config_dlg_.Create(IDD_BASE_FUN_DLG, this);
    base_config_dlg_.SetEventCallBack(this);

    real_data_dlg_.Create(IDD_REAL_DATA_DLG, this);
    real_data_dlg_.SetEventCallBack(this);

    return 0;
}

afx_msg LRESULT CPublishDlg::OnUICallbackMsg(WPARAM wParam, LPARAM lParam)
{
    PostUIData * pdata = (PostUIData *)wParam;
    if (pdata != nullptr && pdata->cb_in_ui_fun)
    {
        pdata->cb_in_ui_fun();
    }
    return 0;
}
