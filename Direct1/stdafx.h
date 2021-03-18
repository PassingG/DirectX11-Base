// 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일

#pragma once

#include "targetver.h"


//거의 사용되지 않는 내용들은 Windows 헤더에서 자동 제외시키는 구문
#define WIN32_LEAN_AND_MEAN

//Windows 헤더 파일
#include <Windows.h>

// C 런타임 헤더 파일들
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// 프로그램에 필요한 추가 헤더는 여기에서 참조한다.
#include "DxDefine.h"