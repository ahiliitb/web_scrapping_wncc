#include <bits/stdc++.h>
using namespace std;

int find_no_in_column(vector<vector<int>> matrix, int coloum_index, int no_to_find, int no_of_rows, vector<int> role_allocation)
{
    int ans = -1;
    for (int i = 0; i < no_of_rows; i++)
    {
        if (matrix[i][coloum_index] == no_to_find && role_allocation[i] == -1)
        {
            ans = i;
            break;
        }
    }
    return ans;
}

vector<int> index_of_decreasing_order(vector<int> arr)
{
    vector<int> index(arr.size());
    for (int i = 0; i < arr.size(); i++)
    {
        index[i] = i;
    }
    for (int i = 0; i < arr.size() - 1; i++)
    {
        for (int j = 0; j < arr.size() - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swap(index[j], index[j + 1]);
            }
        }
    }
    reverse(index.begin(), index.end());
    return index;
}

int main()
{
    // number of students
    int n;
    cout << "Enter number of participants" << endl;
    cin >> n;
    vector<string> student_roll(n);
    vector<vector<int>> student_skills(n, vector<int>(5));
    // taking input of student skill
    cout<<"Enter roll no and skills of the student"<<endl;
    for (int i = 0; i < n; i++)
    {
        cin >> student_roll[i];
        for (int j = 0; j < 5; j++)
            cin >> student_skills[i][j];
    }

    // number of projects
    int m;
    cout << "Enter number of projects" << endl;
    cin >> m;
    vector<string> project_name(m);
    vector<vector<int>> skills_required(m, vector<int>(5));
    // taking input of skills required for project

    cout<<"Enter name and required skill of the project"<<endl;
    for (int i = 0; i < m; i++)
    {
        cin >> project_name[i];
        for (int j = 0; j < 5; j++)
            cin >> skills_required[i][j];
    }
    vector<int> role_allocation(n, -1); // i.e. which project will be allocated to the students
    vector<vector<int>> student_allocation(m, vector<int>(5, -1));  // i.e. which student will be allocated for the given role of a project

    // role allocation without taking care of comentor

    vector<int> sum_of_skill_required(m, 0);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            sum_of_skill_required[i] += skills_required[i][j];
        }
    }
    vector<int> project_index = index_of_decreasing_order(sum_of_skill_required);
    for (int i = 0; i < m; i++)
    {
        vector<int> temp(5);
        for (int l = 0; l < 5; l++)
            temp[l] = skills_required[project_index[i]][l];
        vector<int> index = index_of_decreasing_order(temp);
        for (int j = 0; j < 5; j++)
        {
            int helper = skills_required[project_index[i]][index[j]];
            if (helper == 0)
            {
                student_allocation[project_index[i]][index[j]] = -2;
                continue; // as no role to be allocated
            }
            while (helper != 6)
            {
                if (find_no_in_column(student_skills, index[j], helper, n, role_allocation) != -1)
                {
                    student_allocation[project_index[i]][index[j]] = find_no_in_column(student_skills, index[j], helper, n, role_allocation);
                    role_allocation[find_no_in_column(student_skills, index[j], helper, n, role_allocation)] = project_index[i];
                    break;
                }
                helper++;
            }
        }
    }

    // modification due to comentor case

    for (int i = 0; i < m; i++)
    {
        vector<int> temp(5);
        for (int l = 0; l < 5; l++)
            temp[l] = skills_required[project_index[i]][l];
        vector<int> index = index_of_decreasing_order(temp);
        for (int j = 0; j < 5; j++)
        {
            int helper = skills_required[project_index[i]][index[j]];
            if (student_allocation[project_index[i]][index[j]] == -1)
            {
                for (int k = 0; k < 5; k++)
                {
                    int student_index;
                    if (student_allocation[project_index[i]][k] != -2 && student_allocation[project_index[i]][k] != -1)
                        student_index = student_allocation[project_index[i]][k];
                    else
                        continue;
                    if (student_skills[student_index][index[j]] > helper)
                    {
                        if (find_no_in_column(student_skills, index[j], helper - 1, n, role_allocation) != -1)
                        {
                            student_allocation[project_index[i]][index[j]] = find_no_in_column(student_skills, index[j], helper - 1, n, role_allocation);
                            role_allocation[find_no_in_column(student_skills, index[j], helper - 1, n, role_allocation)] = project_index[i];
                            break;
                        }
                    }
                }
            }
        }
    }

    // counting the projects completed

    int project_completed = 0;
    for (int i = 0; i < m; i++)
    {
        int count = 0;
        for (int j = 0; j < 5; j++)
        {
            if (student_allocation[i][j] != -1)
                count++;
        }
        if (count == 5)
            project_completed++;
    }

    cout<<endl<<"Total number of projects completed is: ";
    cout << project_completed << endl; // final output


    return 0;
}
