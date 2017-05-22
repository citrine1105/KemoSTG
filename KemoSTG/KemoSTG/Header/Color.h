#pragma once
#include "Include.h"

enum eColorName {
	eColorName_Black,

	eColorName_TotalNum
};

class cColor {
private:
	cColor() = default;
	~cColor() = default;
public:
	cColor(const cColor&) = delete;
	cColor& operator = (const cColor&) = delete;
	cColor(cColor&&) = delete;
	cColor& operator = (cColor&&) = delete;

	static cColor& get_instance() {
		static cColor inst;
		return inst;
	}

	unsigned int GetColorRaw(eColorName ColorName);
};