#pragma once
#include "model.h"
#include "validator.h"

int add(ListMP* limp, char* name, char* producator, int quantity);

int validate_unique(const ListMP* limp, char* name);

void print_all(ListMP* limp);

