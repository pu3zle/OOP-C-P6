#pragma once
#include "..\models\model.h"
#include "..\validator\validator.h"

int add(ListMP* limp, char* name, char* producator, int quantity);

int validate_unique(const ListMP* limp, char* name);

void l_add(ListMP* limp, m_prim* matPrim);

int search(ListMP* limp, char* name);

int modify(ListMP* limp, char* name, char* modify, int op);

int del(ListMP* limp, char* name);

int char2int(char* q);

int sort_name(ListMP* limp);

int sort_quantity(ListMP* limp);

extern void* new(size_t size);

extern void delete(void* memory, size_t size);

extern void PrintCurrentUsage();


