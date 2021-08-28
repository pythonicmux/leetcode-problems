class Foo {
public:
    std::condition_variable cvar;
    int count = 0;
    std::mutex lock;
    
    Foo() {
        
    }

    void first(function<void()> printFirst) {
        {
            std::unique_lock<std::mutex> lk(this->lock);

            // printFirst() outputs "first". Do not change or remove this line.
            printFirst();

            this->count += 1;
        }
        
        this->cvar.notify_all();
    }

    void second(function<void()> printSecond) {
        {
            std::unique_lock<std::mutex> lk(this->lock);
            this->cvar.wait(lk, [this](){ return this->count == 1; });
            // printSecond() outputs "second". Do not change or remove this line.
            printSecond();

            this->count += 1;
        }
        
        this->cvar.notify_all();
    }

    void third(function<void()> printThird) {
        {
            std::unique_lock<std::mutex> lk(this->lock);
            this->cvar.wait(lk, [this](){ return this->count == 2; });
            // printThird() outputs "third". Do not change or remove this line.
            printThird();
        }
    }
};
