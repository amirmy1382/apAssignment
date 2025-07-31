#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <string>
#include <cassert>
#include <exception>


using namespace std;

typedef array<int,2> Coordinate;
typedef array<const int,2> Direction;

Direction NORTH = {0,-1};
Direction SOUTH = {0,1};
Direction EAST = {1,0};
Direction WEST = {-1,0};

bool isDigit(const string str)
{
    return !str.empty() && str.find_first_not_of("0123456789") == string::npos;
}

class Area {

    public:

        enum Area_Type{RESEARCH,START,FINISH,REGULAR};
        Area_Type type;
        static const char R_CHAR = 'R';
        static const char S_CHAR = 'S';
        static const char F_CHAR = 'F';

    private:

        int power_usage;
        bool has_visited;

        static const int R_POWER = 2;
        static const int S_POWER = 3;
        static const int F_POWER = 1;
        static const int NOTSET_POWER = 0;


    public:

        Area(Area_Type _t):type(_t){

            has_visited = false;

            switch (type)
            {
            case Area_Type::RESEARCH:
                power_usage = R_POWER;
                break;
            case Area_Type::START:
                power_usage = S_POWER;
                break;
            case Area_Type::FINISH:
                power_usage = F_POWER;
                break;
            default:
                power_usage = NOTSET_POWER;
                break;
            }
            
        }
        Area(int _power):power_usage(_power){
            type = Area_Type::REGULAR;
            has_visited = false;
        }


        void setPower(int p){
            assert(isdigit(p));
            if(p > 0){
                power_usage = p;
            }else
            {
                power_usage = NOTSET_POWER;
            }
            
        }
        const int power(){return power_usage;}

        const bool isVisited(){return has_visited;}
        void Visit(){
            has_visited = true;
        }

        friend ostream& operator<<(ostream& os, const Area& obj);
};

ostream& operator<<(ostream& os, const Area& obj)
{
    switch (obj.type)
    {
    case Area::Area_Type::RESEARCH:
        os << Area::R_CHAR;
        break;
    case Area::Area_Type::START:
        os << Area::S_CHAR;
        break;
    case Area::Area_Type::FINISH:
        os << Area::F_CHAR;
        break;
    default:
        os << obj.power_usage;
        break;
    }
    return os;
}

class Robot
{
    private:
        int charge;
        int num_reasearch_visited;
        int num_reasearch_total;
    public:
        
        Robot(int _c, int _r){
            assert(_c > 0);
            assert(_r >= 0);
            charge = _c;
            num_reasearch_visited = 0;
            num_reasearch_total = _r;
        }
        bool canGoTo(Area a){                                           

            int leftover_charge = charge - a.power();

            return leftover_charge >= 0 ;
        }
       
        void moveTo(Area a){

            assert(canGoTo(a));
            charge -= a.power();
            if((a.type == Area::Area_Type::RESEARCH)){

                if(!a.isVisited()){

                    num_reasearch_visited++;
                    if(num_reasearch_visited > num_reasearch_total){throw logic_error("Something wrong in counting Researchs");}
                    a.Visit();
                }
            }
        }
        bool isOutOfCharge(){return charge <= 0;}
        bool isResearchDone(){
            assert(num_reasearch_visited <= num_reasearch_total);
            return num_reasearch_visited == num_reasearch_total;
        }
};

class Map
{
private:
    vector<vector<Area*>> elements;
    Coordinate start_cord;
    Coordinate finish_cord;
    int numOfReasearch;
    
public:
    int size;
    
    Map(){
        string line;
        vector<Area*> row;
        size = 0;
        bool at_first_row;
        bool has_one_start = false;
        bool has_one_finish = false;

        while (getline(cin, line))
        {
            if (line.empty()) {throw invalid_argument("Empty input line");}

            if (elements.size() == 0)
            {
                at_first_row = true;
            }

            stringstream ss(line);

            string input_string;
            while (ss >> input_string)
            {
                assert(input_string.size() == 1);

                Area* a;
                if(input_string[0] == Area::R_CHAR){
                    a = (Area*) new Area(Area::Area_Type::RESEARCH);
                    

                }else if (input_string[0] == Area::S_CHAR)
                {
                    a = (Area*) new Area(Area::Area_Type::START);

                    if(has_one_start){has_one_start = false;}
                    else{has_one_start = true;}

                }else if (input_string[0] == Area::F_CHAR)
                {
                    a = (Area*) new Area(Area::Area_Type::FINISH);

                    if(has_one_finish){has_one_finish = false;}
                    else{has_one_finish = true;}

                }else if (isDigit(input_string))
                {
                    if(stoi(input_string) <= 0) {throw invalid_argument("Battery usage must be positive and non zero");}

                    a = (Area*) new Area(stoi(input_string));
                }else
                {
                    throw invalid_argument("Invalid Character as input");
                }
                row.push_back(a);
            }
            assert(row.size() > 0);
            
            
            if (at_first_row)
            {
                size = row.size();
                at_first_row = false;
            } else
            {
                if (row.size() != size)
                {
                    throw invalid_argument("Row size inconsistant!");
                }
            }

            elements.push_back(row);
            row.clear();

            if (elements.size() == size) { 
                if (has_one_finish && has_one_start){
                    break;
                }else{
                    throw invalid_argument("Map must have one start and one finish");
                }
            }
        }
        assert(elements.size() == elements[0].size() && elements.size() > 0);

        for (int i=0;i<size;i++)
        {
            for (int j=0;j<size;j++)
            {
                if (elements[i][j]->type == Area::Area_Type::START)
                {
                    start_cord[0]=i;
                    start_cord[1]=j;
                }else if(elements[i][j]->type == Area::Area_Type::FINISH)
                {
                    finish_cord[0]=i;
                    finish_cord[1]=j;
                }else if(elements[i][j]->type == Area::Area_Type::RESEARCH)
                {
                    numOfReasearch++;
                }
            }
        }
    }
    
    int getNumOfResearchAreas(){return numOfReasearch;}
    
    bool cordIsValid(Coordinate c){
        if ((c[0] < 0 || c[0] > size-1)||
        (c[1] < 0 || c[1] > size-1))
        {
            return false;
        }else{ return true;}
    }
    
    Area* getArea(Coordinate c){
        assert(cordIsValid(c));
        return elements[c[0]][c[1]];
    }

    ~Map(){
        for (auto row : elements)
        {
            for (auto e : row)
            {
                delete e;
            }
        }
    }

    static Coordinate getNextCord(Coordinate current_cord, Direction direction){
        Coordinate next_cord;
        next_cord[0] = current_cord[0]+direction[0];
        next_cord[1] = current_cord[1]+direction[1];
    return next_cord;
}
};


/**/

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


int updateBattery(const Map& map, int current_battery_charge, Coordinate current_cord){
    int new_battery_charge = current_battery_charge;
    string element_at_there= map[current_cord[0]][current_cord[1]];

    if (isDigit(element_at_there))
    {
        new_battery_charge -= stoi(element_at_there);

    }else if (element_at_there == START_STR)
    {
        new_battery_charge -= S_POWER;

    }else if (element_at_there == RESEARCH_STR || element_at_there == VISITED_RESEARCH_STR)
    {
        new_battery_charge -= R_POWER;
    }
    return new_battery_charge;
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

     
    int new_battery_charge_after_step = updateBattery(map,remaining_battery_charge,next_cord);
    
    if( new_battery_charge_after_step < 0){
        hasInsufficientPower = true;
    }
    
    return !hasInsufficientPower && !isOutOfBound;
}

void findAllRoutes(Map& map, int remaining_battery_charge, Coordinate current_cord, Coordinate finish_cord, int& route_count){



    Coordinate next_cord;
    array<Direction, 4> directions = {NORTH, EAST, SOUTH, WEST};

    
    int new_battery_charge = updateBattery(map,remaining_battery_charge,current_cord);
    
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


*/



int main() {

    int battery_charge = 0;
    cin >> battery_charge;
    cin.ignore(); // becuase of the leftover \n by cin
    if(battery_charge <= 0){throw invalid_argument("Invalid initial Battry Charge");}

    Map map;
    Robot roby(battery_charge, map.getNumOfResearchAreas());
    

    int route_count=0;

    // findAllRoutes(map,battery_charge,start_cord,finish_cord,route_count);


    cout << route_count << endl;

    // for (auto row : map)
    // {
    //     for (auto e : row)
    //     {
    //         cout << e <<' ';
    //     }
    //     cout << endl;
    // }
    

    return 0;

}
