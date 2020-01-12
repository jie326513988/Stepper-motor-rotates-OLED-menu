#include <EEPROM.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

//****** 电机定义 ******
#include <AccelStepper.h>
//#define STEPPER2_DIR_PIN 7 //步进电机驱动器方向
//#define STEPPER2_STEP_PIN 8 //步进电机驱动器脉冲
#define STEPPER1_DIR_PIN 11 //步进电机驱动器方向
#define STEPPER1_STEP_PIN 10 //步进电机驱动器脉冲
#define EN 12 //步进电机驱动器使能
AccelStepper stepper1(AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN);
//AccelStepper stepper2(AccelStepper::DRIVER, STEPPER2_STEP_PIN, STEPPER2_DIR_PIN);
volatile uint16_t djsd; //电机速度
volatile uint16_t djjsd; //电机加速度
volatile uint16_t jgsj; //间隔时间
volatile float xzds; //旋转角度设定值
volatile int djwz = 0 ;  //电机位置

//****** EEPROM ******
int djsd_eeprom = 0; //电机速度存储地址
int djjsd_eeprom = 4; //电机速度加存储地址
int jgsj_eeprom = 8; //间隔时间存储地址
int xzds_eeprom = 12; //旋转度数存储地址
int gycs_dz_eeprom = 16; //穿梭次数（感应次数阀值）存储地址

//****** 旋转编码器相关定义 ******
const uint8_t  CLK = 2;  //中断0
const uint8_t DT = 4;   //用D4 读取B相 +或—，同时计数
const uint8_t SW = 3;//SW->D3
unsigned long time1 = 0;
unsigned long time2 = 0;

//****** 标志位相关定义 ******
boolean zjm_state = 1; //主界面状态
uint8_t zjm_count = 2; //主界面选项计数
uint32_t sj_count0 = 0; //随机画面计数
uint32_t sj_count1 = 0; //随机画面计数
boolean qd_state = 0; //启动停止状态
boolean dj_state = 1; //电机使能状态
boolean szjm_state = 0; //设置界面状态
uint8_t szjm_count = 0; //设置界面选项计数
boolean djsd_state = 0; //电机速度
boolean djjsd_state = 0; //电机加速度
boolean jgsj_state = 0; //间隔时间
boolean xzds_state = 0; //旋转度数

volatile int8_t gycs = -1; //感应次数计数
volatile uint8_t gycs_dz = 0; //感应次数计数动作阀值
volatile boolean gycs_dz_state = 0; //感应次数计数动作阀值状态

void setup()
{
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
  pinMode(A0, INPUT_PULLUP);
  //pinMode(12, OUTPUT);
  //digitalWrite(12, HIGH);

  pinMode(SW, INPUT);
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);

  attachInterrupt(0, blinkA, LOW);  //注册中断0调用函数blinkA
  attachInterrupt(1, blinkB, LOW);  //注册中断1调用函数blinkA

  EEPROM.get(djsd_eeprom, djsd);
  EEPROM.get(djjsd_eeprom, djjsd);
  EEPROM.get(jgsj_eeprom, jgsj);
  //*************************注意*************************
  //EEPROM.put(xzds_eeprom, 90);//首次刷入，第二次以后刷入时注释上
  EEPROM.get(xzds_eeprom, xzds);//第二次刷入，首次刷入时注释上
  EEPROM.get(gycs_dz_eeprom, gycs_dz);
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_wqy13_t_chinese5);
  u8g2.setContrast(50);
  stepper1.setMaxSpeed(djsd);
  stepper1.setAcceleration(djjsd);
}

void loop()
{
  djyd1();
}

void blinkA()//旋转中断
{
  if ((millis() - time1) > 3) //防抖动处理
  {
    sj_count0 = millis();
    //****** 主界面 ******
    if (digitalRead(DT) == HIGH && zjm_state == 1)  zjm_count ++;
    if (digitalRead(DT) == LOW && zjm_state == 1)   zjm_count --;

    //****** 设置界面 ******
    if (digitalRead(DT) == HIGH && szjm_state == 1 && djsd_state == 0 && djjsd_state == 0 && jgsj_state == 0 && xzds_state == 0 && jgsj_state == 0 && gycs_dz_state == 0)  szjm_count ++;
    if (digitalRead(DT) == LOW && szjm_state == 1 && djsd_state == 0 && djjsd_state == 0 && jgsj_state == 0 && xzds_state == 0 && jgsj_state == 0 && gycs_dz_state == 0)   szjm_count --;
    //电机速度数值加减
    if (digitalRead(DT) == HIGH && djsd_state == 1) {
      djsd  = djsd + 100;
      stepper1.setMaxSpeed(djsd);
    }
    if (digitalRead(DT) == LOW && djsd_state == 1) {
      djsd  = djsd - 100;
      stepper1.setMaxSpeed(djsd);
    }
    //电机加速度数值加减
    if (digitalRead(DT) == HIGH && djjsd_state == 1) {
      djjsd  = djjsd + 100;
      stepper1.setAcceleration(djjsd);
    }
    if (digitalRead(DT) == LOW && djjsd_state == 1) {
      djjsd  = djjsd - 100;
      stepper1.setAcceleration(djjsd);
    }
    //间隔时间数值加减
    if (digitalRead(DT) == HIGH && jgsj_state == 1) jgsj  = jgsj + 100;
    if (digitalRead(DT) == LOW && jgsj_state == 1) jgsj  = jgsj - 100;
    //旋转度数数值加减
    if (digitalRead(DT) == HIGH && xzds_state == 1) xzds ++;
    if (digitalRead(DT) == LOW && xzds_state == 1) xzds --;
    //感应次数计数动作阀值值加减
    if (digitalRead(DT) == HIGH && gycs_dz_state == 1) gycs_dz ++;
    if (digitalRead(DT) == LOW && gycs_dz_state == 1)  gycs_dz --;
  }
  time1 = millis();
}

void blinkB()//按下中断
{
  if ((millis() - time1) > 3) //防抖动处理
  {
    //****** 启动开关  ******
    if (digitalRead(SW) == LOW && zjm_count == 2 && dj_state == 1)
    {
      qd_state = !qd_state;
    }
    //****** 电机使能开关  ******
    if (digitalRead(SW) == LOW && zjm_count == 3 && qd_state == 0)
    {
      dj_state = !dj_state;
      if (dj_state == 1) digitalWrite(EN, LOW);
      else if (dj_state == 0) digitalWrite(EN, HIGH);
    }
    //****** 复位开关  ******
    if (digitalRead(SW) == LOW && zjm_count == 4)
    {
      gycs = -1;
    }
    //****** 进入设置界面  ******
    if (digitalRead(SW) == LOW && zjm_count == 1 && szjm_count == 0) //判断是否进入退出设置界面
    {
      zjm_state = !zjm_state;
      szjm_state = !szjm_state;
    }
    if (digitalRead(SW) == LOW && zjm_count == 1 && szjm_count == 6) //判断是否进入退出设置界面
    {
      zjm_state = !zjm_state;
      szjm_state = !szjm_state;
      szjm_count = 0;
    }
    //判断是否按下按钮，进入数值加减模式
    if (digitalRead(SW) == LOW && szjm_count == 1) //速度值加减并存储
    {
      EEPROM.put(djsd_eeprom, djsd);
      djsd_state = !djsd_state;
    }
    if (digitalRead(SW) == LOW && szjm_count == 2) //加速度值加减并存储
    {
      EEPROM.put(djjsd_eeprom, djjsd);
      djjsd_state = !djjsd_state;
    }
    if (digitalRead(SW) == LOW && szjm_count == 3) //穿梭次数（感应次数阀值）加减并存储
    {
      EEPROM.put(gycs_dz_eeprom, gycs_dz);
      gycs_dz_state = !gycs_dz_state;
    }
    if (digitalRead(SW) == LOW && szjm_count == 4) //旋转度数值加减并存储
    {
      EEPROM.put(xzds_eeprom, xzds);
      xzds_state = !xzds_state;
    }
    if (digitalRead(SW) == LOW && szjm_count == 5) //间隔时间值加减并存储
    {
      EEPROM.put(jgsj_eeprom, jgsj);
      jgsj_state = !jgsj_state;
    }
  }
  time1 = millis();
}
