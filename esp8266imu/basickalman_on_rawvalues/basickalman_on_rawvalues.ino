#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "math.h"

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

float est_ax = 0, err_ax = 32768;
float est_ay = 0, err_ay = 32768;
float est_az = 0, err_az = 32768;

float new_est_ax, new_est_ay, new_est_az;
float new_est_gx, new_est_gy, new_est_gz;

float est_gx = 0, err_gx = 32768;
float est_gy = 0, err_gy = 32768;
float est_gz = 0, err_gz = 32768;

float kg_ax, kg_ay, kg_az, kg_gx, kg_gy, kg_gz;

float err = 182, factor = 0.012;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Wire.begin();

  Serial.begin(115200);

  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
  //accelgyro.reset();

  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  /*
  Serial.print("ax:"); Serial.print(ax); Serial.print("\t");
  Serial.print("ay:"); Serial.print(ay); Serial.print("\t");
  Serial.print("az:"); Serial.print(az); Serial.print("\t");
  Serial.print("gx:"); Serial.print(gx); Serial.print("\t");
  Serial.print("gy:"); Serial.print(gy); Serial.print("\t");
  Serial.print("gz:"); Serial.println(gz);
  */
  kg_ax = err_ax / (err_ax + err);
  kg_ay = err_ay / (err_ay + err);
  kg_az = err_az / (err_az + err);
  kg_gx = err_gx / (err_gx + err);
  kg_gy = err_gy / (err_gy + err);
  kg_gz = err_gz / (err_gz + err);

  new_est_ax = est_ax + kg_ax * (ax - est_ax);
  new_est_ay = est_ay + kg_ay * (ay - est_ay);
  new_est_az = est_az + kg_az * (az - est_az);
  new_est_gx = est_gx + kg_gx * (gx - est_gx);
  new_est_gy = est_gy + kg_gy * (gy - est_gy);
  new_est_gz = est_gz + kg_gz * (gz - est_gz);

  err_ax = (1-kg_ax) * err_ax + factor * fabs(new_est_ax - est_ax);
  err_ay = (1-kg_ay) * err_ay + factor * fabs(new_est_ay - est_ay);
  err_az = (1-kg_az) * err_az + factor * fabs(new_est_az - est_az);
  err_gx = (1-kg_gx) * err_gx + factor * fabs(new_est_gx - est_gx);
  err_gy = (1-kg_gy) * err_gy + factor * fabs(new_est_gy - est_gy);
  err_gz = (1-kg_gz) * err_gz + factor * fabs(new_est_gz - est_gz);

  est_ax = new_est_ax;
  est_ay = new_est_ay;
  est_az = new_est_az;
  est_gx = new_est_gx;
  est_gy = new_est_gy;
  est_gz = new_est_gz;
  /*
  Serial.print("ax:");
  Serial.print(ax);
  Serial.print(",");
  */
  Serial.print("ax':");
  Serial.print(est_ax);
  Serial.print(",");
  /*
  Serial.print("ay:");
  Serial.print(ay);
  Serial.print(",");
  */
  Serial.print("ay':");
  Serial.print(est_ay);
  Serial.print(",");
  /*
  Serial.print("az:");
  Serial.print(az);
  Serial.print(",");
  */
  Serial.print("az':");
  Serial.println(est_az);
  // Serial.print(",");
  /*
  Serial.print("gx:");
  Serial.print(gx);
  Serial.print(",");
  */
  /*
  Serial.print("gx':");
  Serial.print(est_gx);
  Serial.print(",");
  */
  /*
  Serial.print("gy:");
  Serial.print(gy);
  Serial.print(",");
  */
  /*
  Serial.print("gy':");
  Serial.print(est_gy);
  Serial.print(",");
  */
  /*
  Serial.print("gz:");
  Serial.print(gz);
  Serial.print(",");
  */
  /*
  Serial.print("gz':");
  Serial.println(est_gz);
  */
  delay(2);
}
/*
 * As time increases, values seem to be fixed in a certain point. what?
 */
