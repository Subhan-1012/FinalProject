#pragma once
#include<iostream>
#include<string>
using namespace std;
class Kingdom {
private:
	Population* population;
	Army* army;
	Economy* economy;
	Politics* politics;
	Resources* resources;
	Market* market;
	Bank* bank;
	string name;
	int stability;
	bool isAtWar;
	static const int MAX_SAVED_GAMES = 10;
public:
	void updateturn();
	void saveGame();
	void loadGame();
	void displayStatus();
};


class Population {
private:
	int peasants;
	int merchants;
	int nobility;
	int soliders;
	float growthRate;
	float happiness;
	static const int MAX_EVENTS = 5;
	Event* currentEvents[MAX_EVENTS];
public:
	void updatePopulation();
	void applyEventEffects(Event* event);
	float getTaxRevenue(float taxRate);
	void handlePlague();
	void handleFamine();
};


class Army {
private:

	int infantry; //soliders who fight on foot without tanks
	int cavalry; //soliders jo animals ko ride krte for fight
	int archers;
	float morale;
	float trainingProgress;
	bool isTraining;
	static const int MAX_GENERALS = 5;
	General* generals[MAX_GENERALS];
	int generalCount;
	
public:
	Army() : generalCount(0) {}
	void trainTroops(int type, int quantity);
	void updateMorale();
	void paySalaries(float amount);
	bool engageInBattle(Army* enemy);
	void handleDesertion();
	bool addGeneral(General* general);
	bool removeGeneral(int index);

};


class Economy {
private:
	int treasury; //wo dept jahan kingdom apni money rakhe gi
	float taxRate;
	float inflamation;
	float gdp; //specific time mein country mein sari pari hui values ki ammount
	static const int MAX_LOANS = 5;
	Loan* loans[MAX_LOANS];
	int loanCount;
public:
	Economy() : loanCount(0) {}
	void collectTaxes();
	void applyInflation();
	bool takeLoan(float amount, float interest);
	bool repayLoan(int loanId, float amount);
	void handleCorruption();
};


class Politics {
private:
	Leader* currentLeader;
	static const int MAX_FACTIONS = 5;// faction ka mtlb aik baray group k andar ain chota group
	Faction* factions[MAX_FACTIONS];
	int factionCount;
	float stability;
	int electionTimer;
public:
	Politics() : factionCount(0) {}
	void holdElection();
	void handleCoupAttempt();
	void updateFactionRelations();
	void applyLeaderEffects();
	bool addFaction(Faction* faction);
};


class Resource {
	//is class mein templates use honge
};


class Market {
private:
	static const int MAX_PRICES = 10;
	struct PriceEntry {

		string item;
		float price;
	} 
	prices[MAX_PRICES];
	int priceCount;

	static const int MAX_TRADE_ROUTES = 5;
	TradeRoute* tradeRoutes[MAX_TRADE_ROUTES];
	int routeCount;

	static const int MAX_AGREEMENTS = 5;
	TradeAgreement* agreements[MAX_AGREEMENTS];
	int agreementCount;

public:
	Market() : priceCount(0), routeCount(0), agreementCount(0) {}
	void updatePrices();
	bool establishTradeRoute(TradeRoute* route);
	bool breakTradeRoute(int index);
	void handleTradeEvent();
};


class Bank {
private:
	float reserves;
	float interestRate;
	static const int MAX_ACCOUNTS = 100;
	Account* accounts[MAX_ACCOUNTS];
	int accountCount;
	float corruptionLevel;

public:
	Bank() : accountCount(0) {}
	bool processLoan(Loan* loan);
	void detectFraud();
	void applyInterest();
	void handleBankHeist();
};


class Event {
protected:
	string description;
	float probability;

public:
	virtual void trigger(Kingdom* kingdom) = 0;
};

class RandomEvents {
private:
	static const int MAX_EVENTS = 20;
	Event* possibleEvents[MAX_EVENTS];
	int eventCount;

public:
	RandomEvents() : eventCount(0) {}
	void checkForEvent(Kingdom* kingdom);
	bool addEvent(Event* event);
};


class Leader {
private:
	string name;
	string type;
	float popularity;
	float corruption;

public:
	virtual float getTaxModifier() = 0;
	virtual float getMilitaryModifier() = 0;
	virtual void specialAction(Kingdom* kingdom) = 0;
};

class King : public Leader {
public:
	float getTaxModifier() override;
	float getMilitaryModifier() override;
	void specialAction(Kingdom* kingdom) override;
};

class Commander : public Leader {
public:
	float getTaxModifier() override;
	float getMilitaryModifier() override;
	void specialAction(Kingdom* kingdom) override;
};