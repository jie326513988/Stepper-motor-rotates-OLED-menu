//****** 设置界面 ******

void szjm_0() //第1页内容
{
  u8g2.setCursor(1, 14);
  u8g2.print("速度");
  u8g2.setCursor(80, 14);
  u8g2.print(djsd);

  u8g2.setCursor(1, 30);
  u8g2.print("加速度");
  u8g2.setCursor(80, 30);
  u8g2.print(djjsd);

  u8g2.setCursor(1, 46);
  u8g2.print("穿梭次数");
  u8g2.setCursor(80, 46);
  u8g2.print(gycs_dz);

  u8g2.setCursor(1, 62);
  u8g2.print("旋转度数");
  u8g2.setCursor(80, 62);
  u8g2.print(xzds, 0);
}

void szjm_0_0() //第2页内容
{
  u8g2.setCursor(1, 14);
  u8g2.print("间隔时间");
  u8g2.setCursor(80, 14);
  u8g2.print(jgsj);

  u8g2.setCursor(1, 30);
  u8g2.print("返回");

  u8g2.setCursor(1, 63);
  u8g2.print("Version:006");
}

//****** 第1页 ******
void szjm_1() //显示设置界面第1页，无光标
{
  u8g2.firstPage();
  do {
    if (szjm_count <= 4) szjm_0();
    if (szjm_count >= 5) szjm_0_0();
  } while ( u8g2.nextPage() );
}
void szjm_2() //光标指向速度
{
  u8g2.firstPage();
  do {
    if (djsd_state == 0) szjm_1();
    if (djsd_state == 1) szjm_0();
    u8g2.drawFrame(0, 0, 128, 16);
  } while ( u8g2.nextPage() );
}
void szjm_3() //光标指向加速度
{
  u8g2.firstPage();
  do {
    if (djjsd_state == 0) szjm_1();
    if (djjsd_state == 1) szjm_0();
    u8g2.drawFrame(0, 16, 128, 16);
  } while ( u8g2.nextPage() );
}
void szjm_4() //光标指向穿梭次数（感应次数阀值）
{
  u8g2.firstPage();
  do {
    if (gycs_dz_state == 0) szjm_1();
    if (gycs_dz_state == 1) szjm_0();
    u8g2.drawFrame(0, 32, 128, 16);
  } while ( u8g2.nextPage() );
}
void szjm_5() //光标指向旋转角度
{
  u8g2.firstPage();
  do {
    if (xzds_state == 0) szjm_1();
    if (xzds_state == 1) szjm_0();
    u8g2.drawFrame(0, 48, 128, 16);
  } while ( u8g2.nextPage() );
}

//****** 第2页 ******
void szjm_1_1() //显示设置界面第2页，无光标
{
  u8g2.firstPage();
  do {
    szjm_0_0();
  } while ( u8g2.nextPage() );
}
void szjm_6() //光标指向间隔时间
{
  u8g2.firstPage();
  do {
    if (jgsj_state == 0) szjm_1_1();
    if (jgsj_state == 1) szjm_0_0();
    u8g2.drawFrame(0, 0, 128, 16);
  } while ( u8g2.nextPage() );
}
void szjm_7() //光标指向返回
{
  u8g2.firstPage();
  do {
    szjm_1_1();
    u8g2.drawFrame(0, 16, 128, 16);
  } while ( u8g2.nextPage() );
}
