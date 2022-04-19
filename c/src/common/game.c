#include <common/game.h>
#include <stdlib.h>
#include <common/array.h>
#include <common/maze.h>

gl_game_t *gl_game_find_game_with_socket(gl_game_t *games, int32_t socket_id) {
    for (uint32_t i = 0; i < gl_array_get_size(games); i++) {
        for (uint32_t j = 0; j < gl_array_get_size(games[i].players); j++) {
            if (games[i].players[j].socket_id == socket_id) {
                return &games[i];
            }
        }
    }
    
    return 0;
}

gl_player_t *gl_game_find_player_with_socket(gl_game_t *games, int32_t socket_id) {
    for (uint32_t i = 0; i < gl_array_get_size(games); i++) {
        for (uint32_t j = 0; j < gl_array_get_size(games[i].players); j++) {
            if (games[i].players[j].socket_id == socket_id) {
                return &games[i].players[i];
            }
        }
    }
    
    return 0;
}

gl_ghost_t *gl_game_generate_ghosts(gl_maze_t *maze, uint8_t num_ghosts) {
    gl_ghost_t *ghosts = 0;
    
    uint32_t i = 0;
    while (gl_array_get_size(ghosts) < num_ghosts) {
        gl_pos_t pos;
        
        uint32_t j = 0;
        do {
            pos.x = rand() % gl_array_get_size(maze->grid[0]);
            pos.y = rand() % gl_array_get_size(maze->grid);
            
            if (j++ >= 100) {
                break;
            }
        } while (maze->grid[pos.y][pos.x] != GL_MAZE_ELEMENT_ROOM || gl_game_is_ghost_at_pos(ghosts, pos));
        
        if (j < 100) {
            gl_array_push(ghosts, ((gl_ghost_t) { .pos = pos }));
        } else if (i++ > 5) {
            break;
        }
    }
    
    return ghosts;
}

gl_player_t *gl_game_generate_players_pos(struct gl_maze_t *maze, gl_player_t *players, gl_ghost_t *ghosts) {
    if (!players) {
        return 0;
    }
    
    for (uint32_t i = 0; i < gl_array_get_size(players); i++) {
        gl_pos_t pos;
    
        uint32_t j = 0;
        do {
            pos.x = rand() % gl_array_get_size(maze->grid[0]);
            pos.y = rand() % gl_array_get_size(maze->grid);
        
            if (j++ >= 100) {
                break;
            }
        } while (maze->grid[pos.y][pos.x] != GL_MAZE_ELEMENT_ROOM || gl_game_is_ghost_at_pos(ghosts, pos) || gl_game_is_player_at_pos(players, pos));
    
        players[i].pos = pos;
    }
    
    return players;
}

bool gl_game_is_ghost_at_pos(gl_ghost_t *ghosts, gl_pos_t pos) {
    if (!ghosts) {
        return false;
    }
    
    bool found = false;
    
    for (uint32_t i = 0; i < gl_array_get_size(ghosts); i++) {
        if (ghosts[i].pos.x == pos.x && ghosts[i].pos.y == pos.y) {
            found = true;
            break;
        }
    }
    
    return found;
}

bool gl_game_is_player_at_pos(gl_player_t *players, gl_pos_t pos) {
    if (!players) {
        return false;
    }
    
    bool found = false;
    
    for (uint32_t i = 0; i < gl_array_get_size(players); i++) {
        if (players[i].pos.x == pos.x && players[i].pos.y == pos.y) {
            found = true;
            break;
        }
    }
    
    return found;
}

void gl_game_free(gl_game_t *game) {
    if (game) {
        gl_maze_free(game->maze);
        gl_array_free(game->ghosts);
        gl_array_free(game->players);
    }
}