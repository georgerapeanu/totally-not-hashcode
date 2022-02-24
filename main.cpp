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

  string get_name()const{
    return name;
  }

  int get_level()const{
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
  int last_day_of_work;
  
public:

  Member(){
    name = "";
    skills = vector<Skill>();
    last_day_of_work = 0;
  }

  Member(string name, vector<Skill> skills){
    last_day_of_work = 0;
    this->name = name;
    this->skills = skills;
  }
  
  int get_last_day_of_work()const{
    return last_day_of_work;
  }

  void update_last_day_of_work(int day){
    last_day_of_work = day;
  }

  void read(){
    int skill_count;
    cin >> name >> skill_count;
    skills = vector<Skill>(skill_count, Skill());

    for(auto &skill:skills){
      skill.read();
    }
  }

  string get_name()const{
    return name;
  }

  vector<Skill> get_skills()const{
    return skills;
  }

  bool is_valid(){
    return name != "";
  }

  void update_skill_level_of(string skill_name, int level){
    for(auto it:skills){
      if(it.get_name() == skill_name){
        it.update_level(level);
      }
    }
  }

  int get_skill_level_of(string skill_name)const {
    for(auto it:skills){
      if(it.get_name() == skill_name){
        return it.get_level();
      }
    }
    return 0;
  }
  bool is_better(const Member &other, string name)const{
    if(other.get_skill_level_of(name) > this->get_skill_level_of(name)){
      return true;
    }
    long long sum = 0;
    for(auto skill:skills){
      sum += skill.get_level();
    }
    for(auto skill:other.get_skills()){
      sum -= skill.get_level();
    }
    return sum < 0;
  }
};

class Project{
  string name;
  int days_to_complete;
  int initial_score;
  int best_before_day;
  vector<Skill> roles;

  public:

  Project(){
    ;
  }

  Project(string name, int days_to_complete, int initial_score, int best_before_day, vector<Skill> roles){
    this->name = name;
    this->days_to_complete = days_to_complete;
    this->initial_score = initial_score;
    this->best_before_day = best_before_day;
    this->roles = roles;
  }

  void read(){
    int role_count;
    cin >> name >> days_to_complete >> initial_score >> best_before_day >> role_count;

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

  string get_name(){
    return name;
  }

  int get_score_at(int day){
    return max(0, initial_score - max(day - best_before_day, 0));
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

  int evaluate(){
    assert(this->is_valid());
    return project.get_score_at(this->get_last_day());
  }

  void run(){
    assert(this->is_valid());
    
    for(int i = 0;i < (int)p_members.size();i++){
      if(p_members[i]->get_skill_level_of(project.get_roles()[i].get_name()) <= project.get_roles()[i].get_level()){
        p_members[i]->update_skill_level_of(project.get_roles()[i].get_name(), project.get_roles()[i].get_level() + 1); 
        p_members[i]->update_last_day_of_work(this->get_last_day()); 
      }
    }
  }

  void write(){
    cout << project.get_name() << "\n";
    for(auto &member:p_members){
      cout << member->get_name() << " ";
    }
    cout << "\n";
  }
};

class AssignmentRepository{
  vector<AssignedProject> assignments;

  public:
  AssignmentRepository(){
    ;
  }
  
  AssignmentRepository(const vector<AssignedProject> &assignments){
    this->assignments = assignments;
  }

  long long total_score(){
    long long ans = 0;
    for(auto assignment:assignments){
      ans += assignment.evaluate();
      assignment.run();
    }
    return ans;
  }

  void write(){
    cout << (int)assignments.size() << "\n";
    for(auto assignment:assignments){
      assignment.write();
    }
  }
};

class MemberCollection{
  vector<Member*> p_members;

  public:

  MemberCollection(){
    ;
  }
  
  void push_back(Member* p_member){
    p_members.push_back(p_member);
  }

  vector<Member*> get_p_members(){
    return p_members;
  }

  bool has_by_name(string name){
    for(auto p_member:p_members){
      if(p_member->get_name() == name){
        return true;
      }
    }
    return false;
  }

  int get_best_skill_level(string name){
    int ans = 0;
    for(auto p_member:p_members){
      ans = max(ans, p_member->get_skill_level_of(name));
    }
    return ans;
  }
};

int main(){

  int n, m;

  cin >> n >> m;

  vector<Member> members(n, Member());
  vector<Project> projects(m, Project());

  for(auto &member:members){
    member.read();
  }
  
  for(auto &project:projects){
    project.read();
  }

  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  vector<AssignedProject> assignments;

  int current_day = 0;
  long long score = 0;

  while(projects.empty() == false){
    bool done_something = false;

    sort(projects.begin(), projects.end(), [&](Project &a, Project &b){
      return 1LL * a.get_score_at(current_day + a.get_days_to_complete()) * b.get_days_to_complete() < 
             1LL * b.get_score_at(current_day + b.get_days_to_complete()) * a.get_days_to_complete();
    });
    for(int plm_counter = 0;plm_counter < 5;plm_counter++){
      shuffle(members.begin(), members.end(), rng);
      for(int project_idx = 0;project_idx < (int)projects.size();project_idx++){
        vector<int> roles_order(projects[project_idx].get_roles().size(), 0);
        for(int i = 0;i < (int)roles_order.size();i++){
          roles_order[i] = i;
        }
        shuffle(roles_order.begin(),roles_order.end(), rng);
        MemberCollection collection;
        Project project = projects[project_idx];
        for(auto role_idx:roles_order){
          Member* p_best_member = NULL;
          for(auto &member:members){
            if(member.get_last_day_of_work() + 1 > current_day || collection.has_by_name(member.get_name())){
              continue;
            }
            if(project.get_roles()[role_idx].get_level() - 1 == member.get_skill_level_of(project.get_roles()[role_idx].get_name()) &&
               collection.get_best_skill_level(project.get_roles()[role_idx].get_name()) >= project.get_roles()[role_idx].get_level()){
                  if(p_best_member == NULL || member.is_better(*p_best_member, project.get_roles()[role_idx].get_name())){
                    p_best_member = &member;
                  }
               }else if(project.get_roles()[role_idx].get_level() >= member.get_skill_level_of(project.get_roles()[role_idx].get_name()) &&
                    (p_best_member == NULL || member.is_better(*p_best_member,project.get_roles()[role_idx].get_name()))){
                      p_best_member = &member;
                    }
          }
          if(p_best_member == NULL){
            break; 
          }
          collection.push_back(p_best_member);
        }
        if(collection.get_p_members().size() == roles_order.size()){
          AssignedProject assignment(current_day, projects[project_idx], collection.get_p_members());
          score += assignment.evaluate();
          assignment.run();
          done_something = true;
          assignments.push_back(assignment);
          swap(projects[project_idx], projects.back());
          projects.pop_back();
          break;
        }
      }
    }
    if(done_something == false){
      current_day++;
    }
  }

  fprintf(stderr, "score is %lld\n", score);
  AssignmentRepository repo(assignments);
  repo.write();

  return 0;
}
