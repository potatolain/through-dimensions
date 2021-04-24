#include "source/map/level_defs.h"
#include "source/globals.h"
#include "source/sprites/player.h"
#include "source/map/map.h"
#include "source/map/load_map.h"
#include "source/menus/input_helpers.h"
#include "source/neslib_asm/neslib.h"
#include "source/graphics/fade_animation.h"
#include "source/graphics/palettes.h"

#include "graphics/screen_firstlev.h"

CODE_BANK(PRG_BANK_LEVEL_DEFS);
const unsigned char levelFirstScreens[] = {
    0x01, 0x04, 0x08, 0x0a,
    0x10, 0x24, 0x18, 0x1a,
    0x20, 0x34, 0x28, 0x2a,
    0x30, 0x24, 0x38, 0x3a
};

const unsigned char levelFirstDimensions[] = {
    0x00, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
};

const unsigned char levelStartXPos[] = {
    48, 128, 128, 128,
    128, 128, 128, 128,
    128, 128, 128, 128,
    128, 128, 128, 128
};

const unsigned char levelStartYPos[] = {
    72, 128, 128, 128,
    128, 128, 128, 128,
    128, 128, 128, 128,
    128, 128, 128, 128
};

const unsigned char* LEVEL_INTRO_SCREEN[] = {
    0, screen_firstlev, 0, 0, 
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
};

void load_level(void) {
    playerOverworldPosition = levelFirstScreens[currentStageId];
    load_map();
    playerXPosition = levelStartXPos[currentStageId] << PLAYER_POSITION_SHIFT;
    playerYPosition = levelStartYPos[currentStageId] << PLAYER_POSITION_SHIFT;
    currentLayer = levelFirstDimensions[currentStageId];
    banked_call(PRG_BANK_PLAYER_SPRITE, update_player_sprite);

}

void draw_level_intro(void) {
    if (LEVEL_INTRO_SCREEN[currentStageId] != 0) {
        oam_clear();
        ppu_off();
        vram_adr(0x2000);
        set_chr_bank_0(CHR_BANK_MENU);
        pal_bg(titlePalette);

        set_vram_update(0);
        vram_unrle(LEVEL_INTRO_SCREEN[currentStageId]);
        scroll(0, 0);
        ppu_on_all();
        fade_in();
        banked_call(PRG_BANK_MENU_INPUT_HELPERS, wait_for_start);
        fade_out();
    } // Or just bail
}