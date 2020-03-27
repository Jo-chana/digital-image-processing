
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
END_MESSAGE_MAP()



// CMFCApplication1View construction/destruction
RGBQUAD** rgbBuffer; //-> 이미지를 저장할 변수
float** rgb_red;
float** rgb_green;
float** rgb_blue;
int imgHeight; //-> 이미지 높이 정보
int imgWidth; //-> 이미지 너비 정보
BITMAPINFOHEADER bmpInfo; //-> BMP 정보 헤더
BITMAPFILEHEADER bmpHeader;// -> BMP 파일 헤더	
						   /*동적 할당하는 포인터 배열은 반드시 '생성자'와 '소멸자' 에
						   null 로 초기화 및 해제를 수행해야 한다.*/

float** hueBuffer; //이미지 색조 정보
float** satuBuffer; //이미지 채도 정보
float** intenBuffer; //이미지 밝기 정보
int viewType;

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

			}
		}		
		
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


void CMFCApplication1View::OnImageBmp()
{
	
	//1. 파일 다이얼로그로부터 BMP 파일 입력
	CFileDialog dlg(TRUE, ".bmp", NULL, NULL, "Bitmap File(*.bmp)|*.bmp||");
	if (IDOK != dlg.DoModal())
		return;
	CString filename = dlg.GetPathName();
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
	CFileDialog dlg(TRUE, ".jpg", NULL, NULL, "Jpeg File(*.jpg)|*jpg||");
	if (IDOK != dlg.DoModal()) return;
	CString filename = dlg.GetPathName();

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
	Invalidate(TRUE);
}


void CMFCApplication1View::OnRgbtohsiChange()
{   //1. rgbBuffer 에 이미지가 들어있는 지 여부 확인
	if (rgbBuffer == NULL)
		OnImageBmp(); //rgbBuffer 에 데이터가 없는 경우, 로드 함수를 호출하여 이미지 획득

	//2. 변수 메모리 할당

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
				total = (0.5*(r - g + r - b) / sqrt(r - g)*(r - g) + (r - b)*(g - b));
				hueBuffer[i][j] = acos((double)total);
				if (b > g) {
					hueBuffer[i][j] = 6.28 - hueBuffer[i][j];
				}
			}
		}
	}
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


void CMFCApplication1View::OnPointprocessingContraststretching()
{
	//1. 원래 이미지를 HSI 컬러스페이스로 변환: RGB
	satuBuffer = new float*[imgHeight];toHSI 함수 출력 제외 부분

	if (rgbBuffer == NULL)
		OnImageBmp();

	hueBuffer = new float*[imgHeight];
	intenBuffer = new float*[imgHeight];

	for (int i = 0;i < imgHeight;i++) {
		hueBuffer[i] = new float[imgWidth];
		satuBuffer[i] = new float[imgWidth];
		intenBuffer[i] = new float[imgWidth];
	}

	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			float r = rgbBuffer[i][j].rgbRed;
			float g = rgbBuffer[i][j].rgbGreen;
			float b = rgbBuffer[i][j].rgbBlue;
			//대비개선: intensity level * 1.5
			intenBuffer[i][j] = min(1,((r + g + b) / (float)(3 * 255))*1.5);
			float total = r + g + b;
			r = r / total; g = g / total; b = b / total;
			satuBuffer[i][j] = 1 - 3 * (r > g ? (g > b ? b : g) : (r > b ? b : r));
			if (r == g&&g == b) {
				hueBuffer[i][j] = 0;satuBuffer[i][j] = 0;
			}
			else {
				total = (0.5*(r - g + r - b) / sqrt(r - g)*(r - g) + (r - b)*(g - b));
				hueBuffer[i][j] = acos((double)total);
				if (b > g) {
					hueBuffer[i][j] = 6.28 - hueBuffer[i][j];
				}
			}
		}
	}
	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			hueBuffer[i][j] = hueBuffer[i][j] * 255 / (3.14 * 2);
			satuBuffer[i][j] = satuBuffer[i][j] * 255;
			intenBuffer[i][j] = intenBuffer[i][j] * 255;
		}
	}


	//3. 변환된 HSI 컬러를 RGB 컬러스페이스로 변환

	
	// 새로운 이미지 변수 메모리 할당

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
			float R = rgbBuffer[i][j].rgbRed; 
			float G = rgbBuffer[i][j].rgbGreen;
			float B = rgbBuffer[i][j].rgbBlue;
			float S = satuBuffer[i][j];
			float H = hueBuffer[i][j];
			float I = intenBuffer[i][j];
			
			if (H <= 120) {
				B = (float)(1 - S) / 3;
				R = (float)(1 + S*cos(H) / cos(60 - H)) / 3;
				G = (float)1 - (R + B);
			}
			else if (H <= 240) {
				H = H - 120;
				G = (1 + S*cos(H) / cos(60 - H)) / 3;
				R = (1 - S) / 3;
				B = 1 - (R + G);
			}
			//정규화
			R = R * 255;
			G = G * 255;
			B = B * 255;

			//원본 이미지 데이터를 보존하기 위해 새로운 변수에 저장
			rgb_red[i][j] = R;
			rgb_green[i][j] = G;
			rgb_blue[i][j] = B;
		}
	}
	//4. 출력
	viewType = 3;
	Invalidate(FALSE);
}
