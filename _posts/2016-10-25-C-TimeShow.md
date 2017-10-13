---
layout: post
title: C 时间矩阵显示
categories: C
description: 笔记
keywords: C, Ubuntu, Time 
---

在命令行里显示时间

## 链接

* [C 时间矩阵显示](https://tsbxmw.github.io/2016/10/25/C-TimeShow/)

##  内容

### 起源
    easy time show on ubuntu

### 显示效果

![](/images/blog/sae/img_006.PNG)

### 行动
  设想是美好的，行动是复杂的。

#### 获取系统时间

  为了更好的实时同步系统时间并显示，采用了一个懒办法
  使用popen来获取系统时间

```c

        stream = popen("date","r");
        fread(buf,sizeof(char),sizeof(buf),stream);
        char *tmp;
        int i = 0;
        tmp = strtok(buf," ");
        while(tmp!=NULL&&i<4){
            tmp = strtok(NULL," ");
            if(i==3){
                i = 4;
            }
            i++;
        }
```

  获取之后如何显示呢?


#### 制定点阵：

```c
            char a0[8][6] = {" *** ",
                             "*   *",
                             "*   *",
                             "*   *",                                       
                             "*   *",                   
                             "*   *",
                             "*   *",                               
                             " *** "};
            char a1[8][6] = {"  *  ",
                             " **  ",
                             "  *  ",
                             "  *  ",
                             "  *  ",
                             "  *  ",
                             "  *  ",
                             "*****"};
            char a2[8][6] = {" *** ",
                             "*   *",
                             "*   *",
                             "   * ",
                             "  *  ",
                             " *   ",
                             "*   *",
                             "*****"};
            char a3[8][6] = {" *** ",
                             "*   *",
                             "    *",
                             "  ** ",
                             "    *",
                             "    *",
                             "*   *",
                             " *** "};
            char a4[8][6] = {"   * ",
                             "  ** ",
                             " * * ",
                             "*  * ",
                             "*  * ",
                             " ****",
                             "   * ",
                             "  ***"};
            char a5[8][6] = {"*****",
                             "*    ",
                             "*    ",
                             "**** ",
                             "    *",
                             "    *",
                             "*   *",
                             " *** "};
            char a6[8][6] = {" *** ",
                             "*   *",
                             "*    ",
                             "**** ",
                             "*   *",
                             "*   *",
                             "*   *",
                             " *** "};
            char a7[8][6] = {"*****",
                             "*   *",
                             "   * ",
                             "  *  ",
                             "  *  ",
                             "  *  ",
                             "  *  ",
                             "  *  "};
            char a8[8][6] = {" *** ",
                             "*   *",
                             "*   *",
                             " *** ",
                             "*   *",
                             "*   *",
                             "*   *",
                             " *** "};
            char a9[8][6] = {" *** ",
                             "*   *",           
                             "*   *",
                             "*   *",
                             " ****",          
                             "    *",
                             "*   *",
                             " *** "};
            char ax[8][6] = {"     ",
                             "  ** ",
                             "  ** ",
                             "     ",
                             "     ",
                             "  ** ",
                             "  ** ",
                             "     "};
```

#### 匹配时间字符
  例如输入时间是16:35:21
  则开始匹配：
  将匹配到的数字每行相加，输出到新的数组中。

```c

       char time[8][200];
            for(int i=0;i<8;i++)
                    for(int j=0;j<200;j++)
                            time[i][j]='\0';
            while((temp=date[i])!=NULL){
                if(temp =='1')
                        strcpy_1(time_temp,a1);
                if(temp =='2')
                        strcpy_1(time_temp,a2);
                if(temp =='3')
                        strcpy_1(time_temp,a3);
                if(temp =='4')
                        strcpy_1(time_temp,a4);
                if(temp =='5')
                        strcpy_1(time_temp,a5);
                if(temp =='6')
                        strcpy_1(time_temp,a6);
                if(temp =='7')
                        strcpy_1(time_temp,a7);
                if(temp =='8')
                        strcpy_1(time_temp,a8);
                if(temp =='9')
                        strcpy_1(time_temp,a9);
                if(temp =='0')
                        strcpy_1(time_temp,a0);
                if(temp ==':')
                        strcpy_1(time_temp,ax);
                //将匹配到的字符的每行相加
                for(int j=0;j<8;j++){
                    int m = i*8;
                    int n = (i+1)*8;
                    time[j][m] = xspace[j][0];
                    m++;
                    time[j][m] = xspace[j][1];
                    m++;
                    for(int x=0;m<n;m++){
                            time[j][m]=time_temp[j][x];
                            x++;
                    }
                }
                i++;
            }
```

#### 获得时间结果，并输出
  最开始是1s的间隔，效果令人不能忍受，而且由于延时函数的不准确导致秒会跳动。
  后来usleep(100000)函数，100000ns = 0.01s解决了问题
  并增加了彩色显示效果：

```c

      for(int i=0;i<8;i++)
            {
                   for(int j=0;j<200;j++)
                   { 
                           if(time[i][j]!='\0')
                           {
                                 int x = rand()%7;
                                 if(x==0)
                                   printf("\033[1;32m%c",time[i][j]);
                                 if(x==1)
                                   printf("\033[1;33m%c",time[i][j]);
                                 if(x==2)
                                   printf("\033[1;34m%c",time[i][j]);
                                 if(x==3)
                                   printf("\033[1;35m%c",time[i][j]);
                                if(x==4)
                                   printf("\033[1;36m%c",time[i][j]);
                                if(x==5)
                                   printf("\033[1;37m%c",time[i][j]);
                                if(x==6)
                                   printf("\033[1;38m%c",time[i][j]);
                                   
                                
                           }
                   }
                   printf("\n");
            }
```

###源码 

```c

    #include<sys/types.h>
    #include<unistd.h>
    #include<stdlib.h>
    #include<string.h>
    #include<stdio.h>
    
    void strcpy_1(char a[8][6],char b[8][6]){
          for(int i =0;i<8;i++)
                  for(int j=0;j<6;j++)
                          a[i][j] = b[i][j];   
    }
    
    void print_number(char *date){
            char a0[8][6] = {" *** ",
                             "*   *",
                             "*   *",
                             "*   *",
                             "*   *",
                             "*   *",
                             "*   *",
                             " *** "};
            char a1[8][6] = {"  *  ",
                             " **  ",
                             "  *  ",
                             "  *  ",
                             "  *  ",
                             "  *  ",
                             "  *  ",
                             "*****"};
            char a2[8][6] = {" *** ",
                             "*   *",
                             "*   *",
                             "   * ",
                             "  *  ",
                             " *   ",
                             "*   *",
                             "*****"};
            char a3[8][6] = {" *** ",
                             "*   *",
                             "    *",
                             "  ** ",
                             "    *",
                             "    *",
                             "*   *",
                             " *** "};
            char a4[8][6] = {"   * ",
                             "  ** ",
                             " * * ",
                             "*  * ",
                             "*  * ",
                             " ****",
                             "   * ",
                             "  ***"};
            char a5[8][6] = {"*****",
                             "*    ",
                             "*    ",
                             "**** ",
                             "    *",
                             "    *",
                             "*   *",
                             " *** "};
            char a6[8][6] = {" *** ",
                             "*   *",
                             "*    ",
                             "**** ",
                             "*   *",
                             "*   *",
                             "*   *",
                             " *** "};
            char a7[8][6] = {"*****",
                             "*   *",
                             "   * ",
                             "  *  ",
                             "  *  ",
                             "  *  ",
                             "  *  ",
                             "  *  "};
            char a8[8][6] = {" *** ",
                             "*   *",
                             "*   *",
                             " *** ",
                             "*   *",
                             "*   *",
                             "*   *",
                             " *** "};
            char a9[8][6] = {" *** ",
                             "*   *",           
                             "*   *",
                             "*   *",
                             " ****",          
                             "    *",
                             "*   *",
                             " *** "};
            char ax[8][6] = {"     ",
                             "  ** ",
                             "  ** ",
                             "     ",
                             "     ",
                             "  ** ",
                             "  ** ",
                             "     "};
            char xspace[8][3]={"  ","  ","  ","  ","  ","  ","  ","  "};
            char temp;
            char time_temp[8][6];
            int i = 0;        
            char time[8][200];
            for(int i=0;i<8;i++)
                    for(int j=0;j<200;j++)
                            time[i][j]='\0';
            while((temp=date[i])!=NULL){
                if(temp =='1')
                        strcpy_1(time_temp,a1);
                if(temp =='2')
                        strcpy_1(time_temp,a2);
                if(temp =='3')
                        strcpy_1(time_temp,a3);
                if(temp =='4')
                        strcpy_1(time_temp,a4);
                if(temp =='5')
                        strcpy_1(time_temp,a5);
                if(temp =='6')
                        strcpy_1(time_temp,a6);
                if(temp =='7')
                        strcpy_1(time_temp,a7);
                if(temp =='8')
                        strcpy_1(time_temp,a8);
                if(temp =='9')
                        strcpy_1(time_temp,a9);
                if(temp =='0')
                        strcpy_1(time_temp,a0);
                if(temp ==':')
                        strcpy_1(time_temp,ax);
                for(int j=0;j<8;j++){
                    int m = i*8;
                    
                    int n = (i+1)*8;
                    time[j][m] = xspace[j][0];
                    m++;
                    time[j][m] = xspace[j][1];
                    m++;
                    for(int x=0;m<n;m++){
                            time[j][m]=time_temp[j][x];
                            x++;
                    }
                   // if(i==0)
                     //   for(int x=0;x<n;x++)
                       //     printf("%c",time[j][x]);
                    //time_x = strcat(time[j],xspace[j]);
                    //time[j] = strcat(time_x[j],time_temp);
                }
                i++;
            }
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<200;j++)
                { 
                           if(time[i][j]!='\0')
                           {
                                 int x = rand()%7;
                                 if(x==0)
                                   printf("\033[1;32m%c",time[i][j]);
                                 if(x==1)
                                   printf("\033[1;33m%c",time[i][j]);
                                 if(x==2)
                                   printf("\033[1;34m%c",time[i][j]);
                                 if(x==3)
                                   printf("\033[1;35m%c",time[i][j]);
                                if(x==4)
                                   printf("\033[1;36m%c",time[i][j]);
                                if(x==5)
                                   printf("\033[1;37m%c",time[i][j]);
                                if(x==6)
                                   printf("\033[1;38m%c",time[i][j]);
                                   
                                
                           }
                   }
                   printf("\n");
            }
    }
    int main(){
        while(1)
        {
            printf("\033[1;32m*****   **   ***   ***   *****    \n");
            printf("\033[31m  *          *  * *  *   *           **\n");
            printf("\033[1;34m  *     **   *   *   *   *****    \n");
            printf("\033[1;33m  *     **   *   *   *   *           ** \n");
            printf("\033[1;37m  *     **   *   *   *   *****    \n\n\n");
            printf("\033\[1;32m\n");
            FILE *stream;
            char buf[50];
            stream = popen("date","r");
            fread(buf,sizeof(char),sizeof(buf),stream);
            char *tmp;
            int i = 0;
            tmp = strtok(buf," ");
            while(tmp!=NULL&&i<4){
                tmp = strtok(NULL," ");
                if(i==3){
                    i = 4;
                }
                i++;
            }
            pclose(stream);
            print_number(tmp);
            //system("sleep 1");
            usleep(100000);
            system("clear");
        }
    return 0;
    }
```

### LINK
* [github time show ](https://github.com/tsbxmw/c-_show_config/)