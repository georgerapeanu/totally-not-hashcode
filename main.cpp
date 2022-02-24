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
  
  void update_level(int level){
    this->level = level;
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

  void update_skill_level_of(string skill_name, int level){
    for(auto it:skills){
      if(it.get_name() == skill_name){
        it.update_level(level);
      }
    }
  }

  int get_skill_level_of(string skill_name){
    for(auto it:skills){
      if(it.get_name() == skill_name){
        return it.get_level();
      }
    }
    return 0;
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

class AssignedProject{
  int start_day;
  Project project;
  vector<Member*> p_members; /// the members assigned in the order of the roles

  public:

  AssignedProject(){
    ;
  }

  AssignedProject(int start_day, Project project, vector<Member*> p_members){
    this->start_day = start_day;
    this->project = project;
    this->p_members = p_members;
  }

  bool is_valid(){
    map<string, int> best_level_for;
    if((int)p_members.size() == project.get_roles().size()){
      return false;
    }

    map<string, int> frequency_of_member;

    for(auto member:p_members){
      if(frequency_of_member.count(member->get_name()) != 0){
        return false;
      }
      frequency_of_member[member->get_name()] = 1;
      for(auto skill:member->get_skills()){
        if(best_level_for.count(skill.get_name()) == 0){
          best_level_for[skill.get_name()] = 0;
        }
        best_level_for[skill.get_name()] = max(best_level_for[skill.get_name()], skill.get_level());
      }
    }
    frequency_of_member.clear();

    for(int i = 0;i < (int)p_members.size();i++){
      int member_skill_level = p_members[i]->get_skill_level_of(project.get_roles()[i].get_name());
      if(member_skill_level < project.get_roles()[i].get_level() - 1){
        return false;
      }else if(member_skill_level == project.get_roles()[i].get_level() - 1){
        if(best_level_for[project.get_roles()[i].get_name()] < project.get_roles()[i].get_level()){
          return false;
        }
      }
    }
    return true;
  }

  int get_last_day(){
    assert(this->is_valid());
    return start_day + project.get_days_to_complete() - 1;
  }

  int evaluate_project(){
    assert(this->is_valid());
    return max(project.get_initial_score() - (this->get_last_day() - project.get_best_before_day()), 0);
  }

  void run(){
    assert(this->is_valid());
    
    for(int i = 0;i < (int)p_members.size();i++){
      if(p_members[i]->get_skill_level_of(project.get_roles()[i].get_name()) <= project.get_roles()[i].get_level()){
        p_members[i]->update_skill_level_of(project.get_roles()[i].get_name(), project.get_roles()[i].get_level() + 1); 
      }
    }
  }

};

int main(){
  return 0;
}
