---
layout: post
title: Android Espresso Test
categories: Test
description: 笔记
keywords: android, test, Espresso
---

一个简单的用例

## 链接

* [Android Espresso Test](https://tsbxmw.github.io/2016/12/01/Test-Espresso/)

##  内容

  Android auto test of Espresso
  一个简单的用例，用来测试登录界面
  PS:使用的app是xxx1项目。

* 使用mavenCentral()代替jcenter()
  在project的build.gradle中，替换：

```gradle

    buildscript {
        repositories {
            //jcenter()
            mavenCentral()
        }
        dependencies {
            classpath 'com.android.tools.build:gradle:2.2.0'
        }
    }

    allprojects {
        repositories {
            //jcenter()
            mavenCentral()
            maven { url 'http://repo1.maven.org/maven2' }
        }
    }
```

* 在app的build.gradle中添加espresso依赖项
androidTestCompile ('com.android.support.test.espresso:espresso-core:2.2.2'
androidTestCompile ('com.android.support.test:runner:0.5' )
androidTestCompile ('junit:junit:4.12')

```gradle

        apply plugin: 'com.android.application'

        android {
            compileSdkVersion 23
            buildToolsVersion '23.0.3'

            defaultConfig {
                applicationId "com.example.app_test"
                minSdkVersion 23
                targetSdkVersion 23
                testInstrumentationRunner "android.support.test.runner.AndroidJUnitRunner"
            }

            buildTypes {
                release {
                    minifyEnabled false
                    proguardFiles getDefaultProguardFile('proguard-android.txt'), 'proguard-rules.txt'
                }
            }
        }

        dependencies {
            compile 'com.android.support:appcompat-v7:24.2.1'
            compile files('libs/core-3.1.0.jar')
            compile files('libs/org.apache.http.legacy.jar')
            compile 'pl.droidsonroids.gif:android-gif-drawable:1.2.2'
            androidTestCompile ('com.android.support.test.espresso:espresso-core:2.2.2') {
                exclude group: 'com.android.support'
            }
            androidTestCompile ('com.android.support.test:runner:0.5' ){
                exclude group: 'com.android.support'
            }
            androidTestCompile ('junit:junit:4.12'){
                exclude group : ' com.android.support'
            }
        }
```
* 进行编程

```java

        package AndroidTest;
        import android.app.Activity;
        import android.support.test.rule.ActivityTestRule;
        import com.example.app_test.MainActivity;
        import com.example.app_test.R;
        import org.hamcrest.Matcher;
        import static android.support.test.espresso.Espresso.closeSoftKeyboard;
        import static android.support.test.espresso.Espresso.onView;
        import static android.support.test.espresso.action.ViewActions.clearText;
        import static android.support.test.espresso.action.ViewActions.click;
        import static android.support.test.espresso.action.ViewActions.typeText;
        import static android.support.test.espresso.assertion.ViewAssertions.matches;
        import static android.support.test.espresso.matcher.ViewMatchers.isChecked;
        import static android.support.test.espresso.matcher.ViewMatchers.isClickable;
        import static android.support.test.espresso.matcher.ViewMatchers.isDisplayed;
        import static android.support.test.espresso.matcher.ViewMatchers.isNotChecked;
        import static android.support.test.espresso.matcher.ViewMatchers.withHint;
        import static android.support.test.espresso.matcher.ViewMatchers.withId;
        import static android.support.test.espresso.matcher.ViewMatchers.withText;
        import static org.hamcrest.Matchers.allOf;

        /**
         * Created by 10192582 on 2016/11/17.
         */

        public class MainActivityTest {
            @org.junit.Rule
            public ActivityTestRule<MainActivity> mainActivityActivityTestRule = new ActivityTestRule<MainActivity>(MainActivity.class);

            @org.junit.Before
            public void setUp() throws Exception {
                Thread.sleep(1000);
                closeSoftKeyboard();

            }

            @org.junit.After
            public void tearDown() throws Exception {

            }

            @org.junit.Test
            public void onCreate() throws Exception {

            }

            @org.junit.Test
            public void loginNow() throws Exception {
                Activity activity = mainActivityActivityTestRule.getActivity();
                Matcher user = allOf(withId(R.id.user),withHint("User-Email-Tel-Num"));
                onView(user).perform(clearText());
                onView(user).perform(typeText("123"));
                onView(user).check(matches(withText("123")));
                closeSoftKeyboard();
                Matcher pass = allOf(withId(R.id.pass),withHint("Password"));
                onView(pass).perform(clearText());
                onView(pass).perform(typeText("123"));
                closeSoftKeyboard();
                //onView(pass).check(matches(withText("..3")));
                //can not check
                Matcher rem = withId(R.id.remember);
                onView(rem).check(matches(isNotChecked()));
                onView(rem).perform(click());
                onView(rem).check(matches(isChecked()));
                onView(rem).perform(click());
                onView(rem).check(matches(isNotChecked()));

                Matcher autologin = withId(R.id.autologin);
                onView(autologin).check(matches(isNotChecked()));
                onView(autologin).perform(click());
                onView(autologin).check(matches(isChecked()));
                onView(autologin).perform(click());
                onView(autologin).check(matches(isNotChecked()));


                Matcher login = withId(R.id.button_login);
                onView(login).perform(click());

                Thread.sleep(10000);


            }

            @org.junit.Test
            public void registerNow() throws Exception {

            }

            @org.junit.Test
            public void back() throws Exception {
                Matcher back = withId(R.id.button_back);
                closeSoftKeyboard();
                onView(back).check(matches(isClickable()));
                onView(back).check(matches(isDisplayed()));

            }
        }
```        
        
### 有时间分析

<一个大坑：不定时更新>

### LINK
* [github xxx1 test ](https://github.com/tsbxmw/xxx1/)