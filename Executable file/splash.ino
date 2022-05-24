void splash1( int row, String txt)
{
  int curs = (17 - txt.length()) / 2;
  lcd.setCursor(0, row);
  lcd.print("----------------");

  lcd.setCursor(curs, row);
  lcd.print(txt);
  delay(300);
  
}
