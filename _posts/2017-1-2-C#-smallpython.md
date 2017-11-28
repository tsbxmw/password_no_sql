---
layout: post
title: C# 小程序 
categories: C#
description: 笔记
keywords: C# , python ,exe ,jenkins
---

C# 小程序  -  模拟 jenkins 的运行

## 链接

* [C# 小程序](https://tsbxmw.github.io/2017/1/2/C#-smallpython/)

##  摘要
    
    利用 C# 程序模拟 Jenkins 连续运行的 Pipeline


----------

## 内容    
    
### 做什么

> 设计一个类似 **jenkins** 作用的应用程序

### 设计阶段

> #### **Jenkins 是一个集成的系统，包含了各样的插件方便我们的使用** <br><br>
> 对于一些本地的程序，我们不希望使用 Jenkins 进行运行，因为Jenkins 对初学者来说是不友好的，虽然使用简单，但是建立 Node / Job / View 等各式各样的配置会使人头晕眼花，纵然已经使用Jenkins 接近两年，但是许多功能并没有使用到。
> 在这中情况下，萌生了做一个比Jenkins 简单但是易用的应用程序进行使用。


----------


### How does Jenkins work？

> #### **Pipeline** <br><br>
>
> #### What is the Pipeline ？ <br><br>
> 在jenkins 2.0 时代，Pipeline已经取代了原来的Job的形式，更为易用，但是需要熟悉 groovy 代码，熟悉 git svn jenkins python bat shell 等各种脚本和程序你才可以熟练的使用它！
 

----------


### Python to run !

> #### **python simulate** <br><br>
> 使用 python 生成exe程序去模拟 Jenkins 的 Pipeline ！
> 13个参数，程序可以定制，前12个为 name-value 对，后面为运行过程。<br><br>
>
> #### 整个程序所做的是：<br><br>
> 1 、将前12个输入的参数设置为**环境变量**<br><br>
> 2 、将13往后的参数作为运行过程，即进入参数名的文件夹，运行 run.cmd 文件 


```python
    #encoding=utf-8
    
    import sys
    import os
    import time
    
    def curfiledir():
        path = os.getcwd()
        if os.path.isdir(path):
            return path
        elif os.path.isfile(path):
            return os.path.dirname(path)
    
    
    if __name__=="__main__":
        try:
            args = sys.argv
            if len(args) < 3:
                print ("<error> [ " + time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time())) +  " ] runtest.exe Wrong with input args ,need 3 or more ! now is " + str(len(args)))
                sys.exit()
                
            par_dir = curfiledir()
            print ("<*log*> [ " + time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time())) +  " ] Set sys env now !\n")
            os.environ[args[1]] = args[2]
            os.environ[args[3]] = args[4]
            os.environ[args[5]] = args[6]
            os.environ[args[7]] = args[8]
            os.environ[args[9]] = args[10]
            os.environ[args[11]] = args[12]
            print ("<*log*> [ " + time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time())) +  " ] Set sys env done !\n")
            for i in range(13,len(args)):
                time_now = time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time()))
                #os.system("echo [ " +  time + " ]** STAGE " + args[i] + " Starting ... **")
                #print ("<*log*> [ " + time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time())) +  " ] Stage : "  +args[i] )
                sys.stdout.write("\n>---------------------------------------------------< " + args[i] + " >-------------------------------------------------<\n")
                sys.stdout.write("<*log*> [ " + time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time())) +  " ] Stage : " +args[i] +" Start now ...\n\n" )
                sys.stdout.flush()
                time.sleep(1)
                if os.path.exists(par_dir+"\\"+args[i]):
                    os.chdir(par_dir+"\\"+args[i])
                else :
                    print ("<error> [ " + time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time())) + " ] dir " + par_dir+"\\"+args[i] + "is missing , please check path")
                    sys.exit()
                if os.path.exists("run.cmd"):
                    os.system("run.cmd")
                else:
                    print ("<error> [ " + time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time())) + " ] run.cmd is missing , please check path")
                #os.system("echo [ " +  time + " ]** STAGE " + args[i] + " Starting ... **")
                    sys.exit()
                sys.stdout.write("\n<*log*> [ " + time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time()))+ " ] Stage : "  + args[i] +" Finished \n\n")
                sys.stdout.write(">---------------------------------------------------< " + args[i] + " >-------------------------------------------------<\n\n")
                sys.stdout.flush()
            print ("[ ** test finished ** ]")
        except Exception,e:
            print("<error> [ " + time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time())) + " ] " + str(e))
```

> #### 生成可执行文件，而不需要pyton环境<br><br>
>   **pyinstaller -F runtest.py**<br><br>
> 上面的命令 用来生成 runtest.exe


----------


### 使用C# 做个界面去调用 python 程序

> 实时显示时，调用其他程序如 bat/python 的时候，会造成异步与同步同时出现，导致 Exception 。
> 解决方法：<br><br>
    *  直接调用 python生成的 exe<br><br>
    *  bat中不掺杂其他的非windows自带语句<br><br>
    *  win32 console exe中不调用其他程序<br><br>

----------


> #### 设计

![](/images/blog/python/img_003.PNG)

![](/images/blog/python/img_004.PNG)

![](/images/blog/python/img_005.PNG)

![](/images/blog/python/img_006.PNG)

> #### 功能<br><br>
> 历史记录<br><br>
> 显示日志<br><br>
> 点选过程<br><br>
> 生成报告<br><br>
> 显示结果<br><br>

----------


### **附件代码 C#**

```c++  
    /*
     * author : 10192582
     * version : 0.2
     * date : 20170112
     * modify : 20170117
     * function : to run the jenkins files at local without jenkins
     */
    
    
    
    using System;
    using System.Collections.Generic;
    using System.ComponentModel;
    using System.Data;
    using System.Drawing;
    using System.Linq;
    using System.Text;
    using System.Threading.Tasks;
    using System.Windows.Forms;
    using System.Diagnostics;
    using System.Threading;
    using System.Runtime.InteropServices;
    using System.IO;
    
    
    namespace WindowsFormsApplication3
    {
        public partial class AutoTest : Form
        {
            public AutoTest()
            {
                InitializeComponent();
            }
            //本程序目录
            String strpath = "";
            //输入的流程
            String[] stagelist = new String[10];
            //已有的流程
            String[] list = { "00_step_00",
                    "01_step_01",
                    "02_step_02",
                    "03_step_03",
                    "04_step_04",
                    "05_step_05",
                    "06_step_06",
                    "07_step_07",
                    "08_step_08",
                    "END_step_END"};
            String arg1 = "", arg2 = "", arg3 = "", arg4 = "", arg5 = "", arg6 = "";
            String project = "", fotaversion1 = "", fotaversion2 = "", fotaupp = "", fotadownp = "", rootapk = "";
            //参数
            String env = "";
            //所有button的数组
            Button[] buttonx = new Button[10];
            //全局i（输入的流程的个数）
            int i;
            //存储哪个流程的button对应值
            int [] stage = new int[10] ;
            //同上
            int stage_flag = 0;
    
            Thread thread;
            Process cmd;
            int stagenum = 0;
    
            private void Form1_Load(object sender, EventArgs e)
            {
    
                Control.CheckForIllegalCrossThreadCalls = false;
               
                //流程 button 放入 button[]
                buttonx[0] = button3;
                buttonx[1] = button4;
                buttonx[2] = button5;
                buttonx[3] = button6;
                buttonx[4] = button7;
                buttonx[5] = button8;
                buttonx[6] = button9;
                buttonx[7] = button10;
                buttonx[8] = button11;
                buttonx[9] = button12;
                //进度条初始值
                //0 ~ 100
                progressBar1.Value = 0;
                progressBar1.Maximum = 100;
                progressBar1.Minimum = 0;
                // 读取历史记录
                readHistory();
                //设置所有流程 button 为 false
                setbuttonfalse();
    
            }
            //从文件中读取历史记录并设置到对应的组建
            public void readHistory()
            {
                //获取当前程序执行路径
                String path = System.Windows.Forms.Application.StartupPath;
                
                if (File.Exists(@path + "\\history.ini"))
                {
                    StreamReader sr = new StreamReader(path + "\\history.ini", Encoding.UTF8);
                    String line;
                    line = sr.ReadLine();
                    int x = 0;
                    while (line != null)
                    {
                        switch (x)
                        {
                            case 0:
                                ARG_1.Text = line;                          
                                break;
                            case 1:
                                projectname.Text = line;
                                break;
                            case 2:
                                ARG_2.Text = line;
                                break;
                            case 3:
                                fotabeforeversion.Text = line;
                                break;
                            case 4:
                                ARG_3.Text = line;                            
                                break;
                            case 5:
                                fotaafterversion.Text = line;
                                break;
                            case 6:
                                ARG_4.Text = line;
                                break;
                            case 7:
                                fotauppack.Text = line;
                                break;
                            case 8:
                                ARG_5.Text = line;
                                break;
                            case 9:
                                fotadownpack.Text = line;
                                break;
                            case 10:
                                ARG_6.Text = line;
                                break;
                            case 11:
                                rootapkpath.Text = line;
                                break;
                        }
                        line = sr.ReadLine();
                        x++;
                    }
                    sr.Close();
                }
                else
                {
    
                }
            }
    
            //设置所有流程按钮不可点击
            public void setbuttonfalse()
            {
                button3.Enabled = false;
                button4.Enabled = false;
                button5.Enabled = false;
                button6.Enabled = false;
                button7.Enabled = false;
                button8.Enabled = false;
                button9.Enabled = false;
                button10.Enabled = false;
                button11.Enabled = false;
                button12.Enabled = false;
            }
    
            public void stageget()
            {
                for (int x = 0; x < 10; x++)
                    stage[x] = 0;
                //获取流程
                i = 0;
                if (downloadversion.Checked)
                {
                    stagelist[i] = list[0];
                    stage[stage_flag] = 1;
                    i = i + 1;
                }
                stage_flag++;
                if (flashversion.Checked)
                {
                    stagelist[i] = list[1];
                    stage[stage_flag] = 1;
                    i = i + 1;
                }
                stage_flag++;
                if (openadb.Checked)
                {
                    stagelist[i] = list[2];
                    stage[stage_flag] = 1;
                    i = i + 1;
                }
                stage_flag++;
                if (getroot.Checked)
                {
                    stagelist[i] = list[3];
                    stage[stage_flag] = 1;
                    i = i + 1;
                }
                stage_flag++;
                if (setupwizard.Checked)
                {
                    stagelist[i] = list[4];
                    stage[stage_flag] = 1;
                    i = i + 1;
                }
                stage_flag++;
                if (fotabeforetest.Checked)
                {
                    stagelist[i] = list[5];
                    stage[stage_flag] = 1;
                    i = i + 1;
                }
                stage_flag++;
                if (fotaupgrade.Checked)
                {
                    stagelist[i] = list[6];
                    stage[stage_flag] = 1;
                    i = i + 1;
                }
                stage_flag++;
                if (fotaaftertest.Checked)
                {
                    stagelist[i] = list[7];
                    stage[stage_flag] = 1;
                    i = i + 1;
                }
                stage_flag++;
                if (fotadowngrade.Checked)
                {
                    stagelist[i] = list[8];
                    stage[stage_flag] = 1;
                    i = i + 1;
                }
                stage_flag++;
                if (Report.Checked)
                {
                    stagelist[i] = list[9];
                    stage[stage_flag] = 1;
                    i = i + 1;
                }
                stage_flag++;
            }
            //读历史纪录
            public void readhistory()
            {
                try
                {
                    //写历史记录文件夹
                    FileStream fs = new FileStream(strpath + "\\history.ini", FileMode.Create);
                    StreamWriter sw = new StreamWriter(fs, Encoding.UTF8);
                    //开始写入;
                    sw.WriteLine(arg1);
                    sw.WriteLine(project);
                    sw.WriteLine(arg2);
                    sw.WriteLine(fotaversion1);
                    sw.WriteLine(arg3);
                    sw.WriteLine(fotaversion2);
                    sw.WriteLine(arg4);
                    sw.WriteLine(fotaupp);
                    sw.WriteLine(arg5);
                    sw.WriteLine(fotadownp);
                    sw.WriteLine(arg6);
                    sw.WriteLine(rootapk);
                    //清空缓冲区
                    sw.Flush();
                    //关闭流
                    sw.Close();
                    fs.Close();
                }catch(Exception eee)
                {
                    
                }
            }
    
            //获取输入的参数
            public void getargs()
            {
                try
                {
                    project = "";
                    fotaversion1 = "";
                    fotaversion2 = "";
                    fotaupp = "";
                    fotadownp = "";
                    rootapk = "";
                    project = projectname.Text.ToString();
                    fotaversion1 = fotabeforeversion.Text.ToString();
                    fotaversion2 = fotaafterversion.Text.ToString();
                    fotaupp = fotauppack.Text.ToString();
                    fotadownp = fotadownpack.Text.ToString();
                    rootapk = rootapkpath.Text.ToString();
                    arg1 = ARG_1.Text.ToString();
                    arg2 = ARG_2.Text.ToString();
                    arg3 = ARG_3.Text.ToString();
                    arg4 = ARG_4.Text.ToString();
                    arg5 = ARG_5.Text.ToString();
                    arg6 = ARG_6.Text.ToString();
                }catch(Exception eee)
                {
    
                }
             
            }
            //这里是开始测试按钮点击函数
            private void button1_Click(object sender, EventArgs e)
            {
                //
                try
                {
                    //设置所有流程按钮不可点击
                    setbuttonfalse();
                    //每次点击都设置初始值
                    stagenum = 0;
                    stage_flag = 0;
                    //清除（TEXT)log的TXT
                    log.Clear();
                    //获取当前运行的目录
                    strpath = System.Windows.Forms.Application.StartupPath;
                    //每次运行删除上次log
                    if (File.Exists(strpath + "\\log\\log.txt"))
                        File.Delete(strpath + "\\log\\log.txt");
                    //不存在log文件夹则进行创建
                    if (!Directory.Exists(strpath + "\\log"))
                        Directory.CreateDirectory(strpath + "\\log");
                    //获取输入参数
                    getargs();
                    /*
                     * 设置环境变量，在C#中必须重启才有效，所以不用
                    System.Environment.SetEnvironmentVariable("PRODUCT_NAME", project, EnvironmentVariableTarget.Machine);
                    System.Environment.SetEnvironmentVariable("VERSION_PATH_IN_FTP", fotaversion1, EnvironmentVariableTarget.Machine);
                    System.Environment.SetEnvironmentVariable("FOTAUP_PATH_IN_FTP", fotaupp, EnvironmentVariableTarget.Machine);
                    System.Environment.SetEnvironmentVariable("FOTADOWN_PATH_IN_FTP", fotadownp, EnvironmentVariableTarget.Machine);
                    System.Environment.SetEnvironmentVariable("VERSIONTARGET_PATH_IN_FTP", fotaversion2, EnvironmentVariableTarget.Machine);
                    System.Environment.SetEnvironmentVariable("ROOTAPK_PATH_IN_FTP", rootapk, EnvironmentVariableTarget.Machine);
                    //MessageBox.Show(project+fotaversion1+fotaversion2+fotaupp+fotadownp);
                     */
    
                    //作为参数输入
                    env = " " + arg1 + " " + project + " " + arg2 + " " + fotaversion1 + " " + arg3 + " "  + fotaversion2 + " " + arg4 + " "+ fotaupp + " " + arg5 + " " + fotadownp + " " + arg6 + " " + rootapk + " ";
                    //写log的txt
                    log.AppendText(">------------------------------------------------------< args >-----------------------------------------------------<\r\n");
                    log.AppendText(" \r\n[ -- arg1 : " + project + " -- ]\r\n");
                    log.AppendText("[ -- arg2 : " + fotaversion1 + " -- ]\r\n");
                    log.AppendText("[ -- arg3 : " + fotaversion2 + " -- ]\r\n");
                    log.AppendText("[ -- arg4 : " + fotaupp + " -- ]\r\n");
                    log.AppendText("[ -- arg5 : " + fotadownp + " -- ]\r\n");
                    log.AppendText("[ -- arg6 : " + rootapk + " -- ]\r\n");
                    log.AppendText(">------------------------------------------------------< args >-----------------------------------------------------<\r\n\r\n");
               
    
                    //读取流程
                    stageget();
                    //根据流程多少设置 进度条最大值
                    progressBar1.Maximum = i * 10 + 10;
                    progressBar1.Value = 0;
    
                    //写历史记录
                    readhistory();
                    if (i == 0)//i = 0 说明没有选择checkbox
                    {
                        MessageBox.Show("必须选择一个过程！");
                    }
                    else
                    {
                        //设置开始测试按钮不可点击，设置停止测试按钮可点击
    
                        button1.Enabled = false;
                        button2.Enabled = true;
                        //选择tab1
                        this.tabControl1.SelectedIndex = 1;
    
                        log.AppendText(">------------------------------------------------------< stage >----------------------------------------------------<\r\n\r\n");
                        for (int x = 0; x < i; x++)
                        {
                            log.AppendText("Stage : " + stagelist[x] + "\r\n");
    
                        }
                        log.AppendText(">------------------------------------------------------< stage >----------------------------------------------------<\r\n\r\n");
                        log.AppendText("\r\n");
                        try
                        {
                            thread = new Thread(new ParameterizedThreadStart(Exe));
                            thread.Start();
                        }
                        catch (Exception exception)
                        {
                            MessageBox.Show(exception.ToString());
    
                            throw exception;
                        }
                    }
                }
                catch (Exception eee)
                {
                    MessageBox.Show(eee.ToString());
                    throw eee;
                }
            }
    
            public void Exe(object obj)
            {
                try
                {
                    String filepath = "runtest.exe";
                    String args = "";
                    
                    for (int x = 0; x < i; x++)
                    {
                        args = args + stagelist[x] + " ";
    
                        
                    }
                    args = env + args;
                    log.AppendText(">------------------------------------------------------< envs >-----------------------------------------------------<\r\n\r\n");
                    log.AppendText("[ -- runtest.exe all args is \r\n" + args);
                    log.AppendText("\r\n>------------------------------------------------------< envs >-----------------------------------------------------<\r\n\r\n");
                    //
                    cmd  = new Process();
                    cmd.StartInfo.FileName = filepath;
                    cmd.StartInfo.Arguments = args;
                        //将cmd的标准输入和输出全部重定向到.NET的程序里   
                    cmd.StartInfo.RedirectStandardInput = true;//标准输入   
                    cmd.StartInfo.RedirectStandardOutput = true;//标准输出   
                    cmd.StartInfo.UseShellExecute = false;//此处必须为false否则引发异常   
                    cmd.StartInfo.CreateNoWindow = true;//不显示命令行窗口  
                    cmd.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
                    cmd.Start();
                    cmd.OutputDataReceived += new DataReceivedEventHandler(cmd_OutputDataReceived);
                    cmd.BeginOutputReadLine();
                    Application.DoEvents();
                    cmd.WaitForExit();
                    String msg;
                    if (cmd.ExitCode != 0)
                    {
                        ShowMessage(cmd.StandardOutput.ReadToEnd());
                    }
                        
                        
                        //if (cmd.ExitCode != 0)
                        //{
                        //ShowMessage(cmd.StandardOutput.ReadToEnd());
                        //}
              
                        cmd.Close();
                    
                    }
                
                catch (Exception exception)
                {
                    MessageBox.Show(exception.ToString());
                    throw exception;
                }
                /*
                ThreadPool.SetMaxThreads(1, 1);
                ThreadPool.QueueUserWorkItem(new WaitCallback(ExeThread), cmd);*/
            }
    
    
            void cmd_OutputDataReceived(object sender, DataReceivedEventArgs e)
            {
                ShowMessage(e.Data);
            }
    
    
            private delegate void ShowMessageHandler(string msg);
    
            //显示message
            private void ShowMessage(string msg)
            {
                try
                {
                    if (this.InvokeRequired)
                    {
                        this.BeginInvoke(new ShowMessageHandler(ShowMessage), new object[] { msg });
                    }
                    else
                    {
                        if (msg != null)
                        {
    
                            log.AppendText(msg + "\r\n");
    
                            findStage(msg);
                            if (msg.Equals("[ ** test finished ** ]"))
                            {
                                button1.Enabled = true;
                                progressBar1.Value = progressBar1.Value + 10;
                            }
                            if(msg.Contains("<error>"))
                            {
                                button1.Enabled = true;
                                log.AppendText("\r\n>---[ Check the error info ↑ ]---<\r\n\r\n");
                                
                            }
                                
                        }
                    }
                }
                catch (Exception eee)
                {
                    throw eee;
                }
            }
    
            //分流程写log文件
            private void findStage(String message)
            {
                try
                {
                    //写总log文件
                    FileStream fs1;
                    fs1 = new FileStream(strpath + "\\log\\log.txt", FileMode.Append);
                    StreamWriter sw1 = new StreamWriter(fs1, Encoding.UTF8);
                    //开始写入;
                    //清空缓冲区
                    sw1.WriteLine(message);
                    sw1.Flush();
                    //关闭流
                    sw1.Close();
                    fs1.Close();
    
                   
                }
                catch (Exception eee)
                {
                    throw eee;
                }
                int jright = 1;
                //判断流程
                if (stagelist[stagenum]!=null && message.Contains(stagelist[stagenum]))
                {
                    
                    stagenum++;
                    //设置对应的流程button为true
                    setbuttontrue(stagenum);
                    textBox2.Text = stagelist[stagenum - 1];
                    if (File.Exists(strpath + "\\log\\" + stagelist[stagenum-1] + ".txt"))
                        File.Delete(strpath + "\\log\\" + stagelist[stagenum-1] + ".txt");
                    jright = 0;
    
                }
                else if (stagenum == 0)
                {
                    //do noting here
                }
                else
                {
                    try
                    {
                        FileStream fs;
                        if(jright == 0)//为0则创建新的log文件
                            fs = new FileStream(strpath + "\\log\\" + stagelist[stagenum - 1] + ".txt", FileMode.Create);
                        else
                            fs = new FileStream(strpath + "\\log\\" + stagelist[stagenum - 1] + ".txt", FileMode.Append);
    
                        StreamWriter sw = new StreamWriter(fs, Encoding.UTF8);
                        //开始写入;
                        //清空缓冲区
                        sw.WriteLine(message);
                        sw.Flush();
                        //关闭流
                        sw.Close();
                        fs.Close();
                    }
                    catch (Exception eee)
                    {
                        MessageBox.Show(eee.ToString());
                    }
                }
                
            }
    
    
            //设置对应流程按钮可点击
            //nubinput:对应按钮的下标
            public void setbuttontrue(int nubinput)
            {
                try
                {
    
                    int j = 0;
                    for (int i = 0; i < 10; i++)
                    {
                        if (stage[i] == 1)
                            j++;
    
                        if (j == nubinput)
                        {
                            buttonx[i].Enabled = true;
    
                            break;
                        }
    
                    }
                    //将进程加10
                    progressBar1.Value = progressBar1.Value + 10;
                    progressBar1.Enabled = true;
                }
                catch (Exception eee)
                {
                    throw eee;
                }
            }
    
    
            private void log_TextChanged(object sender, EventArgs e)
            {
    
            }
    
    
            //结束测试按钮
            //结束掉runtest.exe的所有进程
            private void button2_Click(object sender, EventArgs e)
            {
                log.AppendText("[ ** END TEST ** ]");
                try  
                {  
                    //模糊进程名  枚举  
                    //Process[] ps = Process.GetProcesses();  //进程集合  
                    foreach (Process p in Process.GetProcesses())  
                    {  
                        Console.WriteLine(p.ProcessName + p.Id);  
      
                        if (p.ProcessName.IndexOf("runtest") > -1)  //第一个字符匹配的话为0，这与VB不同  
                        {
                            log.AppendText(p.ToString());
                            p.Kill();  
                            
                        }  
                    }  
                }  
                catch  
                {  
      
                } 
                
                button2.Enabled = false;
                button1.Enabled = true;
            }
    
    
            //流程按钮函数
            //点击打开log
            private void button3_Click(object sender, EventArgs e)
            {
                if (File.Exists(strpath + "\\log\\" + list[0] + ".txt"))
                    System.Diagnostics.Process.Start("notepad.exe", strpath + "\\log\\"+list[0]+".txt");
            }
            private void button4_Click(object sender, EventArgs e)
            {
                if (File.Exists(strpath + "\\log\\" + list[1] + ".txt"))
                    System.Diagnostics.Process.Start("notepad.exe", strpath + "\\log\\" + list[1] + ".txt");
            }
            private void button5_Click(object sender, EventArgs e)
            {
                if (File.Exists(strpath + "\\log\\" + list[2] + ".txt"))
                    System.Diagnostics.Process.Start("notepad.exe", strpath + "\\log\\" + list[2] + ".txt");
            }
            private void button6_Click(object sender, EventArgs e)
            {
                if (File.Exists(strpath + "\\log\\" + list[3] + ".txt"))
                    System.Diagnostics.Process.Start("notepad.exe", strpath + "\\log\\" + list[3] + ".txt");
            }
            private void button7_Click(object sender, EventArgs e)
            {
                if (File.Exists(strpath + "\\log\\" + list[4] + ".txt"))
                    System.Diagnostics.Process.Start("notepad.exe", strpath + "\\log\\" + list[4] + ".txt");
            }
            private void button8_Click(object sender, EventArgs e)
            {
                if (File.Exists(strpath + "\\log\\" + list[5] + ".txt"))
                    System.Diagnostics.Process.Start("notepad.exe", strpath + "\\log\\" + list[5] + ".txt");
            }
            private void button9_Click(object sender, EventArgs e)
            {
                if (File.Exists(strpath + "\\log\\" + list[6] + ".txt"))
                    System.Diagnostics.Process.Start("notepad.exe", strpath + "\\log\\" + list[6] + ".txt");
            }
            private void button10_Click(object sender, EventArgs e)
            {
                if (File.Exists(strpath + "\\log\\" + list[7] + ".txt"))
                    System.Diagnostics.Process.Start("notepad.exe", strpath + "\\log\\" + list[7] + ".txt");
            }
    
            private void button11_Click(object sender, EventArgs e)
            {
                if (File.Exists(strpath + "\\log\\" + list[8] + ".txt"))
                    System.Diagnostics.Process.Start("notepad.exe", strpath + "\\log\\" + list[8] + ".txt");
            }
    
            private void button12_Click(object sender, EventArgs e)
            {
                this.tabControl1.SelectedIndex = 2;
                if (File.Exists(strpath + "\\testdata\\report\\summary.html"))
                    webBrowser1.Navigate(strpath + "\\testdata\\report\\summary.html");
                else
                    webBrowser1.DocumentText = "Do not find Report !";
            }
    
            private void button13_Click(object sender, EventArgs e)
            {
                if (File.Exists(strpath + "\\testdata\\report\\summary.html"))
                    System.Diagnostics.Process.Start(strpath + "\\testdata\\report\\summary.html");  
            }
    
        }
    }
        
        

```


### LINK

*  [**github code link**](https://github.com/tsbxmw/autotest)