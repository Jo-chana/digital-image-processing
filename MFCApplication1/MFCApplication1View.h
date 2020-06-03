
// MFCApplication1View.h : interface of the CMFCApplication1View class
//

#pragma once


class CMFCApplication1View : public CView
{
protected: // create from serialization only
	CMFCApplication1View();
	DECLARE_DYNCREATE(CMFCApplication1View)

// Attributes
public:
	CMFCApplication1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnImageBmp();
	afx_msg void OnImageJepg();
	afx_msg void OnRgbtohsiChange();
	afx_msg void OnPointprocessingContraststretching();
	afx_msg void OnPointprocessingSaturationinjecting();
	afx_msg void OnPointprocessingHistogram();
	afx_msg void OnHistogramColor();
	afx_msg void OnHistogramIntensity();
	afx_msg void OnRgb2hsiChange();
	afx_msg void OnRgbtohsiHsi2rgb();
	afx_msg void OnPointprocessingFacedetection();
	afx_msg void OnHistogramEqualization();
	afx_msg void OnBmpBlackwhite();
	afx_msg void OnBmpColoroption();
	afx_msg void OnHistogramColorequalization();
	afx_msg void OnHistogramDraw();
	afx_msg void OnHistogramDraw32799();
	afx_msg void OnBasicgraylevelNegative();
	afx_msg void OnBasicgraylevelLog();
	afx_msg void OnBasicgraylevelPower();
	afx_msg void OnBasicgraylevelThreshold();
	afx_msg void OnPowerGamma0();
	afx_msg void OnPowerGamma1();
	afx_msg void OnPowerGamma2();
	afx_msg void OnBasicgraylevelSolarizing();
	afx_msg void OnPowerGamma3();
	afx_msg void OnPowerGamma4();
	afx_msg void OnImageloadAvi();
	afx_msg void OnColorspaceTest();
	afx_msg void OnMean3();
	afx_msg void OnGaussian3();
	afx_msg void OnImageloadNewimagesave();
	afx_msg void OnImageloadNewimagesave32826();
	afx_msg void OnPowerGamma5();
	afx_msg void OnPowerGamma6();
	afx_msg void OnPowerGamma7();
	afx_msg void OnMean5();
	afx_msg void OnMean7();
	afx_msg void OnGaussian5();
	afx_msg void OnGaussian7();
	afx_msg void OnShapeBlock();
	afx_msg void OnSize3();
	afx_msg void OnSize5();
	afx_msg void OnSize7();
	afx_msg void OnMedianProcess();
	afx_msg void OnColoroptionColor();
	afx_msg void OnColoroptionGrayscale();
	afx_msg void OnShapeCross();
	afx_msg void OnShapeDiamond();
	afx_msg void OnShapeXshape();
	afx_msg void OnColoroptionIntensity();
	afx_msg void OnRgb2hsiGrayscale();
	afx_msg void OnColoroptionRgb();
	afx_msg void OnColorprocessHsi();
	afx_msg void OnMaskHB12();
	afx_msg void OnMorphologyDilation();
	afx_msg void OnMorphologyErosion();
	afx_msg void OnStructureBlock();
	afx_msg void OnSize4();
	afx_msg void OnMask22();
	afx_msg void OnEdgedetectionSobel();
	afx_msg void OnEdgedetectionPrewitt();
	afx_msg void OnEdgedetectionLog();
	afx_msg void OnLog3();
	afx_msg void OnLog5();
	afx_msg void LoG(int,float**,double);
	afx_msg void EdgeOperator();
	afx_msg void Mask();
	afx_msg void OnLog7();
	afx_msg void OnLog9();
	afx_msg void OnLog11();
	afx_msg void OnLog15();
	afx_msg void OnLogMultiple();
	afx_msg void OnEdgedetectionCanny();
	afx_msg void OnLog17();
	afx_msg void OnLog19();
};

#ifndef _DEBUG  // debug version in MFCApplication1View.cpp
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
   { return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument); }
#endif

