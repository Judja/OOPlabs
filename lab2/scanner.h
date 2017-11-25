/************************************************************************
*file: scanner.h
*synopsis: declarations for scanner functions, types, constants
*author: Denys Fedorchenko
*created: 19/11/2017
*last modified: 20/11/2017
************************************************************************/

#include <stddef.h> // for  size_t
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <io.h>

#ifndef _HEADER_H
#define _HEADER_H


typedef struct {
	int id;//унікальний ідентифікатор
	char manufacturer[20];// виготовлювач
	int year;	 // рік виготовлення
	char model[20];// найменування моделі
	float price;// ціна
	int x_size;// горизонтальний розмір області сканування
	int y_size;// вертикальний розмір області сканування
	int amount;//кількіть на складі(нехай)
} SCAN_INFO;

typedef struct {
	int rec_nmb;//number of records
	SCAN_INFO *recs;//records 
}RECORD_SET;


/* function prototypes */

int create_db(const char* csv, const char *db);//DONE
int make_index(const char *db, const char *field_name);//DONE
RECORD_SET * get_recs_by_index(const char *dba, char *indx_field);//DONE
void reindex(const char *db);//DONE
void del_scanner(const char *db, int id);//DONE
void add_scanner(const char *db, const char* scanner_str);//DONE
void print_db(const char *db);//DONE
RECORD_SET* select(const char *db, const char *field, const char *value);//DONE
void print_rec_set(RECORD_SET *rs);
#endif