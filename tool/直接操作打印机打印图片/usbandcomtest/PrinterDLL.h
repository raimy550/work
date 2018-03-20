/******************************************************************* 
 *  ��ǰ�汾:0.5.0.1128 
 *  ����: lakerszhy(lakerszhy@gmail.com)
 *  ����: 2013-11-28
 ******************************************************************/  

#ifdef PRINTERDLL_EXPORTS
#define PRINTERDLL_API __declspec(dllexport)
#else
#define PRINTERDLL_API __declspec(dllimport)
#endif

//��ӡ������
enum PRINTER_TYPE {POS_OPEN_BYUSB_PORT, POS_OPEN_NETPORT};

//��ӡ��״̬
enum PRINTER_STATUS {NORMAL, LESS_PAPER, NO_PAPER, NOT_CONNECT, CUTTER_ERROR, ABNORMAL_TEMPERATURE, UNKOWN};

//HRI��ӡλ��
enum HRI_POSITION {NOT_PRINT, ABOVE_BARCODE, BELOW_BARCODE, ABOVE_BELOW_BARCODE};

//�ַ�ģʽ
#define CHARACTER_MODEL_COMPRESSION		0x00000001 //ѹ��ASCII
#define CHARACTER_MODEL_BOLDFACE		0x00000008 //�Ӵ�
#define CHARACTER_MODEL_DOUBLE_HEIGHT	0x00000010 //˫�ָ�
#define CHARACTER_MODEL_DOUBLE_WIDTH	0x00000020 //˫�ֿ�
#define CHARACTER_MODEL_UNDERLINE		0x00000080 //�»���

#define POS_SUCCESS                     1001 // ����ִ�гɹ�
#define POS_FAIL                        1002 // ����ִ��ʧ��

#define POS_ERROR_INVALID_HANDLE        1101 // �˿ڻ��ļ��ľ����Ч
#define POS_ERROR_INVALID_PARAMETER     1102 // ������Ч

extern "C" 
{
	/************************************************************************/
	//�������򿪴�ӡ���˿�      
	//������szPrinterName��[in] ָ���� null ��β�Ĵ�ӡ�����ƻ�˿�����
	//			���printerTypeΪPOS_OPEN_BYUSB_PORT��szPrinterNameΪ"USB"
	//			���printerTypeΪPOS_OPEN_NETPORT��szPrinterNameΪ��ӡ��ip��ַ
	//		printerType:[in] ��ӡ������,POS_OPEN_BYUSB_PORT��POS_OPEN_NETPORT
	// ����ֵ���ɹ�����POS_SUCCESS
	//         ʧ�ܷ���POS_ERROR_INVALID_PARAMETER��INVALID_HANDLE_VALUE
	/************************************************************************/
	PRINTERDLL_API int Wz_Open(const char* szPrinterName, enum PRINTER_TYPE printerType);

	/************************************************************************/
	//�������رմ�ӡ���˿�
	//��������
	//����ֵ���ɹ�����POS_SUCCESS
	//		  ʧ�ܷ���POS_FAIL��POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_Close();

	/************************************************************************/
	//��������λ��ӡ��
	//��������
	//����ֵ���ɹ�����POS_SUCCESS
	//		  ʧ�ܷ���POS_FAIL��POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_Reset();

	/************************************************************************/
	//��������ӡszText�е�����
	//������szText��[in] ��Ҫ��ӡ������
	//����ֵ���ɹ�����POS_SUCCESS
	//		  ʧ�ܷ���POS_FAIL��POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_Print(const char* szText);

	/************************************************************************/
	//��������ӡ����ֽnRows��
	//������nRows��[in] ��ֽ����, 0-20֮��
	//����ֵ���ɹ�����POS_SUCCESS
	//		  ʧ�ܷ���POS_FAIL��POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_FreedPaper(const int nRows);

	/************************************************************************/
	//��������Ǯ��
	//��������
	//����ֵ���ɹ�����POS_SUCCESS
	//		  ʧ�ܷ���POS_FAIL��POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_OpenCashBox();

	/************************************************************************/
	//��������ӡEAN13��
	//������szCode��[in] ��Ҫ��ӡ��13λ����
	//		hriPosition��[in] HRI��ӡλ��
	//					 NOT_PRINT������ӡHRI
	//					 ABOVE_BARCODE��HRI������֮��
	//				 	 BELOW_BARCODE��HRI����������
	//					 ABOVE_BELOW_BARCODE����������������涼��ӡHRI
	//����ֵ���ɹ�����POS_SUCCESS
	//		  ʧ�ܷ���POS_FAIL��POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_PrintBarCode(const char* szCode, enum HRI_POSITION hriPosition);

	/************************************************************************/
	//��������������߶�ΪnHeight��nHeight/8mm��nHeight/203Ӣ�磩
	//������nHeight��[in] ����߶ȣ�0-255��Ĭ��216
	//����ֵ���ɹ�����POS_SUCCESS
	//		  ʧ�ܷ���POS_FAIL��POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_SetBarCodeHeight(const int nHeight);

	/************************************************************************/
	//����������������ΪnWidth
	//������nWidth��[in] ����߶ȣ�2-6��Ĭ��2
	//����ֵ���ɹ�����POS_SUCCESS
	//		  ʧ�ܷ���POS_FAIL��POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_SetBarCodeWidth(const int nWidth);

	/************************************************************************/
	//����������/������ֽ��
	//������bEnable��[in] �Ƿ�������ֽ��
	//				 true�� ������ֽ��
	//				 false��������ֽ��
	//����ֵ���ɹ�����POS_SUCCESS
	//		  ʧ�ܷ���POS_FAIL��POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_EnableFeedButton(bool bEnable);

	/************************************************************************/
	//��������ֽ
	//��������
	//����ֵ���ɹ�����POS_SUCCESS
	//		  ʧ�ܷ���POS_FAIL��POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_CutPaper();

	/************************************************************************/
	//�����������м��ΪnSpace/203Ӣ�磨nSpace/8mm��
	//	    ��nSpace̫Сʱ���иߵ����ַ��߶�
	//      ��nSpace����ָ����Χ�����������
	//������nSpace��[in] �м�� 0-255��Ĭ��27��3.37mm��
	//����ֵ���ɹ�����POS_SUCCESS
	//		  ʧ�ܷ���POS_FAIL��POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_SetLineSpace(const int nSpace);

	/************************************************************************/
	//�����������ַ��Ҽ��ΪnSpace��
	//      ��nSpace����ָ����Χ�����������
	//������nSpace��[in] �м�� 0-32��Ĭ��0
	//����ֵ���ɹ�����POS_SUCCESS
	//		  ʧ�ܷ���POS_FAIL��POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_SetWordSpace(const int nSpace);

	/************************************************************************/
	//��������ô�ӡ��״̬
	//��������
	//����ֵ��NORMAL����ӡ������
	//		  LESS_PAPER��ֽ����
	//		  NO_PAPER��ȱֽ
	//		  NOT_CONNECT����ӡ��δ����
	//		  CUTTER_ERROR���е�����
	//		  ABNORMAL_TEMPERATURE����ӡ���¶��쳣
	//		  UNKOWN��δ֪����
	/************************************************************************/
	PRINTERDLL_API int Wz_GetStatus();

	/************************************************************************/
	//�����������ַ�ģʽ
	//������dwCharModel��[in] ����Ϊ����ֵ��
	//			CHARACTER_MODEL_COMPRESSION��	ѹ��ASCII
	//			CHARACTER_MODEL_BOLDFACE��		�Ӵ�
	//			CHARACTER_MODEL_DOUBLE_HEIGHT��	˫�ָ�
	//			CHARACTER_MODEL_DOUBLE_WIDTH��	˫�ֿ�
	//			CHARACTER_MODEL_UNDERLINE��		�»���
	//����ֵ���ɹ�����POS_SUCCESS
	//		  ʧ�ܷ���POS_FAIL��POS_ERROR_INVALID_HANDLE
	/************************************************************************/
	PRINTERDLL_API int Wz_SetCharModel(const DWORD dwCharModel);

};