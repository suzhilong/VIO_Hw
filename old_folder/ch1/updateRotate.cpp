#include <iostream>
#include <cmath>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "sophus/so3.h"
#include "sophus/se3.h"

using namespace std;

int main(){
	//沿z轴旋转90度的旋转矩阵
	Eigen::AngleAxisd v(M_PI/2, Eigen::Vector3d(0, 0, 1));
	Eigen::Matrix3d R = v.toRotationMatrix();
	Eigen::Quaterniond q(R);
	
	//更新量 w=[0.01,0.02,0.03]
	//用SO3更新 R <- Rexp(w^)
	Sophus::SO3 SO3_R(R);
	//cout << "SO3_R:\n" << SO3_R << endl;
	Eigen::Vector3d update_R(0.01,0.02,0.03);
    Sophus::SO3 R_updated = SO3_R*Sophus::SO3::exp(update_R);
	
	//用四元数更新 q <- q * [1,(1/2)w]
	Eigen::Quaterniond update_q(1, 0.01/2, 0.02/2, 0.03/2);
	Eigen::Quaterniond q_updated = q*update_q;
	
	cout << "R_updated:\n" << R_updated.matrix()
		<<"\nq_updated:\n" << q_updated.matrix() << endl;
	
	return 0;
}