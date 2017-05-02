---
layout: post
title: jenkins autotest
categories: jenkins
description: bookmark
keywords: jenkins, autotest, groovy
---

auto test struct of jenkins with groovy script 

## 链接

* nothing here

##  摘要
    
    Jenkins Auto Test Struct 

----------

## 内容    

### Pipeline -- jenkins file

```java

    import hudson.model.*
    import jenkins.model.Jenkins
    import hudson.AbortException
    import org.jenkinsci.plugins.workflow.steps.FlowInterruptedException
    import static groovy.io.FileType.FILES

    echo "-----------------------------------------------------------------------------"
    echo "Start Test now ... "
    echo "PRODUCT NAME : " + "${PRODUCT_NAME}"
    echo "Device Ip : " + "${IP_SLAMWARE}"
    echo "-----------------------------------------------------------------------------"
    echo "Test Stages : " + "${TEST_STAGES}"
    echo "-----------------------------------------------------------------------------"



    node("${PRODUCT_NAME}") {
        
        configEnv()
        echo env.PATH
        echo env.PYTHONPATH
        
        //when stage test failed, stop the whole test 
        testTypesStopOnFailed = ["Download Daily Build","Flash Daily Build","Flash Down and Up","Flash One Build","Simulator Mode","Send Report"]
        //the stage which is not need send report
        noNeedReportStage = ["Send Report"]
        
        testTypes = "${TEST_STAGES}".replaceAll(/\r\n|\r/,'\n').tokenize('\n')
        //at first the sendreport is not true
        sendReport = false
        
        //get the code from the git server , check out to the local dir "checkout"
        //dir("checkout")
        //{
           //checkout changelog: false, poll: false, scm: [$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false, extensions: [[$class: 'CleanBeforeCheckout'], [$class: 'CheckoutOption', timeout: 1], [$class: 'CloneOption', depth: 0, noTags: true, reference: '', shallow: true]], submoduleCfg: [], userRemoteConfigs: [[credentialsId: '6e519a56-9857-46cc-ad30-369cd6984189', url: 'https://stash.slamtec.com/scm/zeus/topic_zeus_test.git']]]
           
        //}
        
        checkout("https://wei.meng:TdCnps1o@stash.slamtec.com/scm/zeus/topic_zeus_test.git","checkout")
        
        //copy the code out of the checkout , just copy the stage code in the TEST_STAGES
        for(xxx in testTypes)
        {
            bat "xcopy /yse \".\\checkout\\" + xxx + "\\*\" \".\\" + xxx + "\\\""
        }
        
        //copy the pylibs and tools to the local dir
        bat "xcopy /yse .\\checkout\\base\\* .\\base\\"
        bat "xcopy /yse .\\checkout\\testdata\\* .\\testdata\\"
        
        //delete the reports and jsons file and logs
        bat "del /Q .\\testdata\\report\\*"
        bat "del /Q .\\testdata\\report\\json\\*"
        bat "del /Q \".\\testdata\\report\\log\\Flash Daily Build\\*\""
        bat "del /Q \".\\testdata\\report\\log\\Flash Down and Up\\*\""
        bat "del /Q \".\\testdata\\report\\log\\Flash One Build\\*\""
        bat "del /Q \".\\testdata\\report\\log\\Flash Wrong Build\\*\""
        bat "del /Q \".\\testdata\\report\\log\\MoveTest\\*\""
        
        //if TEST_STAGES contains the Send Report stage, we send the report
        if(testTypes.contains("Send Report")) 
        {
            sendReport = true
            echo "contain Send Report"
        }
        
        // run the test stage in turn
        for(t in testTypes)
        {
            if(t=="Send Report")
                continue
            echo "-----------------------------------------"
            echo " stage " + t
            stop_on_fail = false
            if(testTypesStopOnFailed.contains(t)) 
            {
                stop_on_fail = true
            }
            RunTestStage(t, sendReport, stop_on_fail)
            echo "-----------------------------------------"
        }
        publishTestReport(testTypes, noNeedReportStage, sendReport)
    }

    def RunTestStage(this_stage, sendReport, stop_on_fail=true) {
        stage this_stage
        env.CURRENT_TEST = this_stage
        try {
            dir(this_stage) 
            {
                if(isUnix()) 
                {
                    sh 'sh ./cirun'
                } 
                else {
                    def cmd = '''cirun.cmd'''
                    if(env.WINDOWS_SET_CHCP!=null) 
                    {
                        cmd="chcp " + env.WINDOWS_SET_CHCP +'\r\n' + cmd
                    }
                    bat cmd
                }
            
                try {
                    if(fileExists('report/report.xml'))
                        publishXML source:"report/report.xml",target:this_stage+".xml"
                }
                catch(Exception e) {
                        echo "no xml report"
                }
            }
        } 
        catch(org.jenkinsci.plugins.workflow.steps.FlowInterruptedException e) 
        {
            echo "org.jenkinsci.plugins.workflow.steps.FlowInterrupted"
            echo "org.jenkinsci.plugins.workflow.steps.FlowInterruptedException"
            echo e.toString()
            throw e
        } 
        catch(Exception e) 
        {
            echo e.toString()
            if(stop_on_fail) 
            {
                if(sendReport)
                {
                    publishFailed(this_stage,e.toString())
                }
                throw e
            }
        }
    }


    def configEnv() {
        
        try{ env.PRODUCT_NAME = "${PRODUCT_NAME}" }catch(Exception e) {}
        try{ env.SLAMWARE_PATH = "${SLAMWARE_PATH}" }catch(Exception e) {}
        try{ env.IP_SLAMWARE = "${IP_SLAMWARE}" }catch(Exception e){}
        try{ env.TEST_STAGES = "${TEST_STAGES}" }catch(Exception e){}
        try{ env.COUNT_OF_DOWNUP = "${COUNT_OF_DOWNUP}" }catch(Exception e){}
        try{ env.COUNT_OF_ONEBUILD = "${COUNT_OF_ONEBUILD}" }catch(Exception e){}
        try{ env.TEST_NAME = "${TEST_NAME}" }catch(Exception e){}
        try{ env.NAME_OF_ONEBUILD = "${NAME_OF_ONEBUILD}" }catch(Exception e){}
        try{ env.NAME_OF_DOWNBUILD = "${NAME_OF_DOWNBUILD}" }catch(Exception e){}
        try{ env.NAME_OF_UPBUILD = "${NAME_OF_UPBUILD}" }catch(Exception e){}
        try{ env.NAME_OF_WRONGBUILD = "${NAME_OF_WRONGBUILD}" }catch(Exception e){}

            a = env.PYTHONPATH
            pylib = pwd() + "\\base\\tools\\pylibs"
            if(a) 
            {
                env.PYTHONPATH = a + ";"+ pylib
            } else 
            {
                env.PYTHONPATH = pylib
            }
            echo env.PYTHONPATH
            env.REPORT_DIR = pwd() + "\\report"
            env.PATH = pwd() + "\\base\\tools\\win32tools;" + pwd() + "\\base\\tools\\ant\\bin;${env.PATH}"
        env.PYTHONUNBUFFERED="1"
    }

    //do not complete this function
    def publishFailed(stage_name,errorinfo) {
        subjects = stage_name + " Failed!"
        detail = errorinfo
        
        mail body: detail, cc: "${FAIL_MAIL_TO}", charset: 'UTF-8', mimeType: 'text/html',subject:subjects , to: "${FAIL_MAIL_TO}"
        
    }

    def publishTestReport(testTypes, noNeedReportStage, sendReport) {
        
        reportDir = "testdata/report"
        reportFiles = ""
        for(t in testTypes) 
        {
            if(!noNeedReportStage.contains(t)) 
            {
                bat 'copy  \"' + t +'\\report\\\"* ' + "testdata\\report\\"
                cmdstr = "move testdata\\report\\report.html \"testdata\\report\\" + t + '.html\"'
                bat cmdstr
                bat 'copy  \"' + t +'\\\"testinfo.json testdata\\report\\json\\'
                bat "move testdata\\report\\json\\testinfo.json \"testdata\\report\\json\\" + t + '.json\"'
                //not complete
                bat 'copy \"' + t + '\\log\\\"* ' + "\"testdata\\report\\log\\" + t + "\\\""
                
                reportFiles = reportFiles + t +".html,"
            }
            
        }
        
        
        if(sendReport) 
        {
            stage "Create Report"
            dir("Send Report")
            {
                execCommand("cirun.cmd")
            }
           
        }
        
        reportFiles = reportFiles + "summary.html"
        echo reportFiles
        name = "TestReport"
        publishHTML(target:[allowMissing: true, alwaysLinkToLastBuild: false, keepAll: true, reportDir: reportDir, reportFiles: reportFiles, reportName: name])
        
        if(sendReport){
            //send test mail to wei.meng
            stage "Send mail"
            String mailbody = readFile(".\\testdata\\report\\summary.html")
            String subjects = 'ZEUS AUTO TEST REPORT -- ' + env.JOB_NAME + "--" +  env.BUILD_NUMBER
            echo subjects
            mail body: mailbody, cc: "${MAIL_CC}", charset: 'UTF-8', mimeType: 'text/html',subject:subjects , to: "${MAIL_TO}"
        
        }
        
        //push the report to the share dir not complete
        //push the log file to the share dir
        bat "mkdir \\\\10.254.1.27\\TestReport\\%JOB_NAME%\\%BUILD_NUMBER%"
        bat "xcopy /yse .\\testdata\\report\\* \\\\10.254.1.27\\TestReport\\%JOB_NAME%\\%BUILD_NUMBER%\\"
        
    }

    //do not work fine at the jenkins.slamtec.com
    def checkout(remote,local)
    {
        str = "if exist " + local + " ( cd " + local + " & git pull " + remote + " ) else ( md " + local + " & git clone " + remote + " " + local + "\\ )"
        echo str
        bat str
        //bat "git clone " + remote + " " + local + "\\"
    }

    def execCommand(cmd) {
        if(isUnix()) 
        {
            sh cmd
        } 
        else 
        {
            bat cmd
        }
    }

```

> #### LINK

* nothing to show
