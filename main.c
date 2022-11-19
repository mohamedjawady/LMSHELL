#include <stdio.h>
#include <signal.h>
#include "lm_modes.h"
int main(int argc, char** argv) {
    lm_mode mode = parse_mode(argc);
    if(mode){
        // INTERACTIVE MODE
        lm_context ctx;
        initialize_ctx(&ctx);

        while(strcmp(ctx.last_comm, "quit")){
            // INTERACTIVE LOOP
            printf("> Last command %s\n", lm_prompt(&ctx));
        }
        printf("Exited successfully\n");
    }else{
        // BACH MODE
        printf("BACH mode\n");
    }
}