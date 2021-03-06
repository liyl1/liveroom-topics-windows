
// ExternalVideoFilterDlg.cpp: 实现文件
//

#include "stdafx.h"

#include "ExternalVideoFilterDlg.h"
#include "afxdialogex.h"


#include "ExternalVideoFilter/ExternalVideoFilterUI/resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std::placeholders;

// CExternalVideoFilterDlg 对话框



CExternalVideoFilterDlg::CExternalVideoFilterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXTERNALVIDEOFILTER_DIALOG, pParent)
{
}

CExternalVideoFilterDlg * CExternalVideoFilterDlg::CreateDlgInstance(CWnd * pParent)
{
    CExternalVideoFilterDlg * p = new CExternalVideoFilterDlg(pParent);
    p->Create(IDD_EXTERNALVIDEOFILTER_DIALOG, pParent);
    return p;
}

void CExternalVideoFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExternalVideoFilterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_MESSAGE(UI_CALLBACK_MSG, &CExternalVideoFilterDlg::OnUICallbackMsg)
    ON_BN_CLICKED(IDC_BUTTON_EXTERNAL_FILTER_PUBLISH, &CExternalVideoFilterDlg::OnBnClickedButtonExternalFilterPublish)
    ON_BN_CLICKED(IDC_CHECK_VIDEO_EXTERNAL_FILTER_ENABLE_BEAUTY, &CExternalVideoFilterDlg::OnBnClickedCheckVideoExternalFilterEnableBeauty)
    ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CExternalVideoFilterDlg 消息处理程序

BOOL CExternalVideoFilterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 在此添加额外的初始化代码

    ((CButton*)GetDlgItem(IDC_CHECK_VIDEO_EXTERNAL_FILTER_ENABLE_BEAUTY))->SetCheck(true);

    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_EXTERNAL_VIDEO_FILTER_BEAUTY_LEVEL))->SetRangeMax(9);
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_EXTERNAL_VIDEO_FILTER_BEAUTY_LEVEL))->SetRangeMin(0);
    ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_EXTERNAL_VIDEO_FILTER_BEAUTY_LEVEL))->SetPos(5);
    

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExternalVideoFilterDlg::OnPaint()
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


void CExternalVideoFilterDlg::OnStatusUpdate(std::string status)
{
    PostUIData * pdata = CreateUIData();
    pdata->cb_in_ui_fun = [status, pdata, this]()->void
    {
        GetDlgItem(IDC_STATIC_EXTERNAL_VIDEO_FILTER_STATUS)->SetWindowText(CString(CStringA(status.c_str())));

        if (status == "LoginOk")
        {
            // 登录成功后开始预览
            helper_.StartPreview(GetDlgItem(IDC_STATIC_EXTERNAL_FILTER_LOCAL_VIDEO)->GetSafeHwnd());
            // 开始推流
            helper_.StartPublishing();
        }else if (status == "Publishing")
        {
            helper_.StartPlaying(GetDlgItem(IDC_STATIC_EXTERNAL_FILTER_REMOTE_VIDEO)->GetSafeHwnd());
        }

        DestroyUIData(pdata);
    };

    PostMsgDataToUI(pdata);
}

void CExternalVideoFilterDlg::OnBnClickedButtonExternalFilterPublish()
{
    // 设置状态函数回调
    helper_.SetPublishStateObserver(std::bind(&CExternalVideoFilterDlg::OnStatusUpdate, this, _1));

    demo_.EnableVideoFilter(true);
    helper_.LoginRoom();

}

void CExternalVideoFilterDlg::OnBnClickedCheckVideoExternalFilterEnableBeauty()
{
    bool enable = ((CButton*)GetDlgItem(IDC_CHECK_VIDEO_EXTERNAL_FILTER_ENABLE_BEAUTY))->GetCheck();
    demo_.EnableBeauty(enable);
}

void CExternalVideoFilterDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    if (pScrollBar != NULL)
    {
        CSliderCtrl* pSlider = (CSliderCtrl*)pScrollBar;
        // 根据来判断是哪一个CSliderCtrl
        if (pSlider->GetDlgCtrlID() == IDC_SLIDER_EXTERNAL_VIDEO_FILTER_BEAUTY_LEVEL)
        {
            int beauty_level = ((CSliderCtrl*)GetDlgItem(IDC_SLIDER_EXTERNAL_VIDEO_FILTER_BEAUTY_LEVEL))->GetPos();
            demo_.UpdateBeautyLevel(beauty_level);
        }
    }
}

afx_msg LRESULT CExternalVideoFilterDlg::OnUICallbackMsg(WPARAM wParam, LPARAM lParam)
{
    PostUIData * pdata = (PostUIData *)wParam;
    if (pdata != nullptr && pdata->cb_in_ui_fun)
    {
        pdata->cb_in_ui_fun();
    }
    return 0;
}

