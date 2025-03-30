//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.consts.h"
//silver_chain_scope_end


KnolageDigestor *newKnolageDigestor(ModelProps *props, const char *question);

void KnolageDigestor_digest(KnolageDigestor *self,const char *current_item);

void KnolageDigestor_digest_file(KnolageDigestor *self,const char *file_path,const char *current_item);

void KnolageDigestor_digest_url(KnolageDigestor *self,const char *url,const char *current_item);

void KnolageDigestor_free(KnolageDigestor *self);
