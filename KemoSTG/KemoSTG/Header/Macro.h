#pragma once
#define PI 3.1415926535897932
#define CAPTION_STRING _T("KemoSTG")	// キャプションテキスト
#define VERSION_STRING _T("Alpha 1")	// バージョン

#ifdef _WIN64
#define AUTO_INT long long int	// 64ビットバイナリの場合、64ビット変数を使用
#else
#define AUTO_INT int		// 32ビットバイナリの場合、32ビット変数を使用
#endif	// _WIN64

#ifdef _UNICODE
#define tstring wstring	// Unicode対応の場合、ワイド文字列クラスを使用
#else
#define tstring string	// Unicode非対応の場合、通常文字列クラスを使用
#endif	// _UNICODE