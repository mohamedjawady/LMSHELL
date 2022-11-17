#include "lm_modes.h"

lm_mode parse_mode(int argc) {
    return argc == 1;
}

char* print_mode(lm_mode mode){
    char* buffer = (char*)malloc(15);
    switch (mode)
    {
    case LM_BACH:
        snprintf(buffer, 15, "%s", "LM_BACH");
        break;
    
    default:
        snprintf(buffer, 15, "%s", "LM_INTERACTIVE");
        break;
    }
    return buffer;
}

void initialize_ctx(lm_context* context){
    char cwd[MAX_NAME*MAX_NAME];
    getcwd(cwd, sizeof(cwd));
    context->curr_path = cwd;
    context->l_com_status = 0;
    context->last_comm = "";
}

char* lm_prompt(lm_context* context) {
    char* str_icmd = (char*)malloc(MAX_CMD);
    printf("[%s] %% ", context->curr_path);
    gets(str_icmd);
    context->last_comm = str_icmd;
    return str_icmd;
}