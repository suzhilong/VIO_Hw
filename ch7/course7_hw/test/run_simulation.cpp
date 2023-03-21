#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <eigen3/Eigen/Dense>
#include <iomanip>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>

#include "System.h"

using namespace std;
using namespace cv;
using namespace Eigen;

const int nDelayTimes = 2;
string sData_path = "../../../ch2/course2_hw_new/vio_data_simulation/bin/";
string sConfig_path = "../config/simluation_config.yaml";

std::shared_ptr<System> pSystem;

void PubImuData() {
  string sImu_data_file = sData_path + "imu_pose_noise.txt";
  cout << "1 PubImuData start sImu_data_filea: " << sImu_data_file << endl;
  ifstream fsImu;
  fsImu.open(sImu_data_file.c_str());
  if (!fsImu.is_open()) {
    cerr << "Failed to open imu file! " << sImu_data_file << endl;
    return;
  }

  std::string sImu_line;
  double dStampNSec = 0.0;
  Vector3d vAcc;
  Vector3d vGyr;
  double tmp;
  while (std::getline(fsImu, sImu_line) &&
         !sImu_line.empty()) {  // read imu data
    std::istringstream ssImuData(sImu_line);
    ssImuData >> dStampNSec;  // timestamp
    for (int i = 0; i < 7; i++) {
      ssImuData >> tmp;  // imu quaternion(4)，imu position(3)
    }
    ssImuData >> vGyr.x() >> vGyr.y() >> vGyr.z() >> vAcc.x() >> vAcc.y() >>
        vAcc.z();
    // time is second
    pSystem->PubImuData(dStampNSec, vGyr, vAcc);
    usleep(5000 * nDelayTimes);
  }
  fsImu.close();
}

void PubImageData() {
  string sImage_file = sData_path + "cam_pose.txt";

  cout << "1 PubImageData start sImage_file: " << sImage_file << endl;

  ifstream fsImage;
  fsImage.open(sImage_file.c_str());
  if (!fsImage.is_open()) {
    cerr << "Failed to open image file! " << sImage_file << endl;
    return;
  }

  std::string sImage_line;
  double dStampNSec;

  int n = 0;
  // cv::namedWindow("SOURCE IMAGE", CV_WINDOW_AUTOSIZE);
  while (std::getline(fsImage, sImage_line) && !sImage_line.empty()) {
    std::istringstream ssImuData(sImage_line);
    ssImuData >> dStampNSec;
    string pointsFileName =
        sData_path + "keyframe/all_points_" + to_string(n) + ".txt";

    std::ifstream fsPoints;
    fsPoints.open(pointsFileName);
    if (!fsPoints.is_open()) {
      cerr << "Failed to open points file! " << sImage_file << endl;
      return;
    }

    std::vector<cv::Point2f> featurePoints;
    double tmp;
    std::string sPoints_line;
    while (std::getline(fsPoints, sPoints_line) && !sPoints_line.empty()) {
      std::istringstream ssPointsData(sPoints_line);
      for (size_t i = 0; i < 4; i++) {
        ssPointsData >> tmp; // x, y, z, 1, u, v
      }
      cv::Point2f tmpPoint;
      ssPointsData >> tmpPoint.x >> tmpPoint.y;
      featurePoints.emplace_back(tmpPoint);
    }

    pSystem->PubFeatureData(dStampNSec, featurePoints);

    usleep(50000 * nDelayTimes);
    n++;
  }
  fsImage.close();
}

int main(int argc, char **argv) {
  // if (argc != 3) {
  //   cerr << "./run_simuilation  ../config/ \n"
  //        << "For example:\n "
  //        << "./run_simulation ../vio_data_simulation/bin/ ../config/" <<
  //        endl;
  //   return -1;
  // }
  // sData_path = argv[1];
  // sConfig_path = argv[2];

  pSystem.reset(new System(sConfig_path));

  std::thread thd_BackEnd(&System::ProcessBackEnd, pSystem);

  // sleep(5);
  std::thread thd_PubImuData(PubImuData);
  std::thread thd_PubImageData(PubImageData);
  std::thread thd_Draw(&System::Draw, pSystem);

  thd_PubImuData.join();
  thd_PubImageData.join();
  thd_BackEnd.join();
  thd_Draw.join();

  cout << "main end... see you ..." << endl;
  return 0;
}
