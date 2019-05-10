#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <string>

int jobs_ammount;
const int file_nr = 3;

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



std::vector<Jobs> load_jobs() {
	
	std::vector<Jobs> jobs_vector;
	std::ifstream file;
	std::string files[3] = {"in50.txt", "in100.txt", "in200.txt"};

	file.open(files[file_nr-1]);
	int r,p,q,columns;
	file >> jobs_ammount >> columns;
	for (int i = 0; i < jobs_ammount; i++)
	{
		file >> r >> p >> q;
		jobs_vector.push_back(Jobs(r, p, q));
	}

	std::cout << "File: " << files[file_nr-1] 
		<< "\nJobs: " << jobs_ammount 
		<< "\nColumns: " << columns << std::endl;
	
	std::sort(jobs_vector.begin(), jobs_vector.end(), argMin());

	return jobs_vector;
}

int find_max(int Cmax, int Q)
{
	return Cmax > Q ? Cmax : Q;
}


std::vector<Jobs> Schrage(std::vector<Jobs> jobs_vector)
{
	int i = 0;
	int Cmax = 0;
	int temp = 0;
	int temp_order = 0;
	
	std::vector<Jobs> Permutation;
	std::vector<Jobs> not_ready = jobs_vector;
	std::vector<Jobs> ready;

	int t = not_ready.front().get_R();

	while ((!empty(not_ready) || !empty(ready)))
	{
		while (!empty(not_ready) && not_ready.front().get_R() <= t)
		{
			ready.push_back(not_ready.front());
			not_ready.erase(not_ready.begin());
		}
		if (empty(ready))
			t = not_ready.front().get_R();
		else
		{
			if (ready.size() > 1)
			{
				for (int j=0; j < ready.size(); j++)
				{
					if (ready[j].get_Q() >= temp)
					{
						temp = ready[j].get_Q();
						temp_order = j;
					}
				}
			}

			Permutation.push_back(ready[temp_order]);
			ready.erase(ready.begin()+temp_order);

			t += Permutation.back().get_P();

			Cmax = find_max(Cmax, t + Permutation.back().get_Q());
			temp = 0;
			temp_order = 0;
			
			i++;
		}
	}
	
	std::cout << "\nCmax: " << Cmax << std::endl;
	return Permutation; //Jaka kolejnosc powinno mi zwrocic?
}


std::vector<Jobs> Schrage_pmtn(std::vector<Jobs> jobs_vector)
{
	int Cmax = 0;
	std::vector<Jobs> ready;
	std::vector<Jobs> not_ready = jobs_vector;
	std::vector<Jobs> Permutation;
	std::vector<Jobs> current_job;
	std::vector<Jobs> temp_job;
	current_job.push_back(Jobs(0, 0, 999999));
	temp_job.push_back(Jobs(0, 0, 0));
	
	int t = 0;

	int temp = 0;
	int temp_order = 0;

	while (!empty(ready) || !empty(not_ready))
	{
		while (!empty(not_ready) && not_ready.front().get_R() <= t)
		{
			ready.push_back(not_ready.front());	
			temp_job.erase(temp_job.begin());
			temp_job.push_back(not_ready.front());	
			not_ready.erase(not_ready.begin());

			if (temp_job.front().get_Q() > current_job.front().get_Q())
			{
				current_job.front().setP(t - temp_job.front().get_R());
				t = temp_job.front().get_R();
				

				if (current_job.front().get_P() > 0)
					ready.push_back(current_job.front());
			}
		}
		////
		if (empty(ready))
			t = not_ready.front().get_R();
		else
		{
			if (ready.size() > 1)
			{
				for (int j = 0; j < ready.size(); j++)
				{
					if (ready[j].get_Q() >= temp)
					{
						temp = ready[j].get_Q();
						temp_order = j;
					}
				}
			}

			Permutation.push_back(ready[temp_order]);	//add jobs to permutation
			current_job.erase(current_job.begin());
			current_job.push_back(ready[temp_order]);	//adding to current job

			ready.erase(ready.begin() + temp_order);

			t += Permutation.back().get_P();
			Cmax = find_max(Cmax, t + Permutation.back().get_Q());

			temp = 0;
			temp_order = 0;
		}

	}

	std::cout << "\nCmax z przerwaniami: " << Cmax << std::endl;
	return Permutation; 
}


int main() {

	std::vector<Jobs> jobs_vector = load_jobs();
	std::vector<Jobs> Permutation = Schrage(jobs_vector);
	std::vector<Jobs> Permutation2 = Schrage_pmtn(jobs_vector);
	

	system("pause");
	return 0;
}




//Complexity of vector.erase()
//Linear on the number of elements erased(destructions) plus the number of elements after the last element deleted(moving).