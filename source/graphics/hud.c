#include "source/neslib_asm/neslib.h"
#include "source/graphics/hud.h"
#include "source/globals.h"

CODE_BANK(PRG_BANK_HUD);

void draw_hud(void) {
    vram_adr(NAMETABLE_A + HUD_POSITION_START);
    for (i = 0; i != 160; ++i) {
        vram_put(HUD_TILE_BLANK);
    }
    vram_put(HUD_TILE_BORDER_BL);
    for (i = 0; i != 30; ++i) {
        vram_put(HUD_TILE_BORDER_HORIZONTAL);
    }
    vram_put(HUD_TILE_BORDER_BR);

    vram_adr(NAMETABLE_A + HUD_ATTRS_START);
    for (i = 0; i != 16; ++i) {
        vram_put(0xff);
    }

    vram_adr(NTADR_A(24, 26));
    vram_put(0xf3);
    for (i = 0; i != 4; ++i) {
        vram_put(0xec + i);
    }

    /*
    vram_adr(NAMETABLE_A + HUD_HEART_START - 0x20 - 1);
    for (i = 0; i != 6; ++i)  {
        vram_put(0xea + i);
    }
    */

   vram_adr(NAMETABLE_A + HUD_HEART_START - 0x20);
   vram_put(0xe2);
   vram_put(0xee);
   vram_put(0xe3);
   vram_put(0xf1);

}

void update_hud(void) {
    // Make sure we don't update vram while editing the screenBuffer array, or we could get visual glitches.
    set_vram_update(NULL);

    // This sets up screenBuffer to print x hearts, then x more empty hearts. 
    // You give it the address, tell it the direction to write, then follow up with
    // Ids, ending with NT_UPD_EOF
    
    // We use i for the index on screen buffer, so we don't have to shift things around
    // as we add values. 
    i = 0;
    screenBuffer[i++] = MSB(NAMETABLE_A + HUD_HEART_START+1) | NT_UPD_HORZ;
    screenBuffer[i++] = LSB(NAMETABLE_A + HUD_HEART_START+1);
    /*
    screenBuffer[i++] = playerMaxHealth;
    // Add one heart for every health the player has
    for (j = 0; j != playerHealth; ++j) {
        screenBuffer[i++] = HUD_TILE_HEART;
    }
    // Using the same variable, add empty hearts up to max health
    for (; j != playerMaxHealth; ++j) {
        screenBuffer[i++] = HUD_TILE_HEART_EMPTY;
    }
    */
   // TODO: If we're struggling, this is terrifyingly inefficient
   screenBuffer[i++] = 2;
   screenBuffer[i++] = (HUD_TILE_NUMBER) + ((playerGemCount) / 10);
   screenBuffer[i++] = (HUD_TILE_NUMBER) + ((playerGemCount) % 10);

    // Next, draw the key count, using the key tile, and our key count variable
    screenBuffer[i++] = MSB(NTADR_A(25, 27)) | NT_UPD_HORZ;
    screenBuffer[i++] = LSB(NTADR_A(25, 27));
    screenBuffer[i++] = 2;
    // FIXME: Draw layer names if we have the space
    screenBuffer[i++] = HUD_TILE_NUMBER;
    screenBuffer[i++] = HUD_TILE_NUMBER + currentLayer + 1;


    screenBuffer[i++] = NT_UPD_EOF;
    set_vram_update(screenBuffer);

}