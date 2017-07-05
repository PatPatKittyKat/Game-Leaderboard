/* Anthony Cooper - CSCE 315 - Fall 2016 - Individual Assignment 1*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <iomanip>			//IO manipulators [for setw()]
#include <map>				//for VictoryRanking
using namespace std;

//-----------------------------------
//            STRUCTS
//-----------------------------------

struct Victory {
	int ID;
	string Name;
	int Points;
};

struct Game {
	int ID;
	string Name;
	unordered_map<int,Victory> victoryMap;
};

struct Player {
	int ID;
	string Name;
	vector<Player> friends;
	unordered_map<int,string> games;
	vector<int> victories;
};

//-----------------------------------
//            GLOBALS
//-----------------------------------

unordered_map<int,Game> gameMap;
unordered_map<int,Player> playerMap;

//-----------------------------------
//           FUNCTIONS
//-----------------------------------

void AddGame(int gameID, string gameName){
	//cout << gameID << " " << gameName << endl;
	Game g;
	g.ID = gameID;
	g.Name = gameName;
	gameMap.insert({g.ID, g});
	//gameList.push_back(g);
}

void AddVictory(int gameID, int victoryID, string victoryName, int victoryPoints){
	Victory v;
	v.ID = victoryID;
	v.Name = victoryName;
	v.Points = victoryPoints;
	//http://en.cppreference.com/w/cpp/container/unordered_map/find
	//auto temp = gameMap.find(gameID);
	((gameMap.find(gameID))->second).victoryMap.insert({v.ID,v});
	
	/*	//testing syntax
	Game g = temp->second;
	g.victoryMap.find(victoryID);
	cout << ((g.victoryMap.find(victoryID))->second).Name << endl;
	*/
	
	/*	SUCCESS: the 3 lines below print:
	the name of the game being accessed and
	the name of the victory that was added to the game's victoryMap
	the point-value
	*/
	//cout << ((gameMap.find(gameID))->second).Name << ": ";
	//cout << ((((gameMap.find(gameID))->second).victoryMap.find(victoryID))->second).Name;
	//cout << " -- " << ((gameMap.find(gameID)->second.victoryMap.find(victoryID))->second).Points << endl;
}

void AddPlayer(int playerID, string playerName){
	Player p;
	p.ID = playerID;
	p.Name = playerName;
	playerMap.insert({p.ID,p});
	/*	//accessing player's name through playerMap
	auto temp = playerMap.find(playerID);
	cout << (temp->second).Name << endl;
	*/
}

void AddFriends(int player1ID, int player2ID){	
	/*
	auto temp = playerMap.find(player1ID);
	auto temp1 = playerMap.find(player2ID);
	Player p = temp->second;
	Player p1 = temp1->second;
	*/
	(((playerMap.find(player1ID))->second).friends).push_back(
		(playerMap.find(player2ID))->second);
	(((playerMap.find(player2ID))->second).friends).push_back(
		(playerMap.find(player1ID))->second);
	
}

void Plays(int playerID, int gameID, string ign){
	/*auto temp = playerMap.find(playerID);
	auto temp1 = gameMap.find(gameID);
	Player p = temp->second;
	*/
	((playerMap.find(playerID))->second).games.insert({gameID,ign});
	/*cout << ((playerMap.find(playerID))->second).Name << " plays: " <<
		(gameMap.find(gameID)->second).Name << endl;
	*/
}

void WinVictory(int playerID, int gameID, int victoryID){
	//cout << playerID << " " << gameID << " " << victoryID << endl;
	
	/*[FROM EXAMPLE INPUT FILE]: all victories have separate victoryIDs, so
	there is no need to specify the gameID under this assumption.
	*/
	
	//add victoryID to player's victories vector
	(playerMap.find(playerID)->second).victories.push_back(victoryID);
}

void SummarizePlayer(int playerID){
	string name = (playerMap.find(playerID)->second).Name;
	int gamerScore = 0;
	int tempVictoryID;
	
	int victoryNum = 0;
	int totalVictoriesPossible = 0;
	int tempVictoryScore = 0;
	string ign;
	
	//-----------------------------Calculating Total GamerScore-----------------------------
	//iterating through games the player plays
	for (auto i=(playerMap.find(playerID)->second).games.begin();
	i!=(playerMap.find(playerID)->second).games.end(); ++i){
		
		//iterating through the victories the player has
		for(int j=0; j<(playerMap.find(playerID)->second).victories.size(); ++j){
			tempVictoryID = 0;
			//cout << (playerMap.find(playerID)->second).victories.at(j) << endl;	//victoryID that the player has
			tempVictoryID = (playerMap.find(playerID)->second).victories.at(j);
			//cout << i->first << endl;	//the gameID for which victories are being looked up
			
			//searching victories possible for the game
			for(auto k=(gameMap.find(i->first)->second).victoryMap.begin();
			k!=(gameMap.find(i->first)->second).victoryMap.end(); ++k){
				
				//increases total gamerScore for matching victories
				if (tempVictoryID==k->first){
					//prints points gained for each matching victory
					//cout << "Points gained: " << (gameMap.find(i->first)->second).victoryMap.find(k->first)->second.Points << endl;
					gamerScore += (gameMap.find(i->first)->second).victoryMap.find(k->first)->second.Points;
				}
			}
			
		}
		//cout << endl;
	}
	//-----------------------------Done Calculating GamerScore-----------------------------
	
	cout << "Player: " << name << endl;
	cout << "Total Gamerscore: " << gamerScore << endl;
	cout << endl;
	cout << setw(20) << left << "Game" << setw(12) << left << "Victories"
		 << setw(15) << left << "Gamerscore" << setw(1) << left << " IGN" << endl;
	cout << "----------------------------------------------------------------------" << endl;
	for (auto i=(playerMap.find(playerID)->second).games.begin();
	i!=(playerMap.find(playerID)->second).games.end(); ++i){
		
		//print the name of the game played
		cout << setw(20) << left << (gameMap.find(i->first)->second).Name;
		victoryNum=0;
		tempVictoryScore=0;
		ign = i->second;
		
		//print the number of victories the player has for this game
		
		//------------PASTED AND EDITED FROM TOTALGAMERSCORE CODE ABOVE-------------
		//iterating through the victories the player has
		for(int j=0; j<(playerMap.find(playerID)->second).victories.size(); ++j){
			tempVictoryID = 0;
			//cout << (playerMap.find(playerID)->second).victories.at(j) << endl;	//victoryID that the player has
			tempVictoryID = (playerMap.find(playerID)->second).victories.at(j);
			//cout << i->first << endl;	//the gameID for which victories are being looked up
			
			totalVictoriesPossible=0;
			
			//searching victories possible for the game
			for(auto k=(gameMap.find(i->first)->second).victoryMap.begin();
			k!=(gameMap.find(i->first)->second).victoryMap.end(); ++k){
				
				//increases total gamerScore for matching victories
				if (tempVictoryID==k->first){
					//prints points gained for each matching victory
					//cout << "Points gained: " << (gameMap.find(i->first)->second).victoryMap.find(k->first)->second.Points << endl;
					//gamerScore += (gameMap.find(i->first)->second).victoryMap.find(k->first)->second.Points;
					++victoryNum;
					tempVictoryScore+=(gameMap.find(i->first)->second).victoryMap.find(k->first)->second.Points;
				}
				++totalVictoriesPossible;
			}
			
		}
		//----------------------------------------------------------
		cout << victoryNum << "/" << totalVictoriesPossible;
		cout << "\t\t" << tempVictoryScore << "\t\t" << ign << endl;
		
		
		
	}
	
	cout << endl;
	cout << setw(20) << left << "Friend" << setw(10) << left << "Gamerscore" << endl;
	cout << "--------------------------------------" << endl;
	
	for(int i=0; i<(playerMap.find(playerID)->second).friends.size(); ++i) {
		auto temp = playerMap.find(playerID)->second;
		cout << setw(20) << left << temp.friends.at(i).Name;
		
		//calculate friend's gamerscore
		int temp1 = temp.friends.at(i).ID;
		gamerScore = 0;
		
		//------------PASTED AND EDITED FROM TOTALGAMERSCORE CODE ABOVE-------------
		for (auto j=(playerMap.find(temp1)->second).games.begin();
		j!=(playerMap.find(temp1)->second).games.end(); ++j){
			
			
			//iterating through the victories the player has
			for(int k=0; k<(playerMap.find(temp1)->second).victories.size(); ++k){
				tempVictoryID = 0;
				//cout << (playerMap.find(temp1)->second).victories.at(k) << endl;	//victoryID that the player has
				tempVictoryID = (playerMap.find(temp1)->second).victories.at(k);
				//cout << j->first << endl;	//the gameID for which victories are being looked up
				
				//searching victories possible for the game
				for(auto l=(gameMap.find(j->first)->second).victoryMap.begin();
				l!=(gameMap.find(j->first)->second).victoryMap.end(); ++l){
					
					//increases total gamerScore for matching victories
					if (tempVictoryID==l->first){
						//prints points gained for each matching victory
						//cout << "Points gained: " << (gameMap.find(j->first)->second).victoryMap.find(l->first)->second.Points << endl;
						gamerScore += (gameMap.find(j->first)->second).victoryMap.find(l->first)->second.Points;
					}
				}
				
			}
			//cout << endl;
		}
		//----------------------------------------------------------
		cout << gamerScore << endl;
	}
	
	cout << endl << endl;
}

void FriendsWhoPlay(int playerID, int gameID){
	
	cout << "Friends Who Play: " << (gameMap.find(gameID)->second).Name << endl;
	cout << "----------------------------" << endl;
	
	for(int i=0; i<(playerMap.find(playerID)->second).friends.size(); ++i) {
		auto temp=(playerMap.find(playerID))->second;
		cout << temp.friends.at(i).Name << endl; 
	}
	
}

void ComparePlayers(int player1ID, int player2ID, int gameID){
	int tempVictoryID 		   = 0;
	int gamerScore 			   = 0;
	int totalVictoriesPossible = 0;
	int victoryNum			   = 0;
	int tempVictoryScore	   = 0;
	
	cout << endl;
	
	cout << "Comparing Players for: " << gameMap.find(gameID)->second.Name << endl;
	cout << "------------------------------------" << endl;
	//showing player1's record
	for(int j=0; j<(playerMap.find(player1ID)->second).victories.size(); ++j){
		tempVictoryID = 0;
		tempVictoryID = (playerMap.find(player1ID)->second).victories.at(j);
		totalVictoriesPossible=0;
		
		//searching victories possible for the game
		for(auto k=(gameMap.find(gameID)->second).victoryMap.begin();
		k!=(gameMap.find(gameID)->second).victoryMap.end(); ++k){
			
			//increases total gamerScore for matching victories
			if (tempVictoryID==k->first){
				++victoryNum;
				tempVictoryScore+=(gameMap.find(gameID)->second).victoryMap.find(k->first)->second.Points;
			}
			++totalVictoriesPossible;
		}
		
	}
	
	cout << playerMap.find(player1ID)->second.Name << "'s record: " << endl;
	cout << "------------------------------------" << endl;
	cout << "Victory Record: " << victoryNum << "/" << totalVictoriesPossible << endl;
	cout << "Gamerscore: " << tempVictoryScore << endl << endl;
	
	//showing player2's record
	gamerScore = 0;
	victoryNum = 0;
	tempVictoryScore = 0;
	
	for(int j=0; j<(playerMap.find(player2ID)->second).victories.size(); ++j){
		tempVictoryID = 0;
		tempVictoryID = (playerMap.find(player2ID)->second).victories.at(j);
		totalVictoriesPossible=0;
		
		//searching victories possible for the game
		for(auto k=(gameMap.find(gameID)->second).victoryMap.begin();
		k!=(gameMap.find(gameID)->second).victoryMap.end(); ++k){
			
			//increases total gamerScore for matching victories
			if (tempVictoryID==k->first){
				++victoryNum;
				tempVictoryScore+=(gameMap.find(gameID)->second).victoryMap.find(k->first)->second.Points;
			}
			++totalVictoriesPossible;
		}
		
	}
	
	cout << "------------------------------------" << endl;
	cout << playerMap.find(player2ID)->second.Name << "'s record: " << endl;
	cout << "------------------------------------" << endl;
	cout << "Victory Record: " << victoryNum << "/" << totalVictoriesPossible << endl;
	cout << "Gamerscore: " << tempVictoryScore << endl;
	
	
	cout << endl;
}

void VictoryRanking() {
	map<int,string> victoryRanking;
	
	int gamerScore = 0;
	int tempVictoryID;
	
	cout << "Victory Ranking" << endl;
	cout << "---------------------------------------" << endl;
	cout << setw(10) << left << "Points" << setw(10) << left << "Player" << endl;
	cout << "---------------------------------------" << endl;
	
	for (auto g=playerMap.begin(); g!=playerMap.end(); ++g){
		int playerID = g->first;
		gamerScore = 0;
		
		//cout << playerID << endl;
		
		for (auto i=(playerMap.find(playerID)->second).games.begin();
		i!=(playerMap.find(playerID)->second).games.end(); ++i){
			
			//iterating through the victories the player has
			for(int j=0; j<(playerMap.find(playerID)->second).victories.size(); ++j){
				tempVictoryID = 0;
				//cout << (playerMap.find(playerID)->second).victories.at(j) << endl;	//victoryID that the player has
				tempVictoryID = (playerMap.find(playerID)->second).victories.at(j);
				//cout << i->first << endl;	//the gameID for which victories are being looked up
				
				//searching victories possible for the game
				for(auto k=(gameMap.find(i->first)->second).victoryMap.begin();
				k!=(gameMap.find(i->first)->second).victoryMap.end(); ++k){
					
					//increases total gamerScore for matching victories
					if (tempVictoryID==k->first){
						//prints points gained for each matching victory
						//cout << "Points gained: " << (gameMap.find(i->first)->second).victoryMap.find(k->first)->second.Points << endl;
						gamerScore += (gameMap.find(i->first)->second).victoryMap.find(k->first)->second.Points;
					}
				}
				
			}
			//cout << endl;
		}
		//cout << setw(10) << left << gamerScore << playerMap.find(playerID)->second.Name << endl;
		victoryRanking.insert({gamerScore,playerMap.find(playerID)->second.Name});
				
	}
		//printing map of victoryRanking in reverse order: http://www.cplusplus.com/reference/map/map/rend/
		for (auto i=victoryRanking.rbegin(); i!=victoryRanking.rend(); ++i){
			cout << setw(10) << left << i->first << i->second << endl;
		}
}

//-----------------------------------
//            MAIN
//-----------------------------------

int main() {
	string s,s2;								//input strings
	int x,y,z;									//input int values
	//unordered_map<int, string> gameMap;
	cout << endl;
	
	while(cin.good()) {
		getline(cin >> std::ws ,s);	//https://piazza.com/class/isgz5z49v5p57c?cid=25
		
		if (s.substr(0,s.find(' '))=="AddGame"){
			//cout << s.substr(8,s.find(' ')-3) << endl; //this line works for 4-digit gameID only
			s = s.substr(s.find(' ')+1);
			x = stoi(s.substr(0,s.find(' ')));			//x=gameID
			s = s.substr(s.find(' ')+2);				
			s = s.substr(0,s.find('\"'));				//s=gameName
			//cout << x << " " << s << endl;
			AddGame(x,s);
		}
		else if (s.substr(0,s.find(' '))=="AddVictory"){
			s = s.substr(s.find(' ')+1);
			x = stoi(s.substr(0,s.find(' ')));			//x=gameID
			s = s.substr(s.find(' ')+1);
			y = stoi(s.substr(0,s.find(' ')));			//y=victoryID
			s = s.substr(s.find(' ')+2);
			s2 = s.substr(0,s.find('\"'));				//s2=gameName
			s = s.substr(s.find('\"')+2);
			z = stoi(s);								//z=victoryPoints
			//cout << x << " " << y << " " << s2 << " " << z << endl;
			AddVictory(x,y,s2,z);
		}
		else if (s.substr(0,s.find(' '))=="AddPlayer"){
			s = s.substr(s.find(' ')+1);
			x = stoi(s.substr(0,s.find(' ')));			//x=playerID
			s = s.substr(s.find(' ')+2);
			s = s.substr(0,s.find('\"'));				//s=playerName
			//cout << x << " " << s << endl;
			AddPlayer(x,s);
		}
		else if (s.substr(0,s.find(' '))=="AddFriends"){
			s = s.substr(s.find(' ')+1);
			x = stoi(s.substr(0,s.find(' ')));			//x=playerID 1
			s = s.substr(s.find(' ')+1);
			y = stoi(s);								//y=playerID 2
			//cout << x << " " << y << endl;
			AddFriends(x,y);
		}
		else if (s.substr(0,s.find(' '))=="Plays"){
			s = s.substr(s.find(' ')+1);
			x = stoi(s.substr(0,s.find(' ')));			//x=playerID
			s = s.substr(s.find(' ')+1);
			y = stoi(s.substr(0,s.find(' ')));			//y=gameID
			s = s.substr(s.find(' ')+2);
			s = s.substr(0,s.find('\"'));				//s=IGN
			//cout << x << " " << y << " " << s << endl;
			Plays(x,y,s);
		}
		else if (s.substr(0,s.find(' '))=="WinVictory"){
			//<playerID><gameID><victoryID>
			s = s.substr(s.find(' ')+1);
			x = stoi(s.substr(0,s.find(' ')));			//x=playerID
			s = s.substr(s.find(' ')+1);
			y = stoi(s.substr(0,s.find(' ')));			//y=gameID
			s = s.substr(s.find(' ')+1);
			z = stoi(s);								//z=victoryID
			//cout << x << " " << y << " " << z << endl;
			WinVictory(x,y,z);
		}
		else if (s.substr(0,s.find(' '))=="FriendsWhoPlay"){
			s = s.substr(s.find(' ')+1);
			x = stoi(s.substr(0,s.find(' ')));			//x=playerID
			s = s.substr(s.find(' ')+1);
			y = stoi(s);								//y=gameID
			//cout << x << " " << y << endl;
			FriendsWhoPlay(x,y);
		}
		else if (s.substr(0,s.find(' '))=="ComparePlayers"){
			s = s.substr(s.find(' ')+1);
			x = stoi(s.substr(0,s.find(' ')));			//x=playerID 1
			s = s.substr(s.find(' ')+1);
			y = stoi(s.substr(0,s.find(' ')));			//y=playerID 2
			s = s.substr(s.find(' ')+1);
			z = stoi(s);								//z=gameID
			//cout << x << " " << y << " " << z << endl;
			ComparePlayers(x,y,z);
		}
		else if (s.substr(0,s.find(' '))=="SummarizePlayer") {
			s = s.substr(s.find(' ')+1);
			x = stoi(s);								//x=playerID
			//cout << x << endl;
			SummarizePlayer(x);
		}
		else if (s.substr(0,s.find(' '))=="SummarizeGame")
			cout << "SummarizeGame" << endl;
		else if (s.substr(0,s.find(' '))=="SummarizeVictory")
			cout << "SummarizeVictory" << endl;
		else if (s=="VictoryRanking"){
			VictoryRanking();
		}
		else
			cout << s << endl;
	}
	
	//TESTING: making sure playerMap is updated with friends
	/*
	for (int i=0; i<((playerMap.find(40001)->second).friends).size(); ++i)
		cout << (playerMap.find(40001)->second).Name << "'s friend: " << ((playerMap.find(40001)->second).friends.at(i)).Name << endl;
	*/
	
	//TESTING: making sure player's played games is accessible
	
	/*
	for (int i=0; i<((playerMap.find(40001)->second).games).size(); ++i){
		cout << ((playerMap.find(40001)->second).Name) << " plays: " << endl;
	}
	for (int i=0; i<((playerMap.find(40002)->second).games).size(); ++i){
		cout << ((playerMap.find(40002)->second).Name) << " plays: " << endl;
	}
	for (int i=0; i<((playerMap.find(40003)->second).games).size(); ++i){
		cout << ((playerMap.find(40003)->second).Name) << " plays: " << endl;
	}
	for (int i=0; i<((playerMap.find(40004)->second).games).size(); ++i){
		cout << ((playerMap.find(40004)->second).Name) << " plays: " << endl;
	}
	for (int i=0; i<((playerMap.find(40005)->second).games).size(); ++i){
		cout << ((playerMap.find(40005)->second).Name) << " plays: " << endl;
	}
	*/
	
	//TESTING: prints gameIDs and IGNs for player 40001's played games
	/*
	for (auto i = ((playerMap.find(40001))->second).games.begin(); i != ((playerMap.find(40001))->second).games.end(); ++i)
		cout << i->first << " : " << i->second << endl;
	*/
	
	cout << endl << "PROGRAM TERMINATED SUCCESSFULLY" << endl;
}