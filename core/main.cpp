import optimization.transformation;
import optimization.gpubindings;
import optimization.solvers;
#include <iostream>
#include <vector>
#include<array>

template<class T>
typename T::value_type sos(T& storage){
	auto sum=*(storage.begin());
	auto curr=storage.begin()+1;
	for (int i=0;i<storage.size();i++){
		sum+=*curr;
		curr++;
	}
		return sum;
}



template<class T>
void residual(const T& params, typename T::iterator storage){
	*storage=params[0]-1;
	*(storage+1)=params[1]+0.3;
}

/*Transposed jacobian*/
template<class T>
void j_t_circle(const T& x, typename T::iterator storage){
	
	*storage=2*x[0];
	*(storage+1)=0;
	*(storage+2)=0;
	*(storage+3)=2*x[1];	
}

template<class T>
void j_t_j_inv_circle(const T& x, typename T::iterator storage){
	*storage=1.0/(4.0*x[0]*x[0]);
	*(storage+1)=0;
	*(storage+2)=0;
	*(storage+3)=1.0/(4.0*x[1]*x[1]);	
}




int main(){
	std::vector<double> v={1.3,-0.3};
	std::array<double,3> v2={1,-0.3,4};
	//std::cout<<sos(v2);
	
	
	int dim_residual=2;
	opt::solvers::gns::ResidualPure<std::vector<double>> res(residual,dim_residual);
	opt::solvers::gns::ResidualPureJI<std::vector<double>> res_ji(residual,j_t_circle,j_t_j_inv_circle,dim_residual);
//	opt::solvers::A a(res);
	opt::solvers::GNSCPU gns(res_ji,std::cout);
	//opt::solvers::gns::Residual<opt::solvers::gns::ResidualSpec::Pure,std::vector<double>,opt::solvers::gns::HasJacInv::No> res(residual,dim_residual);
	//opt::solvers::GNSCPU gns(res,std::cout);
	
	//<std::vector<double>,opt::solvers::gns::ResidualSpec::Pure,opt::solvers::gns::HasJacInv::No>
	auto result=gns.run(v);
	if (result){
		std::cout<<"Gauss-Newton procedure finished successfully\n";
	}
	else{
		std::cout<<"Gauss-Newton procedure terminated with error.\n";
	}

	
}