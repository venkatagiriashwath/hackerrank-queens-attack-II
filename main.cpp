#include <bits/stdc++.h>
using namespace std;

vector<string> split_string(string);

int queensAttack(int n, int k, int r_q, int c_q, vector<vector<int>> obstacles) {
    long qscount = 4 * (n - 1) - abs(r_q - c_q) - abs(n + 1 - (r_q + c_q));
    //count of queen attacking positions, without any obstacles
    //horizontal (n - 1)
    //vertical (n - 1)
    //left diagonal (n - abs(r_q - c_q) - 1)
    //right diagonal (n - abs((n + 1) - (r_q + c_q)) - 1)

    vector<vector<vector<int>>> relevant_obstacles(8); 
    //obstacles which are in the queen's line of attack
    
    vector<vector<int>> most_relevant_obstacles;
    //the obstacles in the line of attack, closest to the queen
    
    vector<int> flag(2);
    //stores the position of the obstacle with minimum distance from the queen, in a 
    //particular segment
    
    long r_o, c_o, distance, min;
    long i,j;

    //loop to find the relevant obstacles
    for (i = 0; i < obstacles.size(); i++) {

        r_o = obstacles[i][0];
        c_o = obstacles[i][1];
        
        //left diagonal
        if ((r_o + c_o) == (r_q + c_q)) {
            
            //upper half of left diagonal   
            if ((r_o - c_o) > (r_q - c_q)) 
                relevant_obstacles[0].push_back(obstacles[i]);
        
            //lower half of left diagonal
            else
                relevant_obstacles[1].push_back(obstacles[i]);
        }
        
        //right diagonal
        else if ((r_o - c_o) == (r_q - c_q)) {
        
            //upper half of right diagonal
            if ((r_o + c_o) > (r_q + c_q))
                relevant_obstacles[2].push_back(obstacles[i]);
        
            //lower half of right diagonal
            else
                relevant_obstacles[3].push_back(obstacles[i]);
        }
        
        //horizontal
        else if (r_o == r_q) {
        
            //to the left of the queen
            if (c_o < c_q)
                relevant_obstacles[4].push_back(obstacles[i]);
        
            //to the right of the queen
            else
                relevant_obstacles[5].push_back(obstacles[i]);
        }
        
        //vertical
        else if (c_o == c_q) {
        
            //under the queen
            if (r_o < r_q)
                relevant_obstacles[6].push_back(obstacles[i]);
        
            //above the queen
            else
                relevant_obstacles[7].push_back(obstacles[i]);
        }
    }

    //loop to find the most relevant obstacles
    for (i = 0; i < 8; i++) {
       
        min = 0;
       
        for (j = 0; j < relevant_obstacles[i].size(); j++) {
       
            //employing coordinate geometry distance formula
            distance = pow(relevant_obstacles[i][j][0] - r_q, 2);
            distance += pow(relevant_obstacles[i][j][1] - c_q, 2);
       
            //initialising the minimum
            if (j == 0) {
            
                min = distance;
                flag[0] = i;
                flag[1] = j;
            }
            
            else {
            
                if (distance < min) {
            
                    min = distance;
                    flag[0] = i;
                    flag[1] = j;
                }
            }
        }
        
        if (min != 0) //if elements exist in the segment
            most_relevant_obstacles.push_back(relevant_obstacles[flag[0]][flag[1]]);
    }

    //finding the number of positions the queen can attack
    for (i = 0; i < most_relevant_obstacles.size(); i++) {
    
        r_o = most_relevant_obstacles[i][0];
        c_o = most_relevant_obstacles[i][1];
        
        //left diagonal for queen position
        if (r_o + c_o == r_q + c_q) {
       
            //upper half of left diagonal
            if ((r_o - c_o) > (r_q - c_q)) {
       
                //diagonal border condition, r_b = n
                if ((r_q + c_q - n) >= 1 && (r_q + c_q - n) <= n) 
                    qscount -= (n - ((r_q + c_q) - n) - (r_o - c_o)) / 2 + 1;
       
                //diagonal border condition, c_b = 1
                else     
                    qscount -= ((r_q + c_q) - 1 - 1 - (r_o - c_o)) / 2 + 1;
                
            }
       
            //lower half of left diagonal
            else {
       
                //diagonal border condition, c_b = n
                if ((r_q + c_q - n) >= 1 && (r_q + c_q - n) <= n) 
                    qscount += ((r_q + c_q - n) - n - (r_o - c_o)) / 2 - 1;
       
                //diagonal border condition, r_b = 1
                else
                    qscount += (1 - (r_q + c_q - 1) - (r_o - c_o)) / 2 - 1;
            }
        }

        //right diagonal for queen position
        else if ((r_o - c_o) == (r_q - c_q)) {
       
            //upper half of right diagonal
            if ((r_o + c_o) > (r_q + c_q)) {
       
                //diagonal border condition, c_b = n
                if ((r_q - c_q + n) >= 1 && (r_q - c_q + n) <= n) 
                    qscount -= (((r_q - c_q + n) + n) - (r_o + c_o)) / 2 + 1;
       
                //diagonal border condition, r_b = n
                else        
                    qscount -= ((n + (c_q - r_q + n)) - (r_o + c_o)) / 2 + 1;    
            }
       
            //lower half of right diagonal
            else {
       
                //diagonal border condition, c_b = 1
                if ((r_q - c_q + 1) >= 1 && (r_q - c_q + 1) <= n) 
                    qscount += (((r_q - c_q + 1) + 1) - (r_o + c_o)) / 2 - 1;
       
                //diagonal border condition, r_b = 1
                else
                    qscount += ((1 + (c_q - r_q + 1)) - (r_o + c_o)) / 2 - 1;
            }
        }
       
        //horizontal line for queen position
        else if (r_o == r_q) {
       
            //left side of queen
            if (c_o < c_q)
                qscount -= c_o;
       
            //right side of queen
            else
                qscount -= n - c_o + 1;
        }
       
        //vertical line for queen position
        else if (c_o == c_q) {
       
            //under the queen
            if (r_o < r_q)
                qscount -= r_o;
       
            //above the queen
            else
                qscount -= n - r_o + 1;
        }
        else continue;
    }

    //returning the number 
    return qscount;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string r_qC_q_temp;
    getline(cin, r_qC_q_temp);

    vector<string> r_qC_q = split_string(r_qC_q_temp);

    int r_q = stoi(r_qC_q[0]);

    int c_q = stoi(r_qC_q[1]);

    vector<vector<int>> obstacles(k);
    for (int i = 0; i < k; i++) {
        obstacles[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> obstacles[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = queensAttack(n, k, r_q, c_q, obstacles);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
