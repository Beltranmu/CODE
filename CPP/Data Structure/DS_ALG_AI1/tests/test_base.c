// test_base.h
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//
// Generates data to be used in the battery test

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ABGS_MemoryManager/abgs_memory_manager.h"

#define _TEST_PRINT_DATA

#define kNumberOfStoragePtrTest_A	10
#define kNumberOfStoragePtrTest_B	5
#define kNumberOfStoragePtrTest_C	7
#define kIterationsBigData			10

const u16 kSingleSizeData1		= 5;
const u16 kSingleSizeData2		= 15;
const u16 kSingleSizeData3		= 10;
const u16 kSingleSizeData4		= 117;
const u16 kSingleSizeBigData	= (117 * kIterationsBigData);

const u16 kMaxAsciiChars		= 26;
const u16 kMaxIntegerChars		= 10;

struct test_data_s {
	void *single_ptr_data_1;
	void *single_ptr_data_2;
	void *single_ptr_data_3;
	void *single_ptr_data_4;
	void *single_ptr_big_data;
	void *storage_ptr_test_A[kNumberOfStoragePtrTest_A];
	void *storage_ptr_test_B[kNumberOfStoragePtrTest_B];
	void *storage_ptr_test_C[kNumberOfStoragePtrTest_C];
} TestData;

u8 *abgs_msg = (u8 *)"\n   ABGS - Artificial Bytes Game Studio\n  **  Tap Pop Balloon - Combo Party  **\n      Available for Android and iOS\n\n";

void* TESTBASE_allocateData(u16 size) {
	void *data = NULL;
	data = MM->malloc(size);
	if (NULL == data) {
		printf("ERROR: Cannot allocate %d bytes of memory for data test\n", size);
		return NULL;
	}
	return data;
}

void* TESTBASE_generateDataAscii(u8 char_from, u16 size, bool end_of_string) {
	u16 eos = end_of_string ? 1 : 0;
	void *data = TESTBASE_allocateData(size + eos);
	if (NULL == data)
		return NULL;

	u8 *runner = (u8 *)data;
	for (u16 i = 0; i < size; ++i) {
		*runner = char_from + (i % kMaxAsciiChars);
		runner++;
	}
	if (true == end_of_string)
		*runner = 0;
	return data;
}

void* TESTBASE_generateDataString(u8 *string) {
	u16 size = strlen(string) + 1;
	void *data = TESTBASE_allocateData(size);
	if (NULL == data)
		return NULL;
	strcpy(data, string);
	return data;
}

void* TESTBASE_generateDataIntegerAsString(u16 value) {
	void *data = TESTBASE_allocateData(kMaxIntegerChars);
	if (NULL == data)
		return NULL;
	itoa(value, data, 10);
	return data;
}

void TESTBASE_generateDataForTest() {
	MM->status();
	printf("  ============= GENERATING DATA =============\n");
	//////////////////////////////////////////////////////////////////////////////////////////////
	// Allocate memory for single pointers
	printf("  + Allocating memory for single pointers\n");
	TestData.single_ptr_data_1 = MM->malloc(sizeof(u8) * kSingleSizeData1); // abcde
	if (NULL == TestData.single_ptr_data_1) {
		printf("\n create returned a null node in TestData.single_ptr_data_1");
		return -1;
	}
	TestData.single_ptr_data_2 = MM->malloc(sizeof(u8) * kSingleSizeData2); // fghijklmnopqrst
	if (NULL == TestData.single_ptr_data_2) {
		printf("\n create returned a null node in TestData.single_ptr_data_2");
		return -1;
	}
	TestData.single_ptr_data_3 = MM->malloc(sizeof(u8) * kSingleSizeData3); // 0123456789
	if (NULL == TestData.single_ptr_data_3) {
		printf("\n create returned a null node inTestData.single_ ptr_data_3");
		return -1;
	}
	TestData.single_ptr_data_4 = MM->malloc(sizeof(u8) * kSingleSizeData4); // ABGS
	if (NULL == TestData.single_ptr_data_4) {
		printf("\n create returned a null node in TestData.single_ptr_data_4");
		return -1;
	}
	TestData.single_ptr_big_data = MM->malloc(sizeof(u8) * kSingleSizeBigData);
	if (NULL == TestData.single_ptr_big_data) {
		printf("\n create returned a null node in TestData.single_ptr_big_data");
		return -1;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	// Fill single pointers
	printf("  + Filling single pointers\n");
	u8 *data = (u8 *) TestData.single_ptr_data_1;
	for (u8 i = 0; i < kSingleSizeData1; ++i) {
		*(data++) = 'a' + i;
	}
	data = (u8 *)TestData.single_ptr_data_2;
	for (u8 i = 0; i < kSingleSizeData2; ++i) {
		*(data++) = 'f' + i;
	}
	data = (u8 *)TestData.single_ptr_data_3;
	for (u8 i = 0; i < kSingleSizeData3; ++i) {
		*(data++) = '0' + i;
	}
	strcpy(TestData.single_ptr_data_4, abgs_msg);
	strcpy(TestData.single_ptr_big_data, "");
	//////////////////////////////////////////////////////////////////////////////////////////////
	// Allocate and memory pointers of TEST A
	printf("  + Generating Integers as String\n");
	for (u32 n = 0; n < kNumberOfStoragePtrTest_A; ++n) {
		TestData.storage_ptr_test_A[n] = TESTBASE_generateDataIntegerAsString(1 << (n + 5));
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	// Allocate and memory pointers of TEST B
	printf("  + Generating ASCII as String\n");
	u8 char_from = 'a';
	u8 str_len = 3;
	for (u8 n = 0; n < kNumberOfStoragePtrTest_B; ++n) {
		TestData.storage_ptr_test_B[n] = TESTBASE_generateDataAscii(char_from, str_len, true);
		printf("        - [%d] from '%c' to '%c' with length %d\n", n, char_from, (char_from + str_len - 1), str_len);
		char_from += str_len;
		str_len++;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	// Allocate and memory pointers of TEST C
	printf("  + Generating Strings\n");
	TestData.storage_ptr_test_C[0] = TESTBASE_generateDataString("\n   ABGS - ");
	TestData.storage_ptr_test_C[1] = TESTBASE_generateDataString("Artificial Bytes Game Studio\n");
	TestData.storage_ptr_test_C[2] = TESTBASE_generateDataString("  **  Tap Pop Balloon - ");
	TestData.storage_ptr_test_C[3] = TESTBASE_generateDataString("Combo Party  **\n");
	TestData.storage_ptr_test_C[4] = TESTBASE_generateDataString("      Available for Android");
	TestData.storage_ptr_test_C[5] = TESTBASE_generateDataString(" and iOS\n");
	TestData.storage_ptr_test_C[6] = TESTBASE_generateDataString("\n");
	//////////////////////////////////////////////////////////////////////////////////////////////
	// Print data
#ifdef _TEST_PRINT_DATA
	// Print all data
	printf("\n");
	printf("  ============== PRINTING DATA ==============\n");
	printf("TestData.fixed_ptr_data_1 (allocated %d bytes) = ", kSingleSizeData1);
	data = (u8 *)TestData.single_ptr_data_1;
	for (u8 i = 0; i < kSingleSizeData1; ++i) {
		printf("%c", *(data++));
	}
	printf("\n");
	printf("TestData.fixed_ptr_data_2 (allocated %d bytes) = ", kSingleSizeData2);
	data = (u8 *)TestData.single_ptr_data_2;
	for (u8 i = 0; i < kSingleSizeData2; ++i) {
		printf("%c", *(data++));
	}
	printf("\n");
	data = (u8 *)TestData.single_ptr_data_3;
	printf("TestData.fixed_ptr_data_3 (allocated %d bytes) = ", kSingleSizeData3);
	for (u8 i = 0; i < kSingleSizeData3; ++i) {
		printf("%c", *(data++));
	}
	printf("\n");
	printf("TestData.fixed_ptr_data_4 (allocated %d bytes) = ", kSingleSizeData4);
	data = (u8 *)TestData.single_ptr_data_4;
	for (u8 i = 0; i < kSingleSizeData4; ++i) {
		printf("%c", *(data++));
	}
	printf("TestData.single_ptr_big_data (allocated %d bytes) = \"%s\"\n", kSingleSizeBigData, (u8 *)TestData.single_ptr_big_data);
	printf("\n");
	for (u8 n = 0; n < kNumberOfStoragePtrTest_A; ++n) {
		printf("TestData.storage_ptr_test_A[%d] (allocated %d bytes) = \"%s\"\n", n, (strlen(TestData.storage_ptr_test_A[n]) + 1), TestData.storage_ptr_test_A[n]);
	}
	printf("\n");
	for (u8 n = 0; n < kNumberOfStoragePtrTest_B; ++n) {
		printf("TestData.storage_ptr_test_B[%d] (allocated %d bytes) = \"%s\"\n", n, (strlen(TestData.storage_ptr_test_B[n]) + 1), TestData.storage_ptr_test_B[n]);
	}
	printf("\n");
	for (u8 n = 0; n < kNumberOfStoragePtrTest_C; ++n) {
		printf("TestData.storage_ptr_test_C[%d] (allocated %d bytes) = \"%s\"\n", n, (strlen(TestData.storage_ptr_test_C[n]) + 1), TestData.storage_ptr_test_C[n]);
	}
#endif
	printf("  ===========================================\n");
}

void TESTBASE_freeDataForTest() {
	if (NULL != TestData.single_ptr_data_1)
		MM->free(TestData.single_ptr_data_1);
	if (NULL != TestData.single_ptr_data_2)
		MM->free(TestData.single_ptr_data_2);
	if (NULL != TestData.single_ptr_data_3)
		MM->free(TestData.single_ptr_data_3);
	if (NULL != TestData.single_ptr_data_4)
		MM->free(TestData.single_ptr_data_4);
	if (NULL != TestData.single_ptr_big_data)
		MM->free(TestData.single_ptr_big_data);
	for (u8 n = 0; n < kNumberOfStoragePtrTest_A; ++n) {
		if (NULL != TestData.storage_ptr_test_A[n])
			MM->free(TestData.storage_ptr_test_A[n]);
	}
	for (u8 n = 0; n < kNumberOfStoragePtrTest_B; ++n) {
		if (NULL != TestData.storage_ptr_test_B[n])
			MM->free(TestData.storage_ptr_test_B[n]);
	}
	for (u8 n = 0; n < kNumberOfStoragePtrTest_C; ++n) {
		if (NULL != TestData.storage_ptr_test_C[n])
			MM->free(TestData.storage_ptr_test_C[n]);
	}
}


/*Hay que modificarla para seg�n el codigo de error imprima un mensaje*/
void TESTBASE_printFunctionResult(void *address, u8 *msg, s16 error_type) {
	u8 *error_msg = (u8 *)MM->malloc(sizeof(u8) * 100); //If error in line 250, perhaps more than 100.
	if (NULL == error_msg) {
		printf(" [TEST] Error allocating error mesage\n");
		return;
	}

  char*  error_code[21];
  error_code[0] = "Everything OK";
  error_code[1] = "MemoryNode NULL, Error";
  error_code[2] = "File Error";
  error_code[3] = "Error, Size 0";
  error_code[4] = "Error, no data";
  error_code[5] = "Vector NULL, Error";
  error_code[6] = "Error, Vector is full :D";
  error_code[7] = "Error, None fuction";
  error_code[8] = "Circular Vector NULL, Error";
  error_code[9] = "Movable Head Vector NULL, Error";
  error_code[10]= "List NULL, Error";
  error_code[11]= "List FULL, Error";
  error_code[12]= "List Empty, Error";
  error_code[13]= "Stack NULL, Error";
  error_code[14]= "Stack FULL, Error";
  error_code[15]= "Queue NULL, Error";
  error_code[16]= "Queue FULL, Error";
  error_code[17]= "Queue Empty, Error";
  error_code[18]= "Logger NULL, Error";
  error_code[19]= "Logger Empty, Error";
  error_code[20]= "No Memory Available";
 

  
  
  strcpy((char *)error_msg, error_code[error_type / (-10)]);
	printf(" [TEST] Function %s returns (%s) ", msg , error_msg);

	printf(" in address = %p", address);
	printf("\n");
	MM->free(error_msg);
}
