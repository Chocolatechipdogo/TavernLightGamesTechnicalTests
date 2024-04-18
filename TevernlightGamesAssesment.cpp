//for all functions where given {} as well as the ends removed to look closer to a c++ functions as well 
//as adding the missing ; and function return types which for the releaseStorage function will be void 
//since it only  modifies a exisiting  object with no real need for anything else to be return.

//function meant to override any player value with -1 meaning its now available and inactive
void local releaseStorage(player){

player.setStorageValue(1000, -1);

return;
}


 // under the impression that the loggout function is meant to loggout a specific player not just 
 //the player at 1000 as well as have a error for if a player is still valued as -1 since 
 //you can't really have a negative of a person just 0 when they don't exist. Decided to make 
 //this function's return type be a bool due to the existing return True which gives the impression 
 //that bool is need to confirm if the player was logged out propperly.

//Int meant to represent the value of the player that is going to be logged out
int specificPlayer = 1000;

//function meant to log a player out based on there value which in this case is represented by specific player
bool onLogout(player, int specificPlayer){
//replaced the bellow commented out code to the one written to fix the hard coded 1000 as well as 
//overall if statement
//if player:getStorageValue(1000) == 1 then

//specific if meant to catch if player is already empty
if (player.sgetStorageValue(specificPlayer) <= -1){
    // I understand that this specific call of throw isn't anything specific but I was originally 
    //planning on using dynamic exception specification only to find out its a deprecated thing in c++ 
    //so to play it safe I wanted to at least throw something so that when the function is used else 
    //where a catch can be set up when this possible error may occur.
    throw -1;
    //end the function
    return false;
}
//edited else if that acts like logging out by calling release storage through a function unknown to me
else if (player.getStorageValue(specificPlayer) == 1){

addEvent(releaseStorage, specificPlayer, player);

}



return true;
}








//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// this method is supposed to print names of all guilds that have less than memberCount max members

void printSmallGuildNames(memberCount){

local selectGuildQuery = "SELECT name FROM guilds WHERE max_members < %d;";

local resultId = db.storeQuery(string.format(selectGuildQuery, memberCount));

local guildName = resultId.getString("name");

print(guildName)
}






//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Function for removing a member from a players party given the party leaders ID and the party members 
void do_sth_with_PlayerParty(int playerId, string membername){

//retrieving player data based on player ID. left the same because under the impression its a function
//that works in the player class other wise I would have been more inclined to set up the call
//like a vector due to the flexiablity of what can be stored in it as well as not being fixed.
player = Player(playerId);


//retreiving player's party information. again under the assumtion that getParty is a available function 
//in the player class
local party = player.getParty();
//retrieving the pairs in a format that works in c++ while still keeping the idea of a key an element
std::map<int, string> partyMembers = party.getMembers(); 
// meant to loop with the map in mind to retrive the element in the key element format
for(std::map<int, string>::iterator it = partyMembers.begin(); it != partyMembers.end(); ++it){

    //checks if current party member is the member that is being looked for
    if(it->secound == membername){

        //removes the member from the party with the assumption that removeMember is a function in the
        //party class
        party.removeMember(Player(membername)); 
    }
}


}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// assuming Game is meant to be the class that this function is meant to be for
void Game::addItemToPlayer(const std::string& recipient, uint16_t itemId)

{
//pointer to name based on recipient
Player* player = g_game.getPlayerByName(recipient);

//Checking if player exists else continue
if (*player.isEmpty()) {

player = new Player(nullptr);

if (!IOLoginData::loadPlayerByName(player, recipient)) {

return;

}

}
//pointer to item from itemId assuming its using function from Item class
Item* item = Item::CreateItem(itemId);
//checking if Item is a actual item else continue
if (item == 0) {
    //exit function
    return;

}

 
//assuming the funtion from g_game exists and attually assigns item retrieved
g_game.internalAddItem(player->getInbox(), item, INDEX_WHEREEVER, FLAG_NOLIMIT);

 

if (player->isOffline()) {

    IOLoginData::savePlayer(player);

}


//end the function
return;
}