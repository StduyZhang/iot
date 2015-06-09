//Ubuntu 12.04.4 LTS
//Linux bob 3.2.0-64-generic
//(gcc version 4.6.3)

#include "my_sqlite.h"

 int result;
	
 char *errmsg=NULL;

	
int sqlite_open(const char *filename, sqlite3 **db) 
{   
    if( sqlite3_open(filename, db) != SQLITE_OK )
    {
    	fprintf(stderr, "Open database error: %s\n", sqlite3_errmsg(*db)); 
		sqlite3_free(errmsg); 
		return -1;
	}
	
	return 0;	
}	


int sqlite_write(const char *sql,sqlite3 *db)
{
	result = sqlite3_exec( db,sql,NULL, NULL, &errmsg );		
	if( result != SQLITE_OK )	 
	{ 
	 	if(strcmp(errmsg,"column name is not unique")==0) return -1;//don't print this errmsg 
			
	 	printf( "Operate table failure,error code:%d,reason:%s\n", result, errmsg );
		sqlite3_free(errmsg); 
	 	return -1;
	}	
	
	return 0;
}   

int sqlite_create(const char *table_name,const char *prefence,sqlite3 *db)
{
	//"create table if not exists Tcp_Table(Ftp_Ip ,Ftp_Port,Password);"
	char sql[128]= {0};
	snprintf(sql,sizeof(sql),"create table if not exists %s ( %s );",table_name, prefence);	
	return(sqlite_write(sql,db));
}



int sqlite_insert(const char *table_name,const char *prefence,sqlite3 *db)	
{
	// "insert into Tcp_Table values ('192.168.0.233','7879','123456');"
	char sql[128]= {0};
	snprintf(sql,sizeof(sql),"insert into %s values( %s );",table_name, prefence);		
	return(sqlite_write(sql,db));		
}

int sqlite_update(const char *table_name,const char *prefence, const char *condition,sqlite3 *db)	
{		
	//"update Tcp_Table set Password='000000' where name==' ';", p_db );// WHERE ID >=0 AND ID <=20
	char sql[128]= {0};
	snprintf(sql,sizeof(sql),"update %s set %s where %s;",table_name, prefence,condition);		
	return(sqlite_write(sql,db));	
}

int sqlite_delete(const char *table_name,const char *qualify,sqlite3 *db)	
{
	//sqlite_delete( "delete from Tcp_Table where ID !=1", p_db );
	char sql[128]= {0};
	snprintf(sql,sizeof(sql),"delete from %s where %s;",table_name, qualify);	
	return(sqlite_write(sql,db));
}
/*				
int sqlite_read(const  char *table_name, sqlite3 *db)	
{	
	int index;
	int nRow, nColumn,i,j;		
	char **read_data;
	char sql[50];
	
	memset(sql,0,sizeof(sql));	
	snprintf(sql,sizeof(sql),"select * from %s;",table_name);	
	
	result = sqlite3_get_table( db, sql, &read_data, &nRow, &nColumn, &errmsg );		   
	if( result == SQLITE_OK )
	{	 			
		index = nColumn;		   
		printf("search %d records\n", nRow );			   
		for(  i = 0; i < nRow ; i++ )	
		{	
			 printf("Record %d \n", i+1 );	
			 for( j = 0 ; j < nColumn; j++ )
			 {	
				  printf("column:%s  value:%s\n",  read_data[j], read_data[index++] );					 
			 }	
			 printf("------------------\n" );   		
		}			
	}	
		   
	else	
	{ 
	 printf( "Read table error,error code:%d,reason:%s\n", result, errmsg );
	 sqlite3_free(errmsg); 
	 return -1;
	}			
		   
	sqlite3_free_table( read_data);
	return 0;
//result = sqlite3_exec( db,sql, LoadMyInfo, NULL, errmsg );//use  recall func		
}



*/

int sqlite_update_tcp_table( const char *name,   const char *value )
{    	
	sqlite3 *p_db = NULL;

	const char *filename= TCP_IP_PORT_PASSWORD;
	char table_name[]= TABLE_NAME;		
	char condition[40]={0};
	char new_value[100]={0};	
	
	sqlite_open(filename,&p_db);		
		
	memset(new_value,0,sizeof(new_value));		
	snprintf(new_value,sizeof(new_value),"value='%s'",value);
	
	memset(condition,0,sizeof(condition));
	snprintf(condition,sizeof(condition),"name=='%s'",name);	
				
	if(sqlite_update( table_name,new_value,condition, p_db )==-1)
	{
		puts( "*********Update tcp_table Error*********");			
	}
	sqlite3_close(p_db);	
		
	return 0;
		
}



int init_tcp_table(const char* filename)
{	
	sqlite3 *p_db = NULL;
	
	char table_name[]= TABLE_NAME;	
	char sql[50]= "name primary key,value"; 	
	
	sqlite_open( filename, &p_db ) ;
	sqlite_create( table_name, sql, p_db );	

	
	memset(sql,0,sizeof(sql));	
	snprintf(sql,sizeof(sql),"'%s','%s'","area","");	
	sqlite_insert( table_name ,sql, p_db );

	

	sqlite3_close(p_db);

}



int init_table(void)
{
	init_tcp_table( TCP_IP_PORT_PASSWORD );

}

