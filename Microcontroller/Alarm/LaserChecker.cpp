bool prevIsBlocked = false;
bool CheckLaser()
{
  double adcValue = analogRead(photoPin);
  double adcVoltage = adcValue / pow(2, 12) * 3.3;

  bool isBlocked = adcVoltage < 1.4;

  prevReading = currReading;
  return !prevIsBlocked && isBlocked;
}
