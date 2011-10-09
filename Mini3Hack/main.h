class OutData
{
  
  public:
  
  char UTC_time[8]; //"hhmm.ss"
  int alt;
  double lat;
  double lon;
  
  OutData()
  {
    
    UTC_time = "0000.00";
    alt = 0;
    lat = 0.0;
    lon = 0.0;
    
  }
  
  private:
  
}
