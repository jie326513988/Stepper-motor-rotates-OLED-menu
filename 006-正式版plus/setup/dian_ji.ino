//****** 电机运动 ******
void djyd0()
{
  stepper1.setMaxSpeed(djsd);
  stepper1.setAcceleration(djjsd);
  if (qd_state == 1)
  {
    stepper1.runToNewPosition(800);
    delay(1000);
    stepper1.runToNewPosition(0);
    delay(1000);
  }
  else display1();
}
void djyd1()
{
  if (digitalRead (A0) == 0 && qd_state == 1) {
    delay(30);
    while (digitalRead (A0) == 0) display1();
    gycs ++;
    if (gycs_dz < 2) djyd3(); //来回循环不停
    else if (gycs_dz >= 2) djyd2(); //一个周期停一次
  }
  else display1();
}
void djyd2()  //穿梭次数>=2
{
  if (gycs <= gycs_dz && gycs > 0) {
    if (gycs <= gycs_dz - 1) {
      delay(jgsj);
      djwz = djwz + (xzds / 0.45);
      stepper1.runToNewPosition(djwz);
    }
    else if (gycs == gycs_dz) {
      if (djwz < 800) {
        delay(jgsj);
        stepper1.runToNewPosition(0);
      }
      else if (djwz == 800) {
        stepper1.setCurrentPosition(0);
      }
      djwz = 0;
    }
  }
  if (gycs > gycs_dz)  gycs = 0;
}
void djyd3()  //穿梭次数<2
{
  if (gycs == 0) {
    delay(jgsj);
    djwz = xzds / 0.45;
    stepper1.runToNewPosition(djwz);
  }
  else if (gycs >= 1) {
    delay(jgsj);
    stepper1.runToNewPosition(0);
    gycs = -1;
  }
}
