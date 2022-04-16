#ifndef GHOSTLAB_GUI_H
#define GHOSTLAB_GUI_H

#if GHOSTLAB_TUI || GHOSTLAB_GUI

#include <common/types.h>

struct gl_command_definition_t;

int32_t gl_gui_create(const char *gui_title);

void gl_gui_start_render(bool *quit);

void gl_gui_end_render();

void gl_gui_free();

void gl_igBegin(const char *title, float height);

void gl_igConsole(const struct gl_command_definition_t **cmd_defs, uint32_t cmd_defs_count);

#endif

#endif /* GHOSTLAB_GUI_H */