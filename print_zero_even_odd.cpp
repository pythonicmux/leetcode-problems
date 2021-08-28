class ZeroEvenOdd {
private:
    int state = 0; // 0 = Zero, 1 = Odd, 2 = Zero_2, 3 = Even
    int n;
    
    std::mutex m;
    std::condition_variable cvar;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for(int i = 0; i < n; i++) {
            {
                std::unique_lock lk(m);
                this->cvar.wait(lk, [this](){ return this->state == 0 || this->state == 2; });

                printNumber(0);
                this->state = (this->state + 1) % 4;
            }
            
            this->cvar.notify_all();
        }
    }

    void even(function<void(int)> printNumber) {
        for(int i = 2; i <= n; i += 2) {
            {
                std::unique_lock lk(m);
                this->cvar.wait(lk, [this](){ return this->state == 3; });

                printNumber(i);
                this->state = (this->state + 1) % 4;
            }
            
            this->cvar.notify_all();
        }
    }

    void odd(function<void(int)> printNumber) {
        for(int i = 1; i <= n; i += 2) {
            {
                std::unique_lock lk(m);
                this->cvar.wait(lk, [this](){ return this->state == 1; });

                printNumber(i);
                this->state = (this->state + 1) % 4;
            }
            
            this->cvar.notify_all();
        }
    }
};
