/*光标闪烁原理

   闪烁
  u8g2.firstPage();
  do {
    zjm_2();
    u8g2.drawFrame(93, 46, 33, 18);
  } while ( u8g2.nextPage() );

   不闪烁
    u8g2.firstPage();
  do {
    zjm_1();
    u8g2.drawFrame(93, 46, 33, 18);
  } while ( u8g2.nextPage() );

*/
//****** 主界面 ******

void zjm_0() //主界面内容
{
  u8g2.setFont(u8g2_font_logisoso28_tn);
  if (gycs < 0)
  {
    u8g2.setCursor(35, 31);
    u8g2.print(gycs); //感应次数
  }
  else if(gycs >= 0)
  {
    u8g2.setCursor(55, 31);
    u8g2.print(gycs); //感应次数
  }
  u8g2.setFont(u8g2_font_wqy13_t_chinese5);

  u8g2.setCursor(1, 61);
  u8g2.print("设置");

  u8g2.setCursor(96, 15);
  u8g2.print("复位");

  u8g2.setCursor(1, 10);
  u8g2.print(abs(xzds), 0); //旋转角度

  if (abs(xzds) / 10 >= 0 && abs(xzds) / 10 < 1)  u8g2.drawCircle(12, 2, 2, U8G2_DRAW_ALL);
  if (abs(xzds) / 10 >= 1 && abs(xzds) / 10 < 10)  u8g2.drawCircle(20, 2, 2, U8G2_DRAW_ALL);
  if (abs(xzds) / 10 >= 10 && abs(xzds) / 10 < 100)  u8g2.drawCircle(28, 2, 2, U8G2_DRAW_ALL);

  //u8g2.setCursor(0, 10);
  //u8g2.print( zjm_count);
}

void zjm_1() //主界面内容
{
  if (qd_state == 0) {
    u8g2.setCursor(50, 61);
    u8g2.print("启动");
  }
  if (qd_state == 1) {
    u8g2.setCursor(50, 61);
    u8g2.print("停止");
  }

  if (dj_state == 1) {
    u8g2.setCursor(96, 61);
    u8g2.print("解锁");
  }
  if (dj_state == 0) {
    u8g2.setCursor(96, 61);
    u8g2.print("锁定");
  }

  if (xzds >= 0)
  {
    u8g2.setCursor(2, 30);
    u8g2.print("顺");
  }
  if (xzds < 0)
  {
    u8g2.setCursor(2, 30);
    u8g2.print("逆");
  }

  zjm_0();
}

void zjm_2() //显示主界面，无光标
{
  u8g2.firstPage();
  do {
    zjm_1();
  } while ( u8g2.nextPage() );
}

void zjm_3() //光标指向设置，并闪烁
{
  u8g2.firstPage();
  do {
    zjm_2();
    u8g2.drawFrame(0, 46, 33, 18);
  } while ( u8g2.nextPage() );
}

void zjm_4() //光标指向启动/停止，并闪烁
{
  u8g2.firstPage();
  do {
    zjm_2();
    u8g2.drawFrame(49, 46, 33, 18);
  } while ( u8g2.nextPage() );
}

void zjm_5() //光标指向解锁/锁定，并闪烁
{
  u8g2.firstPage();
  do {
    zjm_2();
    u8g2.drawFrame(95, 46, 33, 18);
  } while ( u8g2.nextPage() );
}

void zjm_6() //光标指向复位，并闪烁
{
  u8g2.firstPage();
  do {
    zjm_2();
    u8g2.drawFrame(95, 0, 33, 18);
  } while ( u8g2.nextPage() );
}
