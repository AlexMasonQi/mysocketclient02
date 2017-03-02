#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _SCK_HANDLE_
{
	char version[64];
	unsigned char *buffer;
	char ip[128];
	int bufferlen;
	int port;
}_SCK_HANDLE_;

///<summary>
///�ͻ��˳�ʼ��
///</summary>
_declspec(dllexport)
int cltSocketInit2(void **handle)
{
	int ret = 0;
	printf("The function socket client initialization begins!\n");

	_SCK_HANDLE_ *hdl = (_SCK_HANDLE_ *)malloc(sizeof(_SCK_HANDLE_));
	if (hdl == NULL)
	{
		printf("Distribute menory failed!");
		ret -1;
	}
	memset(hdl, 0, sizeof(_SCK_HANDLE_));
	strcpy(hdl->ip, "192.168.4.253");
	strcpy(hdl->version, "10.0.0.1");
	hdl->port = 8082;
	*handle = hdl;

	printf("The function socket client initialization ends!\n");

	return ret;
}

///<summary>
///�ͻ��˷���
///</summary>
_declspec(dllexport)
int cltSocketSend2(void *handle, unsigned char *buf, int buflen)
{
	int ret = 0;
	if (handle == NULL || buf == NULL)
	{
		ret = -1;
	}
	_SCK_HANDLE_ *hdl = (_SCK_HANDLE_ *)handle;
	hdl->buffer = (char *)malloc(sizeof(char) *buflen);
	if (hdl->buffer == NULL)
	{
		printf("Distribute memory failed!");
		return -1;
	}
	memset(hdl->buffer, 0, buflen);
	memcpy(hdl->buffer, buf, buflen);
	hdl->bufferlen = buflen;

	return ret;
}

///<summary>
///�ͻ��˽��ձ���
///</summary>
_declspec(dllexport)
int cltSocketRev2(void *handle, unsigned char **buf, int *buflen)
{
	int ret = 0;
	char *temp = NULL;
	if (handle == NULL || buf == NULL || buflen == NULL)
	{
		ret = -1;
	}
	_SCK_HANDLE_ *hdl = (_SCK_HANDLE_ *)handle;
	temp = (unsigned char *)malloc(sizeof(unsigned char) *(hdl->bufferlen));
	if (temp == NULL)
	{
		printf("Distribute memory failed!");
		return -1;
	}
	memset(temp, 0, hdl->bufferlen);
	memcpy(temp, hdl->buffer, hdl->bufferlen);
	*buf = temp;
	*buflen = hdl->bufferlen;

	return ret;
}

///<summary>
///�ͷſͻ��˽��ջ������ڴ�
///</summary>
_declspec(dllexport)
int cltSocketRev2Free(unsigned char **buf)
{
	int ret = 0;
	if (buf == NULL)
	{
		ret = -1;
	}
	if (*buf != NULL)
	{
		free(*buf);
	}
	*buf = NULL;
	return ret;
}

///<sumary>
///�ͻ����ͷ���Դ
///</summary>
_declspec(dllexport)
int cltSocketDestory2(void **handle)
{
	int ret = 0;
	if (handle == NULL)
	{
		ret = -1;
	}
	_SCK_HANDLE_ *sck = NULL;
	sck = *handle;
	if (sck != NULL)
	{
		free(sck);
	}
	*handle = NULL;
	return ret;
}

int main()
{
	system("pause");
	return 0;
}