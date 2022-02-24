#include<iostream>
#include<vector>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<Member> members;
    for (int i = 0; i < n; ++i)
    {
        string name;
        cin >> name;
        int skill_cnt;
        cin >> skill_cnt;
        vector<Skill> skills;
        while (skill_cnt--)
        {
            string skill_name;
            cin >> skill_name;
            int skill_level;
            cin >> skill_level;
            skills.emplace_back(skill_name, skill_level);
        }
        members.emplace_back(name, skills);
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
        projects.emplace_back(days_to_complete, initial_score, best_before_day, roles);
    }

    return 0;
}