#ifndef PUBLIC_H
#define PUBLIC_H

class Foo {
public:
    int n = 1;
    mutex mtx;
    condition_variable cv;

    Foo() {

    }

    void first(function<void()> printFirst) {

        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();

        n++;
        cv.notify_one();
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> lk(mtx);
        cv.wait(lk, [&]() { return n == 2; });
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        n++;
        cv.notify_one();
    }

    void third(function<void()> printThird) {
        unique_lock<mutex> lk(mtx);
        cv.wait(lk, [&]() { return n == 3; });
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};

#endif // PUBLIC_H
