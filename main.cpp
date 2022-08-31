#import <vector> 
using std::vector;

#import <map>
using std::map;

// for debugging
#import <iostream> 
using std::cout;

#import <string>
using std::string;

#import <algorithm>
// IPs are 4 bytes (4 * 0-255 values) and an int(32) is 4 bytes so makes sense to convert them 
// LAN connections do make this more complicated and suggests use of a struct so I included one for scalability.
struct IP {
  uint publicIP;
  char LANid; 
    
  IP(uint Public, char LANID = 0)
  {
    publicIP = Public; LANid = LANID;
  }
  IP(){}

};

struct Packet {    //once created should be immutable
  private: 
    IP ip;  
    uint elo; 
  public:
    // elo => elo; 
    IP getIp(){return ip;}
    uint getElo(){return elo;}
    Packet(uint publicIP, char Lanid, uint Elo){
      ip = IP(publicIP, Lanid); elo = Elo; 
    }
    Packet(IP Ip, uint Elo){
      ip = Ip;
      elo = Elo;      
    }
    Packet(){}
    bool const operator < (const Packet p){return elo < p.elo; }
};

class Bounds 
{
  public: 
    uint Lb;
    uint Ub;
    Bounds(){}
    Bounds(int Lower, int Upper){
      Lb = Lower; Ub = Upper;
    }
    bool const operator == (const uint c){
      return (c < Ub && c > Lb);
    }
    
};

const int MY_ELO = 56678; //for referance and scalablity


Bounds bounds = Bounds(MY_ELO * 0.9, MY_ELO * 1.1);
const uint ELO_LOWERBOUND = MY_ELO * 0.9;
const uint ELO_UPPERBOUND = MY_ELO * 1.1;

// vector<Packet> database[RANK_NUM]; // one for each rank, each should be sorted
map<int,IP> database; 

// to be deprecated, look ups in map instead
vector<Packet> possible_matches; // the players 

//to be depricated
bool database_insert(map<int,IP> & M, Packet p)
{
  uint item = p.getElo();
  if (std::distance(M.find(item), M.end()) > 0) 
  {
    // key is not in database
    M[item] = p.getIp(); //add item to map
    return true;
  }
  
  return false;
}

//Run when packet comes in, if the value is within the bounds for a match, adds it to all possible matches, always adds it to database. 
void check_elo( Packet query )
{
  int q_elo = query.getElo();
  if (q_elo > ELO_LOWERBOUND && q_elo < ELO_UPPERBOUND)
  {
    //check if in last match
    
    //Add to my possible matches
    possible_matches.emplace_back(query.getIp(),q_elo); 
  }
  database_insert(database, query);
}  






bool check_matchfound()
{
  bool b = false;
  // tell all of the clients we found a match and await response
  // set a flag so incomming UDP connections know we're in a match
  // awaiting_reponse ? continue : ( matchfound ? b= true, continue : return false)
  // write database to file so we can remove it from the heap
  
  
  //check repsonse from match clients again
  // b ? return true : continue
  
  //return b

  return true; 
}

void send(uint x, uint lb, uint ub){}

void SYN()
{
  //send UDP packet
  send(MY_ELO, bounds.Lb, bounds.Ub);
}

//Run as soon as a packet comes in, returns all the values in it's database that are a possible match for the incomming packet. SYN-ACK refers to synchronize-acknowledgment in TCP handshake
map<int,IP> SYN_ACK(Packet q, uint lower_bound, uint upper_bound)
{
  map<int,IP> result = {};
  auto LBit = database.lower_bound(lower_bound);
  auto UBit = database.lower_bound(upper_bound);
  
  //return all the usefull values from our database. 
  std::copy(LBit, UBit, std::inserter(result, result.begin()));
  check_elo(q);
  
  return result;
}




int main(){
  

  
  cout<<"successfully compiled! 👍😁" << "\n";
}
  
