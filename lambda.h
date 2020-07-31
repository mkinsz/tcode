#ifndef LAMBDA_H
#define LAMBDA_H

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <string>
#include <cctype>
#include <iterator>
#include <random>
#include <numeric>
#include <list>
#include <chrono>

/*
 * 变量截取的方式
 * []           不截取任何变量
 * [&]          截取外部作用域中所有变量，并作为引用在函数体中使用
 * [=]          截取外部作用域中所有变量，并拷贝一份在函数体中使用
 * [=, &foo]    截取外部作用域中所有变量，并拷贝一份在函数体中使用，但是对foo变量使用引用
 * [bar]        截取bar变量并且拷贝一份在函数体重使用，同时不截取其他变量
 * [this]       截取当前类中的this指针。如果已经使用了&或者=就默认添加此选项。
 *
 */

#define _BREAK_SECTION_ do{ std::cout << std::endl; } while(0);

void test_lambda() {
    auto add = [](int a, int b) { return a + b; };
    std::function<int(int, int)> Add = [=](int a, int b) { return a + b; };

    _BREAK_SECTION_

    // Fibonacci数列
    std::function<int(int)> recursion = [&recursion](int n) {
        return n < 2 ? 1 : recursion(n - 1) + recursion(n - 2);
    };

    std::cout << recursion(10) << std::endl;

    _BREAK_SECTION_

    int data[6] = { 3, 4, 12, 2, 1, 6 };
    std::vector<int> testdata;
    testdata.insert(testdata.begin(), data, data + 6);

    sort(testdata.begin(), testdata.end(), [](int a, int b){ return a < b; });

    for(auto a : testdata) {
        std::cout << a << std::endl;
    }

    _BREAK_SECTION_

    auto it = std::find_if (testdata.begin(),testdata.end(),[](const int &a) { return (a%2)==0; });
    std::cout << *it << std::endl;

    _BREAK_SECTION_

    //高性能随机数
    unsigned int c = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(c);
    std::cout << generator() << std::endl;


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 6);

    for (int n=0; n<10; ++n)
        std::cout << distrib(gen) << ' ';
    std::cout << '\n';

    _BREAK_SECTION_

    std::list<int> l(10);
    std::iota(l.begin(), l.end(), -4);  //iota v++

    std::vector<std::list<int>::iterator> v(l.size());
    std::iota(v.begin(), v.end(), l.begin());

    std::shuffle(v.begin(), v.end(), std::mt19937{std::random_device{}()});

    std::cout << "Contents of the list: ";
    for(auto n: l) std::cout << n << ' ';
    std::cout << '\n';

    std::cout << "Contents of the list, shuffled: ";
    for(auto i: v) std::cout << *i << ' ';
    std::cout << '\n';

    _BREAK_SECTION_

    std::vector<int> v1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::fill_n(v1.begin(), 5, -1);

    std::copy(begin(v1), end(v1), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";


    _BREAK_SECTION_

    std::vector<int> _v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::fill_n(std::back_inserter(_v), 3, -1);
    for (int n : _v)
        std::cout << n << ' ';

    _BREAK_SECTION_

    std::string s("hello");
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) -> unsigned char { return std::toupper(c); });

    std::vector<std::size_t> ordinals;
    std::transform(s.begin(), s.end(), std::back_inserter(ordinals),
                   [](unsigned char c) -> std::size_t { return c; });

    std::cout << s << ':';
    for (auto ord : ordinals) {
        std::cout << ' ' << ord;
    }

    _BREAK_SECTION_

}

#endif // LAMBDA_H
