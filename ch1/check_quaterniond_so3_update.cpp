#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <sophus/so3.hpp>

int main()
{
    // 旋转矩阵
    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();
    Eigen::AngleAxisd rotation_vector(M_PI/2, Eigen::Vector3d(0,0,1));  // 沿Z轴旋转 90 度
    rotation_matrix = rotation_vector.toRotationMatrix();
    std::cout << "R: "<< std::endl << rotation_matrix << std::endl << std::endl;

    // 构造对应的四元数
    Eigen::Quaterniond q(rotation_matrix);
    std::cout << "q: "<< std::endl << q.coeffs().transpose() << std::endl << std::endl;

    // 使用对数映射获得它的李代数
    Sophus::SO3d SO3_R(rotation_matrix);
    std::cout << "so3: "<< std::endl << SO3_R.log().transpose() << std::endl << std::endl;

    // 更新量 omega
    Eigen::Vector3d omega(0.01, 0.02, 0.03); //更新量

    // 李代数更新
    Eigen::Matrix3d skew_symmetric_matrix = Sophus::SO3d::hat(omega).matrix();
    std::cout << "SO3 hat: "<< std::endl << skew_symmetric_matrix << std::endl << std::endl;
    Sophus::SO3d SO3_updated = SO3_R * Sophus::SO3d::exp(omega);
    std::cout << "SO3 updated: " << std::endl << (SO3_R * Sophus::SO3d::exp(omega)).matrix() << std::endl << std::endl;

    // 四元数更新
    Eigen::Quaterniond q_update(1, omega(0)/2, omega(1)/2, omega(2)/2);
    Eigen::Quaterniond q_updated = q * q_update.normalized();
    std::cout << "Quaterniond updated: " << std::endl << q_updated.toRotationMatrix() << std::endl << std::endl;

    // 衡量两种方法之间的差距
    std::cout << "diff: " << std::endl << SO3_updated.matrix().transpose()*q_updated.toRotationMatrix() << std::endl;

    return 0;
}