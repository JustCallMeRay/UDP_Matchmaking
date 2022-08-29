#import <vector> 
using std::vector;

#import <iostream>

struct packet {    //once created should be immutable
  private: 
    uint ip;  
    uint elo; 
  public:
    // elo => elo; 
    uint getIp(){return ip;}
    uint getElo(){return elo;}
    packet(uint Ip, uint Elo)
    {
      ip = Ip;
      elo = Elo;      
    }
    bool const operator < (const packet p){return elo < p.elo; }
};

vector<packet>::iterator sorted_pos(vector<packet> vec, int item){
  int key = vec.size() / 2 ;
  int min = 0; int max = vec.size();  
  while(max-min>1)
    {
       if(vec[key].getElo() > item)
      { 
        min = key; 
        key += (key/2);
      } else if( vec[key].getElo() == item) {
        return vec.begin() + key;
      } else {
        max = key; 
        key -= (key/2);
      }
    } // end while 
  return vec.begin() + min;
}

