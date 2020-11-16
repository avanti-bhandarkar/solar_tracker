{
  
  for(i=r; i<=s ; i+=10)
  {
  digitalWrite(forwards, LOW);
  digitalWrite(backwards, HIGH);  
  delay(60000);
  
  digitalWrite(forwards, HIGH);
  digitalWrite(backwards, HIGH); 
  delay(10000);
  }
  digitalWrite(forwards, HIGH);
  digitalWrite(backwards, LOW);
}
