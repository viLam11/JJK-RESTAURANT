#include "main.h"

int MAXSIZE;

class imp_res : public Restaurant
{
    public:
    class CDLL 
    {
        public:
            Restaurant::customer* head;
            Restaurant::customer* curr;
            int count;
        public:
            CDLL(){
                this->head = nullptr;
                this->curr = nullptr;
                this->count = 0;
            }
            
            bool LEXIST(string name){
                if(this->count == 0) return false;
                customer* temp =this->head;

                do{
                    if(temp->name == name) return true;
                    temp = temp->next;
                }
                while (temp != this->head && temp);

                return false;
            };

            void ADD(string name, int energy){
                if(this->count == 0){
                        customer* cus = new customer(name, energy, nullptr, nullptr);
                        this->head = cus;
                        this->curr = cus;
                        this->count = 1;
                    }
                else if(this->count == 1){
                        Restaurant::customer* cus = new Restaurant::customer(name, energy, this->head, this->head);
                        this->curr = cus;
                        this->curr->next = this->head;
                        this->curr->prev = this->head;
                        this->head->next = this->curr;
                        this->head->prev = this->curr;
                        this->count = 2;
                    }
                else{
                        Restaurant::customer* cus = new Restaurant::customer(name, energy, this->curr, this->head);
                        this->head->prev = cus;
                        this->curr->next = cus;
                        this->curr = cus;
                        this->count++;
                }
            };

            void ADD_RED(string name, int energy){
                cout << "Eneter ADD_RED, count: "<<this->count<<endl;
                if(this->count < MAXSIZE/2){
                    if(this->count == 0){
                        customer* cus = new customer(name, energy, nullptr, nullptr);
                        this->head = cus;
                        this->curr = cus;
                        this->count = 1;
                    }
                    else if(this->count == 1){
                        Restaurant::customer* cus = new Restaurant::customer(name, energy, this->head, this->head);
                        this->curr = cus;
                        this->curr->next = this->head;
                        this->curr->prev = this->head;
                        this->head->next = this->curr;
                        this->head->prev = this->curr;
                        this->count = 2;
                    }
                    else{
                        // chu thuat su
                        if(energy >= this->curr->energy){
                            Restaurant::customer* cus = new Restaurant::customer(name, energy, this->curr, this->curr->next);
                            this->curr->next->prev = cus;
                            this->curr->next = cus;
                            this->curr = cus;
                        }
                        else{
                            Restaurant::customer* cus = new Restaurant::customer(name, energy, this->curr->prev, this->curr);
                            this->curr->prev->next = cus;
                            this->curr->prev = cus;
                            this->curr = cus;
                        }
                        this->count++;
                    }
                }

                /* FIND THE MAX ABS DIFF OF ENERGY BEFORE ADDING */
                else if( this->count >= MAXSIZE/2 && this->count < MAXSIZE){
                    Restaurant::customer* temp = this->head;
                    Restaurant::customer* pos = temp;
                    int max = abs(energy - temp->energy);
                    // check CDLL
                    int res;
                    cout<<"Add [Maxsize/2; Maxsize] count: "<<this->count<<endl;
                    while(temp->next != head){
                        cout<<"temp2 name, energy: "<<temp->name<<", "<<temp->energy << endl;
                        res = abs(energy - temp->energy);
                        if(res > max) {
                            max = res;
                            pos = temp;
                        }
                        temp = temp->next;
                    }
                    res = abs(energy - temp->energy);
                    if(res > max) {
                        max = res; 
                        pos = temp;
                    }

                    if(this->count == 0){
                        Restaurant::customer* cus = new Restaurant::customer(name, energy, nullptr, nullptr);
                        this->head = cus;
                        this->curr = cus;
                        this->count = 1;
                    }
                    else if(this->count == 1){
                        Restaurant::customer* cus = new Restaurant::customer(name, energy, this->head, this->head);
                        this->curr = cus;
                        this->curr->next = this->head;
                        this->curr->prev = this->head;
                        this->head->next = this->curr;
                        this->head->prev = this->curr;
                        this->count = 2;
                    }
                    else{
                        if(energy - pos->energy >= 0){
                            Restaurant::customer* cus = new Restaurant::customer(name, energy, pos, pos->next);
                            pos->next->prev = cus;
                            pos->next = cus;
                            while(this->curr != cus) this->curr = this->curr->next;
                        }
                        else{
                            Restaurant::customer* cus = new Restaurant::customer(name, energy, pos->prev, pos);
                            pos->prev->next = cus;
                            pos->prev = cus;
                            while(this->curr != cus) this->curr = this->curr->next;
                        }
                        this->count++;
                    }
                }
            };

            void LPRINT(int num){
                cout << "print eating list, count: "<<this->count<< endl;
                customer* temp = curr;
				if(this->count == 0) return;
                /* print in clockwise direction */
                if(num > 0){
					if(this->count == 1) this->head->print();
                    else{
                    while(temp->next != curr){
                        temp->print();
                        temp = temp->next;
                    }
                    if(temp) temp->print();
                    }
                }
                
                /* print in counterclockwise direction */
                else if(num < 0){
                    if(this->count == 1 ) this->head->print();
                    else{
                        while(temp->prev != curr){
                            temp->print();
                            temp = temp->prev;
                        }
                        if(temp) temp->print();
                    }
                }
            };

            void clear(){
                if(this->count == 0) return;
                else if(this->count == 1){
                    delete this->head;
                    this->head = nullptr;
                    delete this->curr;
                    this->curr = nullptr;
                    this->count = 0;
                }
                else {
                    customer* temp = this->head;
                    while(temp){
                        this->head = this->head->next;
                        delete temp;
                        temp = nullptr;
                        temp = this->head;
                    }
                    delete this->head;
                    delete this->curr;
                    this->head = nullptr;
                    this->curr = nullptr;
                    this->count = 0;
                }
            }

            void DELatFirst(){
                while(this->curr != this->head->prev) this->curr = this->curr->next;
                customer* temp = this->head;
                if(this->count == 0 ) return;
                else if(this->count == 1){
                    delete this->head;
                    this->head = nullptr;
                    delete this->curr;
                    this->curr = nullptr;
                    this->count = 0;
                }
                else{
                    customer* temp = this->head;
                    temp->prev->next = this->head->next;
                    this->head->next->prev = temp->prev;
                    this->head->prev = nullptr;
                    this->head = this->head->next;
                    temp->next = nullptr;
                    delete temp;
                    temp = nullptr;
                    this->count--;
                }
            };

            void REMOVE_BLUE(string name){
                while(this->curr != this->head) this->curr = this->curr->next;
                customer* temp = this->head;
                while(temp->next != this->head && temp->name != name){
                    temp = temp->next;
                }
                if(temp->name != name && temp == this->head){
                    temp = temp->next;
                    if(temp->name != name ) return;
                }
                if(temp->name == name){
                    customer* pre = temp->prev;
                    pre->next = temp->next;
                    if(temp->energy < 0 ){
                        this->curr = temp->prev;
                    }
                    else this->curr = temp->next;

                    if(temp == this->head){
                        if(this->count == 1){
                            this->head = nullptr;
                            this->count = 0;
                        }
                        else{
                            this->head = this->head->next;
                            delete temp;
                            this->count--;
                        }
                    }
                    else{
                        pre->next = temp->next;
                        temp->next->prev = pre;
                        delete temp;
                        temp = nullptr;
                        this->count--;
                    }
                }
            
            }

            int countTS(){
                int countTS = 0;
				customer* temp = this->head;

                do{
                    if(temp->energy > 0 ) countTS++;
                    temp = temp->next;
                }
                while(temp != this->head);

                cout <<"Enter REVERSAL_TS, countTS: "<<countTS<<endl;
                return countTS;
            };

            int countOL(){
                int countOL = 0;
				customer* temp = this->head;

                do{
                    if(temp->energy < 0 ) countOL++;
                    temp = temp->next;
                }
                while(temp != this->head);

                cout <<"Enter REVERSAL_TS, countTS: "<<countOL<<endl;

                return countOL;
            };

			void REVERSAL_TS(){
				int countTS = this->countTS();

                cout <<"Enter REVERSAL_TS, countTS: "<<countTS<<endl;

				if(countTS <= 1) return;
                
                string namePC = this->curr->name;
                cout << "Previous curr name: "<<namePC<<endl;

				customer* TSFirst = this->curr;
				customer* TSLast = this->curr->next;
				while(TSFirst->energy < 0) TSFirst = TSFirst->prev;
				while(TSLast->energy < 0) TSLast = TSLast->next;

				while(TSFirst != TSLast){
						string name = TSFirst->name;
						int energy = TSFirst->energy;
						TSFirst->name = TSLast->name;
						TSFirst->energy = TSLast->energy;
						TSLast->name = name;
						TSLast->energy = energy;
                        TSFirst = TSFirst->prev;
						while(TSFirst->energy < 0) TSFirst = TSFirst->prev;
						if(TSFirst == TSLast) break;
                        TSLast = TSLast->next;
						while(TSLast->energy < 0) TSLast = TSLast->next;
					}

                /* Tim lai vi tri curr*/
                while(curr->name != namePC) curr = curr->next;

				cout << "end reversal thuat su, check!"<<endl;
				this->LPRINT(9);
			};

            void REVERSAL_OL(){
                int countOL = this->countOL();
                string nameOP = this->curr->name;

				if(countOL <= 1) return;

				customer* OLFirst = this->curr;
				customer* OLLast = this->curr->next;
				while(OLFirst->energy > 0) OLFirst = OLFirst->prev;
				while(OLLast->energy > 0) OLLast = OLLast->next;

				while(OLFirst != OLLast){
						string name = OLFirst->name;
						int energy = OLFirst->energy;
						OLFirst->name = OLLast->name;
						OLFirst->energy = OLLast->energy;
						OLLast->name = name;
						OLLast->energy = energy;
                        OLFirst = OLFirst->prev;
						while(OLFirst->energy > 0) OLFirst = OLFirst->prev;
						if(OLFirst == OLLast) break;
                        OLLast = OLLast->next;
						while(OLLast->energy > 0) OLLast = OLLast->next;
					}
				cout << "end reversal oan linh, check!"<<endl;
                /* Update the curr to previous value */
                while(curr->name != nameOP) curr = curr->next;

				this->LPRINT(9);
            };
    
            
    };

    public:
    class WaitList 
    {
        public:
            Restaurant::customer* first;
            Restaurant::customer* last;
            int countWait;
        public:
            WaitList(){
                this->first = nullptr;
                this->last = nullptr;
                this->countWait = 0;
            }

            bool WEXIST(string name){
                if(this->countWait == 0) return false;
                customer* temp = this->first;
                while(temp){
                    if(temp->name == name) return true;
                    temp = temp->next;
                }
                return false;
            };

            void ADD(string name, int energy){
                if(this->countWait == 0){
                    this->first = new customer(name, energy, nullptr, nullptr);
                    this->last  = nullptr;
                    this->countWait = 1;
                }
                else if(this->countWait == 1){
                    this->last = new customer(name, energy, this->first, nullptr);
                    this->first->next = this->last;
                    this->last->prev = this->first;
                    this->countWait = 2;
                }
                else{
                    customer* newCus = new customer(name, energy, this->last, nullptr);
                    this->last->next = newCus;
                    this->last = newCus;
                    this->countWait++;
                }
            };

            void WADD_RED(string name, int energy){
                cout << "* Adding to waiting list "<<endl;
                if(this->countWait < MAXSIZE){
                customer *wcus;
                if(this->countWait == 0){
                    wcus = new customer(name, energy, nullptr, nullptr);
                    this->first = wcus;
                    this->first->prev = nullptr;
                    this->first->next = this->last;
                    this->last = wcus;
                    this->last->prev = this->first;
                    this->last->next = nullptr;
                    this->countWait = 1;
                    }
                else if(this->countWait == 1){
                    wcus = new customer(name, energy, this->first, nullptr );
                    this->first->next = wcus;
                    this->last = wcus;
                    this->countWait = 2;
                    }
                else {
                    wcus = new customer(name, energy, this->last, nullptr);
                    this->last->next = wcus;
                    this->last = wcus;
                    this->countWait++;
                    }
                }
            };

            void WPRINT(){
                /* print Waiting list */
                customer* tempWait = this->first;
                while(tempWait != nullptr){
                        tempWait->print();
                        tempWait = tempWait->next;
                }
            };

            void REMOVE(){
                if(this->countWait == 0) return;
                if(this->countWait == 1){
                    this->first = nullptr;
                    this->last = nullptr;
                    this->countWait = 0;
                }
                else{
                    customer* DEL = this->first;
                    this->first = this->first->next;
                    delete DEL;
                    this->countWait--;
                }
            };

            void REMOVE(string name){
                if(this->countWait == 0) return;
                customer* del = this->first;
                while(del->name != name) del = del->next;
                if(del == this->first){
                    if(this->countWait == 1){
                        this->first = nullptr;
                        this->last = nullptr;
                        delete this->first;
                        delete this->last;
                    }
                    else{
                        this->first = this->first->next;
                        this->first->prev = nullptr;
                        del->next = nullptr;
                        delete del;
                    }
                }
                else if(del == this->last){
                    this->last = this->last->prev;
                    this->last->next = nullptr;
                    del->prev = nullptr;
                    delete del;
                }
                else{
                    customer* preDel = del->prev;
                    preDel->next = del->next;
                    del->next->prev = preDel;
                    delete del;
                }
                this->countWait--;
            }
    };

    public:
        CDLL* LL;
        WaitList* TimeList;
        WaitList* WL;

    public: 
        imp_res() {
            LL = new CDLL();
            WL = new WaitList();
            TimeList = new WaitList();
        };
        bool EXIST(string name);
        void RED(string name, int energy);
        void BLUE(int num);
        void PURPLE();
        void REVERSAL();
        void UNLIMITED_VOID();
        void DOMAIN_EXPANSION();
        void LIGHT(int num);
};

bool imp_res::EXIST(string name){
    if (LL->LEXIST(name) || WL->WEXIST(name)) return true;
    return false;
}

void imp_res::RED(string name, int energy){
    cout << "RED "<<endl;
    cout << name <<" - " <<energy<<endl;
    if(energy == 0 ) return;

    TimeList->ADD(name, energy);

    if(LL->count < MAXSIZE) LL->ADD_RED(name, energy);
    else WL->WADD_RED(name, energy);
    
}

void imp_res::BLUE(int num){
    cout << "blue "<< num << endl;
    if(num <= 0 ) return;
    
    if(num >= LL->count) LL->clear();
    else{
        for(int i=0; i<num; i++){
            string Del_name = TimeList->first->name;
            TimeList->REMOVE();
            LL->REMOVE_BLUE(Del_name);
        }
    }

    while(LL->count < MAXSIZE && WL->countWait > 0) {
        // cout<<"LL.count, WL.countWait: "<<LL->count<<", "<<WL->countWait<<endl;
        string name = WL->first->name;
        int energy = WL->first->energy;
        WL->REMOVE();
        LL->ADD_RED(name, energy);
    }
}

void imp_res::PURPLE(){
    cout << "purple"<< endl;
}
        
void imp_res::REVERSAL(){
    cout << "reversal" << endl;
    LL->REVERSAL_TS();
    LL->REVERSAL_OL();
}

void imp_res::UNLIMITED_VOID(){
    cout << "unlimited_void" << endl;
    if(LL->count < 4) return;

    customer* start = LL->curr;
    customer* end = start;
    int MIN, sum, MAXLEN, len;
    customer* Fstart;
    customer* Fend;
    do{
        sum = 0;
        for(int i=0; i < 4; i++){
            sum += end->energy;
            end = end->next;
        }
        len  = 4;

        if(start == LL->curr){
            MIN = sum;
            MAXLEN = len;
        }
        
        if(sum <= MIN && len >= MAXLEN){
            MIN = sum;
            MAXLEN = len;
            Fstart = start;
            Fend = end;
        }

        while(end != start){
            sum += end->energy;
            len++;
            if(sum <= MIN && len >= MAXLEN){
                MIN = sum;
                MAXLEN = len;
                Fstart = start;
                Fend = end;
            }
            end = end->next;
        }

        start = start->next;
        end = start;
    }
    while (start != LL->curr);

    CDLL* chuoi = new CDLL();
    customer* temp = Fstart;
    while(temp != Fend){
        chuoi->ADD(temp->name, temp->energy);
        temp = temp->next;
    }
    chuoi->ADD(Fend->name, Fend->energy);

    /* UPDATE THE CURR OF CDLL chuoi SO THAT PRINT FROM THE SMALLEST ENERGY WHICH IS FIRST FOUND */
    customer* minCus = chuoi->head;
    int minEn = minCus->energy;
    chuoi->curr = minCus;
    do{
        if(minCus->energy < minEn) {
            minEn = minCus->energy;
            chuoi->curr = minCus;
        }
        minCus = minCus->next;
    }
    while(minCus != chuoi->head);

    chuoi->LPRINT(2);

}

void imp_res::DOMAIN_EXPANSION(){
    cout << "domain_expansion" << endl;
    int energyTS = 0, energyOL = 0;
    customer* temp = LL->curr;

    if(LL->count < 1) return;

    do{
        if(temp->energy > 0) energyTS += temp->energy;
        else energyOL += temp->energy;
        temp = temp->next;
    }
    while(temp != LL->curr);

    /* REMOVE ALL OAN LINH*/
    if(energyTS >= abs(energyOL) ){
        customer* del = TimeList->last;
        cout<<"check timelist: "<<endl;
        TimeList->WPRINT();
        while(del){
            while(del->energy > 0 && del != TimeList->first) {
                del->print();
                del = del->prev;
                }
            if(del->energy > 0 ){
                if(TimeList->first->energy > 0) break;
                else del = TimeList->first;
            }
            string delname = del->name;
            del->print();
            if(WL->WEXIST(delname)) WL->REMOVE(delname);
            else if(LL->LEXIST(delname)) LL->REMOVE_BLUE(delname);
            del = del->prev;
            TimeList->REMOVE(delname);
        }
    }
    /*REMOVER ALL THUAT SU */
    else{
        customer* del = TimeList->last;
        while(del){
            while(del->energy < 0 && del) del = del->prev;
            if(del == nullptr) break;
            string delname = del->name;
            del->print();
            if(WL->WEXIST(delname)) WL->REMOVE(delname);
            else if(LL->LEXIST(delname)) LL->REMOVE_BLUE(delname);
            TimeList->REMOVE(delname);
            del = del->prev;
        }
    }

    /* ARRAGE CUSTOMERS IN WAITING LIST TO TABLES IN RED METHOD */
    while(LL->count < MAXSIZE && WL->countWait > 0){
        LL->ADD_RED(WL->first->name, WL->first->energy);
        WL->REMOVE();
    }
}

void imp_res::LIGHT(int num){
    cout << "light " << num << endl;
    if(num == 0){
        /* print Waiting list */
        WL->WPRINT();
    }
    else LL->LPRINT(num);
}

