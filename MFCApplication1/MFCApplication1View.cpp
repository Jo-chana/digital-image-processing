
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
RGBQUAD** rgbBuffer; //-> �̹����� ������ ����
float** rgb_red;
float** rgb_green;
float** rgb_blue;
int imgHeight; //-> �̹��� ���� ����
int imgWidth; //-> �̹��� �ʺ� ����
BITMAPINFOHEADER bmpInfo; //-> BMP ���� ���
BITMAPFILEHEADER bmpHeader;// -> BMP ���� ���	
						   /*���� �Ҵ��ϴ� ������ �迭�� �ݵ�� '������'�� '�Ҹ���' ��
						   null �� �ʱ�ȭ �� ������ �����ؾ� �Ѵ�.*/

float** hueBuffer; //�̹��� ���� ����
float** satuBuffer; //�̹��� ä�� ����
float** intenBuffer; //�̹��� ��� ����
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
	Invalidate(TRUE);
}


void CMFCApplication1View::OnRgbtohsiChange()
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
				total = (0.5*(r - g + r - b) / sqrt(r - g)*(r - g) + (r - b)*(g - b));
				hueBuffer[i][j] = acos((double)total);
				if (b > g) {
					hueBuffer[i][j] = 6.28 - hueBuffer[i][j];
				}
			}
		}
	}
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


void CMFCApplication1View::OnPointprocessingContraststretching()
{
	//1. ���� �̹����� HSI �÷������̽��� ��ȯ: RGB
	satuBuffer = new float*[imgHeight];toHSI �Լ� ��� ���� �κ�

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
			//��񰳼�: intensity level * 1.5
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
			//����ȭ
			R = R * 255;
			G = G * 255;
			B = B * 255;

			//���� �̹��� �����͸� �����ϱ� ���� ���ο� ������ ����
			rgb_red[i][j] = R;
			rgb_green[i][j] = G;
			rgb_blue[i][j] = B;
		}
	}
	//4. ���
	viewType = 3;
	Invalidate(FALSE);
}
