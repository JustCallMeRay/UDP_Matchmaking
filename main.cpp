#import <vector> 
using std::vector; //deprecated 
#import <map>
using std::map;

// for debugging 
#import <iostream> 

// IPs are 4 bytes (4 0-255 values) and an int is 4 bytes so makes sense to convert them like this, 
// LAN connections do make this more complicated and suggest use of a struct, psuedo-coded below
struct IP {
  int publicIP;
  char LANid; 
};


const int MY_ELO = 56678; //for referance and scalablity

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


// Ranges of ranks (bronze, silver, gold etc) 
// Placed in array as ranks don't need to be equally spaced
const int RANK_NUM = 4;
const int RANKS[RANK_NUM+1] = {0, 10, 20, 30, 40 }; // each item represents the lower bound of the rank
// packet my_packet = packet(0, MY_ELO); //client doesn't need referance to own IP
const uint ELO_LOWERBOUND = MY_ELO * 0.9;
const uint ELO_UPPERBOUND = MY_ELO * 1.1;

// vector<packet> database[RANK_NUM]; // one for each rank, each should be sorted
map<int,int> database; 

vector<packet> possible_matches; // the players 

vector<packet>::iterator sorted_pos(vector<packet> vec, int item)
{
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

bool database_insert(map<int,int> & M, packet p)
{
  uint item = p.getElo();
  if (std::distance(M.find(item), M.end()) > 0) //contains is c++ 20
  {
    // key is not in map
    M[item] = p.getIp(); //add item to map
    return true;
  }
  return false;
}

void check_elo( packet query )
{
  int q_elo = query.getElo();
  if (q_elo > ELO_LOWERBOUND && q_elo < ELO_UPPERBOUND)
  {
    //Add to my possible matches
    possible_matches.emplace_back(query.getIp(),q_elo); 
  }
  database_insert(database, query);
} 

int main(){
  std::cout<<"success! :)" << "\n";
}
  
