#import <vector> 
using std::vector;

#import <iostream>

const int MYIP = 6689;
const int MYELO = 56678;

struct packet {    //once created should be immutable
  private: 
    int ip;  //type? 
    int elo; 
  public:
    // elo => elo; 
    int getIp(){return ip;}
    int getElo(){return elo;}
    packet(int Ip, int Elo)
    {
      ip = Ip;
      elo = Elo;      
    }
    bool const operator < (const packet p){return elo < p.elo; }
};

// Ranges of ranks (bronze, silver, gold etc) 
// Placed in array as ranks don't need to be equally spaced
const int RANK_NUM = 4;
const int RANKS[RANK_NUM+1] = {0, 10, 20, 30, 40 }; // each item represents the lower bound of the rank
packet my_packet = packet(MYIP, MYELO);
const int ELO_LOWERBOUND = my_packet.getElo() * 0.9;
const int ELO_UPPERBOUND = my_packet.getElo() * 1.1;

vector<packet> database[RANK_NUM]; // one for each rank, each should be sorted
vector<packet> possible_matches; // the players 

vector<packet>::iterator sorted_pos(vector<packet> vec, int item)
{
  int key = vec.size() / 2 ;
  int min = 0; int max = vec.size();  
  while(max-min>1)
    {
      (vec[key].getElo > item)
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

void check_elo( packet query )
{
  int q_elo = query.getElo();
  if (q_elo > ELO_LOWERBOUND && q_elo < ELO_UPPERBOUND)
  {
    possible_matches.emplace_back(query.getIp(),q_elo); // not a sorted vector
  }
  for (int i=0; i < RANK_NUM; i++)
    {
      if (q_elo > RANKS[i+1])
      {
        database[i].emplace(sorted_pos(database[i],q_elo), query.getIp() , q_elo);
        // UDP.send(database[i].size()); // other end needs to know size of message to recive it 
        // UDP.send(database[i]); // now we can send the data
        break;
      }
    }
  
} 

int main(){
  std::cout<<"help"<<"\n";
}
  
