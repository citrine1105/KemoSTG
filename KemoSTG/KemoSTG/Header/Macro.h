#pragma once
#define PI 3.1415926535897932	// 円周率
#define REFRESH_RATE 60.0	// リフレッシュレート

#define CAPTION_STRING _T("KemoSTG")	// キャプションテキスト
#define VERSION_STRING _T("0.02")	// バージョン
#define DX_ARCHIVE_KEY_STRING _T("TestKey")	// DXアーカイブ展開キー

#define TO_DEGREE(value) (PI / 180.0 * value)
#define TO_RADIAN(value) (value / 180.0 * PI)

#ifdef _WIN64
#define AUTO_INT long long int	// 64ビットバイナリの場合、64ビット変数を使用
#define AUTO_INT_MAX LLONGMAX
#define AUTO_INT_MIN LLONGMIN
#define AUTO_UINT_MAX ULLONG_MAX
#else
#define AUTO_INT int		// 32ビットバイナリの場合、32ビット変数を使用
#define AUTO_INT_MAX INT_MAX
#define AUTO_INT_MIN INT_MIN
#define AUTO_UINT_MAX UINT_MAX
#endif	// _WIN64

#ifdef _UNICODE
#define tstring wstring	// Unicode対応の場合、ワイド文字列クラスを使用
#define to_tstring to_wstring
#else
#define tstring string	// Unicode非対応の場合、通常文字列クラスを使用
#define to_tstring to_string
#endif	// _UNICODE