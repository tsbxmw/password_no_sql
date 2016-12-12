---
layout: post
title: C 连接mysql
categories: C
description: 笔记
keywords: C, Mysql, connect 
---

C 连接mysql

## 链接

* [C C 连接mysql](https://tsbxmw.github.io/2016/10/27/C-mysql_function)

##  内容

### 起源
  
  最近在写一个C命令行程序，需要操作数据，最开始使用的是文件的方式，放在一个windows共享目录中，实时操作，但实现麻烦的很，还要考虑读写操作权限问题。
  最后想为啥不用数据库呢，数据虽小，方便之上。
  首先连接mysql，进行数据操作和显示

### 行动
  网上连接数据库的方式很多。这里使用mysql数据库和jdbc连接？？

```c

                #include <Windows.h>
                #include <stdio.h>
                #include <stdlib.h>
                #include <string>
                #include <mysql.h>
                #include <errmsg.h>
                #include <mysql_version.h>
                #include "config_mysql.h"
                #include <iostream>
                #include "config.h"
                using namespace std;
                string result_find_tab_line[1000];

                int init_db(MYSQL *mysql)
                {
                    int err = 0;
                    if(!mysql_init(mysql))
                    {
                        perror("|-- mysql init: ......");
                        exit(1);
                    }
                    if(!mysql_real_connect(mysql,SERVER_HOST,USER,PASS,NULL,0,NULL,0))
                    {
                        perror("|-- error : mysql_real_connect");
                        exit(1);
                    }
                    printf("|-- connectting now ...... \n");
                    return 0;
                }
                int colse_db(MYSQL *mysql)
                {
                    mysql_close(mysql);
                }

                int check_db(MYSQL *mysql,char *db_name)
                {
                    MYSQL_ROW row = NULL;
                    MYSQL_RES *res = NULL;
                    res = mysql_list_dbs(mysql,NULL);
                    if(res)
                    {
                        while((row=mysql_fetch_row(res))!=NULL)
                        {
                            //printf("db is %s\n",row[0]);
                            if(strcmp(row[0],db_name)==0)
                            {
                                cout<< "|-- find db [ "<<db_name<<" ]"<<endl;
                                break;
                            }
                        }
                            //mysql_list_dbs会分配内存，需要使用mysql_free_result释放  
                        mysql_free_result(res);
                    }
                    if(!row)//没有这个数据库，则建立  
                    {
                        char buf[128]={0};
                        strcpy(buf,"|-- CREATE DATABASE ");
                        strcat(buf,db_name);
                #ifdef DEBUG
                        printf("|-- %s\n",buf);
                #endif
                        if(mysql_query(mysql,buf)){
                            //fprintf(stderr,"Query failed (%s)\n",mysql_error(mysql));
                        exit(1);
                        }
                    }
                    return 0;
                }

                int find_db(MYSQL *mysql,char * db_name)
                {
                    MYSQL_ROW row = NULL;
                    MYSQL_RES *res = NULL;
                    res=mysql_list_dbs(mysql,NULL);
                    int xxx = 0;
                    if(res)
                    {
                        while((row=mysql_fetch_row(res))!=NULL)
                        {
                            //printf("db is %s\n",row[0]);
                            if(strcmp(row[0],db_name)==0)
                            {
                                cout<<"|-- find db [ "<<db_name<<" ]"<<endl;
                                xxx = 1;
                                string buff = "use ";
                                buff = buff + db_name;
                                mysql_query(mysql,buff.c_str());
                                break;
                            }
                        }
                            //mysql_list_dbs会分配内存，需要使用mysql_free_result释放  
                        mysql_free_result(res);
                    }
                    if(xxx == 0)
                    {
                        cout<<"|-- do not find the db! "<<endl;
                        return 0;
                    }
            else
                return 1;
        }
        int select_db(MYSQL *mysql,char * db_name)
        {
            if(!mysql_select_db(mysql,db_name))
                return 1;
            else
                return 0;
        }
        int find_table(MYSQL *mysql,char * table_name)
        {
            MYSQL_ROW row = NULL;
            MYSQL_RES *res = NULL;
            res=mysql_list_tables(mysql,NULL);
            int xxx = 0;
            if(res)
            {
                while((row=mysql_fetch_row(res))!=NULL)
                {
                    //printf("table is %s\n",row[0]);
                    if(strcmp(row[0],table_name)==0)
                    {
                        cout<<"|-- find table [ "<<table_name<<" ]"<<endl;
                        xxx =1 ;
                        break;
                    }
                }
                    //mysql_list_dbs会分配内存，需要使用mysql_free_result释放  
                mysql_free_result(res);
            }
            if(xxx ==0)
            {
            cout<<"|-- do not find the table! "<<endl;
            return 0;
            }
            else
                return 1;
        }

        int read_table(MYSQL *mysql,char *table_name,int number)
        {
            int res;
            MYSQL_ROW row = NULL;
            MYSQL_RES *res_mysql = NULL;
            char buff[128] = "select * from ";
            strcat(buff,table_name);
            cout<<"|-- TABLE　"<<table_name;
            res = mysql_query(mysql,buff);
            if(res)
            {
                cout<<"|-- error"<<endl;
            }
            else
            {
                res_mysql = mysql_store_result(mysql);
                if(res_mysql)
                {
                
                    cout<<" lines : "<<mysql_num_rows(res_mysql)<<endl;
                    int j = 0;
                    while(row = mysql_fetch_row(res_mysql))
                    {
                        int i=0;
                        cout<<"|--   "<<j+1<<"  ";
                        j++;
                        while(i<number-1)
                        {
                            cout<<row[i]<<"-";
                            i++;
                        }
                        cout<<row[number-1];
                        cout<<endl;
                    }
                }
            }
            return 0;
        }

        int  find_one_tab(MYSQL *mysql,string table,string line_name)
        {
            int res;
            int num;
            MYSQL_ROW row = NULL;
            MYSQL_RES *res_mysql = NULL;
            string buff = "select distinct "+ line_name;
            buff = buff + " from ";
            buff = buff + table;
            cout<<"|-- "<<buff<<endl;
            res = mysql_query(mysql,buff.c_str());
            if(!res)
            {
                res_mysql = mysql_store_result(mysql);
                int num = (int)mysql_num_rows(res_mysql);
                cout<<"|-- project numer is "<<num<<endl;
                if((int)num==0)
                {
                    cout<<"|-- do not find the line "<<endl;
                }
                else
                {
                    if(res_mysql)
                    {
                        int i=0;

                    //  cout<<mysql_num_rows(res_mysql)<<endl;
                        cout<<"|-- find the tab line : ";

                        while(row = mysql_fetch_row(res_mysql))
                        {
                            cout<<row[0]<<" ";
                            result_find_tab_line[i]=row[0];
                            i++;
                        }
                        cout<<endl;
                        return num;
                    }

                }
            }
            else
            {
                cout<<"|-- error "<<res<<endl;
                return num;
            }

        }
        //....................................................................................................................
        int  find_one_tab_form_where(MYSQL *mysql,string table,string line_name,string from,string f_where)
        {
            int res;
            int num;
            MYSQL_ROW row = NULL;
            MYSQL_RES *res_mysql = NULL;
            string buff = "select distinct "+ line_name;
            buff = buff + " from ";
            buff = buff + table + " where "  + from + "=\'"+f_where+"\'";
            cout<<"|-- "<<buff<<endl;
            res = mysql_query(mysql,buff.c_str());
            if(!res)
            {
                res_mysql = mysql_store_result(mysql);
                int num = (int)mysql_num_rows(res_mysql);
                cout<<"|-- result numer is "<<num<<endl;
                if((int)num==0)
                {
                    cout<<"|-- do not find the line "<<endl;
                }
                else
                {
                    if(res_mysql)
                    {
                        int i=0;

                    //  cout<<mysql_num_rows(res_mysql)<<endl;
                        cout<<"|-- find the tab line : ";

                        while(row = mysql_fetch_row(res_mysql))
                        {
                            cout<<row[0]<<" ";
                            result_find_tab_line[i]=row[0];
                            i++;
                        }
                        cout<<endl;
                        return num;
                    }

                }
            }
            else
            {
                cout<<"|-- error "<<res<<endl;
                return num;
            }

        }
        //...................................................................................................................




        int find_ip_pro_line(MYSQL *mysql,string table,string insert_values[100])
        {
            int res;
            MYSQL_ROW row = NULL;
            MYSQL_RES *res_mysql = NULL;
            string insert_into[100];
            insert_into[0] = insert_values[17];
            insert_into[1] = insert_values[15];
            insert_into[2] = "12345678";
            insert_into[3] = "NULL";
            insert_into[4] = "ON";
            string buff = "select * from ";
            buff = buff + table;
            buff = buff + " where (ip_address =\'"+insert_values[17]+"\') and (project=\'"+insert_values[15]+"\')";
            //buff = buff + " where (ip_address =\'10.63.220.2\')";
            cout<<"|-- "<<buff<<endl;
            res = mysql_query(mysql,buff.c_str());
            cout<<"<-- debug : "<<res<<endl;
            if(!res )
            {
                res_mysql = mysql_store_result(mysql);
                cout<<"<-- debug : "<<mysql_num_rows(res_mysql)<<endl;
                if(mysql_num_rows(res_mysql)==0)
                {
                    cout<<"|-- do not find the line , insert it"<<endl;
                    

                    insert_into_table(mysql,table,insert_into,5);
                }
                else
                {
                    if(res_mysql)
                    {
                
                    //  cout<<mysql_num_rows(res_mysql)<<endl;
                        cout<<"|-- find the line : ";
                        while(row = mysql_fetch_row(res_mysql))
                        {
                            int i=0;
                            while(i<4)
                            {
                                cout<<row[i]<<"-";
                                i++;
                            }
                            cout<<row[4];
                            cout<<endl;
                        }
                    }
                    while(update_table_one_line(mysql,TABLE_CLI,"status_phone","NULL","ip_address",insert_into[0],insert_into[1]))
                    {
                        Sleep(1000);
                    }
                    while(update_table_one_line(mysql,TABLE_CLI,"phone_ison","ON","ip_address",insert_into[0],insert_into[1]))
                    {
                        Sleep(1000);
                    }
                }
            }
            else
            {
                cout<<"|-- error "<<res<<endl;
            }
            return res;
        }

        string find_ip_pro_line_status(MYSQL *mysql,string table,string insert_values[100])
        {
            int res,res_p;
            string result;
            MYSQL_ROW row = NULL;
            MYSQL_RES *res_mysql = NULL;    
            MYSQL_ROW row_p = NULL;
            MYSQL_RES *res_mysql_p = NULL;
            string insert_into[100];
            string path_version;
            insert_into[0] = insert_values[17];
            insert_into[1] = insert_values[15];
            string buff = "select status_pc from ";
            buff = buff + table;
            buff = buff + " where (ip_address =\'"+insert_values[17]+"\') and (project=\'"+insert_values[15]+"\')";
            string buff_p = "select path_version from "+table+" where (ip_address =\'"+insert_values[17]+"\') and (project=\'"+insert_values[15]+"\')";
            //buff = buff + " where (ip_address =\'10.63.220.2\')";
            cout<<"|-- "<<buff<<endl;
            res = mysql_query(mysql,buff.c_str());
            cout<<"<-- debug : "<<res<<endl;
            if(!res )
            {
                res_mysql = mysql_store_result(mysql);
                cout<<"<-- debug : "<<mysql_num_rows(res_mysql)<<endl;
                if(mysql_num_rows(res_mysql)==0)
                {
                    cout<<"|-- do not find the line ! wait for server"<<endl;
                }
                else
                {
                    if(res_mysql)
                    {
                
                    //  cout<<mysql_num_rows(res_mysql)<<endl;
                        cout<<"|-- find the line : ";
                        while(row = mysql_fetch_row(res_mysql))
                        {
                            result = row[0];
                            cout<<"|-- "<<row[0];
                            cout<<endl;
                        }
                    }
                }
            }
            else
            {
                cout<<"|-- error "<<res<<endl;
            }

            if(result == "NULL")
            {
                cout<<"|-- this is the path "<<endl;
                cout<<"|-- buff_p:"<<buff_p<<endl;
                res_p = mysql_query(mysql,buff_p.c_str());
                cout<<"<-- debug : "<<res_p<<endl;
                if(!res_p )
                {
                    res_mysql_p = mysql_store_result(mysql);
                    cout<<"<-- debug : "<<mysql_num_rows(res_mysql_p)<<endl;
                    if(mysql_num_rows(res_mysql_p)==0)
                    {
                        cout<<"|-- do not find the line ! wait for server"<<endl;
                    }
                    else
                    {
                        if(res_mysql_p)
                        {
                
                        //  cout<<mysql_num_rows(res_mysql)<<endl;
                            cout<<"|-- find the line : ";
                            while(row_p = mysql_fetch_row(res_mysql_p))
                            {
                                path_version = row_p[0];
                                cout<<"|-- "<<row_p[0];
                                cout<<endl;
                            }
                            while(update_table_one_line(mysql,TABLE_CLI,"status_phone","BUSY","ip_address",insert_values[17],insert_values[15]))
                            {
                                Sleep(1000);
                            }
                            return path_version;
                        }
                    }
                }
                else
                {
                    cout<<"|-- error "<<res<<endl;
                }
            }
            return "NULL";
        }
        //..................................................................................................
        string get_path(MYSQL *mysql,string table,string insert_values[100])
        {
            int res;
            string result;
            MYSQL_ROW row = NULL;
            MYSQL_RES *res_mysql = NULL;
            string insert_into[100];
            insert_into[0] = insert_values[17];
            insert_into[1] = insert_values[15];
            insert_into[2] = "12345678";
            insert_into[3] = "NULL";
            insert_into[4] = "ON";
            string buff = "select status_pc from ";
            buff = buff + table;
            buff = buff + " where (ip_address =\'"+insert_values[17]+"\') and (project=\'"+insert_values[15]+"\')";
            //buff = buff + " where (ip_address =\'10.63.220.2\')";
            cout<<"|-- "<<buff<<endl;
            res = mysql_query(mysql,buff.c_str());
            cout<<"<-- debug : "<<res<<endl;
            if(!res )
            {
                res_mysql = mysql_store_result(mysql);
                cout<<"<-- debug : "<<mysql_num_rows(res_mysql)<<endl;
                if(mysql_num_rows(res_mysql)==0)
                {
                    cout<<"|-- do not find the line ! wait for server"<<endl;
                }
                else
                {
                    if(res_mysql)
                    {
                
                    //  cout<<mysql_num_rows(res_mysql)<<endl;
                        cout<<"|-- find the line : ";
                        while(row = mysql_fetch_row(res_mysql))
                        {
                            result = row[0];
                            cout<<"|-- "<<row[0];
                            cout<<endl;
                        }
                    }
                }
            }
            else
            {
                cout<<"|-- error "<<res<<endl;
            }
            return result;
        }
        //..................................................................................................
        int insert_into_table(MYSQL *mysql,string table_name,string values_insert[100],int count)
        {
            int res;
            MYSQL_ROW row = NULL;
            MYSQL_RES *res_mysql = NULL;
            string buff = "insert into ";
            buff = buff + table_name;
            buff = buff + " values(\"" ;
            for(int i=0;i<count-1;i++)
                buff = buff + values_insert[i]+"\",\"";
            buff = buff + values_insert[count-1]+"\")";
            cout<<"|-- "<<buff<<endl;
            res = mysql_query(mysql,buff.c_str());
            if(res)
            {
                cout<<"|-- error "<<endl;
                return 1;
            }
            else
            {
                cout<<"|-- insert ok "<<endl;
            }
            
            return 0;
        }
        //......................................................................................................................
        int update_table_one_line(MYSQL *mysql,string table,string line_name,string line_status,string from,string f_where,string project)
        {
            int res;
            MYSQL_ROW row = NULL;
            MYSQL_RES *res_mysql = NULL;
            string buff = "update ";
            buff = buff + table;
            buff = buff + " set " + line_name + "=\""+line_status + "\" where ("+from +"=\'"+f_where+"\' and project=\'"+project+"\')";
            cout<<"|-- "<<buff<<endl;
            res = mysql_query(mysql,buff.c_str());
            if(res)
            {
                cout<<"|-- error "<<endl;
            }
            else
            {
                cout<<"|-- update success !"<<endl;
            }
            return res;
        }
        //.........................................................................................................................................
        int  find_ip_pro_line_config(MYSQL *mysql,string table,string insert_values[100])
        {
            int res,res_p;
            string result;
            MYSQL_ROW row = NULL;
            MYSQL_RES *res_mysql = NULL;    
            MYSQL_ROW row_p = NULL;
            MYSQL_RES *res_mysql_p = NULL;
            string insert_into[100];
            string path_version;
            insert_into[0] = insert_values[17];
            insert_into[1] = insert_values[15];
            insert_into[2] = insert_values[6];
            insert_into[3] = insert_values[8];
            insert_into[4] = insert_values[9];
            insert_into[5] = insert_values[10];
            insert_into[6] = insert_values[11];
            insert_into[7] = insert_values[13];
            insert_into[8] = insert_values[14];
            insert_into[9] = insert_values[15];
            insert_into[10] = insert_values[16];
            insert_into[11] = insert_values[17];
            string buff = "select * from ";
            buff = buff + table;
            buff = buff + " where (project=\'"+insert_values[15]+"\')";
            //string buff_p = "select path_version from "+table+" where (ip_address =\'"+insert_values[17]+"\') and (project=\'"+insert_values[15]+"\')";
            //buff = buff + " where (ip_address =\'10.63.220.2\')";
            cout<<"|-- "<<buff<<endl;
            res = mysql_query(mysql,buff.c_str());
            cout<<"<-- debug : "<<res<<endl;
            if(!res )
            {
                res_mysql = mysql_store_result(mysql);
                cout<<"<-- debug : "<<mysql_num_rows(res_mysql)<<endl;
                if(mysql_num_rows(res_mysql)==0)
                {
                    cout<<"|-- do not find the line ! insert into lines "<<endl;
                    insert_into_table(mysql,table,insert_into,12);
                }
                else
                {
                    if(res_mysql)
                    {
                    //  cout<<mysql_num_rows(res_mysql)<<endl;
                        cout<<"|-- find the line : ";
                        while(row = mysql_fetch_row(res_mysql))
                        {
                            cout<<"|-- ";
                            for(int i=0;i<11;i++)
                                cout<<row[i]<<"-";
                            cout<<row[11]<<endl;
                        }
                        update_table_config(mysql,"config",insert_values);
                    }
                }
            }
            else
            {
                cout<<"|-- error "<<res<<endl;
            }
            return 0;
        }
        int update_table_config(MYSQL *mysql,string table,string find_value[100])
        {
            int res;
            MYSQL_ROW row = NULL;
            MYSQL_RES *res_mysql = NULL;
            string buff = "update ";
            buff = buff + table;
            buff = buff + " set lcoal_version_path =\'"+find_value[6] +"\',ftp_ip_address=\'"+find_value[8]+"\',ftp_user=\'"+find_value[9]+"\',ftp_password=\'"+find_value[10]+"\',local_upload_path=\'"+find_value[11]+"\',ftp_config_path=\'"+find_value[13]+"\',config_pre_name=\'"+find_value[14]+"\',project_name_config=\'"+find_value[15]+"\',server_ip_address=\'"+find_value[16]+"\',local_ip_address=\'"+find_value[17]+"\' where (ip_address=\'"+find_value[17]+"\' and project=\'"+find_value[15]+"\')" ;
            cout<<"|-- "<<buff<<endl;
            res = mysql_query(mysql,buff.c_str());
            if(res)
            {
                cout<<"|-- error "<<endl;
            }
            else
            {
                cout<<"|-- update success !"<<endl;
            }
            return res;
        }
```

### 之前使用的操作文件的函数

```c

     
                #include <iostream>
                #include <Windows.h>
                #include <fstream>
                #include <string>
                #include "config.h"

                using namespace std;

                /**********************************************************************************************************/
                /*
                    *����ÿ��filename�ļ�
                */
                void refresh_configname(string project)
                {
                    cout<<"update all filename"<<endl;
                    system(("dir /b /o "+project+"\\configfile_all > "+project+"\\filename_all.txt").c_str());
                    system(("dir /b /o "+project+"\\config_not_read > "+project+"\\filename_not_read.txt").c_str());
                    system(("dir /b /o "+project+"\\config_read > "+project+"\\filename_read.txt").c_str());
                    system(("dir /b /o "+project+"\\config_not_test > "+project+"\\filename_not_test.txt").c_str());

                }

                /************************************************************************************************************/
                /*
                    *�˴�ֻ�Ǹ���notread��read��nottest���ļ�������-��Ӧ��txt�ļ���ȥ��
                */
                void refresh_read_not_read(string project)
                {
                    system(("dir /b /o "+project+"\\config_not_read > "+project+"\\filename_not_read.txt").c_str());
                    system(("dir /b /o "+project+"\\config_read > "+project+"\\filename_read.txt").c_str());
                    system(("dir /b /o "+project+"\\config_not_test > "+project+"\\filename_not_test.txt").c_str());

                }

                /************************************************************************************************************/
                /*
            *�Ƴ�ǰ���� PATH=�����þ���·�������أ�����ʵ�ʵ�ǰ׺���и��ģ�
            *removepath(char *x,int y);
        */
        char * removepath(char x[10000],int length)
        {
            length=length+12;//ȥ�� path=ftp://10.63.220.2/transfer/  .length().
            for(int i=0;i<3000;i++)
            {
                x[i]=x[i+length];
                if(x[i]=='\n')//�˴��Ƴ������Ļس�����Ϊ��׼����
                {
                    x[i]='\0';
                }
            }
            return x;
        }

        /************************************************************************************************************/
        /*
            // open the config_ini file to setup and create the new cfg file to 
            // download the version file from the ftpserver
        */
        void open_config_ini(string localfile[100],string project) 
        {
            char local_ini[1000];
            int ini_line=0;
            fstream config_ini;
            //cout<<project<<endl;
            config_ini.open(project+"\\config_ini.ini");//read the config file

            while(config_ini.getline(local_ini,300,'\n'))
            {
                cout<<"<-- local_ini opened : " << local_ini << " -->"<<endl;
                if(!(local_ini[0]==':' && local_ini[1]==':' &&local_ini[2]=='-'))
                {
                    switch(ini_line){
                    case 0:
                        localfile[6]=local_ini;//���ذ汾����·��������
                        break;
                    case 1:
                        localfile[8]=local_ini;//ftp ip address
                        break;
                    case 2:
                        localfile[9]=local_ini;//user_name
                        break;
                    case 3:
                        localfile[10]=local_ini;//password
                        break;
                    case 4:
                        localfile[11]=local_ini;//config_upload_path
                        break;
                    case 5:
                        localfile[13]=local_ini;//ftp servers config_files path
                        break;
                    case 6:
                        localfile[14]=local_ini;//config file pre name
                        break;
                    default:
                        break;
                    }

                    ini_line++;
                }
            }
            config_ini.close();

            //cout<<localfile[10]<<endl;

        }
        void open_config_sql(string localfile[100],string project,MYSQL *mysql) 
        {
            int res;
            MYSQL_ROW row = NULL;
            MYSQL_RES *res_mysql = NULL;
            string buff = "select * from ";
            buff = buff + "config";
            buff = buff + " where project =\'"+project+"\'" ;
            cout<<"|-- "<<buff<<endl;
            res = mysql_query(mysql,buff.c_str());
            if(res)
            {
                cout<<"|-- error "<<endl;

            }
            else
            {
                res_mysql = mysql_store_result(mysql);
                if(mysql_num_rows(res_mysql)==0)
                {

                    cout<<"|-- wrong with the result !!!! error "<<endl;
                }
                else
                {
                    if(res_mysql)
                    {
                
                    //  cout<<mysql_num_rows(res_mysql)<<endl;
                        cout<<"|-- find the line : ";
                        while(row = mysql_fetch_row(res_mysql))
                        {
                            localfile[6] = row[2];
                            localfile[8] = row[3];
                            localfile[9] = row[4];
                            localfile[10] = row[5];
                            localfile[11] = row[6];
                            localfile[13] = row[7];
                            localfile[14] = row[8];
                            for(int i =0;i<12;i++)
                            {
                                cout<<row[i]<<"-";

                            }
                            cout <<endl;
                            cout<<localfile[6]<<localfile[8]<<localfile[9]<<localfile[10]<<localfile[11]<<localfile[13]<<localfile[14]<<endl;
                        }
                    }
                }
                cout<<"|-- get the config info  ok "<<endl;
            }
            



            //cout<<localfile[10]<<endl;

        }

        /************************************************************************************************************/
        void update_project_ini()
        {
            system("dir /ad /b /o PROJECT > PROJECT\\project_info.ini");
        }

        int open_project_config_ini(string localfile[100]) 
        {
            update_project_ini();
            char local_ini[1000];
            int ini_line=0;
            fstream config_ini;
            //cout<<project<<endl;
            config_ini.open("PROJECT\\project_info.ini");//read the config file

            while(config_ini.getline(local_ini,300,'\n'))
            {
                cout<<"<-- project_ini opened " << local_ini<<" -->"<<endl;
                if(!(local_ini[0]==':' && local_ini[1]==':' &&local_ini[2]=='-'))
                {
                    localfile[18+ini_line] =local_ini;

                    //switch(ini_line){
                    //case 0:
                    //  localfile[18]=local_ini;//���ذ汾����·��������
                    //  break;
                    //case 1:
                    //  localfile[19]=local_ini;//ftp ip address
                    //  break;
                    //case 2:
                    //  localfile[20]=local_ini;//user_name
                    //  break;
                    //case 3:
                    //  localfile[21]=local_ini;//password
                    //  break;
                    //case 4:
                    //  localfile[22]=local_ini;//config_upload_path
                    //  break;
                    //case 5:
                    //  localfile[23]=local_ini;//ftp servers config_files path
                    //  break;
                    //case 6:
                    //  localfile[24]=local_ini;//config file pre name
                    //  break;
                    //case 7:
                    //  localfile[25]=local_ini;//config file pre name
                    //  break;
                    //case 8:
                    //  localfile[26]=local_ini;//config file pre name
                    //  break;
                    //case 9:
                    //  localfile[27]=local_ini;//config file pre name
                    //  break;
                    //default:
                    //  break;
                    
                    ini_line++;
                

                }


            }

            
            config_ini.close();

            return ini_line - 1 ;
            //cout<<localfile[10]<<endl;

        }




        /************************************************************************************************************/









        /************************************************************************************************************/
        void config_init()
        {
            
        }

        /************************************************************************************************************/
        void create_getconfig_cfg(string localfile[100],string project)
        {
            system(("@echo open "+localfile[8]+"> getconfig.cfg").c_str());
            system(("@echo "+localfile[9]+">> getconfig.cfg").c_str());
            system(("@echo "+localfile[10]+">> getconfig.cfg").c_str());
            system(("@echo cd "+localfile[13]+">> getconfig.cfg").c_str());
            system(("@echo lcd "+project+"\\configfile_all >> getconfig.cfg").c_str());
            system(("@echo prompt off >> getconfig.cfg"));
            system(("@echo mget "+localfile[14]+">> getconfig.cfg").c_str());
            system(("@echo bye>> getconfig.cfg"));
        }

        /*
        // the delay time function old version
        // the new is to show the minutes and seconds ,qulification the display.
        void delay_time(int time)
        {
            for(int i=1;i<=time;i++)
            {
                system("@ping -n 2 127.0.0.1 > null");
                if(i>60)
                {
                    int j=i%60;
                    int mins = i/60;
                    cout<<"WAIT TIME : "<<mins<<" mins "<<j<<" seconds"<<endl;
                }
                else
                {
                    cout<<"WAIT TIME : "<<i<<" seconds"<<endl;
                }
                
            }
        }
        */

        /************************************************************************************************************/
        void delay_time(int time)
        {
            for(int i=0;i<=time;i++)
            {
                Sleep(1000);

                int j=i%60;
                int mins = i/60;
                if(j==0)
                {
                    cout<<endl<<"<-- WAIT TIME : minute : "<<mins<<endl;
                }
                if(j==59)
                    cout<<j<<"-_-";
                else
                    cout<<j<<endl;;
            }
        }
```

### 先不分析，有时间来写



### LINK
* [github c to mysql ](https://github.com/tsbxmw/SYSTEM_ALL/)