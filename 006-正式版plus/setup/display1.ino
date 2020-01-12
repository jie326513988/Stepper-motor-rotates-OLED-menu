//****** 显示函数 ******

void display1()
{

  //主界面显示
  sui_ji();
  /*if (zjm_state == 1 && szjm_state == 0)
    {
    if (zjm_count == 0) zjm_2(); //显示主界面，光标不显示
    else if (zjm_count == 1) zjm_3(); //光标指向设置
    else if (zjm_count == 2) zjm_4(); //光标指向启动/停止
    else if (zjm_count == 3) zjm_5(); //光标指向锁定/解锁
    else if (zjm_count == 4) zjm_6(); //光标指向复位
    }

    //设置界面显示
    else if (zjm_state == 0 && szjm_state == 1)
    {
    if (szjm_count == 0) szjm_1(); //显示设置界面，无光标
    else if (szjm_count == 1) szjm_2(); //光标指向速度
    else if (szjm_count == 2) szjm_3(); //光标指向加速度
    else if (szjm_count == 3) szjm_4(); //光标指向光标指向穿梭次数（感应次数阀值）
    else if (szjm_count == 4) szjm_5(); //光标指向旋转度数
    else if (szjm_count == 5) szjm_6(); //光标指向间隔时间
    else if (szjm_count == 6) szjm_7(); //光标指向返回
    }*/

  //光标、数值超出归零
  if (zjm_count > 4) zjm_count = 4; // 主菜单的光标位置
  if (szjm_count > 6) szjm_count = 6; // 设置菜单的光标位置

  if (djsd > 65300) djsd = 0;
  if (djjsd > 65300) djjsd = 0;
  if (jgsj > 60000 || jgsj < 0 ) jgsj = 0;
  if (xzds > 370) xzds = 0;
}

void sui_ji()
{
  if (millis() - sj_count0 < 6000) {
    //主界面显示
    if (zjm_state == 1 && szjm_state == 0)
    {
      if (zjm_count == 0) zjm_2(); //显示主界面，光标不显示
      else if (zjm_count == 1) zjm_3(); //光标指向设置
      else if (zjm_count == 2) zjm_4(); //光标指向启动/停止
      else if (zjm_count == 3) zjm_5(); //光标指向锁定/解锁
      else if (zjm_count == 4) zjm_6(); //光标指向复位
    }
    //设置界面显示
    else if (zjm_state == 0 && szjm_state == 1)
    {
      if (szjm_count == 0) szjm_1(); //显示设置界面，无光标
      else if (szjm_count == 1) szjm_2(); //光标指向速度
      else if (szjm_count == 2) szjm_3(); //光标指向加速度
      else if (szjm_count == 3) szjm_4(); //光标指向光标指向穿梭次数（感应次数阀值）
      else if (szjm_count == 4) szjm_5(); //光标指向旋转度数
      else if (szjm_count == 5) szjm_6(); //光标指向间隔时间
      else if (szjm_count == 6) szjm_7(); //光标指向返回
    }
  }
  else {
    if (millis() - sj_count1 < 2100) return;
    sj_count1 = millis();
    u8g2.clearBuffer();
    uint8_t x , y;
    x = random(0, 120);
    y = random(7, 63);
    u8g2.setCursor(x, y);
    u8g2.print(gycs); //感应次数
    x = random(0, 120);
    y = random(7, 63);
    u8g2.setCursor(x, y);
    u8g2.print(abs(xzds), 0); //旋转角度
    if (abs(xzds) / 10 >= 0 && abs(xzds) / 10 < 1)  u8g2.drawCircle(x + 11, y - 8, 2, U8G2_DRAW_ALL);
    else if (abs(xzds) / 10 >= 1 && abs(xzds) / 10 < 10)  u8g2.drawCircle(x + 19, y - 8, 2, U8G2_DRAW_ALL);
    else if (abs(xzds) / 10 >= 10 && abs(xzds) / 10 < 100)  u8g2.drawCircle(x + 27, y - 8, 2, U8G2_DRAW_ALL);
    if (xzds >= 0)
    {
      u8g2.setCursor(x+1, y+20);
      u8g2.print("顺");
    }
    else if (xzds < 0)
    {
      u8g2.setCursor(x+1, y+20);
      u8g2.print("逆");
    }
    u8g2.sendBuffer();
  }
}
