from math import sqrt

gyr_noise = 2.5269485695121152e-01
acc_noise = 2.7440761325972324e-01
gyr_bias = 4.8477797168896648e-03
acc_bias = 8.5627907101857859e-03

gyr_noise_sigma = gyr_noise * (1/sqrt(200))
acc_noise_sigma = acc_noise * (1/sqrt(200))
gyr_bias_sigma = gyr_bias * sqrt(200)
acc_bias_sigma = acc_bias * sqrt(200)

print('gyr_noise_sigma: ', gyr_noise_sigma)
print('acc_noise_sigma: ', acc_noise_sigma)
print('gyr_bias_sigma', gyr_bias_sigma)
print('acc_bias_sigma', acc_bias_sigma)


