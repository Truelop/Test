#ifndef TEST_ALL_H
#define TEST_ALL_H

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>
#include <CUnit/Console.h>

int init_suite(void);
int clean_suite(void);

#include "max.test.h"

#endif /* TEST_ALL_H */