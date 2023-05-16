#include <iostream>
#include <vector>
#include "bank_and_accounts.h"


//----------SEMAPHORE----------

       Semaphore::Semaphore(std::string name_key){
                key_t key = ftok(name_key.c_str(), 1);
                if((semid = semget(key, 1, 0666 | IPC_CREAT)) == -1){
                        perror("semget");
                        exit(1);
                }
        }

        void Semaphore::semWait(){
                struct sembuf semops{0,-1,0};
                if(semop(semid, &semops, 1) == -1){
                        perror("semop");
                }
        }

        void Semaphore::semPost(){
                struct sembuf semops{0, 1, 0};
                if(semop(semid, &semops, 1) == -1){
                        perror("semop");
                }
        }

        void Semaphore::destroy(){
                if( semctl(semid, 0, IPC_RMID, NULL) == -1){
                        perror("semctl");
                }
        }


//----------ACCOUNT----------
        Account::Account(): _curBalance(0), _minPosBalance(0), _maxPosBalance(10000), _isFrozen(false) {}
        Account::Account(int curBalance, int minPosBalance, int maxPosBalance, bool isFrozen){
                _curBalance = curBalance;
                _minPosBalance = minPosBalance;
                _maxPosBalance = maxPosBalance;
                _isFrozen = isFrozen;
        }
        int Account::getCurBalance() const{
                return _curBalance;
        }
        int Account::getMinPosBalance() const{
                return _minPosBalance;
        }
        int Account::getMaxPosBalance() const{ 
                return _maxPosBalance;
        }
        bool Account::getIsFrozen() const{
                return _isFrozen;
        }
        void Account::setCurBalance(int newCurBalance){
                _curBalance = newCurBalance;
        }
        void Account::setMinPosBalance(int newMinPosBalance){
                _minPosBalance = newMinPosBalance;
        }
        void Account::setMaxPosBalance(int newMaxPosBalance){
                _maxPosBalance = newMaxPosBalance;
        }
        void Account::setIsFrozen(bool newIsFrozen){
                _isFrozen = newIsFrozen;
        }
	bool Account::isValid(){
		if(_minPosBalance <= _curBalance && _curBalance <= _maxPosBalance){
			return true;
		}
		return false;
	}

//----------BANK----------
	Bank::Bank(){
		key_t key = ftok("shm_file", 1);
		int shmid = shmget(key, 0, 0);
		if(key < 0){
			std::cout << "ERROR: Cannot generate a key!!\n";
			exit(1);
		}
		if(shmid == -1){
			perror("Shared memory");
			exit(1);
		}
		_bank = (Account*) shmat(shmid, NULL, 0);
		if(_bank == (Account*)-1){
			perror("Shared memory attach");
			exit(1);
		}
		struct shmid_ds buf;
		shmctl(shmid, IPC_STAT, &buf);
		_accNum = (int) buf.shm_segsz / sizeof(Account);
		sem = new Semaphore("sem_file");
	}
	Account* Bank::getBank() const{
		return _bank;
	}
	int Bank::getAccNum() const{
		return _accNum;
	}
	void Bank::setBank(Account* newBank){
		_bank = newBank;
	}
	void Bank::setAccNum(int newAccNum){
		_accNum = newAccNum;
	}
	Bank::~Bank(){
		if(shmdt(_bank) == -1){
			perror("shmdt");
			exit(1);
		}
	}
	//operations
	//for each operation:
	//semWait at the begining, semPost at the end +
	//check getIsFrozen() function +
	//check isValid() function +
	//check account number +
	//inapropriate input data +
	void Bank::displayCurBalance(int a){
		sem->semWait();
		if(_bank[a].getIsFrozen()){
			std::cout<<"The account " << a << " is frozen!!\n";
			sem->semPost();
			return;
		}
		if(a > _accNum || a < 0){
			std::cout << "Inappropriate account number!!\n";
			sem->semPost();
			return;
		}
		std::cout << "The current balance of the account "<< a << " is: "<< _bank[a].getCurBalance() << std::endl;
		sem->semPost();
	}
	void Bank::displayMinPosBalance(int a){
		sem->semWait();
		if(_bank[a].getIsFrozen()){
                        std::cout<<"The account " << a << " is frozen!!\n";
			sem->semPost();
			return;
                }
                if(a > _accNum || a < 0){
                        std::cout << "Inappropriate account number!!\n";
			sem->semPost();
                        return;
                }
		std::cout << "The minimum possible balance of the account " << a << " is: "<< _bank[a].getMinPosBalance() << std::endl;
		sem->semPost();
	}
	void Bank::displayMaxPosBalance(int a){
		sem->semWait();
		if(_bank[a].getIsFrozen()){
                        std::cout<<"The account " << a << " is frozen!!\n";
			sem->semPost();
			return;
              	}
                if(a > _accNum || a < 0){
                        std::cout << "Inappropriate account number!!\n";
			sem->semPost();
                        return;
                }
		std::cout << "The maximum possible balance of the account " << a << " is: "<< _bank[a].getMaxPosBalance() << std::endl;
		sem->semPost();
	}
	void Bank::freezeAcc(int a){
		sem->semWait();
		if(_bank[a].getIsFrozen()){
                        std::cout<<"The account " << a << " is already frozen!!\n";
			sem->semPost();
			return;
                }
                if(a > _accNum || a < 0){
                        std::cout << "Inappropriate account number!!\n";
			sem->semPost();
                        return;
                }
		_bank[a].setIsFrozen(true);
		std::cout << "The account " << a << " has been succesfully frozen\n";
		sem->semPost();
	}
	void Bank::unfreezeAcc(int a){
		sem->semWait();
		if(!_bank[a].getIsFrozen()){
                        std::cout<<"The account " << a << " is already unfrozen!!\n";
			sem->semPost();
			return;
                }
                if(a > _accNum || a < 0){
                        std::cout << "Inappropriate account number!!\n";
			sem->semPost();
                        return;
                }
		_bank[a].setIsFrozen(false);
		std::cout << "The account " << a << " has been succesfully frozen\n";
		sem->semPost();
	}
	void Bank::transfer(int x, int a, int b){
		sem->semWait();
		if(_bank[a].getIsFrozen()){
                        std::cout<<"The account " << a << " is frozen!!\n";
			sem->semPost();
                        return;
                }
		if(_bank[b].getIsFrozen()){
                        std::cout<<"The account " << b << " is frozen!!\n";
			sem->semPost();
                        return;
                }
		if(a > _accNum || a < 0){
                        std::cout << "Inappropriate account number!!\n";
			sem->semPost();
                        return;
                }
		if(b > _accNum || b < 0){
			std::cout << "Inappropriate account number!!\n";
			sem->semPost();
			return;
		}
		if(x <= 0){
                        std::cout<<"The argument x should be positive!!\n";
			sem->semPost();
			return;
                }
		_bank[a].setCurBalance(_bank[a].getCurBalance() - x);
		_bank[b].setCurBalance(_bank[b].getCurBalance() + x);
		if(_bank[a].isValid() == false || _bank[b].isValid() == false){
			std::cout << "Cannot complete transfer, as in result one of the accounts become non-valid\n";
			_bank[a].setCurBalance(_bank[a].getCurBalance() + x);
	                _bank[b].setCurBalance(_bank[b].getCurBalance() - x);
		}
		sem->semPost();
	}
	void Bank::giveAllAcc(int x){
		sem->semWait();
		//check wheteher all accs are available
		for(int i = 0; i < _accNum; ++i){
			if(_bank[i].isFrozen()){
				std::cout << "Cannot complete this operation as the account " << i << " is frozen!!\n";
				sem->semPost();
				return;
			}
		}
		if(x <= 0){
			std::cout<<"The argument x should be positive!!\n";
			sem->semPost();
			return;
		}
		int completedTr = 0;
		for(int i = 0; i < _accNum; ++i){
			_bank[i].setCurBalance(_bank[i].getCurBalance() + x);
			++comletedTr;
			if(_bank[i].isValid() == false){
				std::cout << "Cannot complete transfer, as in result one of the accounts become non-valid\n";
				break;
			}
		}
		for(int i = 0; i < completedTr; ++i){
			_bank[i].setCurBalance(_bank[i].getCurBalance() - x);
		}
		sem->semPost();
	}
	void Bank::takeAllAcc(int x){
		sem->semWait();
		//check wheteher all accs are available
                for(int i = 0; i < _accNum; ++i){
                        if(_bank[i].isFrozen()){
                                std::cout << "Cannot complete this operation as the account " << i << " is frozen!!\n";
				sem->semPost();
				return;
                        }
                }
		if(x <= 0){
                        std::cout<<"The argument x should be positive!!\n";
			sem->semPost();
			return;
                }
		int completedTr = 0;
                for(int i = 0; i < _accNum; ++i){
                        _bank[i].setCurBalance(_bank[i].getCurBalance() - x);
                        ++comletedTr;
                        if(_bank[i].isValid() == false){
                                std::cout << "Cannot complete transfer, as in result one of the accounts become non-valid\n";
                                break;
                        }
                }
                for(int i = 0; i < completedTr; ++i){
                        _bank[i].setCurBalance(_bank[i].getCurBalance() + x);
                }

		sem->semPost();
	}
	void Bank::setMinPosBalance(int x, int a){
		sem->semWait();
		if(_bank[a].getIsFrozen()){
                        std::cout<<"The account " << a << " is frozen!!\n";
			sem->semPost();
                        return;
                }
		if(a > _accNum || a < 0){
                        std::cout << "Inappropriate account number!!\n";
			sem->semPost();
                        return;
                }
		int oldMinPosBalance = _bank[a].getMinPosBalance();
		_bank[a].setMinPosBalance(x);
		if(_bank[a].isValid() == false){
			std::cout << "Cannot complete setting minimum possible balance, as the account " << a <<" becomes non-valid\n";
			_bank[a].setMinPosBalance(oldMinPosBalance);
		}
		sem->semPost();
	}
	void Bank::setMaxPosBalance(int x, int a){
		sem->semWait();
		if(_bank[a].getIsFrozen()){
                        std::cout<<"The account " << a << " is frozen!!\n";
                        sem->semPost();
			return;
                }
		if(a > _accNum || a < 0){
                        std::cout << "Inappropriate account number!!\n";
                	sem->semPost();
                        return;
                }
		int oldMaxPosBalance = _bank[a].getMaxPosBalance();
                _bank[a].setMaxPosBalance(x);
                if(_bank[a].isValid() == false){
                        std::cout << "Cannot complete setting maximum possible balance, as the account " << a <<" becomes non-valid\n";
                        _bank[a].setMaxPosBalance(oldMaxPosBalance);
                }

		sem->semPost();
	}


















