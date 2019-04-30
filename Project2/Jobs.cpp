#include "Jobs.h"

class Jobs
{
private:	//Czasy: przygotowania, wykonywania, dostarczenia, moment zakoñczenia
	int R;
	int P;
	int Q;
public:
	Jobs(int R, int P, int Q)
	{
		this->R = R;
		this->P = P;
		this->Q = Q;
	}

	int get_R() const { return R; }
	int get_P() { return P; }
	int get_Q() const { return Q; }

	void setR(int R) { this->R = R; }
	void setP(int P) { this->P = P; }
	void setQ(int Q) { this->Q = Q; }

};

struct argMin
{
	bool operator()(const Jobs &z1, const Jobs &z2)
	{
		return z1.get_R() < z2.get_R();
	}
};
struct argMax
{
	bool operator()(const Jobs &z1, const Jobs &z2)
	{
		return z1.get_Q() > z2.get_Q();
	}
};

