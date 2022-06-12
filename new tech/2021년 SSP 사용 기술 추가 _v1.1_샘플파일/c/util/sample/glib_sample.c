#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>




/**********************************************
 * 예제 1) 양방향 linked list 숫자 처리
 **********************************************/

// 비교 함수
static gint GCompareFunc_1(gconstpointer a, gconstpointer b){
	return GPOINTER_TO_INT(a)-GPOINTER_TO_INT(b);
}

static void _test1(){
	// 반드시 NULL로 초기화 필요함.
	GList *number_list = NULL, *temp;
	
	// 숫자 추가
	number_list = g_list_append (number_list, GINT_TO_POINTER(345));
	number_list = g_list_append (number_list, GINT_TO_POINTER(234));
	number_list = g_list_append (number_list, GINT_TO_POINTER(123));

	// 순차 조회
	for(temp=number_list ; temp ; temp=temp->next){
		printf("숫자 [%d]\n", (int)temp->data);
	}
	
	// 정렬
	number_list = g_list_sort(number_list, GCompareFunc_1);
	
	// 순차 조회
	for(temp=number_list ; temp ; temp=temp->next){
		printf("숫자 [%d]\n", GPOINTER_TO_INT(temp->data));
	}
	
	// g_list_free() : 리스트 자체만 헤제함. 문자열 메모리는 사용자가 직접 관리
	g_list_free(number_list);
	number_list=NULL;
	
	return;
}





/**********************************************
 * 예제 2) 양방향 linked list 문자열 처리 (데이터 heap 사용 안함)
 **********************************************/

// 비교 함수
static gint GCompareFunc_2(gconstpointer a, gconstpointer b){
	return strcmp((char*)a,(char*)b);
}

static void _test2(){
	// 반드시 NULL로 초기화 필요함.
	GList *string_list = NULL, *temp;
	
	// 문자열 추가 : (heap 사용 안함)
	string_list = g_list_append (string_list, "third");
	string_list = g_list_append (string_list, "first");
	string_list = g_list_append (string_list, "second");

	// 순차 조회
	for(temp=string_list ; temp ; temp=temp->next){
		printf("문자열 [%s]\n", (char*)temp->data);
	}
	
	// 정렬
	string_list = g_list_sort(string_list, GCompareFunc_2);
	
	// 순차 조회
	for(temp=string_list ; temp ; temp=temp->next){
		printf("문자열 [%s]\n", (char*)temp->data);
	}
	
	// g_list_free() : 리스트 자체만 헤제함. 문자열 메모리는 사용자가 직접 관리
	g_list_free(string_list);
	string_list=NULL;
	
	return;
}




/**********************************************
 * 예제 3) 양방향 linked list 구조체 처리 (데이터 heap 사용)
 **********************************************/
 
typedef struct SampleData{
	char *teststr;
	int index;
} SampleData;

// 비교 함수
static gint GCompareFunc_3(gconstpointer a, gconstpointer b){
	return strcmp(((SampleData*)a)->teststr,((SampleData*)(char*)b)->teststr);
}

// 구조체 free 함수
static void _free_func(gpointer data){
	SampleData *val = (SampleData*)data;
	
	if(val){
		if(val->teststr) free(val->teststr);
		free(val);
	}
}

static void _test3(){
	SampleData *struct1, *struct2, *struct3;
	// 반드시 NULL로 초기화 필요함.
	GList *struct_list = NULL, *temp;
	
	// data 생성 : heap malloc by malloc() and strdup()
	struct1 = (SampleData*)malloc(sizeof(SampleData));
	struct2 = (SampleData*)malloc(sizeof(SampleData));
	struct3 = (SampleData*)malloc(sizeof(SampleData));
	struct1->teststr = strdup("val3");
	struct1->index = 1;
	struct2->teststr = strdup("val2");
	struct2->index = 2;
	struct3->teststr = strdup("val1");
	struct3->index = 3;

	// 구조체 추가
	struct_list = g_list_append (struct_list, struct1);
	struct_list = g_list_append (struct_list, struct2);
	struct_list = g_list_append (struct_list, struct3);

	// 순차 조회
	for(temp=struct_list ; temp ; temp=temp->next){
		printf("구조체 [%s:%d]\n", ((SampleData*)temp->data)->teststr, ((SampleData*)temp->data)->index);
	}
	
	// 정렬
	struct_list = g_list_sort(struct_list, GCompareFunc_3);
	
	// 순차 조회
	for(temp=struct_list ; temp ; temp=temp->next){
		printf("구조체 [%s:%d]\n", ((SampleData*)temp->data)->teststr, ((SampleData*)temp->data)->index);
	}
	
	// g_list_free_full() : 리스트 및 data까지 free.
	g_list_free_full(struct_list, _free_func);
	struct_list=NULL;
	
	return;
}




int main(int argc, char *argv[]){
	
	_test1();
	
	_test2();
	
	_test3();
	
	return 0;
}

