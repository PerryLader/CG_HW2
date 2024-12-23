#pragma once

class CDynamicSliderDialog : public CDialog
{
    DECLARE_DYNAMIC(CDynamicSliderDialog)

public:
    CDynamicSliderDialog(CString title, float min, float max, float tickWidth, CWnd* pParent = nullptr);   // Constructor
    virtual ~CDynamicSliderDialog();

    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DIALOG1 };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    CSliderCtrl m_sliderCtrl;
    CStatic m_staticMin;
    CStatic m_staticMax;
    float GetSliderPos() const {
        if (m_sliderCtrl.GetSafeHwnd() != NULL) {
            int pos = m_sliderCtrl.GetPos();
            return pos * m_tickWidth;
        }
        else return m_tickWidth * m_sliderPos;
    }
private:
    float m_min;
    float m_max;
    float m_tickWidth;
    int m_sliderPos;
    CString m_title;
};