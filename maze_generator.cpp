#include "maze_generator.h"


void generate_maze::generate_map()
{
	srand(unsigned(time(0)));
	int random_wall = 0;

	int pos_X, pos_Y;
	int total_num_cells;


	// pick a random starting point with odd coordinates
	pos_X = ( ( (rand()/2) *2) +1) % (map_size -1);
	pos_Y = ( ( (rand()/2) *2) +1) % (map_size -1);

	// total number of walls to be removed to make the maze
	total_num_cells = ((map_size-1)/2)*((map_size-1)/2);

	// store starting pos in corresponding members
	start_X = pos_X;
	start_Y = pos_Y;

	map[start_Y][start_X].cell_type = START;		// mark cell as starting point
	map[start_Y][start_X].visited = true;

	int num_visited_cells = 1;

	// stores the pos for X and Y
	// when dead end is reached, pop X and Y off and check
	// for a traversable cell
	// repeat until maze is generated
	stack<int> traversed_X, traversed_Y;

	while((num_visited_cells < total_num_cells))
	{
		bool can_move_north = false;
		bool can_move_south = false;
		bool can_move_west = false;
		bool can_move_east = false;

		if ( (pos_Y > 1) && (map[pos_Y-2][pos_X].visited == false) &&
				(map[pos_Y][pos_X].north_wall == true &&
				map[pos_Y-2][pos_X].south_wall == true) )
		{
			can_move_north = true;
		}
		if ( (pos_Y < map_size-2) && (map[pos_Y+2][pos_X].visited == false) &&
				(map[pos_Y][pos_X].south_wall == true &&
				 map[pos_Y+2][pos_X].north_wall == true) )
		{
			can_move_south = true;
		}
		if ( (pos_X > 1) && (map[pos_Y][pos_X-2].visited == false) &&
				(map[pos_Y][pos_X].west_wall == true &&
				 map[pos_Y][pos_X-2].east_wall == true) )
		{
			can_move_west = true;
		}
		if ( (pos_X < map_size-2) &&
				(map[pos_Y][pos_X+2].visited == false) &&
				(map[pos_Y][pos_X].east_wall == true &&
				 map[pos_Y][pos_X+2].west_wall == true) )
		{
			can_move_east = true;
		}

		if (can_move_north || can_move_south || can_move_west || can_move_east)
		{
			bool found_next_move = false;
			// cycle through until correct move is found
			while (!found_next_move) {
				// pick a random wall bordering the current cell
				random_wall = (rand() % 4);
				Direction dir;
				switch (random_wall)
				{
				case 0:
					dir = Direction::NORTH;
					break;
				case 1:
					dir = Direction::SOUTH;
					break;
				case 2:
					dir = Direction::WEST;
					break;
				case 3:
					dir = Direction::EAST;
					break;
				}
				if (dir == Direction::NORTH && can_move_north)
				{
					found_next_move = true;
					map[pos_Y-1][pos_X].cell_type = SPACE;	// clear the cell
					map[pos_Y-1][pos_X].visited = true;	// mark cell as visited
					map[pos_Y][pos_X].north_wall = false;	// remove north wall

					// store x and y pos on stack
					traversed_X.push(pos_X);
					traversed_Y.push(pos_Y);

					pos_Y -= 2;								// move to new cell
					map[pos_Y][pos_X].visited = true;		// mark new cell as visited
					map[pos_Y][pos_X].cell_type = SPACE;		// clear the new cell
					map[pos_Y][pos_X].south_wall = false;	// remove south wall
					num_visited_cells++;
				}
				else if (dir == Direction::SOUTH && can_move_south)
				{
					found_next_move = true;
					map[pos_Y+1][pos_X].cell_type = SPACE;	// clear the cell
					map[pos_Y+1][pos_X].visited = true;	// mark cell as visited
					map[pos_Y][pos_X].south_wall = false;	// remove south wall

					// store x and y pos on stack
					traversed_X.push(pos_X);
					traversed_Y.push(pos_Y);

					pos_Y += 2;								// move to new cell
					map[pos_Y][pos_X].visited = true;		// mark new cell as visited
					map[pos_Y][pos_X].cell_type = SPACE;		// clear the new cell
					map[pos_Y][pos_X].north_wall = false;	// remove north wall
					num_visited_cells++;
				}
				else if (dir == Direction::WEST && can_move_west)
				{
					found_next_move = true;
					map[pos_Y][pos_X-1].cell_type = SPACE;	// clear the cell
					map[pos_Y][pos_X-1].visited = true;	// mark cell as visited
					map[pos_Y][pos_X].west_wall = false;	// remove west wall

					// store x and y pos on stack
					traversed_X.push(pos_X);
					traversed_Y.push(pos_Y);

					pos_X -= 2;								// move to new cell
					map[pos_Y][pos_X].visited = true;		// mark new cell as visited
					map[pos_Y][pos_X].cell_type = SPACE;		// clear the new cell
					map[pos_Y][pos_X].east_wall = false;	// remove east wall
					num_visited_cells++;
				}
				else if (dir == Direction::EAST && can_move_east)
				{
					found_next_move = true;
					map[pos_Y][pos_X+1].cell_type = SPACE;	// clear the cell
					map[pos_Y][pos_X+1].visited = true;	// mark cell as visited
					map[pos_Y][pos_X].east_wall = false;	// remove east wall

					// store x and y pos on stack
					traversed_X.push(pos_X);
					traversed_Y.push(pos_Y);

					pos_X += 2;								// move to new cell
					map[pos_Y][pos_X].visited = true;		// mark cell as visited
					map[pos_Y][pos_X].cell_type = SPACE;		// clear the new cell
					map[pos_Y][pos_X].west_wall = false;	// remove west wall
					num_visited_cells++;
				}
			}
		}
		else
		{
			// pop off x and y pos, reiterate and check for walls on new x and y pos
			// until a new path can be formed
			if ((traversed_X.size() != 0)) {
				pos_X = traversed_X.top();
				traversed_X.pop();
				pos_Y = traversed_Y.top();
				traversed_Y.pop();
			}
		}
	}
	// mark last cell as End
	map[pos_Y][pos_X].cell_type = END;
}

void generate_maze::init_map()
{
	for(int i = 0; i < map_size; i++)
	{
		for(int j = 0; j < map_size; j++)
		{
			map[i][j].cell_type = WALL;		// mark each cell as a wall
			map[i][j].visited = false;		// mark each cell as unvisited

			// mark each cell as surrounded by walls
			map[i][j].north_wall = true;
			map[i][j].south_wall = true;
			map[i][j].west_wall = true;
			map[i][j].east_wall = true;
		}
	}

	// for each cell bordering the edge
	// mark the walls bordering the edge as false
	// given the maze:
	// 0 0 0 0 0
	// 0 1 1 1 0
	// 0 1 0 1 0
	// 0 1 1 1 0
	// 0 0 0 0 0
	// the 1s denote the cells to be changed in this nested loop
	for(int i = 1; i < map_size-1; i++)
	{
		for(int j = 1; j < map_size-1; j++)
		{
			map[1][j].north_wall = false;
			map[map_size-2][j].south_wall = false;
			map[i][1].west_wall = false;
			map[i][map_size-2].east_wall = false;
		}
	}
}

void generate_maze::print_map()
{
	for (int i = 0; i < map_size; i++)
	{
		cout << endl;
		for (int j = 0; j < map_size; j++)
		{
			if (map[i][j].cell_type == SPACE)
				cout << " ";
			else if (map[i][j].cell_type == WALL)
				cout << "#";
			else if (map[i][j].cell_type == START)
				cout << "S";
			else if (map[i][j].cell_type == END)
				cout << "E";
		}
	}
	cout << endl;
}









