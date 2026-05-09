//probably a lidar public class to create an instance have things like lidar1.read(), lidar2.read()... lidarN.read(), in case i have more than one
#ifndef LIDAR_H
#define LIDAR_H
class Lidar{
  public:
    Lidar(int id);

    void begin(); 
    void update(); 
    int getDistance() const; 
  
  private: 
    int LidarId; 
    int distance;
}
#endif