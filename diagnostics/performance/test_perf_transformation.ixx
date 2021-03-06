module;
#include <vector>
#include <random>
#include <ostream>
#include <chrono>
export module tests.performance:transformation;

import tests;

import optimization.transformation;

namespace opt{
	namespace test{

		namespace perf{
			
			bool gemm_test_square_d(std::ostream& os, PerformanceTest& v, int n){
				std::vector<double> A(n*n);
				std::vector<double> B(n*n);
				std::vector<double> C(n*n);
				std::random_device os_seed;
				const uint32_t seed=os_seed();
				std::mt19937 rng(seed);
				opt::test::fill_container_randomly<std::vector<double>::iterator,double>(rng,A.begin(),n*n);
				opt::test::fill_container_randomly<std::vector<double>::iterator,double>(rng,B.begin(),n*n);
		
					
				// Get starting timepoint 
			  	auto start = std::chrono::high_resolution_clock::now(); 
				//Function to measure
				opt::math::cpu::gemm(n,n,n,1.0,A.begin(),1,n,B.begin(),1,n,double(0.0),C.begin(),1,n);
				// Get ending timepoint 
				auto stop = std::chrono::high_resolution_clock::now(); 
			  
				auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start); 
				
				os << v.name<<" took "
					 << duration.count() << " seconds \n";
			
				v.time_taken=duration;
				
				return true;
			}		
			
			//Test how quickly a square 5000x5000 matrix with is multiplied
			export bool gemm_test_square_5000_d(std::ostream& os, PerformanceTest& v){
				return gemm_test_square_d(os,v,5000);
			}
			export bool gemm_test_square_800_d(std::ostream& os, PerformanceTest& v){
				return gemm_test_square_d(os,v,800);
			}
			export bool gemm_test_square_1600_d(std::ostream& os, PerformanceTest& v){
				return gemm_test_square_d(os,v,1600);
			}

			export bool gemm_test_square_3200_d(std::ostream& os, PerformanceTest& v){
				return gemm_test_square_d(os,v,3200);
			}
		
		
		
		}
	
	}

}
