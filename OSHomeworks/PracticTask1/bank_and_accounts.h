#ifndef BANK_AND_ACOOUNTS_H
#define BANK_AND_ACCOUNTS_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>

class Semaphore{
private:
	int semid;
public:
	Semaphore(std::string name_key);

	void semWait();

	void semPost();

	void destroy();
};

class Account{
public:
	Account();
	Account(int curBalance, int minPosBalance, int maxPosBalance, bool isFrozen);
	int getCurBalance() const;
	int getMinPosBalance() const;
	int getMaxPosBalance() const;
	bool getIsFrozen() const;
	void setCurBalance(int newCurBalance);
	void setMinPosBalance(int newMinPosBalance);
        void setMaxPosBalance(int newMaxPosBalance);
        void setIsFrozen(bool newIsFrozen);
	bool isValid();
private:
	int _curBalance;
	int _minPosBalance;
	int _maxPosBalance;
	bool _isFrozen;
};

class Bank{
public:
	Bank();
	Account* getBank() const;
	int getAccNum() const;
	void setBank(Account* newBank);
	void setAccNum(int newAccNum);

	void displayCurBalance(int a);
	void displayMinPosBalance(int a);
	void displayMaxPosBalance(int a);
	void freezeAcc(int a);
	void unfreezeAcc(int a);
	void transfer(int x, int a, int b);
	void giveAllAcc(int x);
	void takeAllAcc(int x);
	void setMinPosBalance(int x, int a);
	void setMaxPosBalance(int x, int a);
	~Bank();

private:
	Account* _bank;
	int _accNum;
	Semaphore* sem;
};

#endif
