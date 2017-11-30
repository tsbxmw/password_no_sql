---
layout: post
title: Hexadecimal conversion 2~64(any to any)
categories: C++
description: Hexadecimal conversion 2~64 to 2~64
keywords: c++, convert, 2, 64
---
Hexadecimal conversion [2~64] to [2~64]

# an example of hexadecimal conversion

## About

Here is the normal conversion 

* 2     Binary        010            (Decimal=2)
* 8     Octal         O10            (Decimal=8)
* 10    Decimal       10             (Decimal=10)
* 16    Hexadeciaml   0x10           (Decimal=16)

## so what is the 2~64 ?

* it look like this on my define

```c
    1~11  : 0 1 2 3 4 5 6 7 8 9 
    12~21 : a b c d e f g h j k
    22~31 : l m n o p q r s t u 
    32~41 : v w x y z A B C D E 
    42~51 : F G H I J K L M N O 
    52~61 : P Q R S T U V W X Y
    62~63 : Z + /
```

## the key of conversion

### first is convert input to 10

* example binary(2) to decimal(10)

```c++
        binary     =>  decimal
    id  4 3 2 1
    num 1 0 1 0    =>  10
    ^id 3 2 1 0
    end 8 0 2 0    =>  8+2 = 10
        result = id * 2^(^id) + ...
```

* calculate the mod of number

```c++
    long long cal_mod(int mod, int count)
    {
        long long result = 1;
        while (true)
        {
            if (count <= 0)
                break;
            result *= mod;
            count--;
        }
        return result;

    }
```
* add togeter

```c++
    for (int i = 0; i < input_value.GetLength(); i++)
            temp += getmod(input_value.GetAt(i)) * cal_mod(input_mod, input_value.GetLength()-i-1);

```

### second is convert 10 to output

* example decimal to binary

```c++
    decimal       =>      binary
        10 % 2    =>      0
      10/2 % 2    =>      1
       5/2 % 2    =>      0
       2/2 % 2    =>      1
     
     result = Reverse(0101)
     
```

```c++
    while (true)
    {
        if (temp > 0)
        {
            output_value.AppendChar(setmod(temp%output_mod));
            temp /= output_mod;
        }
        else
            break;
    }
```


### finally is Reverse

```c++
    
    CString Reverse(CString str)
    {
        CString output_str = CString();
        for (int i = str.GetLength() - 1; i >= 0; i--)
            output_str.AppendChar(str.GetAt(i));
        return output_str;
    }
```


## source code

```c++
    #include <iostream>
    #include <afx.h>
    using namespace std;

    long long cal_mod(int mod, int count);
    int getmod(char str);
    char setmod(int num);
    CString Reverse(CString str);
    CString convert(int input_mod, CString input_value, int output_mod);

    CString convert(int input_mod, CString input_value, int output_mod)
    {
        CString output_value = CString();
        if (input_mod == output_mod)
            return input_value;
        if (input_value.GetLength() == 1 && input_value.GetAt(0) == '0')
            return input_value;
        long long temp = 0;
        for (int i = 0; i < input_value.GetLength(); i++)
            temp += getmod(input_value.GetAt(i)) * cal_mod(input_mod, input_value.GetLength()-i-1);

        while (true)
        {
            if (temp > 0)
            {
                output_value.AppendChar(setmod(temp%output_mod));
                temp /= output_mod;
            }
            else
                break;
        }
        return Reverse(output_value);
    }

    long long cal_mod(int mod, int count)
    {
        long long result = 1;
        while (true)
        {
            if (count <= 0)
                break;
            result *= mod;
            count--;
        }
        return result;

    }

    int getmod(char str)
    {
        if (str >= '0' && str <= '9')
            return str - '0';
        if (str >= 'A' && str <= 'Z')
            return str - 'A' + 36;
        if (str >= 'a' && str <= 'z')
            return str - 'a' + 10;
        if (str == '+')
            return 62;
        if (str == '/')
            return 63;
    }

    char setmod(int num)
    {
        char result;
        if (num >= 0 && num <= 9)
            return num + '0';
        if (num >= 10 && num <= 35)
            return num + 'a' - 10;
        if (num >= 36 && num <= 61)
            return num + 'A' - 36;
        if (num == 62)
            return '+';
        if (num == 63)
            return '/';
    }

    CString Reverse(CString str)
    {
        CString output_str = CString();
        for (int i = str.GetLength() - 1; i >= 0; i--)
            output_str.AppendChar(str.GetAt(i));
        return output_str;
    }

    int main()
    {
        for (int in = 2; in <= 64; in++)
        {
            CString num = convert(in, "101", 10);
            for (int i = 0; i < num.GetLength(); i++)
                cout << char(num.GetAt(i));
            cout << endl; 
        }
        
        return 0;
    }
```

> #### LINK

* no link here
