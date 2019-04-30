#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <string>
#define Jobs_hpp
#ifndef Jobs_hpp

#include <iostream>
class Jobs
{
private:	
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
	bool operator()(const Jobs &z1, const Jobs &z2);
};

struct argMax
{
	bool operator()(const Jobs &z1, const Jobs &z2);
};

#endif
