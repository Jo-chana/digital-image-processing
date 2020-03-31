
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
#define _USE_MATH_DEFINES
#include <cmath>

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
END_MESSAGE_MAP()



// CMFCApplication1View construction/destruction
RGBQUAD** rgbBuffer; //-> �̹����� ������ ����
float** rgb_red; // ��ȯ�� �̹��� R ��ġ
float** rgb_green; // ��ȯ�� �̹��� G ��ġ
float** rgb_blue; // ��ȯ�� �̹��� B ��ġ
int imgHeight; //-> �̹��� ���� ����
int imgWidth; //-> �̹��� �ʺ� ����
BITMAPINFOHEADER bmpInfo; //-> BMP ���� ���
BITMAPFILEHEADER bmpHeader;// -> BMP ���� ���	
						   /*���� �Ҵ��ϴ� ������ �迭�� �ݵ�� '������'�� '�Ҹ���' ��
						   null �� �ʱ�ȭ �� ������ �����ؾ� �Ѵ�.*/

float** hueBuffer; //�̹��� ���� ����
float** satuBuffer; //�̹��� ä�� ����
float** intenBuffer; //�̹��� ��� ����
int viewType = 0; // ȭ�� ��� ���� ����

int* histogram; // ������׷� ��ġ ����

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
	ASSERT_VALID(pDoc);//������ ���� �״�� ���
	if (!pDoc)
		return;

	if (rgbBuffer != NULL) { //�̹��� ����ִ� ��� ���
		for (int i = 0;i < imgHeight;i++) { //�̹��� ������ ��ŭ ���鼭 �� �ȼ��� ���
			for (int j = 0;j < imgWidth;j++) {//rgbBuffer�� ����ߴ� 2�� for��
				POINT p; //����� �ȼ��� ��ġ ����
				p.x = j;
				p.y = i;
				pDC->SetPixel(p, RGB(rgbBuffer[i][j].rgbRed, rgbBuffer[i][j].rgbGreen, rgbBuffer[i][j].rgbBlue));
				//�ȼ� ��ġ p�� RGB ���� �Է�
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
	
	//1. ���� ���̾�α׷κ��� BMP ���� �Է�
	CFileDialog dlg(TRUE, ".bmp", NULL, NULL, "Bitmap File(*.bmp)|*.bmp||");
	if (IDOK != dlg.DoModal())
		return;
	CString filename = dlg.GetPathName();
	if(rgbBuffer != NULL){//�̹� �Ҵ�� ��� �޸� ����
		for (int i = 0;i < imgHeight;i++)
			delete [] rgbBuffer[i];
		delete [] rgbBuffer;
	}

	//2. ������ �����Ͽ� ���� ���� ȹ��
	CFile file;
	file.Open(filename, CFile::modeRead);
	file.Read(&bmpHeader, sizeof(BITMAPFILEHEADER));
	file.Read(&bmpInfo, sizeof(BITMAPINFOHEADER));
	imgWidth = bmpInfo.biWidth;
	imgHeight = bmpInfo.biHeight;

	//3. �̹����� ������ ���� �Ҵ�(2���� �迭) [�̹��� ����*�̹��� �ʺ� ��ŭ �Ҵ�]
	rgbBuffer = new RGBQUAD*[imgHeight];
	for (int i = 0;i < imgHeight;i++)
		rgbBuffer[i] = new RGBQUAD[imgWidth];

	//4. �̹����� �ʺ� 4�� ������� üũ
	// BMP ���� ���δ� 4byte �̾�� �Ѵ�.
	// �� �ȼ��� 3����Ʈ(R,G,B)�̹Ƿ�, ����(m_width)*3 �� 4�� ������� �ƴ��� �˾ƾ� ��
	// b4byte : 4byte �� ������� �ƴ��� �ȴ�.
	// upbyte : 4byte �� ���ڶ�� ����Ʈ��.
	bool b4byte = false;
	int upbyte = 0;
	if ((imgWidth * 3) % 4 == 0) {
		// 4�� ����� �������� ���
		b4byte = true;
		upbyte = 0;
	}
	else {
		// 4�� ����� �������� �ʴ� ���
		b4byte = false;
		upbyte = 4 - (imgWidth * 3) % 4;
	}

	//5. �ȼ� �����͸� ���Ϸκ��� �о��
	BYTE data[3];
	for (int i = 0; i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			file.Read(&data, 3);
			//�̹��� �Ųٷ� ����Ǿ� �����Ƿ� �Ųٷ� �о��
			rgbBuffer[imgHeight - i - 1][j].rgbBlue = data[0];
			rgbBuffer[imgHeight - i - 1][j].rgbGreen = data[1];
			rgbBuffer[imgHeight - i - 1][j].rgbRed = data[2];

		}
		if (b4byte == false)
		{
			//���ΰ� 4byte ����� �ƴϸ� ������ ���� �д´�
			file.Read(&data, upbyte);
		}
	}
	file.Close(); //���� �ݱ�
	viewType = 0;
	Invalidate(TRUE); // ȭ�� ����

}


BYTE* LoadJpegFromOpenFile(FILE *fp, BITMAPINFOHEADER *pbh, UINT *pWidth, UINT *pHeight) {
	//���Ϸκ��� JPG ���� ȹ��
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

	//BMP �ε�� ���������� rgbBuffer�� NULL�� �ƴ� ��� �޸� ���� �ڵ� �߰��ϱ�
	if (rgbBuffer != NULL) {//�̹� �Ҵ�� ��� �޸� ����
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
	//BMP �ε�� ���������� rgbBuffer�� �̹��� ������ ��ŭ �޸� �Ҵ� �ڵ� �߰�
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


void CMFCApplication1View::OnRgbtohsiChange() // �Լ� ���� �������� �ۼ�
{   //1. rgbBuffer �� �̹����� ����ִ� �� ���� Ȯ��
	if (rgbBuffer == NULL)
		OnImageBmp(); //rgbBuffer �� �����Ͱ� ���� ���, �ε� �Լ��� ȣ���Ͽ� �̹��� ȹ��

	//2. ���� �޸� �Ҵ�

	hueBuffer = new float*[imgHeight];
	satuBuffer = new float*[imgHeight];
	intenBuffer = new float*[imgHeight];

	for (int i = 0;i < imgHeight;i++) {
		hueBuffer[i] = new float[imgWidth];
		satuBuffer[i] = new float[imgWidth];
		intenBuffer[i] = new float[imgWidth];
	}

	//3. RGB to HSI �� ��ȯ
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
					hueBuffer[i][j] = 2*M_PI - hueBuffer[i][j];
				}
			} // �Լ� ������ ���� ����ȭ �� ����� �Լ������� �и��Ͽ���.
		}
	}
	
}

void CMFCApplication1View::OnRgb2hsiChange()
{
	OnRgbtohsiChange();

	//4.��� �� ���� ����ȭ: ��� ��, ���� ������ [0,255]�� ����
	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			hueBuffer[i][j] = hueBuffer[i][j] * 255 / (3.14 * 2);
			satuBuffer[i][j] = satuBuffer[i][j] * 255;
			intenBuffer[i][j] = intenBuffer[i][j] * 255;
		}
	}

	//5.���
	viewType = 2;
	Invalidate(FALSE);

}

void CMFCApplication1View::OnRgbtohsiHsi2rgb() // �Լ� ���� �������� �ۼ�
{
	//3. ��ȯ�� HSI �÷��� RGB �÷������̽��� ��ȯ


	// ���ο� �̹��� ���� �޸� �Ҵ�

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
				r = 1 / 3;
				g = 1 / 3;
				b = 1 / 3;
			}
			else {

				if (H <= 2 * M_PI / 3) { // 0 <= H <= 2/3Pi
					b = (1 - S) / 3;
					r = (1 + (S*cos((double)H) / cos((double)M_PI / 3 - H))) / 3;
					g = 1 - (r + b);

				}
				else if (H <= 4 * M_PI / 3) { // 2/3Pi < H <= 4/3Pi
					H = H - 2 * M_PI / 3;
					r = (1 - S) / 3;
					g = (1 + (S*cos((double)H) / cos((double)M_PI / 3 - H))) / 3;
					b = 1 - (r + g);

				}
				else { // 4/3Pi < H =< 2Pi
					H = H - 4 * M_PI / 3;
					g = (1 - S) / 3;
					b = (1 + (S*cos((double)H) / cos((double)M_PI / 3 - H))) / 3;
					r = 1 - (g + b);

				}
			}

			R = min(255, 255 * 3 * r * I);
			G = min(255, 255 * 3 * g * I);
			B = min(255, 255 * 3 * b * I);

			//���� �̹��� �����͸� �����ϱ� ���� ���ο� ������ ����
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
			intenBuffer[i][j] = min(1, intenBuffer[i][j] * 1.5); // ��� 1.5��
		}
	}


	//3. ��ȯ�� HSI �÷��� RGB �÷������̽��� ��ȯ
	OnRgbtohsiHsi2rgb(); // �ش� �Լ� �ּ� ����
	
	
	//4. ���
	viewType = 3;
	Invalidate(FALSE);
}


void CMFCApplication1View::OnPointprocessingSaturationinjecting()
{
	OnRgbtohsiChange();
	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			satuBuffer[i][j] = min(1, satuBuffer[i][j] * 2); // ä�� 2�� ����
		}
	}

	OnRgbtohsiHsi2rgb();
	//4. ���
	viewType = 3;
	Invalidate(FALSE);
}


void CMFCApplication1View::OnPointprocessingHistogram()
{
	
}


void CMFCApplication1View::OnHistogramColor()
{
	OnRgbtohsiChange(); // HSI ���� ȹ��

	if (histogram==NULL)
		histogram = new int[360]; // Hue 360�� ������
	for (int i = 0;i < 360;i++) {
		histogram[i] = 0;
	}

	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			int color = (int)hueBuffer[i][j] * 180 / M_PI;
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
			int color = (int)hueBuffer[i][j] * 180 / M_PI;
			hueBuffer[i][j] = (float)histogram[color] * 255 / max;
		}
	}
	viewType = 2;
	Invalidate(FALSE);
}


void CMFCApplication1View::OnHistogramIntensity()
{
	OnRgbtohsiChange(); // HSI ���� ȹ��

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
	int max = 0;
	for (int i = 0; i < 256;i++) {
		if (histogram[i] > max)
			max = histogram[i];
	}
	for (int i = 0; i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			int inten = (int)(intenBuffer[i][j] * 255);
			hueBuffer[i][j] = (float)histogram[inten] * 255 / max;
		}
	}
	viewType = 2;
	Invalidate(FALSE);
}








void CMFCApplication1View::OnPointprocessingFacedetection()
{
	/*
	�Ǻλ� ����
	Saturation >= 0.2
	Hue < 50��
	Intensity/Saturation 0.5 ~ 3.0 -> deleted
	*/

	OnRgbtohsiChange();
	for (int i = 0;i < imgHeight;i++) {
		for (int j = 0;j < imgWidth;j++) {
			float S = satuBuffer[i][j];
			float H = hueBuffer[i][j];
			float I = intenBuffer[i][j];

			if (S < 0.2 || S > 0.7)
				intenBuffer[i][j] = 0;
			
			if (H > 0.88)
				intenBuffer[i][j] = 0;

			//if (I / S < 0.5 || I / S > 3.0)
				//intenBuffer[i][j] = 0;
		}
	}
	OnRgbtohsiHsi2rgb();
	viewType = 3;
	Invalidate(FALSE);

}
