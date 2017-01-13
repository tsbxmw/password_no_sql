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
    
    利用 C# 程序模拟 jenkins 连续运行的 pipeline

## 内容    

### 界面

![](/images/blog/python/img_002.PNG)
    
### 内容
    
> 调用其他程序如bat的时候，会造成异步与同步同时出现，导致 Exception 。
> 解决方法：

*  直接调用 python生成的 exe
*  bat中不掺杂其他的非windows自带语句
*  win32 console exe中不调用其他程序

```C  

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
            String strpath = "";
            String[] stagelist = new String[10];
            String env = "";
            int i;
            Thread thread;
            Process cmd;
            private void Form1_Load(object sender, EventArgs e)
            {
                Control.CheckForIllegalCrossThreadCalls = false;
                
                String path = System.Windows.Forms.Application.StartupPath;
                if (File.Exists(@path + "\\history.ini"))//如果不存在就创建file文件夹
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
                                projectname.Text = line;
                                break;
                            case 1:
                                fotabeforeversion.Text = line;
                                break;
                            case 2:
                                fotaafterversion.Text = line;
                                break;
                            case 3:
                                fotauppack.Text = line;
                                break;
                            case 4:
                                fotadownpack.Text = line;
                                break;
                            case 5:
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
           
            private void button1_Click(object sender, EventArgs e)
            {

                log.Clear(); 
                String project = "", fotaversion1 = "", fotaversion2 = "", fotaupp = "", fotadownp = "",rootapk="";
                
                String[] list = { "00DownloadVersion",
                    "01FlashVersion",
                    "02Fota_open_adb",
                    "03getroot",
                    "04setupwizard",
                    "05FotaBeforeTest",
                    "06FotaUpgradeCompare",
                    "07FotaAfterTest" };

                strpath = System.Windows.Forms.Application.StartupPath;

                project = projectname.Text.ToString();
                fotaversion1 = fotabeforeversion.Text.ToString();
                fotaversion2 = fotaafterversion.Text.ToString();
                fotaupp = fotauppack.Text.ToString();
                fotadownp = fotadownpack.Text.ToString();
                rootapk = rootapkpath.Text.ToString();
                /*
                System.Environment.SetEnvironmentVariable("PRODUCT_NAME", project, EnvironmentVariableTarget.Machine);
                System.Environment.SetEnvironmentVariable("VERSION_PATH_IN_FTP", fotaversion1, EnvironmentVariableTarget.Machine);
                System.Environment.SetEnvironmentVariable("FOTAUP_PATH_IN_FTP", fotaupp, EnvironmentVariableTarget.Machine);
                System.Environment.SetEnvironmentVariable("FOTADOWN_PATH_IN_FTP", fotadownp, EnvironmentVariableTarget.Machine);
                System.Environment.SetEnvironmentVariable("VERSIONTARGET_PATH_IN_FTP", fotaversion2, EnvironmentVariableTarget.Machine);
                System.Environment.SetEnvironmentVariable("ROOTAPK_PATH_IN_FTP", rootapk, EnvironmentVariableTarget.Machine);
                //MessageBox.Show(project+fotaversion1+fotaversion2+fotaupp+fotadownp);
                 */
                

                env = " " + project + " " + fotaversion1 + " " + fotaversion2 + " " + fotaupp + " " + fotadownp + " " + rootapk + " ";
                log.AppendText("----------------------------------get input---------------------------------\r\n");
                log.AppendText(" \r\nproject name is : " + project + "\r\n");
                log.AppendText("fota target version is : " + fotaversion2 + "\r\n");
                log.AppendText("fota upgrade package is : " + fotaupp + "\r\n");
                log.AppendText("fota downgrade package is : " + fotadownp + "\r\n");
                log.AppendText("fota root apk is : " + rootapk + "\r\n");
                log.AppendText("-------------------------------------------------------------------\r\n\r\n");
                log.AppendText("    all is " + env + "\r\n");
                log.AppendText("-------------------------------------------------------------------\r\n\r\n");

                i = 0;
                if (downloadversion.Checked)
                {
                    stagelist[i] = list[0];
                    i = i+1;
                }
                if (flashversion.Checked)
                {
                    stagelist[i] = list[1];
                    i = i + 1;
                }
                if (openadb.Checked)
                {
                    stagelist[i] = list[2];
                    i = i + 1;
                }
                if (getroot.Checked)
                {
                    stagelist[i] = list[3];
                    i = i + 1;
                }
                if (setupwizard.Checked)
                {
                    stagelist[i] = list[4];
                    i = i + 1;
                }
                if (fotabeforetest.Checked)
                {
                    stagelist[i] = list[5];
                    i = i + 1;
                }
                if (fotaupgrade.Checked)
                {
                    stagelist[i] = list[6];
                    i = i + 1;
                }
                if (fotaaftertest.Checked)
                {
                    stagelist[i] = list[7];
                    i = i + 1;
                }
                FileStream fs = new FileStream(strpath + "\\history.ini", FileMode.Create);
                StreamWriter sw = new StreamWriter(fs, Encoding.UTF8);
                //开始写入;
                sw.WriteLine(project);
                sw.WriteLine(fotaversion1);
                sw.WriteLine(fotaversion2);
                sw.WriteLine(fotaupp);
                sw.WriteLine(fotadownp);
                sw.WriteLine(rootapk);
                //清空缓冲区
                sw.Flush();
                //关闭流
                sw.Close();
                fs.Close();
                if (i == 0)
                {
                    MessageBox.Show("必须选择一个过程！");

                }
                else
                {
                    button1.Enabled = false;
                    button2.Enabled = true;
                    this.tabControl1.SelectedIndex = 1;
                    log.AppendText("---------------------------------- Test Start now ... ---------------------------------\r\n");
                    for (int x = 0; x < i; x++)
                    {
                        log.AppendText("Stage : " + stagelist[x] + "   ");

                    }
                    log.AppendText("\r\n---------------------------------- Test Start now ... ---------------------------------\r\n");
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
                    log.AppendText(args);
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

            private void ShowMessage(string msg)
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
                    }
                }
            }

            private void log_TextChanged(object sender, EventArgs e)
            {

            }

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

        }
    }

```

### 调用的 python 生成的小程序

* 安装 pyinstaller
* 安装 pypiwin32

```python
    
    #encoding=utf-8

    import sys
    import os

    def curfiledir():
        path = os.getcwd()
        if os.path.isdir(path):
            return path
        elif os.path.isfile(path):
            return os.path.dirname(path)


    if __name__=="__main__":
        args = sys.argv
        if len(args) < 7:
            print ("wrong with args ")
        par_dir = curfiledir()
        
        os.environ["PRODUCT_NAME"] = args[1]
        os.environ["VERSION_PATH_IN_FTP"] = args[2]
        os.environ["VERSIONTARGET_PATH_IN_FTP"] = args[3]
        os.environ["FOTAUP_PATH_IN_FTP"] = args[4]    
        os.environ["FOTADOWN_PATH_IN_FTP"] = args[5]
        os.environ["ROOTAPK_PATH_IN_FTP"] = args[6]

        for i in range(7,len(args)):
            print ("[ -- Stage " +args[i] +" -- ]")
            os.chdir(par_dir+"\\"+args[i])
            if os.path.exists("cirun.cmd"):
                os.system("cirun.cmd")
            else:
                print ("<* cirun.cmd is missing , please check path*>")
            print ("[ -- Finish -- ]")
        print ("[ ** test finished ** ]")
```

### LINK

*  no link here 