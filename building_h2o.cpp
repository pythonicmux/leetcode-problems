class H2O {
public:
    std::mutex internal_lock;
    std::condition_variable cvar;
    int os_ct = 0;
    int hs_ct = 0;
    int state = 0; // 0 means filling up, 1 means full and releasing
    
    H2O() {
        
    }

    void hydrogen(function<void()> releaseHydrogen) {
        {
            std::unique_lock<std::mutex> lk(internal_lock);
            
            // Only let 2 hydrogens through at once.
            cvar.wait(lk, [this](){ return this->state == 0 && this->hs_ct < 2; });
            
            hs_ct++;
            if(hs_ct == 2 && os_ct == 1) {
                state = 1;
                cvar.notify_all();
            }
            
            // When 2H and 1O fill up, unload and print hydrogens.
            cvar.wait(lk, [this](){ return this->state == 1; });
            
            // cout << "Made it to H release " << endl;
            
            // releaseHydrogen() outputs "H". Do not change or remove this line.
            releaseHydrogen();
            
            // Change the state back to filling up once everyone has woke.
            hs_ct--;
            
            if(hs_ct == 0 && os_ct == 0) {
                state = 0;
                // cout << "Notifying that it's back to fill" << endl;
                cvar.notify_all();
            }
            
            // cout << "H going to wait" << endl;
            
            // Don't release until everyone has printed.
            cvar.wait(lk, [this](){ return this->state == 0; });
        }
        
        cvar.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) { 
        {
            std::unique_lock<std::mutex> lk(internal_lock);
            
            // Only let 1 oxygen through at once.
            cvar.wait(lk, [this](){ return this->state == 0 && this->os_ct < 1; });
            
            os_ct++;
            if(hs_ct == 2 && os_ct == 1) {
                state = 1;
                cvar.notify_all();
            }
            
            // When 2H and 1O fill up, unload and print hydrogens.
            cvar.wait(lk, [this](){ return this->state == 1; });
            
            // cout << "Made it to O release " << endl;
            
            // releaseOxygen() outputs "O". Do not change or remove this line.
            releaseOxygen();
            
            // Change the state back to filling up once everyone has woke.
            os_ct--;
            
            if(hs_ct == 0 && os_ct == 0) {
                state = 0;
                // cout << "Notifying that it's back to fill" << endl;
                cvar.notify_all();
            }
            
            // cout << "O going to wait" << endl;
            
            // Don't release until everyone has printed.
            cvar.wait(lk, [this](){ return this->state == 0; });
        }
        
        cvar.notify_all();
    }
};
