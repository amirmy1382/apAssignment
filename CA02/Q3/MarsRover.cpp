#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <string>
#include <cassert>
#include <exception>


using namespace std;

typedef array<const int,2> Direction;
typedef array<int,2> Coordinate;
typedef vector<vector<string>> Map;

Direction NORTH = {0,-1};
Direction SOUTH = {0,1};
Direction EAST = {1,0};
Direction WEST = {-1,0};

const string START_STR{"S"};
const string FINISH_STR{"F"};
const string RESEARCH_STR{"R"};
const string VISITED_RESEARCH_STR{"V"};

const int RESEARCH_AREA_POWER_USAGE = 3;
const int START_AREA_POWER_USAGE = 3;

void fillMap(Map& map)
{
    string line;
    vector<string> row;
    int board_size = 0;
    bool at_first_row;

    while (getline(cin, line))
    {
        if (line.empty()) { continue; }

        if (map.size() == 0)
        {
            at_first_row = true;
        }

        stringstream ss(line);

        string element;
        while (ss >> element)
        {
            row.push_back(element);
        }

        if (at_first_row)
        {
            board_size = row.size();
        } else
        {
            if (row.size() != board_size)
            {
                throw invalid_argument("Row size inconsistant!");
            }
        }

        map.push_back(row);
        row.clear();



        assert(board_size > 0);
        if (map.size() == board_size) { break; }
    }
    assert(map.size() == map[0].size() && map.size() > 0);
}

void findStartAndFinish(const Map& map, Coordinate& start_cord, Coordinate& finish_cord){


    for (int i=0;i<map.size();i++)
    {
        for (int j=0;j<map[i].size();j++)
        {
            if (map[i][j] == START_STR)
            {
                start_cord[0]=i;
                start_cord[1]=j;
            }else if(map[i][j] == FINISH_STR)
            {
                finish_cord[0]=i;
                finish_cord[1]=j;
            }
        }
    }
}

bool isRouteEnded(const Map& map, Coordinate current_cord, Coordinate finish_cord){

    bool isAtFinishCord = current_cord == finish_cord;
    int allReasurchAreasReached = true;

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if ( map[i][j] == RESEARCH_STR)
            {
                allReasurchAreasReached = false;
                break;
            }
        }
        if (allReasurchAreasReached == false){ break;}
    }
    
    return isAtFinishCord && allReasurchAreasReached;
}

bool is_digit(const string str)
{
    return !str.empty() && str.find_first_not_of("0123456789") == string::npos;
}

int update_battery(const Map& map, int current_battery_charge, Coordinate current_cord){
    int new_battery_charge = current_battery_charge;
    string element_at_there= map[current_cord[0]][current_cord[1]];

    if (is_digit(element_at_there))
    {
        new_battery_charge -= stoi(element_at_there);

    }else if (element_at_there == START_STR)
    {
        new_battery_charge -= START_AREA_POWER_USAGE;

    }else if (element_at_there == RESEARCH_STR || element_at_there == VISITED_RESEARCH_STR)
    {
        new_battery_charge -= RESEARCH_AREA_POWER_USAGE;
    }
    return new_battery_charge;
}

Coordinate getNextCord(Coordinate current_cord, Direction direction){
    Coordinate next_cord;
    next_cord[0] = current_cord[0]+direction[0];
    next_cord[1] = current_cord[1]+direction[1];
    return next_cord;
}

bool canIGoThere(const Map& map, int remaining_battery_charge, Coordinate current_cord, Direction direction)
{
    Coordinate next_cord = getNextCord(current_cord, direction);

    bool isOutOfBound = false;
    bool hasInsufficientPower = false;

    if ((next_cord[0] < 0 || next_cord[0] > map.size()-1)||
        (next_cord[1] < 0 || next_cord[1] > map[next_cord[0]].size()-1))
        {
            isOutOfBound = true;
        }

     
    int new_battery_charge_after_step = update_battery(map,remaining_battery_charge,next_cord);
    
    if( new_battery_charge_after_step < 0){
        hasInsufficientPower = true;
    }
    
    return !hasInsufficientPower && !isOutOfBound;
}

void findAllRoutes(Map& map, int remaining_battery_charge, Coordinate current_cord, Coordinate finish_cord, int& route_count){



    Coordinate next_cord;
    array<Direction, 4> directions = {NORTH, EAST, SOUTH, WEST};

    
    int new_battery_charge = update_battery(map,remaining_battery_charge,current_cord);
    
    bool visited_research_here = false;
    if(map[current_cord[0]][current_cord[1]] == RESEARCH_STR){
        map[current_cord[0]][current_cord[1]] = VISITED_RESEARCH_STR;
        visited_research_here = true;
    }

    for (auto dir : directions)
    {

        if(!canIGoThere(map, new_battery_charge, current_cord, dir)){continue;}

        next_cord = getNextCord(current_cord, dir);

        if(isRouteEnded(map,next_cord,finish_cord)){
            route_count++;
        }else{
            
            findAllRoutes(map,new_battery_charge,next_cord,finish_cord,route_count);
        }
    }
    if (visited_research_here) {
        map[current_cord[0]][current_cord[1]] = RESEARCH_STR; // backtrack
    }
    
}




int main() {

    int battery_charge = 0;
    cin >> battery_charge;
    cin.ignore(); // becuase of the leftover \n by cin

    Map map;

    fillMap(map);



    Coordinate start_cord,finish_cord;

    findStartAndFinish(map, start_cord,finish_cord);


    int route_count=0;

    findAllRoutes(map,battery_charge,start_cord,finish_cord,route_count);


    cout << route_count << endl;
    for (auto row : map)
    {
        for (auto e : row)
        {
            cout << e<<' ';
        }
        cout << endl;
    }
    

    return 0;

}
