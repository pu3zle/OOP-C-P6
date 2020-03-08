#pragma warning(disable:4996)
#pragma once
#include "service.h"
#include <stdio.h>
#include <io.h>

void ui_add(ListMP* limp, char* params);
void ui_modify(ListMP* limp, char* params);
void ui_del(ListMP* limp, char* params);
void ui_c_view(ListMP* limp, char* params);
void ui_o_view(ListMP* limp, char* params);
void run(ListMP* limp);