
// MFCApplication1View.cpp : implementation of the CMFCApplication1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma once
#include "Jpegfile.h"

#include <iostream>

#include "opencv2/opencv.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <stdlib.h>

// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_IMAGE_BMP, &CMFCApplication1View::OnImageBmp)
	ON_COMMAND(ID_IMAGE_JEPG, &CMFCApplication1View::OnImageJepg)
	ON_COMMAND(ID_RGBTOHSI_CHANGE, &CMFCApplication1View::OnRgbtohsiChange)
	ON_COMMAND(ID_POINTPROCESSING_CONTRASTSTRETCHING, &CMFCApplication1View::OnPointprocessingContraststretching)
	ON_COMMAND(ID_POINTPROCESSING_SATURATIONINJECTING, &CMFCApplication1View::OnPointprocessingSaturationinjecting)
	ON_COMMAND(ID_POINTPROCESSING_HISTOGRAM, &CMFCApplication1View::OnPointprocessingHistogram)
	ON_COMMAND(ID_HISTOGRAM_COLOR, &CMFCApplication1View::OnHistogramColor)
	ON_COMMAND(ID_HISTOGRAM_INTENSITY, &CMFCApplication1View::OnHistogramIntensity)
	ON_COMMAND(ID_RGB2HSI_CHANGE, &CMFCApplication1View::OnRgb2hsiChange)
	ON_COMMAND(ID_RGBTOHSI_HSI2RGB, &CMFCApplication1View::OnRgbtohsiHsi2rgb)
	ON_COMMAND(ID_POINTPROCESSING_FACEDETECTION, &CMFCApplication1View::OnPointprocessingFacedetection)
	ON_COMMAND(ID_HISTOGRAM_EQUALIZATION, &CMFCApplication1View::OnHistogramEqualization)
	ON_COMMAND(ID_BMP_BLACKWHITE, &CMFCApplication1View::OnBmpBlackwhite)
	ON_COMMAND(ID_BMP_COLOROPTION, &CMFCApplication1View::OnBmpColoroption)
	ON_COMMAND(ID_HISTOGRAM_COLOREQUALIZATION, &CMFCApplication1View::OnHistogramColorequalization)
	ON_COMMAND(ID_BASICGRAYLEVEL_NEGATIVE, &CMFCApplication1View::OnBasicgraylevelNegative)
	ON_COMMAND(ID_BASICGRAYLEVEL_LOG, &CMFCApplication1View::OnBasicgraylevelLog)
	ON_COMMAND(ID_BASICGRAYLEVEL_POWER, &CMFCApplication1View::OnBasicgraylevelPower)
	ON_COMMAND(ID_BASICGRAYLEVEL_THRESHOLD, &CMFCApplication1View::OnBasicgraylevelThreshold)
	ON_COMMAND(ID_POWER_GAMMA0, &CMFCApplication1View::OnPowerGamma0)
	ON_COMMAND(ID_POWER_GAMMA1, &CMFCApplication1View::OnPowerGamma1)
	ON_COMMAND(ID_POWER_GAMMA2, &CMFCApplication1View::OnPowerGamma2)
	ON_COMMAND(ID_BASICGRAYLEVEL_SOLARIZING, &CMFCApplication1View::OnBasicgraylevelSolarizing)
	ON_COMMAND(ID_POWER_GAMMA3, &CMFCApplication1View::OnPowerGamma3)
	ON_COMMAND(ID_POWER_GAMMA4, &CMFCApplication1View::OnPowerGamma4)
	ON_COMMAND(ID_IMAGELOAD_AVI, &CMFCApplication1View::OnImageloadAvi)
	ON_COMMAND(ID_COLORSPACE_TEST, &CMFCApplication1View::OnColorspaceTest)
	ON_COMMAND(ID_MEAN_3, &CMFCApplication1View::OnMean3)
	ON_COMMAND(ID_GAUSSIAN_3, &CMFCApplication1View::OnGaussian3)
	ON_COMMAND(ID_IMAGELOAD_NEWIMAGESAVE, &CMFCApplication1View::OnImageloadNewimagesave)
	ON_COMMAND(ID_POWER_GAMMA5, &CMFCApplication1View::OnPowerGamma5)
	ON_COMMAND(ID_POWER_GAMMA6, &CMFCApplication1View::OnPowerGamma6)
	ON_COMMAND(ID_POWER_GAMMA7, &CMFCApplication1View::OnPowerGamma7)
	ON_COMMAND(ID_MEAN_5, &CMFCApplication1View::OnMean5)
	ON_COMMAND(ID_MEAN_7, &CMFCApplication1View::OnMean7)
	ON_COMMAND(ID_GAUSSIAN_5, &CMFCApplication1View::OnGaussian5)
	ON_COMMAND(ID_GAUSSIAN_7, &CMFCApplication1View::OnGaussian7)
	ON_COMMAND(ID_SHAPE_BLOCK, &CMFCApplication1View::OnShapeBlock)
	ON_COMMAND(ID_SIZE_3, &CMFCApplication1View::OnSize3)
	ON_COMMAND(ID_SIZE_5, &CMFCApplication1View::OnSize5)
	ON_COMMAND(ID_SIZE_7, &CMFCApplication1View::OnSize7)
	ON_COMMAND(ID_MEDIAN_PROCESS, &CMFCApplication1View::OnMedianProcess)
	ON_COMMAND(ID_COLOROPTION_COLOR, &CMFCApplication1View::OnColoroptionColor)
	ON_COMMAND(ID_COLOROPTION_GRAYSCALE, &CMFCApplication1View::OnColoroptionGrayscale)
	ON_COMMAND(ID_SHAPE_CROSS, &CMFCApplication1View::OnShapeCross)
	ON_COMMAND(ID_SHAPE_DIAMOND, &CMFCApplication1View::OnShapeDiamond)
	ON_COMMAND(ID_SHAPE_XSHAPE, &CMFCApplication1View::OnShapeXshape)
	ON_COMMAND(ID_COLOROPTION_INTENSITY, &CMFCApplication1View::OnColoroptionIntensity)
	ON_COMMAND(ID_RGB2HSI_GRAYSCALE, &CMFCApplication1View::OnRgb2hsiGrayscale)
	ON_COMMAND(ID_COLOROPTION_RGB, &CMFCApplication1View::OnColoroptionRgb)
	ON_COMMAND(ID_COLORPROCESS_HSI, &CMFCApplication1View::OnColorprocessHsi)
	ON_COMMAND(ID_MASK2_1, &CMFCApplication1View::OnMaskHB12)
	ON_COMMAND(ID_MORPHOLOGY_DILATION, &CMFCApplication1View::OnMorphologyDilation)
	ON_COMMAND(ID_MORPHOLOGY_EROSION, &CMFCApplication1View::OnMorphologyErosion)
	ON_COMMAND(ID_STRUCTURE_BLOCK, &CMFCApplication1View::OnStructureBlock)
	ON_COMMAND(ID_SIZE_4, &CMFCApplication1View::OnSize4)
	ON_COMMAND(ID_MASK2_2, &CMFCApplication1View::OnMask22)
	ON_COMMAND(ID_EDGEDETECTION_SOBEL, &CMFCApplication1View::OnEdgedetectionSobel)
	ON_COMMAND(ID_EDGEDETECTION_PREWITT, &CMFCApplication1View::OnEdgedetectionPrewitt)
	ON_COMMAND(ID_LOG_3, &CMFCApplication1View::OnLog3)
	ON_COMMAND(ID_LOG_5, &CMFCApplication1View::OnLog5)
	ON_COMMAND(ID_LOG_7, &CMFCApplication1View::OnLog7)
	ON_COMMAND(ID_LOG_9, &CMFCApplication1View::OnLog9)
	ON_COMMAND(ID_LOG_11, &CMFCApplication1View::OnLog11)
	ON_COMMAND(ID_LOG_15, &CMFCApplication1View::OnLog15)
	ON_COMMAND(ID_LOG_MULTIPLE, &CMFCApplication1View::OnLogMultiple)
	ON_COMMAND(ID_EDGEDETECTION_CANNY, &CMFCApplication1View::OnEdgedetectionCanny)
END_MESSAGE_MAP()



// CMFCApplication1View construction/destruction
RGBQUAD** rgbBuffer; //-> 이미지를 저장할 변수
float** rgb_red; // 변환된 이미지 R 수치
float** rgb_green; // 변환된 이미지 G 수치
float** rgb_blue; // 변환된 이미지 B 수치
int imgHeight; //-> 이미지 높이 정보
int imgWidth; //-> 이미지 너비 정보
BITMAPINFOHEADER bmpInfo; //-> BMP 정보 헤더
BITMAPFILEHEADER bmpHeader;// -> BMP 파일 헤더	
						   /*동적 할당하는 포인터 배열은 반드시 '생성자'와 '소멸자' 에
						   null 로 초기화 및 해제를 수행해야 한다.*/

float** hueBuffer; //이미지 색조 정보
float** satuBuffer; //이미지 채도 정보
float** intenBuffer; //이미지 밝기 정보
int viewType = 0; // 화면 출력 유형 정보

int* histogram; // 히스토그램 수치 정보
bool is_color = FALSE; //컬러사진 여부 정보

float** intensity; // 흑백 이미지 편의용 

CMFCApplication1View::CMFCApplication1View()
{
	// TODO: add construction code here

}

CMFCApplication1View::~CMFCApplication1View()
{
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View drawing

void CMFCApplication1View::OnDraw(CDC* pDC)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);//기존의 것을 그대로 사용
	if (!pDoc)
		return;

	if (rgbBuffer != NULL) { //이미지 들어있는 경우 출력
		for (int i = 0;i < imgHeight;i++) { //이미지 사이즈 만큼 돌면서 한 픽셀씩 출력
			for (int j = 0;j < imgWidth;j++) {//rgbBuffer를 출력했던 2중 for문
				POINT p; //출력할 픽셀의 위치 지정
				p.x = j;
				p.y = i;
				pDC->SetPixel(p, RGB(rgbBuffer[i][j].rgbRed, rgbBuffer[i][j].rgbGreen, rgbBuffer[i][j].rgbBlue));
				//픽셀 위치 p에 RGB 값을 입력
				if (viewType == 2) {
					p.x = j + imgWidth + 10;
					p.y = i;
					pDC->SetPixel(p, RGB(hueBuffer[i][j], hueBuffer[i][j], hueBuffer[i][j]));

					p.x = j + imgWidth + 10;
					p.y = i + imgHeight + 10;
					pDC->SetPixel(p, RGB(satuBuffer[i][j], satuBuffer[i][j], satuBuffer[i][j]));

					p.x = j;
					p.y = i + imgHeight + 10;
					pDC->SetPixel(p, RGB(intenBuffer[i][j], intenBuffer[i][j], intenBuffer[i][j]));
				}

				if (viewType == 3) {
					p.x = j + imgWidth + 10;
					p.y = i;
					pDC->SetPixel(p, RGB(rgb_red[i][j], rgb_green[i][j], rgb_blue[i][j]));

				}
				if (viewType == 4) {
					p.x = j + imgWidth + 10;
					p.y = i;
					pDC->SetPixel(p, RGB(intensity[i][j], intensity[i][j], intensity[i][j]));
					if (intensity[i][j]!=255&&intensity[i][j]!=0) {
					}
				}
				
			}
		}		
		if (viewType == 5) {
			float max = 0;
			for (int i = 0;i < 256;i++) {
				if (histogram[i] > max)
					max = histogram[i];
			}

			for (int i = 0;i < 256;i++) {
				histogram[i] = histogram[i]*imgHeight / max;
				pDC->Rectangle(imgWidth + (i * 2), imgHeight - histogram[i], imgWidth + 2 + (i * 2), imgHeight);
			}
		}
		std::cout << "화면 출력 완료 viewType: ";
		std::cout << viewType << std::endl;
	}
}


// CMFCApplication1View printing

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMFCApplication1View diagnostics

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View message handlers

CString path;
void CMFCApplication1View::OnImageBmp()
{
	
	//1. 파일 다이얼로그로부터 BMP 파일 입력
	CFileDialog dlg(TRUE, ".bmp", NULL, NULL, "Bitmap File(*.bmp)|*.bmp||");
	if (IDOK != dlg.DoModal())
		return;
	CString filename = dlg.GetPathName();
	path = filename;
	if(rgbBuffer != NULL){//이미 할당된 경우 메모리 헤제
		for (int i = 0;i < imgHeight;i++)
			delete [] rgbBuffer[i];
		delete [] rgbBuffer;
	}

	//2. 파일을 오픈하여 영상 정보 획득
	CFile file;
	file.Open(filename, CFile::modeRead);
	file.Read(&bmpHeader, sizeof(BITMAPFILEHEADER));
	file.Read(&bmpInfo, sizeof(BITMAPINFOHEADER));
	imgWidth = bmpInfo.biWidth;
	imgHeight = bmpInfo.biHeight;

	//3. 이미지를 저장할 버퍼 할당(2차원 배열) [이미지 높이*이미지 너비 만큼 할당]
	rgbBuffer = new RGBQUAD*[imgHeight];
	for (int i = 0;i < imgHeight;i++)
		rgbBuffer[i] = new RGBQUAD[imgWidth];

	//4. 이미지의 너비가 4의 배수인지 체크
	// BMP 조건 가로는 4byte 이어야 한다.
	// 한 픽셀이 3바이트(R,G,B)이므로, 가로(m_width)*3 이 4의 배수인지 아닌지 알아야 함
	// b4byte : 4byte 의 배수인지 아닌지 안다.
	// upbyte : 4byte 에 모자라는 바이트다.
	bool b4byte = false;
	int upbyte = 0;
	if ((imgWidth * 3) % 4 == 0) {
		// 4의 배수로 떨어지는 경우
		b4byte = true;
		upbyte = 0;
	}
	else {
		// 4의 배수로 떨어지지 않는 경우
		b4byte = false;
		upbyte = 4 - (imgWidth * 3) % 4;
	}

	//5. 픽셀 데이터를 파일로부터 읽어옴
	BYTE data[3];
	for (int i = 0; i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			file.Read(&data, 3);
			//이미지 거꾸로 저장되어 있으므로 거꾸로 읽어옴
			rgbBuffer[imgHeight - i - 1][j].rgbBlue = data[0];
			rgbBuffer[imgHeight - i - 1][j].rgbGreen = data[1];
			rgbBuffer[imgHeight - i - 1][j].rgbRed = data[2];

		}
		if (b4byte == false)
		{
			//가로가 4byte 배수가 아니면 쓰레기 값을 읽는다
			file.Read(&data, upbyte);
		}
	}
	file.Close(); //파일 닫기
	viewType = 0;
	Invalidate(TRUE); // 화면 갱신

}

void CMFCApplication1View::OnBmpColoroption()
{
	is_color = TRUE;
	OnImageBmp();
}

void CMFCApplication1View::OnBmpBlackwhite()
{ 
	is_color = FALSE;
	//1. 파일 다이얼로그로부터 BMP 파일 입력
	CFileDialog dlg(TRUE, ".bmp", NULL, NULL, "Bitmap File(*.bmp)|*.bmp||");
	if (IDOK != dlg.DoModal())
		return;
	CString filename = dlg.GetPathName();
	path = filename;
	if (rgbBuffer != NULL) {//이미 할당된 경우 메모리 헤제
		for (int i = 0;i < imgHeight;i++)
			delete[] rgbBuffer[i];
		delete[] rgbBuffer;
	}

	//2. 파일을 오픈하여 영상 정보 획득
	CFile file;
	file.Open(filename, CFile::modeRead);
	file.Read(&bmpHeader, sizeof(BITMAPFILEHEADER));
	file.Read(&bmpInfo, sizeof(BITMAPINFOHEADER));
	imgWidth = bmpInfo.biWidth;
	imgHeight = bmpInfo.biHeight;

	//3. 이미지를 저장할 버퍼 할당(2차원 배열) [이미지 높이*이미지 너비 만큼 할당]
	rgbBuffer = new RGBQUAD*[imgHeight];
	for (int i = 0;i < imgHeight;i++)
		rgbBuffer[i] = new RGBQUAD[imgWidth];

	//4. 이미지의 너비가 4의 배수인지 체크
	// BMP 조건 가로는 4byte 이어야 한다.
	// 한 픽셀이 1바이트이므로, 가로(m_width) 이 4의 배수인지 아닌지 알아야 함
	// b4byte : 4byte 의 배수인지 아닌지 안다.
	// upbyte : 4byte 에 모자라는 바이트다.
	bool b4byte = false;
	int upbyte = 0;
	if (imgWidth % 4 == 0) {
		// 4의 배수로 떨어지는 경우
		b4byte = true;
		upbyte = 0;
	}
	else {
		// 4의 배수로 떨어지지 않는 경우
		b4byte = false;
		upbyte = 4 - (imgWidth % 4);
	}

	//5. 픽셀 데이터를 파일로부터 읽어옴
	BYTE data[1];
	for (int i = 0; i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			file.Read(&data, 1);
			//이미지 거꾸로 저장되어 있으므로 거꾸로 읽어옴
			rgbBuffer[imgHeight - i - 1][j].rgbBlue = data[0];
			rgbBuffer[imgHeight - i - 1][j].rgbGreen = data[0];
			rgbBuffer[imgHeight - i - 1][j].rgbRed = data[0];

		}
		if (b4byte == false)
		{
			//가로가 4byte 배수가 아니면 쓰레기 값을 읽는다
			file.Read(&data, upbyte);
		}
	}
	file.Close(); //파일 닫기
	viewType = 0;
	Invalidate(TRUE); // 화면 갱신
}

BYTE* LoadJpegFromOpenFile(FILE *fp, BITMAPINFOHEADER *pbh, UINT *pWidth, UINT *pHeight) {
	//파일로부터 JPG 정보 획득
	if (pWidth == NULL || pHeight == NULL) return NULL;
	BYTE *tmp = JpegFile::OpenFileToRGB(fp , pWidth, pHeight);
	if (!tmp) return NULL;
	JpegFile::BGRFromRGB(tmp, *pWidth, *pHeight);
	UINT dw;
	BYTE *pbuf = JpegFile::MakeDwordAlignedBuf(tmp, *pWidth, *pHeight, &dw);
	delete[] tmp;
	if (!pbuf) return NULL;
	JpegFile::VertFlipBuf(pbuf, dw, *pHeight);
	pbh->biSize = sizeof(BITMAPINFOHEADER);
	pbh->biWidth = *pWidth;
	pbh->biHeight = *pHeight;
	pbh->biPlanes = 1;
	pbh->biBitCount = 24;
	pbh->biCompression = BI_RGB;
	pbh->biSizeImage = 0;
	pbh->biXPelsPerMeter = 0;
	pbh->biYPelsPerMeter = 0;
	pbh->biClrUsed = 0;
	pbh->biClrImportant = 0;
	return pbuf;
}

void CMFCApplication1View::OnImageJepg()
{
	is_color = TRUE;
	CFileDialog dlg(TRUE, ".jpg", NULL, NULL, "Jpeg File(*.jpg)|*jpg||");
	if (IDOK != dlg.DoModal()) return;
	CString filename = dlg.GetPathName();
	path = filename;

	//BMP 로드와 마찬가지로 rgbBuffer가 NULL이 아닌 경우 메모리 헤제 코드 추가하기
	if (rgbBuffer != NULL) {//이미 할당된 경우 메모리 헤제
		for (int i = 0;i < imgHeight;i++)
			delete[] rgbBuffer[i];
		delete[] rgbBuffer;
	}

	FILE *fp = fopen(filename, "rb");
	BITMAPINFOHEADER pbh;
	UINT w, h;
	BYTE *pbuf = LoadJpegFromOpenFile(fp, &pbh, &w, &h);
	imgWidth = (int)w;
	imgHeight = (int)h;
	//BMP 로드와 마찬가지로 rgbBuffer를 이미지 사이즈 만큼 메모리 할당 코드 추가
	rgbBuffer = new RGBQUAD*[imgHeight];
	for (int i = 0;i < imgHeight;i++)
		rgbBuffer[i] = new RGBQUAD[imgWidth];

	int dw = WIDTHBYTES(imgWidth * 24);
	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			rgbBuffer[imgHeight - i - 1][j].rgbBlue = pbuf[dw * i + j * 3 + 0];
			rgbBuffer[imgHeight - i - 1][j].rgbGreen = pbuf[dw * i + j * 3 + 1];
			rgbBuffer[imgHeight - i - 1][j].rgbRed = pbuf[dw * i + j * 3 + 2];
					}
	}
	delete[] pbuf;
	fclose(fp);
	viewType = 0;
	Invalidate(TRUE);
}

void CMFCApplication1View::OnRgb2hsiGrayscale()
{
	OnRgbtohsiChange();
	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			intenBuffer[i][j] *= 255;
		}
	}
	intensity = intenBuffer;
	viewType = 4;
	Invalidate(FALSE);
}


void CMFCApplication1View::OnColoroptionColor()
{
	is_color = TRUE;
}


void CMFCApplication1View::OnColoroptionGrayscale()
{
	is_color = FALSE;
}

void CMFCApplication1View::OnImageloadNewimagesave()
{
	if (!rgbBuffer)
		return;
	if (viewType == 3) {
		for (int i = 0;i < imgHeight;i++) {
			for (int j = 0;j < imgWidth;j++) {
				rgbBuffer[i][j].rgbBlue = rgb_blue[i][j];
				rgbBuffer[i][j].rgbRed = rgb_red[i][j];
				rgbBuffer[i][j].rgbGreen = rgb_green[i][j];
			}
		}
	}
	if (viewType == 4) {
		for (int i = 0;i < imgHeight;i++) {
			for (int j = 0;j < imgWidth;j++) {
				rgbBuffer[i][j].rgbBlue = intensity[i][j];
				rgbBuffer[i][j].rgbRed = intensity[i][j];
				rgbBuffer[i][j].rgbGreen = intensity[i][j];
			}
		}
	}
	viewType = 0;
	Invalidate(TRUE);

}

void CMFCApplication1View::OnImageloadAvi()
{
	/*using namespace cv;*/
	CFileDialog dlg(TRUE, ".avi", NULL, NULL, "AVI File (*.avi)|*.avi||");
	if (IDOK != dlg.DoModal())
		return;

	CString cfilename = dlg.GetPathName();
	CT2CA strAtl(cfilename);
	cv::String filename(strAtl);

	cv::VideoCapture Capture;
	Capture.open(filename);

	if (!Capture.isOpened())
		AfxMessageBox("Error Video");

	for (;;) {
		cv::Mat frame;
		Capture >> frame;
		if (frame.data == nullptr)
			break;
		imshow("video", frame);
		if (cv::waitKey(30) >= 0)
			break;
	}
	AfxMessageBox("Completed");

}

void CMFCApplication1View::OnRgbtohsiChange() // 함수 재사용 목적으로 작성
{   
	//2. rgbBuffer 에 이미지가 들어있는 지 여부 확인
	if (rgbBuffer == NULL)
		OnImageBmp(); //rgbBuffer 에 데이터가 없는 경우, 로드 함수를 호출하여 이미지 획득

	hueBuffer = new float*[imgHeight];
	satuBuffer = new float*[imgHeight];
	intenBuffer = new float*[imgHeight];

	for (int i = 0;i < imgHeight;i++) {
		hueBuffer[i] = new float[imgWidth];
		satuBuffer[i] = new float[imgWidth];
		intenBuffer[i] = new float[imgWidth];
	}

	//3. RGB to HSI 값 변환
	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			float r = rgbBuffer[i][j].rgbRed;
			float g = rgbBuffer[i][j].rgbGreen;
			float b = rgbBuffer[i][j].rgbBlue;
			intenBuffer[i][j] = (r + g + b) / (float)(3 * 255);//intensity
			float total = r + g + b;
			r = r / total; g = g / total; b = b / total;
			satuBuffer[i][j] = 1 - 3 * (r > g ? (g > b ? b : g) : (r > b ? b : r));
			if (r == g&&g == b) {
				hueBuffer[i][j] = 0;satuBuffer[i][j] = 0;
			}
			else {
				total = (0.5*(r - g + r - b) / sqrt((r - g)*(r - g) + (r - b)*(g - b)));
				hueBuffer[i][j] = acos((double)total);
				if (b > g) {
					hueBuffer[i][j] = 2*3.1415 - hueBuffer[i][j];
				}
			} // 함수 재사용을 위해 정규화 와 출력은 함수적으로 분리하였음.
		}
	}
	
}

void CMFCApplication1View::OnRgb2hsiChange()
{
	OnRgbtohsiChange();

	//4.출력 값 범위 정규화: 출력 시, 값의 범위를 [0,255]로 맞춤
	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			hueBuffer[i][j] = hueBuffer[i][j] * 255 / (3.14 * 2);
			satuBuffer[i][j] = satuBuffer[i][j] * 255;
			intenBuffer[i][j] = intenBuffer[i][j] * 255;
		}
	}

	//5.출력
	viewType = 2;
	Invalidate(FALSE);

}

void CMFCApplication1View::OnRgbtohsiHsi2rgb() // 함수 재사용 목적으로 작성
{
	rgb_red = new float*[imgHeight];
	rgb_green = new float*[imgHeight];
	rgb_blue = new float*[imgHeight];
	for (int i = 0;i < imgHeight;i++) {
		rgb_red[i] = new float[imgWidth];
		rgb_green[i] = new float[imgWidth];
		rgb_blue[i] = new float[imgWidth];
	}

	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			float R = 0;
			float G = 0;
			float B = 0;
			float r = 0;
			float g = 0;
			float b = 0;
			float S = satuBuffer[i][j];
			float H = hueBuffer[i][j];
			float I = intenBuffer[i][j];

			if (I == 0) {
				r = 0;
				g = 0;
				b = 0;
			}
			else if (S == 0) {
				r = 1. / 3.;
				g = 1. / 3.;
				b = 1. / 3.;
			}
			else {

				if (H < 2. * 3.1415 / 3.) { // 0 <= H <= 2/3Pi
					b = (1 - S) / 3.;
					r = (1 + (S*cos((double)H) / cos(3.1415 / 3 - H))) / 3.;
					g = 1 - (r + b);

				}
				else if (H < 4 * 3.1415 / 3) { // 2/3Pi < H <= 4/3Pi
					H = H - 2. * 3.1415 / 3.;
					r = (1 - S) / 3.;
					g = (1 + (S*cos((double)H) / cos(3.1415 / 3 - H))) / 3.;
					b = 1 - (r + g);

				}
				else { // 4/3Pi < H =< 2Pi
					H = H - 4. * 3.1415 / 3.;
					g = (1 - S) / 3.;
					b = (1 + (S*cos((double)H) / cos(3.1415 / 3 - H))) / 3.;
					r = 1 - (g + b);

				}
			}
#define min(a, b) (((a) < (b)) ? (a) : (b))
			R = min(255, 255 * 3 * r * I); //255 * 3 * r*I;
			G = min(255, 255 * 3 * g * I); //255 * 3 * g*I;
			B = min(255, 255 * 3 * b * I); //255 * 3 * b*I;

			//원본 이미지 데이터를 보존하기 위해 새로운 변수에 저장
			rgb_red[i][j] = R;
			rgb_green[i][j] = G;
			rgb_blue[i][j] = B;
		}
	}
}

void CMFCApplication1View::OnPointprocessingContraststretching()
{
	OnRgbtohsiChange();

	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0; j < imgWidth;j++) {
			intenBuffer[i][j] = intenBuffer[i][j] * 1.5; // 밝기 1.5배
		}
	}


	//3. 변환된 HSI 컬러를 RGB 컬러스페이스로 변환
	OnRgbtohsiHsi2rgb(); // 해당 함수 주석 참조
	
	
	//4. 출력
	viewType = 3;
	Invalidate(FALSE);
}


void CMFCApplication1View::OnPointprocessingSaturationinjecting()
{
#define min(a, b) (((a) < (b)) ? (a) : (b))
	OnRgbtohsiChange();
	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			satuBuffer[i][j] = min(1, satuBuffer[i][j] * 1.5); // 채도 1.5배 개선
		}
	}

	OnRgbtohsiHsi2rgb();
	//4. 출력
	viewType = 3;
	Invalidate(FALSE);
}


void CMFCApplication1View::OnPointprocessingHistogram()
{
	
}


void CMFCApplication1View::OnHistogramColor()
{
	OnRgbtohsiChange(); // HSI 정보 획득

	if (histogram==NULL)
		histogram = new int[360]; // Hue 360도 스케일
	for (int i = 0;i < 360;i++) {
		histogram[i] = 0;
	}

	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			int color = (int)(hueBuffer[i][j] * 180 / 3.1415);
			histogram[color]++;
		}
	}
	int max = 0;
	for (int i = 0; i < 360;i++) {
		if( histogram[i] > max)
			max = histogram[i];
	}
	for (int i = 0; i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			int color = (int)(hueBuffer[i][j] * 180 / 3.1415);
			hueBuffer[i][j] = (float)histogram[color] * 255 / max;
		}
	}
	viewType = 2;
	Invalidate(FALSE);
}


void CMFCApplication1View::OnHistogramIntensity()
{
	OnRgbtohsiChange(); // HSI 정보 획득

	if(histogram==NULL)
		histogram = new int[255]; 
	for (int i = 0;i < 256;i++) {
		histogram[i] = 0;
	}

	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			int inten = (int)(intenBuffer[i][j] * 255);
			histogram[inten]++;
		}
	}

	
	viewType = 5;
	Invalidate(FALSE);
}








void CMFCApplication1View::OnPointprocessingFacedetection()
{
	/*
	피부색 조건
	Saturation 0.1 ~ 0.6
	Hue < 0.1 || > 0.88
	*/

	OnRgbtohsiChange();
	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			float S = satuBuffer[i][j];
			float H = hueBuffer[i][j];
			float I = intenBuffer[i][j];

			if (S < 0.1 || S > 0.6)
				intenBuffer[i][j] = 0;
			
			if (H > 0.88 || H < 0.1)
				intenBuffer[i][j] = 0;

		}
	}
	OnRgbtohsiHsi2rgb();
	viewType = 3;
	Invalidate(FALSE);

}


void CMFCApplication1View::OnHistogramEqualization()
{
	// Intensity 값을 기준으로 histogram equalize
	OnRgbtohsiChange();

	// 히스토그램 초기화
	if (histogram == NULL)
		histogram = new int[255];
	for (int i = 0;i < 256;i++) {
		histogram[i] = 0;
	}

	float max_pixel = 0;
	float total_pixel = 0;

	// 밝기 히스토그램 
	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			int inten = (int)(intenBuffer[i][j] * 255.);
			histogram[inten]++;
			total_pixel++;
			if (inten > max_pixel)
				max_pixel = inten;
		}
	}

	// 히스토그램 정규화
	float sum = 0.;
	float* sum_hist = new float[255];
	for (int i = 0;i < 256;i++) {
		sum += histogram[i];
		sum_hist[i] = sum*max_pixel/total_pixel + 0.5;
	}

	//컬러사진일때
	if (is_color) {
		//변환
		for (int i = 0;i < imgHeight;i++) {
			for (int j = 0;j < imgWidth;j++) {
				intenBuffer[i][j] = (float)sum_hist[(int)(intenBuffer[i][j] * 255)] / 255.;
			}
		}

		OnRgbtohsiHsi2rgb();

		viewType = 3;
		Invalidate(FALSE);
	}
	
	//흑백사진일때
	else {

		intensity = new float*[imgHeight];
		for (int i = 0;i < imgHeight;i++) {
			intensity[i] = new float[imgWidth];
		}
		// 변환
		for (int i = 0;i < imgHeight;i++) {
			for (int j = 0;j < imgWidth;j++) {
				intensity[i][j] = sum_hist[(int)(intenBuffer[i][j] * 255.)];
			}
		}

		// 출력
		viewType = 4;
		Invalidate(FALSE);
	}

}


void CMFCApplication1View::OnHistogramColorequalization()
{
	if (rgbBuffer == NULL)
		OnImageBmp();

	int* hred = new int[255];
	int* hgreen = new int[255];
	int* hblue = new int[255];

	for (int i = 0;i < 256;i++) {
		hred[i] = 0;hgreen[i] = 0;hblue[i] = 0;
	}

	float total_pixel = 0;
	float max_red = 0;
	float max_green = 0;
	float max_blue = 0;

	// RGB 히스토그램 
	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			total_pixel++;
			hred[rgbBuffer[i][j].rgbRed]++;
			hgreen[rgbBuffer[i][j].rgbGreen]++;
			hblue[rgbBuffer[i][j].rgbBlue]++;
			max_red = (rgbBuffer[i][j].rgbRed > max_red ? rgbBuffer[i][j].rgbRed : max_red);
			max_green = (rgbBuffer[i][j].rgbGreen > max_green ? rgbBuffer[i][j].rgbGreen : max_green);
			max_blue = (rgbBuffer[i][j].rgbBlue > max_blue ? rgbBuffer[i][j].rgbBlue : max_blue);
		}
	}

	// 히스토그램 정규화
	int sumred = 0;
	int sumgreen = 0;
	int sumblue = 0;

	float* sum_red = new float[255];
	float* sum_green = new float[255];
	float* sum_blue = new float[255];

	for (int i = 0;i < 256;i++) {
		sumred += hred[i];
		sumgreen += hgreen[i];
		sumblue += hblue[i];
		sum_red[i] = (float)sumred*max_red / total_pixel + 0.5;
		sum_green[i] = (float)sumgreen*max_green / total_pixel + 0.5;
		sum_blue[i] = (float)sumblue*max_blue / total_pixel + 0.5;
	}

	rgb_red = new float*[imgHeight];
	rgb_green = new float*[imgHeight];
	rgb_blue = new float*[imgHeight];
	for (int i = 0;i < imgHeight;i++) {
		rgb_red[i] = new float[imgWidth];
		rgb_green[i] = new float[imgWidth];
		rgb_blue[i] = new float[imgWidth];
	}
	

	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			rgb_red[i][j] = sum_red[rgbBuffer[i][j].rgbRed];
			rgb_green[i][j] =sum_green[rgbBuffer[i][j].rgbGreen];
			rgb_blue[i][j] = sum_blue[rgbBuffer[i][j].rgbBlue];
		}
	}

	viewType = 3;
	Invalidate(FALSE);
}






void CMFCApplication1View::OnBasicgraylevelNegative()
{
	if (rgbBuffer == NULL)
		OnBmpBlackwhite();
	
	rgb_red = new float*[imgHeight];
	rgb_green = new float*[imgHeight];
	rgb_blue = new float*[imgHeight];
	for (int i = 0;i < imgHeight;i++){
		rgb_red[i] = new float[imgWidth];
		rgb_green[i] = new float[imgWidth];
		rgb_blue[i] = new float[imgWidth];
	}

	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			rgb_red[i][j] = 255 - rgbBuffer[i][j].rgbRed;
			rgb_green[i][j] = 255 - rgbBuffer[i][j].rgbGreen;
			rgb_blue[i][j] = 255 - rgbBuffer[i][j].rgbBlue;
		}
	}
	viewType = 3;
	Invalidate(FALSE);

}


void CMFCApplication1View::OnBasicgraylevelLog()
{
	
}

double gamma;

void CMFCApplication1View::OnBasicgraylevelPower()
{
	
	if (rgbBuffer == NULL)
		OnBmpBlackwhite();
	OnRgbtohsiChange();

	intensity = new float*[imgHeight];
	for (int i = 0;i < imgHeight;i++) {
		intensity[i] = new float[imgWidth];
	}

	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			double inten = intenBuffer[i][j];
			inten = pow(inten, gamma);
			intensity[i][j] = inten;
		}
	}
	if (is_color) {
		intenBuffer = intensity;
		OnRgbtohsiHsi2rgb();
		viewType = 3;
		Invalidate(FALSE);
	}
	else {
		for (int i = 0;i < imgHeight;i++) {
			for (int j = 0;j < imgWidth;j++) {
				intensity[i][j] = intensity[i][j] * 255.;
			}
		}
		viewType = 4;
		Invalidate(FALSE);
	}
}

void CMFCApplication1View::OnPowerGamma0()
{
	gamma = 0.3;
	OnBasicgraylevelPower();
}


void CMFCApplication1View::OnPowerGamma1()
{
	gamma = 0.5;
	OnBasicgraylevelPower();
}


void CMFCApplication1View::OnPowerGamma2()
{
	gamma = 0.7;
	OnBasicgraylevelPower();
}

void CMFCApplication1View::OnPowerGamma3()
{
	gamma = 1.3;
	OnBasicgraylevelPower();
}


void CMFCApplication1View::OnPowerGamma4()
{
	gamma = 1.7;
	OnBasicgraylevelPower();
}

void CMFCApplication1View::OnPowerGamma5()
{
	gamma = 3.;
	OnBasicgraylevelPower();
}


void CMFCApplication1View::OnPowerGamma6()
{
	gamma = 4.;
	OnBasicgraylevelPower();
}


void CMFCApplication1View::OnPowerGamma7()
{
	gamma = 5.;
	OnBasicgraylevelPower();
}


void CMFCApplication1View::OnBasicgraylevelThreshold()
{
	//OnHistogramEqualization();

	OnRgbtohsiChange();
	
	intensity = intenBuffer;

		
	//평균값 계산
	float sum = 0; // 총 합
	float total = 0; // 픽셀 수
	float med = 0; // 평균
	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			sum += intensity[i][j];
			total++;
		}
	}
	med = sum / total;

	// 이진화
	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			intensity[i][j] = intensity[i][j] > med ? 255 : 0;
		}
	}

	viewType = 4;
	Invalidate(FALSE);
}

void CMFCApplication1View::OnBasicgraylevelSolarizing()
{
	OnHistogramEqualization();

	if (is_color)
		intensity = intenBuffer;

	// 데이터 정규화
	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			intensity[i][j] = 3.14*intensity[i][j] / 255.;
			intensity[i][j] = sin(intensity[i][j])*255.;
		}
	}
	if (is_color) {
		intenBuffer = intensity;
		OnRgbtohsiHsi2rgb();
		viewType = 3;
		Invalidate(FALSE);
	}
	else {
		viewType = 4;
		Invalidate(FALSE);
	}
}

void CMFCApplication1View::OnColorspaceTest()
{
	OnRgbtohsiChange();
	OnRgbtohsiHsi2rgb();
	viewType = 3;
	Invalidate(FALSE);
}


float** mask;
int size;
bool rgb_option;
bool hue_option;

void CMFCApplication1View::Mask() {
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

	int k = (size - 1) / 2;

	if (!is_color) {
		intensity = new float*[imgHeight];
		for (int i = 0;i < imgHeight;i++) {
			intensity[i] = new float[imgWidth];
		}
		OnRgbtohsiChange();
		
		for (int i = 0;i < imgHeight;i++) {
			for (int j = 0;j < imgWidth;j++) {

				float value = 0.; // pixel value

				// Mask loop Start
				for (int x = 0;x < size;x++) {
					for (int y = 0;y < size;y++) {
						int u = x - k;
						int v = y - k;
						if (i + u >= 0 && j + v >= 0) {
							if (i + u < imgHeight && j + v < imgWidth)
								value = value + intenBuffer[i + u][j + v]*255*mask[x][y];
						}
							
					}
				}
				// Mask loop End
				intensity[i][j] = value;
			}
		}
	}
	else {
		rgb_red = new float*[imgHeight];
		rgb_green = new float*[imgHeight];
		rgb_blue = new float*[imgHeight];
		for (int i = 0;i < imgHeight;i++) {
			rgb_red[i] = new float[imgWidth];
			rgb_green[i] = new float[imgWidth];
			rgb_blue[i] = new float[imgWidth];
		}
		for (int i = 0;i < imgHeight;i++) {
			for (int j = 0;j < imgWidth;j++) {

				float value = 0.; // pixel value
				float value2 = 0;
				float value3 = 0;
								  // Mask loop Start
				for (int x = 0;x < size;x++) {
					for (int y = 0;y < size;y++) {
						int u = x - k;
						int v = y - k;
						if (i + u >= 0 && j + v >= 0) {
							if (i + u < imgHeight && j + v < imgWidth) {
								value = value + rgbBuffer[i + u][j + v].rgbRed*mask[x][y];
								value2 = value2 + rgbBuffer[i + u][j + v].rgbGreen*mask[x][y];
								value3 = value3 + rgbBuffer[i + u][j + v].rgbBlue*mask[x][y];
							}
						}

					}
				}
				// Mask loop End
				rgb_red[i][j] = max(0,min(255,value));
				rgb_green[i][j] = max(0,min(255,value2));
				rgb_blue[i][j] = max(0,min(255,value3));
			}
		}
	}

}

void CMFCApplication1View::OnMean3()
{
	/*if (mask) {
		for (int i = 0;i < size ;i++) {
			delete[] mask[i];
		}
		delete[] mask;
	}*/

	mask = new float*[3];
	for (int i = 0;i < 3;i++) {
		mask[i] = new float[3];
	}

	for (int i = 0;i < 3;i++) {
		for (int j = 0;j < 3;j++) {
			mask[i][j] = 0.11;
		}
	}
	size = 3;
	Mask();
	if (!is_color) {
		viewType = 4;
		Invalidate(FALSE);
	}
	else {
		viewType = 3;
		Invalidate(FALSE);
	}
}

void CMFCApplication1View::OnMean5()
{
	if (mask) {
		for (int i = 0;i < size;i++) {
			delete[] mask[i];
		}
		delete[] mask;
	}

	mask = new float*[5];
	for (int i = 0;i < 5;i++) {
		mask[i] = new float[5];
	}

	for (int i = 0;i < 5;i++) {
		for (int j = 0;j < 5;j++) {
			mask[i][j] = 0.04;
		}
	}
	size = 5;
	Mask();
	if (!is_color) {
		viewType = 4;
		Invalidate(FALSE);
	}
	else {
		viewType = 3;
		Invalidate(FALSE);
	}
}


void CMFCApplication1View::OnMean7()
{
	if (mask) {
		for (int i = 0;i < size;i++) {
			delete[] mask[i];
		}
		delete[] mask;
	}

	mask = new float*[7];
	for (int i = 0;i < 7;i++) {
		mask[i] = new float[7];
	}

	for (int i = 0;i < 7;i++) {
		for (int j = 0;j < 7;j++) {
			mask[i][j] = 0.02;
		}
	}
	size = 7;
	Mask();
	if (!is_color) {
		viewType = 4;
		Invalidate(FALSE);
	}
	else {
		viewType = 3;
		Invalidate(FALSE);
	}
}

void CMFCApplication1View::OnGaussian3()
{
	if (mask) {
		for (int i = 0;i < size;i++) {
			delete[] mask[i];
		}
		delete[] mask;
	}
	mask = new float*[3];
	for (int i = 0;i < 3;i++) {
		mask[i] = new float[3];
	}

	for (int i = 0;i < 3;i++) {
		for (int j = 0;j < 3;j++) {
			if (i != 1 && j != 1)
				mask[i][j] = 0.0625;
			else if (i != j)
				mask[i][j] = 0.125;
			else
				mask[i][j] = 0.25;
		}
	}
	size = 3;
	Mask();
	if (!is_color) {
		viewType = 4;
		Invalidate(FALSE);
	}
	else {
		viewType = 3;
		Invalidate(FALSE);
	}
}

void CMFCApplication1View::OnGaussian5()
{
	if (mask) {
		for (int i = 0;i < size;i++) {
			delete[] mask[i];
		}
		delete[] mask;
	}
	mask = new float*[5];
	for (int i = 0;i < 5;i++) {
		mask[i] = new float[5];
	}

	for (int i = 0;i < 5;i++) {
		for (int j = 0;j < 5;j++) {
			double sigma = 1;
			double d = -((i - 2)*(i - 2) + (j - 2)*(j - 2)) / (2*sigma*sigma);
			mask[i][j] = exp(d)/(6.28*sigma*sigma);
		}
	}
	size = 5;
	Mask();
	if (!is_color) {
		viewType = 4;
		Invalidate(FALSE);
	}
	else {
		viewType = 3;
		Invalidate(FALSE);
	}
}


void CMFCApplication1View::OnGaussian7()
{
	/*if (mask) {
		for (int i = 0;i < size;i++) {
			delete[] mask[i];
		}
		delete[] mask;
	}*/
	mask = new float*[7];
	for (int i = 0;i < 7;i++) {
		mask[i] = new float[7];
	}

	for (int i = 0;i < 7;i++) {
		for (int j = 0;j < 7;j++) {
			double sigma = 1.3;
			double d = -((i - 2)*(i - 2) + (j - 2)*(j - 2)) / (2 * sigma*sigma);
			mask[i][j] = exp(d) / (6.28*sigma*sigma);
		}
	}
	size = 7;
	Mask();
	if (!is_color) {
		viewType = 4;
		Invalidate(FALSE);
	}
	else {
		viewType = 3;
		Invalidate(FALSE);
	}
}

void quick_sort(float *data, int start, int end) {
	if (start >= end) { // 원소가 1개인 경우 
		return; 
	} 
	int pivot = start; 
	int i = pivot + 1; 
	// 왼쪽 출발 지점 
	int j = end; 
	// 오른쪽 출발 지점 
	float temp; while(i <= j){ 
		// 포인터가 엇갈릴때까지 반복 
		while(i <= end && data[i] <= data[pivot])
		{ i++; } 
		while(j > start && data[j] >= data[pivot]){ j--; } 
		if(i > j){ 
			// 엇갈림 
			temp = data[j]; 
			data[j] = data[pivot];
			data[pivot] = temp; 
		}else{ 
			// i번째와 j번째를 스왑 
			temp = data[i]; 
			data[i] = data[j]; 
			data[j] = temp; } } 
	// 분할 계산 
	quick_sort(data, start, j - 1); 
	quick_sort(data, j + 1, end); 
}

void median() {
	int k = (size - 1) / 2;

	intensity = new float*[imgHeight];
	for (int i = 0;i < imgHeight;i++) {
		intensity[i] = new float[imgWidth];
	}

	if (!is_color) {
		for (int i = k;i < imgHeight-k;i++) {
			for (int j = k;j < imgWidth-k;j++){
				float list[50];
				int idx = 0;
				for (int x = 0;x < size;x++) {
					for (int y = 0;y < size;y++) {
						int u = x - k;
						int v = y - k;
						if (mask[x][y])
							list[idx] = rgbBuffer[i + u][j + v].rgbBlue;idx += 1;						
					}
				}
				
				quick_sort(list, 0, idx - 1);
				float value = list[k];
					

				// Mask loop End
				intensity[i][j] = value;
			}
		}
	}
	else {
		if (hue_option) {
			for (int i = k;i < imgHeight - k;i++) {
				for (int j = k;j < imgWidth - k;j++) {
					float list[50];
					int idx = 0;
					for (int x = 0;x < size;x++) {
						for (int y = 0;y < size;y++) {
							int u = x - k;
							int v = y - k;
							if (mask[x][y])
								list[idx] = hueBuffer[i + u][j + v]*10;idx += 1;
						}
					}

					quick_sort(list, 0, idx - 1);
					float value = list[k]/10.;


					// Mask loop End
					intensity[i][j] = value;
				}
			}
			for (int i = 0;i < imgHeight;i++) {
				for (int j = 0;j < imgWidth;j++) {
					hueBuffer[i][j] = intensity[i][j];
				}
			}
		}
		else {
			if (rgb_option) {
				rgb_red = new float*[imgHeight];
				rgb_green = new float*[imgHeight];
				rgb_blue = new float*[imgHeight];
				for (int i = 0;i < imgHeight;i++) {
					rgb_red[i] = new float[imgWidth];
					rgb_green[i] = new float[imgWidth];
					rgb_blue[i] = new float[imgWidth];
				}
				for (int i = k;i < imgHeight - k;i++) {
					for (int j = k;j < imgWidth - k;j++) {
						float list[50];
						float list2[50];
						float list3[50];
						int idx = 0;
						int idx2 = 0;
						int idx3 = 0;
						for (int x = 0;x < size;x++) {
							for (int y = 0;y < size;y++) {
								int u = x - k;
								int v = y - k;
								if (mask[x][y]) {
									list[idx] = rgbBuffer[i + u][j + v].rgbRed;idx += 1;
									list2[idx2] = rgbBuffer[i + u][j + v].rgbGreen;idx2 += 1;
									list3[idx3] = rgbBuffer[i + u][j + v].rgbBlue;idx3 += 1;
								}
							}
						}

						quick_sort(list, 0, idx - 1);
						quick_sort(list2, 0, idx2 - 1);
						quick_sort(list3, 0, idx3 - 1);
						float value = list[k];
						float value2 = list2[k];
						float value3 = list3[k];


						// Mask loop End
						rgb_red[i][j] = value;
						rgb_green[i][j] = value2;
						rgb_blue[i][j] = value3;
					}
				}
			}
			else {
				for (int i = k;i < imgHeight - k;i++) {
					for (int j = k;j < imgWidth - k;j++) {
						float list[50];
						int idx = 0;
						for (int x = 0;x < size;x++) {
							for (int y = 0;y < size;y++) {
								int u = x - k;
								int v = y - k;
								if (mask[x][y])
									list[idx] = intenBuffer[i + u][j + v]*255;idx += 1;
							}
						}

						quick_sort(list, 0, idx - 1);
						float value = list[k]/255;


						// Mask loop End
						intensity[i][j] = value;
					}
				}
				intenBuffer = intensity;
			}
		}
	}
}

void CMFCApplication1View::OnSize3()
{
	size = 3;
}


void CMFCApplication1View::OnSize5()
{
	size = 5;
}


void CMFCApplication1View::OnSize7()
{
	size = 7;
}

void CMFCApplication1View::OnShapeBlock()
{
	
	mask = new float*[size];
	for (int i = 0;i < size;i++) {
		mask[i] = new float[size];
	}

	for (int i = 0;i < size;i++) {
		for (int j = 0;j < size;j++) {
			mask[i][j] = 1;
		}
	}
}

void CMFCApplication1View::OnShapeCross()
{
	
}

void CMFCApplication1View::OnShapeDiamond()
{
	
}

void CMFCApplication1View::OnShapeXshape()
{
	
}

void CMFCApplication1View::OnMedianProcess()
{
	median();
	viewType = 4;
	Invalidate(FALSE);
}

void CMFCApplication1View::OnColoroptionIntensity()
{
	hue_option = FALSE;
	rgb_option = FALSE;
	OnRgbtohsiChange();
	median();
	OnRgbtohsiHsi2rgb();
	viewType = 3;
	Invalidate(FALSE);
}

void CMFCApplication1View::OnColoroptionRgb()
{
	hue_option = FALSE;
	rgb_option = TRUE;
	median();
	viewType = 3;
	Invalidate(FALSE);
}


void CMFCApplication1View::OnColorprocessHsi()
{
	rgb_option = FALSE;
	hue_option = TRUE;
	OnRgbtohsiChange();
	median();
	OnRgbtohsiHsi2rgb();
	viewType = 3;
	Invalidate(FALSE);
}


void CMFCApplication1View::OnMaskHB12()
{
	float a = 1.2;

	mask = new float*[3];
	for (int i = 0;i < 3;i++) {
		mask[i] = new float[3];
	}
	
	for (int i = 0;i < 3;i++) {
		for (int j = 0;j < 3;j++) {
			if (i == 1 && j == 1)
				mask[i][j] = a + 8;
			else
				mask[i][j] = -1;
		}
	}
	size = 3;
	Mask();
	if (!is_color) {
		viewType = 4;
		Invalidate(FALSE);
	}
	else {
		viewType = 3;
		Invalidate(FALSE);
	}
}


void CMFCApplication1View::OnMask22()
{
	float a = 1.5;

	mask = new float*[3];
	for (int i = 0;i < 3;i++) {
		mask[i] = new float[3];
	}

	for (int i = 0;i < 3;i++) {
		for (int j = 0;j < 3;j++) {
			if (i == 1 && j == 1)
				mask[i][j] = a + 8;
			else
				mask[i][j] = -1;
		}
	}
	size = 3;
	Mask();
	if (!is_color) {
		viewType = 4;
		Invalidate(FALSE);
	}
	else {
		viewType = 3;
		Invalidate(FALSE);
	}
}

void CMFCApplication1View::OnMorphologyDilation()
{
	int k = (size - 1) / 2;
	if (!is_color) {

		intensity = new float*[imgHeight];
		for (int i = 0;i < imgHeight;i++) {
			intensity[i] = new float[imgWidth];
		}

		for (int i = k;i < imgHeight - k;i++) {
			for (int j = k;j < imgWidth - k;j++) {
				float list[50];
				int idx = 0;
				for (int x = 0;x < size;x++) {
					for (int y = 0;y < size;y++) {
						int u = x - k;
						int v = y - k;
						if (mask[x][y])
							list[idx] = rgbBuffer[i + u][j + v].rgbBlue;idx += 1;
					}
				}

				quick_sort(list, 0, idx - 1);
				float value = list[idx - 1];
				
				// Mask loop End
				intensity[i][j] = value;
			}
		}
		viewType = 4;
		Invalidate(FALSE);
	}
}


void CMFCApplication1View::OnMorphologyErosion()
{
	int k = (size - 1) / 2;
	if (!is_color) {

		intensity = new float*[imgHeight];
		for (int i = 0;i < imgHeight;i++) {
			intensity[i] = new float[imgWidth];
		}

		for (int i = k;i < imgHeight - k;i++) {
			for (int j = k;j < imgWidth - k;j++) {
				float list[50];
				int idx = 0;
				for (int x = 0;x < size;x++) {
					for (int y = 0;y < size;y++) {
						int u = x - k;
						int v = y - k;
						if (mask[x][y])
							list[idx] = rgbBuffer[i + u][j + v].rgbBlue;idx += 1;
					}
				}

				quick_sort(list, 0, idx - 1);
				float value = list[0];

				// Mask loop End
				intensity[i][j] = value;
			}
		}
		viewType = 4;
		Invalidate(FALSE);
	}
}


void CMFCApplication1View::OnStructureBlock()
{
	mask = new float*[size];
	for (int i = 0;i < size;i++) {
		mask[i] = new float[size];
	}

	for (int i = 0;i < size;i++) {
		for (int j = 0;j < size;j++) {
			mask[i][j] = 1;
		}
	}
}


void CMFCApplication1View::OnSize4()
{
	size = 3;
}


float** x_mask;
float** y_mask;
void CMFCApplication1View::EdgeOperator() {
	int k = (size - 1) / 2;

	OnRgbtohsiChange();
	 
	intensity = new float*[imgHeight];
	for (int i = 0;i < imgHeight;i++) {
		intensity[i] = new float[imgWidth];
	}
	for (int i = k;i < imgHeight-k;i++) {
		for (int j = k;j < imgWidth-k;j++) {

			double x_value = 0.; 
			double y_value = 0.;
							  // Mask loop Start
			for (int x = 0;x < size;x++) {
				for (int y = 0;y < size;y++) {
					int u = x - k;
					int v = y - k;
					y_value += y_mask[x][y] * intenBuffer[i + u][j + v]*255;
					x_value += x_mask[x][y] * intenBuffer[i + u][j + v]*255;
					
				}
			}
			// Mask loop End
			intensity[i][j] = sqrt(x_value*x_value + y_value*y_value);
			intensity[i][j] = 255 - intensity[i][j];
		}
	}
}


void CMFCApplication1View::OnEdgedetectionSobel()
{
	size = 3;
	x_mask = new float*[3];
	for (int i = 0;i < 3;i++) {
		x_mask[i] = new float[3];
	}
	y_mask = new float*[3];
	for (int i = 0;i < 3;i++) {
		y_mask[i] = new float[3];
	}

	y_mask[2][0] = -1; y_mask[2][2] = -1; x_mask[2][0] = -1; x_mask[0][0] = -1;
	x_mask[0][2] = 1; x_mask[2][2] = 1; y_mask[0][0] = 1; y_mask[0][2] = 1;
	x_mask[1][0] = -2; y_mask[2][1] = -2;
	x_mask[1][2] = 2; y_mask[0][1] = 2;
	for (int i = 0;i < 3;i++) {
		for (int j = 0;j < 3;j++) {
			if (i == 1)
				y_mask[i][j] = 0;
			if (j == 1)
				x_mask[i][j] = 0;
		}
	}

	EdgeOperator();
	viewType = 4;
	Invalidate(FALSE);

}


void CMFCApplication1View::OnEdgedetectionPrewitt()
{
	size = 3;
	x_mask = new float*[3];
	for (int i = 0;i < 3;i++) {
		x_mask[i] = new float[3];
	}
	y_mask = new float*[3];
	for (int i = 0;i < 3;i++) {
		y_mask[i] = new float[3];
	}

	y_mask[2][0] = -1; y_mask[2][2] = -1; x_mask[2][0] = -1; x_mask[0][0] = -1;
	x_mask[0][2] = 1; x_mask[2][2] = 1; y_mask[0][0] = 1; y_mask[0][2] = 1;
	x_mask[1][0] = -1; y_mask[2][1] = -1;
	x_mask[1][2] = 1; y_mask[0][1] = 1;
	for (int i = 0;i < 3;i++) {
		for (int j = 0;j < 3;j++) {
			if (i == 1)
				y_mask[i][j] = 0;
			if (j == 1)
				x_mask[i][j] = 0;
		}
	}

	EdgeOperator();
	viewType = 4;
	Invalidate(FALSE);
}


void CMFCApplication1View::LoG(int size, float** filter) { 

	OnRgb2hsiGrayscale();

	int k = (size - 1) / 2;
	float** intensity_ = new float*[imgHeight];
	for (int i = 0;i < imgHeight;i++) {
		intensity_[i] = new float[imgWidth];
	}
	int idx = 0;
	for (int i = k;i < imgHeight - k;i++) {
		for (int j = k;j < imgWidth - k;j++) {

		    float value = 0;
			idx++;
			for (int x = 0;x < size;x++) {
				for (int y = 0;y < size;y++) {
					int u = x - k;
					int v = y - k;
					if (i + u >= 0 && j + v >= 0) {
						if (i + u < imgHeight && j + v < imgWidth)
							value = value + intensity[i + u][j + v]*filter[x][y];
					}
				}

			}
			value = value < 0 ? 0 : 255;
			intensity_[i][j] = value;
		}
	}
	for (int i = 0;i < imgHeight;i++) {
		delete[] intensity[i];
	}
	intensity = intensity_;

	for (int i = 0;i < size; i++) {
		delete[] filter[i];
	}
	delete[] filter;
}

float** logFilter(int size, double sigmanum=0) {
	float** filter = new float*[size];
	for (int i = 0;i < size;i++) {
		filter[i] = new float[size];
	}

	int k = (size - 1) / 2;

	double sigma = sigmanum;
	if (!sigmanum) 
		sigma = size / 6.;

	for (int i = 0;i < size;i++) {
		for (int j = 0;j < size;j++) {
			double x = i - k;
			double y = j - k;
			filter[i][j] = (1 / 3.14*pow(sigma, 4))*(1 - (pow(x, 2) + pow(y, 2)) / (2 * pow(sigma, 2)))*exp(-1 * ((pow(x, 2) + pow(y, 2)) / (2 * pow(sigma, 2))));
			//filter[i][j] = -1*( x*x + y*y - 2*sigma*sigma ) * exp(-1 * (x*x + y*y) / (2 * sigma*sigma)) / pow(sigma, 4);
			std::cout << filter[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return filter;

}

void CMFCApplication1View::OnLog3()
{
	/*float** filter = new float*[3];
	filter[0] = new float[3]{ 0,-1,0 };
	filter[1] = new float[3]{ -1,4,-1 };
	filter[2] = new float[3]{ 0,-1,0 };*/
	float** filter = logFilter(3);

	LoG(3,filter);
	viewType = 4;
	Invalidate(FALSE);
}


void CMFCApplication1View::OnLog5()
{
	/*float** filter = new float*[5];
	for (int i = 0;i < 5;i++) {
		switch (i) {
		case 0:
		case 4:
			filter[i] = new float[5]{ 0,0,-1,0,0 };
			break;
		case 1:
		case 3:
			filter[i] = new float[5]{ 0,-1,-2,-1,0 };
			break;
		case 2:
			filter[i] = new float[5]{ -1,-2,16,-2,-1 };
			break;
		}
	}*/
	float** filter = logFilter(5);
	LoG(5,filter);
	viewType = 4;
	Invalidate(FALSE);
}


void CMFCApplication1View::OnLog7()
{
	float** filter = logFilter(7);
	LoG(7, filter);
	viewType = 4;
	Invalidate(FALSE);
}


void CMFCApplication1View::OnLog9()
{
	float** filter = logFilter(9,1.4);
	LoG(9, filter);
	viewType = 4;
	Invalidate(FALSE);
}


void CMFCApplication1View::OnLog11()
{
	float** filter = logFilter(11);
	LoG(11, filter);
	viewType = 4;
	Invalidate(FALSE);
}


void CMFCApplication1View::OnLog15()
{
	float** filter = logFilter(15);
	LoG(15, filter);
	viewType = 4;
	Invalidate(FALSE);
}



void CMFCApplication1View::OnLogMultiple()
{
	float** log3;
	float** log5;
	float** log7;
	float** log11;
	float** log15;

	LoG(3, logFilter(3));
	log3 = intensity;

	/*LoG(5, logFilter(5));
	log5 = intensity;*/

	LoG(7, logFilter(7));
	log7 = intensity;

	/*LoG(11, logFilter(11));
	log11 = intensity;*/

	LoG(15, logFilter(15));
	log15 = intensity;

	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			float value = (log3[i][j] + /*log5[i][j] +*/ log7[i][j] + /*log11[i][j] +*/ log15[i][j]) / 3;
			value = value < 50 ? 0 : 255;
			intensity[i][j] = value;
		}
	}
	viewType = 4;
	Invalidate(FALSE);


}


void CMFCApplication1View::OnEdgedetectionCanny()
{ 
	std::string imgpath;
	imgpath = path;
	std::cout << imgpath;
	cv::Mat image = cv::Mat(imgHeight, imgWidth, CV_8U);
	image = cv::imread(imgpath);

	cv::Mat out1, out2;
	cv::Canny(image, out1,150, 255,3);
	cv::Canny(image, out2, 150, 255,3,TRUE);

	cv::bitwise_not(out1, out1);
	cv::bitwise_not(out2, out2);

	cv::Mat logout;
	
	
	cv::imshow("out1", out1);
	cv::imshow("out2", out2);
	

}
