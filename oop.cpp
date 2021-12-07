#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include <cstdlib>
#include <ctime>
#include<list>
using namespace std;

enum AlphaCoronaVirrusColor {
	blue = 0x0000ff,
	red = 0xff0000,
};

enum BetaCoronaVirusProtein
{
	NS3,
    NS5,
    E,
};
enum PatientState
{
	DIE,
	ALIVE
};

void log(string i_msg) {
	cout << i_msg << "\n";
}

class CoronaVirus
{
public:
	CoronaVirus();
	~CoronaVirus();
	string m_dra;
	int m_resistance;

	void loadADNInfomation(){
		ifstream f;
		f.open("D:/ATGX.bin");
		getline(f, m_dra);
		f.close();
		//log("CoronaVirus LoadADNInfomation()");
	}

	void reduceResistance(int i_medicineResistance) {
		m_resistance = m_resistance - i_medicineResistance;
	}

	bool isLive()
	{
		cout << "virus song" << endl;
		return this->m_resistance > 0;
	}

	virtual vector<CoronaVirus*> doClone()=0;
	virtual void doBorn() {};
	virtual void initResistance() {};
	virtual void doDie() {};
private:

};

CoronaVirus::CoronaVirus()
{
	doBorn();
	initResistance();
	//log("CoronaVirus Contructor()");
};

CoronaVirus::~CoronaVirus()
{
	doDie();
	//log("CoronaVirus Destructor()");
};


class AlphaCoronaVirus : public CoronaVirus
{
public:
	AlphaCoronaVirus();
	~AlphaCoronaVirus();
	void doBorn() override;
	vector<CoronaVirus*> doClone() override;
	void doDie() override;
	void initResistance() override;
	void setResistance(int resistance);

private:
	AlphaCoronaVirrusColor m_color;
};

AlphaCoronaVirus::AlphaCoronaVirus()
{
	this->doBorn();
	this->initResistance();
	//log("AlphaCoronaVirus Contructor()");
}

AlphaCoronaVirus::~AlphaCoronaVirus()
{
	this->doDie();
	//log("AlphaCoronaVirus Destructor()");
}

void AlphaCoronaVirus::doBorn()
{
	this->loadADNInfomation();
	this->m_color = (rand() % 2 == 0) ? AlphaCoronaVirrusColor::blue : AlphaCoronaVirrusColor::red;
	//log("AlphaCoronaVirus doBorn()");
}
vector<CoronaVirus*> AlphaCoronaVirus::doClone()
{
	vector<CoronaVirus*> array(1, new AlphaCoronaVirus(*this));
	return array;
};
void AlphaCoronaVirus::doDie()
{
	//log("AlphaCoronaVirus doDie()");
}
void AlphaCoronaVirus::initResistance()
{
	switch (this->m_color)
	{
	case AlphaCoronaVirrusColor::red:
		this->m_resistance = rand() % 11 + 10;
		break;
	case AlphaCoronaVirrusColor::blue:
		this->m_resistance = rand() % 6 + 10;
		break;
	}
	//log("AlphaCoronaVirus initResistance()");
}
void AlphaCoronaVirus::setResistance(int resistance)
{
	this->m_resistance = resistance;
}

class BetaCoronaVirus :public CoronaVirus
{
public:
	BetaCoronaVirus();
	~BetaCoronaVirus();
	void doBorn() override;
	vector<CoronaVirus*> doClone() override;
	void doDie() override;
	void initResistance() override;
	void SetResistance(int resistance);
private:
	BetaCoronaVirusProtein m_protein;
};

BetaCoronaVirus::BetaCoronaVirus()
{
	this->doBorn();
	this->initResistance();
	//log("BetaCoronaVirus Contructor()");
};

BetaCoronaVirus::~BetaCoronaVirus()
{
	this->doDie();
	//log("BetaCoronaVirus Destructor()");
};

void BetaCoronaVirus::doBorn(){
	this->loadADNInfomation();
	if (rand() % 3 == 0) {
		this->m_protein = BetaCoronaVirusProtein::NS3;
	}
	else if(rand() % 3 == 1)
	{
		this->m_protein = BetaCoronaVirusProtein::NS5;
	}
	else
	{
		this->m_protein = BetaCoronaVirusProtein::E;
	}
	//log("BetaCoronaVirus doBorn()");
}

vector<CoronaVirus*> BetaCoronaVirus::doClone(){
	vector<CoronaVirus*> array(2, new BetaCoronaVirus(*this));
	return array;
}

void BetaCoronaVirus::doDie() {
	
	//log("BetaCoronaVirus doDie()");
}

void BetaCoronaVirus::initResistance() {
	switch (this->m_protein)
	{
	case BetaCoronaVirusProtein::NS3:
		this->m_resistance = rand() % 11;
	case BetaCoronaVirusProtein::NS5:
		this->m_resistance = rand() % 11 + 10;
	case BetaCoronaVirusProtein::E:
		this->m_resistance = rand() % 11 + 20;
	}
	//log("BetaCoronaVirus initResistance()");
}

void BetaCoronaVirus::SetResistance(int resistance) {
	this->m_resistance = resistance;
}

class Patient
{
public:
	Patient();
	~Patient();
	int number_Alpha = 0;
	int number_Beta = 10;
	int Alpha_Resistance = 100;
	int Beta_Resistance = 100;
	int m_resistance;
	PatientState getState();
	void initResistance();
	void doStart(int number_Alpha, int number_Beta);
	void takeMedicine(int i_medicineResistance);
	void doDie();
	PatientState m_state = PatientState::ALIVE;
	vector<CoronaVirus*> m_virusList;

	void SetResistance(int resistance) {
		this->m_resistance = resistance;
	}
private:

};

Patient::Patient()
{
	this->initResistance() ;
	this->doStart(number_Alpha, number_Beta);
	this->m_state = ALIVE;
}

Patient::~Patient()
{
}

void Patient::initResistance() {//khoi tao de khang
	this->m_resistance = rand() % 8001 + 1000;
	//cout << "Patient initResistance()" << endl;
}


void Patient::doStart(int number_Alpha, int number_Beta) {
	for (int i = 0; i < number_Alpha; i++)
	{
		auto virus = new AlphaCoronaVirus();
		virus->setResistance(Alpha_Resistance);
		this->m_virusList.push_back(virus);
		this->m_state = ALIVE;
	}
	for (int i = 0; i <	number_Beta; i++)
	{
		auto virus = new BetaCoronaVirus();
		virus->SetResistance(Beta_Resistance);
		this->m_virusList.push_back(virus);
		this->m_state = ALIVE;
	}
}

void Patient::takeMedicine(int i_medicineResistance) {
	cout << "trong co the nguoi co " << m_virusList.size() << "virus" << endl;
	for (vector<CoronaVirus*>::iterator it = m_virusList.begin(); it < m_virusList.end(); it++)
	{
		cout << "de khang ban dau virut" << (*it)->m_resistance << endl;
		(*it)->reduceResistance(i_medicineResistance);
		if ((*it)->isLive() == false)
		{
			cout << (*it)->m_resistance;

			if (it != m_virusList.end())
			{
				it = m_virusList.erase(it);
			}
			if (it > m_virusList.begin()) it--;
			cout << "a Virus die" << endl;

		}
	}
	if (m_virusList.size() == 1)
	{
		auto it = m_virusList.begin();
		if ((*it)->m_resistance <= i_medicineResistance)
			m_virusList.clear();
	}
	cout << "trong co the nguoi con lai " << m_virusList.size() << "virus" << endl;

	vector <CoronaVirus*> virusnew;
	for (vector<CoronaVirus*>::iterator it = m_virusList.begin(); it < m_virusList.end(); it++)
	{
		auto i = (*it)->doClone();
		if (i.size() == 1)
			virusnew.insert(virusnew.end(), *i.begin());
		else
		{
			for (vector<CoronaVirus*>::iterator j = i.begin(); j < i.end(); j++)
			{
				virusnew.push_back(*j);
			}
		}
	}
	for (vector<CoronaVirus*>::iterator it = virusnew.begin(); it < virusnew.end(); it++)
	{
		m_virusList.push_back(*it);
	}

	cout << "tong sau khi nhan ban " << m_virusList.size() << "virus" << endl;
	int sum = 0;
	for (vector<CoronaVirus*>::iterator it = m_virusList.begin(); it < m_virusList.end(); it++)
	{
		sum += (*it)->m_resistance;
	}
	cout << "de khang virus" << sum << "de khang benh nhan" << this->m_resistance << endl;
	if (sum > this->m_resistance) this->doDie();
	else
	{
		cout << "dont die" << endl;
	}
}

void Patient::doDie() {
	m_state = DIE;
	this->m_virusList.clear();
	//cout << "Patient doDie" << endl;
}

PatientState Patient::getState() {
	//cout << "Patient getState" << endl;
	return m_state;
}

int main() {
	Patient p;
	p.SetResistance(1000);
	const int k_m = 1;
	while (p.getState() != DIE) {
		p.takeMedicine(k_m);
	}
	return 0;
}































