#include "source/neslib_asm/neslib.h"
#include "source/menus/title.h"
#include "source/globals.h"
#include "source/configuration/game_states.h"
#include "source/configuration/system_constants.h"
#include "source/menus/text_helpers.h"
#include "source/graphics/palettes.h"
#include "source/configuration/game_info.h"
#include "graphics/intro.h"
#include "source/graphics/fade_animation.h"

#include "graphics/title.h"

CODE_BANK(PRG_BANK_TITLE);

void draw_title_screen(void) {
    ppu_off();
	pal_bg(real_title);
	pal_spr(mainSpritePalette);

	set_chr_bank_0(0x0a);
    set_chr_bank_1(CHR_BANK_SPRITES);
	clear_screen();
	oam_clear();

	vram_adr(0x2000);
	vram_unrle(title);

	if (DEBUG) {
		put_str(NTADR_A(2, 2), "DEBUG MODE ON");
	}

	oam_spr(15 * 8, 18 * 8-2, 0x80, 0, 16);
	oam_spr(16 * 8, 18 * 8-2, 0x81, 0, 20);
	oam_spr(15 * 8, 19 * 8-2, 0x90, 0, 24);
	oam_spr(16 * 8, 19 * 8-2, 0x91, 0, 28);
	

	ppu_on_all();

	gameState = GAME_STATE_TITLE_INPUT;
}

void handle_title_input(void) {
	if (pad_trigger(0) & PAD_START) {
		gameState = GAME_STATE_POST_TITLE;
		sfx_play(SFX_CONFIRM, SFX_CHANNEL_1);
	}
}

void draw_post_title(void) {
	ppu_off();
	set_chr_bank_0(CHR_BANK_MENU);
	set_chr_bank_1(CHR_BANK_MENU);
	pal_bg(titlePalette);
	pal_spr(titlePalette);


	vram_adr(0x2000);
	vram_unrle(intro);

	ppu_on_all();
	fade_in();
}