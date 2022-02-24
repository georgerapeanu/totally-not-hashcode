#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<string, int> LastTime;
map<string, string> Name;

class Skill
{
    string name;
    int level;

public:
    Skill()
    {
        name = "";
        level = 0;
    }

    Skill(string name, int level)
    {
        this->name = name;
        this->level = level;
    }

    string get_name()
    {
        return name;
    }

    int get_level()
    {
        return level;
    }

    void read()
    {
        cin >> name;
        cin >> level;
    }
};

class Member
{
    string name;
    vector<Skill> skills;

public:
    Member()
    {
        name = "";
        skills = vector<Skill>();
    }

    Member(string name, vector<Skill> skills)
    {
        this->name = name;
        this->skills = skills;
    }

    void read()
    {
        int skill_count;
        cin >> name >> skill_count;
        skills = vector<Skill>(skill_count, Skill());

        for (auto &skill : skills)
        {
            skill.read();
        }
    }

    string get_name()
    {
        return name;
    }

    vector<Skill> get_skills()
    {
        return skills;
    }
};

class Project
{
    string name;
    int days_to_complete;
    int initial_score;
    int best_before_day;
    vector<Skill> roles;

public:
    Project()
    {
        ;
    }

    Project(string name, int days_to_complete, int initial_score, int best_before_day, vector<Skill> roles)
    {
        this->name = name;
        this->days_to_complete = days_to_complete;
        this->initial_score = initial_score;
        this->best_before_day = best_before_day;
        this->roles = roles;
    }

    void read()
    {
        int role_count;
        cin >> name >> days_to_complete >> initial_score >> best_before_day >> role_count;

        roles = vector<Skill>(role_count, Skill());

        for (auto &role : roles)
        {
            role.read();
        }
    }

    string get_name()
    {
        return name;
    }

    int get_days_to_complete()
    {
        return days_to_complete;
    }

    int get_initial_score()
    {
        return initial_score;
    }

    int get_best_before_day()
    {
        return best_before_day;
    }

    vector<Skill> get_roles()
    {
        return roles;
    }
};

bool cmp(Project a, Project b)
{
    return a.get_best_before_day()<b.get_best_before_day();
}

int main()
{
    ifstream cin("input.txt");
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        string name;
        cin >> name;
        int skill_cnt;
        cin >> skill_cnt;
        string skill_name;
        cin >> skill_name;
        int skill_level;
        cin >> skill_level;
        LastTime[skill_name] = 0;
        Name[skill_name]=name;
    }

    vector<Project> projects;
    for (int i = 0; i < m; ++i)
    {
        string name;
        cin >> name;
        int days_to_complete;
        cin >> days_to_complete;
        int initial_score;
        cin >> initial_score;
        int best_before_day;
        cin >> best_before_day;
        int cnt_roles;
        cin >> cnt_roles;
        vector<Skill> roles;
        while (cnt_roles--)
        {
            string skill_name;
            cin >> skill_name;
            int skill_level;
            cin >> skill_level;
            roles.emplace_back(skill_name, skill_level);
        }
        projects.emplace_back(name, days_to_complete, initial_score, best_before_day, roles);
    }

    sort(projects.begin(), projects.end(),cmp);

    vector<pair<string, vector<string> > > Res;
    for(auto project: projects)
    {
        int begin_day=0;

        if(project.get_initial_score()-(project.get_best_before_day()-(begin_day+project.get_days_to_complete()))>0)
        {
            vector<string> Assigned;
            for(auto role: project.get_roles())
            {
                Assigned.push_back(Name[role.get_name()]);
            }

            Res.push_back({project.get_name(), Assigned});
        }
    }

    ofstream fo("output.txt");

    fo<<Res.size()<<"\n";
    for(auto prj: Res)
    {
        fo<<prj.first<<"\n";
        for(auto pax: prj.second)
        {
            fo<<pax<<" ";
        }

        fo<<"\n";
    }

    fo.close();
    return 0;
}