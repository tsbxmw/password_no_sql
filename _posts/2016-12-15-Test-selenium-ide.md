---
layout: post
title: Selenium Test 初探
categories: Test
description: 笔记
keywords: selenium, test, selenium ide
---

一个简单的用例

## 链接

* [ Selenium Test ](https://tsbxmw.github.io/2016/12/15/Test-selenium-ide/)

##  内容

### selenium

> selenium

   一款开源测试框架，用来做自动化测试

> 支持的语言

    java
    c#
    python
    ruby

> IDE

   对浏览器有支持的IDE，作为插件安装。
   1、可以用来录制脚本
   2、可以导出脚本为各种语言
   3、可以进行测试
    
> 优点

  录制简单，使用方便，导出代码多样性


> 例子

   使用ide录制脚本

* 打开页面
* 输入username
* 输入password
* 点击登录按钮
* 进入页面
* 点击退出按钮

![](/images/blog/selenium/img_001.PNG)

> java

```java

    package com.example.tests;

    import java.util.regex.Pattern;
    import java.util.concurrent.TimeUnit;
    import org.junit.*;
    import static org.junit.Assert.*;
    import static org.hamcrest.CoreMatchers.*;
    import org.openqa.selenium.*;
    import org.openqa.selenium.firefox.FirefoxDriver;
    import org.openqa.selenium.support.ui.Select;

    public class IdeJava {
      private WebDriver driver;
      private String baseUrl;
      private boolean acceptNextAlert = true;
      private StringBuffer verificationErrors = new StringBuffer();

      @Before
      public void setUp() throws Exception {
        driver = new FirefoxDriver();
        baseUrl = "http://10.63.220.2:8080/visual/login.jsp";
        driver.manage().timeouts().implicitlyWait(30, TimeUnit.SECONDS);
      }

      @Test
      public void testIdeJava() throws Exception {
        driver.findElement(By.linkText("管理员登录")).click();
        driver.findElement(By.name("username")).clear();
        driver.findElement(By.name("username")).sendKeys("root");
        driver.findElement(By.name("password")).clear();
        driver.findElement(By.name("password")).sendKeys("zte");
        driver.findElement(By.cssSelector("input[type=\"submit\"]")).click();
        driver.findElement(By.id("quit")).click();
        assertTrue(closeAlertAndGetItsText().matches("^是否退出[\\s\\S]$"));
      }

      @After
      public void tearDown() throws Exception {
        driver.quit();
        String verificationErrorString = verificationErrors.toString();
        if (!"".equals(verificationErrorString)) {
          fail(verificationErrorString);
        }
      }

      private boolean isElementPresent(By by) {
        try {
          driver.findElement(by);
          return true;
        } catch (NoSuchElementException e) {
          return false;
        }
      }

      private boolean isAlertPresent() {
        try {
          driver.switchTo().alert();
          return true;
        } catch (NoAlertPresentException e) {
          return false;
        }
      }

      private String closeAlertAndGetItsText() {
        try {
          Alert alert = driver.switchTo().alert();
          String alertText = alert.getText();
          if (acceptNextAlert) {
            alert.accept();
          } else {
            alert.dismiss();
          }
          return alertText;
        } finally {
          acceptNextAlert = true;
        }
      }
    }
```

> python2

```python

    # -*- coding: utf-8 -*-
    from selenium import webdriver
    from selenium.webdriver.common.by import By
    from selenium.webdriver.common.keys import Keys
    from selenium.webdriver.support.ui import Select
    from selenium.common.exceptions import NoSuchElementException
    from selenium.common.exceptions import NoAlertPresentException
    import unittest, time, re

    class IdePython(unittest.TestCase):
        def setUp(self):
            self.driver = webdriver.Firefox()
            self.driver.implicitly_wait(30)
            self.base_url = "http://10.63.220.2:8080/visual/login.jsp"
            self.verificationErrors = []
            self.accept_next_alert = True
        
        def test_ide_python(self):
            driver = self.driver
            driver.find_element_by_link_text(u"管理员登录").click()
            driver.find_element_by_name("username").clear()
            driver.find_element_by_name("username").send_keys("root")
            driver.find_element_by_name("password").clear()
            driver.find_element_by_name("password").send_keys("zte")
            driver.find_element_by_css_selector("input[type=\"submit\"]").click()
            driver.find_element_by_id("quit").click()
            self.assertRegexpMatches(self.close_alert_and_get_its_text(), r"^是否退出[\s\S]$")
        
        def is_element_present(self, how, what):
            try: self.driver.find_element(by=how, value=what)
            except NoSuchElementException as e: return False
            return True
        
        def is_alert_present(self):
            try: self.driver.switch_to_alert()
            except NoAlertPresentException as e: return False
            return True
        
        def close_alert_and_get_its_text(self):
            try:
                alert = self.driver.switch_to_alert()
                alert_text = alert.text
                if self.accept_next_alert:
                    alert.accept()
                else:
                    alert.dismiss()
                return alert_text
            finally: self.accept_next_alert = True
        
        def tearDown(self):
            self.driver.quit()
            self.assertEqual([], self.verificationErrors)

    if __name__ == "__main__":
        unittest.main()
```

> ruby

```ruby

    require "json"
    require "selenium-webdriver"
    require "rspec"
    include RSpec::Expectations

    describe "IdeRuby" do

      before(:each) do
        @driver = Selenium::WebDriver.for :firefox
        @base_url = "http://10.63.220.2:8080/visual/login.jsp"
        @accept_next_alert = true
        @driver.manage.timeouts.implicit_wait = 30
        @verification_errors = []
      end
      
      after(:each) do
        @driver.quit
        @verification_errors.should == []
      end
      
      it "test_ide_ruby" do
        @driver.find_element(:link, "管理员登录").click
        @driver.find_element(:name, "username").clear
        @driver.find_element(:name, "username").send_keys "root"
        @driver.find_element(:name, "password").clear
        @driver.find_element(:name, "password").send_keys "zte"
        @driver.find_element(:css, "input[type=\"submit\"]").click
        @driver.find_element(:id, "quit").click
        close_alert_and_get_its_text().should =~ /^是否退出[\s\S]$/
      end
      
      def element_present?(how, what)
        ${receiver}.find_element(how, what)
        true
      rescue Selenium::WebDriver::Error::NoSuchElementError
        false
      end
      
      def alert_present?()
        ${receiver}.switch_to.alert
        true
      rescue Selenium::WebDriver::Error::NoAlertPresentError
        false
      end
      
      def verify(&blk)
        yield
      rescue ExpectationNotMetError => ex
        @verification_errors << ex
      end
      
      def close_alert_and_get_its_text(how, what)
        alert = ${receiver}.switch_to().alert()
        alert_text = alert.text
        if (@accept_next_alert) then
          alert.accept()
        else
          alert.dismiss()
        end
        alert_text
      ensure
        @accept_next_alert = true
      end
    end
```

### pyton 自己写的脚本（进行对比）

```python

    # -*- coding: utf-8 -*-
    from selenium import webdriver
    from selenium.common.exceptions import NoSuchElementException
    from selenium.webdriver.common.keys import Keys
    import time
    from pprint import pprint


    class WebTest:
        def __init__(self):
            print "test start ..."

        def beforeTest(self):
            self.browser = webdriver.Firefox()
            self.browser.set_window_position(800,0)
            self.browser.get('http://10.63.220.2:8080/visual/login.jsp')    

        def testlogin(self):
            try:
                username = self.browser.find_element_by_name("username")
                assert username
                username.send_keys("root")
                password = self.browser.find_element_by_name("password")
                assert password
                password.send_keys("zte")
                button_login = self.browser.find_element_by_xpath("//td/input[@type='submit']")
                assert button_login
                button_login.click()
            except Exception,e:
                raise(e)

        def afterTest(self):
            self.browser.quit()
            print "test end..."


    if __name__=='__main__':
        webtest = WebTest()
        webtest.beforeTest()
        webtest.testlogin()
        webtest.afterTest()

```




### LINK

* [ Selenium Test ](https://tsbxmw.github.io/2016/12/15/Test-selenium-ide/)