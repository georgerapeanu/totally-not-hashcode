#include <bits/stdc++.h>

using namespace std;

const int INF = (int)1e9 + 10;

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

  string get_name() const {
    return name;
  }

  int get_level() const {
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

  string get_name() const {
    return name;
  }

  vector<Skill> get_skills() const {
    return skills;
  }

  bool has_skill_in_range(const string &skill_name, int min_level, int max_level) const {
    for (auto skill : skills) {
      if (skill.get_name() == skill_name && min_level <= skill.get_level() && skill.get_level() <= max_level) {
        return true;
      }
    }
    return false;
  }

  bool operator<(const Member &other) const {
    return name < other.get_name();
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

pair<vector<Member>, vector<Project>> ReadInput() {
  int n, m; cin >> n >> m;
  vector<Member> members;
  for (int i = 0; i < n; ++i) {
    Member member;
    member.read();
    members.emplace_back(member);

    /*
    string name; cin >> name;
    int skill_cnt; cin >> skill_cnt;
    vector<Skill> skills;
    while (skill_cnt--) {
      string skill_name; cin >> skill_name;
      int skill_level; cin >> skill_level;
      skills.emplace_back(skill_name, skill_level);
    }
    members.emplace_back(name, skills);
    */
  }

  vector<Project> projects;
  for (int i = 0; i < m; ++i) {
    Project project;
    project.read();
    projects.emplace_back(project);
    /*
    string name; cin >> name;
    int days_to_complete; cin >> days_to_complete;
    int initial_score; cin >> initial_score;
    int best_before_day; cin >> best_before_day;
    int cnt_roles; cin >> cnt_roles;
    vector<Skill> roles;
    while (cnt_roles--) {
      string skill_name; cin >> skill_name;
      int skill_level; cin >> skill_level;
      roles.emplace_back(skill_name, skill_level);
    }
    projects.emplace_back(days_to_complete, initial_score, best_before_day, roles);
    */
  }
  return {members, projects};
}

const double PROB = 0.8;

vector<Member> GetMembersWithSkillInRange(
  string skill_name, int min_level, int max_level, const set<Member> members) {
  vector<Member> ret;
  for (auto member : members) {
    if (member.has_skill_in_range(skill_name, min_level, max_level)) {
      ret.emplace_back(member);
    }
  }
  return ret;
}

void Solve(vector<Member> members, vector<Project> projects) {
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  shuffle(projects.begin(), projects.end(), rng);
  for (int project_it = 0; project_it < (int)projects.size(); ++project_it) {
    set<Member> available(members.begin(), members.end());
    bool done = false;
    while (!done) {
      shuffle(project.get_roles().begin(), project.get_roles().end(), rng); 
      for (auto skill : project.get_roles()) {
        auto candidates = GetMembersWithSkillInRange(
          skill.get_name(), skill.get_level(), INF, available
        );
        auto second_best = GetMembersWithSkillInRange(
          skill.get_name(), skill.get_level() - 1, skill.get_level() - 1, available
        );

        bool is_second_best_ok = false;
        for (int i = 0; i < project_it; ++i) {
        }
      }

      done = true;
    }
  }
}

int main(){
  vector<Member> members;
  vector<Project> projects;
  tie(members, projects) = ReadInput();
  Solve(members, projects);
}
