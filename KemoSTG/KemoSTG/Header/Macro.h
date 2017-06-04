#pragma once
#define PI 3.1415926535897932	// 円周率
#define CAPTION_STRING _T("KemoSTG")	// キャプションテキスト
#define VERSION_STRING _T("Alpha 1")	// バージョン
#define DX_ARCHIVE_KEY_STRING _T("TestKey")	// DXアーカイブ展開キー

#define RADIAN_TO_DEGREE(value) (PI / 180.0 * value)
#define DEGREE_TO_RADIAN(value) (value / 180.0 * PI)

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