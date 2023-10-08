#include "main.h"

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
				while(temp->next != head ){
					if(temp->name == name) return true;
					temp = temp->next;
				}
				if(temp->name == name) return true;
				return false;
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
				/* print in clockwise direction */
				if(num > 0){
					if(this->count == 0) this->head->print();
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
					if(this->count == 0 ) this->head->print();
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

			void REMOVE_BLUE(int num){
				cout <<"remove blue, count: "<<this->count<<endl;
				
				if(num >= this->count) this->clear();
				else{
					while(this->curr != this->head->prev) curr = curr->next;
					/* DELETE (NUM-1) FIRST CUSTOMER, THE LAST CUSTOMER USING TO UPDATE CURR */
					for(int i=0; i<num-1; i++) DELatFirst();
					if(this->count == 1){
						delete this->head;
						this->head = nullptr;
						delete this->curr;
						this->curr = nullptr;
						this->count = 0;
					}
					else {
						customer* temp = this->head;
						temp->prev->next = this->head->next;
						this->head->next->prev = temp->prev;
						this->head->prev = nullptr;
						this->head = this->head->next;
						temp->next = nullptr;
						
						if(temp->energy > 0) {
							while(this->curr != this->head) this->curr = this->curr->next;
						}
						else{
							while (this->curr != this->head->prev ) this->curr = this->curr->next;
							
						}
						delete temp;
						temp = nullptr;
						this->count--;
					}
				}
				cout << "end remover blue, count: "<<this->count<<endl;
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

			/* WAITING LIST IS IMPLEMETED AS SINGLY LINKED LIST */
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
					this->last->next = wcus;
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
	};

	public:
		CDLL* LL;

		WaitList* WL;

	public:	
		imp_res() {
			LL = new CDLL();
			WL = new WaitList();
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
	cout << name <<"-" <<energy<<endl;
	if(energy == 0 ) return;
	if(LL->count < MAXSIZE) LL->ADD_RED(name, energy);
	else WL->WADD_RED(name, energy);
	
}

void imp_res::BLUE(int num){
	cout << "blue "<< num << endl;
	if(num <= 0 ) return;

	LL->REMOVE_BLUE(num);

	while(LL->count < MAXSIZE && WL->countWait > 0) {
		cout<<"LL.count, WL.countWait: "<<LL->count<<", "<<WL->countWait<<endl;
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
}

void imp_res::UNLIMITED_VOID(){
	cout << "unlimited_void" << endl;
}

void imp_res::DOMAIN_EXPANSION(){
	cout << "domain_expansion" << endl;
	
}


void imp_res::LIGHT(int num){
	cout << "light " << num << endl;
	if(num == 0){
		/* print Waiting list */
		WL->WPRINT();
	}
	else LL->LPRINT(num);
}