#ifndef _MY_SQLITE_H_
#define _MY_SQLITE_H_

#include <string.h>
#include <stdio.h>
#include "sqlite3.h"

#define TCP_IP_PORT_PASSWORD    "/mnt/area_infor.db"
#define TABLE_NAME    			 "area_table"


int sqlite_open(const char *file, sqlite3 **db);

int  sqlite_write(const char *sql,sqlite3 *db);
   
int sqlite_create(const char *table_name,const char *prefence,sqlite3 *db);

int sqlite_insert(const char *table_name,const char *prefence,sqlite3 *db);

int sqlite_update(const char *table_name,const char *prefence, const char *qualify,sqlite3 *db);	

int sqlite_delete(const char *table_name,const char *qualify,sqlite3 *db);	
			
int sqlite_read(const  char *table_name, sqlite3 *db);

char* sqlite_select(const char *table_name, const char *prefence, const char *condition, sqlite3 *db);

int init_area_table(const char* filename);

int sqlite_update_table( const char *name,  const char *value );

int save_client_area_infor(const char *info);

char* get_info_from_table(const char *name,  const char *value);

int init_table(void);

#endif


