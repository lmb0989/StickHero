#include "StringUtil.h"
#include <WinNls.h>
//#define CP_ACP     0
//#define CP_UTF8    65001

char* StringUtil::G2UTF(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

//int code_convert(const char *from_charset, const char *to_charset, const char *inbuf, size_t inlen, char *outbuf, size_t outlen)
//{
//	iconv_t cd;
//	const char *temp = inbuf;
//	const char **pin = &temp;
//	char **pout = &outbuf;
//	memset(outbuf, 0, outlen);
//	cd = iconv_open(to_charset, from_charset);
//	if (cd == 0) return -1;
//	if (iconv(cd, pin, &inlen, pout, &outlen) == -1) return -1;
//	iconv_close(cd);
//	return 0;
//}
//
//std::string u2a(const char *inbuf)
//{
//	size_t inlen = strlen(inbuf);
//	char * outbuf = new char[inlen * 2 + 2];
//	std::string strRet;
//	if (code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
//	{
//		strRet = outbuf;
//	}
//	delete[] outbuf;
//	return strRet;
//}
//
//std::string a2u(const char *inbuf)
//{
//	size_t inlen = strlen(inbuf);
//	char * outbuf = new char[inlen * 2 + 2];
//	std::string strRet;
//	if (code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, inlen * 2 + 2) == 0)
//	{
//		strRet = outbuf;
//	}
//	delete[] outbuf;
//	return strRet;
//}