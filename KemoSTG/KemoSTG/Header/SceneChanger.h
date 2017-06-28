#pragma once
#include "Include.h"

template<typename T> class iSceneChanger {
public:
	virtual ~iSceneChanger() = 0;
	virtual void ChangeScene(T NextScene) = 0;
};

template<typename T> iSceneChanger<T>::~iSceneChanger() {

}