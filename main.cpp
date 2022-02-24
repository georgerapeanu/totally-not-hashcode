#include <bits/stdc++.h>

using namespace std;

class Skill{
  string name;
  int level;

  public:

  Skill(){
    name = "";
    level = 0;
  }

  Skill(string name, int level){
    this->name = name;
    this->level = level;
  }

  string get_name(){
    return name;
  }

  int get_level(){
    return level;
  }

  void read(){
    cin >> name;
    cin >> level;
  }
};

class Member{
  string name;
  vector<Skill> skills;
  
public:

  Member(){
    name = "";
    skills = vector<Skill>();
  }

  Member(string name, vector<Skill> skills){
    this->name = name;
    this->skills = skills;
  }

  void read(){
    int skill_count;
    cin >> name >> skill_count;
    skills = vector<Skill>(skill_count, Skill());

    for(auto &skill:skills){
      skill.read();
    }
  }

  string get_name(){
    return name;
  }

  vector<Skill> get_skills(){
    return skills;
  }
};

class Project{
  int days_to_complete;
  int initial_score;
  int best_before_day;
  vector<Skill> roles;

  public:

  Project(){
    ;
  }

  Project(int days_to_complete, int initial_score, int best_before_day, vector<Skill> roles){
    this->days_to_complete = days_to_complete;
    this->initial_score = initial_score;
    this->best_before_day = best_before_day;
    this->roles = roles;
  }

  void read(){
    int role_count;
    cin >> days_to_complete >> initial_score >> best_before_day >> role_count;

    roles = vector<Skill>(role_count, Skill());

    for(auto &role:roles){
      role.read();
    }
  }
  
  int get_days_to_complete(){
    return days_to_complete;
  }

  int get_initial_score(){
    return initial_score;
  }
  
  int get_best_before_day(){
    return best_before_day; 
  }

  vector<Skill> get_roles(){
    return roles;
  }
};

int main(){
  return 0;
}
