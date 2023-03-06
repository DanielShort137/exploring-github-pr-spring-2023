// <h1>The Code Puzzles - Labyrinth</h1>
// <h2>Labyrinth Introduction</h2>
// <p><em>In this section, a brief discussion about the code puzzle is
//         given.&nbsp; The complete set of instructions and complimentary
//         information</em></p>
// <p><em>can be found at the following <a title="The game description"
//             href="https://www.codingame.com/training/hard/the-labyrinth"
//             target="_blank" rel="noopener">website</a></em></p>
// <p style="padding-left: 40px;">The information that helped solve this puzzle
//     came from the "Introduction to Algorithms" course offered</p>
// <p>&nbsp;</p>
// <h2>The Code - Labyrinth</h2>
// <p>In this game, we are asked to help the captain of a starship (Captain
//     Kirk) with one of his missions.&nbsp; He has just landed on a planet that
//     requires the exploration of an unknown environment (covered grid-style
//     maze).&nbsp; There are only a limited amount of moves that Kirk is
//     permitted, as each move takes away from his available air supply.&nbsp;
//     If his air supply is depleted, then he dies.&nbsp; Once on the planet,
//     Kirk's goal is to look through each cell of the unknown environment, and
//     to make moves in any direction, and as he does reveal the maze of cells
//     that have been explored; which are now <em>mapped </em>and
//     <em>visible.&nbsp;&nbsp;</em>As each new cell is explored, Kirk must be
//     careful not to touch any of the off-limit walls, or he instantly
//     dies.&nbsp; Additionally, once the special <strong>"Control
//         Center"</strong> cell is revealed, a countdown timer is
//     started.&nbsp; At that time, he only has a few seconds to retrace the
//     shortest path, from the control center back to where he was originally
//     dropped off by the ship, and thus safely leave the planet.</p>
// <p>&nbsp;</p>
// <p><mark> crm: I like how you had added this introduction with access to the
//         hyperlink to the game I would suggest that you would add a brief
//         description of the game the reason I would suggest this is because
//         certain target audience would like some or others wouldn't</mark></p>
// <p><span style="background-color: rgb(45, 194, 107);"><mark>dls781:&nbsp;
//             Thanks for the feedback.&nbsp; See the above
//             description</mark></span></p>


#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <queue>
#include <limits>

using namespace std;

const int INFINITY = numeric_limits<int>::max();
int r, c, alarm;
// <p>&nbsp; &nbsp; This function checks to see if given coordinate is on the
//     map provided by the game.&nbsp; It compares the initialized row and
//     column arguments that&nbsp;</p>
// <p>were passed into the code main as a size of the unexplored grid.</p>
bool is_on_map(vector<int> v) {
    if (v[0] < 0 || v[0] >= r || v[1] < 0 || v[1] >= c) {
        return false;
    }
    return true;
}

// <p>The following function returns a field of neighbors that are on the map by
//     searching in each cardinal direction by one cell .&nbsp;</p>
// <p>It calls the is_on_map() function to check to make sure the</p>
// <p>boundaries are respected and no invalid neighbors are returned as a
//     possible direction to travel.</p>
vector<vector<int>> get_neighbours(vector<int> vertex) {
    int vr = vertex[0];
    int vc = vertex[1];
    vector<vector<int>> first_set = {{vr-1, vc}, {vr+1, vc}, {vr, vc-1}, {vr, vc+1}};

    vector<vector<int>> neighbours;
    for (vector<int> v : first_set) {
        if (is_on_map(v)) {
            neighbours.push_back(v);
        }
    }
    return neighbours;
}

// <p>In order to find our way back to the entry point of the maze, we need to
//     remember our steps, and that is why this traces</p>
// <p>our first step from search path</p>
vector<int> first_step(vector<vector<vector<int>>> parent, vector<int> start, vector<int> n) {
    vector<int> v = n;
    while (parent[v[0]][v[1]] != start) {
        v = parent[v[0]][v[1]];
    }
    return v;
}

// <p>The game solution is based upon the popular Breadth First Search (BFS)
//     algorithm for exploring and plotting a trajectory through the Labyrinth
//     game.</p>
// <p><mark> Crm: This is a quality example of pseudocode to show how you have
//         gotten BFS algorithm and helps to explain the algorithm</mark></p>
// <p><mark>dls781:&nbsp; Again, thanks.&nbsp; I borrowed it from my class
//         lecture notes in an introduction to algorithms class that I took last
//         semester.&nbsp; Credit to Dr. Maxwell Young.</mark></p>
// <p>The algorithm is composed of several code blocks that help to perform the
//     search.&nbsp; The image below provides the psuedo-code that helps to
//     simplify the</p>
// <p>intent of the detailed functions to follow.</p>
// <figure class="image"><img title="Pseudo-Code" src="media/Picture1.png"
//         alt="" width="800" height="602">
//     <figcaption>Pseudo-Code</figcaption>
// </figure>
// <p><span
//         style="background-color: rgb(255, 255, 255); color: rgb(185, 106, 217);"><strong>Graph
//             Theory</strong></span>, <span
//         style="color: rgb(230, 126, 35);"><strong>En-Queueing</strong></span>
//     and<strong> <span
//             style="color: rgb(22, 145, 121);">De-Queueing</span></strong>,
//     <span
//         style="color: rgb(35, 111, 161);"><strong>Parent-Child</strong></span>
//     node relationships, and concepts</p>
// <p>of <strong><span
//             style="background-color: rgb(236, 202, 250);">Path-Planning</span>
//     </strong>are prerequisite knowledge for understanding the code.&nbsp; But
//     in each iteration through the main loop,&nbsp;</p>
// <p>much of the details may be reasoned out by studying the basic graph below;
//     which is explored using a BFS:</p>
// <p><mark> Crm: I like how you have added this note and what prerequisites you
//         need in order to understand this algorithm.</mark></p>
// <p><mark>dls781:&nbsp; Same comment as above.</mark></p>
// <p>&nbsp;</p>
// <figure class="image"><img title="Iterative Steps of BFS Algo."
//         src="media/Picture2.png" alt="" width="704" height="597">
//     <figcaption>Iterative Steps of BFS Algo.</figcaption>
// </figure>
// <p>&nbsp;</p>
vector<int> BFS(vector<vector<char>> game_map, vector<int> start, char goal) {
    // <p><mark> crm: Your naming of variables for the BFS algorithm is clear
    //         and coherent</mark></p>
    // <p><mark>dls781:&nbsp; I tried to keep the variable names consistent with
    //         the pseudo-code above, so that it would be easier to make sense
    //         of, once the algorithm was presented.</mark></p>
    queue<vector<int>> queue;
    vector<vector<int>> colour;
    vector<vector<int>> distance;
    vector<vector<vector<int>>> parents;
    for (int row = 0; row < game_map.size(); row++) {
        colour.push_back({});
        distance.push_back({});
        parents.push_back({});
        for (int collumn = 0; collumn < game_map[row].size(); collumn++) {
            colour[row].push_back(0);
            distance[row].push_back(INFINITY);
            parents[row].push_back({});
        }
    }

    colour[start[0]][start[1]] = 1;
    distance[start[0]][start[1]] = 0;

    queue.push(start);

    // <p><strong><span style="color: rgb(224, 62, 45);">Algorithm
    //             loop</span></strong></p>
    // <p><mark> crm: From a first reader perspective this is a great indication
    //         of for where the loop of the alogrithm starts this is a great
    //         thing to add</mark></p>
    // <p><mark>dls781:&nbsp; Cool, I was hoping for that to be helpful for
    //         those who may be looking back at the diagram of each iteration
    //         through the loop.</mark></p>
    while (!queue.empty()) {
        vector<int> u = queue.front();
        queue.pop();
        vector<char> forbidden_symbols = {'#'};
        if (goal == '?') {
            forbidden_symbols.push_back('C');
        }
        vector<vector<int>> neighbours = get_neighbours(u);
        for (vector<int> n : neighbours) {
            if (find(forbidden_symbols.begin(), forbidden_symbols.end(), game_map[n[0]][n[1]]) == forbidden_symbols.end()) {
                if (colour[n[0]][n[1]] == 0) {
                    colour[n[0]][n[1]] = 1;
                    distance[n[0]][n[1]] = distance[u[0]][u[1]] + 1;
                    parents[n[0]][n[1]] = u;
                    queue.push(n);
                    if (game_map[n[0]][n[1]] == goal) {
                        return first_step(parents, start, n);
                    }
                }
            }
        }
        colour[u[0]][u[1]] = 2;
    }

    return {};
}
    
vector<int>  where_to_go(vector<vector<char>> game_map, vector<int> start, bool back) {
    if (!back) {
        vector<int>  go_to;
       go_to = BFS(game_map, start, '?');
        if (go_to.empty()) {
            return BFS(game_map, start, 'C');
        }
        return go_to;
    } else {
        return BFS(game_map, start, 'T');
    }
}
// <p><mark>&nbsp;crm: Like how you have detailed description on how the main
//         code functions and that helps grasp the idea on how main
//         works.</mark></p>
// <p><mark>dls781:&nbsp; It was meant to mirror the flow of the pseudo-code
//         above, for the sake of consistency and ease of understanding.</mark>
// </p>
// <h2>The Main body of the Code is Here.</h2>
// <p>the way that the challenge was organized was to have parameters passed
//     into the main execution</p>
// <p>from the standard input, and then the code would right out the next "step"
//     as a direction in either one of the</p>
// <p>UP/DOWN/LEFT/RIGHT&nbsp;</p>
// <p>directions.&nbsp; That choice depends on whether or not the main character
//     (Kirk) was still searching the maze,&nbsp;</p>
// <p>or whether he had found the control room and needed to take his shortest
//     path from "C"- control to "T"- target</p>
// <p>to get back to where he started before a timer expired.</p>
int main()
{
// <p><mark>&nbsp;crm: The variables in main are consistent and are easy to
//         understand and the main code is formatted nicely.</mark></p>
// <p><mark>dls781:&nbsp; Thank you.&nbsp; I try to keep it clean.&nbsp; I
//         probably could have added many comments to assist with reading the
//         code.</mark></p>
// <p>&nbsp;</p>

    cin >> r >> c >> alarm; cin.ignore();
    bool back = false;
    while (1) {
        vector<int> pair;
        int kr, kc;
        cin >> kr >> kc; cin.ignore();
        pair.push_back(kr);
        pair.push_back(kc);
        vector<vector<char>> game_map;
        vector<int> go_to;
        vector<char> row;
        for (int i = 0; i < r; i++) {
            string ROW; // C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
            cin >> ROW; cin.ignore();
            
            game_map.push_back({});
            for (char c : ROW)
                game_map.back().push_back(c);
        }
        fprintf(stderr,"%s\n",row.data());
        if (game_map[kr][kc] == 'C') {
            back = true;
            //alarm = a;
        }
        go_to = where_to_go(game_map, pair, back);
        fprintf(stderr,"%i\n",go_to[0]);
		if (go_to[1] > kc)
			printf("RIGHT\n");
		else if (go_to[1] < kc)
			printf("LEFT\n");
		else if (go_to[0] < kr)
			printf("UP\n");
		else
			printf("DOWN\n");
    }
}
