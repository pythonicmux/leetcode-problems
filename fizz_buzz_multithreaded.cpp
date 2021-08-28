class FizzBuzz {
private:
    int n;
    int ct = 1;
    std::mutex lock;
    std::condition_variable cvar;
    bool done = false;

public:
    FizzBuzz(int n) {
        this->n = n;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        {
            std::unique_lock<std::mutex> lk(lock);
            while(this->ct <= this->n) {
                cvar.wait(lk, [this](){ return this->done || ((this->ct % 3 == 0) && !(this->ct % 5 == 0)); });
                
                if(this->done) {
                    return;
                }

                printFizz();
                
                this->ct++;
                
                if(this->ct > n) {
                    this->done = true;
                }
                
                cvar.notify_all();
            }
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        {
            std::unique_lock<std::mutex> lk(lock);
            while(this->ct <= this->n) {
                cvar.wait(lk, [this](){ return this->done || (!(this->ct % 3 == 0) && (this->ct % 5 == 0)); });
                
                if(this->done) {
                    return;
                }

                printBuzz();
                
                this->ct++;
                
                if(this->ct > n) {
                    this->done = true;
                }
                
                cvar.notify_all();
            }
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        {
            std::unique_lock<std::mutex> lk(lock);
            while(this->ct <= this->n) {
                cvar.wait(lk, [this](){ return this->done || ((this->ct % 3 == 0) && (this->ct % 5 == 0)); });
                
                if(this->done) {
                    return;
                }
                
                printFizzBuzz();
            
                this->ct++;
                
                if(this->ct > n) {
                    this->done = true;
                }
                
                cvar.notify_all();
            }
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        {
            std::unique_lock<std::mutex> lk(lock);
            while(this->ct <= this->n) {
                cvar.wait(lk, [this](){ return this->done || (!(this->ct % 3 == 0) && !(this->ct % 5 == 0)); });
                
                if(this->done) {
                    return;
                }
            
                printNumber(this->ct);
            
                this->ct++;
                
                if(this->ct > n) {
                    this->done = true;
                }
                
                cvar.notify_all();
            }
        }
    }
};
