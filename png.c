#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "png.h"

bool is_PNG(FILE * image){
    const char PNG_sign [] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0};

    // Criando variável para guardar a assinatura
    Byte signature[9];
    signature[8] = 0; /* Caractere vazio para in-
                         dicar fim da string. */
    // Lendo os 8 bytes da imagem e colocando na variavel signature
    fread(signature, 1, 8, image);
    // Checando se o arquivo é ou não uma PNG
    if (strcmp(signature, PNG_sign) == 0)
        return  true;
    return false;
}

Chunk * next_chunk(FILE * image){
    Chunk* block = (Chunk*)malloc(sizeof (Chunk));
    fread(block, 8, 1, image);

    // Corrigindo bug de little endian
    Byte * lenght = (Byte *)block;

    // Tem que vir antes do data, para não corromper os dados do mesmo
    block->type[4] = 0;
    block->data = (char *)malloc(block->lenght);

    // Lendo os dados do chunk
    fread(block->data, block->lenght, 1, image);

    // Lendo o crc
    fread(&block->crc, 4, 1, image);     // Salvando dados no cabeçalho
    return block;
}

void trash_chunk(Chunk * block){
    free(block->data);
    free(block);
}

IHDR* to_IHDR(const char * raw_data){
    Dimentions* data = (Dimentions*)raw_data;
    IHDR* header = (IHDR*)raw_data;
    return header;
}
