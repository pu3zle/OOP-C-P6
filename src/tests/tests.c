#include "tests.h"

void TestCreateM_Prim()
{
	MatPrim* Test_mprim = MatPrimCreate("faina", "panemar", 23);
	assert(strcmp(Test_mprim->name, "faina") == 0);
	assert(strcmp(Test_mprim->provider, "panemar") == 0);
	assert(Test_mprim->quantity == 23);
	assert(Test_mprim->name_length == 5);
	assert(Test_mprim->provider_length == 7);
	destroyM_Prim(Test_mprim);

}

void TestSetters()
{
	MatPrim* Test_mprim = MatPrimCreate("faina", "panemar", 23);
	set_name(Test_mprim, "cereale");
	set_provider(Test_mprim, "donald");
	set_quantity(Test_mprim, 4);

	assert(strcmp(Test_mprim->name, "cereale") == 0);
	assert(strcmp(Test_mprim->provider, "donald") == 0);
	assert(Test_mprim->quantity == 4);

	destroyM_Prim(Test_mprim);
}

void TestListDestroy()
{
	MatPrim* T_mprim = MatPrimCreate("faina", "panemar", 23);
	ListMP T_list = l_create();
	l_add(&T_list, T_mprim);
	destroyListMP(&T_list);
}

void TestAdd()
{
	ListMP limp = l_create();
	assert(add(&limp, " ", "asd", 23) == 1);
	assert(add(&limp, "asd", " ", 23) == 2);
	assert(add(&limp, "asd", "asd", -3) == 4);
	
	add(&limp, "asd", "asd", 23);
	assert(strcmp(limp.matPrim[0]->name, "asd") == 0);
	assert(strcmp(limp.matPrim[0]->name, "asd") == 0);
	assert(limp.matPrim[0]->quantity == 23);
	assert(limp.matPrim[0]->name_length == 3);
	assert(limp.matPrim[0]->provider_length == 3);

	add(&limp, "asd", "asd", 2);
	assert(strcmp(limp.matPrim[0]->name, "asd") == 0);
	assert(strcmp(limp.matPrim[0]->provider, "asd") == 0);
	assert(limp.matPrim[0]->quantity == 25);
	assert(limp.matPrim[0]->name_length == 3);
	assert(limp.matPrim[0]->provider_length == 3);

	destroyListMP(&limp);

}

void TestSearch()
{
	ListMP limp = l_create();
	add(&limp, "asd", "asd", 23);
	assert(search(&limp, "nasaud") == -1);
	assert(search(&limp, "asd") == 0);

	destroyListMP(&limp);
}

void TestModify()
{
	ListMP limp = l_create();
	add(&limp, "asd", "asd", 23);
	assert(modify(&limp, "asd", " ", 0) == 1);
	assert(modify(&limp, "asd", " ", 1) == 2);
	assert(modify(&limp, "asd", "-32", 2) == 4);
	modify(&limp, "asd", "tractor", 0);
	assert(modify(&limp, "asd", "JohnDeer", 1) == -4);
	modify(&limp, "tractor", "JohnDeer", 1);
	modify(&limp, "tractor", "123", 2);

	assert(strcmp(limp.matPrim[0]->name, "tractor") == 0);
	assert(strcmp(limp.matPrim[0]->provider, "JohnDeer") == 0);
	assert(limp.matPrim[0]->quantity == 123);

	destroyListMP(&limp);
}

void TestDel()
{
	ListMP limp = l_create();
	add(&limp, "asd", "asd", 23);
	add(&limp, "afd", "asd", 23);
	add(&limp, "agd", "asd", 23);
	add(&limp, "ahd", "asd", 23);
	add(&limp, "aed", "asd", 23);

	assert(limp.size == 6);

	assert(del(&limp, "azbest") == -4);
	del(&limp, "agd");
	assert(limp.length == 4);
	assert(strcmp(limp.matPrim[0]->name, "asd") == 0);
	assert(strcmp(limp.matPrim[1]->name, "afd") == 0);
	assert(strcmp(limp.matPrim[2]->name, "ahd") == 0);
	assert(strcmp(limp.matPrim[3]->name, "aed") == 0);

	del(&limp, "aed");
	assert(strcmp(limp.matPrim[0]->name, "asd") == 0);
	assert(strcmp(limp.matPrim[1]->name, "afd") == 0);
	assert(strcmp(limp.matPrim[2]->name, "ahd") == 0);


	del(&limp, "afd");
	del(&limp, "asd");
	assert(strcmp(limp.matPrim[0]->name, "ahd") == 0);
	

	destroyListMP(&limp);
}

void TestSortName()
{
	ListMP limp = l_create();

	assert(sort(&limp, 0, NameComparison) == -1);

	add(&limp, "asd", "asd", 23);
	add(&limp, "afd", "asd", 23);
	add(&limp, "agd", "asd", 23);
	add(&limp, "ahd", "asd", 23);

	sort(&limp, 0, NameComparison);
	assert(strcmp(limp.matPrim[0]->name, "afd") == 0);
	assert(strcmp(limp.matPrim[1]->name, "agd") == 0);
	assert(strcmp(limp.matPrim[2]->name, "ahd") == 0);
	assert(strcmp(limp.matPrim[3]->name, "asd") == 0);

	destroyListMP(&limp);
}

void TestSortQuantity()
{
	ListMP limp = l_create();
	add(&limp, "asd", "asd", 2);
	add(&limp, "afd", "asd", 4);
	add(&limp, "agd", "asd", 1);
	add(&limp, "ahd", "asd", 3);

	sort(&limp, 1, QuantityComparison);

	assert(strcmp(limp.matPrim[0]->name, "afd") == 0);
	assert(strcmp(limp.matPrim[1]->name, "ahd") == 0);
	assert(strcmp(limp.matPrim[2]->name, "asd") == 0);
	assert(strcmp(limp.matPrim[3]->name, "agd") == 0);

	destroyListMP(&limp);

}

void runTests()
{
	TestCreateM_Prim();
	TestSetters();
	TestListDestroy();
	TestAdd();
	TestSearch();
	TestModify();
	TestDel();
	TestSortName();
	TestSortQuantity();
}