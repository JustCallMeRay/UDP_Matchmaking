#import <vector> 
using std::vector;

#import <map>
using std::map;

// for debugging
#import <iostream> 
using std::cout;

// IPs are 4 bytes (4 0-255 values) and an int is 4 bytes so makes sense to convert them like this, 
// LAN connections do make this more complicated and suggest use of a struct, psuedo-coded below
struct IP {
  uint publicIP;
  char LANid; 
    
  IP(uint Public, char LANID = 0)
  {
    publicIP = Public; LANid = LANID;
  }
  IP(){}

};


struct packet {    //once created should be immutable
  private: 
    IP ip;  
    uint elo; 
  public:
    // elo => elo; 
    IP getIp(){return ip;}
    uint getElo(){return elo;}
    packet(uint publicIP, char Lanid, uint Elo){
      ip = IP(publicIP, Lanid); elo = Elo; 
    }
    packet(IP Ip, uint Elo){
      ip = Ip;
      elo = Elo;      
    }
    packet(){}
    bool const operator < (const packet p){return elo < p.elo; }
};

const int MY_ELO = 56678; //for referance and scalablity


// Ranges of ranks (bronze, silver, gold etc) 
// Placed in array as ranks don't need to be equally spaced
const int RANK_NUM = 4;
const int RANKS[RANK_NUM+1] = {0, 10, 20, 30, 40 }; // each item represents the lower bound of the rank
// packet my_packet = packet(0, MY_ELO); //client doesn't need referance to own IP
const uint ELO_LOWERBOUND = MY_ELO * 0.9;
const uint ELO_UPPERBOUND = MY_ELO * 1.1;

// vector<packet> database[RANK_NUM]; // one for each rank, each should be sorted
map<int,IP> database; 

vector<packet> possible_matches; // the players 

bool database_insert(map<int,IP> & M, packet p)
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

void on_questioned(packet q, int lower_bound, int upper_bound)
{
  cout << "not yet implmneted \n"; 
}

int main(){
  cout<<"successfully compiled! 👍😁" << "\n";
}
  
