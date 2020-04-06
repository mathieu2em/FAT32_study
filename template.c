#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
#pragma ide diagnostic ignored "readability-non-const-parameter"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAT_NAME_LENGTH 11
#define FAT_EOC_TAG 0x0FFFFFF8
#define FAT_DIR_ENTRY_SIZE 32
#define HAS_NO_ERROR(err) ((err) >= 0)
#define NO_ERR 0
#define GENERAL_ERR -1
#define OUT_OF_MEM -3
#define RES_NOT_FOUND -4
#define CAST(t, e) ((t) (e))
#define as_uint16(x) \
((CAST(uint16,(x)[1])<<8U)+(x)[0])
#define as_uint32(x) \
((((((CAST(uint32,(x)[3])<<8U)+(x)[2])<<8U)+(x)[1])<<8U)+(x)[0])

typedef unsigned char uint8;
typedef uint8 bool;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef int error_code;

/**
 * Pourquoi est-ce que les champs sont construit de cette façon et non pas directement avec les bons types?
 * C'est une question de portabilité. FAT32 sauvegarde les données en BigEndian, mais votre système de ne l'est
 * peut-être pas. Afin d'éviter ces problèmes, on lit les champs avec des macros qui convertissent la valeur.
 * Par exemple, si vous voulez lire le paramètre BPB_HiddSec et obtenir une valeur en entier 32 bits, vous faites:
 *
 * BPB* bpb;
 * uint32 hidden_sectors = as_uint32(BPB->BPP_HiddSec);
 *
 */
typedef struct BIOS_Parameter_Block_struct {
    uint8 BS_jmpBoot[3];
    uint8 BS_OEMName[8];
    uint8 BPB_BytsPerSec[2];  // 512, 1024, 2048 or 4096
    uint8 BPB_SecPerClus;     // 1, 2, 4, 8, 16, 32, 64 or 128
    uint8 BPB_RsvdSecCnt[2];  // 1 for FAT12 and FAT16, typically 32 for FAT32
    uint8 BPB_NumFATs;        // should be 2
    uint8 BPB_RootEntCnt[2];
    uint8 BPB_TotSec16[2];
    uint8 BPB_Media;
    uint8 BPB_FATSz16[2];
    uint8 BPB_SecPerTrk[2];
    uint8 BPB_NumHeads[2];
    uint8 BPB_HiddSec[4];
    uint8 BPB_TotSec32[4];
    uint8 BPB_FATSz32[4];
    uint8 BPB_ExtFlags[2];
    uint8 BPB_FSVer[2];
    uint8 BPB_RootClus[4];
    uint8 BPB_FSInfo[2];
    uint8 BPB_BkBootSec[2];
    uint8 BPB_Reserved[12];
    uint8 BS_DrvNum;
    uint8 BS_Reserved1;
    uint8 BS_BootSig;
    uint8 BS_VolID[4];
    uint8 BS_VolLab[11];
    uint8 BS_FilSysType[8];
} BPB;

typedef struct FAT_directory_entry_struct {
    uint8 DIR_Name[FAT_NAME_LENGTH];
    uint8 DIR_Attr;
    uint8 DIR_NTRes;
    uint8 DIR_CrtTimeTenth;
    uint8 DIR_CrtTime[2];
    uint8 DIR_CrtDate[2];
    uint8 DIR_LstAccDate[2];
    uint8 DIR_FstClusHI[2];
    uint8 DIR_WrtTime[2];
    uint8 DIR_WrtDate[2];
    uint8 DIR_FstClusLO[2];
    uint8 DIR_FileSize[4];
} FAT_entry;

uint8 ilog2(uint32 n) {
    uint8 i = 0;
    while ((n >>= 1U) != 0)
        i++;
    return i;
}

//--------------------------------------------------------------------------------------------------------
//                                           DEBUT DU CODE
//--------------------------------------------------------------------------------------------------------

/**
 * Exercice 1
 *
 * Prend cluster et retourne son addresse en secteur dans l'archive
 * @param block le block de paramètre du BIOS
 * @param cluster le cluster à convertir en LBA
 * @param first_data_sector le premier secteur de données, donnée par la formule dans le document
 * @return le LBA
 */
uint32 cluster_to_lba(BPB *block, uint32 cluster, uint32 first_data_sector) {
    return 0;
}

/**
 * Exercice 2
 *
 * Va chercher une valeur dans la cluster chain
 * @param block le block de paramètre du système de fichier
 * @param cluster le cluster qu'on veut aller lire
 * @param value un pointeur ou on retourne la valeur
 * @param archive le fichier de l'archive
 * @return un code d'erreur
 */
error_code get_cluster_chain_value(BPB *block,
                                   uint32 cluster,
                                   uint32 *value,
                                   FILE *archive) {
    return 0;
}


/**
 * Exercice 3
 *
 * Vérifie si un descripteur de fichier FAT identifie bien fichier avec le nom name
 * @param entry le descripteur de fichier
 * @param name le nom de fichier
 * @return 0 ou 1 (faux ou vrai)
 */
bool file_has_name(FAT_entry *entry, char *name) {
    return 0;
}

/**
 * Exercice 4
 *
 * Prend un path de la forme "/dossier/dossier2/fichier.ext et retourne la partie
 * correspondante à l'index passé. Le premier '/' est facultatif.
 * @param path l'index passé
 * @param level la partie à retourner (ici, 0 retournerait dossier)
 * @param output la sortie (la string)
 * @return -1 si les arguments sont incorrects, -2 si le path ne contient pas autant de niveaux
 * -3 si out of memory
 */
error_code break_up_path(char *path, uint8 level, char **output) {
    return 0;
}


/**
 * Exercice 5
 *
 * Lit le BIOS parameter block
 * @param archive fichier qui correspond à l'archive
 * @param block le block alloué
 * @return un code d'erreur
 */
error_code read_boot_block(FILE *archive, BPB **block) {
    return 0;
}

/**
 * Exercice 6
 *
 * Trouve un descripteur de fichier dans l'archive
 * @param archive le descripteur de fichier qui correspond à l'archive
 * @param path le chemin du fichier
 * @param entry l'entrée trouvée
 * @return un code d'erreur
 */
error_code find_file_descriptor(FILE *archive, BPB *block, char *path, FAT_entry **entry) {
    return 0;
}

/**
 * Exercice 7
 *
 * Lit un fichier dans une archive FAT
 * @param entry l'entrée du fichier
 * @param buff le buffer ou écrire les données
 * @param max_len la longueur du buffer
 * @return un code d'erreur qui va contenir la longueur des donnés lues
 */
error_code
read_file(FILE *archive, BPB *block, FAT_entry *entry, void *buff, size_t max_len) {
    return 0;
}

int main(int argc, char *argv[]) {
    /*
     * Vous êtes libre de faire ce que vous voulez ici.
     */
    return 0;
}
