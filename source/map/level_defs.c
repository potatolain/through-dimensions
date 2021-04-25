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
#include "graphics/screen_secondlev.h"
#include "graphics/screen_gohome.h"
#include "graphics/screen_whereends.h"
#include "graphics/screen_gems.h"

CODE_BANK(PRG_BANK_LEVEL_DEFS);

// Set to 0 for normal gameplay
#define FORCE_LEVEL 4

const unsigned char levelFirstScreens[] = {
    0x01, 0x02, 0x03, 0x04,
    0x06, 0x24, 0x18, 0x1a,
    0x20, 0x34, 0x28, 0x2a,
    0x30, 0x24, 0x38, 0x3a,

    // TEST LEVEL
    62
};

const unsigned char levelFirstDimensions[] = {
    LAYER_NORMAL,    LAYER_NORMAL,    LAYER_DESERT,    LAYER_CALM,
    LAYER_NORMAL,    LAYER_NORMAL,    LAYER_NORMAL,    LAYER_NORMAL,
    LAYER_NORMAL,    LAYER_NORMAL,    LAYER_NORMAL,    LAYER_NORMAL,
    LAYER_NORMAL,    LAYER_NORMAL,    LAYER_NORMAL,    LAYER_NORMAL,

    // TEST LEVEL
    LAYER_NORMAL
};

const unsigned char levelStartXPos[] = {
    48, 24, 128, 24,
    128, 128, 128, 128,
    128, 128, 128, 128,
    128, 128, 128, 128,

    // TEST LEVEL
    128
};

const unsigned char levelStartYPos[] = {
    72, 64, 128, 112,
    128, 128, 128, 128,
    128, 128, 128, 128,
    128, 128, 128, 128,

    // TEST LEVEL
    128
};

const unsigned char* LEVEL_INTRO_SCREEN[] = {
    0, screen_firstlev, screen_secondlev, 0, 
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,


    // TEST LEVEL
    0,

    // Homeless, rehome us please!
    screen_gohome,
    screen_whereends,
    screen_gems
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
    #if DEBUG && FORCE_LEVEL != 0
        currentStageId = FORCE_LEVEL;
    #endif

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